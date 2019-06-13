/***************************************************************************
                          micanvas.cpp  -  description
                             -------------------
    begin                : jue may 15 2003
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

#include "micanvas.h"
#if defined __WXMSW__
	#include <wx/msw/winundef.h>
#endif
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ArregloRegiones);

BEGIN_EVENT_TABLE(MiCanvas, wxScrolledWindow)
    EVT_PAINT(MiCanvas::OnPaint)
    EVT_RIGHT_DOWN(MiCanvas::OnRightDown)
    EVT_RIGHT_UP(MiCanvas::OnRightUp)
    EVT_LEFT_UP(MiCanvas::OnLeftUp)
    EVT_MOTION(MiCanvas::OnMouseMove)
    EVT_GRID_CELL_LEFT_CLICK(MiCanvas::clickCelda)
//    EVT_GRID_LABEL_LEFT_CLICK( MiCanvas::OnCellLeftClick )
END_EVENT_TABLE()

/**
 * Define a constructor for my canvas
*/
MiCanvas::MiCanvas(wxWindow *parent, wxHtmlHelpController *ayuda):
 wxScrolledWindow(parent, -1)
{
  Ayuda=ayuda;
  Proy=NULL;
  GrillaLista=NULL;
  GrillaPropiedades=NULL;
  GrillaVariables=NULL;
  GrillaMatriz=NULL;

  nodoMovil=NULL;
  posXNodoMovil=0;
  posYNodoMovil=0;
  nodoEnMovimiento=FALSE;

  Ver = VER_RED;
  VerVariable = 1;
  VistaMatriz=0;
  FlagPintarLista=1;
  FlagPintarVariables=1;
  FlagPintarMatriz=1;

  defecto();
  SetBackgroundColour(*Colores.Color(wxT("Fondo")));

  ListaColores Col;
  llenarListaColores(&Col);

  DialColores =new DialogoColores(Col,this,wxT("Colores de pantalla"));

  NoPintar=FALSE;

  Nuevo=1;
}

MiCanvas::~MiCanvas()
{
  Regiones.Empty();
  Proy=NULL;
}



/**
 * Opciones por defecto
 */
void MiCanvas::defecto()
{
  Colores.limpiar();
  definirColores();
  Fuentes.limpiar();
  definirFuentes();
  Dimensiones.limpiar();
  definirDimensiones();
  Selecciones.limpiar();
  definirSelecciones();
  HSize=Dimensiones.Dimension(wxT("Ancho Mínimo de Marco"));
  VSize=Dimensiones.Dimension(wxT("Altura Mínima de Marco"));
}




/**
 * Llena el Listado de Colores
 */
void MiCanvas::definirColores()
{
// Colores usuales
  data.SetChooseFull(TRUE);
  for (int i = 0; i < 16; i++)
  {

      wxColour colour(i*16, i*16, i*16);
      data.SetCustomColour(i, colour);
  }

// Marco exterior
  Colores.adicionarColor(wxT("Fondo"),wxColour(234,232,225));
  Colores.adicionarColor(wxT("Fondo Red"),wxColour(234,232,225));
  Colores.adicionarColor(wxT("Fondo Caso Como Red"),wxColour(234,232,225));
  Colores.adicionarColor(wxT("Fondo Caso Como Lista"),wxColour(234,232,225));
  Colores.adicionarColor(wxT("Fondo Variables"),wxColour(234,232,225));
  Colores.adicionarColor(wxT("Fondo Todas las variables"),wxColour(234,232,225));
  Colores.adicionarColor(wxT("Fondo Matrices"),wxColour(234,232,225));


  Colores.adicionarColor(wxT("Marco Exterior"),wxColour(wxT("BLACK")));
// Red
  Colores.adicionarColor(wxT("Líneas de Árbol"),wxColour(142,35,35));
  Colores.adicionarColor(wxT("Fondo de Nodos"),wxColour(wxT("WHITE")));
  Colores.adicionarColor(wxT("Fondo de Nodos de entrada"),wxColour(186,234,255));
  Colores.adicionarColor(wxT("Fondo de Enlaces"),wxColour(251,226,178));
  Colores.adicionarColor(wxT("Marco de Nodos"),wxColour(wxT("BLUE")));
  Colores.adicionarColor(wxT("Texto de Nodos"),wxColour(wxT("BLACK")));
  Colores.adicionarColor(wxT("Texto de Metodología"),wxColour(wxT("BLACK")));
// Caso Como Red
  Colores.adicionarColor(wxT("Nodo no Definido en el Caso"),wxColour(250,194,254));
  Colores.adicionarColor(wxT("Nodo es Indefinido"),wxColour(186,234,255));
  Colores.adicionarColor(wxT("Nodo es Crisp"),wxColour(241,234,201));
  Colores.adicionarColor(wxT("Nodo es Intervalo"),wxColour(204,239,215));
  Colores.adicionarColor(wxT("Nodo es Número Difuso"),wxColour(255,255,220));
  Colores.adicionarColor(wxT("Nodo es Etiqueta"),wxColour(255,215,215));
  Colores.adicionarColor(wxT("Nodo es de otro tipo"),wxColour(160,160,160));
  Colores.adicionarColor(wxT("Nodo es Calculado"),wxColour(wxT("WHITE")));
  Colores.adicionarColor(wxT("Nodo es Enlace"),wxColour(251,226,178));
  Colores.adicionarColor(wxT("Texto de Caso"),wxColour(wxT("BLACK")));
// Grilla
  Colores.adicionarColor(wxT("Propiedades"),wxColour(wxT("WHITE")));
  Colores.adicionarColor(wxT("Línea de Grilla"),wxColour(wxT("BLACK")));
  Colores.adicionarColor(wxT("Fondo de Etiqueta en Grilla"),wxColour(224,224,224));
  Colores.adicionarColor(wxT("Texto de Etiqueta en Grilla"),wxColour(wxT("BLACK")));
  Colores.adicionarColor(wxT("Texto de Celdas en Grilla"),wxColour(wxT("BLACK")));

}

/**
 * Llena el Listado de Fuentes
 */
void MiCanvas::definirFuentes()
{
  Fuentes.adicionarFuente(wxT("Nombre de Nodos"),*wxITALIC_FONT);
  Fuentes.adicionarFuente(wxT("Metodología"),*wxITALIC_FONT);
  Fuentes.adicionarFuente(wxT("Valores de Nodos"),*wxITALIC_FONT);
  Fuentes.adicionarFuente(wxT("Caso"),*wxITALIC_FONT);
// Grilla
  Fuentes.adicionarFuente(wxT("Etiqueta en Grilla"),*wxITALIC_FONT);
  Fuentes.adicionarFuente(wxT("Celdas en Grilla"),*wxITALIC_FONT);
}

/**
 * Llena el Listado de Dimensiones
 */
void MiCanvas::definirDimensiones()
{
  Dimensiones.adicionarDimension(wxT("Niveles"),4);
  Dimensiones.adicionarDimension(wxT("Ancho Mínimo de Marco"),800);
  Dimensiones.adicionarDimension(wxT("Altura Mínima de Marco"),300);
  Dimensiones.adicionarDimension(wxT("Separación Horizontal entre Nodos"),10);
  Dimensiones.adicionarDimension(wxT("Separación Vertical entre Nodos"),35);
  Dimensiones.adicionarDimension(wxT("Ancho de Caja"),40);
  Dimensiones.adicionarDimension(wxT("Ancho de Nodo"),60);
  Dimensiones.adicionarDimension(wxT("Ancho de Columnas de Valor"),80);
  Dimensiones.adicionarDimension(wxT("Ancho de Columnas de Ambigüedad"),80);

  Dimensiones.adicionarDimension(wxT("Ancho de Columnas de Interpretación"),120);
  Dimensiones.adicionarDimension(wxT("Ancho de Columnas de Interpretación Larga"),240);
  Dimensiones.adicionarDimension(wxT("Ancho de Columna de Propiedad"),80);
  Dimensiones.adicionarDimension(wxT("Ancho de Columna de Valor de Propiedad"),80);
  Dimensiones.adicionarDimension(wxT("Altura de Caja"),20);
  Dimensiones.adicionarDimension(wxT("Altura de Caja de Variable"),20);
  Dimensiones.adicionarDimension(wxT("Margen Izquierdo"),20);
  Dimensiones.adicionarDimension(wxT("Margen Superior"),50);
  Dimensiones.adicionarDimension(wxT("Margen Derecho"),20);
  Dimensiones.adicionarDimension(wxT("Margen Inferior"),50);
  Dimensiones.adicionarDimension(wxT("Grosor de Líneas del Árbol"),1);
  Dimensiones.adicionarDimension(wxT("Grosor del Marco de Nodo"),1);
  Dimensiones.adicionarDimension(wxT("Grosor del Marco Exterior"),4);
}

/**
 * Llena el Listado de Selecciones
 */
