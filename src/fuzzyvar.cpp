/***************************************************************************
                          fuzzyvar.cpp  -  description
                             -------------------
    begin                : dom abr 13 2003
    copyright            : (C) 2003 by Oscar Germán Duarte Velasco
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <wx/wx.h>
#include "fuzzyvar.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaEtiquetas);

Etiqueta::Etiqueta(wxString str)
{
	Label=str;
	ND=new NumeroDifuso();
}

void Etiqueta::write(Mi_ofpstream &str)
{
	str << Label;
	ND->write(str);
}

void Etiqueta::read(Mi_ifpstream &str)
{
	str >> Label;
	ND->read(str);
}

/**
 * Construye una variable lingüística y autodefine los conjuntos difusos de sus etiquetas
 * \param str Nombre de la Variable Lingüística
 * \param min Extremo inferior del rango en el que se define la variable
 * \param max Extremo superior del rango en el que se define la variable
 * \param num Numero de Etiquetas
 * \see autodefinirRecto
 */
VariableLinguistica::VariableLinguistica(wxString str,float min,float max,int num)
{
	if(min>=max){min=0.0;max=1.0;}
  if(num<2){num=2;}
  Nombre=str;
	Unidades=wxT("");
	Minimo=min;
	Maximo=max;
	autodefinirRecto(num);
	EtiquetaSeleccionada=0;
	Modificador=0;
	TipoDeValor=0;
	Crisp=IntA=IntB=(min+max)/2.0;
  NumDif.trapecio(min,min,max,max);
}

BOOL VariableLinguistica::operator==(VariableLinguistica& other)
{
	int i,tam,res;
	res=((Nombre==other.Nombre) &
			(Descripcion==other.Descripcion) &
			(Unidades==other.Unidades) &
			(Minimo==other.Minimo) &
			(Maximo==other.Maximo) &
			(EtiquetaSeleccionada==other.EtiquetaSeleccionada) &
			(TipoDeValor==other.TipoDeValor) &
			(Crisp==other.Crisp) &
			(IntA==other.IntA) &
			(IntB==other.IntB) &
			(NumDif==other.NumDif) &
			(Modificador==other.Modificador));



	if(Etiquetas.GetCount()==other.Etiquetas.GetCount())
	{
		tam=Etiquetas.GetCount();
		for(i=0;i<tam;i++)
		{
			res=res & (Etiquetas.Item(i)==other.Etiquetas.Item(i));
		}
	}else
	{
		res=0;
	}
	return res;
}

void VariableLinguistica::operator=(VariableLinguistica& other)
{
	Nombre=other.Nombre;
   Descripcion=other.Descripcion;
	Unidades=other.Unidades;
	Minimo=other.Minimo;
	Maximo=other.Maximo;
	EtiquetaSeleccionada=other.EtiquetaSeleccionada;
	TipoDeValor=other.TipoDeValor;
	Crisp=other.Crisp;
	IntA=other.IntA;
	IntB=other.IntB;
	NumDif=other.NumDif;
	Modificador=other.Modificador;
  Etiquetas.Clear();
	int i,tam;
	tam=other.Etiquetas.GetCount();
	for(i=0;i<tam;i++)
	{
		Etiqueta *et;
		et=new Etiqueta;
		*et=other.Etiquetas.Item(i);
		Etiquetas.Add(et);
	}
}


/**
 * Define num etiquetas con funciones de pertenencia a trazos curvos homogéneamente espaciadas en
 * todo el Rango de la Variable
 */
void VariableLinguistica::autodefinirRecto(int num)
{
	limpiarListaEtiquetas();
	Etiqueta *et;
	float dx;
			// esta variable ayuda a calcular los soportes
			//de cada ConjuntoDifuso

	dx=(Maximo-Minimo)/(float)(2*num-1);
	int i;
        wxString cad1;

			// El primer Conjunto es L, el último es Gamma
			// y los demás son Triángulo
	cad1=wxT("Conjunto 1");
	et=new Etiqueta(cad1);
	et->ND->trapecio(Minimo, Minimo, Minimo+dx, Minimo+2*dx);
	Etiquetas.Add(et);
	for (i=1;i<(num-1);i++){
		cad1=wxT("Conjunto ");
		cad1 << i+1;
		et=new Etiqueta(cad1);
		et->ND->trapecio(Minimo+(2*i-1)*dx, Minimo+(2*i)*dx, Minimo+(2*i+1)*dx, Minimo+(2*i+2)*dx);
		Etiquetas.Add(et);
	}
	cad1=wxT("Conjunto ");
	cad1 << i+1;
	et=new Etiqueta(cad1);
	et->ND->trapecio(Maximo-2*dx, Maximo-dx, Maximo, Maximo);
	Etiquetas.Add(et);
}

