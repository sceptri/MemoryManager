#ifndef SRC_HEADERS_MEMORYMANAGER_H_
#define SRC_HEADERS_MEMORYMANAGER_H_

typedef unsigned long int size_t;

const void* NULL = 0;

const static size_t CHUNK_HEADER_SIZE = (sizeof(unsigned char*));

class MemoryPool
{
private:
	//an array of memory blocks, each split up into chunks
	unsigned char** m_ppRawMemoryArray;

	//the from of the memory chunk linked list
	unsigned char* m_pHead;
	//size of each chunk and chunks per block
	unsigned int m_chunkSize, m_numChunks;

	unsigned int m_memArraySize; //number of blocks in the memory array
	bool m_toAllowResize; // true, if we resize memory pool when it fills

public:
	//construction
	MemoryPool(void);
	~MemoryPool(void);
	bool Init(unsigned int chunkSize, unsigned int numChunks);
	void Destroy(void);

	//allocation functions
	void* Alloc(void);
	void Free(void* pMem);
	unsigned int GetChunkSize(void) const { return m_chunkSize; }

	//settings
	void SetAllowResize(bool toAllowResize)
	{
		m_toAllowResize = toAllowResize;
	}

private:
	//resets internal vars
	void Reset(void);

	//internal memory allocation helpers
	bool GrowMemoryArray(void);
	unsigned char* AllocateNewMemoryBlock(void);

	//internal linked list management
	unsigned char* GetNext(unsigned char* pBlock);
	void SetNext(unsigned char* pBlockToChange, unsigned char* pNewNext);

	//don't allow copy constructor
	MemoryPool(const MemoryPool& memPool) {}
};





#endif /* SRC_HEADERS_MEMORYMANAGER_H_ */
