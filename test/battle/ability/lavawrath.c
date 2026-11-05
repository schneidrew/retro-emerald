#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Lavawrath uses Eruption when hit by a contact move")
{
    s16 eruptionDamage;
    u8 tacklePP;
    PARAMETRIZE { tacklePP = 0; }
    PARAMETRIZE { tacklePP = 5; }
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_SCRATCH); Speed(2); }
        OPPONENT(SPECIES_NUMEL) { Ability(ABILITY_LAVAWRATH); MovesWithPP({MOVE_TACKLE, tacklePP}); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ABILITY_POPUP(opponent, ABILITY_LAVAWRATH);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ERUPTION, opponent);
        HP_BAR(player, captureDamage: &eruptionDamage);
    } THEN {
        EXPECT_GT(eruptionDamage, 0);
        EXPECT_EQ(opponent->pp[0], tacklePP);
    }
}

SINGLE_BATTLE_TEST("Lavawrath does not activate on a non-contact move")
{
    GIVEN {
        ASSUME(!MoveMakesContact(MOVE_SWIFT));
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_SWIFT); Speed(2); }
        OPPONENT(SPECIES_CAMERUPT) { Ability(ABILITY_LAVAWRATH); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SWIFT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_LAVAWRATH);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_ERUPTION, opponent);
        }
    }
}

SINGLE_BATTLE_TEST("Lavawrath does not activate when the contact move misses")
{
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_CROSS_CHOP));
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_CROSS_CHOP); Speed(2); }
        OPPONENT(SPECIES_NUMEL) { Ability(ABILITY_LAVAWRATH); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CROSS_CHOP, hit: FALSE); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_LAVAWRATH);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_ERUPTION, opponent);
        }
    }
}