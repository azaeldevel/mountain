

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
	*\param table nombre de la table
	*\param  fileds nombre de los cmapos
	*\param result variable donde se coloca el resutado
	*/
	bool build(const char* table,const std::vector<const char*>& fileds,const char* name,std::string& result,bool human_readable);	
	bool build(const char* table,const std::vector<const char*>& fileds,const char* name,std::ofstream& result,bool human_readable);
	bool build(const char* table,const std::vector<const char*>& fileds,const char* name,std::filesystem::path& result,bool human_readable);

private:
	/**
	*\brief Mapea el nombre del campo con el objeto Field
	*
	*/
	bool maping_fields(const char*,const std::vector<const char*>&,std::vector<const Field*>& result);

private:
	const Database* database;
};

}


#endif