#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Estrutura de metadados para os blocos alocados
struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  int magic; 
};

#define META_SIZE sizeof(struct block_meta)

// Ponteiro para o início da lista de blocos alocados
void *global_base = NULL;

// Encontra um bloco livre de tamanho 'size' na lista
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

// Aloca espaço para um novo bloco
struct block_meta *request_space(struct block_meta *last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  if (request == (void *)-1) {
    return NULL;
  }

  if (last) {
    last->next = block;
  }

  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->magic = 0x12345678;
  return block;
}

// Aloca memória
void *my_malloc(size_t size) {
  struct block_meta *block;

  if (size <= 0) {
    return NULL;
  }

  if (!global_base) {
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    struct block_meta *last = global_base;
    block = find_free_block(&last, size);
    if (!block) {
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {
      block->free = 0;
      block->magic = 0x77777777;
    }
  }

  return (block + 1);
}

// Obtém o ponteiro de bloco a partir do ponteiro de dados
struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta *)ptr - 1;
}

// Libera memória
void my_free(void *ptr) {
  if (!ptr) {
    return;
  }

  struct block_meta *block = get_block_ptr(ptr);
  assert(block->free == 0);
  block->free = 1;
  block->magic = 0x55555555;
}

// Redimensiona a memória alocada
void *my_realloc(void *ptr, size_t size) {
  if (!ptr) {
    return my_malloc(size);
  }

  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    // Temos espaço suficiente. Poderíamos liberar algum espaço quando implementarmos a divisão.
    return ptr;
  }

  // Precisamos realmente realocar. Alocar novo espaço e liberar o espaço antigo.
  // Em seguida, copiar os dados antigos para o novo espaço.
  void *new_ptr = my_malloc(size);
  if (!new_ptr) {
    return NULL; // TODO: definir errno em caso de falha.
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  my_free(ptr);
  return new_ptr;
}

// Aloca memória e a inicializa com zero
void *my_calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize;
  void *ptr = my_malloc(size);
  if (ptr) {
    memset(ptr, 0, size);
  }
  return ptr;
}

int main() {
  // Teste suas funções de alocação e desalocação de memória aqui
  return 0;
}
