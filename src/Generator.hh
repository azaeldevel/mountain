

#ifndef OCTETOS_MOUNTAIN_GENERATOR_HH
#define OCTETOS_MOUNTAIN_GENERATOR_HH

#include "Database.hh"


namespace oct::mont
{

class Generator
{
public:
	Generator(const Database& db);
	/**
	*\brief Genera contenedor para los campos especificados
	*
	*/
	void generate(const char*,const std::vector<char*>&);
	/**
	*\brief Genera contenedor para los campos especificados
	*
	*/
	void maping_fields(const char*,const std::vector<char*>&);

private:
	const Database* database;
};

}


#endif