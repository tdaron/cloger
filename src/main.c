#include <screen.h>
#include <stdio.h>
#define SV_IMPLEMENTATION
#include <sv.h>
#include <time.h>
#include <unistd.h>
int main() {
  screen_init();
  screen_tell_text(sv_from_cstr("Hello, World ! I am cloger, a cool clock !"));
  while (true) {
    time_t t;
    struct tm *tm_info;
    char time_str[6]; // to hold the "HH:MM" string

    // Get the current time
    time(&t);
    tm_info = localtime(&t);

    // Format time as "HH:MM"
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
    screen_draw_text(sv_from_cstr(time_str));
    sleep(1);
  }
  screen_dispose();
  return 0;
}
