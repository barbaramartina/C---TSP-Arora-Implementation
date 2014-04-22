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


#ifndef formImputH
#define formImputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>


#define HORIZONTAL 0
#define VERTICAL 1

#define XC 0
#define XF 80
#define YCCE 74
#define YFCE 111

#define MUSIC 0
#define ERROR 1
#define CLICK 2
#define ZOOMIN 3



#define POSZMASX 20
#define POSZMASY 0
#define ANCHOZMAS  30

#define POSZMENOSX 50
#define POSZMENOSY 0
#define ANCHOZMENOS  30

#define MINGRILLADO 2





#define COLORLINEA clBlack;

#include "FormPrueba.h"
#include "Punto.h"
#include "PuntoExtendido.h"
#include "Values.h"

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
   TImage *imageImput;
        TMainMenu *MainMenu1;
        TMenuItem *Zoom1;
        TMenuItem *ms1;
        TMenuItem *In1;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall In1Click(TObject *Sender);
        void __fastcall ms1Click(TObject *Sender);
 private:	// User declarations
      Graphics::TBitmap *nodo;
      int numEscala,posX,posY,posXIm,posYIm,primerIndiceX,primerIndiceY,maxDiferencia;
      void paintNodos();
      void paintPlano();
      int getNumNodoEnPos(float posX,float posY);
      PuntoExtendido **nodos;
      int numNodos,grillado;
public:		// User declarations
   __fastcall TForm3(TComponent* Owner);
    void setVisible();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
