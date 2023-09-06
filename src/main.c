#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void * malloc(size_t size){

  void *p = sbrk(0);
  void *request = sbrk(size);
  if (request == (void*) -1) {
    return NULL;
  } else {
    assert(p == request);
    return p;
  }
}
