#include <stdio.h>
#include <stdlib.h>

#include "mundo.h"
#include "set.h"
#include "lista.h"

// Funcao que aloca um heroi com suas caracteristicas
struct heroi_t *iniciaHeroi (int id)
{
  struct heroi_t *alocacao ;
  int Nhabilidades, i, *habilidade ;

  alocacao = malloc (sizeof (struct heroi_t)) ;

  alocacao->id = id ;
  alocacao->exp = 0 ;
  alocacao->paciencia = rand () % 101 ;
  alocacao->velocidade = 50 + rand () % 4951 ;

  Nhabilidades = 1 + rand () % 3 ;

  habilidade = malloc (Nhabilidades * sizeof (int)) ;

  for (i = 0; i < Nhabilidades; i++)
  {
    habilidade[i] = 1 + rand () % NHABILIDADES ;
    for (int j = 0; j < i; j++)
    {
      if (habilidade[j] == habilidade[i])
      {
        i-- ;
        break ;
      }
    }
  }

  alocacao->habilidades = set_create (NHABILIDADES + 1) ;

  for (i = 0; i < Nhabilidades;i++)
    set_add (alocacao->habilidades, habilidade[i]) ;

  free (habilidade) ;

  return alocacao ;
}

// Funcao que desaloca o heroi alocado anteriormente
struct heroi_t *destroiHeroi (struct heroi_t *hero)
{
  if (hero == NULL)
    return NULL;

  hero->habilidades = set_destroy (hero->habilidades) ;
  free (hero) ;

  return NULL ;
}

// Funcao que aloca uma base com suas caracteristicas
struct base_t *iniciaBase (int i)
{
  struct base_t *alocacao ;

  alocacao =  malloc (sizeof (struct base_t)) ;

  alocacao->id = i ;
  alocacao->local[0] = rand () % SIZE ;
  alocacao->local[1] = rand () % SIZE ;
  alocacao->lotacao = 3 + rand () % 7 ;

  alocacao->presentes = set_create (NHEROIS) ;

  alocacao->fila = lista_cria () ;

  return alocacao ;
}

// Funcao que desaloca uma base alocada anteriormente
struct base_t *destroiBase (struct base_t *base)
{
  if (base == NULL)
    return NULL;

  int elemento ;

  base->presentes = set_destroy (base->presentes) ;

  while (lista_vazia(base->fila) == 0)
  {
    lista_retira (base->fila, &elemento, 0) ;
  }
  
  base->fila = lista_destroi (base->fila) ;
  
  free (base) ;

  return NULL ;
}

// Funcao que aloca uma missao com suas caracteristicas
struct missao_t *iniciaMissao (int id)
{
  struct missao_t *alocacao ;
  int Nhabilidades, i, *habilidade ;

  alocacao =  malloc (sizeof (struct missao_t)) ;

  alocacao->id = id ;
  alocacao->local[0] = rand () % SIZE ;
  alocacao->local[1] = rand () % SIZE ;

  Nhabilidades = 6 + rand () % 4 ;

  habilidade = malloc (Nhabilidades * sizeof (int)) ;

  for (i = 0; i < Nhabilidades; i++)
  {
    habilidade[i] = 1 + rand () % NHABILIDADES ;
    for (int j = 0; j < i; j++)
    {
      if (habilidade[j] == habilidade[i])
      {
        i-- ;
        break ;
      }
    }
  }

  alocacao->habilidades = set_create (NHABILIDADES + 1) ;

  for (i = 0; i < Nhabilidades;i++)
    set_add (alocacao->habilidades, habilidade[i]) ;

  free (habilidade) ;

  return alocacao ;
}

// Funcao que desaloca uma missao alocada anteriormente
struct missao_t *destroiMissao (struct missao_t *missao)
{
  if (missao == NULL)
    return NULL;

  missao->habilidades = set_destroy (missao->habilidades) ;
  free (missao) ;

  return NULL ;
}

// Funcao que aloca o mundo e chama as funcoes de alocar herois, bases e missoes
struct mundo_t *iniciaMundo ()
{
  struct mundo_t *alocacao ;
  int i ;

  alocacao = malloc (sizeof (struct mundo_t)) ;

  // Set os dados do mundo
  alocacao->Nherois = NHEROIS ;
  alocacao->Nbases = NBASES ;
  alocacao->Nmissoes = NMISSOES ;
  alocacao->Nhabilidades = NHABILIDADES ;
  alocacao->relogio = 0 ;
  alocacao->TamanhoMundo[0] = SIZE ;
  alocacao->TamanhoMundo[1] = SIZE ;

  // Aloca os herois do mundo
  for (i = 0; i < NHEROIS; i++)
    alocacao->herois[i] = iniciaHeroi(i) ;

  // Aloca as bases do mundo
  for (i = 0; i < NBASES; i++)  
    alocacao->bases[i] = iniciaBase(i) ;

  // Aloca as missoes que ocerrerao
  for (i = 0; i < NMISSOES; i++)
    alocacao->missoes[i] = iniciaMissao(i) ;

  return alocacao ;

}

// Funcao que vai desalocar todos herois, bases, missoes e o mundo durante a execucao da simulacao
struct mundo_t *destroiMundo (struct mundo_t *mundo)
{
  int i ;
  
  if (mundo == NULL)
    return NULL;

  // Desalocar herois
  for (i = 0; i < NHEROIS; i++)
    destroiHeroi(mundo->herois[i]) ;
  
  // Desalocar bases
  for (i = 0; i < NBASES; i++)
    destroiBase(mundo->bases[i]) ;
  
  // Desalocar missoes 
  for (i = 0; i < NMISSOES; i++)
    destroiMissao(mundo->missoes[i]) ;

  free (mundo) ;
  return NULL ;
}

// Funcao usada para testar os dados das structs
void impressaoTeste (struct mundo_t *mundo)
{
  int i ;
  
  for (i = 0; i < NHEROIS; i++)
  {
    printf("%d %d %d %d ", mundo->herois[i]->id, mundo->herois[i]->exp, mundo->herois[i]->paciencia, mundo->herois[i]->velocidade) ;
    set_print (mundo->herois[i]->habilidades) ;
  }

  printf("\n") ;

  for (i = 0; i < NBASES; i++)
  {
    printf("%d %d %d %d\n", mundo->bases[i]->id, mundo->bases[i]->local[0], mundo->bases[i]->local[1], mundo->bases[i]->lotacao) ;
  }

  printf("\n") ;

  for (i = 0; i < NMISSOES; i++)
  {
    printf("%d %d %d ", mundo->missoes[i]->id, mundo->missoes[i]->local[0], mundo->missoes[i]->local[1]) ;
    set_print (mundo->missoes[i]->habilidades) ;
  }
  
  return ;
}