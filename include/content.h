#ifndef CONTENT_H
#define CONTENT_H

#define SIZE_LIMIT 5

typedef struct {
  unsigned int n_items;
  char *content[SIZE_LIMIT];
} Trap;

/* 
 * Returns the updated number of items.
 * -1 is return in case of error
 */
int add_content(Trap *trap, char *item);

/*
 * Returns the updated number of items.
 * -1 is return in case of error
 */
int rm_content(Trap *trap, int index);

/*
 * Returns the number of items retrieved from the persistence source.
 * -1 is return in case of error
 */
int import_content(Trap *trap);

/*
 * Persists content.
 * -1 is return in case of error
 */
int export_content(Trap *trap);

#endif /* CONTENT_H */
