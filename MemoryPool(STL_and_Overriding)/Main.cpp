#include "pch.h"
#include "MemoryPool.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

#define MIN 10
#define MAX 10000

using namespace std;

bool dynamicAllocate(MemoryPool* mp) {
	vector<void*> tmp;
	srand(time(NULL));
	void* dynamictmp = NULL;
	int size;
	for (int i = 0; i < 100; i++) {
		size = MIN + rand() % (MAX - MIN);
		dynamictmp = mp->allocate(size);
		tmp.push_back(dynamictmp);
	}

	while (!tmp.empty()) {
		dynamictmp = tmp.back();
		if (dynamictmp == NULL)
			return false;
		delete dynamictmp;

		tmp.pop_back();
	}
	return true;
}

bool MemoryPooling(MemoryPool* mp) {
	vector<void*> tmp;
	srand(time(NULL));
	void* Mptmp = NULL;
	DWORD size;

	for (int i = 0; i < 100; i++) {
		size = MIN + rand() % (MAX - MIN);
		Mptmp = mp->allocate(size);
		tmp.push_back(Mptmp);
	}

	while (!tmp.empty()) {
		Mptmp = tmp.back();
		if (Mptmp == NULL) {
			delete mp;
			return false;
		}
		if (!mp->free(Mptmp)) {
			return false;
		}
		tmp.pop_back();
	}
	return true;
}

int main() {
	clock_t start;
	clock_t end;
	MemoryPool* MP;

	MP = new MemoryPool();

	start = clock();
	bool exe = dynamicAllocate(MP);

	if (exe) {
		end = clock();
		cout << "dynamic allocate : " << end - start << "ms" << endl;
	}
	else
		cout << "dynamic allocate failed!" << endl;

	exe = MemoryPooling(MP);
	if (exe) {
		end = clock();
		cout << "MemoryPooling allocate : " << end - start << "ms" << endl;
	}
	else
		cout << "MemoryPooling failed!" << endl;

	return 0;
}

