#include "LinearAllocator.hpp"

int main()
{
	LinearAllocator li(10000);

	for (int index = 0 ; index < 1000 ; index++)
	{
		li.Allocate(10);
	}
	return (0);
}