///////////TMP
/**
 * Define num etiquetas con funciones de pertenencia a trazos curvos homogéneamente espaciadas en
 * todo el Rango de la Variable

 */
void VariableLinguistica::redefinirRecto()
{
  int num=Etiquetas.GetCount();
	float dx;
	dx=(Maximo-Minimo)/(float)(2*num-1);
	int i;
	Etiquetas.Item(0).ND->trapecio(Minimo, Minimo, Minimo+dx, Minimo+2*dx);
	for (i=1;i<(num-1);i++){
		Etiquetas.Item(i).ND->trapecio(Minimo+(2*i-1)*dx, Minimo+(2*i)*dx, Minimo+(2*i+1)*dx, Minimo+(2*i+2)*dx);
	}
	Etiquetas.Item(num-1).ND->trapecio(Maximo-2*dx, Maximo-dx, Maximo, Maximo);
}



///////////////

/**
 * Define num etiquetas con funciones de pertenencia a trazos rectos homogéneamente espaciadas en
 * todo el Rango de la Variable
 */
void VariableLinguistica::autodefinirCurvo(int num)
{
	limpiarListaEtiquetas();
	Etiqueta *et;
	float dx;
			// esta variable ayuda a calcular los soportes
			//de cada ConjuntoDifuso

	dx=(Maximo-Minimo)/(2*num-1);
	int i;
        wxString cad1;

			// El primer Conjunto es L, el último es Gamma
			// y los demás son Triángulo
	cad1=wxT("Conjunto 1");
	et=new Etiqueta(cad1);
	et->ND->tamano(10);
	et->ND->campana(Minimo, Minimo, Minimo+dx, Minimo+2*dx);
	Etiquetas.Add(et);
	for (i=1;i<(num-1);i++){
		cad1=wxT("Conjunto ");
		cad1 << i+1;
		et=new Etiqueta(cad1);
		et->ND->tamano(10);
		et->ND->campana(Minimo+(2*i-1)*dx, Minimo+(2*i)*dx, Minimo+(2*i+1)*dx, Minimo+(2*i+2)*dx);
		Etiquetas.Add(et);
	}
	cad1=wxT("Conjunto ");
	cad1 << i+1;
	et=new Etiqueta(cad1);
	et->ND->tamano(10);
	et->ND->campana(Maximo-2*dx, Maximo-dx, Maximo, Maximo);
	Etiquetas.Add(et);
}

/**
 * Redefine el rango de la variable, manteniendo la distribución proporcional de las etiquetas
 * y de los valores Crisp, de Intervalos y de Numeros Difusos
 */
void VariableLinguistica::nuevoRango(float nuevoMin, float nuevoMax)
{
  if(nuevoMin>=nuevoMax){return;}
	int i,j,tam,tam1;
	tam=Etiquetas.GetCount();
	float a,b,viejoMin,viejoMax,proporcion;
	NumeroDifuso *nd;
	viejoMin=Minimo;
	viejoMax=Maximo;
	proporcion=(nuevoMax-nuevoMin)/(viejoMax-viejoMin);
	for(i=0;i<tam;i++)
	{
		nd=Etiquetas.Item(i).ND;
      tam1=nd->Tamano;
      for(j=0;j<tam1;j++)
      {
        a=nuevoMin+(nd->L[j] - viejoMin)*proporcion;
        b=nuevoMin+(nd->R[j] - viejoMin)*proporcion;
        nd->L[j]=a;
        nd->R[j]=b;
      }
	}
  Crisp=nuevoMin+(Crisp - viejoMin)*proporcion;
  IntA=nuevoMin+(IntA - viejoMin)*proporcion;
  IntB=nuevoMin+(IntB - viejoMin)*proporcion;
  tam1=NumDif.Tamano;
  for(j=0;j<tam1;j++)
  {
    a=nuevoMin+(NumDif.L[j] - viejoMin)*proporcion;
    b=nuevoMin+(NumDif.R[j] - viejoMin)*proporcion;
    NumDif.L[j]=a;
    NumDif.R[j]=b;
  }

  Minimo=nuevoMin;
  Maximo=nuevoMax;
}

/**
 * Elimina todas las etiquetas de la variable linguistica
 */
void VariableLinguistica::limpiarListaEtiquetas()
{
  Etiquetas.Clear();
}

/**
 * Calcula el nmero difuso correspondiente a la etiqueta seleccionada
 * por EtiquetaSeleccionada, incluyeno el efecto del modificador
 * Lingüístico definido por Modificador
 */
