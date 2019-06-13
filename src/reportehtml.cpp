/***************************************************************************
                          reportehtml.cpp  -  description
                             -------------------
    begin                : jue abr 8 2004
    copyright            : (C) 2004 by
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "reportehtml.h"

ReporteHTML::ReporteHTML()
{
}

ReporteHTML::~ReporteHTML()
{
}

void ReporteHTML::encabezado(wxTextFile *f, wxString Tit)
{
  wxString cad;
  cad =wxT("<HTML>");  f->AddLine(cad);
  cad =wxT("<HEAD>");  f->AddLine(cad);
  cad =wxT("<TITLE>");  f->AddLine(cad);
  cad =Tit;  f->AddLine(cad);
  cad =wxT("</TITLE>");  f->AddLine(cad);
  cad =wxT("</HEAD>");  f->AddLine(cad);
  cad =wxT("<BODY>");  f->AddLine(cad);
}

void ReporteHTML::cierre(wxTextFile *f)
{
  wxString cad;
  cad =wxT("</BODY>");  f->AddLine(cad);
  cad =wxT("</HTML>");  f->AddLine(cad);
}

void ReporteHTML::seccion(wxTextFile *f,wxString Sec)
{
  Contadores.Item(Nivel-1)++;
  wxString cad=wxT("");
  wxString cad2=wxT("");
  cad2=cadenaNivelActual();
  IndiceContador.Add(cad2);
  IndiceContenido.Add(Sec);
  switch(Nivel)
  {
    case 1:  cad << wxT("<H2>") << cad2 << Sec <<wxT("</H1>") ;
              ContadorTablas=0;
              ContadorFiguras=0;
              break;
    case 2:  cad << wxT("<H3>") << cad2 << Sec <<wxT("</H2>") ; break;
    case 3:  cad << wxT("<H4>") << cad2 << Sec <<wxT("</H3>") ; break;
    case 4:  cad << wxT("<H5>") << cad2 << Sec <<wxT("</H4>") ; break;
    case 5:  cad << wxT("<H6>") << cad2 << Sec <<wxT("</H5>") ; break;
    case 6:  cad << wxT("<B><U><I>") << cad2 << Sec <<wxT("</I></U></B><BR>") ; break;
    case 7:  cad << wxT("<B><U>") << cad2 << Sec <<wxT("</U></B><BR>") ; break;
    case 8:  cad << wxT("<B>") << cad2 << Sec <<wxT("</B><BR>") ; break;
    default:  parrafo(f,Sec); break;
  }
  cad2.Replace(wxT("."),wxT("_"));
  cad=destino(cad2,cad);
  f->AddLine(cad);
  avance();
}

void ReporteHTML::parrafo(wxTextFile *f, wxString Par)
{
  Par.Replace(wxT("\n"),wxT("</P>\n<P ALIGN='JUSTIFY'>"));
  wxString cad;
  cad=wxT("<P ALIGN='JUSTIFY'>");
  f->AddLine(cad);
  cad=Par;
  f->AddLine(cad);
  cad=wxT("</P>");
  f->AddLine(cad);
  cad=wxT("");
  f->AddLine(cad);
}

void ReporteHTML::lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des)
{
  wxString cad;
  int i,tam,tam2;





  tam=Nom.GetCount();
  if(tam==0){return;}
  tam2=Des.GetCount();
  cad = wxT("<OL>");
  f->AddLine(cad);
  for(i=0;i<tam;i++)
  {
    cad= wxT("<LI><B>");
    cad << Nom.Item(i) << wxT(":</B>");
    f->AddLine(cad);
    if(i<tam2)
    {
      cad= Des.Item(i);
      f->AddLine(cad);
    }
  }
  cad = wxT("</OL>");
  f->AddLine(cad);
}

wxString ReporteHTML::enlace(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  cad << wxT("<A HREF='#_TAG_") << Dir << wxT("'  TARGET='_frm_contenido'>") << Dato << wxT("</A>");
  return cad;
}

wxString ReporteHTML::enlaceTabla(int Tab)
{
  wxString cad=wxT("");
  wxString cad2=wxT("");
  cad2 << wxT("<A HREF='#_TAB_") << cadenaNivelActual().BeforeFirst('.') << wxT("_") <<  Tab << wxT("'>");
  cad  << cad2 << wxT("Tabla ") <<  cadenaNivelActual().BeforeFirst('.') << wxT(".") <<  Tab << wxT("</A>");
  return cad;
}

wxString ReporteHTML::enlaceFigura(int Fig)
{
  wxString cad=wxT("");
  wxString cad2=wxT("");
  cad2 << wxT("<A HREF='#_FIG_") << cadenaNivelActual().BeforeFirst('.') << wxT("_") <<  Fig << wxT("'>");
  cad  << cad2 << wxT("Figura ") <<  cadenaNivelActual().BeforeFirst('.') << wxT(".") <<  Fig;
  switch(seleccion(wxT("Variables"),wxT("Formato de Figuras HTML")))
  {
    default:
    case 0:
         cad << wxT(".png</A>");
         break;
    case 1:
         cad << wxT(".jpg</A>");
         break;
    case 2:
         cad << wxT(".bmp</A>");
         break;
  }
  return cad;
}

wxString ReporteHTML::enlaceExterno(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  cad << wxT("<A HREF='") << crearCadenaArchivo(Dir) << wxT("' TARGET='_frm_contenido'>") << Dato << wxT("</A>");
  return cad;
}

wxString ReporteHTML::destino(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  cad << wxT("<A NAME='_TAG_") << Dir << wxT("'>") << Dato << wxT("</A>");
  return cad;
}

wxString ReporteHTML::crearCadenaArchivo(wxString Dir)
{
  wxString cad;
  cad  << wxT("sec_") << Dir << wxT(".html");
  return cad;
}

void ReporteHTML::abrirArchivo(wxTextFile* f)
{
  f->Create();
  encabezado(f,cadenaNivelSiguiente());
}

void ReporteHTML::cerrarArchivo(wxTextFile* f)
{
 cierre(f);
 f->Write();
}

void ReporteHTML::incluirArchivo(wxTextFile *f, wxString Origen)
{
  wxTextFile fo(crearCadenaArchivo(Origen));
  fo.Open();
  int i,tam;
  tam=fo.GetLineCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=fo.GetLine(i);
    f->AddLine(cad);
  }
  fo.Close();
}

void ReporteHTML::tablaContenido()
{

  int i,tam;
  wxString nom=wxT("toc");
  wxTextFile *f;
  f=new wxTextFile(crearCadenaArchivo(nom));
  f->Create();
  f->AddLine(wxT("<H1>Tabla de Contenido</H1>"));
  f->AddLine(wxT("<UL>"));
  tam=IndiceContador.GetCount();
  for(i=0;i<tam;i++)
  {
    int nivel=0;
    wxString nom=IndiceContador.Item(i);
    while(!nom.IsEmpty()>0)
    {
      nom=nom.AfterFirst('.');
      nivel++;
    };
    if (nivel <  (NivelMaxTOC+2))
    {
      wxString cad=wxT("<LI>");
      wxString cad2=IndiceContador.Item(i);
      cad2.Replace(wxT("."),wxT("_"));
      cad << IndiceContador.Item(i) << enlaceExterno(cad2,IndiceContenido.Item(i));
      f->AddLine(cad);
    }
  }
  f->AddLine(wxT("</UL>"));
  f->Write();
}

void ReporteHTML::postProceso(wxString arch,wxString Nombre)
{
  wxTextFile f(arch);
  f.Create();
  wxString cad;
  cad =wxT("<HTML>");  f.AddLine(cad);
  cad =wxT("<HEAD>");  f.AddLine(cad);
  cad =wxT("<TITLE>");  f.AddLine(cad);
  cad =Nombre;  f.AddLine(cad);
  cad =wxT("</TITLE>");  f.AddLine(cad);
  cad =wxT("</HEAD>");  f.AddLine(cad);
  cad =wxT("<FRAMESET ROWS=50,*>");  f.AddLine(cad);
  cad =wxT("   <FRAME SRC='titulo.html' NAME='_frm_titulo' SCROLLING=NO>");  f.AddLine(cad);
  cad =wxT("   <FRAMESET COLS=200,*>");  f.AddLine(cad);
  cad =wxT("      <FRAME SRC='sec_toc.html 'NAME='_frm_toc'>");  f.AddLine(cad);
  cad =wxT("      <FRAME SRC='sec_1_.html' NAME='_frm_contenido'>");  f.AddLine(cad);
  cad =wxT("   </FRAMESET>");  f.AddLine(cad);
  cad =wxT("</FRAMESET>");  f.AddLine(cad);
  f.Write();

  wxTextFile f2(wxT("titulo.html"));
  f2.Create();
  encabezado(&f2,arch);
  cad =wxT("<H1>");
  cad << Nombre << wxT("</H1>");
  f2.AddLine(cad);
  cad =wxT("</BODY>");
  cad =wxT("</HTML>");
  f2.AddLine(cad);
  f2.Write();
}

void ReporteHTML::tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre)
{
  int i;
  wxString linea=wxT("");

  ContadorTablas++;
  linea = wxT("<A NAME='_TAB_");
  linea << cadenaNivelActual().BeforeFirst('.') << wxT("_") << ContadorTablas << wxT("'></A>");
  f->AddLine(linea);
  linea=wxT("<TABLE BORDER=1 ALIGN=CENTER>");
  f->AddLine(linea);
  for(i=0;i<tam;i++)
  {
    linea=wxT("<TR>");
    f->AddLine(linea);
    int j,tam2;
    tam2=lista[i].GetCount();
    for(j=0;j<tam2;j++)
    {
      if(i==0)
      {
        linea=wxT("<TH>");
        linea << lista[i][j] <<wxT("</TH>");
        f->AddLine(linea);
      }else
      {
        linea=wxT("<TD>");
        linea << lista[i][j] <<wxT("</TD>");
        f->AddLine(linea);
      }
    }
    linea=wxT("</TR>");
    f->AddLine(linea);
  }
  linea=wxT("<CAPTION><P ALIGN=CENTER>");
  f->AddLine(linea);
  linea=wxT("Tabla ");
  linea << cadenaNivelActual().BeforeFirst('.') << wxT(".") << ContadorTablas << wxT(" ") << Nombre;
  f->AddLine(linea);
  linea=wxT("</P></CAPTION>");
  f->AddLine(linea);
  linea=wxT("</TABLE>");
  f->AddLine(linea);
}

bool ReporteHTML::figuraVariable(VariableLinguistica *Var,NumeroDifuso *Num=NULL,int entrada)
{
////////////// prueba de construcción de bitmap...  si funciona
  wxMemoryDC dc;
  wxBitmap bmp(300,160);
  bmp.Create(300,160);
  dc.SelectObject(bmp);
  dc.SetBackground( *wxWHITE_BRUSH );
  dc.SetPen( *wxBLACK_PEN );
  dc.Clear();

  wxPoint Origen(0,0);
  wxSize Tamano;
  Tamano=dc.GetSize();
  dc.SetPen(* wxBLACK_PEN);

  dc.DrawRectangle(Origen,Tamano);
  int offx=50,offy=40;
  Origen.x+=offx;
  Origen.y+=offy;
  Tamano.SetWidth(Tamano.GetWidth()-2*offx);
  Tamano.SetHeight(Tamano.GetHeight()-2*offy);
  dc.DrawLine(offx/2,offy+Tamano.GetHeight(),offx*1.5+Tamano.GetWidth(),offy+Tamano.GetHeight());
  dc.DrawLine(offx/2,offy+Tamano.GetHeight(),offx/2,offy/2);

  wxString cad=wxT("0.0");
  int w,h;
  do
  {
    dc.GetTextExtent(cad,&w,&h);
    if(w>(offx/2)){cad=cad.Left(cad.Len()-1);}
  }while(w>offx/2);
  dc.DrawText(cad,offx/2-w,offy+Tamano.GetHeight()-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  cad=wxT("1.0");
  do
  {
    dc.GetTextExtent(cad,&w,&h);
    if(w>(offx/2)){cad=cad.Left(cad.Len()-1);}
  }while(w>offx/2);
  dc.DrawText(cad,offx/2-w,offy-h/2);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  cad=wxT("");
  cad << Var->Minimo;
  do
  {
    dc.GetTextExtent(cad,&w,&h);
    if(w>(offx/2)){cad=cad.Left(cad.Len()-1);}
  }while(w>offx/2);
  dc.DrawText(cad,offx-w/2,offy+Tamano.GetHeight());  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  cad=wxT("");
  cad << Var->Maximo;
  do
  {
    dc.GetTextExtent(cad,&w,&h);
    if(w>(offx/2)){cad=cad.Left(cad.Len()-1);}
  }while(w>offx/2);
  dc.DrawText(cad,offx+Tamano.GetWidth()-w/2,offy+Tamano.GetHeight());  // Falla en BC si no se usa #include <wx/msw/winundef.h>

  int i,tam;
  tam=Var->Etiquetas.GetCount();
  for(i=0;i<tam;i++)
  {

    dc.SetPen(* wxGREEN_PEN);
    NumeroDifuso *n;
    n=Var->Etiquetas.Item(i).ND;
    int j,tam2;
    tam2=n->Tamano;
    float xLo,xLf,xRo,xRf,yo,yf;
    for(j=0;j<tam2-1;j++)
    {
      yo=j*n->intervalo();
      yf=(j+1)*n->intervalo();
      xLo=n->L[j];

      xLf=n->L[j+1];
      xRo=n->R[j];
      xRf=n->R[j+1];
      xLo = Origen.x + (xLo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xLf = Origen.x + (xLf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRo = Origen.x + (xRo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRf = Origen.x + (xRf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
    }
    dc.DrawLine(xLf,yf,xRf,yf);
    cad=wxT("");
    switch(seleccion(wxT("Variables"),wxT("Etiqueta en Figuras")))
    {
      default:
      case 0:
            cad << Var->Etiquetas.Item(i).Label;
            break;
      case 1:
            cad << i+1;
            break;
    }
    int caja;
    caja=Tamano.GetWidth()/Var->Etiquetas.GetCount();
    do
    {
      dc.GetTextExtent(cad,&w,&h);
      if(w>(caja)){cad=cad.Left(cad.Len()-1);}
    }while(w>caja);
    dc.DrawText(cad,(xLf+xRf)/2-w/2,yf-h);  // Falla en BC si no se usa #include <wx/msw/winundef.h>
  }

  //// el valor...
  if(seleccion(wxT("Variables"),wxT("Valor por Defecto"))==0 || entrada==0)
  {
    dc.SetPen(* wxRED_PEN);
    NumeroDifuso *n;
    if(Num==NULL)
    {
      n=Var->valor();
    }else
    {
      n=Num;
    }
    int j,tam2;
    tam2=n->Tamano;
    float xLo,xLf,xRo,xRf,yo,yf;
    for(j=0;j<tam2-1;j++)
    {

      yo=j*n->intervalo();
      yf=(j+1)*n->intervalo();
      xLo=n->L[j];
      xLf=n->L[j+1];
      xRo=n->R[j];
      xRf=n->R[j+1];
      xLo = Origen.x + (xLo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xLf = Origen.x + (xLf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRo = Origen.x + (xRo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRf = Origen.x + (xRf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
    }
    dc.DrawLine(xLf,yf,xRf,yf);
  }

// el nombre...
  wxString dirActual,dirFig;
  dirActual=wxGetCwd();
  dirFig=dirActual;
  dirFig << wxT("/fig");
  if(!wxDirExists(dirFig))
  {
    wxMkdir(dirFig);
  }
  wxSetWorkingDirectory(dirFig);
  ContadorFiguras++;
  wxString nomBmp=wxT("fig_");
  nomBmp << cadenaNivelActual().BeforeFirst('.') << wxT(".") << ContadorFiguras;
  nomBmp.Replace(wxT("."),wxT("_"));
  bool ret;
  switch(seleccion(wxT("Variables"),wxT("Formato de Figuras HTML")))
  {
    default:
    case 0:
         nomBmp << wxT(".png");
         ret=bmp.SaveFile(nomBmp,wxBITMAP_TYPE_PNG);
         break;
    case 1:
         nomBmp << wxT(".jpg");
         ret=bmp.SaveFile(nomBmp,wxBITMAP_TYPE_JPEG);
         break;
    case 2:
         nomBmp << wxT(".bmp");
         ret=bmp.SaveFile(nomBmp,wxBITMAP_TYPE_BMP);
         break;
  }
  dc.SelectObject( wxNullBitmap );
  wxSetWorkingDirectory(dirActual);
  return ret;
}

void ReporteHTML::incluirFigura(wxTextFile *f,wxString Nom)
{
  wxString linea=wxT("");
  wxString cad2=wxT("");
  cad2 << wxT("<A NAME='_FIG_") << cadenaNivelActual().BeforeFirst('.') << wxT("_") <<  ContadorFiguras << wxT("'>");
  linea << cad2 <<wxT("<P ALIGN=CENTER><IMG SRC='fig/fig_") << cadenaNivelActual().BeforeFirst('.') << wxT("_") << ContadorFiguras;
  switch(seleccion(wxT("Variables"),wxT("Formato de Figuras HTML")))
  {
    default:
    case 0:
         linea << wxT(".png'></P></A>");
         break;
    case 1:
         linea << wxT(".jpg'></P></A>");
         break;
    case 2:
         linea << wxT(".bmp'></P></A>");
         break;
  }
  f->AddLine(linea);
  linea=wxT("");
  linea  <<wxT("<P ALIGN=CENTER>Figura ") << cadenaNivelActual().BeforeFirst('.') << wxT(".") <<  ContadorFiguras  << wxT(". ") << Nom << wxT("</P>");
  f->AddLine(linea);
}
