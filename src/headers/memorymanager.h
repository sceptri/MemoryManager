#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

typedef unsigned long int size_t;

class IMemoryManager
{
public:
    virtual void* allocate(size_t) = 0;
    virtual void free(void*) = 0;
};

class MemoryManager : public IMemoryManager
{
private:
    struct FreeStore
    {
        FreeStore * next;
    };
    void expandPoolSize();
    void CleanUp();
    FreeStore* freeStoreHead;

public:
    MemoryManager();
    virtual ~MemoryManager();
    virtual void* allocate(size_t);
    virtual void free(void*);
};

#ifndef MEMORYMANAGER
	extern MemoryManager gMemoryManager;
#endif

#endif // MEMORYMANAGER_H
