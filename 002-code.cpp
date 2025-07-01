#include "splashkit.h"
#include "lost_in_space.h"

#include <vector>
using std::vector;
using namespace std;
#define MIN_POWER_RANGE -1500
#define MAX_POWER_RANGE 1500
#define MAX_GAME_RANGE 3000

/**
 * Initialises new player inside the game
 */
game_data new_game()
{
    game_data game;
    game.player = new_player();
    return game;
}

/**
 * It displays the power up bitmaps on the screen at random places
 * @param game
 */
void add_power_up(game_data &game)
{
    int range = rnd(MIN_POWER_RANGE, MAX_POWER_RANGE);
    game.powers.push_back(new_power_up(range, range));
}

/**
 * It displays the powerup effects on the screen
 * @param game
 * @param index
 */
void apply_power_up(game_data &game, int index)
{
    if (game.powers[index].kind == HEART)
    {

        if (game.player.heart <= 1)
            game.player.heart += 0.25;
    }

    else if (game.powers[index].kind == NOS)
    {

        if (game.player.nos <= 1)
            game.player.nos += 0.25;
    }

    else if (game.powers[index].kind == SHIELD)
    {

        if (game.player.shield < 3)
            game.player.shield += 1;
    }
}

// Removing the powerup at the inx from the vector

/**
 * It removes the powerup from the index of the player vector
 * @param game
 * @param index
 */

void remove_power_up(game_data &game, int inx)
{
    int last_idx = game.powers.size() - 1;
    game.powers[inx] = game.powers[last_idx];
    game.powers.pop_back();
}

/**
 * It removes the powerup from the index of the player vector
 * @param game
 * @param index
 */

void check_collisions(game_data &game)
{
    for (int i = 0; i < game.powers.size(); i++)
    {
        if (sprite_collision(game.player.player_sprite, game.powers[i].power_up_sprite)) //predefined function for checking collision
        {
            if (game.powers[i].power_visit == false)
            {
                game.powers[i].power_visit = true;
                game.player.score = game.player.score + 10;
                apply_power_up(game, i);
                remove_power_up(game, i);
            }
        }
    }
}

//checking whether the powerup is within the screen or not if not then removed
void check_power_up_position(game_data &game)
{
    for (int i = 0; i < game.powers.size(); i++)
    {
        double power_up_x = sprite_x(game.powers[i].power_up_sprite);
        double power_up_y = sprite_y(game.powers[i].power_up_sprite);

        // The powerup is removed if it goes out of the playing area of 3000
        if (power_up_x > MAX_POWER_RANGE or power_up_y > MAX_POWER_RANGE or power_up_x < MIN_POWER_RANGE or power_up_y < MIN_POWER_RANGE)
        {
            remove_power_up(game, i);
        }
    }
}

void update_game(game_data &game)
{
    if (rnd() < 0.05)
    {
        add_power_up(game);
    }

    check_collisions(game); // checks the collision between the spaceship and the power ups

    update_player(game.player);

    for (int i = 0; i < game.powers.size(); i++)
    {
        check_power_up_position(game);
        update_power(game.powers[i]);
    }
}
/**
* Shows the position of ship on minimap
*/
point_2d power_mini_map(power_up_data &powers)
{
    double power_x, power_y, mini_map_x, mini_map_y;

    power_x = sprite_x(powers.power_up_sprite);
    power_y = sprite_y(powers.power_up_sprite);

    mini_map_x = (power_x - MIN_POWER_RANGE) / MAX_GAME_RANGE * 100 + 930;
    mini_map_y = (power_y - MIN_POWER_RANGE) / MAX_GAME_RANGE * 100 + 15;

    return point_at(mini_map_x, mini_map_y);
}

point_2d player_mini_map(player_data &player)
{
    double player_x, player_y, mini_map_x, mini_map_y;

    player_x = sprite_x(player.player_sprite);
    player_y = sprite_y(player.player_sprite);

    mini_map_x = (player_x - MIN_POWER_RANGE) / MAX_GAME_RANGE * 100 + 930;
    mini_map_y = (player_y - MIN_POWER_RANGE) / MAX_GAME_RANGE * 100 + 15;

    return point_at(mini_map_x, mini_map_y);
}

void draw_minimap(game_data &game)
{
    for (int i = 0; i < game.powers.size(); i++)
    {
        draw_pixel(rgba_color(255, 0, 0, 350), power_mini_map(game.powers[i]), option_to_screen());
    }

    draw_pixel(rgba_color(0, 255, 0, 350), player_mini_map(game.player), option_to_screen());
}
/*
* Hud display of the game
*/
void hud_display(game_data &game)
{
    // Co ordinates of the player ship
    float x = sprite_x(game.player.player_sprite);
    float y = sprite_y(game.player.player_sprite);

    point_2d player_center;
    player_center = center_point(game.player.player_sprite);

    // displays the rectangle for helath,nos...
    fill_rectangle(COLOR_WHITE, 600, 325, 10, 10, option_to_screen());
    draw_rectangle(COLOR_RED, 915, 15, 130, 130, option_to_screen());

    draw_text("FUEL:", COLOR_WHITE, 420, 40, option_to_screen());
    draw_text("SHIELD:", COLOR_WHITE, 420, 140, option_to_screen());
    draw_text("LOCATION: " + to_string(x) + ", " + to_string(y), COLOR_WHITE, 815, 165, option_to_screen());
    draw_text("SCORE: " + to_string(game.player.score), COLOR_WHITE, 815, 150, option_to_screen());
    draw_text("NITRO:", COLOR_WHITE, 420, 73, option_to_screen());

    load_bitmap("empty", "empty.png");
    load_bitmap("full", "full.png");
    load_bitmap("blue_bar_bubbles", "blue_bar_bubbles.png");

    draw_bitmap("empty", 500, 30, option_to_screen());
    draw_bitmap("full", 500, 30, option_part_bmp(0, 0, game.player.heart * bitmap_width("full"), bitmap_height("full"), option_to_screen()));
    draw_bitmap("blue_bar_bubbles", 500, 60, option_part_bmp(0, 0, game.player.nos * bitmap_width("full"), bitmap_height("full"), option_to_screen()));
    draw_bitmap("empty", 500, 60, option_to_screen());

    // To display the nos updates...
    int a = 500;
    int count = game.player.shield;
    for (int i = 0; i <= count; i++)
    {

        load_bitmap("shield", "shield.png");
        draw_bitmap("shield", a, 95, option_to_screen(option_scale_bmp(0.75, 0.75)));
        a = a + 70;
    }

    draw_minimap(game);
}

void draw_game(game_data &game)
{
    clear_screen(COLOR_BLACK);

    hud_display(game);

    draw_player(game.player);

    for (int i = 0; i < game.powers.size(); i++)
    {
        draw_power(game.powers[i]);
    }

    refresh_screen(60);
}
