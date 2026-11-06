#ifndef GUARD_SHOP_H
#define GUARD_SHOP_H

extern struct ItemSlot gMartPurchaseHistory[3];

void CreatePokemartMenu(const u16 *itemsForSale);
void OpenPokemartMenuAfterService(void);
void CreateDecorationShop1Menu(const u16 *itemsForSale);
void CreateDecorationShop2Menu(const u16 *itemsForSale);
void FieldCB_ReturnToPokemartAfterService(void);
bool8 CB2_ReturnToPokemartAfterService(void);
void CB2_ExitSellMenu(void);

#endif // GUARD_SHOP_H
