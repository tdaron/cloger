#ifndef SCREEN_H
#define SCREEN_H
#include <sv.h>

void screen_init();

void screen_tell_text(String_View text);
void screen_draw_text(String_View text);

void screen_dispose();

#endif
