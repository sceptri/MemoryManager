#include <iostream>
#include <ctime>

#include "complex.h"
#include "memorymanager.h"

int main(void)
{
#ifdef USE_MEMORY_MANAGER
	std::cout << "Using custom memory manager(memory pool): " << std::endl;
#endif
	std::cout << "Start" << std::endl;

	std::time_t t = std::time(0);

    Complex* array[1000];
	for (int i = 0; i < 750000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            array[j] = new Complex(i, j);
        }
        for (int j = 0; j < 1000; ++j)
        {
            delete array[j];
        }
    }

    std::time_t t2 = std::time(0);

	std::cout << "end: " << std::difftime(t2, t) << std::endl;

    return 0;
}
