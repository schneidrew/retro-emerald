#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Multi Punch makes single-hit punching moves strike twice")
{
    GIVEN {
        ASSUME(IsPunchingMove(MOVE_MACH_PUNCH));
        ASSUME(GetMoveStrikeCount(MOVE_MACH_PUNCH) <= 1);
        ASSUME(!IsMultiHitMove(MOVE_MACH_PUNCH));
        PLAYER(SPECIES_LEDYBA) { Ability(ABILITY_MULTI_PUNCH); Moves(MOVE_MACH_PUNCH); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(500); }
    } WHEN {
        TURN { MOVE(player, MOVE_MACH_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MACH_PUNCH, player);
        HP_BAR(opponent);
        HP_BAR(opponent);
        MESSAGE("The Pokémon was hit 2 times!");
    }
}

SINGLE_BATTLE_TEST("Multi Punch does not add a hit to already multihit punching moves")
{
    GIVEN {
        ASSUME(IsPunchingMove(MOVE_DOUBLE_IRON_BASH));
        ASSUME(GetMoveStrikeCount(MOVE_DOUBLE_IRON_BASH) == 2);
        PLAYER(SPECIES_LEDIAN) { Ability(ABILITY_MULTI_PUNCH); Moves(MOVE_DOUBLE_IRON_BASH); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(500); }
    } WHEN {
        TURN { MOVE(player, MOVE_DOUBLE_IRON_BASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DOUBLE_IRON_BASH, player);
        HP_BAR(opponent);
        HP_BAR(opponent);
        MESSAGE("The Pokémon was hit 2 times!");
    }
}