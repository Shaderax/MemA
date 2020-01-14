#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <list>

class PoolAllocator
{
	private:
		void*		_data;
		std::size_t	_maxSize;
		std::size_t	_chunkSize;
	public:
		std::list<std::uint32_t>	_freeBlock;
		PoolAllocator( std::size_t size, std::size_t chunkSize );
		~PoolAllocator( void );

		void* Allocate( void );
		void Free( void* ptr );
};