void MiCanvas::definirSelecciones()
{
  wxArrayString arr;
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));



  Selecciones.adicionarSeleccion(wxT("Usar Niveles"),wxArrayString(arr),1);
  arr.Clear();
  arr.Add(wxT("Hacia Abajo"));arr.Add(wxT("Hacia Derecha"));
  Selecciones.adicionarSeleccion(wxT("Dirección del Árbol"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Rectángulo"));arr.Add(wxT("Elipse"));
  Selecciones.adicionarSeleccion(wxT("Figura del Nodo"),wxArrayString(arr),1);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Selecciones.adicionarSeleccion(wxT("Mostrar Colores"),wxArrayString(arr),1);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Selecciones.adicionarSeleccion(wxT("Matriz con colores"),wxArrayString(arr),1);
}

/**
 * Procesa el evento de repintar la pantalla. llama a pintar()
 * @see pintar()
 */
void MiCanvas::OnPaint(wxPaintEvent&)
{
  if(NoPintar){return;}
  switch(Selecciones.Seleccion(wxT("Mostrar Colores")))
  {
    case 0:DialColores->Show(TRUE);break;
    case 1:DialColores->Show(FALSE);break;
  }
  wxPaintDC dc(this);
  PrepareDC(dc);
  ::wxSetCursor(wxCursor(wxCURSOR_WATCH));
//  if(Ver != VER_CASO_LISTA)
//  {
//    wxBeginBusyCursor();
//  }
  pintar(dc);
//  wxEndBusyCursor();
  ::wxSetCursor(wxCursor(wxCURSOR_ARROW));
  ListaColores Col;
  llenarListaColores(&Col);
  DialColores->Colores=Col;
  DialColores->Refresh();
}

void MiCanvas::OnRightDown(wxMouseEvent& event)
{
  if(Ver != VER_RED)
  {
    nodoMovil=NULL;
    posXNodoMovil=0;
    posYNodoMovil=0;
    nodoEnMovimiento=FALSE;
    return;
  }
  Proy->ProyectoModificado=TRUE;
  int i,tam;
  NodoCalculo *n;
  tam=Regiones.Count();
  for(i=0;i<tam;i++)
  {
    int x,y;
    CalcUnscrolledPosition(event.m_x,event.m_y,&x,&y);   // corregir posición por scroll de pantalla
    if(Regiones.Item(i).Rect.Contains(x,y))
    {
      nodoMovil=Regiones.Item(i).Nodo;
      posXNodoMovil=x;
      posYNodoMovil=y;
      nodoEnMovimiento=TRUE;
      wxSetCursor(*wxCROSS_CURSOR);
      return;;
    }
  }
  nodoMovil=NULL;
  posXNodoMovil=0;
  posYNodoMovil=0;
  nodoEnMovimiento=FALSE;
  return;
}

void MiCanvas::OnRightUp(wxMouseEvent& event)
{
  if((Ver !=VER_RED) || (nodoEnMovimiento==FALSE) || (nodoEnMovimiento==NULL))
  {
    wxSetCursor(*wxSTANDARD_CURSOR);
    nodoMovil=NULL;
    nodoEnMovimiento=FALSE;
    return;
  }
  int x,y;
  CalcUnscrolledPosition(event.m_x,event.m_y,&x,&y);   // corregir posición por scroll de pantalla
  if(wxWindow::GetRect().Contains(wxPoint(x,y)))
  {
    int dx,dy;
    dx=(int)(x-posXNodoMovil)/(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
    dy=(int)(y-posYNodoMovil)/(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));

    nodoMovil->OffsetPosicionEnNivel=nodoMovil->OffsetPosicionEnNivel+dx;


    nodoMovil->OffsetNivel=nodoMovil->OffsetNivel+dy;
    if(nodoMovil->OffsetPosicionEnNivel<0)
    {
      nodoMovil->OffsetPosicionEnNivel=0;
    }
    if(nodoMovil->OffsetNivel<0)
    {
      nodoMovil->OffsetNivel=0;
    }
  }
  wxSetCursor(*wxSTANDARD_CURSOR);

  nodoMovil=NULL;
  nodoEnMovimiento=FALSE;
  llenarRegiones();
  Refresh();
}

void MiCanvas::OnMouseMove(wxMouseEvent& event)
{
  Proy->ProyectoModificado=TRUE;
  int i,tam;
  NodoCalculo *n;
  VariableLinguistica *v;
  NumeroDifuso *num;
  tam=Regiones.Count();
  wxString cad=wxT("");
  for(i=0;i<tam;i++)
  {
    int x,y;
    CalcUnscrolledPosition(event.m_x,event.m_y,&x,&y);   // corregir posición por scroll de pantalla
    if(Regiones.Item(i).Rect.Contains(x,y))
    {
      if (Regiones.Item(i).Nodo!=NULL)
      {
        cad=Regiones.Item(i).Nodo->NombreExtendido;
      }
      i=tam;
     }
  }
   wxLogStatus(cad);
}

/**
 * Procesa el evento de levantar el botón derecho del ratón.
 * Verifica si el evento a ocurrido en una elemento de Regiones, para
 * asociar la acción a esa región
 */
void MiCanvas::OnLeftUp(wxMouseEvent& event)
{
  Proy->ProyectoModificado=TRUE;
  int i,tam;
  NodoCalculo *n;
  VariableLinguistica *v;
  NumeroDifuso *num;
  tam=Regiones.Count();
  for(i=0;i<tam;i++)
  {
    int x,y;
    CalcUnscrolledPosition(event.m_x,event.m_y,&x,&y);   // corregir posición por scroll de pantalla
    if(Regiones.Item(i).Rect.Contains(x,y))

    {
     wxString cad;
      switch(Ver)
      {
        case VER_RED:
//                               cad << Regiones.Item(i).Nodo->VarCalculada.Nombre;
                               if (Regiones.Item(i).Nodo!=NULL)
                               {
                                DialogoNodo dlg(Regiones.Item(i).Nodo,Proy,this,wxT("PRUEBA"), Ayuda);
                                dlg.ShowModal();
                                Proy->calcularTodo();

                                llenarRegiones();
                                Refresh();
                               }
                               break;
        case VER_CASO_RED:
                               n=Regiones.Item(i).Nodo;
                               v=Regiones.Item(i).Variable;
                               if(n->FormaDeCalculo==2)
                               {
                                 wxString EstNom=n->EstrategiaCalculo;
                                 int iii,tttam,EstNum=-1;
                                 tttam=Proy->Estrategias.GetCount();
                                 for(iii=0;iii<tttam;iii++)
                                 {
                                   if(Proy->Estrategias.Item(iii).Nombre==EstNom)
                                   {
                                     EstNum=iii;
                                     iii=tttam;
                                   }
                                 }
                                 if(EstNum>=0)
                                 {
                                   Proy->calcularTodo();
                                   Proy->NumEstrategia=EstNum;
                                   llenarRegiones();
                                   Refresh();
                                 }
                               }else if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
                               {
                                 if(v==NULL)
                                 {
                                    // no hay variable en el caso
                                   if(wxMessageBox(wxT("Desea definir la Variable de Entrada?"),wxT("No hay variable"),wxYES_NO)==wxYES)
                                   {
                                     v=new VariableLinguistica();
                                     Proy->Casos.Item(Proy->NumCaso).Variables.Add(v);
                                     *v=n->VarCalculada;
                                     Regiones.Item(i).Variable=v;
                                     DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
                                     dlg.ShowModal();
                                     Proy->calcularTodo();
                                     llenarRegiones();
                                     Refresh();
                                   }
                                 }else{
                                 // Variable

                                   DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
                                   dlg.ShowModal();
                                   Proy->calcularTodo();
                                   llenarRegiones();
                                   Refresh();
                                 }
                               }else
                               {
                                 v=&n->VarCalculada;
                                 num=Regiones.Item(i).Numero;
                                 DialogoNumeroMostrar dlg(v,num,this,wxT("PRUEBA"), Ayuda);
                                 dlg.ShowModal();
                               }
                               break;
        case VER_CASO_LISTA:
        case VER_CASO_VARIABLES_TODAS:
        case VER_CASO_VARIABLES: break;
/*                               if (Regiones.Item(i).Variable==NULL)
                               {
                                  wxTextEntryDialog dlg(this,Proy->Casos.Item(Proy->NumCaso).Generalidades.nombre(Regiones.Item(i).Propiedad),"Modifque el Valor de la propiedad",Proy->Casos.Item(Proy->NumCaso).Generalidades.valor(Regiones.Item(i).Propiedad));
                                  if(dlg.ShowModal()==wxID_OK)
                                  {
                                    cad=dlg.GetValue();
                                    Proy->Casos.Item(Proy->NumCaso).Generalidades.modificarValor(cad,Regiones.Item(i).Propiedad);
                                  }
                               }else

                               {
                                DialogoVariable dlg(Regiones.Item(i).Variable,Proy,this,"PRUEBA");
                                dlg.ShowModal();
                                Proy->calcularTodo();
                               }

                               llenarRegiones();
                               Refresh();
                               break;*/
        case VER_MATRIZ: break;
/*                               cad << Regiones.Item(i).Nodo->VarCalculada.Nombre;
                               cad << "=" << Regiones.Item(i).Numero->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);
                               cad << " / " << Regiones.Item(i).Numero->ambiguedad();
                               break;*/
        default:
                               cad << wxT("Región Indefinida");
                               break;
      }
      i=tam;
     }
  }
}

void MiCanvas::clickCelda(wxGridEvent &ev)
{
  int grilla=ev.GetId();
  switch(grilla)
  {
    case MICANVAS_GRILLA_LISTA: clickCeldaLista(ev);break;
    case MICANVAS_GRILLA_PROPIEDADES: clickCeldaPropiedades(ev);break;
    case MICANVAS_GRILLA_VARIABLES: clickCeldaVariables(ev);break;
    case MICANVAS_GRILLA_MATRIZ: clickCeldaMatriz(ev);break;
  }
}

void MiCanvas::clickCeldaLista(wxGridEvent &ev)
{
  Proy->ProyectoModificado=TRUE;
  int fil,col;
  fil=ev.GetRow();
  col=ev.GetCol();
  NodoCalculo *n;
  VariableLinguistica *v;
  NumeroDifuso *num;
  wxString cad,cadStatus;
  cadStatus=wxT("");
//  switch(Ver)
//  {
//      case VER_CASO_LISTA:

          if( fil >=0 & col ==0)
          {
            n=Regiones.Item(fil).Nodo;
            cadStatus=n->NombreExtendido;
          }

          if( fil >=0 & col >0)
          {
            n=Regiones.Item(fil).Nodo;
            v=Regiones.Item(fil).Variable;

            if(n->FormaDeCalculo==2)
            {
              wxMessageBox(wxT("El Nodo es un Enlace"),wxT("Aviso"));
            }else if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
            {
              if(v==NULL)
              {
                 // no hay variable   ??????
                 if(wxMessageBox(wxT("Desea definir la Variable de Entrada?"),wxT("No hay variable"),wxYES_NO)==wxYES)
                 {
                   v=new VariableLinguistica();
                   Proy->Casos.Item(Proy->NumCaso).Variables.Add(v);
                   *v=n->VarCalculada;
                   Regiones.Item(fil).Variable=v;
                   DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
                   dlg.ShowModal();
                   Proy->calcularTodo();
                   llenarRegiones();
                   Refresh();
                 }
              }else{
              // Variable
                DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
                dlg.ShowModal();
                Proy->calcularTodo();
                llenarRegiones();
                Refresh();
              }
            }else
            {
              v=&n->VarCalculada;

              num=Regiones.Item(fil).Numero;

              DialogoNumeroMostrar dlg(v,num,this,wxT("PRUEBA"), Ayuda);
              dlg.ShowModal();
           }
            Refresh();
            GrillaLista->SelectBlock(fil,col,fil,col);
          }
//          break;
//  }
  wxLogStatus(cadStatus);
}

void MiCanvas::clickCeldaPropiedades(wxGridEvent &ev)
{
  Proy->ProyectoModificado=TRUE;
  int i,tam;
  i=ev.GetRow();
  tam=Proy->Casos.Item(Proy->NumCaso).Generalidades.tamano();
  if(i>=0 && i<tam)
  {
    wxString nom,val;
    nom=Proy->Casos.Item(Proy->NumCaso).Generalidades.nombre(i);

    val=Proy->Casos.Item(Proy->NumCaso).Generalidades.valor(i);
    wxTextEntryDialog dlg(this,nom,_("Entrada de información"),val);
    dlg.ShowModal();
    val=dlg.GetValue();
    Proy->Casos.Item(Proy->NumCaso).Generalidades.modificarValor(val,i);
    llenarRegiones();
    Refresh();
  }
}

void MiCanvas::clickCeldaVariables(wxGridEvent &ev)
{
  Proy->ProyectoModificado=TRUE;
  int i,tam;
  i=ev.GetRow();
  tam=Proy->Casos.Item(Proy->NumCaso).Variables.GetCount();
  if(i>=0 && i<tam)
  {
    VariableLinguistica *v;
    v=&Proy->Casos.Item(Proy->NumCaso).Variables.Item(i);
    DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
    dlg.ShowModal();
    Proy->calcularTodo();
    llenarRegiones();
    Refresh();
  }
}

void MiCanvas::clickCeldaMatriz(wxGridEvent &ev)
{

  Proy->ProyectoModificado=TRUE;
  int fil,col;
  fil=ev.GetRow();
  col=ev.GetCol();
  NodoCalculo *n;
  VariableLinguistica *v;
  NumeroDifuso *num;
  if(fil>1 && col>0)
  {
    int it;
    int numCols=GrillaMatriz->GetNumberCols()-1;
    it=(fil-2)*numCols + (col-1);
    int numCas;
    numCas=Regiones.Item(it).PosY;
    Caso *caso;
    caso=&Proy->Casos.Item(numCas);

    Regiones.Item(it).Variable=NULL;
    int j,tam2;
    tam2=caso->Variables.GetCount();
    Regiones.Item(it).Variable=NULL;
    for(j=0;j<tam2;j++)
    {
      if(Regiones.Item(it).Nodo->VarCalculada.Nombre==caso->Variables.Item(j).Nombre)
      {
        Regiones.Item(it).Variable=&caso->Variables.Item(j);
        j=tam2;
      }
    }

    VariableLinguistica *v;
    v=Regiones.Item(it).Variable;
    n=Regiones.Item(it).Nodo;

    if( fil >=0 & col >0)
    {
      n=Regiones.Item(it).Nodo;
      v=Regiones.Item(it).Variable;
      if(n->FormaDeCalculo==2)
      {
        wxMessageBox(wxT("El Nodo es un Enlace"),wxT("Aviso"));
      }else if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
      {
        if(v==NULL)
        {
           // no hay variable   ??????
           if(wxMessageBox(wxT("Desea definir la Variable de Entrada?"),wxT("No hay variable"),wxYES_NO)==wxYES)
           {
             v=new VariableLinguistica();
             Proy->Casos.Item(numCas).Variables.Add(v);
             *v=n->VarCalculada;
             Regiones.Item(it).Variable=v;
             DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
             dlg.ShowModal();
             Proy->calcularTodo();
             llenarRegiones();
             Refresh();
           }
        }else{
        // Variable

          DialogoVariable dlg(v,Proy,this,wxT("PRUEBA"), Ayuda);
          dlg.ShowModal();
          Proy->calcularTodo();
          llenarRegiones();
          Refresh();
        }
      }else
      {
        v=&n->VarCalculada;
        num=Regiones.Item(it).Numero;
        DialogoNumeroMostrar dlg(v,num,this,wxT("PRUEBA"), Ayuda);
        dlg.ShowModal();
     }
      Refresh();
      GrillaMatriz->SelectBlock(fil,col,fil,col);
    }
  }else if(fil==0 && col>0)
  {
//    wxMessageBox("est","est");
  }else if(fil==1 && col>0)
  {
//    wxMessageBox("est_nod","est_nod");
  }else if(fil>1 && col==0)
  {
//    wxMessageBox("cas","cas");
  }else
  {
//    wxMessageBox("proy","proy");
  }
}

/**
 * Función empleada para definir qué colores se muestran con DialogoColores
 */
void MiCanvas::llenarListaColores(ListaColores *Col)
{
  Col->limpiar();
  wxString nom;
  nom=wxT("Nodo no Definido en el Caso");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Indefinido");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Crisp");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Intervalo");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Número Difuso");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Etiqueta");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es de otro tipo");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Calculado");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Nodo es Enlace");
  Col->adicionarColor(nom,*Colores.Color(nom));
  nom=wxT("Fondo de Nodos de entrada");
  Col->adicionarColor(nom,*Colores.Color(nom));
}


