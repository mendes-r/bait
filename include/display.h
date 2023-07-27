// ifdef ... endif

typedef struct{
  unsigned int row;
  unsigned int col;
  unsigned int pad[4];
  unsigned int marg[4];
  char *content;
  unsigned int select;
}Menu;

void init_menu(Menu *f);

void draw(Menu *f);

