/*
    Declaracao das funcoes que sao
    Necessarias para a simulacao
    Do mundo, os eventos e a simulacao
*/

#ifndef _EVENTOS_H
#define _EVENTOS_H

#include "mundo.h"
#include "lef.h"

// O heroi chega a alguma base
void eventoChega (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l) ;

// O heroi resolve esperar para entrar na base
void eventoEspera (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l) ;

// O heroi decide ir a outra base
void eventoDesistencia (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l ) ;

// O porteiro avisa quantos tem dentro da base e na fila, deixando entrar enquanto houver espaco
void eventoAvisa (struct mundo_t *mundo, struct base_t *base, struct lef_t *l ) ; 

// O heroi entra em uma base
void eventoEntra (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l ) ;

// O heroi sai de uma base
void eventoSai (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l ) ;

// O heroi se desloca para uma base aleatoria
void eventoViaja (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l ) ;

// Missao que verifica se ha base que consiga resolve-la
void eventoMissao (struct mundo_t *mundo, struct missao_t *missao, struct lef_t *l, int *missoesCumpridas, int *tentativas, int segundaChance) ;

// Fim da simulacao mostrando estatistcas dos herois e missoes
void eventoFim (struct mundo_t *mundo, int missoesCumpridas, int tentativas) ;

// Simulacao do mundo 
void simulaMundo (struct mundo_t *mundo) ;


#endif