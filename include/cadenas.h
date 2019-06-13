/***************************************************************************
                          cadenas.h  -  description
                             -------------------
    begin                : abr 30 2003
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

#ifndef CADENAS_H
#define CADENAS_H

//Fuzzynet
#define ESPECIFICO 0
#define APLICACION_NOMBRE       wxT("Fuzzynet - Redes de Sistemas difusos")

//Vertederos Diputación
//#define ESPECIFICO 1
//#define APLICACION_NOMBRE       wxT("EDIAV - Evaluación Difusa del Impacto Ambiental en Vertederos")

//Vertederos Montserrat
//#define ESPECIFICO 5
//#define APLICACION_NOMBRE       wxT("EVIAVE - Evaluación Inteligente del Impacto Ambiental en Vertederos")

class cadenas{public: cadenas(){}};

#define GENERAL_ADVERTENCIA     wxT("Atención")


#define FRAME_MENU_ARCHIVO                 wxT("Archivo")
#define FRAME_MENU_ARCHIVO_NUEVO           wxT("Nuevo Proyecto")
#define FRAME_MENU_ARCHIVO_LEER            wxT("Leer Proyecto")
#define FRAME_MENU_ARCHIVO_GUARDAR         wxT("Guardar Proyecto")
#define FRAME_MENU_ARCHIVO_GUARDARCOMO     wxT("Guardar Proyecto Como...")
#define FRAME_MENU_ARCHIVO_IMPORTAR        wxT("Importar")
#define FRAME_MENU_ARCHIVO_EXPORTAR        wxT("Exportar")
#define FRAME_MENU_ARCHIVO_SALIR           wxT("Salir")

#define FRAME_MENU_PROYECTO                 wxT("Proyecto")
#define FRAME_MENU_PROYECTO_PROYECTO         wxT("Proyecto")
#define FRAME_MENU_PROYECTO_ESTRATEGIA       wxT("Metodología")
#define FRAME_MENU_PROYECTO_CASO             wxT("Caso")
#define FRAME_MENU_PROYECTO_CONFIGURACION    wxT("Opciones de Configuración")

#define FRAME_MENU_HLP_PROYECTO_PROYECTO         wxT("Editar Proyecto")
#define FRAME_MENU_HLP_PROYECTO_ESTRATEGIA       wxT("Editar Metodología Seleccionada")
#define FRAME_MENU_HLP_PROYECTO_CASO             wxT("Editar Caso Seleccionado")
#define FRAME_MENU_HLP_PROYECTO_CONFIGURACION    wxT("Opciones de Configuración del Programa")

#define FRAME_MENU_HLP_ARCHIVO_NUEVO           wxT("Crear un proyecto nuevo")
#define FRAME_MENU_HLP_ARCHIVO_LEER            wxT("Leer Proyecto de disco")
#define FRAME_MENU_HLP_ARCHIVO_GUARDAR         wxT("Guardar Proyecto en disco")
#define FRAME_MENU_HLP_ARCHIVO_GUARDARCOMO     wxT("Guardar Proyecto en disco con otro nombre")
#define FRAME_MENU_HLP_ARCHIVO_IMPORTAR        wxT("Importar Archivo de Texto")
#define FRAME_MENU_HLP_ARCHIVO_EXPORTAR        wxT("Exportar Archivo de Texto")
#define FRAME_MENU_HLP_ARCHIVO_SALIR           wxT("Salir del Programa")

#define FRAME_MENU_VER                      wxT("Ver")
#define FRAME_MENU_VER_RED              wxT("Red")
#define FRAME_MENU_VER_CASORED_PALABRAS wxT("Caso como Red - Palabras")
#define FRAME_MENU_VER_CASORED_VALOR    wxT("Caso como Red - Valor")
#define FRAME_MENU_VER_CASORED_AMBIGUEDAD wxT("Caso como Red - Ambigüedad")
#define FRAME_MENU_VER_CASOLISTA        wxT("Caso como Lista")
#define FRAME_MENU_VER_CASOVARIABLES        wxT("Variables del Caso en la Metodología")
#define FRAME_MENU_VER_CASOVARIABLESTODAS        wxT("Todas las Variables del caso")
#define FRAME_MENU_VER_MATRIZ_VALOR           wxT("Matriz de Casos - Valores")
#define FRAME_MENU_VER_MATRIZ_AMBIGUEDAD           wxT("Matriz de Casos - Ambigüedades")
#define FRAME_MENU_VER_MATRIZ_INTERPRETACION           wxT("Matriz de Casos - Interpretaciones")
#define FRAME_MENU_VER_MATRIZ_INTERPRETACIONLARGA           wxT("Matriz de Casos - Interpretaciones Largas")

#define FRAME_MENU_HLP_VER_RED          wxT("Ver la red seleccionada")
#define FRAME_MENU_HLP_VER_CASORED_PALABRAS   wxT("Ver el caso seleccionado como una red. Muestra Palabras")
#define FRAME_MENU_HLP_VER_CASORED_VALOR      wxT("Ver el caso seleccionado como una red. Muestra el Valor Representativo")
#define FRAME_MENU_HLP_VER_CASORED_AMBIGUEDAD wxT("Ver el caso seleccionado como una red. Muestra la Ambigüedad")
#define FRAME_MENU_HLP_VER_CASOLISTA    wxT("Ver el caso seleccionado como una lista")
#define FRAME_MENU_HLP_VER_CASOVARIABLES    wxT("Ver las variables del caso seleccionado relativas a la Metodología")
#define FRAME_MENU_HLP_VER_CASOVARIABLESTODAS    wxT("Ver todas la variables del caso seleccionado")
#define FRAME_MENU_HLP_VER_MATRIZ_VALOR       wxT("Ver  valores en la matriz de casos para la red seleccionada")
#define FRAME_MENU_HLP_VER_MATRIZ_AMBIGUEDAD       wxT("Ver ambigüedades en la matriz de casos para la red seleccionada")
#define FRAME_MENU_HLP_VER_MATRIZ_INTERPRETACION       wxT("Ver interpretaciones lingüísticas en la matriz de casos para la red seleccionada")
#define FRAME_MENU_HLP_VER_MATRIZ_INTERPRETACIONLARGA       wxT("Ver interpretaciones lingüísticas largas en la matriz de casos para la red seleccionada")

#define FRAME_MENU_REPORTES                 wxT("Reportes")
#define FRAME_MENU_REPORTES_PROYECTO        wxT("Proyecto")
#define FRAME_MENU_REPORTES_ESTRATEGIA             wxT("Metodología")
#define FRAME_MENU_REPORTES_CASO            wxT("Caso")
#define FRAME_MENU_REPORTES_RESULTADOS            wxT("Resultados")
#define FRAME_MENU_REPORTES_CONFIGURACION   wxT("Configuración")

#define FRAME_MENU_HLP_REPORTES_PROYECTO        wxT("Crear Reporte del Proyecto")
#define FRAME_MENU_HLP_REPORTES_ESTRATEGIA             wxT("Crear Reporte de la Metodología Seleccionada")
#define FRAME_MENU_HLP_REPORTES_CASO            wxT("Crear Reporte del Caso Seleccionado")
#define FRAME_MENU_HLP_REPORTES_RESULTADOS            wxT("Crear Reporte de los Resultados del Proyecto")
#define FRAME_MENU_HLP_REPORTES_CONFIGURACION   wxT("Configurar generación de reportes")

#define FRAME_MENU_LIBRERIAS                wxT("Librerías")
#define FRAME_MENU_LIBRERIAS_PROYECTOS      wxT("Proyectos")
#define FRAME_MENU_LIBRERIAS_ESTRATEGIAS          wxT("Metodologías")
#define FRAME_MENU_LIBRERIAS_CASOS          wxT("Casos")

#define FRAME_MENU_HLP_LIBRERIAS_PROYECTOS      wxT("Administrar Librerías de Proyectos")
#define FRAME_MENU_HLP_LIBRERIAS_ESTRATEGIAS          wxT("Administrar Librerías de Metodologías")
#define FRAME_MENU_HLP_LIBRERIAS_CASOS          wxT("Administrar Librerías de Casos")

#define FRAME_MENU_AYUDA                    wxT("Ayuda")
#define FRAME_MENU_AYUDA_ABCW               wxT("Sistemas de Computación con Palabras")
#define FRAME_MENU_AYUDA_REDES              wxT("Redes de Palabras")
#define FRAME_MENU_AYUDA_MANUAL             wxT("Manual del Usuario")
#define FRAME_MENU_AYUDA_ACERCA             wxT("Acerca de...")

#define FRAME_MENU_HLP_AYUDA_ABCW               wxT("Ayuda sobre Sistemas de Computación con Palabras")
#define FRAME_MENU_HLP_AYUDA_REDES              wxT("Ayuda sobre Redes de Palabras")
#define FRAME_MENU_HLP_AYUDA_MANUAL             wxT("Manual del usuario del programa")
#define FRAME_MENU_HLP_AYUDA_ACERCA             wxT("Acerca de...")

#define FRAME_STATUSBAR_VACIO       wxT("Proyecto Vacío")

#define FRAME_PROYECTO_LEER_CAPTION         wxT("Seleccione un archivo de Proyecto")

#define FRAME_NOIMPLEMENTADA    wxT("Opción No Implementada")

#define CANVAS_NODO                wxT("NODO")
#define CANVAS_VALOR                wxT("VALOR")
#define CANVAS_AMBIGUEDAD            wxT("AMBIGÜEDAD")
#define CANVAS_INTMAXIMA            wxT("INTERPRETACIÓN")
#define CANVAS_INTERPRETA            wxT("INTERPRETACIÓN LARGA")
#define CANVAS_PROPIEDAD            wxT("PROPIEDAD")
#define CANVAS_PROPVALOR            wxT("VALOR")
#define CANVAS_VARIABLE            wxT("VARIABLE")
#define CANVAS_VARVALOR            wxT("VALOR")


#endif
