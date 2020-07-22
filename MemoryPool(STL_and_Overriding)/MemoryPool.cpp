#include "pch.h"
#include "MemoryPool.h"
#include <iterator>

void* MemoryPool::allocate(DWORD size) {
	if (PoolSize < size)
		return NULL;
	Chunk* block = NULL;
	DWORD require = size + sizeof(Chunk);
	DWORD space;
	std::list<Chunk*>::iterator it = Chlist.begin();
	//search space
	while (it != Chlist.end()) {
		block = *it;
		if (block->getFree() && block->getUserDataSize() >= require) {
			space = block->getUserDataSize();
			block->setUserDataSize(block->getUserDataSize() - require);
			PoolSize -= require;
			break;
		}
		it++;
	}

	if (it == Chlist.end()) //can`t find
		return NULL;
	
	Chunk newCh(space - require);
	newCh.write(block);
	Chlist.insert(it++, block);
	return block;
}

bool MemoryPool::free(void* ptr) {
	std::list<Chunk*>::iterator it = Chlist.begin();
	while (it != Chlist.end()) {
		Chunk* chPtr = *it;
		if (chPtr == ptr) {
			chPtr->setFree(false);
			Chlist.erase(it);
			return true;
		}
		it++;
	}

	if (it == Chlist.end())
		return false;
}