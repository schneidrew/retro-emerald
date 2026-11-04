#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Pestilence infests the target after a powder move")
{
    bool32 isWrapped;
    u16 wrappedMove;
    GIVEN {
        ASSUME(IsPowderMove(MOVE_COTTON_SPORE));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_COTTON_SPORE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_COTTON_SPORE, player);
        ABILITY_POPUP(player, ABILITY_PESTILENCE);
        MESSAGE("The opposing Wobbuffet has been afflicted with an infestation by Paras!");
    } THEN {
        isWrapped = opponent->volatiles.wrapped;
        wrappedMove = opponent->volatiles.wrappedMove;
        EXPECT(isWrapped);
        EXPECT_EQ(wrappedMove, MOVE_INFESTATION);
    }
}

SINGLE_BATTLE_TEST("Pestilence infests the target after a seed move")
{
    bool32 isWrapped;
    GIVEN {
        ASSUME(IsSeedMove(MOVE_SEED_BOMB));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SEED_BOMB); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SEED_BOMB, player);
        HP_BAR(opponent);
        ABILITY_POPUP(player, ABILITY_PESTILENCE);
        MESSAGE("The opposing Wobbuffet has been afflicted with an infestation by Paras!");
    } THEN {
        isWrapped = opponent->volatiles.wrapped;
        EXPECT(isWrapped);
    }
}

SINGLE_BATTLE_TEST("Pestilence infests the target after Leech Seed")
{
    bool32 isWrapped;
    GIVEN {
        ASSUME(IsSeedMove(MOVE_LEECH_SEED));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LEECH_SEED); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_PESTILENCE);
    } THEN {
        isWrapped = opponent->volatiles.wrapped;
        EXPECT(isWrapped);
    }
}

SINGLE_BATTLE_TEST("Pestilence does not activate for moves that are not powder or seed moves")
{
    GIVEN {
        ASSUME(!IsPowderMove(MOVE_SCRATCH));
        ASSUME(!IsSeedMove(MOVE_SCRATCH));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_PESTILENCE);
    }
}

SINGLE_BATTLE_TEST("Pestilence does not activate if the move misses")
{
    GIVEN {
        ASSUME(IsPowderMove(MOVE_SLEEP_POWDER));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SLEEP_POWDER, hit: FALSE); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_PESTILENCE);
    }
}

SINGLE_BATTLE_TEST("Pestilence does not activate if the target is already trapped")
{
    GIVEN {
        ASSUME(IsPowderMove(MOVE_COTTON_SPORE));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_COTTON_SPORE); }
        TURN { MOVE(player, MOVE_COTTON_SPORE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_PESTILENCE);
        NOT ABILITY_POPUP(player, ABILITY_PESTILENCE);
    }
}

SINGLE_BATTLE_TEST("Pestilence does not activate against Shield Dust")
{
    GIVEN {
        ASSUME(IsPowderMove(MOVE_COTTON_SPORE));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_PESTILENCE); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHIELD_DUST); }
    } WHEN {
        TURN { MOVE(player, MOVE_COTTON_SPORE); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_PESTILENCE);
    }
}
