#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Soprano increases the power of sound moves by 50%", s16 damage)
{
    enum Move move;
    enum Ability ability;
    PARAMETRIZE { move = MOVE_HYPER_VOICE; ability = ABILITY_SOPRANO; }
    PARAMETRIZE { move = MOVE_HYPER_VOICE; ability = ABILITY_CUTE_CHARM; }
    PARAMETRIZE { move = MOVE_TACKLE; ability = ABILITY_SOPRANO; }
    PARAMETRIZE { move = MOVE_TACKLE; ability = ABILITY_CUTE_CHARM; }

    GIVEN {
        ASSUME(IsSoundMove(MOVE_HYPER_VOICE));
        ASSUME(!IsSoundMove(MOVE_TACKLE));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.5), results[0].damage); // Soprano affects sound moves
        EXPECT_EQ(results[2].damage, results[3].damage); // Soprano does not affect non-sound moves
    }
}

SINGLE_BATTLE_TEST("Soprano makes sound moves always hit")
{
    PASSES_RANDOMLY(100, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(IsSoundMove(MOVE_SCREECH));
        ASSUME(GetMoveAccuracy(MOVE_SCREECH) < 100);
        ASSUME_STAT_CHANGE(MOVE_SCREECH, defense: -2);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SOPRANO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCREECH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREECH, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 2);
    }
}

SINGLE_BATTLE_TEST("Soprano does not make non-sound moves always hit")
{
    PASSES_RANDOMLY(GetMoveAccuracy(MOVE_FIRE_BLAST), 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(!IsSoundMove(MOVE_FIRE_BLAST));
        ASSUME(GetMoveAccuracy(MOVE_FIRE_BLAST) < 100);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SOPRANO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FIRE_BLAST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FIRE_BLAST, player);
    }
}
