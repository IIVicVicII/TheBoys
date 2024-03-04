#include <stdio.h>
#include <stdlib.h>

#include "lef.h"

/* 
 * Cria um evento contendo os parâmetros informados.
 * Retorna um ponteiro para o evento ou NULL se falhar.
 */
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2)
{
  struct evento_t **ponteiro ;
  struct evento_t *locacao ;

  locacao = malloc (sizeof (struct evento_t)) ;

  locacao->tempo = tempo ;
  locacao->tipo = tipo ;
  locacao->dado1 = dado1 ;
  locacao->dado2 = dado2 ;

  ponteiro = &locacao ;

  return *ponteiro ;
}

/* 
 * Destroi um evento e retorna NULL.
 */ 
struct evento_t *destroi_evento (struct evento_t *e)
{
    if (!e)
        return NULL;
    
    free (e) ;
    e = NULL ;
    return NULL ;
}

/* 
 * Cria uma LEF vazia 
 * Retorna um ponteiro para a LEF ou NULL se falhar.
 */
struct lef_t *cria_lef ()
{
  struct lef_t **ponteiro ;
  struct lef_t *locacao ;

  locacao = malloc (sizeof (struct lef_t)) ;

  locacao->primeiro = NULL ;

  ponteiro = &locacao ;

  return *ponteiro ;
}

/* 
 * Destroi a LEF, liberando a memória ocupada por ela, inclusive os eventos.
 * Retorna NULL.
 */ 
struct lef_t *destroi_lef (struct lef_t *l)
{
    if (!l)
        return NULL;
    
    free (l) ;
    l = NULL ;
    return NULL ;
}

/*
 * Insere o evento apontado na LEF na ordem de tempos crescentes.
 * Eventos com o mesmo tempo devem respeitar a politica FIFO.
 * Retorna 1 em caso de sucesso ou 0 caso contrario.
*/
int insere_lef(struct lef_t *l, struct evento_t *e)
{
    struct nodo_lef_t *auxiliar ;

    auxiliar = malloc (sizeof (struct nodo_lef_t));

    if (auxiliar == NULL)
    {
        return 0;
    }

    auxiliar->evento = e;
    auxiliar->prox = NULL;

    if (l->primeiro == NULL || l->primeiro->evento->tempo > e->tempo)
    {

        auxiliar->prox = l->primeiro;
        l->primeiro = auxiliar;

        return (1);
    }

    struct nodo_lef_t *auxiliarAnterior= l->primeiro;

    while (auxiliarAnterior->prox != NULL && (auxiliarAnterior->prox->evento->tempo <= e->tempo || (auxiliarAnterior->prox->evento->tipo < e->tipo && auxiliarAnterior->prox->evento->tempo < e->tempo)))
    {
        auxiliarAnterior= auxiliarAnterior->prox;
    }

    auxiliar->prox = auxiliarAnterior->prox;
    auxiliarAnterior->prox = auxiliar;

    return (1);
}

/* 
 * Retira o primeiro evento da LEF.
 * Retorna ponteiro para o evento ou NULL se falhar.
 */
struct evento_t *retira_lef (struct lef_t *l)
{
  struct nodo_lef_t *auxiliar ;
  struct evento_t *retorna ;

  auxiliar = l->primeiro ;

  l->primeiro = l->primeiro->prox ;

  retorna = auxiliar->evento ;

  free (auxiliar) ;

  return retorna ;
}

/* 
 * Informa se a LEF está vazia.
 * Retorna 1 se estiver vazia, 0 se não estiver ou -1 se falhar.
 */
int vazia_lef (struct lef_t *l)
{
  if (!l)
    return -1 ;
  
  if (l->primeiro == NULL)
    return 1 ;

  return 0 ;
}

/* 
 * Imprime a LEF. Não faz parte do TAD, mas serve para depuração.
 * Formato de saída:
 * tempo tipo dado1 dado2
 * tempo tipo dado1 dado2
 * ...
 * total XX eventos
 */
void imprime_lef (struct lef_t *l)
{
  int i = 0 ;

	printf ("LEF:\n") ;
	
  if (vazia_lef (l) == 1)
	{
		printf ("total %d eventos\n", i) ;
    return ;
	}
  struct nodo_lef_t *auxiliar ;

  auxiliar = l->primeiro ;

  while (auxiliar != NULL)
  {
    printf ("%d %d %d %d\n", auxiliar->evento->tempo, auxiliar->evento->tipo, auxiliar->evento->dado1, auxiliar->evento->dado2) ;
    auxiliar = auxiliar->prox ;
    i++ ;
  }
  printf ("total %d eventos\n", i) ;
}