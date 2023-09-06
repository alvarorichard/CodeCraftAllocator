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

struct block_meta {
  size_t;
  struct block_meta *next;
  int free;
  int magic;
};


#define META_SIZE sizeof (struct block_meta)

void *global_base = NULL;


struct block_meta *find_free_block(struct block_meta **last size_t size) {

  struct block_meta *current = global_base;

  while (current && ! (current -> free && current ->size >=size)) {

    *last = current;
    current = current -> next;
  }
  return current;


}

