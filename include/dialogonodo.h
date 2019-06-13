/***************************************************************************
                          dialogonodo.h  -  description
                             -------------------
    begin                : mar ago 5 2003
    copyright            : (C) 2003 by Oscar G. Duarte
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DIALOGONODO_H
#define DIALOGONODO_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include <wx/grid.h>
#include "dialogovariable.h"
#include "cadenas.h"
#include "proyecto.h"

/**
  *@author Oscar G. Duarte
  */

class DialogoNodo : public wxDialog  {
public: 
	DialogoNodo(NodoCalculo *nod, Proyecto *proy,wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoNodo();

  void llenarCuadro();

  void editarVariable(wxCommandEvent&);
  void editarHijo(wxCommandEvent&);
  void nuevoHijo(wxCommandEvent&);
  void borrarHijo(wxCommandEvent&);
  void editarParFijo(wxCommandEvent&);
  void cambiaCelda(wxGridEvent &ev);
//  void clickVariable();
//  void clickNodos();
  void cambiarFuncion(wxCommandEvent&);
  void cambiarFormaCalculo(wxCommandEvent&);
  void cambiaSpinH(wxSpinEvent&);
  void cambiaSpinV(wxSpinEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
    Proyecto *Proy;

    NodoCalculo *NodTemp;
    NodoCalculo *Nod;
//    NodoCalculo Nod;
    wxHtmlHelpController *Ayuda;
    
    wxButton *ButtonVariable;
    wxButton *ButtonEditarHijo;
    wxButton *ButtonNuevoHijo;
    wxButton *ButtonBorrarHijo;
    wxButton *ButtonOK;
//    wxButton *ButtonEditarParFijos;
//    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxStaticText *StaticNombre;
    wxStaticText *StaticPadres;
    wxStaticText *StaticHijos;
    wxStaticText *StaticParFijos;
    wxStaticText *StaticParVariables;
    wxStaticText *StaticFuncion;
    wxStaticText *StaticSpinH;
    wxStaticText *StaticSpinV;
    wxStaticText *StaticFormaCalculo;
    wxListBox *ListBoxPadres;
    wxListBox *ListBoxHijos;
    wxListBox *ListBoxParFijos;
    wxGrid *GrillaParVariables;
    wxChoice *ChoiceFormaCalculo;
    wxChoice *ChoiceFuncion;
//    wxCheckBox *CheckBoxFormaVariable;
//    wxCheckBox *CheckBoxFormaNodos;
    wxSpinCtrl *SpinOffsetHorizontal;
    wxSpinCtrl *SpinOffsetVertical;
    wxStaticText *StaticDescripcion;
    wxTextCtrl *TextDescripcion;
    wxStaticText *StaticExtendido;
    wxTextCtrl *TextExtendido;

    
    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_NODO_BTN_EDITAR_VARIABLE = 1,
  DLG_NODO_BTN_EDITAR_HIJO,
  DLG_NODO_BTN_NUEVO_HIJO,
  DLG_NODO_BTN_BORRAR_HIJO,
  DLG_NODO_BTN_OK,
  DLG_NODO_BTN_CANCEL,
  DLG_NODO_BTN_AYUDA,
//  DLG_NODO_BTN_EDITAR_PARFIJOS,
  DLG_NODO_STATIC_NOMBRE,
  DLG_NODO_STATIC_PADRES,
  DLG_NODO_STATIC_HIJOS,
  DLG_NODO_STATIC_PARFIJOS,
  DLG_NODO_STATIC_PARVARIABLES,
  DLG_NODO_STATIC_FUNCION,
  DLG_NODO_STATIC_SPINH,
  DLG_NODO_STATIC_SPINV,
  DLG_NODO_STATIC_DESCRIPCION,
  DLG_NODO_STATIC_EXTENDIDO,
  DLG_NODO_STATIC_FORMACALCULO,
  DLG_NODO_TEXT_DESCRIPCION,
  DLG_NODO_TEXT_EXTENDIDO,
  DLG_NODO_LISTBOX_PADRES,
  DLG_NODO_LISTBOX_HIJOS,
  DLG_NODO_LISTBOX_PARFIJOS,
  DLG_NODO_GRID_GRILLAPARVARIABLES,
  DLG_NODO_CHOICE_FUNCION,
  DLG_NODO_CHOICE_FORMACALCULO,
//  DLG_NODO_COMBOBOX_FORMADECALCULO,
//  DLG_NODO_CHECKBOX_FORMAVARIABLE,
//  DLG_NODO_CHECKBOX_FORMANODOS,
  DLG_NODO_SPIN_HORIZONTAL,
  DLG_NODO_SPIN_VERTICAL
};
     
#endif
