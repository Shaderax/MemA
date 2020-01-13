#include "StackAllocator.hpp"

int main()
{
	StackAllocator al(1000);

	al.Allocate(10);
	return 0;
}
