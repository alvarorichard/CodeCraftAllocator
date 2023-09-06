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


void *global_base = NULL;

struct block_meta *request_space(struct block_meta* last,size_t size){

  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*) block == request);
  if (request == (void*) -1) {
    return NULL;
  }
  if (last) {
    last -> next = block;
  }
  block -> size = size;
  block -> next = NULL;
  block -> free = 0;
  block -> magic = 0x12345678;
  return block;
}

void *malloc(size_t size){

  struct block_meta *block;

  if (size <= 0) {
    return NULL;
  }

  global_base = block;

  else {
    struct block_meta *last = global_base;
    if (!block) {
      block = request_space(last,size);
      if (!block) {
        return NULLL;
      }

    }
    else {
      block -> free = 0;
      block -> magic = 0x77777777;
    }
  }
  return (block+1);
}




