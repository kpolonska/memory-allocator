#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

typedef char ALIGN[16]; // stub var of 16 bytes

// TBD:
// 1. solve fragmentation - this code does not

union header {
	struct {
		size_t size;
		unsigned is_free; // 1 - free, 0 - busy
		union header *next;
	} s;
	ALIGN stub; // force union to be >= 16 bytes
};
typedef union header header_t;

header_t *head = NULL, *tail = NULL;
pthread_mutex_t global_malloc_lock; // declare the mutex

header_t *get_free_block(size_t size) // match the 
{
	header_t *curr = head;
	while(curr) {
		if (curr->s.is_free && curr->s.size >= size)
			return curr;
		curr = curr->s.next;
	}
	return NULL;
}