/**
 * Llena Regiones, segn el tipo de vista que esté ctiva
 * @see Ver

 * @see llenarRegionesRed()
 * @see llenarRegionesCasoRed()
 * @see llenarRegionesCasoLista()
 * @see llenarRegionesMatriz()
 */
void MiCanvas::llenarRegiones()
{
  switch(Ver)
  {
    case VER_RED:
      llenarRegionesRed();
      break;
    case VER_CASO_RED:

      llenarRegionesCasoRed();
      break;
    case VER_CASO_LISTA:
      llenarRegionesCasoLista();
      break;

    case VER_CASO_VARIABLES:
      llenarRegionesCasoVariables();
      break;
    case VER_CASO_VARIABLES_TODAS:
      llenarRegionesCasoVariablesTodas();
      break;
    case VER_MATRIZ:
      llenarRegionesMatriz();
      break;
    default:
      llenarRegionesRed();
      break;
  }
}

/**
 * A partir de la Estrategia que se desea visualizar, construye una Region por cada Nodo de
 * esta Estrategia. El rectángulo asociado no se asigna aqui; se debe asignar en pintarRed();
 * @see pintarRed()
 */


void MiCanvas::llenarRegionesRed()
{
  Regiones.Empty();
  Region *reg;
  NodoCalculo *arbol;
  Estrategia *Est;
  Est=&(Proy->Estrategias.Item(Proy->NumEstrategia));
  ListaNodos ListaRed;

  if(Est!=NULL)
  {
    arbol=Est->Grafo.arbol();
    arbol->limpiarNivel();
    arbol->calcularNivel();
    arbol->calcularPosicionEnNivel();
    arbol->llenarArreglo(&ListaRed);
  }
  int i,tam,profX=0,profY=0;
  tam=ListaRed.GetCount();
  for(i=0;i<tam;i++)

  {
    if(ListaRed.Item(i).Nivel > profY)
    {
      profY=ListaRed.Item(i).Nivel;
    }
    if(ListaRed.Item(i).PosicionEnNivel > profX)
    {
      profX=ListaRed.Item(i).PosicionEnNivel;
    }
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= ListaRed.Item(i).Nivel)
    {
      reg=new Region(&ListaRed.Item(i));
      reg->Tipo=Ver;
      Regiones.Add(reg);
    }
  }
  for(i=0;i<tam;i++)

  {
    ListaRed.Detach(0);
  }
  if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&profX,&profY);}
  HSize=Dimensiones.Dimension(wxT("Margen Izquierdo"))+profX*Dimensiones.Dimension(wxT("Ancho de Caja"))+(profX-1)*Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos"))+Dimensiones.Dimension(wxT("Margen Derecho"));
  if(Ver==VER_RED)
  {
    VSize=Dimensiones.Dimension(wxT("Margen Superior"))+profY*Dimensiones.Dimension(wxT("Altura de Caja"))+(profY-1)*Dimensiones.Dimension(wxT("Separación Vertical entre Nodos"))+Dimensiones.Dimension(wxT("Margen Inferior"));
  }else
  {
    VSize=Dimensiones.Dimension(wxT("Margen Superior"))+profY*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")))+(profY-1)*Dimensiones.Dimension(wxT("Separación Vertical entre Nodos"))+Dimensiones.Dimension(wxT("Margen Inferior"));
  }
  if(HSize<Dimensiones.Dimension(wxT("Ancho Mínimo de Marco")))
  {
      HSize=Dimensiones.Dimension(wxT("Ancho Mínimo de Marco"));
  }

  if(VSize<Dimensiones.Dimension(wxT("Altura Mínima de Marco")))
  {
      VSize=Dimensiones.Dimension(wxT("Altura Mínima de Marco"));
  }
//  SetSize(HSize,VSize);
  HSize=(int)(HSize/20)+1;HSize=HSize*20;
  VSize=(int)(VSize/20)+1;VSize=VSize*20;
  SetScrollbars(20,20,(int)(HSize/20),(int)(VSize/20));
}



/**
 * Llena las Regiones para ver el Caso como Red
 */
void MiCanvas::llenarRegionesCasoRed()
{

  llenarRegionesRed();
  Caso *cas;
  cas=&Proy->Casos.Item(Proy->NumCaso);
  int i,tam;
  tam=Regiones.GetCount();
  for(i=0;i<tam;i++)
  {
    Regiones.Item(i).Variable=NULL;
    int j,tam2;
    tam2=cas->Variables.GetCount();

    Regiones.Item(i).Variable=NULL;
    for(j=0;j<tam2;j++)
    {
      if(Regiones.Item(i).Nodo->VarCalculada.Nombre==cas->Variables.Item(j).Nombre)
      {
        Regiones.Item(i).Variable=&cas->Variables.Item(j);
        j=tam2;
      }
    }
    NumeroDifuso *N;
    N=Regiones.Item(i).Nodo->calcularCaso(cas);
    Regiones.Item(i).Numero=N;
  }
}


/**
 * Llena las Regiones para visualizar El Caso como Lista
 */
void MiCanvas::llenarRegionesCasoLista()
{
  llenarRegionesCasoRed();


  HSize=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Dimensiones.Dimension(wxT("Ancho de Nodo"))+Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"))+Dimensiones.Dimension(wxT("Ancho de Columnas de Ambigüedad"))+Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación"))+Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación Larga"))+Dimensiones.Dimension(wxT("Margen Derecho"));
  VSize=Dimensiones.Dimension(wxT("Margen Superior"))+Dimensiones.Dimension(wxT("Margen Inferior"))+1.2*Dimensiones.Dimension(wxT("Altura de Caja"))*(Regiones.GetCount() + 1);
  HSize=(int)(HSize/20)+1;HSize=HSize*20;
  VSize=(int)(VSize/20)+1;VSize=VSize*20;
  SetScrollbars(20,20,(int)(HSize/20),(int)(VSize/20));
}

/**
 * Llena las Regiones para visualizar Las variables del caso con las estrategia seleccionada
 */
void MiCanvas::llenarRegionesCasoVariables()
{
  llenarRegionesCasoVariablesTodas();
}

/**

 * Llena las Regiones para visualizar todas las variables del caso
 */
void MiCanvas::llenarRegionesCasoVariablesTodas()
{
  Regiones.Empty();

  Region *reg;
  Estrategia* est;
  Caso* caso;

  est=&Proy->Estrategias.Item(Proy->NumEstrategia);
  caso=&Proy->Casos.Item(Proy->NumCaso);
  int i,tam;
  tam=caso->Generalidades.tamano();
  for(i=0;i<tam;i++)
  {
    reg=new Region(NULL);
    reg->Tipo=Ver;
    Regiones.Add(reg);
    reg->Propiedad=i;
  }
  tam=caso->Variables.GetCount();
  for(i=0;i<tam;i++)
  {
    if(Ver==VER_CASO_VARIABLES_TODAS || est->Grafo.buscarNodo(caso->Variables.Item(i).Nombre) != NULL)
    {
      reg=new Region(NULL);


      reg->Tipo=Ver;
      Regiones.Add(reg);

      reg->Variable=&caso->Variables.Item(i);
    }
  }
  HSize=Dimensiones.Dimension(wxT("Margen Izquierdo"))+2*Dimensiones.Dimension(wxT("Ancho de Columna de Propiedad"))+2*Dimensiones.Dimension(wxT("Ancho de Columna de Valor de Propiedad"))+Dimensiones.Dimension(wxT("Margen Derecho"))+3*Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos"));
  VSize=Dimensiones.Dimension(wxT("Margen Superior"))+Dimensiones.Dimension(wxT("Margen Inferior"))+Dimensiones.Dimension(wxT("Altura de Caja"))*(Regiones.GetCount() + 2);
  HSize=(int)(HSize/20)+1;HSize=HSize*20;
  VSize=(int)(VSize/20)+1;VSize=VSize*20;
  SetScrollbars(20,20,(int)(HSize/20),(int)(VSize/20));
}


/**
 * No Implementada
 */
void MiCanvas::llenarRegionesMatriz()
{
  Regiones.Empty();
  Region *reg;
  Estrategia* Est;
  NumeroDifuso *N;
  Caso* caso;
  int i,j,k,tam,tam2,tam3,contador=0;
  tam=Proy->Casos.GetCount();
  tam2=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    caso=&Proy->Casos.Item(i);

    contador=0;
    for(j=0;j<tam2;j++)
    {
      Est=&(Proy->Estrategias.Item(j));
      ListaNodos ListaRed;
      Est->Grafo.llenarArreglo(&ListaRed);
      tam3=ListaRed.GetCount();
      for(k=0;k<tam3;k++)
      {
        reg=new Region(&ListaRed.Item(k));
        reg->Tipo=Ver;
        N=ListaRed.Item(k).calcularCaso(caso);
        reg->Numero=N;

        reg->PosX=contador+k;
        reg->PosY=i;
        Regiones.Add(reg);
      }
      contador+=tam3;
      for(k=0;k<tam3;k++)
      {
        ListaRed.Detach(0);
      }
    }
  }
  int HX,VX;
  switch(VistaMatriz)
  {
      case 0:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 1:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Ambigüedad"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 2:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 3:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación Larga"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      default:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
  }

  HSize=Dimensiones.Dimension(wxT("Margen Izquierdo"))+HX*(contador+1)+Dimensiones.Dimension(wxT("Margen Derecho"));
  VSize=Dimensiones.Dimension(wxT("Margen Superior"))+VX*(tam + 3)+Dimensiones.Dimension(wxT("Margen Inferior"));

  HSize=(int)(HSize/20)+1;HSize=HSize*20;
  VSize=(int)(VSize/20)+1;VSize=VSize*20;
  SetScrollbars(20,20,(int)(HSize/20),(int)(VSize/20));
}


/**
 * Función utilitaria para intercambiar los valores de x1 y x2

 */
void MiCanvas::intercambiar(int *x1, int *x2)
{
  int tmp=*x1;

  *x1=*x2;
  *x2=tmp;
}

/**
 * Cambia la orientación de la información desplegada
 */
//void MiCanvas::cambiarOrientacion()
//{
//  Orientacion=(Orientacion+1)%2;
//  llenarRegiones();
//}


/**

 * Pinta el fondo de pantalla y llama a las funciones auxiliares para pintar
 * segn el tipo de vista deseado
 * @see Ver
 * @see pintarRegionesRed()
 * @see pintarRegionesCasoRed()
 * @see pintarRegionesCasoLista()
 * @see pintarRegionesMatriz()
 */
