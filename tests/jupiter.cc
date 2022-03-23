

#include "jupiter.hh"

int jupiter_init(void)
{

	return 0;
}
int jupiter_clean(void)
{

	return 0;
}
void jupiter_developing()
{
	Jupiter jupiter;
	jupiter.type = Jupiter::Type::Autotools;
	jupiter.component = Jupiter::Component::Library;
	jupiter.lingua = Jupiter::Lingua::CC;
	jupiter.model = Jupiter::Model::Mountain;
	jupiter.directory = "mountaintests";
	jupiter.name = "mountaintests";
	jupiter.maintenance = "azael.devel@gmail.com";
	jupiter.version.set("0.1-alpha");
	if(std::filesystem::exists(jupiter.directory)) std::filesystem::remove_all(jupiter.directory);
	
	CU_ASSERT(jupiter.generate());
}
