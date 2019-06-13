/***************************************************************
 * Name:      FuzzynetMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2017-10-04
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "FuzzynetMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


#include  <wx/menuitem.h>
#include "wx/wizard.h"
#include <wx/html/htmlwin.h>
#include <wx/statline.h>

#include "FuzzynetMain.h"
#include "cadenas.h"
#include "reportetexto.h"
#include "reportehtml.h"
#include "reportelatex.h"
#include "dialogoproyecto.h"
#include "dialogocopiarnumero.h"
#include "dialogocaso.h"
#include "dialogoestrategia.h"
#include "dialogoconfigura.h"
#include "dialogoexportar.h"
#include "dialogoimportar.h"
#include "dialogoreporte.h"
#include "dialogolibreria.h"
#include "xpms.h"

BEGIN_EVENT_TABLE(MiFrame, wxFrame)
//    EVT_PAINT(MiFrame::OnPaint)
    EVT_CLOSE(MiFrame::archivoClose)
    EVT_MENU(archivo_Nuevo,  MiFrame::archivoNuevo)
    EVT_MENU(archivo_Leer,  MiFrame::archivoLeer)
    EVT_MENU(archivo_Guardar,  MiFrame::archivoGuardar)
    EVT_MENU(archivo_GuardarComo,  MiFrame::archivoGuardarComo)
    EVT_MENU(archivo_Importar,  MiFrame::archivoImportar)
    EVT_MENU(archivo_Exportar,  MiFrame::archivoExportar)
    EVT_MENU(archivo_Salir,  MiFrame::archivoSalir)
    EVT_MENU(proyecto_Proyecto,  MiFrame::proyectoProyecto)
    EVT_MENU(proyecto_Estrategia,  MiFrame::proyectoEstrategia)
    EVT_MENU(proyecto_Caso,  MiFrame::proyectoCaso)
    EVT_MENU(proyecto_Configuracion,  MiFrame::proyectoConfiguracion)
    EVT_MENU(ver_Red,  MiFrame::verRed)
    EVT_MENU(ver_CasoRedPalabras,  MiFrame::verCasoRedPalabras)
    EVT_MENU(ver_CasoRedValor,  MiFrame::verCasoRedValor)
    EVT_MENU(ver_CasoRedAmbiguedad,  MiFrame::verCasoRedAmbiguedad)
    EVT_MENU(ver_CasoLista,  MiFrame::verCasoLista)
    EVT_MENU(ver_CasoVariables,  MiFrame::verCasoVariables)
    EVT_MENU(ver_CasoVariablesTodas,  MiFrame::verCasoVariablesTodas)
    EVT_MENU(ver_MatrizValor,  MiFrame::verMatrizValor)
    EVT_MENU(ver_MatrizAmbiguedad,  MiFrame::verMatrizAmbiguedad)
    EVT_MENU(ver_MatrizInterpretacion,  MiFrame::verMatrizInterpretacion)
    EVT_MENU(ver_MatrizInterpretacionLarga,  MiFrame::verMatrizInterpretacionLarga)
    EVT_MENU(reportes_Proyecto_txt,  MiFrame::reportes)
    EVT_MENU(reportes_Proyecto_latex,  MiFrame::reportes)
    EVT_MENU(reportes_Proyecto_html,  MiFrame::reportes)
    EVT_MENU(reportes_Estrategia_txt,  MiFrame::reportes)
    EVT_MENU(reportes_Estrategia_latex,  MiFrame::reportes)
    EVT_MENU(reportes_Estrategia_html,  MiFrame::reportes)
    EVT_MENU(reportes_Todos_Estrategia_txt,  MiFrame::reportes)
    EVT_MENU(reportes_Todos_Estrategia_latex,  MiFrame::reportes)
    EVT_MENU(reportes_Todos_Estrategia_html,  MiFrame::reportes)
    EVT_MENU(reportes_Caso_txt,  MiFrame::reportes)
    EVT_MENU(reportes_Caso_latex,  MiFrame::reportes)
    EVT_MENU(reportes_Caso_html,  MiFrame::reportes)
    EVT_MENU(reportes_Todos_Caso_txt,  MiFrame::reportes)
    EVT_MENU(reportes_Todos_Caso_latex,  MiFrame::reportes)
    EVT_MENU(reportes_Todos_Caso_html,  MiFrame::reportes)
    EVT_MENU(reportes_Resultados_txt,  MiFrame::reportes)
    EVT_MENU(reportes_Resultados_latex,  MiFrame::reportes)
    EVT_MENU(reportes_Resultados_html,  MiFrame::reportes)
    EVT_MENU(ayuda_ABCW,  MiFrame::ayudaABCW)
    EVT_MENU(ayuda_RedesPalabras,  MiFrame::ayudaRedesPalabras)
    EVT_MENU(ayuda_Manual,  MiFrame::ayudaManual)
    EVT_MENU(ayuda_Acerca,  MiFrame::ayudaAcerca)
    EVT_COMBOBOX(tb_combo_Estrategias,  MiFrame::cambiaEstrategia)
    EVT_COMBOBOX(tb_combo_Casos,  MiFrame::cambiaCaso)
    EVT_MENU(tb_cambia_Colores,  MiFrame::cambiaColores)
    EVT_SPINCTRL(tb_spin_Opt,  MiFrame::cambiaSpinOpt)
    EVT_MENU(tb_valor,  MiFrame::valor)
    EVT_MENU(tb_ambiguedad,  MiFrame::ambiguedad)
    EVT_MENU(tb_corta,  MiFrame::corta)
    EVT_MENU(tb_larga,  MiFrame::larga)
    EVT_MENU(tb_redE,  MiFrame::redE)
    EVT_MENU(tb_redC,  MiFrame::redC)
    EVT_MENU(tb_lista,  MiFrame::lista)
    EVT_MENU(tb_variables,  MiFrame::variables)
    EVT_MENU(tb_matriz,  MiFrame::matriz)
END_EVENT_TABLE()

//IMPLEMENT_APP(FuzzynetApp)

/**
 * Constructor del marco
 */

