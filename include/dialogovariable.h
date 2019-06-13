/***************************************************************************
                          dialogovariable.h  -  description
                             -------------------
    begin                : mar jul 22 2003
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

#ifndef DIALOGOVARIABLE_H
#define DIALOGOVARIABLE_H

#include <wx/html/helpctrl.h>
#include "dialogoautodefinirvariable.h"
#include "dialogomodificador.h"
#include "dialogolibreria.h"

/**
  *@author 
  */

class DialogoVariable : public wxDialog  {
public:
	DialogoVariable(VariableLinguistica *var, Proyecto *proy,
                 wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoVariable();

  void OnPaint(wxPaintEvent&);
  void pintar(wxPaintDC &dc);
  void llenarCuadro();
  void leerTextos();

  void editarEtiqueta(wxCommandEvent&);
  void nuevaEtiqueta(wxCommandEvent&);
  void borrarEtiqueta(wxCommandEvent&);
  void autodefinir(wxCommandEvent&);
  void editarValor(wxCommandEvent&);
  void seleccionarEtiqueta(wxCommandEvent&);
  void verValor(wxCommandEvent&);
  void seleccionarTipoDeValor(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  void librerias(wxCommandEvent&);

private:
    Proyecto *Proy;
  
    VariableLinguistica *VarTemp;
    VariableLinguistica Var;
    wxHtmlHelpController *Ayuda;
    
    wxButton *ButtonEditarEtiqueta;
    wxButton *ButtonNuevaEtiqueta;
    wxButton *ButtonBorrarEtiqueta;
    wxButton *ButtonAutodefinir;
    wxButton *ButtonEditarValor;
    wxButton *ButtonOK;
    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxButton *ButtonLibrerias;
    wxStaticText *StaticNombre;
    wxStaticText *StaticMinimo;
    wxStaticText *StaticMaximo;
    wxStaticText *StaticUnidades;
    wxStaticText *StaticEtiquetas;
    wxCheckBox *CheckValor;
    wxStaticText *StaticValorCalculado;
    wxStaticText *StaticDescripcion;
    wxTextCtrl *TextDescripcion;
    wxTextCtrl *TextNombre;
    wxTextCtrl *TextMinimo;
    wxTextCtrl *TextMaximo;
    wxTextCtrl *TextUnidades;
    wxListBox *ListBoxEtiquetas;
    wxChoice *ChoiceTipoDeValor;

    wxSizer* SizerDibujo;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_VARIABLE_BTN_EDITAR_ETIQUETA = 1,
  DLG_VARIABLE_BTN_NUEVA_ETIQUETA,
  DLG_VARIABLE_BTN_BORRAR_ETIQUETA,
  DLG_VARIABLE_BTN_AUTODEFINIR,
  DLG_VARIABLE_BTN_EDITAR_VALOR,
  DLG_VARIABLE_BTN_OK,
  DLG_VARIABLE_BTN_CANCEL,
  DLG_VARIABLE_BTN_AYUDA,
  DLG_VARIABLE_BTN_LIBRERIAS,
  DLG_VARIABLE_STATIC_NOMBRE,
  DLG_VARIABLE_STATIC_MINIMO,
  DLG_VARIABLE_STATIC_MAXIMO,
  DLG_VARIABLE_STATIC_UNIDADES,
  DLG_VARIABLE_STATIC_ETIQUETAS,
  DLG_VARIABLE_CHECKBOX_VALOR,
  DLG_VARIABLE_STATIC_VALORCALCULADO,
  DLG_VARIABLE_STATIC_INTERPRETACION,
  DLG_VARIABLE_STATIC_INTERPRETACIONLARGA,
  DLG_VARIABLE_STATIC_DESCRIPCION,
  DLG_VARIABLE_TEXT_DESCRIPCION,
  DLG_VARIABLE_TEXT_NOMBRE,
  DLG_VARIABLE_TEXT_MINIMO,
  DLG_VARIABLE_TEXT_MAXIMO,
  DLG_VARIABLE_TEXT_UNIDADES,
  DLG_VARIABLE_LISTBOX_ETIQUETAS,
  DLG_VARIABLE_CHOICE_TIPODEVALOR
};                

#endif
