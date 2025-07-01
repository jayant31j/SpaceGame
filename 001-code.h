#ifndef LOST_IN_SPACE
#define LOST_IN_SPACE

#include "splashkit.h"
#include "power_up.h"
#include "player.h"

#include <string>
#include <vector>
using std::vector;
using namespace std;

struct game_data
{
    player_data player;
    vector<power_up_data> powers;
};

/**
 *  Starts the new game
 * @param game
 */

game_data new_game();

/**
 * Draw all the vectors on the screen
 * @param game
 */

void draw_game(game_data &game);

/**
 * Update the game data on the screen
 * @param game
 */


void check_power_up_position(game_data &game);

void draw_minimap(const game_data &game);


void update_game(game_data &game);

/**
 * Check the collison between spaceship and the powerups
 * @param game
 */


void check_collisions(game_data &game);


/*
*Adds power ups
*/
void add_power_up(const game_data &game);

/*
*Shows the powerups effects
*/

void apply_power_up(const game_data &game);

/*
*Remove the epowerups after collision with the spaceship
*/

void remove_power_up(const game_data &game);


#endif
