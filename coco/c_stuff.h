#ifndef _c_stuff_h
#define _c_stuff_h

#include <coco.h>

#define long int

#define copy_struct(dst, src) memcpy((void *)&(dst), (void *)&(src), sizeof(src))

byte heapInit();
void abort();
void free(void *ptr);
void *calloc(unsigned num, unsigned sz);
void walkHeap();

#endif
