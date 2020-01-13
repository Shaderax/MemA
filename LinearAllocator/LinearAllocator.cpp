#include "LinearAllocator.hpp"
#include <sys/mman.h>
#include <stdexcept>
#include <cassert>

LinearAllocator::LinearAllocator( std::size_t size )
{
	_data = mmap(nullptr, size, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);

	if (_data == MAP_FAILED)
		std::runtime_error("mmap error");

	_offset = 0;
	_maxSize = size;
}

LinearAllocator::~LinearAllocator( void )
{
	if (_data)
		munmap(_data, _maxSize);
}

void*	LinearAllocator::Allocate( std::size_t size )
{
	assert((_offset + size <= _maxSize) && "Exceed the maximum size");

	std::size_t mem = (std::size_t)_data + _offset;
	_offset += size;

	return ((void*)mem);
}

void LinearAllocator::Reset( void )
{
	_offset = 0;
}
