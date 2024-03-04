/*
    Declaracao das structs necessarias e
    Funcoes auxiliares que alocam ou desalocam 
    Structs do mundo, como herois, bases e missoes 
*/

#ifndef _MUNDO_H
#define _MUNDO_H

#include "set.h"
#include "lista.h"

#define FIMDOMUNDO 525600
#define NHABILIDADES 10
#define NHEROIS 5 * NHABILIDADES
#define NBASES (NHEROIS/6)
#define NMISSOES (FIMDOMUNDO/100)
#define SIZE 20000

// minimize o uso de variáveis globais

struct heroi_t {
  int id ;                    // id do heroi
  int exp ;                   // experiencia total que o heroi obteve
  int paciencia ;             // paciencia do heroi
  int velocidade ;            // velocidade do heroi
  struct set_t *habilidades ; // struct que vai as habilidades do heroi
} ;

struct base_t {
  int id ;                    // id da base
  int local [2] ;             // coordenadas da base
  int lotacao ;               // herois totais que a base comporta
  struct set_t *presentes ;   // herois presentes na base
  lista_t *fila ;             // fila de espera
} ;

struct missao_t {
  int id ;                    // id da missao 
  int local [2] ;             // coordenadas da missao
  struct set_t *habilidades ; // struct que vai as habilitades que a missao requer 
} ;

struct mundo_t {
  int Nherois ;                            // numero total de herois que tem o mundo
  struct heroi_t *herois [NHEROIS] ;       // ponteiros para todos os herois
  int Nbases ;                             // numero total de bases que tem o mundo
  struct base_t *bases [NBASES] ;          // ponteiros para todas as bases
  int Nmissoes ;                           // numero total de missoes a acontecerem
  struct missao_t *missoes [NMISSOES] ;    // ponteiros para todas as missoes
  int Nhabilidades ;                       // numero de habilidades diferentes
  int TamanhoMundo [2] ;                   // dimensoes do mundo
  int relogio ;                            // relogio do mundo
} ;

// Alocacao do heroi com sua id, velocidade e paciencia ja colocados, sua experiencia zerada e um conjunto de habilidades aleatorio
struct heroi_t *iniciaHeroi (int id) ;

// Desalocacao do heroi
struct heroi_t *destroiHeroi (struct heroi_t *hero) ;

// Alocacao da base com id, local e lotacao ja colocados e structs que representam os herois presentes dentro da base e na fila para entrar
struct base_t *iniciaBase (int i) ;

// Desalocacao da base
struct base_t *destroiBase (struct base_t *base) ;

// Alocacao da missao com id e local ja colocados e um conjunto de habilidades necessarias para ser concluida
struct missao_t *iniciaMissao (int id) ;

// Desalocacao da missao
struct missao_t *destroiMissao (struct missao_t *missao) ;

// Iniciacao do mundo alocando o numero necessario de herois, bases e missoes que sao usadas durante a simulacao
struct mundo_t *iniciaMundo () ;

// Desalocacao de todo o mundo anteriormente alocado
struct mundo_t *destroiMundo (struct mundo_t *mundo) ;

// Funcao auxiliar que usei so para testar se os dados das structs estavam corretos (achei interessante deixar aqui)
void impressaoTeste (struct mundo_t *mundo) ;

#endif