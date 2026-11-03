#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Truant loafs 50% of the time and heals 1/8 max HP when loafing")
{
	PASSES_RANDOMLY(1, 2, RNG_TRUANT);
	GIVEN {
		PLAYER(SPECIES_SLAKING) { Ability(ABILITY_TRUANT); MaxHP(160); HP(80); Moves(MOVE_CELEBRATE); }
		OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
	} WHEN {
		TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
		TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
	} SCENE {
		ABILITY_POPUP(player, ABILITY_TRUANT);
		HP_BAR(player, damage: -20);
		MESSAGE("Slaking is loafing around!");
	}
}
