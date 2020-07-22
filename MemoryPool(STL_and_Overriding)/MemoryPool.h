#pragma once

#include "Chunk.h"
#include <list>

class MemoryPool {
private:
	std::list<Chunk*> Chlist;
	DWORD PoolSize;
	BYTE* poolMemory;
public:
	//Constructor
	MemoryPool() {
		poolMemory = ::new unsigned char[10000 * 100 + 1600];
		PoolSize = 10000 * 100 - sizeof(Chunk);

		//first Chunk
		Chunk freeChunk(PoolSize);
		freeChunk.write(poolMemory);
		Chlist.push_front(&freeChunk);
	}
	~MemoryPool() {	
		delete[] poolMemory;
	};
	void* allocate(int size) {
		void* ptr = new char[size];
		return ptr;
	}
	void* allocate(DWORD size);
	bool free(void* ptr);
};