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

#include "Error.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
   : TForm(Owner)
{
   numError=0;
   errorFormato=new Graphics::TBitmap;
   errorNoProceso=new Graphics::TBitmap;
   errorAbrir=new Graphics::TBitmap;
   errorGral=new Graphics::TBitmap;

   errorFormato->LoadFromFile("Imagenes\\errorFormato.bmp");
   errorNoProceso->LoadFromFile("Imagenes\\errorNoProceso.bmp");
   errorAbrir->LoadFromFile("Imagenes\\errorAbrir.bmp");
   errorGral->LoadFromFile("Imagenes\\errorGral.bmp");

}
//---------------------------------------------------------------------------
void TForm5::setVisible(){
   this->Visible=true;
   showError();
};
//---------------------------------------------------------------------------
void __fastcall TForm5::FormClose(TObject *Sender, TCloseAction &Action)
{
   this->Visible=false;

}
//---------------------------------------------------------------------------
void TForm5::setError(int n){
  numError=n;
};
//---------------------------------------------------------------------------
void TForm5::showError(){
 switch (numError)
 {
   case 1:Image1->Canvas->Draw(0,0,errorFormato);
   break;
   case 2:Image1->Canvas->Draw(0,0,errorNoProceso);
   break;
   case 3:Image1->Canvas->Draw(0,0,errorAbrir);
   break;
   case 4:Image1->Canvas->Draw(0,0,errorGral);
   break;
 };

};
//---------------------------------------------------------------------------

