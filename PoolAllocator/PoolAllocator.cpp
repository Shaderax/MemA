#include "PoolAllocator.hpp"
#include <sys/mman.h>
#include <stdexcept>
#include <cassert>

PoolAllocator::PoolAllocator( std::size_t size, std::size_t chunkSize )
{
	assert((size >= chunkSize) && "Chunck Size must be greater than total size");
    	assert((size % chunkSize == 0) && "Size must be a multiple of Chunk Size");

	_data = mmap(nullptr, size, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);

	if (_data == MAP_FAILED)
		std::runtime_error("mmap error");

	std::size_t nbChunk = size / chunkSize;
	for ( uint32_t index = 0 ; index < nbChunk ; index++)
	{
		_freeBlock.push_back(index);
	}
	_maxSize = size;
}

PoolAllocator::~PoolAllocator( void )
{
	if (_data)
		munmap(_data, _maxSize);
}

void*	PoolAllocator::Allocate( void )
{
	assert(!(_freeBlock.empty()) && "Exceed the maximum size");

	std::size_t free = _freeBlock.front();
	_freeBlock.pop_front();
	return ((void*)((std::size_t)_data + (free * _chunkSize)));
}

void PoolAllocator::Free( void* ptr )
{
	std::size_t current = (std::size_t)ptr - (std::size_t)_data;

//	assert((current % _chunkSize == 0) && "Free : Not Valid Pointer");

	current /= _chunkSize;
	_freeBlock.push_back(current);
}
