// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "eventos.h"
#include "lef.h"

// Funcoes auxiliares:

// Funcao que ordena bases de acordo com a distancia
void ordenaBases (int bases [][2], struct mundo_t *mundo, struct missao_t *missao)
{
	int ordenado, auxiliar, i ;
	
	// Prenchimento da matriz com a id e com a distancia
  for (i = 0; i < NBASES; i++)
  {
    bases[i][0] = mundo->bases[i]->id ;
    bases[i][1] =  sqrt (pow (mundo->bases[i]->local[0] - missao->local[0], 2) + pow (mundo->bases[i]->local[1] - missao->local[1], 2)) ;
  }

  // Ordenacao das bases da mais proxima para mais distante

  ordenado = 0 ;
  while (ordenado == 0)
  {	
    ordenado = 1 ;
    for (i = 0; i < NBASES - 1; i++)
    {
      	if (bases[i][1] > bases[i+1][1])
      	{
          	auxiliar = bases [i][1];
            bases [i][1] = bases [i+1][1] ;
            bases [i+1][1] = auxiliar ;
            auxiliar = bases [i][0] ;
            bases [i][0] = bases [i+1][0] ;
            bases [i+1][0] = auxiliar ;
          	
            ordenado = 0 ;
        }
    }
  }
}

// Funcao auxiliar para utilizar o QuickSort
void trocar (int vetor[], int x, int y)
{
	int auxiliar ;

	auxiliar = vetor[x] ;
	vetor[x] = vetor[y] ;
	vetor[y] = auxiliar ;
}

// Funcao auxiliar para utilizar o QuickSort
int divide(int vetor[], int x, int y)
{
	int p, m ;

	p = vetor[y] ;
	m = x ;

	for (int i = x; i < y; i++)
	{
		if (vetor[i] <= p)
		{
			trocar (vetor,m,i) ;
			m++ ;
		}
	}
	
	trocar(vetor, m, y) ;
	return m ;
}

// QuickSort para ordenar vetor
void quickS(int vetor[], int x, int y)
{
	int m ;
	
	if (x >= y)
		return ;

	m = divide (vetor, x, y) ;

	quickS (vetor, x, m-1) ;
	quickS (vetor, m+1, y) ;
}


// Evento chegada de um heroi a uma base
void eventoChega (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  
  int espera ;

  if (base->lotacao > base->presentes->num)
    espera = 1 ;

  else if (heroi->paciencia > (10 * base->fila->size))
    espera = 1 ;
  
  else espera = 0 ;


  if (espera == 1) 
  {
    // Cria o evento Espera
    ev = cria_evento (mundo->relogio, 1, heroi->id, base->id) ;
    insere_lef (l, ev) ;
    printf ("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", mundo->relogio, heroi->id, base->id, base->presentes->num, base->lotacao) ;
  }

  else 
  {
    // Cria o evento Desiste
    ev = cria_evento (mundo->relogio, 2, heroi->id, base->id) ;
    insere_lef (l, ev) ;
    printf ("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n", mundo->relogio, heroi->id, base->id, base->presentes->num, base->lotacao) ;
  }
}

// Evento espera de um heroi
void eventoEspera (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  

  printf ("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", mundo->relogio, heroi->id, base->id, base->fila->size) ;

  lista_insere (base->fila, heroi->id, -1) ;

  // Cria o evento Avisa
  ev = cria_evento (mundo->relogio, 3, base->id, 0) ;
  insere_lef (l, ev) ;
}

// Evento de desistencia de um heroi
void eventoDesistencia (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  

  printf ("%6d: DESIST HEROI %2d BASE %d\n", mundo->relogio, heroi->id, base->id) ;

  // Cria o evento Viagem
  ev = cria_evento (mundo->relogio, 6, heroi->id, base->id) ;
  insere_lef (l, ev) ;  
}

// Evento em que os herois sao avisado pelo porteiro
void eventoAvisa (struct mundo_t *mundo, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  
  int id ;
  char a ;

  printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ", mundo->relogio, base->id, base->presentes->num, base->lotacao) ;
  lista_imprime (&a, base->fila) ;

  // looping que adiciona herois da fila enquanto houver espaco
  while (base->presentes->num < base->lotacao && base->fila->size > 0)
  {
    lista_retira (base->fila, &id, 0) ;
    set_add (base->presentes, id) ;
    printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", mundo->relogio, base->id, id) ;

    // Cria o evento Entra
    ev = cria_evento (mundo->relogio, 4, id, base->id) ;
    insere_lef (l, ev) ; 
  }
}

