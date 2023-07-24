#include <stdio.h>

#include <display.h>

void init_frame(Frame *f){
  f->row=1;
  f->col=1;
  f->pad[0]=0;
  f->pad[1]=0;
  f->pad[2]=0;
  f->pad[3]=0;
  f->marg[0]=0;
  f->marg[1]=0;
  f->marg[2]=0;
  f->marg[3]=0;
  f->content="";
}

void draw(Frame *f){
  printf("DRAWING FRAME\n");
  printf("SIZE = row: %d; col: %d\n", f->row, f->col);
  printf("CONTENT:\n%s\n", f->content);
  // TODO save window current-view
  // TODO draw the bait-frame on top of the current-view
  // TODO re-do the current-view
}
