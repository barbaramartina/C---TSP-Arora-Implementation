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

#include "Tiempos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm6::showDatos(long double per,long double quad,long double  port,long double prog,long double trim,float largo){
    this->Visible=true;
    Edit1->Text=(FloatToStr(per));
    Edit2->Text=(FloatToStr(quad));
    Edit3->Text=(FloatToStr(port));
    Edit4->Text=(FloatToStr(prog));
    Edit5->Text=(FloatToStr(trim));
    Edit6->Text=(FloatToStr(largo));
    Edit7->Text=(FloatToStr(per+quad+port+trim+prog));


};
//---------------------------------------------------------------------------

void __fastcall TForm6::FormClose(TObject *Sender, TCloseAction &Action)
{
   this->Visible=false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

