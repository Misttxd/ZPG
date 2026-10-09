#include "Application.h"

int main(void)
{
	Application app;

	if (!app.initialization())
	{ 
		return -1;
	}


	app.run();

	return 0;
}