MiFrame::MiFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
#ifdef __WXMAC__
    wxApp::s_macAboutMenuItemId = ayuda_Acerca;
#endif

    Icono=wxIcon();
    Icono.CopyFromBitmap(wxBitmap(icono_xpm));
    SetIcon(Icono);

    crearMenu();
    crearBarra();

    DirectorioActual=::wxGetCwd();
    DirectorioAyuda=DirectorioActual;
    ArchivoActual=wxT("");

    crearAyuda();

}

/**
 * Destructor del marco

 */

MiFrame::~MiFrame()
{
}

void MiFrame::crearMenu()
{
    wxMenu *menuArchivo = new wxMenu;
    wxMenu *menuProyecto = new wxMenu;
    wxMenu *menuVerCaso = new wxMenu;
    wxMenu *menuVerVariables = new wxMenu;
    wxMenu *menuVerMatriz = new wxMenu;
    wxMenu *menuVer = new wxMenu;
    wxMenu *menuReportes = new wxMenu;
    wxMenu *menuReportesProyecto = new wxMenu;
    wxMenu *menuReportesEstrategia = new wxMenu;
    wxMenu *menuReportesTodosEstrategia = new wxMenu;
    wxMenu *menuReportesCaso = new wxMenu;
    wxMenu *menuReportesTodosCaso = new wxMenu;
    wxMenu *menuReportesResultados = new wxMenu;
    wxMenu *menuAyuda = new wxMenu;
    wxMenu *menuPrueba = new wxMenu;

    menuArchivo->Append(archivo_Nuevo, FRAME_MENU_ARCHIVO_NUEVO, FRAME_MENU_HLP_ARCHIVO_NUEVO);
    menuArchivo->Append(archivo_Leer, FRAME_MENU_ARCHIVO_LEER, FRAME_MENU_HLP_ARCHIVO_LEER);
    menuArchivo->Append(archivo_Guardar, FRAME_MENU_ARCHIVO_GUARDAR, FRAME_MENU_HLP_ARCHIVO_GUARDAR);
    menuArchivo->Append(archivo_GuardarComo, FRAME_MENU_ARCHIVO_GUARDARCOMO, FRAME_MENU_HLP_ARCHIVO_GUARDARCOMO);
    menuArchivo->AppendSeparator();
    menuArchivo->Append(archivo_Importar, FRAME_MENU_ARCHIVO_IMPORTAR, FRAME_MENU_HLP_ARCHIVO_IMPORTAR);
    menuArchivo->Append(archivo_Exportar, FRAME_MENU_ARCHIVO_EXPORTAR, FRAME_MENU_HLP_ARCHIVO_EXPORTAR);
    menuArchivo->AppendSeparator();
    menuArchivo->Append(archivo_Salir, FRAME_MENU_ARCHIVO_SALIR, FRAME_MENU_HLP_ARCHIVO_SALIR);

    menuProyecto->Append(proyecto_Proyecto, FRAME_MENU_PROYECTO_PROYECTO, FRAME_MENU_HLP_PROYECTO_PROYECTO);
    menuProyecto->Append(proyecto_Estrategia, FRAME_MENU_PROYECTO_ESTRATEGIA, FRAME_MENU_HLP_PROYECTO_ESTRATEGIA);
    menuProyecto->Append(proyecto_Caso, FRAME_MENU_PROYECTO_CASO, FRAME_MENU_HLP_PROYECTO_CASO);
    menuProyecto->AppendSeparator();
    menuProyecto->Append(proyecto_Configuracion, FRAME_MENU_PROYECTO_CONFIGURACION, FRAME_MENU_HLP_PROYECTO_CONFIGURACION);

    menuVerCaso->Append(ver_CasoRedPalabras,wxT("Palabras"),wxT("Mostrar el caso como una red. Mostrar palabras"));
    menuVerCaso->Append(ver_CasoRedValor,wxT("Valor"),wxT("Mostrar el caso como una red. Mostrar valor representativo"));
    menuVerCaso->Append(ver_CasoRedAmbiguedad,wxT("Ambigüedad"),wxT("Mostrar el caso como una red. Mostrar ambigüedad"));

    menuVerVariables->Append(ver_CasoVariables,wxT("En la Metodología Actual"),wxT("Mostrar las variables del Caso Actual en la Metodología Actual"));

    menuVerVariables->Append(ver_CasoVariablesTodas,wxT("Todas"),wxT("Mostrar Todas las variables del Caso Actual"));

    menuVerMatriz->Append(ver_MatrizValor,wxT("Valor"),wxT("Ver Matriz de casos contra Metodología. Mostrar valor Representativo"));
    menuVerMatriz->Append(ver_MatrizAmbiguedad,wxT("Ambigüedad"),wxT("Ver Matriz de casos contra Metodologías. Mostrar Ambigüedad"));
    menuVerMatriz->Append(ver_MatrizInterpretacion,wxT("Interpretación Corta"),wxT("Ver Matriz de casos contra Metodologías. Mostrar Interpretación Corta"));
    menuVerMatriz->Append(ver_MatrizInterpretacionLarga,wxT("Interpretación Larga"),wxT("Ver Matriz de casos contra Metodologías. Mostrar Interpretación Larga"));

    menuVer->Append(ver_Red,wxT("Metodología Actual como Red"),wxT("Mostrar la Metodología Actual como una Red"));
    menuVer->Append(ver_Red,wxT("Caso Actual como Red"),menuVerCaso,wxT("Mostrar el caso como una Red"));
    menuVer->Append(ver_CasoLista, FRAME_MENU_VER_CASOLISTA, FRAME_MENU_HLP_VER_CASOLISTA);
    menuVer->Append(ver_Red,wxT("Variables del caso Actual"),menuVerVariables,wxT("Mostrar las Variables de Entrada del caso Actual"));
    menuVer->Append(ver_Red,wxT("Matriz"),menuVerMatriz,wxT("Mostrar Matriz de Casos contra Metodologías"));

    menuReportesProyecto->Append(reportes_Proyecto_txt,wxT("Texto"),wxT("Generar un reporte del proyecto en formato ASCII"));
    menuReportesProyecto->Append(reportes_Proyecto_latex,wxT("LaTex"),wxT("Generar un reporte del proyecto en formato LaTex"));
    menuReportesProyecto->Append(reportes_Proyecto_html,wxT("HTML"),wxT("Generar un reporte del proyecto en formato HTML"));

    menuReportesEstrategia->Append(reportes_Estrategia_txt,wxT("Texto"),wxT("Generar un reporte de la Metodología actual en formato ASCII"));
    menuReportesEstrategia->Append(reportes_Estrategia_latex,wxT("LaTex"),wxT("Generar un reporte de la Metodología actual en formato LaTex"));
    menuReportesEstrategia->Append(reportes_Estrategia_html,wxT("HTML"),wxT("Generar un reporte de la Metodología actual en formato HTML"));

    menuReportesTodosEstrategia->Append(reportes_Todos_Estrategia_txt,wxT("Texto"),wxT("Generar un reporte de cada Metodología en formato ASCII"));
    menuReportesTodosEstrategia->Append(reportes_Todos_Estrategia_latex,wxT("LaTex"),wxT("Generar un reporte de cada Metodología en formato LaTex"));
    menuReportesTodosEstrategia->Append(reportes_Todos_Estrategia_html,wxT("HTML"),wxT("Generar un reporte de cada Metodología en formato HTML"));

    menuReportesCaso->Append(reportes_Caso_txt,wxT("Texto"),wxT("Generar un reporte del Caso actual en formato ASCII"));
    menuReportesCaso->Append(reportes_Caso_latex,wxT("LaTex"),wxT("Generar un reporte del Caso actual en formato LaTex"));
    menuReportesCaso->Append(reportes_Caso_html,wxT("HTML"),wxT("Generar un reporte del Caso actual en formato HTML"));

    menuReportesTodosCaso->Append(reportes_Todos_Caso_txt,wxT("Texto"),wxT("Generar un reporte de cada Caso en formato ASCII"));
    menuReportesTodosCaso->Append(reportes_Todos_Caso_latex,wxT("LaTex"),wxT("Generar un reporte de cada Caso en formato LaTex"));
    menuReportesTodosCaso->Append(reportes_Todos_Caso_html,wxT("HTML"),wxT("Generar un reporte de cada Caso en formato HTML"));

    menuReportesResultados->Append(reportes_Resultados_txt,wxT("Texto"),wxT("Generar un reporte de los Resultados en formato ASCII"));
    menuReportesResultados->Append(reportes_Resultados_latex,wxT("LaTex"),wxT("Generar un reporte de los Resultados en formato LaTex"));
    menuReportesResultados->Append(reportes_Resultados_html,wxT("HTML"),wxT("Generar un reporte de los Resultados en formato HTML"));

    menuReportes->Append(reportes_Proyecto, FRAME_MENU_REPORTES_PROYECTO, menuReportesProyecto, FRAME_MENU_HLP_REPORTES_PROYECTO);
    menuReportes->Append(reportes_Estrategia, FRAME_MENU_REPORTES_ESTRATEGIA, menuReportesEstrategia,FRAME_MENU_HLP_REPORTES_ESTRATEGIA);
    menuReportes->Append(reportes_Todos_Estrategia, wxT("Todas las Metodologías") , menuReportesTodosEstrategia, wxT("Generar un reporte para cada una de las Metodologías"));

    menuReportes->Append(reportes_Caso, FRAME_MENU_REPORTES_CASO, menuReportesCaso,FRAME_MENU_HLP_REPORTES_CASO);
    menuReportes->Append(reportes_Todos_Caso, wxT("Todos los Casos"), menuReportesTodosCaso, wxT("Generar un reporte para cada uno de los Casos"));
    menuReportes->Append(reportes_Resultados, FRAME_MENU_REPORTES_RESULTADOS, menuReportesResultados,FRAME_MENU_HLP_REPORTES_RESULTADOS);

    menuAyuda->Append(ayuda_ABCW, FRAME_MENU_AYUDA_ABCW, FRAME_MENU_HLP_AYUDA_ABCW);
    menuAyuda->Append(ayuda_RedesPalabras, FRAME_MENU_AYUDA_REDES, FRAME_MENU_HLP_AYUDA_REDES);
    menuAyuda->Append(ayuda_Manual, FRAME_MENU_AYUDA_MANUAL, FRAME_MENU_HLP_AYUDA_MANUAL);
    menuAyuda->Append(ayuda_Acerca, FRAME_MENU_AYUDA_ACERCA, FRAME_MENU_HLP_AYUDA_ACERCA);

    MenuBar = new wxMenuBar();
    SetMenuBar(MenuBar);

    MenuBar->Append(menuArchivo, FRAME_MENU_ARCHIVO);
    MenuBar->Append(menuProyecto, FRAME_MENU_PROYECTO);
    MenuBar->Append(menuVer, FRAME_MENU_VER);
    MenuBar->Append(menuReportes, FRAME_MENU_REPORTES);
    MenuBar->Append(menuAyuda, FRAME_MENU_AYUDA);
}

