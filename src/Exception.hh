
#ifndef OCTETOS_MOUNTAIN_EXCEPTION_HH
#define OCTETOS_MOUNTAIN_EXCEPTION_HH

#include <octetos/core/Exception.hh>

namespace oct::mont
{

class Exception : public oct::Exception
{
public:
	enum Errors
	{
		NO_ERROR,
		NO_EXISTS_DB,
		NO_EXISTS_TB,
		NO_EXISTS_HEADER_TB,
		NO_EXISTS_HEADER_DB,
		NO_CORRUPT_DB_COUNT_TB,
	};
	
public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* filename, unsigned int line);

	virtual const char* what () const throw ();

private:
};

}

#endif