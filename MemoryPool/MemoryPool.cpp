// main.cpp

#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>

#include "memorypool.hpp"
#include "StackAlloc.hpp"

//个数和次数
#define ELEMS 250000
#define REPS 50

int main()
{
	clock_t start;
	 StackAlloc<int, MemoryPool<int> > stackPool;  //使用我们编写好的内存分配器 MemoryPool
	 start = clock();
	for (int j = 0; j < REPS; j++) {
	     assert(stackPool.empty());
	     for (int i = 0; i < ELEMS; i++)
	       stackPool.push(i);
	     for (int i = 0; i < ELEMS; i++)
	       stackPool.pop();
	 }
	 std::cout << "MemoryPool Allocator Time: ";
	 std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";  //CLOCKS_PER_SEC用于将clock()函数的结果转化为以秒为单位的量
	 system("pause");

	return 0;
}

