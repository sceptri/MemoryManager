#define MEMORYMANAGER
#define POOLSIZE 32 //number of blocks for complex types == size of memory pool

#include "memorymanager.h"
#include "complex.h"

MemoryManager gMemoryManager;

MemoryManager::MemoryManager()
{
    freeStoreHead = 0;
    expandPoolSize();
}

MemoryManager::~MemoryManager()
{
    CleanUp();
}

void* MemoryManager::allocate(size_t size)
{
    if(freeStoreHead == 0)
    {
        expandPoolSize();
    }

    FreeStore* head = freeStoreHead;
    freeStoreHead = head->next;
    return head;
}

void MemoryManager::free(void * pointerToDelete)
{
    FreeStore* head = static_cast<FreeStore*>(pointerToDelete); //cast from void* to FreeStore*
    head->next = freeStoreHead;
    freeStoreHead = head;
}

void MemoryManager::expandPoolSize()
{
	size_t size;
	if(sizeof (Complex) > sizeof(FreeStore*))
	{
		size = sizeof (Complex);
	}
	else
	{
		size = sizeof(FreeStore*);
	}

	//reinterpret_cast because we allocate it with char array, but use it for anything else
	FreeStore* head = reinterpret_cast<FreeStore*>(new char[size]); //char is one byte, allocates acording amount of chars as would be in 'size'
	freeStoreHead = head;

	for (int i = 0; i < POOLSIZE; i++)
	{
		head->next = reinterpret_cast<FreeStore*>(new char[size]);
		head = head->next;
	}

	head->next = 0;
}

void MemoryManager::CleanUp()
{
	FreeStore* nextPtr =freeStoreHead;
	for(; nextPtr; nextPtr = freeStoreHead) //until nextPtr != NULL (0)
	{
		freeStoreHead = freeStoreHead->next;
		delete[] nextPtr; //it was allocated as char array
	}
}










