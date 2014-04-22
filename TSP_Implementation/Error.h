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

#ifndef ErrorH
#define ErrorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "formPrueba.h"

//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
   TImage *Image1;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
     Graphics::TBitmap *errorFormato;
     Graphics::TBitmap *errorNoProceso;
     Graphics::TBitmap *errorAbrir;
     Graphics::TBitmap *errorGral;
     int numError;
     void showError();


public:		// User declarations
   __fastcall TForm5(TComponent* Owner);
   void setVisible();
   void setError(int n);
  

};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
