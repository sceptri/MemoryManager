#include "complex.h"
#include "memorymanager.h"

#ifdef USE_MEMORY_MANAGER

void* Complex::operator new(size_t size)
{
	return gMemoryManager.allocate(size);
}

void Complex::operator delete (void* pointerToDelete)
{
	gMemoryManager.free(pointerToDelete);
}

#endif
