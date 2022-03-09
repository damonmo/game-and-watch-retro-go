extern unsigned char STACK_MALLOC_BUFFER[];
extern unsigned int STACK_MALLOC_INDEX;
#ifdef USE_AHB_MALLOC
extern unsigned char AHB_MALLOC_BUFFER[] __attribute__((section (".audio")));
#else
extern unsigned char *AHB_MALLOC_BUFFER;
#endif
extern unsigned int AHB_MALLOC_INDEX;

void stack_malloc_init(void);
#define stack_malloc(sz) _stack_malloc(sz, __FILE__, __FUNCTION__)
void *_stack_malloc(size_t sz, const char *caller_file, const char *caller_function);
void *stack_calloc(size_t nitems, size_t sz);
void *stack_realloc(void *ptr, size_t sz);
void stack_free(void *ptr);

void ahb_malloc_init(void);
#define ahb_malloc(sz) _ahb_malloc(sz, __FILE__, __FUNCTION__)
void *_ahb_malloc(size_t sz, const char *caller_file, const char *caller_function);
void ahb_free(void *ptr);
