#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Bass Quake uses Earthquake after a sound-based move")
{
    s16 earthquakeDamage;
    GIVEN {
        ASSUME(IsSoundMove(MOVE_ECHOED_VOICE));
        PLAYER(SPECIES_WHISMUR) { Ability(ABILITY_BASS_QUAKE); Moves(MOVE_ECHOED_VOICE); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_ECHOED_VOICE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ECHOED_VOICE, player);
        ABILITY_POPUP(player, ABILITY_BASS_QUAKE);
        MESSAGE("Whismur triggered an Earthquake!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        HP_BAR(opponent, captureDamage: &earthquakeDamage);
        NOT MESSAGE("Whismur used Earthquake!");
    } THEN {
        EXPECT_GT(earthquakeDamage, 0);
    }
}

SINGLE_BATTLE_TEST("Bass Quake does not activate if the sound move misses")
{
    GIVEN {
        ASSUME(IsSoundMove(MOVE_ECHOED_VOICE));
        PLAYER(SPECIES_WHISMUR) { Ability(ABILITY_BASS_QUAKE); Moves(MOVE_ECHOED_VOICE); Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); Item(ITEM_BRIGHT_POWDER); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_ECHOED_VOICE, hit: FALSE); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_BASS_QUAKE);
            MESSAGE("Whismur triggered an Earthquake!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        }
    }
}

SINGLE_BATTLE_TEST("Bass Quake does not activate after a non-sound move")
{
    GIVEN {
        ASSUME(!IsSoundMove(MOVE_SCRATCH));
        PLAYER(SPECIES_EXPLOUD) { Ability(ABILITY_BASS_QUAKE); Moves(MOVE_SCRATCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NONE_OF {
            ABILITY_POPUP(player, ABILITY_BASS_QUAKE);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, player);
        }
    }
}

DOUBLE_BATTLE_TEST("Bass Quake does not activate when another battler uses a sound-based move")
{
    GIVEN {
        ASSUME(IsSoundMove(MOVE_ECHOED_VOICE));
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_ECHOED_VOICE); Speed(5); }
        PLAYER(SPECIES_WHISMUR) { Ability(ABILITY_BASS_QUAKE); Moves(MOVE_CELEBRATE); Speed(4); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_ECHOED_VOICE, target: opponentLeft); MOVE(playerRight, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ECHOED_VOICE, playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        NONE_OF {
            ABILITY_POPUP(playerRight, ABILITY_BASS_QUAKE);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, playerRight);
        }
    }
}