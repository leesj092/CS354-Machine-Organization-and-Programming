#include "mem.h"                      
extern BLOCK_HEADER* first_header;

// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){
    // find a free block that's big enough
    if (size == 0) {
        return NULL;
    }

    BLOCK_HEADER *current = first_header;
    while ((current->size_alloc & 1) || (current->payload < size)) {
        // return NULL if we didn't find a block
        if (current->size_alloc == 1) {
            return NULL;
        }

        int block_size = current->size_alloc & 0xFFFFFFFE;
        current = (BLOCK_HEADER *)((unsigned long)current + block_size);
    }

    // allocate the block
    int originalSize = current->size_alloc;
    current->size_alloc += 1;
    current->payload = size;

    void *user_pointer = (void *)((unsigned long)current + 8);

    // split if necessary (if padding size is greater than or equal to 16 split the block)
    int block_size = current->size_alloc & 0xFFFFFFFE;
    int free_space = block_size - 8 - current->payload;

    if (free_space >= 16) {
        int padding = 0;
        BLOCK_HEADER *next_header = (BLOCK_HEADER *)((unsigned long)current + 8 + current->payload);

        while (((unsigned long)next_header + 8 + padding) % 16) {
            padding++;
        }

        next_header = (BLOCK_HEADER *)((unsigned long)current + 8 + current->payload + padding);

        current->size_alloc -= 1; //temporarily change to unallocated
        current->size_alloc = 8 + current->payload + padding;

        next_header->size_alloc = originalSize - current->size_alloc;
        next_header->payload = next_header->size_alloc - 8;

        current->size_alloc += 1; // turn back to allocated
    }

    return user_pointer;
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr) {
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    BLOCK_HEADER *current = first_header;
    void *comparePtr = (void *)((unsigned long)current + 8);

    while (comparePtr != ptr) {
        int block_size = current->size_alloc & 0xFFFFFFFE;
        current = (BLOCK_HEADER *)((unsigned long)current + block_size);

        if (current->size_alloc == 1) {
            return -1;
        }

        comparePtr = (void *)((unsigned long)current + 8);
    }
    
    // free the block
    if (current->size_alloc & 1) {
        current->size_alloc -= 1;
        current->payload = current->size_alloc - 8;
    } else {
        return -1; //already free
    }
    
    // coalesce adjacent free blocks
    // coalesce block after first
    int block_size = current->size_alloc & 0xFFFFFFFE;
    BLOCK_HEADER *next_header = (BLOCK_HEADER *)((unsigned long)current + block_size);

    if (!(next_header->size_alloc & 1)) {
        current->size_alloc += next_header->size_alloc;
        current->payload = current->size_alloc - 8;
    }

    // coalesce block before
    current = first_header;

    while (current->size_alloc != 1) {
        int blkSize = current->size_alloc & 0xFFFFFFFE;
        next_header = (BLOCK_HEADER *)((unsigned long)current + blkSize);

        if (!(current->size_alloc & 1) && !(next_header->size_alloc & 1)) {
            current->size_alloc += next_header->size_alloc;
            current->payload = current->size_alloc - 8;
            continue;
        }

        current = (BLOCK_HEADER *)((unsigned long)current + blkSize);
    }

    return 0;
}

