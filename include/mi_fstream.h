/***************************************************************************
                           mi_fstream.h  -  description
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

#ifndef _MI_FSTREAM_H
#define _MI_FSTREAM_H


#include "cadenas.h"
#include <wx/wx.h>
#include  <wx/textfile.h>

/**
 * Implementa la clase para escribir en archivos de texto.
 *
 * Mediante el operador << se pueden salvar: int, float, wxString y char*
 */
class Mi_ofpstream
{
public:
  Mi_ofpstream(wxString cad);
	~Mi_ofpstream()
  {
    outputFile->Write();
    delete outputFile;
  }
	void close()
  {
    outputFile->Write();
  }
	void operator << (const int& D)  {cad=wxT(""); cad << D;outputFile->AddLine(cad);}
	void operator << (const float& D){cad=wxT(""); cad << D;outputFile->AddLine(cad);}
	void operator << (const wxString& D);

	wxTextFile *outputFile;
  wxString cad;
protected:
  int TipoPropio;
};


/**
 * Implementa la clase para leer de archivos de texto.
 *
 * Mediante el operador >> se pueden salvar: int, float, wxString
 */
class Mi_ifpstream
{
public:
	Mi_ifpstream(wxString Cad);
	~Mi_ifpstream()
  {
    inputFile->Close();
    delete inputFile;
 }
	void close()
  {
    inputFile->Close();
  }
	void operator >> (int& D);
	void operator >> (float& D);
	void operator >> (wxString& D);

	wxTextFile *inputFile;
	wxString cad;
  wxChar decimalArchivo;
  wxChar decimalPropio;
protected:
};

#endif
