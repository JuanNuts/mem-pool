#include <assert.h>
#include <stdio.h>
#include "mem_pool.h"

void test_full_allocation() {
    printf("TEST: full allocation... ");
    mem_pool_t *pool = mem_pool_new(sizeof(int), 3);

    void *p1 = mem_pool_alloc(pool);
    void *p2 = mem_pool_alloc(pool);
    void *p3 = mem_pool_alloc(pool);
    void *p4 = mem_pool_alloc(pool);

    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(p3 != NULL);
    assert(p4 == NULL); // Pool must be full
    
    mem_pool_destroy(pool);
    printf("\tOK\n");
}

void test_free_and_reuse() {
    printf("TEST: free and reuse... ");
    mem_pool_t *pool = mem_pool_new(sizeof(int), 2);

    void *p1 = mem_pool_alloc(pool);
    mem_pool_free(pool, p1);
    
    void *p2 = mem_pool_alloc(pool);
    assert(p1 == p2); // The same block should be allocated
    
    mem_pool_destroy(pool);
    printf("\tOK\n");
}

void test_invalid_free() {
    printf("TEST: invalid free... ");
    mem_pool_t *pool = mem_pool_new(sizeof(int), 10);

    // Out of range pointer
    int dummy;
    assert(mem_pool_free(pool, &dummy) == -1);

    // Double free
    void *p1 = mem_pool_alloc(pool);
    assert(mem_pool_free(pool, p1) == 0);
    assert(mem_pool_free(pool, p1) == -1); // It should be already free

    // Misaligned pointer
    p1 = mem_pool_alloc(pool);
    void *misaligned = (char*)p1 + 1; 
    assert(mem_pool_free(pool, misaligned) == -1); 

    mem_pool_destroy(pool);
    printf("\t\tOK\n");
}

int main() {
    test_full_allocation();
    test_free_and_reuse();
    test_invalid_free();
    
    printf("\nALL TESTS OK\n");
    return 0;
}