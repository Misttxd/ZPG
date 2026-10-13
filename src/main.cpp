#include "Application.h"
#include <cstdlib>
#include <ctime>

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Application app;

	if (!app.initialization())
	{ 
		return -1;
	}


	app.run();

	return 0;
}
