// TAD lista de números inteiros - interface
// Carlos Maziero - DINF/UFPR, Set 2023

#ifndef _LISTA_H
#define _LISTA_H

// estrutura de um nodo da lista
typedef struct lnode_t {
  int val ;			// valor armazenado
  struct lnode_t *prev ;	// nodo anterior
  struct lnode_t *next ;	// nodo seguinte
} lnode_t;

// estrutura de uma lista
typedef struct {
  lnode_t *head ;		// primeiro elemento
  lnode_t *tail ;		// último elemento
  int size ;			// tamanho da lista
} lista_t;

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL se falhar.
lista_t* lista_cria ();

// Remove todos os elementos da lista, libera espaço.
// Retorno: NULL.
lista_t* lista_destroi (lista_t* lst);

// Nas operações insere/retira/consulta, a posição 0 indica o início da lista;
// se a posição for -1 ou for além do fim, considerar o fim da lista.

// Insere o elemento na lista na posição indicada.
// Retorno: número de elementos na lista após a operação ou -1 se falhar.
int lista_insere (lista_t* lst, int elem, int pos);

// Retira o elemento da lista, na posição indicada.
// Retorno: número de elementos na lista após a operação ou -1 se falhar.
int lista_retira (lista_t* lst, int* elem, int pos);

// Informa o valor do elemento na posição indicada, sem retirá-lo.
// Retorno: número de elementos na lista ou -1 se falhar.
int lista_consulta (lista_t* lst, int* elem, int pos);

// Informa a posição da 1ª ocorrência do elemento indicado.
// Retorno: posição do elemento ou -1 se não encontrar ou falhar.
int lista_procura (lista_t* lst, int elem);

// Informa se a lista está vazia.
// Retorno: 1 se a lista está vazia ou 0 caso contrário.
int lista_vazia (lista_t* lst);

// Informa o tamanho da lista (o número de elementos presentes nela).
// Retorno: número de elementos na lista ou -1 se falhar.
int lista_tamanho (lista_t* lst);

// Imprime o conteúdo da lista, do inicio ao fim, neste formato:
// [ valor valor valor valor ... ]
// Esta função não faz parte do TAD, mas é útil para testes.
void lista_imprime (char *nome, lista_t* lst);

#endif

