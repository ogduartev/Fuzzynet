/***************************************************************
 * Name:      FuzzynetMain.h
 * Purpose:   Defines Application Frame
 * Author:    Oscar Duarte (ogduartev@unal.edu.co)
 * Created:   2017-10-04
 * Copyright: Oscar Duarte ()
 * License:
 **************************************************************/

#ifndef FUZZYNETMAIN_H
#define FUZZYNETMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "FuzzynetApp.h"
#include "proyecto.h"
#include "micanvas.h"
#include<wx/wx.h>
#include<wx/dialog.h>
#include<wx/filedlg.h>

/**
 * Implementa el marco principal
 */
class MiFrame : public wxFrame
{
public:
    MiFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MiFrame();

    void crearMenu();
    void crearBarra();
    void crearAyuda();

    void OnPaint(wxPaintEvent& event);

    void archivoNuevo(wxCommandEvent& event);
    void archivoLeer(wxCommandEvent& event);
    void archivoGuardar(wxCommandEvent&);
    void archivoGuardarComo(wxCommandEvent&);
    void archivoImportar(wxCommandEvent& event);
    void archivoExportar(wxCommandEvent& event);
    void archivoClose(wxCloseEvent&);
    void archivoSalir(wxCommandEvent&);
    void proyectoProyecto(wxCommandEvent& event);
    void proyectoEstrategia(wxCommandEvent& event);
    void proyectoCaso(wxCommandEvent& event);
    void proyectoConfiguracion(wxCommandEvent& event);

    void verRed(wxCommandEvent& event);
    void verCasoRedPalabras(wxCommandEvent& event);
    void verCasoRedValor(wxCommandEvent& event);
    void verCasoRedAmbiguedad(wxCommandEvent& event);
    void verCasoLista(wxCommandEvent& event);
    void verCasoVariables(wxCommandEvent& event);
    void verCasoVariablesTodas(wxCommandEvent& event);
    void verMatrizValor(wxCommandEvent& event);
    void verMatrizAmbiguedad(wxCommandEvent& event);
    void verMatrizInterpretacion(wxCommandEvent& event);
    void verMatrizInterpretacionLarga(wxCommandEvent& event);

    void reportes(wxCommandEvent& event);

    void ayudaABCW(wxCommandEvent& event);
    void ayudaRedesPalabras(wxCommandEvent& event);
    void ayudaManual(wxCommandEvent& event);
    void ayudaAcerca(wxCommandEvent& event);

    void llenarCombos();
    void llenarSpin();
    void cambiaEstrategia(wxCommandEvent&);
    void cambiaCaso(wxCommandEvent&);
    void cambiaColores(wxCommandEvent&);
    void cambiaSpinOpt(wxSpinEvent&);
    void valor(wxCommandEvent&);
    void ambiguedad(wxCommandEvent&);
    void corta(wxCommandEvent&);
    void larga(wxCommandEvent&);
    void redE(wxCommandEvent&);
    void redC(wxCommandEvent&);
    void lista(wxCommandEvent&);
    void variables(wxCommandEvent&);
    void matriz(wxCommandEvent&);

    void noImplementada();

    MiCanvas *canvas;
    Proyecto Proy;
    wxString DirectorioAyuda;
    wxString DirectorioActual;
    wxString ArchivoActual;

    wxIcon Icono;
    wxToolBar *ToolBar;
    wxStatusBar *StatusBar;
    wxMenuBar *MenuBar;
    wxComboBox *ComboEstrategias;
    wxComboBox *ComboCasos;
    wxSpinCtrl *SpinOpt;
    wxStaticText *StaticOpt;

    wxHtmlHelpController *Ayuda;

private:

    DECLARE_EVENT_TABLE()
};

/**
 * Controles y Menús
 */
enum
{
    archivo_Nuevo = 1,
    archivo_Leer,
    archivo_Guardar,
    archivo_GuardarComo,
    archivo_Importar,
    archivo_Exportar,
    archivo_Salir,
    proyecto_Proyecto,
    proyecto_Estrategia,
    proyecto_Caso,
    proyecto_Configuracion,
    ver_Red,
    ver_CasoRedPalabras,
    ver_CasoRedValor,
    ver_CasoRedAmbiguedad,
    ver_CasoLista,
    ver_CasoVariables,
    ver_CasoVariablesTodas,
    ver_MatrizValor,
    ver_MatrizAmbiguedad,
    ver_MatrizInterpretacion,
    ver_MatrizInterpretacionLarga,
    reportes_Proyecto,
    reportes_Proyecto_txt,
    reportes_Proyecto_latex,
    reportes_Proyecto_html,
    reportes_Estrategia,
    reportes_Estrategia_txt,
    reportes_Estrategia_latex,
    reportes_Estrategia_html,
    reportes_Todos_Estrategia,
    reportes_Todos_Estrategia_txt,
    reportes_Todos_Estrategia_latex,
    reportes_Todos_Estrategia_html,
    reportes_Caso,
    reportes_Caso_txt,
    reportes_Caso_latex,
    reportes_Caso_html,
    reportes_Todos_Caso,
    reportes_Todos_Caso_txt,
    reportes_Todos_Caso_latex,
    reportes_Todos_Caso_html,
    reportes_Resultados,
    reportes_Resultados_txt,
    reportes_Resultados_latex,
    reportes_Resultados_html,
    ayuda_ABCW,
    ayuda_RedesPalabras,
    ayuda_Manual,
    ayuda_Acerca,
    tb_combo_Estrategias,
    tb_combo_Casos,
    tb_cambia_Colores,
    tb_spin_Opt,
    tb_valor,
    tb_ambiguedad,
    tb_corta,
    tb_larga,
    tb_redE,
    tb_redC,
    tb_lista,
    tb_variables,
    tb_matriz
};

#endif // FUZZYNETMAIN_H
