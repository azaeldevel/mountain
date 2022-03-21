
#include <iostream>



int main()
{
	oct::core::Shell shell;

	std::cout << "work directory : " << shell.cwd() << "\n";

	if(shell.exists("bin"))
    {
        std::cout << "Existe el directorio\n";
    }
    else
    {
        std::cout << "No existe el directorio\n";
    }

    if(shell.exists("configure.ac"))
    {
        std::cout << "Existe el configure.ac\n";
    }
    else
    {
        std::cout << "No existe el configure.ac\n";
    }


    if(shell.exists("configure2.ac"))
    {
        std::cout << "Existe el configure2.ac\n";
    }
    else
    {
        std::cout << "No existe el configure2.ac\n";
    }

    std::string logDirectory = "bin";
    std::string strDay = std::to_string(oct::core::getDayID());
    std::string strTime = std::to_string(oct::core::getTimeID());
    logDirectory = logDirectory + "/" + strDay + strTime;
    shell.mkdir(logDirectory);

	return EXIT_SUCCESS;
}
