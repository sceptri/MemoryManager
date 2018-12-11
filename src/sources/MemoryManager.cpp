
/* ---------- FROM GCC --------------
	To use this class, instantiate it and call the Init() function. The chunkSize is the
	size of each atomic memory chunk, and numChunks is the number of chunks that are
	created for each set of chunks. Collectively, this set of chunks is called a block. If you
	go over your limit of memory chunks, the memory pool will allocate another block for
	you. This isn’t catastrophic, but you don’t want to make a habit of going over your
	limit because it’s very time consuming to set up a new memory block. If Init()
	returns true , your memory pool is ready to go! You can call Alloc() and Free()
	to allocate and free a chunk, respectively.

*/
#include "MemoryManager.h"

bool MemoryPool::GrowMemoryArray(void)
{
	//allocate a new array
	size_t allocationSize = sizeof(unsigned char*) * (m_memArraySize+1);
	unsigned char** ppNewMemArray = (unsigned char**)malloc(allocationSize);

	//make sure the allocation succeeded
	if(!ppNewMemArray)
	{
		return false;
	}

	//copy existing memory pointers over
	for(unsigned int i = 0; i < m_memArraySize; i++)
	{
		ppNewMemArray[i] = m_ppRawMemoryArray[i];
	}

	//Allocate a new block of memory, Indexing m_memArraySize here is safe
	//because we haven't incremented it yet to reflect the new size
	ppNewMemArray[m_memArraySize] = AllocateNewMemoryBlock();

	//attach the block to the end of the current memory list
	if(m_pHead)
	{
		unsigned char* pCurr = m_pHead;
		unsigned char* pNext = GetNext(m_pHead);

		while(pNext)
		{
			pCurr = pNext;
			pNext = GetNext(pNext);
		}
		SetNext(pCurr, ppNewMemArray[m_memArraySize]);
	}
	else
	{
		m_pHead = ppNewMemArray[m_memArraySize];
	}

	//destroy old memory array
	if(m_ppRawMemoryArray)
	{
		free(m_ppRawMemoryArray);
	}

	//assign the new memory array and increment the size count
	m_ppRawMemoryArray = ppNewMemArray;
	m_memArraySize++;

	return true;
}

unsigned char* MemoryPool::AllocateNewMemoryBlock(void)
{
	//calculate the size of each block
	//and the size of the actual memory allocation
	size_t blockSize = m_chunkSize + CHUNK_HEADER_SIZE; //chunk + linked list

	//overhead
	size_t trueSize = blockSize * m_numChunks;

	//allocate the memory
	unsigned char* pNewMem = (unsigned char*)malloc(trueSize);
	if(!pNewMem)
	{
		return NULL;
	}

	//turn memory into a linked list of chunks
	unsigned char* pEnd = pNewMem + trueSize;
	unsigned char* pCurr = pNewMem;

	while(pCurr < pEnd)
	{
		//calculate the next pointer position
		unsigned char* pNext = pCurr + blockSize;

		//set the next pointer
		unsigned char** ppChunkHeader = (unsigned char**)pCurr;
		ppChunkHeader[0] = (pNext < pEnd ? pNext : NULL);

		//move to the next block
		pCurr += blockSize;
	}

	return pNewMem;
}

void* MemoryPool::Alloc(void)
{
	//if we're out of memory, grow the pool. This is very expensive
	if(!m_pHead)
	{
		//if we don't allow resize
		if(!m_toAllowResize)
		{
			return NULL;
		}

		//attempt to grow the pool
		if(!GrowMemoryArray())
		{
			return NULL; //couldn't allocate anymore memory
		}
	}

	//grab the first chunk from the list and to the next chunks
	unsigned char* pRet = m_pHead;

	m_pHead = GetNext(m_pHead);

	return (pRet + CHUNK_HEADER_SIZE); //make sure we return a pointer to
									   //the data section only
}

void MemoryPool::Free(void* pMem)
{
	//Calling Free() on a NULL pointer is perfectly valid C++ so
	//we have to check for it
	if(pMem != NULL)
	{
		//The pointer we get back is just to the data section of
		//the chunk. This gets us the full chunk
		unsigned char* pBlock =
			((unsigned char*)pMem) - CHUNK_HEADER_SIZE;

		//push the chunk to the front of the list
		SetNext(pBlock, m_pHead);
		m_pHead = pBlock;
	}
}























