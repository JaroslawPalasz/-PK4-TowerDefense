#include "enums.h"
#include "game.h"
#include "Menu.h"
#include "TextureHolder.h"
#include "SceneManager.h"

//#include <vld.h>

int main()
{
	try
	{
		TextureHolder textures;
		Menu menu(&textures);
		menu.loop();

		if (menu.get_level() == 0 || menu.get_level() == 1 || menu.get_level() == 2)
		{
			Game game(&textures, menu.get_level());
			game.game_loop();
		}
	}
	catch (std::exception & ex)
	{
		std::cout << "error " << ex.what() << std::endl;
	}
	
	return 0;
}