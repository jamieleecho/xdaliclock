#include "tester.h"

#include "setjmp.h"


jmp_buf testJumpBuffer;

void testFunctions(char *name, void (*f)(), ...) {
  if (!name) {
    return;
  }
  va_list ap; 
  va_start(ap, f);
  while(f) {
    if (!setjmp(&testJumpBuffer)) {
      printf("Testing %s...\n", name);
      (*f)();
    }

    name = va_arg(ap, char *); 
    if (!name) {
      va_end(ap);
      return;
    }
    f = va_arg(ap, void *);
  }
  va_end(ap);
}
