#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stddef.h>

/// @brief Describes a memory pool
typedef struct mem_pool mem_pool_t;

/// @brief Allocate resources for a new memory pool
/// @param n_blocks Number of pool blocks
/// @param block_sz Size of a single block
/// @return Pointer to new memory pool struct, `NULL` on errors
mem_pool_t *mem_pool_new(size_t block_sz, size_t n_blocks);

/// @brief Free resources allocated for...
/// @param pool ... this memory pool
void mem_pool_destroy(mem_pool_t *pool);

/// @brief Allocate a new block in...
/// @param pool ... this memory pool
/// @return Pointer to block, `NULL` on failure
void* mem_pool_alloc(mem_pool_t *pool);

/// @brief Free a block in...
/// @param pool ... this memory pool...
/// @param ptr ... pointed to by this pointer
/// @return `0` on success, `-1` on failures
int mem_pool_free(mem_pool_t *pool, void *ptr);
#endif