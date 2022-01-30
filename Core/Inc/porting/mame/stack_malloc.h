unsigned char STACK_MALLOC_BUFFER[1024 * 1024];
unsigned int STACK_MALLOC_INDEX;

#define stack_malloc(sz) _stack_malloc(sz, __FILE__, __FUNCTION__)
void *_stack_malloc(size_t sz, char *caller_file, char *caller_function);
void *stack_calloc(size_t nitems, size_t sz);
void *stack_realloc(void *ptr, size_t sz);
void stack_free(void *ptr);
