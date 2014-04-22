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
#include "L.h"

template class Lista<Punto>;
template class Lista<Cuadrante>;
template class Lista<unsigned int>;
template class Lista<bool>;

template <class T>
Lista<T>::Lista(){raiz=actual=final=NULL; longitud=0;} ;

//--------------------------------
template <class T>
Lista<T>::~Lista(){vaciar();} ;
//--------------------------------
template <class T>
void Lista<T>::vaciar(){
        Nodo *aux = raiz;
	while(raiz != NULL)
	{aux = raiz;
	 raiz = raiz->sig;
	 delete aux;
	} ;
        raiz = final = actual = NULL;
 longitud=0;
};
//--------------------------------
template <class T>
void Lista<T>::agregar (T *elem)
{	Nodo *aux = new Nodo;
        aux->elem=elem;
	aux->sig = raiz;
        if ( raiz == NULL ){ //primera inserción
                final = aux;
        }
	raiz = aux;
	longitud++;
}
//--------------------------------
template <class T>
void Lista<T>::agregarOrdenado(T *elem){
	Nodo *aux = new Nodo;
        Nodo *actual,*anterior;
        aux->elem=elem;
	aux->sig =NULL;

        actual=raiz;
        anterior=NULL;
        while ((actual->elem<elem) && (actual!=NULL)){
          anterior=actual;
          actual=actual->sig;
        };

        //actualizo datos del puntero al final
        if ( actual != NULL && actual->sig == NULL ){
             final = actual;
        };
        if ( actual == NULL ){
             final = aux;   
        }

        //caso insercion en la raiz
        if (anterior==NULL){
           aux->sig=raiz;
           raiz=aux;
        }
        else{
           aux->sig=actual;
           anterior->sig=aux;
        };


	longitud++;
}
//--------------------------------
template <class T>
void Lista<T>::agregarFinal(T *elem){
	Nodo *aux = new Nodo;
        Nodo *actual;
        aux->elem=elem;
	aux->sig =NULL;

        actual=raiz;

        //caso insercion en la raiz
        if (actual==NULL){
           aux->sig=raiz;
           raiz=aux;
           final = raiz;
        }
        else{
           final->sig = aux;
           final = aux;
        }

	longitud++;
};
//--------------------------------
template <class T>
void Lista<T>::eliminar (T *elem)
{// si el elemento no esta no pasa nada
	Nodo *aux2, *aux1 = raiz;

	if(raiz == NULL) return;
	//primer caso

	if (*(raiz->elem)==*elem)
		{raiz = raiz->sig;
		 longitud--;
                 if ( raiz == NULL ){
                        final = NULL;
                 }
		 delete aux1;
		 return;
		}

	aux2 = aux1->sig;
	while (aux2 != NULL){
          if (*(aux2->elem)==*elem)
			{aux1->sig = aux2->sig;
                         if ( aux1->sig == NULL ){  //elimine el último nodo
                            final = aux1;
                         }
			 longitud--;
			 delete aux2;
			 return;
			}
		else
			{aux1=aux2;
			 aux2=aux2->sig;
			};
		};

} ;
//--------------------------------
template <class T>
void Lista<T>::eliminarSinBorrar (T *elem)
{// si el elemento no esta no pasa nada
	Nodo *aux2, *aux1 = raiz;

	if(raiz == NULL) return;
	//primer caso

	if (*(raiz->elem)==*elem)
		{raiz = raiz->sig;
		 longitud--;
                 if ( raiz == NULL ){
                        final = NULL;
                 }
		 return;
		}

	aux2 = aux1->sig;
	while (aux2 != NULL){
          if (*(aux2->elem)==*elem)
			{aux1->sig = aux2->sig;
                         if ( aux1->sig == NULL ){  //elimine el último nodo
                            final = aux1;
                         }
			 longitud--;
			 return;
			}
		else
			{aux1=aux2;
			 aux2=aux2->sig;
			};
		};

} ;
//--------------------------------
template <class T>
T *Lista<T>::get(int pos){
    if (pos<longitud){
      Nodo *aux1=raiz;
      T *aux=new T;
      int i;
      for (i=0; i<pos; i++)
           aux1=aux1->sig;
      aux=aux1->elem;
      return aux;
    }
    else
        return NULL;
};
//--------------------------------
template <class T>
T *Lista<T>::pertenece (T *elem)
{// NULL si no existe y sino la posición
	Nodo *aux = raiz;
	while (aux != NULL)
		{if (*(aux->elem)==(*elem))
			 return (aux->elem);
		else
			 aux=aux->sig;
		};
	return NULL;
} ;
//--------------------------------                  
template <class T>
T *Lista<T>::primero()
{
	if (raiz == NULL)
		return(NULL);
	else{
		actual=raiz;
		return(raiz->elem);
	}
}

//--------------------------------
template <class T>
T *Lista<T>::siguiente()
{
	if (actual == NULL)
		return(NULL);
	else
		if (actual->sig == NULL)
			return(NULL);
		else
		{  actual = actual->sig;
		   return(actual->elem);
		};
} ;
//--------------------------------
template <class T>
int Lista<T>:: tamanio()
{
 return(longitud);
 };
//--------------------------------
template <class T>
void Lista<T>::clonar(Lista<T> *origen){
	T *tmp;
	for (T *aux=origen->primero();aux;aux=origen->siguiente()){
		tmp=new T;
		*tmp=*aux;
		agregarFinal(tmp);
	} ;
};


//--------------------------------
//anibal
template <class T>
void Lista<T>::agregarLista(Lista<T> *list){
	T *tmp;
	for (T *aux=list->primero();aux;aux=list->siguiente()){
		tmp=new T;
		*tmp=*aux;
		agregar(tmp);
	};
} ;
//------------------------------------------------


//#pragma option -Jgd
//Lista<Punto>;
//Lista<Cuadrante>;




#pragma package(smart_init)



//---------------------------------------------------------------------------


