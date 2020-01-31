#pragma once
#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

const int memPoolCapacity = 4096;			//Max size of memory pool

class MemoryPool
{
private:
	static MemoryPool* instance;
	char mem[memPoolCapacity];				//Preallocate memory on stack
	char* stackPtr;							//Pointer to end of memory pool stack

	MemoryPool();
	//TO DO???
	//operator overload = 
	//copy constructor

public:
	static MemoryPool& GetInstance();
	static void DestroyInstance();
	void* Allocate(int memSize);
	void Deallocate(int memSize, void* memAdd);
	void GetMem();

};

#endif // !MEMORYPOOL_H
