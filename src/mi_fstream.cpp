/***************************************************************************
                          mi_fstream.cpp  -  description
                             -------------------
    begin                : mar abr 15 2003
    copyright            : (C) 2003 by Oscar G. Duarte V.
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *      
 *                                                                         *
 ***************************************************************************/

#include "mi_fstream.h"

Mi_ofpstream::Mi_ofpstream(wxString cad)
{
    outputFile=new wxTextFile(cad);
    outputFile->Create();
    wxString cad2=wxT("Fuzzynet%1.0%");
    float a=0.5;
    cad2 << a << wxT("%");
    outputFile->AddLine(cad2);
    wxString finl;
    finl=outputFile->GetEOL();
    TipoPropio=finl.Len()-1;
    if(TipoPropio<0)TipoPropio=0;
}

void Mi_ofpstream::operator << (const wxString& D)
{
  wxString DX=D;
  wxArrayString lineas;
  while(DX.length()>0)
  {
    lineas.Add(DX.BeforeFirst(outputFile->GetEOL()[TipoPropio]));
    DX=DX.AfterFirst(outputFile->GetEOL()[TipoPropio]);            // asi funciona... en Windows
  };
  int i,tam;
  tam=lineas.GetCount();
  cad=wxT(""); cad << tam; outputFile->AddLine(cad);
  for(i=0;i<tam;i++)
  {
    outputFile->AddLine(lineas[i]);
  }
  lineas.Clear();
}


Mi_ifpstream::Mi_ifpstream(wxString Cad)
{
  inputFile=new wxTextFile(Cad);
  inputFile->Open();
  wxString cad2;
  cad2=inputFile->GetFirstLine();
  cad2=cad2.AfterFirst('%');  // "Fuzzynet"
  cad2=cad2.AfterFirst('%');  // "1.0"
  wxString f;
  f=cad2.BeforeFirst('%'); // "0,5" o "0.5"
  cad2=cad2.AfterFirst('%');  // "1.0"
  if(f.Find(',')==-1)
  {
    decimalArchivo='.';
  }else
  {
    decimalArchivo=',';
  }
  wxString prueba;
  float a=0.5;
  prueba << a;
  if(prueba.Find(',')==-1)
  {
    decimalPropio='.';
  }else
  {
    decimalPropio=',';
  }
}

void Mi_ifpstream::operator >> (int& D)
{
	cad=inputFile->GetNextLine();
	long d;
	cad.ToLong(&d);
	D=(int)d;
	//D=atoi(cad.c_str());
}

void Mi_ifpstream::operator >> (float& D)
{
	cad=inputFile->GetNextLine();
  wxString arch,prop;
  arch=decimalArchivo;
  prop=decimalPropio;
  cad.Replace(arch,prop);
  double d;
  cad.ToDouble(&d);
  D=(float)d;
//  D=atof(cad.c_str());
}

void Mi_ifpstream::operator >> (wxString& D)
{
  D=wxT("");
  int i,tam;
  cad=inputFile->GetNextLine();
  long Tam;
  cad.ToLong(&Tam);
  tam=(int)Tam;
//  tam=atoi(cad.c_str());
  for(i=0;i<tam;i++)
  {
    wxString linea;
    linea=inputFile->GetNextLine();
    linea=linea.BeforeFirst(inputFile->GetEOL()[0]);
    D << linea << inputFile->GetEOL();
  }
  if(tam>0){D=D.BeforeLast(inputFile->GetEOL()[0]);}  // el último fin de línea sobra
}


//void Mi_ofpstream::operator << (const wxString& D)
//{
//// No se salvan bien los caracteres propios del español...
//// tal vez sobre el condicional... o esté incompleto ...
//// Debe revisarse
//	wxString DX;
//	int i,tam;
//	tam=D.length();
//	for(i=0;i<tam;i++)
//	{
//		char c;
//		c=D[i];
//		if(isprint(c)||c=='\n'||c=='ú'||c=='Ú'||c=='ü'||c=='Ü')
//		{
//			if(c=='{'){c=19;}
//			if(c=='}'){c=20;}
//			DX+=c;
//		}
//	}
//	*os << '{' << DX << "}\n";
//}
//
//void Mi_ifpstream::cadena()
//{
//	Str="";
//	StrTmp="";
//	char c;
//	do
//	{
//		is->get(c);
//		if(c!='\n')
//		{
//			StrTmp+=c;
//		}
//	}while(c!='{');
//	do
//	{
//		is->get(c);
//		if(c!='}')
//		{
//			if(c=='\n')
//			{
//				Str+="\r\n";
//			}else
//			{
//				Str+=c;
//			}
//		}
//	}while(c!='}');
//}
//
//void Mi_ifpstream::operator >> (int& D)
//{
//	cadena();
//	D=atoi(Str.c_str());
//}
//
//void Mi_ifpstream::operator >> (float& D)
//{
//// Atención, aqui hay algo raro: un float se salva con un separador decimal
//// que es un punto, pero al leerlo espera que sea una coma...
//// Lo más extraño es que esto 'no siempre sucede' ... vale la pena
//// mirarlo con mucho más detalle
//	cadena();
//    char coma[3],punto[3];
//    sprintf(coma,",");
//    sprintf(punto,".");
//    Str.Replace(punto,coma);
//	D=atof(Str.c_str());
//}
//
//void Mi_ifpstream::operator >> (wxString& D)
//{
//	cadena();
//	unsigned int i,tam;
//	tam=Str.length();
//	for(i=0;i<tam;i++)
//	{
//		if(Str[i]==19){Str.SetChar(i,'{');}
//		if(Str[i]==20){Str.SetChar(i,'}');}
//	}
//	D=Str;
//}
//

/*
//////////////////  EJEMPLO DE UTILIZACION

    Mi_ofpstream text_output("pr.txt");

    wxString cad="Una hermosa prueba";

    int ii=3;
    float ff=4.5;

    text_output << cad;
    text_output << "cadena libre";
    text_output << ii;
    text_output << ff;

    text_output.close();

    Mi_ifpstream text_input("pr.txt");

    wxString cadL1,cadL2;
    int j;
    float f;

    text_input >> cadL1;
    text_input >> cadL2;
    text_input >> j;
    text_input >> f;

    text_input.close();

    cout << cadL1 << cadL2 << j << f << endl;

*/
