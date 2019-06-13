/***************************************************************************
                          reportelatex.cpp  -  description
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

#include "reportelatex.h"

ReporteLatex::ReporteLatex()
{
}

ReporteLatex::~ReporteLatex()
{
}

wxString ReporteLatex::remplazo(wxString c)
{
  wxString C=c;
  C.Replace(wxT("%"),wxT("\\%"));
  return C;
}

void ReporteLatex::encabezado(wxTextFile *f, wxString Tit)
{
  wxString cad;
  cad =wxT("\\documentclass{book}");  f->AddLine(cad);
  cad =wxT("\\usepackage[utf8]{inputenc}");  f->AddLine(cad);
  cad =wxT("\\usepackage[spanish]{babel}");  f->AddLine(cad);
  cad =wxT("\\usepackage{enumerate}");  f->AddLine(cad);
  cad =wxT("\\usepackage{amsmath}");  f->AddLine(cad);
  if(seleccion(wxT("Variables"),wxT("Formato de Figuras Latex"))==0)
  {
    cad =wxT("\\usepackage{pst-all}");  f->AddLine(cad);
  }else
  {
    cad =wxT("\\usepackage[shell,debug]{pdftricks-1.16}");  f->AddLine(cad);
    cad =wxT("\\begin{psinputs}");  f->AddLine(cad);
    cad =wxT("\\usepackage{txfonts}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pstricks}");  f->AddLine(cad);
    cad =wxT("\\usepackage{color}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pstcol}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pst-plot}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pst-tree}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pst-eps}");  f->AddLine(cad);
    cad =wxT("\\usepackage{multido}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pst-node}");  f->AddLine(cad);
    cad =wxT("\\usepackage{pst-eps}");  f->AddLine(cad);
    cad =wxT("\\end{psinputs}");  f->AddLine(cad);
  }
  cad =wxT("\\usepackage{longtable}");  f->AddLine(cad);
  cad =wxT("\\usepackage{hyperref}");  f->AddLine(cad);
  cad =wxT("\\usepackage{titletoc}");  f->AddLine(cad);
  cad =wxT("\\title{"); cad << Tit << wxT("}"); f->AddLine(cad);
  cad =wxT("\\author{Fuzzynet}");  f->AddLine(cad);
  cad =wxT("\\begin{document}");  f->AddLine(cad);
  cad =wxT("\\setcounter{tocdepth}{"); cad << NivelMaxTOC << wxT("}");  f->AddLine(cad);
  cad =wxT("\\setcounter{secnumdepth}{5}");  f->AddLine(cad);
  cad =wxT("\\titlecontents{chapter}[0em]{\\filright \\bf}{\\contentslabel{.8em}}{\\hspace*{-.5em}}{\\bf \\titlerule*[1pc]{.} \\contentspage}");  f->AddLine(cad);
  cad =wxT("\\titlecontents{section}[1.5em]{\\filright }{\\contentslabel{1.5em} }{\\hspace*{-1.5em}}{\\bf \\titlerule*[1pc]{.} \\contentspage}");  f->AddLine(cad);
  cad =wxT("\\titlecontents{subsection}[3.5em]{\\filright \\em}{\\contentslabel{2.5em} }{\\hspace*{-2.5em}}{\\bf \\titlerule*[1pc]{.} \\contentspage}");  f->AddLine(cad);
  cad =wxT("\\titlecontents{subsubsection}[5.5em]{\\filright \\small \\em}{\\contentslabel{3.8em}}{\\hspace*{-3.8em}}{\\bf \\titlerule*[1pc]{.} \\contentspage}");  f->AddLine(cad);
  cad =wxT("\\maketitle");  f->AddLine(cad);
}

void ReporteLatex::cierre(wxTextFile *f)
{
  wxString cad;
  cad =wxT("\\end{document}");  f->AddLine(cad);
}

void ReporteLatex::seccion(wxTextFile *f,wxString Sec)
{
  Contadores.Item(Nivel-1)++;
  wxString cad=wxT("");
  Sec=remplazo(Sec);
  switch(Nivel)
  {
    case 1:  cad << wxT("\\chapter{") << Sec  <<wxT("}") ;
                ContadorTablas=0;
                ContadorFiguras=0;
                break;
    case 2:  cad << wxT("\\section{") << Sec <<wxT("}") ; break;
    case 3:  cad << wxT("\\subsection{") << Sec  <<wxT("}") ; break;
    case 4:  cad << wxT("\\subsubsection{") << Sec <<wxT("}") ; break;
    case 5:  cad << wxT("\\paragraph{") << Sec <<wxT("}") ; break;
    case 6:  cad << wxT("\\subparagraph{") << Sec <<wxT("}") ; break;
    default: parrafo(f,Sec); break;
  }
  wxString cad2=cadenaNivelActual();
  IndiceContador.Add(cad2);
  IndiceContenido.Add(Sec);
  cad2.Replace(wxT("."),wxT("_"));
  cad=destino(cad2,cad);
  f->AddLine(cad);
  avance();
}

void ReporteLatex::parrafo(wxTextFile *f, wxString Par)
{
  Par.Replace(wxT("\n"),wxT("\n\n"));
  Par=remplazo(Par);
  wxString cad;
  cad=Par;
  f->AddLine(cad);
  cad=wxT("");
  f->AddLine(cad);
}

void ReporteLatex::lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des)
{
  wxString cad;
  int i,tam,tam2;
  tam=Nom.GetCount();
  if(tam==0){return;}
  tam2=Des.GetCount();
  cad = wxT("\\begin{description}");
  f->AddLine(cad);
  for(i=0;i<tam;i++)
  {
    cad= wxT("\\item [");
    cad << remplazo(Nom.Item(i)) << wxT(":]");
    f->AddLine(cad);
    if(i<tam2)
    {
      cad= remplazo(Des.Item(i));
      f->AddLine(cad);
    }
  }
  cad = wxT("\\end{description}");
  f->AddLine(cad);
}

wxString ReporteLatex::enlace(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  cad << remplazo(Dato) << wxT("(ver \\ref{sec:") << Dir << wxT("})");
  return cad;
}

wxString ReporteLatex::enlaceTabla(int Tab)
{
  wxString cad=wxT("");
  cad  << wxT("Tabla \\ref{tab:") << cadenaNivelActual().BeforeFirst('.') << wxT("_") << Tab << wxT("} ");
  return cad;
}

wxString ReporteLatex::enlaceFigura(int Fig)
{
  wxString cad=wxT("");
  cad  << wxT("Figura \\ref{fig:") << cadenaNivelActual().BeforeFirst('.') << wxT("_") << Fig << wxT("} ");
  return cad;
}

wxString ReporteLatex::destino(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  cad << remplazo(Dato) << wxT("\\label{sec:") << Dir  << wxT("}");
  return cad;
}

wxString ReporteLatex::crearCadenaArchivo(wxString Dir)
{
  wxString cad;
  cad  << wxT("sec_") << Dir << wxT(".tex");
  return cad;
}

void ReporteLatex::incluirArchivo(wxTextFile *f, wxString Origen)
{
  if(Nivel < 3)
  {
    wxString cad,cad2;
    Origen.Replace(wxT("."),wxT("_"));
    cad2=crearCadenaArchivo(Origen);
    cad2.Replace(wxT(".tex"),wxT(""));
    cad << wxT("\\input{") <<  cad2 << wxT("}");
    f->AddLine(cad);
  }else
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
    wxRemoveFile(crearCadenaArchivo(Origen));
  }

}

void ReporteLatex::tablaContenido()
{
  int i,tam;
  wxString nom=wxT("toc");
  wxTextFile *f;
  f=new wxTextFile(crearCadenaArchivo(nom));
  f->Create();
  wxString cad=wxT("\\tableofcontents");
  f->AddLine(cad);
//  cad=wxT("\\listoftables");
//  f->AddLine(cad);
//  cad=wxT("\\listoffigures");
//  f->AddLine(cad);
  f->Write();
}

void ReporteLatex::escribirFuncion(wxTextFile *f,Funcion *F)
{
  wxString cad;
  cad = F->descripcionLatex();
  parrafo(f,cad);
}

void ReporteLatex::tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre)
{
  if(tam==0){return;}
  int i,j,tam2;
  wxString cad;
  cad = wxT("");
  f->AddLine(cad);
  if(tam>15)
  {
    cad = wxT("\\begin{center}\\tiny");
    f->AddLine(cad);
    cad = wxT("\\begin{longtable}{|");
  }else
  {
    cad = wxT("\\begin{table}");
    f->AddLine(cad);
    cad = wxT("\\begin{center}");
    f->AddLine(cad);
    cad = wxT("\\begin{tabular}{|");
  }
  tam2=lista[0].GetCount();
  cad << wxT("p{2.5cm}|");
  for(j=1;j<tam2;j++)
  {
    cad << wxT("p{1.7cm}|");
  }
  cad << wxT("} \\hline");
  f->AddLine(cad);
  for(i=0;i<tam;i++)
  {
    cad =wxT("");
    tam2=lista[i].GetCount();
    for(j=0;j<tam2 - 1;j++)
    {
      cad << remplazo(lista[i][j]) << wxT(" & ");
    }
    cad << remplazo(lista[i][tam2-1]);
    if((tam>15) &(i==0))
    {
//      cad << wxT(" \\\\ \\hline \\endhead ");
      cad << wxT(" \\\\ \\hline");
    }else
    {
      cad << wxT(" \\\\ \\hline ");
    }
    f->AddLine(cad);
  }
  if(tam>15)
  {
    cad = wxT("\\caption{");
    cad << Nombre << wxT("}");
    f->AddLine(cad);
    ContadorTablas++;
    cad = wxT("\\label{tab:");
    cad << cadenaNivelActual().BeforeFirst('.') << wxT("_") << ContadorTablas << wxT("}");
    f->AddLine(cad);
    cad = wxT("\\end{longtable}");
    f->AddLine(cad);
    cad = wxT("\\end{center}");
    f->AddLine(cad);
  }else
  {
    cad = wxT("\\end{tabular}");
    f->AddLine(cad);
    cad = wxT("\\caption{");
    cad << Nombre << wxT("}");
    f->AddLine(cad);
    ContadorTablas++;
    cad = wxT("\\label{tab:");
    cad << cadenaNivelActual().BeforeFirst('.') << wxT("_") << ContadorTablas << wxT("}");
    f->AddLine(cad);
    cad = wxT("\\end{center}");
    f->AddLine(cad);
    cad = wxT("\\end{table}");
    f->AddLine(cad);
  }
}

bool ReporteLatex::figuraVariable(VariableLinguistica *Var,NumeroDifuso *Num=NULL,int entrada)
{
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
  wxString nomTex=wxT("fig_");
  nomTex << cadenaNivelActual().BeforeFirst('.') << wxT(".") << ContadorFiguras;
  nomTex.Replace(wxT("."),wxT("_"));
  nomTex << wxT(".tex");
  wxTextFile f(nomTex);
  f.Create();

  int tamx=300,tamy=160;
  int offx=50,offy=40;

  wxString linea;
  if(seleccion(wxT("Variables"),wxT("Formato de Figuras Latex"))==1)
  {
    linea=wxT("\\begin{pdfdisplay}");
    f.AddLine(linea);
  }
  linea=wxT("\\begin{pspicture}(0,0)(");
  linea << tamx << wxT("pt,") << tamy << wxT("pt)");
  f.AddLine(linea);
  linea=wxT("\\psset{unit=1pt}");
  f.AddLine(linea);
  linea=wxT("\\psframe(0,0)(");
  linea << tamx << wxT(",") << tamy << wxT(")");
  f.AddLine(linea);
  linea=wxT("\\psline{->}(");
  linea << (int)(offx/2) << wxT(",") << offy <<wxT(")(") << tamx-(int)(offx/2) << wxT(",") << offy << wxT(")");
  f.AddLine(linea);
  linea=wxT("\\psline{->}(");
  linea << (int)(offx/2) << wxT(",") << offy <<wxT(")(") << (int)(offx/2) << wxT(",") << tamy-(int)(offy/2) << wxT(")");
  f.AddLine(linea);
  linea=wxT("\\rput[r](");
  linea << (int)(offx/2)-5 << wxT(",") << offy << wxT("){$0.0$}");
  f.AddLine(linea);
  linea=wxT("\\rput[r](");
  linea << (int)(offx/2)-5 << wxT(",") << tamy-offy << wxT("){$1.0$}");
  f.AddLine(linea);
  linea=wxT("\\rput[t](");
  linea << offx << wxT(",") << offy-5 << wxT("){$") << Var->Minimo << wxT("$}");
  f.AddLine(linea);
  linea=wxT("\\rput[t](");
  linea << tamx-offx << wxT(",") << offy-5 << wxT("){$") << Var->Maximo << wxT("$}");
  f.AddLine(linea);

  tamx=tamx-2*offx;
  tamy=tamy-2*offy;

  int i,tam;
  tam=Var->Etiquetas.GetCount();
  for(i=0;i<tam;i++)
  {
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
      xLo = offx + (xLo - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);
      xLf = offx + (xLf - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);
      xRo = offx + (xRo - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);
      xRf = offx + (xRf - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);

      yo = offy +  (yo - 0.0)*(tamy)/(1.0-0.0);
      yf = offy +  (yf - 0.0)*(tamy)/(1.0-0.0);

      linea=wxT("\\psline[linecolor=green](");
      linea << (int)(xLo) << wxT(",") << (int)(yo) << wxT(")(") << (int)(xLf) << wxT(",") << (int)(yf) << wxT(")");
      f.AddLine(linea);
      linea=wxT("\\psline[linecolor=green](");
      linea << (int)(xRo) << wxT(",") << (int)(yo) << wxT(")(") << (int)(xRf) << wxT(",") << (int)(yf) << wxT(")");
      f.AddLine(linea);
    }
    linea=wxT("\\psline[linecolor=green](");
    linea << (int)(xLf) << wxT(",") << (int)(yf) << wxT(")(") << (int)(xRf) << wxT(",") << (int)(yf) << wxT(")");
    f.AddLine(linea);

    linea=wxT("");
    linea=wxT("\\rput[b](");
    switch(seleccion(wxT("Variables"),wxT("Etiqueta en Figuras")))
    {
      default:
      case 0:
            linea << (int)((xLf+xRf)/2) << wxT(",") << (int)yf+5 << wxT("){") << remplazo(Var->Etiquetas.Item(i).Label) << wxT("}");
            break;
      case 1:
            linea << (int)((xLf+xRf)/2) << wxT(",") << (int)yf+5 << wxT("){") << i+1 << wxT("}");
            break;
    }
    f.AddLine(linea);
  }
//  el valor
  if(seleccion(wxT("Variables"),wxT("Valor por Defecto"))==0 || entrada==0)
  {
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
      xLo = offx + (xLo - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);
      xLf = offx + (xLf - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);
      xRo = offx + (xRo - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);
      xRf = offx + (xRf - Var->Minimo)*(tamx)/(Var->Maximo-Var->Minimo);

      yo = offy +  (yo - 0.0)*(tamy)/(1.0-0.0);
      yf = offy +  (yf - 0.0)*(tamy)/(1.0-0.0);


      linea=wxT("\\psline[linecolor=red](");
      linea << (int)(xLo) << wxT(",") << (int)(yo) << wxT(")(") << (int)(xLf) << wxT(",") << (int)(yf) << wxT(")");
      f.AddLine(linea);
      linea=wxT("\\psline[linecolor=red](");
      linea << (int)(xRo) << wxT(",") << (int)(yo) << wxT(")(") << (int)(xRf) << wxT(",") << (int)(yf) << wxT(")");
      f.AddLine(linea);
    }
    linea=wxT("\\psline[linecolor=red](");
    linea << (int)(xLf) << wxT(",") << (int)(yf) << wxT(")(") << (int)(xRf) << wxT(",") << (int)(yf) << wxT(")");
    f.AddLine(linea);
  }

  linea=wxT("\\end{pspicture}");
  f.AddLine(linea);
  if(seleccion(wxT("Variables"),wxT("Formato de Figuras Latex"))==1)
  {
    linea=wxT("\\end{pdfdisplay}");
    f.AddLine(linea);
  }

  f.Write();
  wxSetWorkingDirectory(dirActual);
  return TRUE;
}

void ReporteLatex::incluirFigura(wxTextFile *f,wxString Nom)
{
  wxString nomTex=wxT("fig/fig_");
  nomTex << cadenaNivelActual().BeforeFirst('.') << wxT(".") << ContadorFiguras;
  nomTex.Replace(wxT("."),wxT("_"));
//  nomTex << ".tex";

  wxString linea=wxT("");
  linea = wxT("\\begin{figure}");
  f->AddLine(linea);
  linea = wxT("\\begin{center}");
  f->AddLine(linea);
  linea = wxT("\\input{");

  linea <<  nomTex << wxT("}");
  f->AddLine(linea);
  linea = wxT("\\end{center}");
  f->AddLine(linea);
  linea = wxT("\\caption{");
  linea << Nom << wxT("}");
  f->AddLine(linea);
  linea = wxT("\\label{fig:");
  linea <<  cadenaNivelActual().BeforeFirst('.') << wxT("_") << ContadorFiguras << wxT("}");
  f->AddLine(linea);
  linea = wxT("\\end{figure}");
  f->AddLine(linea);
}
