// main.cpp

#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>

#include "memorypool.hpp"
#include "StackAlloc.hpp"

//�����ʹ���
#define ELEMS 250000
#define REPS 50

int main()
{
	clock_t start;
	 StackAlloc<int, MemoryPool<int> > stackPool;  //ʹ�����Ǳ�д�õ��ڴ������ MemoryPool
	 start = clock();
	for (int j = 0; j < REPS; j++) {
	     assert(stackPool.empty());
	     for (int i = 0; i < ELEMS; i++)
	       stackPool.push(i);
	     for (int i = 0; i < ELEMS; i++)
	       stackPool.pop();
	 }
	 std::cout << "MemoryPool Allocator Time: ";
	 std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";  //CLOCKS_PER_SEC���ڽ�clock()�����Ľ��ת��Ϊ����Ϊ��λ����
	 system("pause");

	return 0;
}

