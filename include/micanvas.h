/***************************************************************************
                          micanvas.h  -  description
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

#ifndef MICANVAS_H
#define MICANVAS_H


enum{
      VER_RED =1,
      VER_CASO_RED,
      VER_CASO_LISTA,
      VER_CASO_VARIABLES,
      VER_CASO_VARIABLES_TODAS,
      VER_MATRIZ
};

#include "dialogovariable.h"
#include "dialogonumeromostrar.h"
#include "dialogonodo.h"
#include "dialogocolores.h"
#include "region.h"
#include "listacolores.h"
#include "listafuentes.h"
#include "listadimensiones.h"
#include "listaselecciones.h"
#include<wx/wx.h>
#include<wx/grid.h>
#include<wx/config.h>
#include<wx/font.h>
#include<wx/html/helpctrl.h>
#include<wx/colourdata.h>
#include <wx/fileconf.h>
#include <wx/wfstream.h>

/**
  *@author Oscar Germán Duarte Velasco
  */

WX_DECLARE_OBJARRAY(Region, ArregloRegiones);

/**
 * Esta clase encapsula el comportamiento de la pantalla principal
 */

class MiCanvas : public wxScrolledWindow  {
public:
    MiCanvas(wxWindow *frame, wxHtmlHelpController *ayuda);
    ~MiCanvas();
    void defecto();
    void definirColores();
    void definirFuentes();
    void definirDimensiones();
    void definirSelecciones();
    void OnPaint(wxPaintEvent&);
    void OnRightUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
//    void OnCellLeftClick( wxGridEvent& ev );
    void clickCelda(wxGridEvent &ev);
    void clickCeldaLista(wxGridEvent &ev);
    void clickCeldaPropiedades(wxGridEvent &ev);
    void clickCeldaVariables(wxGridEvent &ev);
    void clickCeldaMatriz(wxGridEvent &ev);
    void llenarRegiones();
    void llenarRegionesRed();

    void llenarRegionesCasoRed();
    void llenarRegionesCasoLista();
    void llenarRegionesCasoVariables();
    void llenarRegionesCasoVariablesTodas();
    void llenarRegionesMatriz();

    void llenarListaColores(ListaColores *Col);

    void pintar(wxPaintDC &dc);
    void pintarRed(wxPaintDC &dc);
    void pintarCasoRed(wxPaintDC &dc);
    void pintarCasoLista(wxPaintDC &dc);
    void pintarCasoVariables(wxPaintDC &dc);
    void pintarCasoVariablesTodas(wxPaintDC &dc);
    void pintarMatriz(wxPaintDC &dc);
    void pintarCasoLista2(wxPaintDC &dc);
    void pintarCasoVariables2(wxPaintDC &dc);
    void pintarCasoVariablesTodas2(wxPaintDC &dc);
    void pintarMatriz2(wxPaintDC &dc);

    void llenarGrillaCasoLista2();
    void llenarGrillaCasoVariables2();
    void llenarGrillaCasoMatriz2();

    void intercambiar(int *x1, int *x2);

    void writeConfigura();
    void readConfigura();
// para mover nodos...
  NodoCalculo *nodoMovil;
  int posXNodoMovil;
  int posYNodoMovil;
  bool nodoEnMovimiento;

/**
 * Archivo de configuración
 */
    wxConfig *Configura;
/**
 * Manejador del sistema de ayuda
 */
    wxHtmlHelpController *Ayuda;

/**
 * Apuntador al proyecto que se visualiza
 */
  Proyecto *Proy;
/**

 * Listado de regiones que se despliegan
 * @see Region
 */
  ArregloRegiones Regiones;
/**
 * Tipo de vistas disponibles:
 * 1: Muestra la Estrategia como una Red
 * 2: Muestra el Caso como una Red
 * 3: Muestra el Caso como un listado de datos
 * 4: Muestra la matriz de Casos
 */
  int Ver;
/**
 * Tipo de información de la variable:
 * 1: Muestra la interpretación Lingüística
 * 2: Muestra el valor Representativo
 * 3: Muestra el valor Representativo y la Ambiguedad
 */
  int VerVariable;
/**
 * Tamaño horizontal de la pantalla
 */
  int HSize;
/**
 * Tamaño horizontal de la pantalla
 */
  int VSize;
///**
// * Dibujo de un nodo en el árbol: 0=rectángulo    1=elipse
// */
//  int FiguraArbol;
/**
 * Tipo de Vista de la Matriz: 0=valor 1=ambiguedad 2=interp max 3= interpreta
 */
  int VistaMatriz;
///**
// * bandera para utilizar o No Niveles: 0: no utilizar 1: utilizar
// */
//  int VerNiveles;
/**
 * Listado con los colores empleados

 */
  ListaColores Colores;
/**
 * Listado con los fuentes empleados
 */
  ListaFuentes Fuentes;
/**
 * Listado con las dimensiones empleadas
 */
  ListaDimensiones Dimensiones;
/**
 * Listado con las selecciones empleadas
 */
  ListaSelecciones Selecciones;
/**
 * Colores usuales
 */
  wxColourData data;
/**
 * Grilla para matrices
 */
  wxGrid *GrillaLista,*GrillaPropiedades,*GrillaVariables,*GrillaMatriz;
/**
 * Bandera para no repintar la grilla
 */
  int FlagPintarLista,FlagPintarVariables,FlagPintarMatriz;
/**
 * Dialogo de Colores de Pantalla
 */
  DialogoColores *DialColores;
  bool NoPintar;
  int Nuevo;
DECLARE_EVENT_TABLE()
};

enum
{
  MICANVAS_GRILLA_LISTA = 1,
  MICANVAS_GRILLA_PROPIEDADES,
  MICANVAS_GRILLA_VARIABLES,
  MICANVAS_GRILLA_MATRIZ
};

#endif
