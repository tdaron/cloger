#include <screen.h>
#include <stdio.h>
#define SV_IMPLEMENTATION
#include "wren.h"
#include <files.h>
#include <sv.h>
#include <unistd.h>

static void writeFn(WrenVM *vm, const char *text) {
  (void)vm;
  printf("%s", text);
}

void errorFn(WrenVM *vm, WrenErrorType errorType, const char *module,
             const int line, const char *msg) {
  (void)vm;
  switch (errorType) {
  case WREN_ERROR_COMPILE: {
    printf("[%s line %d] [Error] %s\n", module, line, msg);
  } break;
  case WREN_ERROR_STACK_TRACE: {
    printf("[%s line %d] in %s\n", module, line, msg);
  } break;
  case WREN_ERROR_RUNTIME: {
    printf("[Runtime Error] %s\n", msg);
  } break;
  }
}

void screenTell(WrenVM *vm) {
  const char *data = wrenGetSlotString(vm, 1);
  screen_tell_text(sv_from_cstr(data));
}
void screenDraw(WrenVM *vm) {
  const char *data = wrenGetSlotString(vm, 1);
  screen_draw_text(sv_from_cstr(data));
}

void wrenSleep(WrenVM *vm) {
  const double time = wrenGetSlotDouble(vm, 1);
  usleep(time * 1000000);
}

WrenForeignMethodFn bindForeignMethod(WrenVM *vm, const char *module,
                                      const char *className, bool isStatic,
                                      const char *signature) {
  (void)vm;
  (void)module;
  if (strcmp(className, "Screen") == 0) {
    if (isStatic && strcmp(signature, "tell(_)") == 0) {
      return screenTell;
    }
    if (isStatic && strcmp(signature, "draw(_)") == 0) {
      return screenDraw;
    }
  }
  if (strcmp(className, "Cloger") == 0) {
    if (isStatic && strcmp(signature, "sleep(_)") == 0) {
      return wrenSleep;
    }
  }
  // Other classes in main...
  // Other modules...
  return NULL;
}

WrenLoadModuleResult load_module(WrenVM *vm, const char *name) {
  (void)vm;
  char buffer[256] = {0};
  sprintf(buffer, "data/%s.wren", name);
  char *code = read_file(buffer);
  return (WrenLoadModuleResult){
      .source = code, .onComplete = NULL, .userData = NULL};
}

int main() {
  screen_init();
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = &writeFn;
  config.errorFn = &errorFn;
  config.bindForeignMethodFn = bindForeignMethod;
  config.loadModuleFn = load_module;
  WrenVM *vm = wrenNewVM(&config);

  const char *module = "main";
  const char *script = read_file("data/main.wren");
  WrenInterpretResult result = wrenInterpret(vm, module, script);

  switch (result) {
  case WREN_RESULT_COMPILE_ERROR: {
    printf("Compile Error!\n");
  } break;
  case WREN_RESULT_RUNTIME_ERROR: {
    printf("Runtime Error!\n");
  } break;
  case WREN_RESULT_SUCCESS: {
    printf("Success!\n");
  } break;
  }

  wrenFreeVM(vm);
  screen_dispose();
}
