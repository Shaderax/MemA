#include "StackAllocator.hpp"
#include <sys/mman.h>
#include <stdexcept>
#include <cassert>

StackAllocator::StackAllocator( std::size_t size )
{
	_data = mmap(nullptr, size, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);

	if (_data == MAP_FAILED)
		std::runtime_error("mmap error");

	_offset = 0;
	_maxSize = size;
}

StackAllocator::~StackAllocator( void )
{

}

void* StackAllocator::Allocate( std::size_t size )
{
	assert((_offset + size + sizeof(StackAllocator::AllocatorHeader) <= _maxSize) && "Exceed the maximum size");

	std::size_t mem = (std::size_t)_data + _offset + size;
	*(std::size_t*)((std::size_t)mem) = size;
	_offset += size + sizeof(AllocatorHeader);

	return ((void*)(mem + sizeof(AllocatorHeader)));
}

void StackAllocator::Free( void* ptr )
{
	
}
