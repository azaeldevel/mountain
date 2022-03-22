
#include "Exception.hh"

namespace oct::mont
{
	
Exception::Exception() : _subject(NULL)
{

}
Exception::Exception(unsigned int c) : oct::Exception(c)
{

}
Exception::Exception(unsigned int c,const char* s) : oct::Exception(c),_subject(s)
{

}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : oct::Exception(c,f,l)
{

}
Exception::Exception(unsigned int c,const char* s,const char* f, unsigned int l) : oct::Exception(c,f,l),_subject(s)
{

}

const char* Exception::subject()const throw ()
{
	return _subject;
}
std::string Exception::describe() const throw ()
{
	if(not _subject) return what();
	
	std::string msg = what();
	msg += "\n\t devido a ";
	msg += _subject;
	return msg;
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
	case NO_FOUND_TABLE:
		return "No se encontro la tabla especificada";	
	case NO_FOUND_FIELD:
		return "No se encontro el campo especificado";
	case FAIL_BUILD_GENERATION:
		return "Fallo en el conerador de contenedor.";	
	case FAIL_ON_MAPPING_FIEL:
		return "Fallo en el mapeo de los campos";
	default:
		return "Error desconocido";
	}
	return "Error desconocido";
}
	
}