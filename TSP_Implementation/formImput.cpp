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


#include <vcl.h>
#pragma hdrstop

#include "formImput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
   : TForm(Owner)
{
     this->Visible=false;

    grillado=GRILLADODEF;
    numEscala=maxDiferencia=1;
    posX=posY=primerIndiceX=primerIndiceY=0;
    nodo=new Graphics::TBitmap;
    nodo->LoadFromFile("Imagenes\\nodoO.bmp");
    nodo->Transparent=true;
    nodo->TransparentColor=nodo->Canvas->Pixels[0][0];



}

//---------------------------------------------------------------------------
void TForm3::setVisible(){
        this->Visible=true;
        nodos=Form2->getNodos();
        numNodos=Form2->getNumNodos();
        paintPlano();
        paintNodos();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
   this->Visible=false;
}
//---------------------------------------------------------------------------
void TForm3::paintNodos(){
   for (int i=0; i<numNodos; i++)
        imageImput->Canvas->Draw((int)(((nodos[i]->getY()-(float)primerIndiceY)/(float)numEscala)*(float)grillado),(int)(((nodos[i]->getX()-(float)primerIndiceX)/(float)numEscala)*(float)grillado),nodo);
}
//---------------------------------------------------------------------------
void TForm3::paintPlano(){

  //cubro de blanco el plano
  imageImput->Canvas->Rectangle(0,0,1999,1999);

  //dibujo las lineas del borde
  imageImput->Canvas->Pen->Color=clBlack;
  imageImput->Canvas->Pen->Width=1;

  for (unsigned int i=0; i*grillado<=MAXANCHOIM  ; i++){
     imageImput->Canvas->Rectangle(i*grillado,0,(i*grillado)+1,MAXANCHOIM );
     imageImput->Canvas->Rectangle(0,i*grillado,MAXANCHOIM ,(i*grillado)+1);
  }

};
//---------------------------------------------------------------------------
void __fastcall TForm3::In1Click(TObject *Sender)
{
  if (this->grillado>=2){
        this->grillado /= 2;
        this->paintPlano();
        this->paintNodos();
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ms1Click(TObject *Sender)
{
        this->grillado *= 2;
        this->paintPlano();
        this->paintNodos();
        
}
//---------------------------------------------------------------------------

