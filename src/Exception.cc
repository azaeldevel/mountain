
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
	case NO_EXISTS_FIELDS_INFO:
		return "No existe informacion de campos";		
	case NO_EXISTS_FIELD_NAME:
		return "No existe nombre de campo";			
	case FAILED_FIELD_INFO_FORMAT_FIELD:
		return "El formato de la configuracion 'fields' es incorrecto, deve ser una lista";	
	case FAILED_FIELD_INFO_FORMAT_FIELD_CONTENT:
		return "El contenido de la lista 'fields', deben ser grupos";	
	case NOT_FOUND_FIELD_NAME:
		return "No se encontro el nombre del campo";	
	case NOT_FOUND_FIELD_TYPE:
		return "No se encontro el tipo del campo";		
	case UNKNOW_TYPE_FIELD:
		return "Tipo de data desconocido";	
	default:
		return "Error desconocido";
	}
	return "Error desconocido";
}
	
}