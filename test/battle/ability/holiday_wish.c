#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Holiday Wish guarantees Rock Slide's flinch effect")
{
    PASSES_RANDOMLY(100, 100, RNG_SECONDARY_EFFECT);
    GIVEN {
        PLAYER(SPECIES_DELIBIRD) { Ability(ABILITY_HOLIDAY_WISH); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_ROCK_SLIDE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_SLIDE, player);
        MESSAGE("The opposing Wobbuffet flinched!");
    }
}