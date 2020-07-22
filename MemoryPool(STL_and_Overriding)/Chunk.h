#pragma once
#include <Windows.h>

class Chunk {
private:
	DWORD userDataSize;
	bool free;
public:
	Chunk(DWORD size) {
		userDataSize = size;
		free = true;
	}
	~Chunk() {};
	void write(void* dst) {
		memcpy(dst, this, sizeof(Chunk));
	}
	void read(void* src) {
		memcpy(this, src, sizeof(Chunk));
	}
	bool getFree() { return free; }
	void setFree(bool free) { this->free = free; }
	DWORD getUserDataSize() { return userDataSize; }
	void setUserDataSize(DWORD size) { userDataSize = size; }
};