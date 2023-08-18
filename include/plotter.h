// ifdef ... endif

#define SIZE_LIMIT 10
#define ASCII_OFFSET 48

typedef struct{
  unsigned int n_items;
  char *content[SIZE_LIMIT];
}Menu;

void init_menu(Menu *m);
void draw(Menu *m);

