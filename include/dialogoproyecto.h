/***************************************************************************
                          dialogoproyecto.h  -  description
                             -------------------
    begin                : jue jul 24 2003
    copyright            : (C) 2003 by 
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

#ifndef DIALOGOPROYECTO_H
#define DIALOGOPROYECTO_H

/**
  *@author 
  */

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "dialogocaso.h"
#include "dialogoestrategia.h"
#include "dialogoordenarcasos.h"
#include "dialogopropiedades.h"

class DialogoProyecto : public wxDialog  {
public: 
	DialogoProyecto(Proyecto *pr, MiCanvas *canvas, wxWindow *parent, const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoProyecto();

  void cerrarOK(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  void llenarCuadro();
  void leerCuadro();

  void nuevaEstrategia(wxCommandEvent&);
  void nuevoCaso(wxCommandEvent&);
  void borrarEstrategia(wxCommandEvent&);
  void borrarCaso(wxCommandEvent&);
  void editarEstrategia(wxCommandEvent&);
  void editarCaso(wxCommandEvent&);
  void seleccionEstrategia(wxCommandEvent&);
  void seleccionCaso(wxCommandEvent&);
  void ordenarCasos(wxCommandEvent&);
  void propiedades(wxCommandEvent&);
  
private:
    Proyecto *Proy;
    MiCanvas *Canvas;
    wxHtmlHelpController *Ayuda;
        
    wxButton *ButtonEditarEstrategia;
    wxButton *ButtonNuevaEstrategia;
    wxButton *ButtonBorrarEstrategia;
    wxButton *ButtonOrdenarEstrategia;
    wxButton *ButtonEditarCaso;
    wxButton *ButtonNuevoCaso;
    wxButton *ButtonBorrarCaso;
    wxButton *ButtonOrdenarCaso;
    wxButton *ButtonPropiedades;
    wxButton *ButtonOK;
//    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxListBox *ListBoxEstrategias;
    wxListBox *ListBoxCasos;
    wxStaticText *StaticEstrategias;
    wxStaticText *StaticCasos;
    wxStaticText *StaticOptimismo;
    wxStaticText *StaticRepresentatividad;
    wxStaticText *StaticDescripcion;
    wxTextCtrl *TextDescripcion;
    wxTextCtrl *TextOptimismo;
    wxTextCtrl *TextRepresentatividad;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PROYECTO_BTN_EDITAR_ESTRATEGIA = 1,
  DLG_PROYECTO_BTN_NUEVA_ESTRATEGIA,
  DLG_PROYECTO_BTN_BORRAR_ESTRATEGIA,
  DLG_PROYECTO_BTN_ORDENAR_ESTRATEGIA,
  DLG_PROYECTO_BTN_EDITAR_CASO,
  DLG_PROYECTO_BTN_NUEVO_CASO,
  DLG_PROYECTO_BTN_BORRAR_CASO,
  DLG_PROYECTO_BTN_ORDENAR_CASO,
  DLG_PROYECTO_BTN_PROPIEDADES,
  DLG_PROYECTO_BTN_OK,
  DLG_PROYECTO_BTN_CANCELAR,
  DLG_PROYECTO_BTN_AYUDA,
  DLG_PROYECTO_LISTBOX_ESTRATEGIAS,
  DLG_PROYECTO_LISTBOX_CASOS,
  DLG_PROYECTO_STATIC_ESTRATEGIAS,
  DLG_PROYECTO_STATIC_OPTIMISMO,
  DLG_PROYECTO_STATIC_REPRESENTATIVIDAD,
  DLG_PROYECTO_STATIC_DESCRIPCION,
  DLG_PROYECTO_TEXT_DESCRIPCION,
  DLG_PROYECTO_TEXT_OPTIMISMO,
  DLG_PROYECTO_TEXT_REPRESENTATIVIDAD,
  DLG_PROYECTO_STATIC_CASOS
};

#endif
