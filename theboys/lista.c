// GRR20231959 Victor Gabriel Rodrigues da Silva

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

// Funcao que aloca a lista
lista_t* lista_cria ()
{
    lista_t* lista ;

    lista = malloc (sizeof (lista_t)) ;

    lista->head = NULL ;
    lista->tail = NULL ;
    lista->size = 0 ;

    return lista ;
}

// Funcao que desaloca a lista
lista_t* lista_destroi (lista_t* lst)
{
    if (!lst)
        return NULL;
    
    free (lst) ;
    lst = NULL ;
    return NULL ;
}

// Funcao que insere um novo elemento na lista
int lista_insere (lista_t* lst, int elem, int pos)
{
    lnode_t* nodo ;
    lnode_t* auxiliar ;
    
    // If caso a lista seja nula
    if (!lst)
        return -1;

    nodo =  malloc (sizeof (lnode_t)) ;
    
    if (!nodo)
        return -1;
    
    lst->size = lst->size + 1;
    nodo->val = elem ;

    
    // If para caso seja o primeiro elemento da fila 
    if (lst->size == 1)
    {
        lst->head = nodo ;
        lst->tail = nodo ;
        nodo->prev = NULL ;
        nodo->next = NULL ;

        return lst->size ;
    }
    
    // If para colocar o elemento no inicio
    if (pos == 0) 
    {
        nodo->prev = NULL ;
        nodo->next = lst->head ;
        lst->head->prev = nodo ;
        lst->head = nodo ;
        
        return lst->size ;
    }

    // If para colocar o elemento no final
    if ((pos <= -1) || (pos >= lst->size))
    {
        nodo->prev = lst->tail ;
        nodo->next = NULL ;
        lst->tail->next = nodo ;
        lst->tail = nodo ;
        
        return lst->size ;
    }

    auxiliar = lst->head ;

    for (int i = 0; i < pos; i++)
    {
        auxiliar = auxiliar->next ;
    }

    nodo->prev = auxiliar->prev ;
    nodo->next = auxiliar ;
    auxiliar->prev->next = nodo ;
    auxiliar->prev = nodo ;

    return lst->size ;
}

// Funcao que retira um elemento da fila
int lista_retira (lista_t* lst, int* elem, int pos)
{
    lnode_t* auxiliar ;
    
    // If caso a fila seja nula ou o tamanho dela seja 0
    if ((!lst) || (lst->size <= 0)) 
    {
        *elem = -1 ;
        return -1;
    }

    lst->size = lst->size - 1 ;
    
    // If caso seja o ultimo elemento da fila
    if (lst->size == 0)
    {
        auxiliar = lst->head ;

        *elem = auxiliar->val ;
        lst->head = NULL ;
        lst->tail = NULL ;
        free (auxiliar) ;


        return lst->size ;
    }
    
    // If para retirar o primeiro elemento da fila
    if (pos == 0) 
    {
        auxiliar = lst->head ;

        *elem = auxiliar->val ;
        lst->head = auxiliar->next ;
        free (auxiliar) ;
        auxiliar = lst->head ;
        auxiliar->prev = NULL ;
        
        return lst->size ;
    }

    // If para retirar o ultimo elemento da fila
    if ((pos == -1) || (pos >= lst->size))
    {
        auxiliar = lst->tail ;

        *elem = auxiliar->val ;
        lst->tail = auxiliar->prev ;
        free (auxiliar) ;
        auxiliar = lst->tail ;
        auxiliar->next = NULL ;

        
        return lst->size ;
    }

    auxiliar = lst->head ;

    for (int i = 0; i < pos; i++)
    {
        auxiliar = auxiliar->next ;
    }

    *elem = auxiliar->val ;
    auxiliar->prev->next = auxiliar->next ;
    auxiliar->next->prev = auxiliar->prev ;
    free (auxiliar ) ;


    return lst->size ;
}

// Funcao que consulta valor na posicao desejada
int lista_consulta (lista_t* lst, int* elem, int pos)
{
    if ((!lst) || (lst->size == 0)) 
        return -1 ;

    lnode_t* auxiliar ;

    if (pos == 0)
    {
        *elem = lst->head->val ;
        return lst->size ;
    }

    if (pos == -1)
    {
        *elem = lst->tail->val ;
        return lst->size ;
    }

    if (pos >= lst->size)
    {
        *elem = -1 ;
        return lst->size ;
    }
    
    auxiliar = lst->head ;

    for (int i = 0; i < pos; i++)
    {
        auxiliar = auxiliar->next ;
    }

    *elem = auxiliar->val ;
    return lst->size ;
}

// Funcao que procura a primeira vez que o elemento aparece na fila
int lista_procura (lista_t* lst, int elem)
{
    if ((!lst) || (lst->size == 0)) 
        return -1 ;

    int x ;
    lnode_t* auxiliar ;

    auxiliar = lst->head ;
    x = 0 ;

    for (int i = 0; i < lst->size; i++)
    {
        if (auxiliar->val == elem)
                return x ;
        auxiliar = auxiliar->next ;
        x++ ;
    }
   
    return -1 ;
}

// Funcao que verifica se a lista esta vazia
int lista_vazia (lista_t* lst)
{
    if (lst->size == 0)
        return 1 ;
    return 0 ;
}

// Funcao que verifica o tamanho da lista
int lista_tamanho (lista_t* lst)
{
    if (!lst)
        return -1 ;

    return lst->size ;
}

// Funcao que imprime a lista
void lista_imprime (char *nome, lista_t* lst)
{
    if (!lst) 
        return ;
    
    lnode_t* auxiliar ;

    auxiliar = lst->head ;
    
    printf ("[ ") ;

    for (int i = 0; i < lst->size; i++)
    {
        printf ("%d ", auxiliar->val) ;
        auxiliar = auxiliar->next ;
    }

    printf ("]\n") ;
    return ;
}