void MiFrame::crearBarra()
{
    StatusBar=CreateStatusBar(1);
    SetStatusBar(StatusBar);
    SetStatusText(FRAME_STATUSBAR_VACIO);

    ToolBar=CreateToolBar();
    SetToolBar(ToolBar);

    ComboEstrategias=new wxComboBox(ToolBar,tb_combo_Estrategias,wxT(""),wxPoint(0,0),wxSize(150,20));
    ComboCasos=new wxComboBox(ToolBar,tb_combo_Casos,wxT(""),wxPoint(0,0),wxSize(150,20));
    llenarCombos();
    StaticOpt=new wxStaticText(ToolBar,-1,wxT("Opt(%):"));
    SpinOpt=new wxSpinCtrl(ToolBar,tb_spin_Opt,wxT(""),wxPoint(0,0),wxSize(50,20));
//    SpinOpt->SetMinSize(wxSize(30,20));
//    ComboEstrategias->SetMinSize(wxSize(100,20));
//    ComboCasos->SetMinSize(wxSize(100,20));

    llenarSpin();

    ToolBar->AddTool(archivo_Nuevo,wxT(""),wxBitmap(nuevo_xpm),wxT("Nuevo"));
    ToolBar->AddTool(archivo_Leer,wxT(""),wxBitmap(leer_xpm),wxT("Leer"));
    ToolBar->AddTool(archivo_Guardar,wxT(""),wxBitmap(guardar_xpm),wxT("Guardar"));
    ToolBar->AddTool(archivo_Importar,wxT(""),wxBitmap(importar_xpm),wxT("Importar"));
    ToolBar->AddTool(archivo_Exportar,wxT(""),wxBitmap(exportar_xpm),wxT("Exportar"));
    ToolBar->AddSeparator();
    ToolBar->AddControl(ComboEstrategias);
    ToolBar->AddControl(ComboCasos);
    ToolBar->AddSeparator();
    ToolBar->AddControl(StaticOpt);
    ToolBar->AddControl(SpinOpt);
    ToolBar->AddSeparator();
    ToolBar->AddTool(tb_cambia_Colores,wxT(""),wxBitmap(colores_xpm),wxT("Mostrar/Ocultar Colores"));
    ToolBar->AddTool(tb_valor,wxT(""),wxBitmap(valor_xpm),wxT("Valor Representativo"));
    ToolBar->AddTool(tb_ambiguedad,wxT(""),wxBitmap(ambiguedad_xpm),wxT("Ambigedad"));
    ToolBar->AddTool(tb_corta,wxT(""),wxBitmap(corta_xpm),wxT("Interpretación Corta"));
    ToolBar->AddTool(tb_larga,wxT(""),wxBitmap(larga_xpm),wxT("Interpretación Larga"));
    ToolBar->AddTool(tb_redE,wxT(""),wxBitmap(redM_xpm),wxT("Metodología"));
    ToolBar->AddTool(tb_redC,wxT(""),wxBitmap(redC_xpm),wxT("Caso como una Red"));
    ToolBar->AddTool(tb_lista,wxT(""),wxBitmap(lista_xpm),wxT("Caso como una Lista"));
    ToolBar->AddTool(tb_variables,wxT(""),wxBitmap(variables_xpm),wxT("Variables de Entrada del caso"));
    ToolBar->AddTool(tb_matriz,wxT(""),wxBitmap(matriz_xpm),wxT("Matriz Total"));

    ToolBar->Realize();

}