NumeroDifuso *VariableLinguistica::etiqueta()
{
	NumeroDifuso *num;
	num=new NumeroDifuso();
	int i,tam;
	switch(Modificador)
	{
		case 0 : // No hay modificador
					num->copiar(Etiquetas.Item(EtiquetaSeleccionada).ND);
					break;
		case 1 : // Menor o igual = "A lo sumo"
					num->copiar(Etiquetas.Item(EtiquetaSeleccionada).ND);
					tam=num->Tamano;
					for(i=0;i<tam;i++)
					{
						num->L[i]=Minimo;
					}
					break;
		case 2 : // Mayor o igual = "Por lo menos"
					num->copiar(Etiquetas.Item(EtiquetaSeleccionada).ND);
					tam=num->Tamano;
					for(i=0;i<tam;i++)
					{
						num->R[i]=Maximo;
					}
					break;
		case 3 : // Nada

					num->trapecio(0,0,0,0);
					break;
		case 4 : // Cualquier cosa
					num->trapecio(Minimo,Minimo,Maximo,Maximo);
					break;
	}

	return num;
}
/**
 * Almacen en et la expresión correspondiente a la etiqueta seleccionada
 * por EtiquetaSeleccionada, incluyeno el efecto del modificador
 * Lingüístico definido por Modificador
 */

 void VariableLinguistica::strEtiqueta(wxString *et)
{

	switch(Modificador)
	{
		case 0 : // No hay modificador
					*et=Etiquetas.Item(EtiquetaSeleccionada).Label;
					break;
		case 1 : // Menor o igual = "A lo sumo"
					*et=wxT("A lo sumo ");
					*et+=Etiquetas.Item(EtiquetaSeleccionada).Label;
					break;
		case 2 : // Mayor o igual = "Por lo menos"
					*et=wxT("Por lo menos ");
					*et+=Etiquetas.Item(EtiquetaSeleccionada).Label;
					break;
		case 3 : // Nada

					*et=wxT("Nada");
					break;
		case 4 : // "Cualquier Cosa"
					*et=wxT("Cualquier cosa");
					break;
		default: *et=wxT("XXX");
					break;
	}
}

/**
 * Devuelve una cadena con información sobre cómo es el valor asignado a la Variable
 */
wxString VariableLinguistica::strEntrada()
{
  wxString res;
 switch(TipoDeValor)
  {
    case 0:
              res=wxT("Indefinido");
              break;
    case 1:
              res << Crisp;
              break;
    case 2:
              res << wxT("[ ") << IntA << wxT(" , ") << IntB << wxT(" ]");
              break;
    case 3:
              res << wxT("ND: ") << NumDif.valorRepresentativo(0.5,0.5) << wxT(" / ") << NumDif.ambiguedad() ;
              break;
    default:
              strEtiqueta(&res);
              break;
  }
  return res;
}

/**
 * Calculo el valor de la Variable Lingüística, segn este definido por
 * TipoDeValor: 0=Indefinido; 1=crisp; 2=intervalo; 3=numeroDifuso;
 * 4=etiqueta
 */
NumeroDifuso* VariableLinguistica::valor()
{
	NumeroDifuso *num;
	num=new NumeroDifuso();

 switch(TipoDeValor)
  {
    case 0:
            num->trapecio(Minimo,Minimo,Maximo,Maximo);
            break;
    case 1:
            num->trapecio(Crisp,Crisp,Crisp,Crisp);
            break;
    case 2:
            num->trapecio(IntA,IntA,IntB,IntB);
            break;
    case 3:
            num->copiar(&NumDif);
            break;
    case 4:
            delete num;
            num=etiqueta();
            break;
    default:
            num->trapecio(Minimo,Minimo,Maximo,Maximo);
            break;
  }
  return num;
}

/**

 * Almacena en ListaStr las frases que resultan de la Interpretación
 * Lingüística de num, con respecto a las etiquetas de la Variable
 * Lingüística
 */
void VariableLinguistica::interpretacion(wxArrayString *ListaStr,NumeroDifuso *num)
{
	int i,tam;
  ListaStr->Clear();

	wxString str1;

	// aqui debe venir el codigo de interpretacion
	float cons;
	tam=Etiquetas.GetCount();
	for(i=0;i<tam;i++)
	{
		cons=Etiquetas.Item(i).ND->consistencia(num);
//		*str1=Nombre;
//		*str1+=" es ";
		str1=wxT("");
		if(cons<(1.0/3.0))
		{
			str1+=wxT("poco posiblemente (");
		}else	if(cons<(2.0/3.0))
		{
			str1+=wxT("posiblemente (");
		}else
		{
			str1+=wxT("muy posiblemente (");
		}

		str1<< cons << wxT(") ");

		str1+=Etiquetas.Item(i).Label;
		if(cons>0.1)    // umbral para despreciar las consistencias
		{
			ListaStr->Add(str1);
		}
	}
}

/**
 * Almacena en Texto la interpretación lingüística de máxima consistencia
 * de num, con respecto a las etiquetas de la Variable Lingüística
 */