void MiCanvas::pintar(wxPaintDC &dc)
{
  SetBackgroundColour(*Colores.Color(wxT("Fondo")));
  wxBrush Brush;
  wxPen Pen;
  int ht,vt;
  GetSize(&ht,&vt);
  switch(Ver)
  {
    case VER_RED:
      Brush.SetColour(*Colores.Color(wxT("Fondo Red")));
      break;
    case VER_CASO_RED:
      Brush.SetColour(*Colores.Color(wxT("Fondo Caso Como Red")));
      break;
    case VER_CASO_LISTA:
      Brush.SetColour(*Colores.Color(wxT("Fondo Caso Como Lista")));
      break;
    case VER_CASO_VARIABLES:
      Brush.SetColour(*Colores.Color(wxT("Fondo Variables")));
      break;
    case VER_CASO_VARIABLES_TODAS:
      Brush.SetColour(*Colores.Color(wxT("Fondo Todas las variables")));
      break;
    case VER_MATRIZ:
      Brush.SetColour(*Colores.Color(wxT("Fondo Matrices")));
      break;
    default:
      Brush.SetColour(*Colores.Color(wxT("Fondo")));
      break;
  }
  if(Nuevo)
  {
    llenarRegiones();
    Nuevo=0;
  }

  dc.SetBrush (Brush);
  dc.DrawRectangle(0,0,HSize,VSize);
  Pen.SetWidth(Dimensiones.Dimension(wxT("Grosor del Marco Exterior")));
  Pen.SetColour(*Colores.Color(wxT("Marco Exterior")));
  dc.SetPen (Pen);
  dc.DrawRectangle(0,0,HSize,VSize);

  switch(Ver)
  {
    case VER_RED:

      FlagPintarLista=1;

      FlagPintarVariables=1;
      FlagPintarMatriz=1;
      delete GrillaLista;
      delete GrillaPropiedades;

      delete GrillaVariables;
      delete GrillaMatriz;
      GrillaLista=NULL;
      GrillaPropiedades=NULL;
      GrillaVariables=NULL;
      GrillaMatriz=NULL;
      pintarRed(dc);
      break;
    case VER_CASO_RED:
      FlagPintarLista=1;
      FlagPintarVariables=1;
      FlagPintarMatriz=1;
      delete GrillaLista;
      delete GrillaPropiedades;
      delete GrillaVariables;
      delete GrillaMatriz;
      GrillaLista=NULL;
      GrillaPropiedades=NULL;
      GrillaVariables=NULL;
      GrillaMatriz=NULL;
      pintarCasoRed(dc);
      break;
    case VER_CASO_LISTA:
      FlagPintarVariables=1;
      FlagPintarMatriz=1;
      delete GrillaPropiedades;
      delete GrillaVariables;
      delete GrillaMatriz;
      GrillaPropiedades=NULL;
      GrillaVariables=NULL;
      GrillaMatriz=NULL;
      pintarCasoLista2(dc);
      FlagPintarLista=0;
      break;
    case VER_CASO_VARIABLES:
      FlagPintarLista=1;
      FlagPintarMatriz=1;
      delete GrillaLista;
      delete GrillaMatriz;

      GrillaLista=NULL;
      GrillaMatriz=NULL;
      pintarCasoVariables2(dc);
      FlagPintarVariables=0;
      break;
    case VER_CASO_VARIABLES_TODAS:
      FlagPintarLista=1;
      FlagPintarMatriz=1;
      delete GrillaLista;
      delete GrillaMatriz;
      GrillaLista=NULL;
      GrillaMatriz=NULL;
      pintarCasoVariablesTodas2(dc);
      FlagPintarVariables=0;
      break;
    case VER_MATRIZ:
      FlagPintarLista=1;
      FlagPintarVariables=1;

      delete GrillaLista;
      delete GrillaPropiedades;
      delete GrillaVariables;
      GrillaLista=NULL;
      GrillaPropiedades=NULL;
      GrillaVariables=NULL;
      pintarMatriz2(dc);
      FlagPintarMatriz=0;
      break;
    default:
      break;
  }
}

/**
 * Pinta la Estrategia seleccionada, como una red.
 * Esta función pinta las líneas y los nodos (como rectángulos).
 * También asigna los rectángulos asociados a cada Región de Regiones.
 * Sólo se pintan los nodos definidos por Niveles
 * @see Regiones
 * @ see Niveles

 */
void MiCanvas::pintarRed(wxPaintDC &dc)
{
  wxBrush Brush;
  wxPen Pen;
  dc.SetBrush (Brush);
  dc.SetPen(Pen);
  int i,tam;
  tam=Regiones.GetCount();

  NodoCalculo *n;
// Líneas
  Pen.SetColour(*Colores.Color(wxT("Líneas de Árbol")));
  Pen.SetWidth(Dimensiones.Dimension(wxT("Grosor de Líneas del Árbol")));
  dc.SetPen(Pen);
  for(i=0;i<tam;i++)
  {
    n=Regiones.Item(i).Nodo;
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= n->Nivel)
    {
      int Nx,Ny,Cx,Cy,Cxf,Cyf;
      Ny=n->Nivel-1;
      Nx=n->PosicionEnNivel-1;
      if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&Nx,&Ny);}
      Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Nx*(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
      Cy=Dimensiones.Dimension(wxT("Margen Superior"))+Ny*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));
      int j,tam2;
      tam2=n->NodosPadre.GetCount();
      for(j=0;j<tam2;j++)
      {
        int Nxf,Nyf;
        Nyf=n->NodosPadre.Item(j).Nivel-1;

        Nxf=n->NodosPadre.Item(j).PosicionEnNivel-1;
        if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&Nxf,&Nyf);}

        Cxf=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Nxf*(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
        Cyf=Dimensiones.Dimension(wxT("Margen Superior"))+Nyf*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));
        switch(Selecciones.Seleccion(wxT("Dirección del Árbol")))
        {
          case 0:
            dc.DrawLine(Cx+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cy,Cxf+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cyf+Dimensiones.Dimension(wxT("Altura de Caja")));
            break;
          case 1:
            dc.DrawLine(Cx,Cy+0.5*Dimensiones.Dimension(wxT("Altura de Caja")),Cxf+Dimensiones.Dimension(wxT("Ancho de Caja")),Cyf+0.5*Dimensiones.Dimension(wxT("Altura de Caja")));
            break;
          default:
            dc.DrawLine(Cx+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cy,Cxf+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cyf+Dimensiones.Dimension(wxT("Altura de Caja")));
            break;
        }
      }
    }
  }
// Cajas
  Pen.SetColour(*Colores.Color(wxT("Marco de Nodos")));
  Pen.SetWidth(Dimensiones.Dimension(wxT("Grosor del Marco de Nodo")));
  dc.SetPen(Pen);
  dc.SetFont(*Fuentes.Fuente(wxT("Nombre de Nodos")));
  for(i=0;i<tam;i++)
  {
    n=Regiones.Item(i).Nodo;
    wxColour col;
    switch(n->FormaDeCalculo)
    {
      case 0: col=*Colores.Color(wxT("Fondo de Nodos de entrada"));break;
      case 1: col=*Colores.Color(wxT("Fondo de Nodos"));break;
      case 2: col=*Colores.Color(wxT("Fondo de Enlaces"));break;
      default: col=*Colores.Color(wxT("Fondo de Nodos"));break;
    }
    if(n->NodosDeCalculo.GetCount()==0 && n->FormaDeCalculo!=2)
    {
      col=*Colores.Color(wxT("Fondo de Nodos de entrada"));
    }
    Brush.SetColour(col);
    dc.SetBrush (Brush);
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= n->Nivel)
    {
      int Nx,Ny,Cx,Cy;
      Ny=n->Nivel-1;
      Nx=n->PosicionEnNivel-1;
      if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&Nx,&Ny);}
      Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Nx*(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
      Cy=Dimensiones.Dimension(wxT("Margen Superior"))+Ny*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));
      switch(Selecciones.Seleccion(wxT("Figura del Nodo")))
      {
          case 0 :dc.DrawRectangle(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja")));break;
          case 1 :dc.DrawEllipse(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja")));break;
          default :dc.DrawRectangle(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja")));break;
      }
      wxRegion rectTmp(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja")));   // aqui se asigna la región
      Regiones.Item(i).Rect=rectTmp;
      dc.SetTextForeground(*Colores.Color(wxT("Texto de Nodos")));
      wxString cad;
      cad=n->VarCalculada.Nombre;
      int w,h;
      do
      {
        dc.GetTextExtent(cad,&w,&h);
        if(w>(Dimensiones.Dimension(wxT("Ancho de Caja"))-2*Dimensiones.Dimension(wxT("Grosor del Marco de Nodo")))){cad=cad.Left(cad.Len()-1);}
      }while(w>(Dimensiones.Dimension(wxT("Ancho de Caja"))-2*Dimensiones.Dimension(wxT("Grosor del Marco de Nodo"))));
      dc.DrawText(cad,Cx+Dimensiones.Dimension(wxT("Ancho de Caja"))/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
    }
  }
  dc.SetTextForeground(*Colores.Color(wxT("Texto de Metodología")));
  dc.SetFont(*Fuentes.Fuente(wxT("Metodología")));
  wxString cad;
  cad = wxT("Metodología: ");
  cad << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre;
  int w,h;
  dc.GetTextExtent(cad,&w,&h);
  dc.DrawText(cad,Dimensiones.Dimension(wxT("Margen Izquierdo")),(Dimensiones.Dimension(wxT("Margen Superior"))-h)/2);

}

/**
 * Pinta el Caso como Red
 */
void MiCanvas::pintarCasoRed(wxPaintDC& dc)
{
  wxBrush Brush;
  wxPen Pen;
  int i,tam;
  tam=Regiones.GetCount();
  NodoCalculo *n;
  VariableLinguistica *v;
  NumeroDifuso *num;
// Líneas
  Pen.SetColour(*Colores.Color(wxT("Líneas de Árbol")));
  Pen.SetWidth(Dimensiones.Dimension(wxT("Grosor de Lìneas del Árbol")));

  dc.SetPen(Pen);
  for(i=0;i<tam;i++)
  {
    n=Regiones.Item(i).Nodo;
    v=Regiones.Item(i).Variable;
    num=Regiones.Item(i).Numero;
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= n->Nivel)
    {
      int Nx,Ny,Cx,Cy,Cxf,Cyf;
      Ny=n->Nivel-1;
      Nx=n->PosicionEnNivel-1;
      if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&Nx,&Ny);}
      Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Nx*(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
      Cy=Dimensiones.Dimension(wxT("Margen Superior"))+Ny*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));
      int j,tam2;
      tam2=n->NodosPadre.GetCount();
      for(j=0;j<tam2;j++)
      {
        int Nxf,Nyf;
        Nyf=n->NodosPadre.Item(j).Nivel-1;
        Nxf=n->NodosPadre.Item(j).PosicionEnNivel-1;
        if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&Nxf,&Nyf);}


        Cxf=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Nxf*(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
        Cyf=Dimensiones.Dimension(wxT("Margen Superior"))+Nyf*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));
        switch(Selecciones.Seleccion(wxT("Dirección del Árbol")))
        {
          case 0:
            dc.DrawLine(Cx+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cy,Cxf+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cyf+Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")));
            break;
          case 1:
            dc.DrawLine(Cx,Cy+0.5*Dimensiones.Dimension(wxT("Altura de Caja"))+0.5*Dimensiones.Dimension(wxT("Altura de Caja de Variable")),Cxf+Dimensiones.Dimension(wxT("Ancho de Caja")),Cyf+0.5*Dimensiones.Dimension(wxT("Altura de Caja"))+0.5*Dimensiones.Dimension(wxT("Altura de Caja de Variable")));
            break;
          default:
            dc.DrawLine(Cx+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cy,Cxf+0.5*Dimensiones.Dimension(wxT("Ancho de Caja")),Cyf+Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")));
            break;
        }
      }
    }
  }
