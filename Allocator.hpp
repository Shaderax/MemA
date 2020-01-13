class Allocator
{
	private:
	public:
		Allocator( void );
		virtual ~Allocator( void );

		Allocate( std::size_t size );
};
