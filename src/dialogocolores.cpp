/***************************************************************************
                          dialogocolores.cpp  -  description
                             -------------------
    begin                : jue abr 1 2004
    copyright            : (C) 2004 by Oscar G. Duarte
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

#include "dialogocolores.h"

BEGIN_EVENT_TABLE(DialogoColores, wxDialog)
    EVT_PAINT(DialogoColores::OnPaint)
END_EVENT_TABLE()

DialogoColores::DialogoColores(ListaColores col,
          wxWindow *parent,const wxString& title)
          :wxDialog(parent,-1,title)
{
  Colores=col;
}

DialogoColores::~DialogoColores()
{
}

void DialogoColores::OnPaint(wxPaintEvent&)
{
  wxPaintDC dc(this);
  wxBrush Brush;
  
  int AlturaCaja=20,Offset=20,AnchoCaja=40;
  int h,v,HT,VT;
  int i,tam;
  tam=Colores.Colores.GetCount();
  VT=(tam+1)*AlturaCaja+2*Offset;
  HT=0;
  for(i=0;i<tam;i++)
  {
    dc.GetTextExtent(Colores.Nombres.Item(i),&h,&v);
    if(HT<h){HT=h;}
  }
  HT=HT+3*Offset+AnchoCaja;
  SetSize(HT,VT);
  
  for(i=0;i<tam;i++)
  {
    Brush.SetColour(Colores.Colores.Item(i));
    dc.SetBrush (Brush);
    dc.DrawRectangle(Offset,Offset+i*AlturaCaja,AnchoCaja,AlturaCaja);
    dc.GetTextExtent(Colores.Nombres.Item(i),&h,&v);
    dc.DrawText(Colores.Nombres.Item(i),AnchoCaja+2*Offset,Offset+i*AlturaCaja+2);
  }
}