// Cajas
  Pen.SetColour(*Colores.Color(wxT("Marco de Nodos")));
  dc.SetPen(Pen);


  Pen.SetWidth(Dimensiones.Dimension(wxT("Grosor del Marco de Nodo")));
  for(i=0;i<tam;i++)
  {

    n=Regiones.Item(i).Nodo;
    v=Regiones.Item(i).Variable;
    num=Regiones.Item(i).Numero;
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= n->Nivel)
    {
      int Nx,Ny,Cx,Cy;
      Ny=n->Nivel-1;
      Nx=n->PosicionEnNivel-1;
      if(Selecciones.Seleccion(wxT("Dirección del Árbol"))){intercambiar(&Nx,&Ny);}
      Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Nx*(Dimensiones.Dimension(wxT("Ancho de Caja"))+Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos")));
      Cy=Dimensiones.Dimension(wxT("Margen Superior"))+Ny*(Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable"))+Dimensiones.Dimension(wxT("Separación Vertical entre Nodos")));


      if(n->FormaDeCalculo==2)
      {
        Brush.SetColour(*Colores.Color(wxT("Nodo es Enlace")));  // Nodo enlace a otra estrategia
      }
      else if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
      {
        if(v==NULL)
        {
          Brush.SetColour(*Colores.Color(wxT("Nodo no Definido en el Caso")));  // No hay Variable definida
        }else{
          switch(v->TipoDeValor)
          {
            case 0:Brush.SetColour(*Colores.Color(wxT("Nodo es Indefinido")));break;  // indefinido
            case 1:Brush.SetColour(*Colores.Color(wxT("Nodo es Crisp")));break;  // crisp
            case 2:Brush.SetColour(*Colores.Color(wxT("Nodo es Intervalo")));break;  // intervalo
            case 3:Brush.SetColour(*Colores.Color(wxT("Nodo es Número Difuso")));break;  // nmero difuso

            case 4:Brush.SetColour(*Colores.Color(wxT("Nodo es Etiqueta")));break;  // etiqueta
            default : Brush.SetColour(*Colores.Color(wxT("Nodo es de otro tipo")));break;  // nodo de otro tipo
          }
        }
      }else
      {
        Brush.SetColour(*Colores.Color(wxT("Nodo es Calculado")));  // Nodo calculado
      }

      dc.SetBrush(Brush);
      switch(Selecciones.Seleccion(wxT("Figura del Nodo")))
      {
          case 0 : dc.DrawRectangle(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")));break;
          case 1 : dc.DrawEllipse(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")));break;

          default : dc.DrawRectangle(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")));break;
      }
      wxRegion rectTmp(Cx,Cy,Dimensiones.Dimension(wxT("Ancho de Caja")),Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable")));   // aqui se asigna la región
      Regiones.Item(i).Rect=rectTmp;
      dc.SetTextForeground(*Colores.Color(wxT("Texto de Nodos")));
      dc.SetFont(*Fuentes.Fuente(wxT("Nombre de Nodos")));
      wxString cad;
      cad=n->VarCalculada.Nombre;
      int w,h;
      do
      {
        dc.GetTextExtent(cad,&w,&h);
        if(w>(Dimensiones.Dimension(wxT("Ancho de Caja"))-2*Dimensiones.Dimension(wxT("Grosor del Marco de Nodo")))){cad=cad.Left(cad.Len()-1);}
      }while(w>(Dimensiones.Dimension(wxT("Ancho de Caja"))-2*Dimensiones.Dimension(wxT("Grosor del Marco de Nodo"))));
      dc.DrawText(cad,Cx+Dimensiones.Dimension(wxT("Ancho de Caja"))/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
      cad=wxT("");


      switch(VerVariable)
      {
        case 1: n->VarCalculada.interpretacionMaxima(&cad,num);break;
        case 2: cad << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);break;
        case 3: cad << num->ambiguedad();
                   break;
//        case 3: cad << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);
//                   cad << " / " << num->ambiguedad();
//                   break;
        default: n->VarCalculada.interpretacionMaxima(&cad,num);break;
      }

      dc.SetFont(*Fuentes.Fuente(wxT("Valores de Nodos")));
      do
      {
        dc.GetTextExtent(cad,&w,&h);
        if(w>(Dimensiones.Dimension(wxT("Ancho de Caja"))-2*Dimensiones.Dimension(wxT("Grosor del Marco de Nodo")))){cad=cad.Left(cad.Len()-1);}
      }while(w>(Dimensiones.Dimension(wxT("Ancho de Caja"))-2*Dimensiones.Dimension(wxT("Grosor del Marco de Nodo"))));
      dc.DrawText(cad,Cx+Dimensiones.Dimension(wxT("Ancho de Caja"))/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))+Dimensiones.Dimension(wxT("Altura de Caja de Variable"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>

    }
  }
  int w,h;
  wxString cad;

  dc.SetTextForeground(*Colores.Color(wxT("Texto de Metodología")));
  dc.SetFont(*Fuentes.Fuente(wxT("Metodología")));
  cad = wxT("Metodología: ");
  cad << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre ;
  dc.GetTextExtent(cad,&w,&h);
  dc.DrawText(cad,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*1/4-h/2);

  dc.SetTextForeground(*Colores.Color(wxT("Texto de Caso")));
  dc.SetFont(*Fuentes.Fuente(wxT("Caso")));
  cad = wxT("Caso: ");
  cad << Proy->Casos.Item(Proy->NumCaso).Nombre;
  dc.GetTextExtent(cad,&w,&h);
  dc.DrawText(cad,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*2/4-h/2);

  switch(VerVariable)

  {

    case 1 : cad = wxT("Interpretación Lingüìstica");break;
    case 2 : cad = wxT("Valor representativo");break;
    case 3 : cad = wxT("Ambigüedad");break;
    default : cad = wxT("Interpretación");break;
  }
  dc.GetTextExtent(cad,&w,&h);
  dc.DrawText(cad,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*3/4-h/2);
}

/**
 * Pinta el Caso como Lista
 */
void MiCanvas::pintarCasoLista(wxPaintDC &dc)
{

  dc.SetPen(* wxGREEN_PEN);
  int i,j,tam;
  int Cx,Cy;
  int HX[5];
  HX[0]=Dimensiones.Dimension(wxT("Ancho de Nodo"));HX[1]=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));HX[2]=Dimensiones.Dimension(wxT("Ancho de Columnas de Ambigedad"));HX[3]=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación"));HX[4]=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación Larga"));

  wxString cad[5];
  cad[0]=CANVAS_NODO;cad[1]=CANVAS_VALOR;cad[2]=CANVAS_AMBIGUEDAD;cad[3]=CANVAS_INTMAXIMA;cad[4]=CANVAS_INTERPRETA;
  tam=Regiones.GetCount();
  NodoCalculo *n;
  VariableLinguistica *v;
  NumeroDifuso *num;
//  Títulos
  Cx=Dimensiones.Dimension(wxT("Margen Izquierdo")); Cy=Dimensiones.Dimension(wxT("Margen Superior"));
  for(i=0;i<5;i++)
  {
    int w,h;
    if(i>0){Cx+=HX[i-1];}
    dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID)); dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja"))); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja")));
    do{dc.GetTextExtent(cad[i],&w,&h); if(w>HX[i]){cad[i]=cad[i].Left(cad[i].Len()-1);}}while(w>HX[i]);
    dc.DrawText(cad[i],Cx+HX[i]/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  }
// Celdas
  for(j=0;j<tam;j++)
  {
    n=Regiones.Item(j).Nodo;
    v=Regiones.Item(j).Variable;
    num=Regiones.Item(j).Numero;
    Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"));Cy=Dimensiones.Dimension(wxT("Margen Superior"))+Dimensiones.Dimension(wxT("Altura de Caja"))*(j+1);
    wxRegion rectTmp(Cx,Cy,HX[0]+HX[1]+HX[2]+HX[3]+HX[4],Dimensiones.Dimension(wxT("Altura de Caja")));   // aqui se asigna la región
    Regiones.Item(j).Rect=rectTmp;
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= n->Nivel)
    {
      cad[0]=n->VarCalculada.Nombre;
      cad[1]=wxT("");cad[1] << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);
      cad[2]=wxT("");cad[2] << num->ambiguedad();
      cad[3]=wxT("");n->VarCalculada.interpretacionMaxima(cad+3,num);
      wxArrayString tmp;

      n->VarCalculada.interpretacion(&tmp,num);
      cad[4]=wxT("");
      for(i=0;(unsigned int)i<tmp.GetCount();i++)
      {
        cad[4] << tmp.Item(i) << wxT("- ");
      }
      for(i=0;i<5;i++)
      {
        int w,h;

        if(i>0){Cx+=HX[i-1];}
        if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
        {
          if(v==NULL)
          {
            dc.SetBrush (wxBrush(wxT("BLUE"), wxSOLID) );  // No hay Variable definida

          }else
          {
            switch(v->TipoDeValor)
            {

              case 0 : dc.SetBrush (wxBrush(wxT("CYAN"), wxSOLID) );break;   // indefinido
              case 1 : dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) );break;   // crisp
              case 2 : dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) );break;   // intervalo
              case 3 : dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) );break;   // numero difuso
              case 4 : dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) );break;   // etiqueta
              default : dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) );break;

            }
          }
        }else

        {
          dc.SetBrush (wxBrush(* wxLIGHT_GREY, wxSOLID) );

        }
        dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja"))); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja")));
        do{dc.GetTextExtent(cad[i],&w,&h); if(w>HX[i]){cad[i]=cad[i].Left(cad[i].Len()-1);}}while(w>HX[i]);

        dc.DrawText(cad[i],Cx+HX[i]/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
      }
    }
  }
  dc.SetTextForeground(*Colores.Color(wxT("Texto de Caso")));
  dc.SetFont(*Fuentes.Fuente(wxT("Caso")));
  int w,h;
  wxString cad2;

  cad2 = wxT("Metodología: ");
  cad2 << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre ;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*1/4-h/2);

  cad2 = wxT("Caso: ");
  cad2 << Proy->Casos.Item(Proy->NumCaso).Nombre;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*2/4-h/2);

}


void MiCanvas::llenarGrillaCasoLista2()
{
  wxColour col;
  int i,j,tam,tam2;
  int HX[5];
  HX[0]=Dimensiones.Dimension(wxT("Ancho de Nodo"));HX[1]=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));HX[2]=Dimensiones.Dimension(wxT("Ancho de Columnas de Ambigedad"));HX[3]=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación"));HX[4]=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación Larga"));

  wxString cad[5];
  cad[0]=CANVAS_NODO;cad[1]=CANVAS_VALOR;cad[2]=CANVAS_AMBIGUEDAD;cad[3]=CANVAS_INTMAXIMA;cad[4]=CANVAS_INTERPRETA;

  tam=Regiones.GetCount();
  tam2=GrillaLista->GetNumberRows();

  for(i=0;i<(tam-tam2);i++)
  {
    GrillaLista->InsertRows();
  }
  for(i=0;i<(tam2-tam);i++)
  {
    GrillaLista->DeleteRows();
  }

//  Títulos
  GrillaLista->SetMargins(10,10);

  GrillaLista->SetGridLineColour(*Colores.Color(wxT("Línea de Grilla")));
  GrillaLista->SetLabelBackgroundColour(*Colores.Color(wxT("Fondo de Etiqueta en Grilla")));
  GrillaLista->SetLabelTextColour(*Colores.Color(wxT("Texto de Etiqueta en Grilla")));
  GrillaLista->SetCellTextColour(*Colores.Color(wxT("Texto de Celdas en Grilla")));
  GrillaLista->SetLabelFont(*Fuentes.Fuente(wxT("Etiqueta en Grilla")));

  GrillaLista->SetDefaultCellFont(*Fuentes.Fuente(wxT("Celdas en Grilla")));

  GrillaLista->SetRowLabelSize(5);
  GrillaLista->SetDefaultRowSize(Dimensiones.Dimension(wxT("Altura de Caja")));
  for(i=0;i<5;i++)
  {
    GrillaLista->SetColSize(i,HX[i]);
    GrillaLista->SetColLabelValue(i,cad[i]);
  }
  GrillaLista->SetColFormatFloat(1,6,2);
  GrillaLista->SetColFormatFloat(2,6,2);
