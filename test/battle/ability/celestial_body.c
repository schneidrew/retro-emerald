#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Celestial Body sets Gravity and blocks Ground attacks")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_MUD_SLAP) == TYPE_GROUND);
        PLAYER(SPECIES_LUNATONE) { Ability(ABILITY_CELESTIAL_BODY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SLAP); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_CELESTIAL_BODY);
        MESSAGE("Gravity intensified!");
        ABILITY_POPUP(player, ABILITY_CELESTIAL_BODY);
        MESSAGE("It doesn't affect Lunatone…");
    }
}