void MiFrame::crearAyuda()
{
  wxInitAllImageHandlers();
  Ayuda= new wxHtmlHelpController (wxHF_DEFAULT_STYLE|wxHF_OPEN_FILES);
  wxString dirAyuda=DirectorioAyuda;
  wxString nomAyuda=wxT("/help/scp/help.hhp");
  nomAyuda=dirAyuda+nomAyuda;
  int flag=0;
  if(!wxFileExists(nomAyuda))
  {
    flag=1;
    wxConfig * Configura;
    switch(ESPECIFICO)
    {
      case 0:Configura = new wxConfig(wxT("fuzzynet"));break;
      case 1:Configura = new wxConfig(wxT("ediav"));break;
      case 5:Configura = new wxConfig(wxT("eviave"));break;
      default:Configura = new wxConfig(wxT("fuzzynet"));break;
    }
    Configura->SetPath(wxT("Ayuda"));
    Configura->Read(wxT("Directorio"),&dirAyuda);
    if(dirAyuda==wxT(""))
    {
      dirAyuda=wxGetCwd();
    }
    delete Configura;
    nomAyuda=wxT("/help/scp/help.hhp");
    nomAyuda=dirAyuda+nomAyuda;
    if(!wxFileExists(nomAyuda))
    {
      flag=1;
    }else
    {
      flag=0;
    }
  }

  if(flag==1)
  {
    if(wxMessageBox(wxT("No se encontró el archivo de ayuda ") + nomAyuda + wxT(". Desea buscarlo?"),wxT("Atencón"),wxICON_QUESTION | wxYES_NO)==wxYES)
    {
      wxString ArchivoTmp=nomAyuda;
      wxFileDialog Dial(this,wxT("Leer archivo de ayuda"),DirectorioActual,ArchivoTmp,wxT("Archivos de ayuda (*.hhp)|*.hhp|Todos los archivos (*.*)|*.*"),wxFD_OPEN|wxFD_CHANGE_DIR);
      if(Dial.ShowModal()==wxID_OK)
      {
        nomAyuda=Dial.GetFilename();
        dirAyuda=Dial.GetDirectory();
        dirAyuda.Replace(wxT("/help/scp"),wxT(""));
      }
    }
  }
  if(wxFileExists(nomAyuda))
  {
    Ayuda->AddBook(nomAyuda);
  }
  nomAyuda=wxT("/help/redes/help.hhp");
  nomAyuda=dirAyuda+nomAyuda;

  if(!wxFileExists(nomAyuda))
  {
    if(wxMessageBox(wxT("No se encontró el archivo de ayuda ") + nomAyuda + wxT(". Desea buscarlo?"),wxT("Atención"),wxICON_QUESTION | wxYES_NO)==wxYES)
    {
      wxString ArchivoTmp=nomAyuda;
      wxFileDialog Dial(this,wxT("Leer archivo de ayuda"),DirectorioActual,ArchivoTmp,wxT("Archivos de ayuda (*.hhp)|*.hhp|Todos los archivos (*.*)|*.*"),wxFD_OPEN|wxFD_CHANGE_DIR);
      if(Dial.ShowModal()==wxID_OK)
      {
        nomAyuda=Dial.GetFilename();
        dirAyuda=Dial.GetDirectory();
        dirAyuda.Replace(wxT("/help/redes"),wxT(""));
      }
    }
  }
  if(wxFileExists(nomAyuda))
  {
    Ayuda->AddBook(nomAyuda);
  }
  switch(ESPECIFICO)
  {
    case 0: nomAyuda=wxT("/help/fzn/help.hhp");break;
    case 1: nomAyuda=wxT("/help/ediav/help.hhp");break;
    case 5: nomAyuda=wxT("/help/eviave/help.hhp");break;
    default: nomAyuda=wxT("/help/fzn/help.hhp");break;
  }
  nomAyuda=dirAyuda+nomAyuda;
  if(!wxFileExists(nomAyuda))
  {
    if(wxMessageBox(wxT("No se encontró el archivo de ayuda ") + nomAyuda + wxT(". Desea buscarlo?"),wxT("Atención"),wxICON_QUESTION | wxYES_NO)==wxYES)
    {
      wxString ArchivoTmp=nomAyuda;
      wxFileDialog Dial(this,wxT("Leer archivo de ayuda"),DirectorioActual,ArchivoTmp,wxT("Archivos de ayuda (*.hhp)|*.hhp|Todos los archivos (*.*)|*.*"),wxFD_OPEN|wxFD_CHANGE_DIR);
      if(Dial.ShowModal()==wxID_OK)
      {
        nomAyuda=Dial.GetFilename();
        dirAyuda=Dial.GetDirectory();
        switch(ESPECIFICO)
        {
          case 0:dirAyuda.Replace(wxT("help/fzn"),wxT(""));break;
          case 1:dirAyuda.Replace(wxT("help/ediav"),wxT(""));break;
          case 5:dirAyuda.Replace(wxT("help/eviave"),wxT(""));break;
          default:dirAyuda.Replace(wxT("help/fzn"),wxT(""));break;
	}
      }
    }
  }
  if(wxFileExists(nomAyuda))
  {
    Ayuda->AddBook(nomAyuda);
  }
  wxConfig * Configura;
  switch(ESPECIFICO)
  {
    case 0:Configura = new wxConfig(wxT("fuzzynet"));break;
    case 1:Configura = new wxConfig(wxT("ediav"));break;
    case 5:Configura = new wxConfig(wxT("eviave"));break;
    default:Configura = new wxConfig(wxT("fuzzynet"));break;
  }
  Configura->SetPath(wxT("Ayuda"));
  Configura->Write(wxT("Directorio"),dirAyuda);
  DirectorioAyuda=dirAyuda;
  delete Configura;
}

