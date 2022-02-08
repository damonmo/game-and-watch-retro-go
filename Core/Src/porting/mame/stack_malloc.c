#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "stack_malloc.h"

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

unsigned int STACK_MALLOC_INDEX;
unsigned char STACK_MALLOC_BUFFER[475 * 1024];

void stack_malloc_init(void)
{
    STACK_MALLOC_INDEX = 0;
    memset(STACK_MALLOC_BUFFER, 0, sizeof(STACK_MALLOC_BUFFER));
}

void *_stack_malloc(size_t sz, const char *caller_file, const char *caller_function)
{
    void *addr;
    sz = ALIGN(sz + SIZE_T_SIZE);
    if(sizeof STACK_MALLOC_BUFFER - STACK_MALLOC_INDEX < sz)
        return NULL;
    addr = &STACK_MALLOC_BUFFER[STACK_MALLOC_INDEX];
    STACK_MALLOC_INDEX += sz;
    printf("stack_malloc %s %s %04x %d %d\n", caller_file, caller_function, addr, sz, STACK_MALLOC_INDEX);
    return addr;
}

void *stack_realloc(void *ptr, size_t sz)
{
    void *new_ptr;
    new_ptr = stack_malloc(sz);
    memcpy(new_ptr, ptr, sz);
    return new_ptr;
}

void *stack_calloc(size_t nitems, size_t sz)
{
    return stack_malloc(sz * nitems);
}

void stack_free(void *ptr)
{
    printf("stack_free %04x\n", ptr);
}