// Celdas
  for(j=0;j<tam;j++)
  {
    NodoCalculo *n;
    VariableLinguistica *v ;
    NumeroDifuso *num;

    n=Regiones.Item(j).Nodo;
    v=Regiones.Item(j).Variable;
    num=Regiones.Item(j).Numero;
    if(Selecciones.Seleccion(wxT("Usar Niveles"))==1 || Dimensiones.Dimension(wxT("Niveles")) >= n->Nivel)
    {
      GrillaLista->SetRowLabelValue(j,wxT(" "));
      cad[0]=n->VarCalculada.Nombre;
      cad[1]=wxT("");cad[1] << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);
      cad[2]=wxT("");cad[2] << num->ambiguedad();
      cad[3]=wxT("");n->VarCalculada.interpretacionMaxima(cad+3,num);
      wxArrayString tmp;
      n->VarCalculada.interpretacion(&tmp,num);
      cad[4]=wxT("");
      for(i=0;(unsigned int)i<tmp.GetCount();i++)
      {

        cad[4] << tmp.Item(i) << wxT("- ");
      }
      for(i=0;i<5;i++)
      {
        if(n->FormaDeCalculo==2)
        {
          col=*Colores.Color(wxT("Nodo es Enlace"));  // Nodo enlace a otra estrategia
        }
        else if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
        {

          if(v==NULL)
          {
            col=*Colores.Color(wxT("Nodo no Definido en el Caso"));
          }else
          {
            switch(v->TipoDeValor)
            {
              case 0 : col=*Colores.Color(wxT("Nodo es Indefinido"));break;   // indefinido
              case 1 : col=*Colores.Color(wxT("Nodo es Crisp"));break;   // crisp
              case 2 : col=*Colores.Color(wxT("Nodo es Intervalo"));break;   // intervalo
              case 3 : col=*Colores.Color(wxT("Nodo es Número Difuso"));break;   // numero difuso
              case 4 : col=*Colores.Color(wxT("Nodo es Etiqueta"));break;   // etiqueta
              default : col=*Colores.Color(wxT("Nodo es de otro tipo"));break;
            }
          }

        }else
        {
          col=*Colores.Color(wxT("Nodo es Calculado"));  // Nodo calculado
        }
        GrillaLista->SetCellBackgroundColour(j,i, col);
//        GrillaLista->SetCellFont(j,i,*Fuentes.Fuente(wxT("Valores de Nodos"));
        GrillaLista->SetCellValue(j,i,cad[i]);
      }


      GrillaLista->SetReadOnly(j,i,TRUE);
    }else
    {
      // no se pinta borrar?
    }
  }
}


/**
 * Pinta el Caso como Lista. Versión con wxGrid
 * tiene problemas con el Refresh():
 * Si se habilita siempre se cuelga;
 * Si se inhabilita, no se actualiza cuando se necesita...
 */
void MiCanvas::pintarCasoLista2(wxPaintDC &dc)
{
  if(FlagPintarLista)
  {
     if(GrillaLista !=NULL)
     {
       GrillaLista->Destroy();
       delete GrillaLista;
     }

     int tam;
     tam=Regiones.GetCount();
     GrillaLista = new wxGrid(this,MICANVAS_GRILLA_LISTA,wxPoint(Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))),wxSize(HSize-Dimensiones.Dimension(wxT("Margen Izquierdo"))-Dimensiones.Dimension(wxT("Margen Derecho")),VSize-Dimensiones.Dimension(wxT("Margen Superior"))-Dimensiones.Dimension(wxT("Margen Inferior"))));
     GrillaLista->CreateGrid(tam,5);
     GrillaLista->SetEditable(FALSE);
     GrillaLista->Refresh();

  }

  llenarGrillaCasoLista2();

  wxString cad2;
  int w,h;

  dc.SetTextForeground(*Colores.Color(wxT("Texto de Metodología")));
  dc.SetFont(*Fuentes.Fuente(wxT("Metodología")));
  cad2 = wxT("Metodología: ");
  cad2 << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre ;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*1/4-h/2);

  dc.SetTextForeground(*Colores.Color(wxT("Texto de Caso")));
  dc.SetFont(*Fuentes.Fuente(wxT("Caso")));
  cad2 = wxT("Caso: ");
  cad2 << Proy->Casos.Item(Proy->NumCaso).Nombre;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*2/4-h/2);
}

//


/**
 * Pinta Las Variables del Caso con la Estrategia Seleccionada
 */
void MiCanvas::pintarCasoVariables(wxPaintDC &dc)

{
  pintarCasoVariablesTodas(dc);
}

void MiCanvas::pintarCasoVariables2(wxPaintDC &dc)
{
  pintarCasoVariablesTodas2(dc);
}

/**
 * Pinta Todas las Variables del Caso

 */
void MiCanvas::pintarCasoVariablesTodas(wxPaintDC &dc)
{
  dc.SetPen(* wxGREEN_PEN);
  int i,j,tam;
  int Cx,Cy;
  int HX[5];
  HX[0]=Dimensiones.Dimension(wxT("Ancho de Columna de Propiedad"));HX[1]=Dimensiones.Dimension(wxT("Ancho de Columna de Valor de Propiedad"));
  wxString cad[2];
  tam=Regiones.GetCount();
  Caso *caso;

  VariableLinguistica *v;
  caso=&Proy->Casos.Item(Proy->NumCaso);
//  Títulos Generalidades
  cad[0]=CANVAS_PROPIEDAD;cad[1]=CANVAS_PROPVALOR;

  Cx=Dimensiones.Dimension(wxT("Margen Izquierdo")); Cy=Dimensiones.Dimension(wxT("Margen Superior"));
  for(i=0;i<2;i++)
  {
    int w,h;
    if(i>0){Cx+=HX[i-1];}
    dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja"))); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja")));
    do{dc.GetTextExtent(cad[i],&w,&h); if(w>HX[i]){cad[i]=cad[i].Left(cad[i].Len()-1);}}while(w>HX[i]);
    dc.DrawText(cad[i],Cx+HX[i]/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  }

// Generalidades
  tam=caso->Generalidades.tamano();
  for(j=0;j<tam;j++)
  {
    int loc=Regiones.Item(j).Propiedad;

    cad[0]=caso->Generalidades.nombre(loc);
    cad[1]=caso->Generalidades.valor(loc);
    Cx=Dimensiones.Dimension(wxT("Margen Izquierdo")); Cy+=Dimensiones.Dimension(wxT("Altura de Caja"));
    wxRegion rectTmp(Cx,Cy,HX[0]+HX[1],Dimensiones.Dimension(wxT("Altura de Caja")));   // aqui se asigna la región
    Regiones.Item(j).Rect=rectTmp;
    for(i=0;i<2;i++)
    {
      int w,h;
      if(i>0){Cx+=HX[i-1];}
      dc.SetBrush (wxBrush(wxT("CYAN"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja"))); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja")));
      do{dc.GetTextExtent(cad[i],&w,&h); if(w>HX[i]){cad[i]=cad[i].Left(cad[i].Len()-1);}}while(w>HX[i]);
      dc.DrawText(cad[i],Cx+HX[i]/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
    }
  }
//  Títulos Variables
  cad[0]=CANVAS_VARIABLE;cad[1]=CANVAS_VARVALOR;
  Cx=Dimensiones.Dimension(wxT("Margen Izquierdo")); Cy+=Dimensiones.Dimension(wxT("Margen Superior"));
  for(i=0;i<2;i++)
  {
    int w,h;

    if(i>0){Cx+=HX[i-1];}
    dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja"))); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja")));
    do{dc.GetTextExtent(cad[i],&w,&h); if(w>HX[i]){cad[i]=cad[i].Left(cad[i].Len()-1);}}while(w>HX[i]);
    dc.DrawText(cad[i],Cx+HX[i]/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  }
