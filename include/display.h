// ifdef ... endif

#include <fileio.h>

typedef struct{
  unsigned int n_items;
  char *content[SIZE_LIMIT];
}Menu;

void init_menu(Menu *m);
void destroy_menu(Menu *m);
void draw(Menu *f);

