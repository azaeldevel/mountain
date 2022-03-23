
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
		NO_EXISTS_FIELDS_INFO,
		NO_EXISTS_FIELD_NAME,
		FAILED_FIELD_INFO_FORMAT_FIELD,
		FAILED_FIELD_INFO_FORMAT_FIELD_CONTENT,
		NOT_FOUND_FIELD_NAME,
		NOT_FOUND_FIELD_TYPE,
		UNKNOW_TYPE_FIELD,
		NO_FOUND_TABLE,
		NO_FOUND_FIELD,
		FAIL_BUILD_GENERATION,
		FAIL_ON_MAPPING_FIEL,
		FAIL_BUILD_GENERATION_NO_ARRAY_POSIBLE,
	};
	
public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* subject);
	Exception(unsigned int code,const char* filename, unsigned int line);
	Exception(unsigned int code,const char* filename, unsigned int line,const char* subject);

	virtual const char* what () const throw ();
};

}

#endif