// Evento do porteiro de avisar o heroi q ele entrara
void eventoEntra (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  
  int tpb ;

  // Calculo de quanto tempo o heroi permanecera na base
  tpb = 15 + heroi->paciencia * (1 + rand () % 20) ;

  printf ("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", mundo->relogio, heroi->id, base->id, base->presentes->num, base->lotacao, mundo->relogio + tpb) ;
 
  // Cria o evento Saida
  ev = cria_evento (mundo->relogio + tpb, 5, heroi->id, base->id) ;
  insere_lef (l, ev) ;  
}

// Evento em que o Heroi sai de uma base e ira para outra
void eventoSai (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  

  set_del (base->presentes, heroi->id) ;

  printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", mundo->relogio, heroi->id, base->id, base->presentes->num, base->lotacao) ;

  // Cria o evento Viagem
  ev = cria_evento (mundo->relogio, 6, heroi->id, base->id) ;
  insere_lef (l, ev) ;  

  // Cria o evento Avisa
  ev = cria_evento (mundo->relogio, 3, base->id, 0) ;
  insere_lef (l, ev) ;
}

// Evento que mostra quanto tempo o heroi demorara para ir de uma base a outra
void eventoViaja (struct mundo_t *mundo, struct heroi_t *heroi, struct base_t *base, struct lef_t *l )
{
  struct evento_t *ev ;  
  int baseNova, distancia ;
  
  baseNova = rand () % NBASES ;

  // Calculo da distancia
  distancia = sqrt (pow (base->local[0] - mundo->bases[baseNova]->local[0], 2) + pow (base->local[1] - mundo->bases[baseNova]->local[1], 2)) ;

  printf ("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", mundo->relogio, heroi->id, base->id, baseNova, distancia, heroi->velocidade, mundo->relogio + (distancia/heroi->velocidade)) ;

  // Cria o evento Chegada
  ev = cria_evento (mundo->relogio + (distancia/heroi->velocidade), 0, heroi->id, baseNova) ;
  insere_lef (l, ev) ;
  
}

// Evento missao 
void eventoMissao (struct mundo_t *mundo, struct missao_t *missao, struct lef_t *l, int *missoesCumpridas, int *tentativas, int segundaChance)
{
  struct evento_t *ev ;  
  struct set_t *base ;
  int i, j, concluida ;
  int bases [NBASES][2] ;

  printf("%6d: MISSAO %d HAB REQ: ", mundo->relogio, missao->id) ;
  set_print (missao->habilidades) ;

	ordenaBases (bases, mundo, missao) ;


  // Tentativas de concluir a missao ate que as bases acabem ou seja concluida
  concluida = 0 ;
  for (i = 0; i < NBASES && concluida == 0; i++)
  {
    base = set_create (NHABILIDADES + 1) ;

    printf ("%6d: MISSAO %d BASE %d DIST %d HEROIS ", mundo->relogio, missao->id, bases[i][0], bases[i][1]) ;
    set_print (mundo->bases[bases[i][0]]->presentes) ;
    
    // Pegar a uniao das habilidades dos herois
    for (j = 0; j < mundo->bases[bases[i][0]]->presentes->size; j++)
    {
      if (set_in (mundo->bases[bases[i][0]]->presentes, j) == 1)
      { 
        printf ("%6d: MISSAO %d HEROI %2d: ", mundo->relogio, missao->id, j) ;
        set_print (mundo->herois[j]->habilidades) ;
        set_union (base, mundo->herois[j]->habilidades, base) ;
      }
    }
    printf ("%6d: MISSAO %d HAB BASE %d: ", mundo->relogio, missao->id, bases[i][0]) ;
    set_print (base) ;

    // Verifica se as habilidades sao o suficiente para concluir a missao
    if (set_contains (base, missao->habilidades) == 1)
    {
      // Se sim aumenta em 1 o XP de cada heroi presente na base e sai do loop
      concluida = 1 ;
      for (j = 0; j < mundo->bases[bases[i][0]]->presentes->size; j++)
      {
        if (set_in (mundo->bases[bases[i][0]]->presentes, j) == 1)
          mundo->herois[j]->exp = mundo->herois[j]->exp + 1 ;
      }
      
      printf ("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", mundo->relogio, missao->id, bases[i][0]) ;
      set_print (mundo->bases[bases[i][0]]->presentes) ;
      *missoesCumpridas = *missoesCumpridas + 1 ;
    }
    
    *tentativas = *tentativas + 1 ;
    base = set_destroy (base) ;
  }

  // Caso nao tenha sido concluida
  if (concluida == 0)
  {
    printf ("%6d: MISSAO %d IMPOSSIVEL\n", mundo->relogio, missao->id) ;
    
    // Se eh a primeira tentativa, recria a mesma missao apos 24 horas
    if (segundaChance == 0)
    {
      ev = cria_evento (mundo->relogio + 1440, 7, missao->id , 1) ;
      insere_lef (l, ev) ;
    }
  }

  return ;
}

