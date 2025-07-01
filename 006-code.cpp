#include "power_up.h"
#include "splashkit.h"

#define PLAYER_SPEED 5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100

bitmap power_up_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case DIAMOND:
        return bitmap_named("diamond");
    case FUEL:
        return bitmap_named("heart");
    case SHIELD:
        return bitmap_named("shield");
    case COIN:
        return bitmap_named("coin");
    case NOS:
        return bitmap_named("nos");

    default:
        return bitmap_named("fuel");
    }
}


power_up_data new_power_up(double x, double y)
{
    power_up_data result;
    result.kind = static_cast<power_up_kind>(rnd(7));
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));
    result.power_visit = false;

    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);

    sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);
    sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
    return result;
}

void draw_power(const power_up_data &power_to_draw)
{
    draw_sprite(power_to_draw.power_up_sprite);
}

void update_power(power_up_data &power_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(power_to_update.power_up_sprite);
}
