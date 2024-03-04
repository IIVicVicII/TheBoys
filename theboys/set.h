// Abstract Data Type "set of integers"
// implemented using a boolean vector
// Carlos Maziero - DINF/UFPR, Sept 2023

// This set implementation uses an array of boolean flags to represent
// the set content: if flag[x] == true then x is in the set

// THIS FILE SHOULD NOT BE MODIFIED - ESTE ARQUIVO NÃO DEVE SER ALTERADO

#ifndef _SET_H
#define _SET_H

#include <stdbool.h>

// represents a set of integers
struct set_t
{
  int size ;		// maximum number of values to store
  int num ;		// cardinality (current number of elements)
  bool *flag ;		// points to an array of "size" booleans
} ;

// Creates an empty set capable of holding "size" values (from 0 to size -1)
// Return: pointer to the new set or NULL if failure
struct set_t *set_create (int max) ;

// Destroys the set, freeing its memory
// Return: NULL
struct set_t *set_destroy (struct set_t *s);

// Add an item to the set.
// Return: 1 if success or 0 if failure
int set_add (struct set_t *s, int item);

// Removes an item from the set.
// Return: 1 if success or 0 if failure
int set_del (struct set_t *s, int item);

// Verifies wether the item belongs to (is in) the set.
// Return: 1 if success or 0 if failure
int set_in (struct set_t *s, int item);

// Verifies wether the set is empty
// Return: 1 if success or 0 if failure
int set_empty (struct set_t *s);

// Informs the set's cardinality (number of items or |S|)
// Return: n >=0 if success or -1 if failure
int set_card (struct set_t *s);

// Verifies wether s1 contains s2
// Return: 1 if success or 0 if failure
int set_contains (struct set_t *s1, struct set_t *s2);

// Verifies wether s1 == s2
// Return: 1 if success or 0 if failure
int set_equal (struct set_t *s1, struct set_t *s2);

// Puts in s3 the union of sets s1 and s2; s3 previous content
// is cleared, but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_union (struct set_t *s1, struct set_t *s2, struct set_t *s3);

// Puts in s3 the intersection of sets s1 and s2; s3 previous content
// is cleared, but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_intersect (struct set_t *s1, struct set_t *s2, struct set_t *s3);

// Puts in s3 the difference s1 - s2; s3 previous content is cleared,
// but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_diff (struct set_t *s1, struct set_t *s2, struct set_t *s3);

// Puts in s2 a copy of set s1; s2 previous content is cleared,
// but its range (0, max) is not modified
// Return: 1 if success or 0 if failure
int set_copy (struct set_t *s1, struct set_t *s2);

// Prints the content of a set using this template:
// [ %d %d %d ]\n
// (Does not belong to the TAD definition, but is useful for testing)
void set_print (struct set_t *s);

#endif
