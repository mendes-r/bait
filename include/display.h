// ifdef ... endif

#define MAX_SIZE 10

typedef struct{
  unsigned int n_items;
  char *content[MAX_SIZE];
}Menu;

void init_menu(Menu *m, FILE *file);
void destroy_menu(Menu *m);

void draw(Menu *f);

