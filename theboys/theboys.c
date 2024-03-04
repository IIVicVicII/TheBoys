// programa principal do projeto "The Boys - 2023"
// Autor: Victor Gabriel Rodrigues da Silva, GRR:20231959

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mundo.h"
#include "eventos.h"
  

// programa principal
int main ()
{
  struct mundo_t *world ;
  
  srand(0) ;
  
  // iniciar o mundo
  world = iniciaMundo() ;
  
  // executar o laço de simulação
  simulaMundo (world) ;
  
  // destruir o mundo
  world = destroiMundo (world) ;
  
  return (0) ;
}
