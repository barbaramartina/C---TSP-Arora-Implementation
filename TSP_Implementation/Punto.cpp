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

#pragma hdrstop

#include "Punto.h"

Punto::Punto(float xx,float yy){
   x=xx;
   y=yy;
}
//---------------------------------------------------------------------------
Punto::Punto(){
   x=ValueDef;
   y=ValueDef;
}
//---------------------------------------------------------------------------
Punto::~Punto(){}
//---------------------------------------------------------------------------
void Punto::setX(float xx){ x=xx;}
//---------------------------------------------------------------------------
void Punto::setY(float yy){y=yy;}
//---------------------------------------------------------------------------
float Punto::getX(){return x;}
//---------------------------------------------------------------------------
float Punto::getY(){return y;}
//---------------------------------------------------------------------------
float Punto::distancia_Total_a(Punto *p){
    return Power(((this->x-p->x)*(this->x-p->x))+((this->y-p->y)*(this->y-p->y)),.5);
}
//---------------------------------------------------------------------------
float Punto::distancia_X_a(Punto *p){
  if (this->x>p->x)
     return this->x-p->x;
  else
     return p->x-this->x;
}
//---------------------------------------------------------------------------
float Punto::distancia_Y_a(Punto *p){
  if (this->y>p->y)
     return this->y-p->y;
  else
     return p->y-this->y;
}
//---------------------------------------------------------------------------
AnsiString Punto::toString(){
       return "( "+FormatFloat("#,##0.00",x)+" , "+FormatFloat("#,##0.00",y)+" )";
}

#pragma package(smart_init)
