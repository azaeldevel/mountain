
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * mountain is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * mountain is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 
#include "Exception.hh"

namespace oct::mont
{
	
Exception::Exception()
{

}
Exception::Exception(unsigned int c) : core::v3::Exception(c)
{

}
Exception::Exception(unsigned int c,const char* s) : core::v3::Exception(c,s)
{

}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : core::v3::Exception(c,f,l)
{

}
Exception::Exception(unsigned int c,const char* s,const char* f, unsigned int l) : core::v3::Exception(c,s,f,l)
{

}


const char* Exception::what () const throw ()
{
	switch(code())
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
	case FAIL_BUILD_GENERATION_NO_ARRAY_POSIBLE:
		return "No se puede crear un arreglo para el campo indicado";
	case NOT_SET_TYPE_FIELD:
		return "No se ha asignado el tipo del campo";
	default:
		return "Error desconocido";
	}
	return "Error desconocido";
}
	
}