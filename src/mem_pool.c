#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "mem_pool.h"

// Describes a dynamic stack node containing info about a block
struct block_node
{
    void *offset;               // Offset of the block from the origin
    bool busy;                  // Busy flag: high when block is in use 
    struct block_node *next;    // Pointer to the next node
};

static struct block_node *block_node_new(void *offset)
{
    struct block_node *node = malloc(sizeof(struct block_node));
    if (!node) return NULL;

    node->offset = offset;
    node->busy = false;
    node->next = NULL;

    return node;
}

struct mem_pool
{
    void *origin;                   // First address of the memory block
    size_t block_sz;                // Size of a memory block
    size_t n_blocks;                // Number of memory blocks

    struct block_node* *blocks;     // Array of block nodes
    struct block_node *next_block;  // Next block to allocate: head of the dynamic stack of nodes
};

mem_pool_t *mem_pool_new(size_t block_sz, size_t n_blocks)
{
    mem_pool_t *pool = malloc(sizeof(mem_pool_t));
    if (!pool) return NULL;

    pool->block_sz = block_sz;
    pool->n_blocks = 0;
    pool->origin = NULL;
    pool->blocks = NULL;
    pool->next_block = NULL;

    if (!(pool->origin = calloc(n_blocks, block_sz)))
    {
        mem_pool_destroy(pool);
        return NULL;
    }

    if (!(pool->blocks = calloc(n_blocks, sizeof(struct node*))))
    {
        mem_pool_destroy(pool);
        return NULL;
    }

    for (size_t i = 0; i < n_blocks; i++)
    if (!(pool->blocks[i] = block_node_new((uint8_t*)(pool->origin) + i * block_sz)))
    {
        mem_pool_destroy(pool);
        return NULL;
    }
    else
    {
        pool->n_blocks++;
        pool->blocks[i]->next = pool->next_block;
        pool->next_block = pool->blocks[i];
    }

    return pool;
}

void mem_pool_destroy(mem_pool_t *pool)
{
    if (!pool) return;

    if (pool->blocks)
    {
        for (size_t i = 0; i < pool->n_blocks; i++) 
            free(pool->blocks[i]);
        free(pool->blocks);
    }

    if (pool->origin) free(pool->origin);
    free(pool);
}

void* mem_pool_alloc(mem_pool_t *pool)
{
    if (!pool->next_block) return NULL;

    pool->next_block->busy = true;
    void *offset = pool->next_block->offset;

    pool->next_block = pool->next_block->next;
    return offset;
}

int mem_pool_free(mem_pool_t *pool, void *ptr)
{
    if (ptr < pool->origin)
        return -1;
    
    void *end = (uint8_t*)(pool->origin) + pool->n_blocks * pool->block_sz;
    if (ptr >= end)
        return -1;

    size_t diff = (uint8_t*)(ptr) - (uint8_t*)(pool->origin);
    if (diff % pool->block_sz != 0)
        return -1;

    struct block_node *node = pool->blocks[diff / pool->block_sz];
    if (!node->busy)
        return -1;
        
    node->busy = false;
    node->next = pool->next_block;
    pool->next_block = node;
    return 0;
}