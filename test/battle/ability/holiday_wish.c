#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Holiday Wish guarantees Rock Slide's flinch effect")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_ROCK_SLIDE, MOVE_EFFECT_FLINCH));
        PLAYER(SPECIES_DELIBIRD) { Ability(ABILITY_HOLIDAY_WISH); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_ROCK_SLIDE, secondaryEffect: FALSE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_SLIDE, player);
        MESSAGE("The opposing Wobbuffet flinched and couldn't move!");
    }
}