#ifdef RAWTERM
#include <screen.h>
#include <stdio.h>
#include <stdlib.h>
void screen_init() {}

void screen_draw_text(String_View text) {
  system("clear");
  printf(SV_Fmt"\n", SV_Arg(text));
}

void screen_dispose() {}


#endif
