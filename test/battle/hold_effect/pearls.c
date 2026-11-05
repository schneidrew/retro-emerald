#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetItemHoldEffect(ITEM_PEARL) == HOLD_EFFECT_PEARL_BOOST);
    ASSUME(GetItemHoldEffectParam(ITEM_PEARL) == 20);
    ASSUME(GetItemHoldEffect(ITEM_BIG_PEARL) == HOLD_EFFECT_PEARL_BOOST);
    ASSUME(GetItemHoldEffectParam(ITEM_BIG_PEARL) == 30);
    ASSUME(GetItemHoldEffect(ITEM_PEARL_STRING) == HOLD_EFFECT_PEARL_BOOST);
    ASSUME(GetItemHoldEffectParam(ITEM_PEARL_STRING) == 50);
}

SINGLE_BATTLE_TEST("Pearls boost Spoink and Grumpig's Special Attack", s16 damage)
{
    static const enum Species sSpecies[] = {
        SPECIES_SPOINK,
        SPECIES_GRUMPIG,
        SPECIES_WOBBUFFET,
    };
    enum Item item = ITEM_NONE;
    enum Species species = SPECIES_SPOINK;

    for (u32 speciesIndex = 0; speciesIndex < ARRAY_COUNT(sSpecies); speciesIndex++) {
        PARAMETRIZE { item = ITEM_NONE;        species = sSpecies[speciesIndex]; }
        PARAMETRIZE { item = ITEM_PEARL;       species = sSpecies[speciesIndex]; }
        PARAMETRIZE { item = ITEM_BIG_PEARL;   species = sSpecies[speciesIndex]; }
        PARAMETRIZE { item = ITEM_PEARL_STRING; species = sSpecies[speciesIndex]; }
    }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_PSYBEAM) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(species) { Item(item); Moves(MOVE_PSYBEAM); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PSYBEAM); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        for (u32 j = 0; j < ARRAY_COUNT(sSpecies); j++) {
            u32 index = j * 4;
            if (sSpecies[j] == SPECIES_WOBBUFFET) {
                EXPECT_EQ(results[index].damage, results[index + 1].damage);
                EXPECT_EQ(results[index].damage, results[index + 2].damage);
                EXPECT_EQ(results[index].damage, results[index + 3].damage);
            } else {
                EXPECT_MUL_EQ(results[index].damage, Q_4_12(1.2), results[index + 1].damage);
                EXPECT_MUL_EQ(results[index].damage, Q_4_12(1.3), results[index + 2].damage);
                EXPECT_MUL_EQ(results[index].damage, Q_4_12(1.5), results[index + 3].damage);
            }
        }
    }
}