void VariableLinguistica::interpretacionMaxima(wxString *Texto,NumeroDifuso *num)
{
	float consMax=-1;
	float cons;
	int i,tam;
	tam=Etiquetas.GetCount();

	for(i=tam-1;i>=0;i--)
	{
		cons=Etiquetas.Item(i).ND->consistencia(num);
		if(cons>consMax)
		{
      	consMax=cons;
			*Texto=Etiquetas.Item(i).Label;
		}
	}
}

void VariableLinguistica::importarCadena(wxString Dato,ListaSelecciones Opciones)
{
  //primero busca coincidencia con etiquetas
  int i,tam,et;
  tam=Etiquetas.GetCount();
  for(i=0;i<tam;i++)
  {
    int cmp;
    // tipo de comparación
    switch(Opciones.Seleccion(wxT("Comparación de cadenas")))
    {
      default:
      case 0:
            cmp=Dato.Cmp(Etiquetas.Item(i).Label);
            break;
      case 1:
            cmp=Dato.CmpNoCase(Etiquetas.Item(i).Label);
            break;
    }
    if(cmp==0)
    {
      // encontró una coincidencia
      TipoDeValor=4;
      EtiquetaSeleccionada=i;
      return;
    }
  }
  // No hay coincidencia con etiqueta
  // se evala si es un nmero
  double tmp,tmp2;
  if(Dato.ToDouble(&tmp))
  {
    // es un nmero
    Crisp=(float)tmp;
    NumeroDifuso num;
    float eps=0.000001;
    num.trapecio(Crisp-eps,Crisp-eps,Crisp+eps,Crisp+eps);
    float cons,consMax;
    switch(Opciones.Seleccion(wxT("Interpretación")))
    {
      default :
      case 0:
            TipoDeValor=4;
            tam=Etiquetas.GetCount();
            consMax=-1;
            for(i=tam-1;i>=0;i--)
            {
              cons=Etiquetas.Item(i).ND->consistencia(&num);
              if(cons>=consMax)
              {
                consMax=cons;
                et=i;
              }
            }
            EtiquetaSeleccionada=et;
             break;
      case 1:
            TipoDeValor=1;
            break;
    }
    return;
  }
  // No es etiqueta ni nmero... quizás es un

  // nmero difuso (valor/ambigedad)
  wxString V,A;
  char sep='/';
  V=Dato.BeforeFirst(sep);
  A=Dato.AfterFirst(sep);
  if(V.ToDouble(&tmp) && A.ToDouble(&tmp2))
  {
    // debe construirse un Nmero difuso
    // de valor V y ambiguedad A
    // se asume simétrico y triangular
    // V es el centro
    // el soporte es A*2/3
    // se toma la mitad para sumarlo a izquierda y derecha
    float centro,soporte;
    centro=(float)tmp;
    soporte=(float)tmp2/3.0;
    NumDif.trapecio(centro-soporte,centro,centro,centro+soporte);
    float cons,consMax;
    switch(Opciones.Seleccion(wxT("Interpretación")))
    {
      default :
      case 0:
            TipoDeValor=4;
            tam=Etiquetas.GetCount();
            consMax=-1;
            for(i=tam-1;i>=0;i--)
            {
              cons=Etiquetas.Item(i).ND->consistencia(&NumDif);
              if(cons>=consMax)
              {
                consMax=cons;
                et=i;
              }
            }
            EtiquetaSeleccionada=et;
             break;
      case 1:
          TipoDeValor=3;
          break;
    }
  }
  // No se halló nada
  TipoDeValor=0;
}


void VariableLinguistica::write(Mi_ofpstream &str)
{
	int i,tam;

	str << Nombre;
  str << Descripcion;
  str << Unidades;
	str << Minimo;
	str << Maximo;
	str << EtiquetaSeleccionada;
	str << Modificador;
	str << TipoDeValor;
	str << Crisp;
  str << IntA;
  str << IntB;
  NumDif.write(str);

	tam=Etiquetas.GetCount();
	str << tam;
	for(i=0;i<tam;i++)
	{
		Etiquetas.Item(i).write(str);
	}
}

void VariableLinguistica::read(Mi_ifpstream &str)
{
	int i,tam;

	str >> Nombre;
  str >> Descripcion;
  str >> Unidades;
	str >> Minimo;
	str >> Maximo;
	str >> EtiquetaSeleccionada;
  str >> Modificador;
	str >> TipoDeValor;
	str >> Crisp;
  str >> IntA;
  str >> IntB;
  NumDif.read(str);

  Etiquetas.Clear();
	str >> tam;
	for(i=0;i<tam;i++)
	{
		Etiqueta *Et;
		Et=new Etiqueta;
		Et->read(str);
		Etiquetas.Add(Et);

	}
  /////////TMP
//  redefinirRecto();
  /////////////
}
