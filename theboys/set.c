// Abstract Data Type "set of integers"
// implemented using a boolean vector
// Carlos Maziero - DINF/UFPR, Sept 2023

#include <stdio.h>
#include <stdlib.h>

#include "set.h"


// Creates an empty set capable of holding "size" values (from 0 to size -1)
// Return: pointer to the new set or NULL if failure
struct set_t *set_create (int max) 
{
  struct set_t *alocacao ;
  struct set_t **ponteiro ;

  // Alocacao da struct
  alocacao = malloc (sizeof (struct set_t)) ;

  alocacao->size = max ;
  alocacao->num = 0 ;

  // Alocacao do vetor nulo
  alocacao->flag = calloc (max, sizeof (bool)) ;

  ponteiro = &alocacao ;

  return *ponteiro ;
}

// Destroys the set, freeing its memory
// Return: NULL
struct set_t *set_destroy (struct set_t *s)
{
  if (!s)
    return NULL;
    
  // Liberacao do vetor
  free (s->flag) ;

  // Liberacao da struct
  free (s) ;
  
  s = NULL ;
  return NULL ;
}

// Add an item to the set.
// Return: 1 if success or 0 if failure
int set_add (struct set_t *s, int item)
{
  if (!s)
    return 0 ;

  if (s->num >= s->size)
    return 0 ;

  s->flag[item] = 1 ;
  s->num = s->num + 1 ;
  return 1 ;
}

// Removes an item from the set.
// Return: 1 if success or 0 if failure
int set_del (struct set_t *s, int item)
{
  
  if (s->flag[item] == true)
  {
    s->flag[item] = 0 ;
    s->num = s->num - 1 ;
    return 1 ;
  }

  return 0 ;
}

// Verifies wether the item belongs to (is in) the set.
// Return: 1 if success or 0 if failure
int set_in (struct set_t *s, int item)
{
  if (s->flag[item] == true)
    return 1 ;
  
  return 0 ;
}

// Verifies wether the set is empty
// Return: 1 if success or 0 if failure
int set_empty (struct set_t *s)
{
  if (s->num == 0)
    return 1 ;

  return 0 ;
}

// Informs the set's cardinality (number of items or |S|)
// Return: n >=0 if success or -1 if failure
int set_card (struct set_t *s)
{
  if (s->num >= 0)
    return s->num ;

  return -1 ;
}

// Verifies wether s1 contains s2
// Return: 1 if success or 0 if failure
int set_contains (struct set_t *s1, struct set_t *s2)
{
  int i, x ;

  x = 1 ;

  for (i = 0; ((i < s1->size) && (x == 1)); i++)
  {
    if ((s2->flag[i] == true) && (s1->flag[i] == false))
      x = 0 ;
  }

  if (x == 1)
    return 1 ;

  return 0 ;
}

// Verifies wether s1 == s2
// Return: 1 if success or 0 if failure
int set_equal (struct set_t *s1, struct set_t *s2)
{
  int i, x ;

  if (s1->num != s2->num)
    return 0 ;
  
  x = 0 ;
  i = 0 ;

  while (((i < s1->num) || (i < s2->num)) && (x == 0))
  {
    if (s1->flag[i] != s2->flag[i])
        x = 1 ;
    i++ ;
  }

  if (x == 1)
    return 0 ;

  return 1 ;
}

// Puts in s3 the union of sets s1 and s2; s3 previous content
// is cleared, but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_union (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
  int i, x ;

  if ((!s1) || (!s2) || (!s3))
    return 0 ;
   
  x = 0 ;
  
  for (i = 0; i < s3->size; i++)
  {
    if ((s1->flag[i] == true) || (s2->flag[i] == true))
    {
      s3->flag[i] = 1 ;
      x++ ;
    }  
  }

  s3->num = x ;
  
  return 1 ;
}

// Puts in s3 the intersection of sets s1 and s2; s3 previous content
// is cleared, but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_intersect (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
  int i, x ;

  if ((!s1) || (!s2) || (!s3))
    return 0 ;
  
  for (i = 0; i < s3->size; i++)
    s3->flag[i] = 0 ;
  
  x = 0 ;
  
  for (i = 0; i < s3->size; i++)
  {
    if ((s1->flag[i] == true) && (s2->flag[i] == true))
    {
      s3->flag[i] = 1 ;
      x++ ;
    }  
  }

  s3->num = x ;
  
  return 1 ;
}

// Puts in s3 the difference s1 - s2; s3 previous content is cleared,
// but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_diff (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
  int i, x ;

  if ((!s1) || (!s2) || (!s3))
    return 0 ;
  
  for (i = 0; i < s3->size; i++)
    s3->flag[i] = 0 ;
  
  x = 0 ;
  
  for (i = 0; i < s3->size; i++)
  {
    if ((s1->flag[i] == true) && (s2->flag[i] == false))
    {
      s3->flag[i] = 1 ;
      x++ ;
    }  
  }

  s3->num = x ;
  
  return 1 ;
}

// Puts in s2 a copy of set s1; s2 previous content is cleared,
// but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_copy (struct set_t *s1, struct set_t *s2)
{
  int i ;

  if ((!s1) || (!s2))
    return 0 ;
  
  for (i = 0; i < s2->size; i++)
    s2->flag[i] = 0 ;

  i = 0 ;

  while ((i < s1->size) || (i < s2->size))
  {
    s2->flag[i] = s1->flag[i] ;
    i++ ;
  }

  s2->num = s1->num ;

  return 1 ;
}

// Prints the content of a set using this template:
// [ %d %d %d ] (%d items)\n
// (Does not belong to the TAD definition, but is useful for testing)
void set_print (struct set_t *s)
{
  int i, x ;

  printf ("[ ") ;

  i = 0 ;
  x = 0 ;

  while ((i < s->num) && (i < s->size))
  {
    if (s->flag[x] == true)
    {
      printf ("%d ", x) ;
      i++ ;
    }
    x++ ;
  }
  
  printf ("]\n") ;
}