// Variables
  int inicio=tam;
  int fin=Regiones.GetCount();
  for(j=inicio;j<fin;j++)
  {
    v=Regiones.Item(j).Variable;

    cad[0]=v->Nombre;
    cad[1]=v->strEntrada();

    Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"));Cy+=Dimensiones.Dimension(wxT("Altura de Caja"));
    wxRegion rectTmp(Cx,Cy,HX[0]+HX[1],Dimensiones.Dimension(wxT("Altura de Caja")));   // aqui se asigna la región
    Regiones.Item(j).Rect=rectTmp;
    for(i=0;i<2;i++)

    {
      int w,h;
      if(i>0){Cx+=HX[i-1];}
      dc.SetBrush (wxBrush(wxT("CYAN"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja"))); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX[i],Dimensiones.Dimension(wxT("Altura de Caja")));
      do{dc.GetTextExtent(cad[i],&w,&h); if(w>HX[i]){cad[i]=cad[i].Left(cad[i].Len()-1);}}while(w>HX[i]);
      dc.DrawText(cad[i],Cx+HX[i]/2-w/2,Cy+Dimensiones.Dimension(wxT("Altura de Caja"))/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
    }
  }
  wxString cad2;
  cad2 = wxT("Caso: ");
  cad2 << Proy->Casos.Item(Proy->NumCaso).Nombre;
  if(Ver==VER_CASO_VARIABLES)
  {
    cad2 << wxT("   Metodología: ");
    cad2 << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre;
  }
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),2);
}

void MiCanvas::llenarGrillaCasoVariables2()
{
  wxColour col;
  int i,j,tam,tam2;
  int HX[2];
  HX[0]=Dimensiones.Dimension(wxT("Ancho de Columna de Propiedad"));HX[1]=Dimensiones.Dimension(wxT("Ancho de Columna de Valor de Propiedad"));
  wxString cad[2];
  Estrategia* est;
  Caso* caso;

  est=&Proy->Estrategias.Item(Proy->NumEstrategia);
  caso=&Proy->Casos.Item(Proy->NumCaso);

//////////////////// PROPIEDADES //////////////////

//  Títulos
  GrillaPropiedades->SetMargins(10,10);
  GrillaPropiedades->SetGridLineColour(*Colores.Color(wxT("Línea de Grilla")));
  GrillaPropiedades->SetLabelBackgroundColour(*Colores.Color(wxT("Fondo de Etiqueta en Grilla")));
  GrillaPropiedades->SetLabelTextColour(*Colores.Color(wxT("Texto de Etiqueta en Grilla")));
  GrillaPropiedades->SetCellTextColour(*Colores.Color(wxT("Texto de Celdas en Grilla")));
  GrillaPropiedades->SetLabelFont(*Fuentes.Fuente(wxT("Etiqueta en Grilla")));
  GrillaPropiedades->SetDefaultCellFont(*Fuentes.Fuente(wxT("Celdas en Grilla")));

  GrillaPropiedades->SetRowLabelSize(5);
  GrillaPropiedades->SetDefaultRowSize(Dimensiones.Dimension(wxT("Altura de Caja")));

  cad[0]=wxT("Propiedad");
  cad[1]=wxT("Valor");
  for(i=0;i<2;i++)
  {
    GrillaPropiedades->SetColSize(i,HX[i]);
    GrillaPropiedades->SetColLabelValue(i,cad[i]);
  }
  GrillaPropiedades->SetColFormatFloat(2,6,2);

  tam=caso->Generalidades.tamano();
  tam2=GrillaPropiedades->GetNumberRows();

  for(i=0;i<(tam-tam2);i++)
  {
    GrillaPropiedades->InsertRows();
  }
  for(i=0;i<(tam2-tam);i++)
  {
    GrillaPropiedades->DeleteRows();
  }

  tam=caso->Generalidades.tamano();
  col=*Colores.Color(wxT("Propiedades"));


  for(j=0;j<tam;j++)
  {

    int loc=Regiones.Item(j).Propiedad;
    cad[0]=caso->Generalidades.nombre(loc);
    cad[1]=caso->Generalidades.valor(loc);
    GrillaPropiedades->SetCellBackgroundColour(j,0, col);
    GrillaPropiedades->SetCellBackgroundColour(j,1, col);
    GrillaPropiedades->SetCellValue(j,0,cad[0]);
    GrillaPropiedades->SetCellValue(j,1,cad[1]);
  }

//////////////////// VARIABLES //////////////////

//  Títulos
  GrillaVariables->SetMargins(10,10);
  GrillaVariables->SetGridLineColour(*Colores.Color(wxT("Línea de Grilla")));
  GrillaVariables->SetLabelBackgroundColour(*Colores.Color(wxT("Fondo de Etiqueta en Grilla")));
  GrillaVariables->SetLabelTextColour(*Colores.Color(wxT("Texto de Etiqueta en Grilla")));
  GrillaVariables->SetCellTextColour(*Colores.Color(wxT("Texto de Celdas en Grilla")));
  GrillaVariables->SetLabelFont(*Fuentes.Fuente(wxT("Etiqueta en Grilla")));
  GrillaVariables->SetDefaultCellFont(*Fuentes.Fuente(wxT("Celdas en Grilla")));

  GrillaVariables->SetRowLabelSize(5);
  GrillaVariables->SetDefaultRowSize(Dimensiones.Dimension(wxT("Altura de Caja")));

  cad[0]=wxT("Variable");
  cad[1]=wxT("Valor");
  for(i=0;i<2;i++)
  {
    GrillaVariables->SetColSize(i,HX[i]);
    GrillaVariables->SetColLabelValue(i,cad[i]);
  }
  GrillaVariables->SetColFormatFloat(2,6,2);


  tam=caso->Variables.GetCount();

  ListaVariables Vars;
  for(i=0;i<tam;i++)
  {
    if(Ver==VER_CASO_VARIABLES_TODAS || est->Grafo.buscarNodo(caso->Variables.Item(i).Nombre) != NULL)
    {
      Vars.Add(caso->Variables.Item(i));
    }
  }

  tam=Vars.GetCount();
  tam2=GrillaVariables->GetNumberRows();

  for(i=0;i<(tam-tam2);i++)

  {
    GrillaVariables->InsertRows();
  }
  for(i=0;i<(tam2-tam);i++)
  {
    GrillaVariables->DeleteRows();
  }


  for(j=0;j<tam;j++)
  {
    cad[0]=Vars.Item(0).Nombre;
    cad[1]=Vars.Item(0).strEntrada();

    switch(Vars.Item(0).TipoDeValor)
    {
      case 0 : col=*Colores.Color(wxT("Nodo es Indefinido"));break;   // indefinido
      case 1 : col=*Colores.Color(wxT("Nodo es Crisp"));break;   // crisp
      case 2 : col=*Colores.Color(wxT("Nodo es Intervalo"));break;   // intervalo
      case 3 : col=*Colores.Color(wxT("Nodo es Número Difuso"));break;   // numero difuso
      case 4 : col=*Colores.Color(wxT("Nodo es Etiqueta"));break;   // etiqueta
      default : col=*Colores.Color(wxT("Nodo es de otro tipo"));break;
    }
    Vars.Detach(0);

    GrillaVariables->SetCellBackgroundColour(j,0, col);
    GrillaVariables->SetCellBackgroundColour(j,1, col);
    GrillaVariables->SetCellValue(j,0,cad[0]);
    GrillaVariables->SetCellValue(j,1,cad[1]);
  }


}

void MiCanvas::pintarCasoVariablesTodas2(wxPaintDC &dc)
{
  Caso *caso;
  caso=&Proy->Casos.Item(Proy->NumCaso);
  if(FlagPintarVariables)
  {
     if(GrillaPropiedades !=NULL)
     {
       GrillaPropiedades->Destroy();
       delete GrillaPropiedades;
     }

     int tam;
     tam=caso->Generalidades.tamano();
     GrillaPropiedades = new wxGrid(this,MICANVAS_GRILLA_PROPIEDADES,wxPoint(Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))),wxSize((Dimensiones.Dimension(wxT("Ancho de Columna de Propiedad"))*2+16),(VSize-Dimensiones.Dimension(wxT("Margen Superior"))-Dimensiones.Dimension(wxT("Margen Inferior")))));

     GrillaPropiedades->CreateGrid(tam,2);
     GrillaPropiedades->SetEditable(FALSE);
     GrillaPropiedades->Refresh();

     if(GrillaVariables !=NULL)
     {
       GrillaVariables->Destroy();
       delete GrillaVariables;
     }

     int posx=Dimensiones.Dimension(wxT("Ancho de Columna de Propiedad"))+Dimensiones.Dimension(wxT("Ancho de Columna de Valor de Propiedad"))+3*Dimensiones.Dimension(wxT("Separación Horizontal entre Nodos"));

     tam=caso->Variables.GetCount();
//     GrillaVariables = new wxGrid(this,MICANVAS_GRILLA_VARIABLES,wxPoint(posx+Dimensiones.Dimension(wxT("Margen Izquierdo"),Dimensiones.Dimension(wxT("Margen Superior")),wxSize((HSize-Dimensiones.Dimension(wxT("Margen Izquierdo"))-Dimensiones.Dimension(wxT("Margen Derecho"))/2,(VSize-Dimensiones.Dimension(wxT("Margen Superior"))-Dimensiones.Dimension(wxT("Margen Inferior"))));
     GrillaVariables = new wxGrid(this,MICANVAS_GRILLA_VARIABLES,wxPoint(posx+Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))),wxSize((Dimensiones.Dimension(wxT("Ancho de Columna de Valor de Propiedad"))*2+16),(VSize-Dimensiones.Dimension(wxT("Margen Superior"))-Dimensiones.Dimension(wxT("Margen Inferior")))));
     GrillaVariables->CreateGrid(tam,2);
     GrillaVariables->SetEditable(FALSE);
     GrillaVariables->Refresh();
  }

  llenarGrillaCasoVariables2();

  wxString cad2;
  int w,h;
  dc.SetTextForeground(*Colores.Color(wxT("Texto de Metodología")));
  dc.SetFont(*Fuentes.Fuente(wxT("Metodología")));
  cad2 = wxT("Metodología: ");
  cad2 << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre ;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*1/4-h/2);

  dc.SetTextForeground(*Colores.Color(wxT("Texto de Caso")));
  dc.SetFont(*Fuentes.Fuente(wxT("Caso")));
  cad2 = wxT("Caso: ");
  cad2 << Proy->Casos.Item(Proy->NumCaso).Nombre;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*2/4-h/2);
}

/**
 * Pintar la Matriz
 */
void MiCanvas::pintarMatriz(wxPaintDC &dc)
{
  dc.SetPen(* wxGREEN_PEN);
  int i,tam;
  wxString cad;
  NodoCalculo *n;

  int Cx,Cy,HX,VX,w,h;
//títulos de casos
  tam=Proy->Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    HX=Dimensiones.Dimension(wxT("Ancho de Nodo"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));
    Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"));Cy=Dimensiones.Dimension(wxT("Margen Superior"))+VX*(i+2);
    cad=Proy->Casos.Item(i).Nombre;
    if(cad==wxT("")){cad=wxT("NN");}
    dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX,VX); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX,VX);


    do{dc.GetTextExtent(cad,&w,&h); if(w>HX){cad=cad.Left(cad.Len()-1);}}while(w>HX);
    dc.DrawText(cad,Cx+HX/2-w/2,Cy+VX/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  }
//títulos de estrategias y nodos
  switch(VistaMatriz)
  {
      case 0:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;

      case 1:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Ambigedad"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 2:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 3:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación Larga"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      default:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;

  }
  tam=Proy->Estrategias.GetCount();
  int contador=0;
  Estrategia *Est;
  for(i=0;i<tam;i++)
  {
    Est=&(Proy->Estrategias.Item(i));

    ListaNodos ListaRed;
    Est->Grafo.llenarArreglo(&ListaRed);
    int k,tam3;
    tam3=ListaRed.GetCount();
    for(k=0;k<tam3;k++)
    {
      Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Dimensiones.Dimension(wxT("Ancho de Nodo"))+HX*(contador+k);Cy=Dimensiones.Dimension(wxT("Margen Superior"))+VX*(1);
      cad=ListaRed.Item(k).VarCalculada.Nombre;

      dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX,VX); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX,VX);
      do{dc.GetTextExtent(cad,&w,&h); if(w>HX){cad=cad.Left(cad.Len()-1);}}while(w>HX);
      dc.DrawText(cad,Cx+HX/2-w/2,Cy+VX/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
    }
    Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+Dimensiones.Dimension(wxT("Ancho de Nodo"))+HX*(contador);Cy=Dimensiones.Dimension(wxT("Margen Superior"));
    cad=Est->Nombre;
    if(cad==wxT("")){cad=wxT("NN");}
    int HXTemp=HX;

    HX=HXTemp*tam3;


    dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX,VX); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX,VX);
    do{dc.GetTextExtent(cad,&w,&h); if(w>HX){cad=cad.Left(cad.Len()-1);}}while(w>HX);
    dc.DrawText(cad,Cx+HX/2-w/2,Cy+VX/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
    HX=HXTemp;
    contador+=tam3;
    for(k=0;k<tam3;k++)
    {
      ListaRed.Detach(0);
    }
  }

// celdas centrales
  tam=Regiones.GetCount();
  for(i=0;i<tam;i++)
  {

    Cx=Dimensiones.Dimension(wxT("Margen Izquierdo"))+HX*(Regiones.Item(i).PosX)+Dimensiones.Dimension(wxT("Ancho de Nodo"));

    Cy=Dimensiones.Dimension(wxT("Margen Superior"))+VX*(Regiones.Item(i).PosY+2);
    NumeroDifuso *num;
    num=Regiones.Item(i).Numero;
    n=Regiones.Item(i).Nodo;
    cad=wxT("");
    wxArrayString tmp;
    int j;
    switch(VistaMatriz)
    {
        case 0: cad << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);break;

        case 1: cad << num->ambiguedad();break;
        case 2: n->VarCalculada.interpretacionMaxima(&cad,num);break;
        case 3:
                   n->VarCalculada.interpretacion(&tmp,num);
                   cad=wxT("");
                   for(j=0;(unsigned int)j<tmp.GetCount();j++)
                   {
                     cad << tmp.Item(j) << wxT("- ");
                   }
                    break;
        default: cad << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);break;
    }
    wxRegion rectTmp(Cx,Cy,HX,VX);   // aqui se asigna la región
    Regiones.Item(i).Rect=rectTmp;
    dc.SetBrush (wxBrush(wxT("WHITE"), wxSOLID) ); dc.DrawRectangle(Cx,Cy,HX,VX); dc.SetPen(* wxBLACK_PEN);  dc.DrawRectangle(Cx,Cy,HX,VX);
    do{dc.GetTextExtent(cad,&w,&h); if(w>HX){cad=cad.Left(cad.Len()-1);}}while(w>HX);
    dc.DrawText(cad,Cx+HX/2-w/2,Cy+VX/2-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  }

}


