/***************************************************************
 * Name:      FuzzynetApp.cpp
 * Purpose:   Code for Application Class
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

#include "FuzzynetApp.h"
#include "FuzzynetMain.h"

IMPLEMENT_APP(FuzzynetApp);

/**
 * Rutina principal
 */
bool FuzzynetApp::OnInit()
{

    MiFrame *frame = new MiFrame(APLICACION_NOMBRE,
                                 wxPoint(50, 50), wxSize(800, 400));

    MiCanvas *canvas = new MiCanvas(frame, frame->Ayuda);
    canvas->Proy=&frame->Proy;

    canvas->llenarRegiones();
    canvas->readConfigura();

    canvas->SetScrollbars(20, 20, 50, 50);
    frame->canvas = canvas;

    frame->Show(TRUE);

    return TRUE;
}

