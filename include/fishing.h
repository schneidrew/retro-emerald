#ifndef GUARD_FISHING_H
#define GUARD_FISHING_H

void StartFishing(void);
void UpdateChainFishingStreak();
u32 CalculateChainFishingShinyRolls(void);
bool32 ShouldUseFishingEnvironmentInBattle();

#endif // GUARD_FISHING_H