void MiCanvas::llenarGrillaCasoMatriz2()
{
  wxColour col;
  wxString cad;

  GrillaMatriz->SetMargins(10,10);
  GrillaMatriz->SetGridLineColour(*Colores.Color(wxT("Línea de Grilla")));
  GrillaMatriz->SetLabelBackgroundColour(*Colores.Color(wxT("Fondo de Etiqueta en Grilla")));
  GrillaMatriz->SetLabelTextColour(*Colores.Color(wxT("Texto de Etiqueta en Grilla")));
  GrillaMatriz->SetCellTextColour(*Colores.Color(wxT("Texto de Celdas en Grilla")));
  GrillaMatriz->SetLabelFont(*Fuentes.Fuente(wxT("Etiqueta en Grilla")));
  GrillaMatriz->SetDefaultCellFont(*Fuentes.Fuente(wxT("Celdas en Grilla")));

  GrillaMatriz->SetRowLabelSize(5);

  GrillaMatriz->SetColLabelSize(5);

  GrillaMatriz->SetDefaultRowSize(Dimensiones.Dimension(wxT("Altura de Caja")));

  col=*Colores.Color(wxT("Propiedades"));
// casos
  int i,tam;
  tam=Proy->Casos.GetCount();
  for(i=0;i<tam;i++)
  {

    cad=Proy->Casos.Item(i).Nombre;
    if(Selecciones.Seleccion(wxT("Matriz con colores"))==0)
    {
      GrillaMatriz->SetCellBackgroundColour(i+2,0, col);
    }
    GrillaMatriz->SetCellValue(i+2,0,cad);
  }
  int HX,VX;
  switch(VistaMatriz)
  {
      case 0:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 1:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Ambigüedad"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 2:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Interpretación"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      case 3:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de InterpretaciónLarga"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;
      default:  HX=Dimensiones.Dimension(wxT("Ancho de Columnas de Valor"));VX=Dimensiones.Dimension(wxT("Altura de Caja"));break;

  }
// estrategias
  tam=Proy->Estrategias.GetCount();
  int contador=0;
  Estrategia *Est;
  for(i=0;i<tam;i++)
  {
    Est=&(Proy->Estrategias.Item(i));

    ListaNodos ListaRed;
    Est->Grafo.llenarArreglo(&ListaRed);
    GrillaMatriz->SetColSize(0,Dimensiones.Dimension(wxT("Ancho de Columna de Propiedad")));
    int k,tam3;
    tam3=ListaRed.GetCount();
    for(k=0;k<tam3;k++)
    {
      cad=ListaRed.Item(0).VarCalculada.Nombre;
      GrillaMatriz->SetColSize(contador+k+1,HX);
      if(Selecciones.Seleccion(wxT("Matriz con colores"))==0)
      {
        GrillaMatriz->SetCellBackgroundColour(1,contador+k+1, col);
      }
      GrillaMatriz->SetCellValue(1,contador+k+1,cad);
      ListaRed.Detach(0);
    }
    cad=Est->Nombre;
    GrillaMatriz->SetCellSize(0,contador+1,1,tam3);
    GrillaMatriz->SetCellAlignment(0,contador+1,wxALIGN_CENTRE,wxALIGN_CENTRE);
    if(Selecciones.Seleccion(wxT("Matriz con colores"))==0)
    {

      GrillaMatriz->SetCellBackgroundColour(0,contador+1, col);
    }
    GrillaMatriz->SetCellValue(0,contador+1,cad);

    contador+=tam3;
  }
  GrillaMatriz->SetCellSize(0,0,2,1);

//// celdas centrales
  tam=Regiones.GetCount();
  for(i=0;i<tam;i++)
  {
    NumeroDifuso *num;
    NodoCalculo *n;
    num=Regiones.Item(i).Numero;
    n=Regiones.Item(i).Nodo;
    cad=wxT("");
    wxArrayString tmp;
    int j;
    switch(VistaMatriz)
    {
        case 0: cad << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);break;
        case 1: cad << num->ambiguedad();break;
        case 2: n->VarCalculada.interpretacionMaxima(&cad,num);break;
        case 3: n->VarCalculada.interpretacion(&tmp,num);
                cad=wxT("");
                for(j=0;(unsigned int)j<tmp.GetCount();j++)
                {
                  cad << tmp.Item(j) << wxT("- ");
                }
                break;
        default: cad << num->valorRepresentativo(Proy->Optimismo,Proy->Representatividad);break;
    }
// selección del color... depende del caso y la variable:
    int numCas;
    numCas=Regiones.Item(i).PosY;
    Caso *caso;
    caso=&Proy->Casos.Item(numCas);

    Regiones.Item(i).Variable=NULL;
    int tam2;
    tam2=caso->Variables.GetCount();
    Regiones.Item(i).Variable=NULL;
    for(j=0;j<tam2;j++)
    {
      if(Regiones.Item(i).Nodo->VarCalculada.Nombre==caso->Variables.Item(j).Nombre)
      {
        Regiones.Item(i).Variable=&caso->Variables.Item(j);
        j=tam2;
      }
    }

    VariableLinguistica *v;
    v=Regiones.Item(i).Variable;
    n=Regiones.Item(i).Nodo;

    if(n->FormaDeCalculo==2)
    {
      col=*Colores.Color(wxT("Nodo es Enlace"));  // Nodo enlace a otra estrategia
    }
    else if(n->FormaDeCalculo==0 || n->NodosDeCalculo.GetCount()==0)
    {
      if(v==NULL)
      {
        col=*Colores.Color(wxT("Nodo no Definido en el Caso")) ;  // No hay Variable definida

      }else{
        switch(v->TipoDeValor)
        {
          case 0:col=*Colores.Color(wxT("Nodo es Indefinido"));break;  // indefinido
          case 1:col=*Colores.Color(wxT("Nodo es Crisp"));break;  // crisp
          case 2:col=*Colores.Color(wxT("Nodo es Intervalo"));break;  // intervalo
          case 3:col=*Colores.Color(wxT("Nodo es Número Difuso"));break;  // nmero difuso
          case 4:col=*Colores.Color(wxT("Nodo es Etiqueta"));break;  // etiqueta
          default : col=*Colores.Color(wxT("Nodo es de otro tipo"));break;  // nodo de otro tipo
        }
      }
    }else
    {
      col=*Colores.Color(wxT("Nodo es Calculado"));  // Nodo calculado
    }
    if(Selecciones.Seleccion(wxT("Matriz con colores"))==0)
    {
      GrillaMatriz->SetCellBackgroundColour(Regiones.Item(i).PosY+2,Regiones.Item(i).PosX+1, col);
    }
    GrillaMatriz->SetCellValue(Regiones.Item(i).PosY+2,Regiones.Item(i).PosX+1,cad);
  }
}

void MiCanvas::pintarMatriz2(wxPaintDC &dc)
{
  if(FlagPintarMatriz)
  {
     if(GrillaMatriz !=NULL)
     {

       GrillaMatriz->Destroy();
       delete GrillaMatriz;
     }

     int i,tamh,tamv,tam;

      tam=Proy->Estrategias.GetCount();
      int contador=0;
      Estrategia *Est;
      for(i=0;i<tam;i++)
      {
        Est=&(Proy->Estrategias.Item(i));
        ListaNodos ListaRed;
        Est->Grafo.llenarArreglo(&ListaRed);
        int k,tam3;
        tam3=ListaRed.GetCount();
        contador+=tam3;
        for(k=0;k<tam3;k++)
        {
          ListaRed.Detach(0);
        }
      }

     tamv=Proy->Casos.GetCount()+2;
     tamh=contador+1;
     GrillaMatriz = new wxGrid(this,MICANVAS_GRILLA_MATRIZ,wxPoint(Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))),wxSize(HSize-Dimensiones.Dimension(wxT("Margen Izquierdo"))-Dimensiones.Dimension(wxT("Margen Derecho")),VSize-Dimensiones.Dimension(wxT("Margen Superior"))-Dimensiones.Dimension(wxT("Margen Inferior"))));
     GrillaMatriz->CreateGrid(tamv,tamh);
     GrillaMatriz->SetEditable(FALSE);
     GrillaMatriz->Refresh();

  }
  llenarGrillaCasoMatriz2();

  wxString cad2;
  int w,h;
  dc.SetTextForeground(*Colores.Color(wxT("Texto de Metodología")));
  dc.SetFont(*Fuentes.Fuente(wxT("Metodología")));
  cad2 = wxT("Todas las Metodologías y Todos los Casos");
  cad2 << Proy->Estrategias.Item(Proy->NumEstrategia).Nombre ;
  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*1/4-h/2);


  switch(VistaMatriz)
  {
    case 0 : cad2 = wxT("Valor representativo");break;
    case 1 : cad2 = wxT("Ambigüedad");break;

    case 2 : cad2 = wxT("Interpretación Corta");break;
    case 3 : cad2 = wxT("Interpretación Larga");break;
    default : cad2 = wxT("Interpretación");break;
  }

  dc.GetTextExtent(cad2,&w,&h);
  dc.DrawText(cad2,Dimensiones.Dimension(wxT("Margen Izquierdo")),Dimensiones.Dimension(wxT("Margen Superior"))*2/4-h/2);
}

void MiCanvas::writeConfigura()
{
  wxFileConfig * Configura;
  wxString configName="";
  configName << wxGetCwd() << "/";
  switch(ESPECIFICO)
  {
    case 0 :configName << wxT("fuzzynet");break;
    case 1 :configName << wxT("ediav");break;
    case 5 :configName << wxT("eiiav");break;
    default:configName << wxT("fuzzynet");break;
  }
  configName << wxT(".cfg");
  Configura = new wxFileConfig();
  int i,tam;
  Configura->SetPath(wxT("Colores"));
  tam=Colores.Colores.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom,cad;
    nom=Colores.Nombres.Item(i);nom << wxT("_Red");
    cad=wxT("");cad << (int)Colores.Colores.Item(i).Red();
    Configura->Write(nom,cad);
    nom=Colores.Nombres.Item(i);nom << wxT("_Green");
    cad=wxT("");cad << (int)Colores.Colores.Item(i).Green();
    Configura->Write(nom,cad);
    nom=Colores.Nombres.Item(i);nom << wxT("_Blue");
    cad=wxT("");cad << (int)Colores.Colores.Item(i).Blue();
    Configura->Write(nom,cad);
  }
  Configura->SetPath(wxT("/Fuentes"));
  tam=Fuentes.Fuentes.GetCount();
  for(i=0;i<tam;i++)

  {
    wxString nom,cad;
    nom=Fuentes.Nombres.Item(i);nom << wxT("_Fte");
    wxFont fte=Fuentes.Fuentes.Item(i);
    cad=fte.GetNativeFontInfoDesc();
    Configura->Write(nom,cad);
  }
  Configura->SetPath(wxT("/Dimensiones"));
  tam=Dimensiones.Dimensiones.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom;
    nom=Dimensiones.Nombres.Item(i);nom << wxT("_Dim");
    int dim=Dimensiones.Dimensiones.Item(i);
    Configura->Write(nom,dim);
  }
  Configura->SetPath(wxT("/Selecciones"));

  tam=Selecciones.Selecciones.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom;
    nom=Selecciones.Nombres.Item(i);nom << wxT("_Sel");
    int dim=Selecciones.Selecciones.Item(i);
    Configura->Write(nom,dim);
  }
  wxFileOutputStream stream(configName);
	Configura->Save(stream);
  delete Configura;
}

void MiCanvas::readConfigura()
{
  wxFileConfig * Configura;
  wxString configName="";
  configName << wxGetCwd() << "/";
  switch(ESPECIFICO)
  {
    case 0 :configName << wxT("fuzzynet");break;
    case 1 :configName << wxT("ediav");break;
    case 5 :configName << wxT("eiiav");break;
    default:configName << wxT("fuzzynet");break;
  }
  configName << wxT(".cfg");

	wxFileInputStream stream(configName);
	Configura=new wxFileConfig(stream);

  int i,tam;
  Configura->SetPath(wxT("Colores"));
  tam=Colores.Colores.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom,nomR,nomG,nomB,cadR,cadG,cadB;
    unsigned char r,g,b;
    nom=Colores.Nombres.Item(i);
    nomR =nom;nomR << wxT("_Red");
    nomG =nom;nomG << wxT("_Green");
    nomB =nom;nomB << wxT("_Blue");
    long dato;
    if(Configura->Read(nomR,&cadR) && Configura->Read(nomG,&cadG) && Configura->Read(nomB,&cadB))
    {
      cadR.ToLong(&dato,10);r=(unsigned char)dato;
      cadG.ToLong(&dato,10);g=(unsigned char)dato;
      cadB.ToLong(&dato,10);b=(unsigned char)dato;
      wxColour col(r,g,b);
      Colores.Colores.Item(i)=col;
    }
  }
  Configura->SetPath(wxT("/Fuentes"));
  tam=Fuentes.Fuentes.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom,cad;
    nom=Fuentes.Nombres.Item(i);nom << wxT("_Fte");
    if(Configura->Read(nom,&cad))
    {
      wxFont fte=Fuentes.Fuentes.Item(i);
      fte.wxFontBase::SetNativeFontInfo(cad);
      Fuentes.Fuentes.Item(i)=fte;
    }
  }
  Configura->SetPath(wxT("/Dimensiones"));
  tam=Dimensiones.Dimensiones.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom;
    int dim;
    nom=Dimensiones.Nombres.Item(i);nom << wxT("_Dim");
    if(Configura->Read(nom,&dim))
    {
      Dimensiones.Dimensiones.Item(i)=dim;
    }
  }
  Configura->SetPath(wxT("/Selecciones"));
  tam=Selecciones.Selecciones.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString nom;
    int dim;
    nom=Selecciones.Nombres.Item(i);nom << wxT("_Sel");
    if(Configura->Read(nom,&dim))
    {
      Selecciones.Selecciones.Item(i)=dim;

    }
  }
  delete Configura;
}
