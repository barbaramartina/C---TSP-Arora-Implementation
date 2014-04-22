/*********************************************************************
*                        CUADRANTE
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
#ifndef CuadranteH
#define CuadranteH

#define LADOS 4
#define EERROR 5

#include <System.hpp>
#include <Values.h>


#include "L2.h"
#include "Matriz.h"
#include "Punto.h"
#include "PuntoExtendido.h"

class Cuadrante{

    private:

           bool tieneHijos;
           unsigned int level;
           unsigned int indice;
           unsigned int indiceReal;
           unsigned int X;
           unsigned int Y;
           unsigned int largo;
           union D{
                   unsigned int posPrimerHijo;
                   PuntoExtendido *nodoIn;
                      }Dato;
           Punto **portales;
           unsigned int cantPortales;


    public:

           Cuadrante();
           ~Cuadrante();
           void setTieneHijos(){tieneHijos=true;};
           void setLevel(unsigned int x){level=x;};
           void setIndice(unsigned int d){indice=d;};
           void setIndiceReal(unsigned int ir){indiceReal=ir;};
           void setposHijos(unsigned int p){Dato.posPrimerHijo=p;};
           void setNodoIn(PuntoExtendido *p){Dato.nodoIn=p;};
           void inicPortales(unsigned int);
           unsigned int getLevel(){return level;};
           unsigned int getIndice(){return indice;};
           unsigned int getIndiceReal(){return indiceReal;};
           unsigned int getposHijos(){return Dato.posPrimerHijo;};
           PuntoExtendido * getNodoIn();
           bool hijos(){return tieneHijos;};
           Punto  **getPortales(){return portales;};
           unsigned int getCantPortales(){return cantPortales;};
           bool operator ==(Cuadrante c){return this->indice==c.indice;};
           bool contienePortal(Punto *);
           void getApareo(unsigned int,Punto *&,Punto *&);
           unsigned int getNumApareo(Punto *,Punto *);
           unsigned int getX(){return X;};
           unsigned int getY(){return Y;};
           unsigned int getLargo(){return largo;};
           void setX(unsigned int x){X = x;};
           void setY(unsigned int y){Y = y;};
           void setLargo(unsigned int larg){largo = larg;};
           void setPortales(Lista2<Punto> *);
 
};

#endif
