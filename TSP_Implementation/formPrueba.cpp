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

#include "formPrueba.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
   : TForm(Owner)
{

    //inicializacion de Datos
    archivoOpen="NULL";
    archivoOut="NULL";

    //inicializando variables de posicionamiento
    posXIm=84;
    posYIm=0;

    grillado=GRILLADODEF;

    //inicializando a nulos todos los pasos del algortimo
    p = NULL;
    q = NULL;
    progD = NULL;
    port = NULL;
    t = NULL;

    //inicializando variables de control
    ejecutado=abierto=mostrado=portDibujados=false;

    //inicializando los timepos de ejecución
    tiempoPert=tiempoQ=tiempoPort=tiempoProg=tiempoTrim=largo=0;

    //inicializacion de imagenes
    nodoO=new Graphics::TBitmap;
    nodoM=new Graphics::TBitmap;
    portal=new Graphics::TBitmap;

    nodoO->LoadFromFile("Imagenes\\nodoO.bmp");
    nodoM->LoadFromFile("Imagenes\\nodoM.bmp");
    portal->LoadFromFile("Imagenes\\portal.bmp");
    nodoO->Transparent=true;
    nodoM->TransparentColor=nodoM->Canvas->Pixels[0][0];
    nodoM->Transparent=true;
    nodoO->TransparentColor=nodoM->Canvas->Pixels[0][0];
    portal->Transparent=true;
    portal->TransparentColor=portal->Canvas->Pixels[0][0];

    this->dibujarPlano();

}
//---------------------------------------------------------------------------
void TForm2::setVisible(){
  this->Visible=true;
  this->grillado=GRILLADODEF;
  dibujarPlano();

};
//---------------------------------------------------------------------------
bool TForm2::checkExtension(){
   int length=archivoOpen.Length();
   AnsiString aux=archivoOpen.SubString(length-3,length);
   if (aux!=".tsp"){
      Form5->setError(1);
      Form5->setVisible();
      return false;
   }
  return  true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::openClose(TObject *Sender)
{
       open->FileName="NULL";
       
}
//---------------------------------------------------------------------------
void __fastcall TForm2::saveClose(TObject *Sender)
{
       save->FileName="NULL";
}
//---------------------------------------------------------------------------
PuntoExtendido **TForm2::getNodos(){
  if (p!=NULL)
    return p->getNodosImput();

  return NULL;
};
//---------------------------------------------------------------------------
int TForm2::getNumNodos(){
  if (p!=NULL)
    return p->getNumNodosO();

  return -1;
};
//---------------------------------------------------------------------------
void TForm2::dibujarQuad(){
  unsigned int ancho=q->getAncho();
  if (ancho*grillado>MAXANCHOIM)
        ancho=MAXANCHOIM/grillado;
  unsigned int level=q->getMaxLevelOcupado();
  unsigned int aumento;

  //preparo algunos colores para las lineas de cada nivel
  TColor *colores = new TColor[5];
  colores[0] = clBlue;
  colores[1] = clRed;
  colores[2] = clBlack;
  colores[3] = clMaroon;
  colores[4] = clBackground;
  colores[5] = clPurple;

  //dibujo las lineas del borde
  plano->Canvas->Pen->Color=clBlue;
  plano->Canvas->Pen->Width=3;
  plano->Canvas->Rectangle(0,0,ancho*grillado,1);
  plano->Canvas->Rectangle(0,0,1,ancho*grillado);
  plano->Canvas->Rectangle(0,ancho*grillado,ancho*grillado,ancho*grillado+1);
  plano->Canvas->Rectangle(ancho*grillado,0,ancho*grillado+1,ancho*grillado);

  plano->Canvas->Pen->Color=clRed;
  plano->Canvas->Pen->Width=1;

  randomize();
  for (unsigned int i=0; i<=6; i++){
      aumento=q->getAnchoLevel(i);
      plano->Canvas->Pen->Color = colores[random(5)];
      while (aumento<=ancho){
          plano->Canvas->Rectangle(aumento*grillado,1,aumento*grillado+2,ancho*grillado);
          plano->Canvas->Rectangle(1,aumento*grillado,ancho*grillado,aumento*grillado+2);
          aumento+=q->getAnchoLevel(i)*2;
      }
  }
}
//---------------------------------------------------------------------------
void TForm2::dibujarPlano(){


  //cubro de blanco el plano
  plano->Canvas->Rectangle(0,0,4000,4000);
 /*
  //dibujo las lineas del borde
  plano->Canvas->Pen->Color=clBlack;
  plano->Canvas->Pen->Width=0.5;

  for (unsigned int i=1; i*grillado<MAXANCHOIM ; i++){
     plano->Canvas->Rectangle(i*grillado,1,(i*grillado)+1,MAXANCHOIM );
     plano->Canvas->Rectangle(1,i*grillado,MAXANCHOIM ,(i*grillado)+1);
  }  */
}
//---------------------------------------------------------------------------
void TForm2::dibujarPortales(){
  Punto **portales;
  unsigned int max=q->getDimComprimida();
  unsigned int numP;
  Cuadrante **quadtr=q->getArreglo();

  for (unsigned int i=1; i<max; i++)
    if (quadtr[i]!=NULL){
     portales=quadtr[i]->getPortales();
     numP=quadtr[i]->getCantPortales();
     for (int j=0; j<numP; j++)
        plano->Canvas->Draw(portales[j]->getY()*this->grillado-3,portales[j]->getX()*this->grillado-4,portal);
   };
};
//---------------------------------------------------------------------------
unsigned int  TForm2::setGrillado(){
    unsigned int maxPos=q->getAncho(); //sera lo maximo que debere dibujar
    if (MAXANCHOIM/maxPos<MINGRILLADO)
        return MINGRILLADO;

    return MAXANCHOIM/maxPos;

};
//---------------------------------------------------------------------------
void TForm2::execute()
{
     
    
        QueryPerformanceFrequency(&frecuencia);
        unsigned __int64 frec=frecuencia.QuadPart;


        //Perturbacion
        LARGE_INTEGER x;
        LARGE_INTEGER z;
        QueryPerformanceCounter(&x);
        p=new Perturbacion(&archivoOpen,c);
        QueryPerformanceCounter(&z);
        int ancho = p->getLargoEnclosingBox();

        unsigned __int64 dif=z.QuadPart-x.QuadPart;
        tiempoPert=(long double)dif/(long double)frec;

        //Portalizacion
        QueryPerformanceCounter(&x);
        port=new Portalizacion(ancho,ancho);
        QueryPerformanceCounter(&z);
        dif=z.QuadPart-x.QuadPart;
        tiempoPort=(long double)dif/(long double)frec;

        //QuadTree
        QueryPerformanceCounter(&x);
        unsigned int  entero=MAXINT;
        q=new QuadTreeTSP(ancho*ancho,ancho,ancho,c);
        q->make(p,port);
        QueryPerformanceCounter(&z);
        dif=z.QuadPart-x.QuadPart;
        tiempoQ=(long double)dif/(long double)frec;

       //Portalizacion
        QueryPerformanceCounter(&x);
        Lista<Cuadrante> *cuadrn = q->getCuadrantesPadres();
        Lista<Cuadrante> *hojas  = q->getHojas();
        port->portalizar(cuadrn,hojas);
        QueryPerformanceCounter(&z);
        dif=z.QuadPart-x.QuadPart;
        tiempoPort=tiempoPort +((long double)dif/(long double)frec);

        //Programacion Dinamica
        progD=new ProgramacionDinamica(q);
        QueryPerformanceCounter(&x);
        progD->execute();
        QueryPerformanceCounter(&z);
        dif=z.QuadPart-x.QuadPart;
        tiempoProg=(long double)dif/(long double)frec;

         //Trimer
        t=new Trimer(q,progD,p);
        QueryPerformanceCounter(&x);
        t->execute();
        QueryPerformanceCounter(&z);
        dif=z.QuadPart-x.QuadPart;
        tiempoTrim=(long double)dif/(long double)frec;
        largo=t->getLargoCamino();

}
//---------------------------------------------------------------------------
void TForm2::dibujarNodos(){
  if (ejecutado){
   PuntoExtendido **nodosAux=t->getCaminoTrimed();
   PuntoExtendido **nodosOrig = this->p->getNodosImput();
   unsigned int *numN=new unsigned int;
   (*numN)=p->getNumNodos();
   unsigned int div=t->getDivide();
   plano->Canvas->Pen->Color=clBlack;
   plano->Canvas->Pen->Width=2;
   plano->Canvas->MoveTo(nodosOrig[nodosAux[0]->getUbicacion()]->getY()*grillado,nodosOrig[nodosAux[0]->getUbicacion()]->getX()*grillado);

   for (int i=0; i<(div); i++)  {
      plano->Canvas->Draw(nodosOrig[nodosAux[i]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[i]->getUbicacion()]->getX()*grillado+2,nodoM);
      plano->Canvas->LineTo(nodosOrig[nodosAux[i]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[i]->getUbicacion()]->getX()*grillado+2);
   };

  if (div<(*numN)){
   plano->Canvas->MoveTo(nodosOrig[nodosAux[0]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[0]->getUbicacion()]->getX()*grillado+2);
   plano->Canvas->LineTo(nodosOrig[nodosAux[div]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[div]->getUbicacion()]->getX()*grillado+2);
  }
  else{
  if (div==(*numN)){
   plano->Canvas->MoveTo(nodosOrig[nodosAux[0]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[0]->getUbicacion()]->getX()*grillado+2);
   plano->Canvas->LineTo(nodosOrig[nodosAux[div-1]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[div-1]->getUbicacion()]->getX()*grillado+2);
  }
 }

   for (unsigned int i=div+1; i<(*numN) ; i++)  {
      plano->Canvas->Draw(nodosOrig[nodosAux[i]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[i]->getUbicacion()]->getX()*grillado+2,nodoM);
      plano->Canvas->LineTo(nodosOrig[nodosAux[i]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[i]->getUbicacion()]->getX()*grillado+2);
   };

   int aux = div -1;
   plano->Canvas->MoveTo(nodosOrig[nodosAux[(*numN)-1]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[(*numN)-1]->getUbicacion()]->getX()*grillado+2);
   plano->Canvas->LineTo(nodosOrig[nodosAux[aux]->getUbicacion()]->getY()*grillado+2,nodosOrig[nodosAux[aux]->getUbicacion()]->getX()*grillado+2);
               
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
       Form3->Close();
       Form5->Close();
       Form6->Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Abrir2Click(TObject *Sender)
{
         if (!abierto){
           open->Execute();
           archivoOpen=open->FileName;
           if (archivoOpen!="NULL")
                if  (!checkExtension())
                        archivoOpen="NULL";
                else{ //la extension era correcta
                        abierto= true;
                        open->CleanupInstance();
                }
          }
          else{
            Form5->setError(3);
            Form5->setVisible();
          }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::mn_resolveClick(TObject *Sender)
{
          if (abierto){
                   if (!ejecutado){
                     this->execute();
                     ejecutado=true;
                     this->dibujarPlano();
                     this->dibujarNodos();
                     
                   }
           }
          else{
                Form5->setError(2);
                Form5->setVisible();
         }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::mn_inputClick(TObject *Sender)
{
        if (ejecutado)  {
                Form3->setVisible();
        }
        else{
                Form5->setError(2);
                Form5->setVisible();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::mn_quadClick(TObject *Sender)
{
        if (ejecutado)  {
                this->dibujarQuad();
                if (portDibujados)
                   this->dibujarPortales();
                mostrado=true;
        }else{
                 Form5->setError(2);
                 Form5->setVisible();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::mn_portalsClick(TObject *Sender)
{
       if (ejecutado){
                this->dibujarPortales();
                mostrado=true;
                portDibujados=true;

       }else{
                Form5->setError(2);
                Form5->setVisible();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::it_closeInstanceClick(TObject *Sender)
{
       this->grillado=GRILLADODEF;
       this->dibujarPlano();
       this->ejecutado=this->abierto=mostrado=portDibujados=false;
       archivoOpen="NULL";      archivoOut="NULL";

}
//---------------------------------------------------------------------------
void __fastcall TForm2::mn_timesClick(TObject *Sender)
{
   if (this->ejecutado)
      Form6->showDatos(tiempoPert,tiempoQ,tiempoPort,tiempoProg,tiempoTrim,largo);
     else{
       this->Enabled=false;
       Form5->setError(2);
       Form5->setVisible();
      }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::it_zoomInClick(TObject *Sender)
{
   if (this->grillado>=MINGRILLADO){
        this->grillado = this->grillado/2;
        this->dibujarPlano();
        this->dibujarNodos();
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::it_zoomOutClick(TObject *Sender)
{
        this->grillado = this->grillado * 2;
        this->dibujarPlano();
        this->dibujarNodos();
}
//---------------------------------------------------------------------------


