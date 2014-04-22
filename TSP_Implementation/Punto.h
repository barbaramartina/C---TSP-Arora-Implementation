/*********************************************************************
*                        PUNTO
*                    Barbara M. Rodeker
*                    TSP
*                    Arora`s implementation
*
**********************************************************************/
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


#ifndef PuntoH
#define PuntoH

#define ValueDef -1.0;

#include <Math.hpp>
#include <System.hpp>
#include <stdio.h>
 
class Punto{

     protected:

             float x;
             float y;
             
     public:

             Punto(float,float);
             Punto();
             ~Punto();
             void setX(float);
             void setY(float);
             float getX();
             float getY();
             float distancia_Total_a(Punto *);
             float distancia_X_a(Punto *);
             float distancia_Y_a(Punto *);
             AnsiString toString();
             bool operator ==(Punto p){ return   ((this->y==p.y) && (this->x==p.x)); }
             bool operator <(Punto *p){ return (this->y<p->y); }

};

#endif
