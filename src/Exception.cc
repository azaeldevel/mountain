
#include "Exception.hh"

namespace oct::mont
{
	
Exception::Exception()
{

}
Exception::Exception(unsigned int c) : oct::Exception(c)
{

}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : oct::Exception(c,f,l)
{

}

const char* Exception::what () const throw ()
{
	switch(code)
	{
	case Errors::NO_ERROR:
		return "No error";
	case Errors::NO_EXISTS_DB:
		return "No existe Base de Datos";
	case Errors::NO_EXISTS_TB:
		return "No existe Tabla";
	case NO_EXISTS_HEADER_TB:
		return "No existe encabezado de Tabla";	
	case NO_EXISTS_HEADER_DB:
		return "No existe encabezado de Base de Datos";	
	case NO_CORRUPT_DB_COUNT_TB:
		return "El conteo de las tablas no coincide";		
	default:
		return "Error desconocido";
	}
	return "Error desconocido";
}
	
}