// Define the repainting behaviour
void MiFrame::OnPaint(wxPaintEvent& event)
{
  canvas->Refresh();
}


/**
 * Leer el proyecto.
 */
void MiFrame::archivoNuevo(wxCommandEvent& WXUNUSED(event))
{
    if(Proy.ProyectoModificado)
    {
      long bandera=wxMessageBox(wxT("Desea salvar el proyecto actual?"),wxT("Advertencia. Proyecto Modificado"),wxYES_NO|wxCANCEL);
      wxCommandEvent ev;
      switch(bandera)
      {
        case wxYES:
              archivoGuardar(ev);
              break;
        case wxNO:
              break;
        case wxCANCEL:
              return;
        default :
              return;
      }
    }
    if(!ESPECIFICO)
    {
      wxString opciones[4];
      opciones[0]=wxT("Vacío");
      opciones[1]=wxT("Evaluación Difusa de Vertederos");
      opciones[2]=wxT("Evaluación Inteligente de Vertederos 2");
      opciones[3]=wxT("QFD");
      wxSingleChoiceDialog Dial(this,wxT("Opciones disponibles"),wxT("Proyecto Nuevo"),4,opciones);
      if(Dial.ShowModal()==wxID_OK)
      {
        int Op;
        Op=Dial.GetSelection();
	switch(Op)
	{
	  case 0: Op=0;break;
	  case 1: Op=1;break;
	  case 2: Op=5;break;
	  case 3: Op=3;break;
	  default: Op=0;break;
	}
        Proy.iniciar(Op);
      }
    }else
    {
      Proy.iniciar(ESPECIFICO);
    }
    Proy.NumCaso=0;
    Proy.NumEstrategia=0;
    Proy.ProyectoModificado=FALSE;

    llenarCombos();
    canvas->Ver=VER_RED;
    canvas->llenarRegiones();
    canvas->Refresh();
}
/**
 * Leer el proyecto.
 */