// Evento Fim que mostra todas estatisticas de herois e missoes
void eventoFim (struct mundo_t *mundo, int missoesCumpridas, int tentativas)
{
  double porcentagem, media ;

  printf ("%6d: FIM\n", mundo->relogio) ;

  // Mostrar atributos dos herois no final de tudo
  for (int i = 0; i < mundo->Nherois; i++)
  {
    printf ("HEROI %2d PAC %3d VEL %4d EXP %4d HABS ", mundo->herois[i]->id, mundo->herois[i]->paciencia, mundo->herois[i]->velocidade, mundo->herois[i]->exp) ;
    set_print (mundo->herois[i]->habilidades) ;
  }

  porcentagem = missoesCumpridas ;
  media = tentativas ;

  // Mostrar estastisticas das missoes durante a simulacao
  printf ("%d/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", missoesCumpridas, NMISSOES, (porcentagem/NMISSOES) * 100, media/NMISSOES) ;

}

/*
  Glossario da variavel tipo da lef 

  0 == Chega
  1 == Espera
  2 == Desiste
  3 == Avisa
  4 == Entra
  5 == Sai
  6 == Viaja
  7 == Missao
  8 == Final
*/



// Funcao que organizara todos os eventos que acontecem durante a simulacao
void simulaMundo (struct mundo_t *mundo) 
{
  struct lef_t *l ;  
  struct evento_t *ev ;
  int i, missoesCumpridas, tentativas, *v ;

  missoesCumpridas = 0 ;
  tentativas = 0 ;
  
  l = cria_lef () ;
  
  v = malloc (NMISSOES * (sizeof (int))) ;

  // Loop para aleatorizar o tempo das missoes
  for (i = 0; i < NMISSOES; i++)
    v[i] = rand () % FIMDOMUNDO ;
  
  // Funcao para ordenar cronologicamente os tempos sorteados anteriormente para colocar o id da missao condizente
  quickS (v, 0, NMISSOES - 1) ;
  
  
  // Loops para inserir eventos na LEF
  // Missoes
  for (i = 0; i < NMISSOES; i++)
  {
    ev = cria_evento (v[i], 7, i, 0) ;
    insere_lef (l, ev) ;
  } 

  free (v) ;
  
  // Chegadas iniciais durante os 3 primeiros dias 
  for (i = 0; i < 50; i++)
  {
    ev = cria_evento (rand () % 4320, 0, i, rand () % 8) ;
    insere_lef (l, ev) ;
  } 
  

  // Evento do fim
  ev = cria_evento (FIMDOMUNDO, 8, 0, 0) ;
  insere_lef (l, ev) ;

  // Looping para realizar os eventos
  while (mundo->relogio < FIMDOMUNDO)
  {
    ev = retira_lef (l) ;
    mundo->relogio = ev->tempo ;

    // Chegada
    if (ev->tipo == 0)
      eventoChega (mundo, mundo->herois[ev->dado1], mundo->bases[ev->dado2], l) ;

    // Espera
    else if (ev->tipo == 1)
      eventoEspera (mundo, mundo->herois[ev->dado1], mundo->bases[ev->dado2], l)  ;
    
    // Desiste
    else if (ev->tipo == 2)
      eventoDesistencia (mundo, mundo->herois[ev->dado1], mundo->bases[ev->dado2], l)  ;
  
    // Avisa
    else if (ev->tipo == 3)
      eventoAvisa (mundo, mundo->bases[ev->dado1], l)  ;
      
    // Entra
    else if (ev->tipo == 4)
      eventoEntra (mundo, mundo->herois[ev->dado1], mundo->bases[ev->dado2], l)  ;

    // Sai
    else if (ev->tipo == 5)
      eventoSai (mundo, mundo->herois[ev->dado1], mundo->bases[ev->dado2], l)  ;

    // Viaja
    else if (ev->tipo == 6)
      eventoViaja (mundo, mundo->herois[ev->dado1], mundo->bases[ev->dado2], l)  ;

    // Missao
    else if (ev->tipo == 7)
      eventoMissao (mundo, mundo->missoes[ev->dado1], l, &missoesCumpridas, &tentativas, ev->dado2) ;

    // Fim 
    else if (ev->tipo == 8)
      eventoFim(mundo, missoesCumpridas, tentativas) ;

    destroi_evento (ev) ;
  }

  // Looping pra retirar possiveis eventos que so aconteceriam apos o final da simulacao 
  while (!vazia_lef (l))
  {
    ev = retira_lef(l) ;
    destroi_evento (ev) ;
  }

  // Desalocar LEF  
  l = destroi_lef (l) ;
  
}
  