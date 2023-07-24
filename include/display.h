// ifdef ... endif

typedef struct{
  unsigned int row;
  unsigned int col;
  unsigned int pad[4];
  unsigned int marg[4];
  char *content;
}Frame;

void init_frame(Frame *f);
void draw(Frame *f);

