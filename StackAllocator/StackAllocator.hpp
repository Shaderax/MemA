#include <cstddef>

class StackAllocator
{
	private:
		void*		_data;
		std::size_t	_offset;
		std::size_t	_maxSize;
	public:
		StackAllocator( std::size_t size );
		~StackAllocator( void );

		void* Allocate( std::size_t size );
		void Free( void* ptr );
		void Reset( void );

		struct AllocatorHeader
		{
			std::size_t	_size;
		};
};