void MiFrame::archivoLeer(wxCommandEvent& WXUNUSED(event))
{
    if(Proy.ProyectoModificado)
    {
      long bandera=wxMessageBox(wxT("Desea salvar el proyecto actual?"),wxT("Advertencia. Proyecto Modificado"),wxYES_NO|wxCANCEL);
      wxCommandEvent ev;
      switch(bandera)
      {
        case wxYES:
              archivoGuardar(ev);
              break;
        case wxNO:
              break;
        case wxCANCEL:
              return;
        default :
              return;
      }

    }
    wxString DirectorioTmp=DirectorioActual;
    wxString ArchivoTmp=ArchivoActual;
    wxString cadDial;
    switch(ESPECIFICO)
    {
      case 0:cadDial=wxT("Archivos Fuzzynet (*.fzn)|*.fzn|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
      case 1:cadDial=wxT("Archivos EDIAV (*.edv)|*.edv|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
      case 5:cadDial=wxT("Archivos EVIAVE (*.evv)|*.evv|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
      default:cadDial=wxT("Archivos Fuzzynet (*.fzn)|*.fzn|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
    }
    wxFileDialog Dial(this,FRAME_PROYECTO_LEER_CAPTION,DirectorioTmp,ArchivoTmp,cadDial,wxFD_OPEN|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoTmp=Dial.GetFilename();
      DirectorioTmp=Dial.GetDirectory();
      if(wxFileExists(ArchivoTmp))
      {

        Mi_ifpstream FileProy(ArchivoTmp);
        ::wxSetCursor(wxCURSOR_WATCH);
        if(!Proy.read(FileProy))
	{
	  wxMessageBox(wxT("El archivo no es del tipo correcto"),wxT("Error"));
	}else
	{
          Proy.NumCaso=0;
          Proy.NumEstrategia=0;
          Proy.ProyectoModificado=FALSE;
          llenarCombos();
          llenarSpin();
          canvas->Ver=VER_RED;
          canvas->llenarRegiones();
          canvas->Refresh();

          SetStatusText(ArchivoTmp);
          ArchivoActual=ArchivoTmp;
          DirectorioActual=DirectorioTmp;
	}
        ::wxSetCursor(wxCURSOR_ARROW);
      }else
      {
        wxMessageBox(wxT("El archivo no existe "),wxT("Error"));
      }
    }
  canvas->Refresh();
}

/**
 * Guardar el proyecto.
 */
void MiFrame::archivoGuardar(wxCommandEvent&)
{
  if(ArchivoActual==wxT(""))
  {
    wxCommandEvent ev;
    archivoGuardarComo(ev);
  }else
  {
    Mi_ofpstream FileProy(ArchivoActual);
    ::wxSetCursor(wxCURSOR_WATCH);
    Proy.write(FileProy);
    ::wxSetCursor(wxCURSOR_ARROW);
    Proy.ProyectoModificado=FALSE;
    SetStatusText(ArchivoActual);
    canvas->Refresh();
  }
}

/**


 * Guardar el proyecto seleccionando el nombre.
 */
void MiFrame::archivoGuardarComo(wxCommandEvent&)
{
    wxString DirectorioTmp=DirectorioActual;
    wxString ArchivoTmp=ArchivoActual;

    wxString cadDial;
    switch(ESPECIFICO)
    {
      case 0:cadDial=wxT("Archivos Fuzzynet (*.fzn)|*.fzn|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
      case 1:cadDial=wxT("Archivos EDIAV (*.edv)|*.edv|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
      case 5:cadDial=wxT("Archivos EVIAVE (*.evv)|*.evv|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
      default:cadDial=wxT("Archivos Fuzzynet (*.fzn)|*.fzn|Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");
	    break;
    }
    wxFileDialog Dial(this,FRAME_PROYECTO_LEER_CAPTION,DirectorioTmp,ArchivoTmp,cadDial,wxFD_SAVE|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoTmp=Dial.GetFilename();
      DirectorioTmp=Dial.GetDirectory();

      Mi_ofpstream FileProy(ArchivoTmp);
      ::wxSetCursor(wxCURSOR_WATCH);
      Proy.write(FileProy);
      ::wxSetCursor(wxCURSOR_ARROW);
      Proy.ProyectoModificado=FALSE;

      SetStatusText(ArchivoTmp);
      ArchivoActual=ArchivoTmp;
      DirectorioActual=DirectorioTmp;
      canvas->Ver=VER_RED;
      canvas->llenarRegiones();
      canvas->Refresh();
    }
}


void MiFrame::archivoClose(wxCloseEvent&)
{
  wxCommandEvent ev;
  archivoSalir(ev);
}

/**

 * Final del programa. Debe revisarse para verificar si se puede salir
 */
void MiFrame::archivoSalir(wxCommandEvent&)
{
    if(Proy.ProyectoModificado)
    {
      long bandera=wxMessageBox(wxT("Desea salvar el proyecto actual?"),wxT("Advertencia. Proyecto Modificado"),wxYES_NO|wxCANCEL);
      wxCommandEvent ev;
      switch(bandera)
      {
        case wxYES:
              archivoGuardar(ev);
              break;
        case wxNO:
              break;
        case wxCANCEL:
              return;
        default :
              return;
      }
    }
//  canvas->Proy=NULL;
  Destroy();
}

/**
 *
 */
void MiFrame::archivoImportar(wxCommandEvent& WXUNUSED(event))
{
  canvas->Ver=VER_RED;
  canvas->llenarRegiones();
  canvas->Refresh();
  DialogoImportar dlg(&Proy, this,wxT("Importar"), Ayuda);
  dlg.ShowModal();
  llenarCombos();
  llenarSpin();
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 *

 */
void MiFrame::archivoExportar(wxCommandEvent& WXUNUSED(event))
{
  DialogoExportar dlg(&Proy, this,wxT("Exportar"), Ayuda);
  dlg.ShowModal();
}

/**
 * Ver la Información Básica del Proyecto
 */
void MiFrame::proyectoProyecto(wxCommandEvent& WXUNUSED(event))
{
  canvas->Ver=VER_RED;
  canvas->llenarRegiones();
  canvas->Refresh();
  DialogoProyecto dlg(&Proy, canvas, this,wxT("Proyecto"), Ayuda);
  dlg.ShowModal();
  llenarCombos();
  llenarSpin();
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Edición de Estrategia
 */
void MiFrame::proyectoEstrategia(wxCommandEvent&  WXUNUSED(event))
{
  Estrategia *est;
  est=&Proy.Estrategias.Item(Proy.NumEstrategia);
  DialogoEstrategia dlg(est, &Proy, canvas, this, Ayuda);
  dlg.ShowModal();
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Edición de Caso
 */
void MiFrame::proyectoCaso(wxCommandEvent&  WXUNUSED(event))
{
  Caso *cas;
  cas=&Proy.Casos.Item(Proy.NumCaso);
  DialogoCaso dlg(canvas, cas, &Proy,this, Ayuda);
  dlg.ShowModal();
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Opción no implementada
 */

void MiFrame::proyectoConfiguracion(wxCommandEvent&  WXUNUSED(event))

{
  DialogoConfigura dlg(canvas,this,wxT("Configuración"), Ayuda);
  dlg.ShowModal();
  canvas->Refresh();
}

/**
 * Visualizar la Estrategia
 */
void MiFrame::verRed(wxCommandEvent& event)
{
  canvas->Ver=VER_RED;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar El caso como Red. Muestra palabras
 */
void MiFrame::verCasoRedPalabras(wxCommandEvent& event)
{
  canvas->Ver=VER_CASO_RED;
  canvas->VerVariable=1;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar El caso como Red. Muestra el Valor Representativo
 */
void MiFrame::verCasoRedValor(wxCommandEvent& event)
{
  canvas->Ver=VER_CASO_RED;
  canvas->VerVariable=2;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar El caso como Red. Muestra la Ambigedad
 */

void MiFrame::verCasoRedAmbiguedad(wxCommandEvent& event)
{
  canvas->Ver=VER_CASO_RED;
  canvas->VerVariable=3;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar el caso como Lista
 */
void MiFrame::verCasoLista(wxCommandEvent& event)
{
  canvas->Ver=VER_CASO_LISTA;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar las variables del Caso Relacionadas con la estrategia
 */
void MiFrame::verCasoVariables(wxCommandEvent& event)
{

  canvas->Ver=VER_CASO_VARIABLES;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar todas las variables del Caso
 */
void MiFrame::verCasoVariablesTodas(wxCommandEvent& event)

{
  canvas->Ver=VER_CASO_VARIABLES_TODAS;
  canvas->llenarRegiones();
  canvas->Refresh();
}


/**
 * Visualizar la Matriz de Casos y Estrategias. Ver Valores
 */
void MiFrame::verMatrizValor(wxCommandEvent& event)
{
  canvas->Ver=VER_MATRIZ;
  canvas->VistaMatriz=0;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar la Matriz de Casos y Estrategias. Ver Ambiguedades
 */
void MiFrame::verMatrizAmbiguedad(wxCommandEvent& event)
{
  canvas->Ver=VER_MATRIZ;
  canvas->VistaMatriz=1;
  canvas->llenarRegiones();
  canvas->Refresh();

}

/**
 * Visualizar la Matriz de Casos y Estrategias. Ver Interpretaciones
 */
void MiFrame::verMatrizInterpretacion(wxCommandEvent& event)
{
  canvas->Ver=VER_MATRIZ;
  canvas->VistaMatriz=2;
  canvas->llenarRegiones();
  canvas->Refresh();
}

/**
 * Visualizar la Matriz de Casos y Estrategias. Ver Interpretaciones Largas
 */
void MiFrame::verMatrizInterpretacionLarga(wxCommandEvent& event)
{
  canvas->Ver=VER_MATRIZ;

  canvas->VistaMatriz=3;
  canvas->llenarRegiones();
  canvas->Refresh();
}


void MiFrame::reportes(wxCommandEvent& event)
{
  int Tipo,Contenido;
  switch(event.GetId())
  {
    case reportes_Proyecto_txt :Tipo=1;Contenido=1;break;
    case reportes_Proyecto_latex :Tipo=2;Contenido=1;break;
    case reportes_Proyecto_html :Tipo=3;Contenido=1;break;
    case reportes_Estrategia_txt :Tipo=1;Contenido=2;break;
    case reportes_Estrategia_latex :Tipo=2;Contenido=2;break;
    case reportes_Estrategia_html :Tipo=3;Contenido=2;break;
    case reportes_Todos_Estrategia_txt :Tipo=1;Contenido=3;break;
    case reportes_Todos_Estrategia_latex :Tipo=2;Contenido=3;break;
    case reportes_Todos_Estrategia_html :Tipo=3;Contenido=3;break;
    case reportes_Caso_txt :Tipo=1;Contenido=4;break;
    case reportes_Caso_latex :Tipo=2;Contenido=4;break;
    case reportes_Caso_html :Tipo=3;Contenido=4;break;
    case reportes_Todos_Caso_txt :Tipo=1;Contenido=5;break;
    case reportes_Todos_Caso_latex :Tipo=2;Contenido=5;break;
    case reportes_Todos_Caso_html :Tipo=3;Contenido=5;break;
    case reportes_Resultados_txt :Tipo=1;Contenido=6;break;
    case reportes_Resultados_latex :Tipo=2;Contenido=6;break;
    case reportes_Resultados_html :Tipo=3;Contenido=6;break;
    default : return;
  }

  wxString dirActual;
  dirActual=wxGetCwd();
  DialogoReporte dlg(&Proy,Contenido,Tipo,this,wxT("Generación de Reportes"), Ayuda);
  dlg.ShowModal();
  wxSetWorkingDirectory(dirActual);
}

void MiFrame::ayudaABCW(wxCommandEvent& event)
{
  Ayuda->Display(wxT("Sistemas de Computación con Palabras"));
}

void MiFrame::ayudaRedesPalabras(wxCommandEvent& event)
{
  Ayuda->Display(wxT("Introducción a las Redes de Cálculo con Palabras"));
}

void MiFrame::ayudaManual(wxCommandEvent& event)
{
  switch(ESPECIFICO)
  {
    case 0:Ayuda->Display(wxT("Fuzzynet - Manual del Usuario"));break;
    case 1:Ayuda->Display(wxT("EDIAV - Manual del Usuario"));break;
    case 5:Ayuda->Display(wxT("EVIAVE - Manual del Usuario"));break;
    default:Ayuda->Display(wxT("Fuzzynet - Manual del Usuario"));break;
  }
}

void MiFrame::ayudaAcerca(wxCommandEvent& event)
{
  wxBoxSizer *topsizer;
  wxHtmlWindow *html;
  wxDialog dlg(this, -1, wxString(_("Acerca de ...")));

  topsizer = new wxBoxSizer(wxVERTICAL);

  html = new wxHtmlWindow(&dlg, -1, wxDefaultPosition, wxSize(380, 160), wxHW_SCROLLBAR_NEVER);
  html -> SetBorders(0);
  wxString dirAyuda;
  wxString nomAcerca;
  dirAyuda=DirectorioAyuda;
  switch(ESPECIFICO)
  {
   case 0:nomAcerca=dirAyuda+wxT("/help/acerca/acerca_fuzzynet.html");break;
   case 1:nomAcerca=dirAyuda+wxT("/help/acerca/acerca_ediav.html");break;
   case 5:nomAcerca=dirAyuda+wxT("/help/acerca/acerca_eviave.html");break;
   default:nomAcerca=dirAyuda+wxT("/help/acerca/acerca_fuzzynet.html");break;
  }
  if(wxFileExists(nomAcerca))
  {
    html -> LoadPage(nomAcerca);
  }else
  {
    switch(ESPECIFICO)
    {
      case 0: html-> SetPage(wxT("<html><body>FUZZYNET 1.0<BR>Software desarrollado por colaboración entre la Universidad de Granada (España) y la Universidad Nacional de Colombia. La implementación ha sido desarrollada por Oscar G. Duarte de la Univ. Nacional de Colombia en Bogota<BR> Oscar G. Duarte <BR>http://www.ing.unal.edu.co/~ogduarte <BR> Universidad Nacional de Colombia<BR></body></html>"));break;
      case 1: html-> SetPage(wxT("<html><body>EDIAV 1.0<BR>Software desarrollado con el Proyecto I+D TIC2002-04330-C02-02 de la DGI del MCyT (Madrid. Españña). La implementación ha sido desarrollada por Oscar G. Duarte de la Univ. Nacional de Colombia en Bogota<BR> Oscar G. Duarte <BR>http://www.ing.unal.edu.co/~ogduarte <BR> Universidad Nacional de Colombia<BR></body></html>"));break;
      case 5: html-> SetPage(wxT("<html><body>EVIAVE 1.0<BR>Software desarrollado con el Proyecto I+D TIC2002-04330-C02-01 y 02 de la DGI del MCyT (Madrid. España). La implementación ha sido desarrollada por Oscar G. Duarte de la Univ. Nacional de Colombia en Bogota<BR> Oscar G. Duarte <BR>http://www.ing.unal.edu.co/~ogduarte <BR> Universidad Nacional de Colombia<BR></body></html>"));break;
      default: html-> SetPage(wxT("<html><body>FUZZYNET 1.0<BR>Software desarrollado por colaboración entre la Universidad de Granada (España) y la Universidad Nacional de Colombia. La implementación ha sido desarrollada por Oscar G. Duarte de la Univ. Nacional de Colombia en Bogota<BR> Oscar G. Duarte <BR>http://www.ing.unal.edu.co/~ogduarte <BR> Universidad Nacional de Colombia<BR></body></html>"));break;
    }
  }
  html -> SetSize(html -> GetInternalRepresentation() -> GetWidth(),
                  html -> GetInternalRepresentation() -> GetHeight());

  topsizer -> Add(html, 1, wxALL, 10);
//  topsizer -> Add(new wxStaticLine(&dlg, -1), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
  wxButton *bu1 = new wxButton(&dlg, wxID_OK, _("OK"));
  bu1 -> SetDefault();
  topsizer -> Add(bu1, 0, wxALL | wxALIGN_RIGHT, 15);

  dlg.SetAutoLayout(TRUE);
  dlg.SetSizer(topsizer);
  topsizer -> Fit(&dlg);
  dlg.ShowModal();
}

void MiFrame::llenarCombos()
{

  int i,tam;
  ComboEstrategias->Clear();
  tam=Proy.Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    ComboEstrategias->Append(Proy.Estrategias.Item(i).Nombre);
  }
  ComboCasos->Clear();
  tam=Proy.Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    ComboCasos->Append(Proy.Casos.Item(i).Nombre);
  }
  ComboEstrategias->SetSelection(Proy.NumEstrategia);
  ComboCasos->SetSelection(Proy.NumCaso);
}

void MiFrame::llenarSpin()
{
  SpinOpt->SetValue(Proy.Optimismo*100.0);

}

void MiFrame::cambiaEstrategia(wxCommandEvent&)

{
  int sel;
  sel=ComboEstrategias->GetSelection();
  if(sel>-1 && sel < Proy.Estrategias.GetCount())
  {
    Proy.NumEstrategia=sel;
  }
  canvas->llenarRegiones();
  canvas->Refresh();

}

void MiFrame::cambiaCaso(wxCommandEvent&)
{
  int sel;
  sel=ComboCasos->GetSelection();
  if(sel>-1 && sel < Proy.Casos.GetCount())

  {
    Proy.NumCaso=sel;
  }
  canvas->llenarRegiones();
  canvas->Refresh();
}



void MiFrame::cambiaColores(wxCommandEvent&)
{
  int col;
  col=canvas->Selecciones.Seleccion(wxT("Mostrar Colores"));
  col=(col+1)%2;
  canvas->Selecciones.seleccion(wxT("Mostrar Colores"),col);
  canvas->Refresh();
}

void MiFrame::cambiaSpinOpt(wxSpinEvent&)
{
  int d;
  d=SpinOpt->GetValue();
  Proy.Optimismo=((float)d)/100.0;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::valor(wxCommandEvent&)
{
  canvas->VerVariable=2;
  canvas->VistaMatriz=0;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::ambiguedad(wxCommandEvent&)
{
  canvas->VerVariable=3;
  canvas->VistaMatriz=1;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::corta(wxCommandEvent&)
{
  canvas->VerVariable=1;
  canvas->VistaMatriz=2;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::larga(wxCommandEvent&)

{

  canvas->VistaMatriz=3;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::redE(wxCommandEvent&)
{

  canvas->Ver=VER_RED;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::redC(wxCommandEvent&)
{

  canvas->Ver=VER_CASO_RED;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::lista(wxCommandEvent&)
{
  canvas->Ver=VER_CASO_LISTA;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::variables(wxCommandEvent&)
{
  canvas->Ver=VER_CASO_VARIABLES;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::matriz(wxCommandEvent&)

{
  canvas->Ver=VER_MATRIZ;
  canvas->llenarRegiones();
  canvas->Refresh();
}

void MiFrame::noImplementada()
{
 wxMessageBox(FRAME_NOIMPLEMENTADA, GENERAL_ADVERTENCIA, wxOK | wxICON_INFORMATION, this);
}
