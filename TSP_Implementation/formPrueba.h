//---------------------------------------------------------------------------
//
//  Licensed to the Apache Software Foundation (ASF) under one
//  or more contributor license agreements.  See the NOTICE file
//  distributed with this work for additional information
//  regarding copyright ownership.  The ASF licenses this file
//  to you under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
//  with the License.  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,
//  software distributed under the License is distributed on an
//  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//  KIND, either express or implied.  See the License for the
//  specific language governing permissions and limitations
//  under the License.
//


#ifndef formPruebaH
#define formPruebaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <NMTime.hpp>
#include <Psock.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <System.hpp>
#include <Menus.hpp>


#define posXC 0
#define posXF 80
#define posYCA 0
#define posYFA 37
#define posYCG 38
#define posYFG 74
#define posYCT 75
#define posYFT 111
#define posYCI 112
#define posYFI 148
#define posYCQ 149
#define posYFQ 185
#define posYCP 186
#define posYFP 222
#define posYCC 223
#define posYFC 260

#define HORIZONTAL 0
#define VERTICAL 1

#define MUSIC 0
#define ERROR 1
#define CLICK 2
#define ZOOMIN 3



#define MAXANCHOIM 4000

#define GRILLADODEF 5
#define MINGRILLADO  1

#include <OleServer.hpp>
#include <ComCtrls.hpp>

#include "Error.h"
#include "formImput.h"
#include "Punto.h"
#include "PuntoExtendido.h"
#include "Perturbacion.h"
#include "Portalizacion.h"
#include "ProgramacionDinamica.h"
#include "SubSolucion.h"
#include "Matriz.h"
#include "Trimer.h"
#include "MatrizVariable.h"
#include "QuadTreeTSP.h"
#include "Tiempos.h"

#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
   TImage *plano;
   TOpenDialog *open;
   TSaveDialog *save;
   TMainMenu *MainMenu1;
   TMenuItem *it_openInstance;
   TMenuItem *mn_resolve;
   TMenuItem *Abrir2;
   TMenuItem *it_closeInstance;
   TMenuItem *mn_times;
   TMenuItem *mn_zoom;
        TScrollBox *ScrollBox1;
        TMenuItem *menos;
   void __fastcall openClose(TObject *Sender);
   void __fastcall saveClose(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall Abrir2Click(TObject *Sender);
   void __fastcall mn_resolveClick(TObject *Sender);
   void __fastcall mn_inputClick(TObject *Sender);
   void __fastcall mn_quadClick(TObject *Sender);
   void __fastcall mn_portalsClick(TObject *Sender);
   void __fastcall it_closeInstanceClick(TObject *Sender);
   void __fastcall mn_timesClick(TObject *Sender);
   void __fastcall it_zoomInClick(TObject *Sender);
   void __fastcall it_zoomOutClick(TObject *Sender);
     




private:	// User declarations
   Graphics::TBitmap *nodoO;
   Graphics::TBitmap *nodoM;
   Graphics::TBitmap *portal;
   int posXIm,posYIm,grillado,numNodos;
   AnsiString archivoOpen,archivoOut;
   bool checkExtension();
   void dibujarQuad();
   void dibujarPlano();
   void dibujarPortales();
   void dibujarNodos();
   void execute();
   int getNumNodoEnPos(int posX,int posY);
   unsigned int  setGrillado();
   LARGE_INTEGER frecuencia;
   Perturbacion *p;
   QuadTreeTSP *q;
   ProgramacionDinamica *progD;
   Portalizacion *port;
   Trimer *t;
   Punto *nodos;
   bool ejecutado,abierto,mostrado,portDibujados;
   long double  tiempoPert,tiempoQ,tiempoPort,tiempoProg,tiempoTrim;
   float c,largo;

public:		// User declarations
   __fastcall TForm2(TComponent* Owner);
   Graphics::TBitmap *getNodoO(){return nodoO;};
   Graphics::TBitmap *getNodoM(){return nodoM;};
   void setVisible();
  
   PuntoExtendido **getNodos();
   int getNumNodos();
   void setGrillado(int g){grillado=g;};
   void setC(int ca){c=ca;};

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
