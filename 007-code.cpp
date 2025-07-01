#include "splashkit.h"
#include "lost_in_space.h"


 
void load_resources()//Load the game images, sounds.
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");

    load_sound_effect("cheer", "cheer.wav");
    load_sound_effect("nos", "nos.wav");
    load_sound_effect("heart", "heart.wav");
    load_sound_effect("fuel", "fuel.wav");
    
}

/**
 * Entry point.
 *
 * Manages the initialisation of data, the event loop, and quitting.
 */

int main()
{   
    game_data game;


    open_window("Lost In Space", 1200, 650); // open game window
    load_resources();// load all the bitmaps for the game

     game = new_game();

    while (not quit_requested())
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(game.player);

        // Perform movement and update the camera
        update_game(game);

        draw_game(game);
        if (game.player.nos < 0 and game.player.heart < 0)
        {
            break;
        }
    }
    return 0;
}
