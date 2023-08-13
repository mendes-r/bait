// ifdef ... endif

typedef struct{
  char *content;
  unsigned int content_size;
  unsigned int nr_items;
}Menu;

void init_menu(Menu *f);

void draw(Menu *f);

