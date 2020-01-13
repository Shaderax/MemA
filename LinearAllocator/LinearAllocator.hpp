#include <cstddef>

class LinearAllocator
{
	private:
		void*		_data;
		std::size_t	_offset;
		std::size_t	_maxSize;
	public:
		LinearAllocator( std::size_t size );
		~LinearAllocator( void );

		void* Allocate( std::size_t size );
		void Reset( void );
};
