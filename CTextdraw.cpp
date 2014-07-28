#include "CTextdraw.h"
void CTextdraw::ShowForAll(void) {
	functions->ShowTextdrawToAll(this->nTextdrawId);
}

void CTextdraw::ShowForPlayer(CPlayer * pPlayer) {
	functions->ShowTextdrawToPlayer(this->nTextdrawId, pPlayer->GetID());
}

void CTextdraw::HideFromAll(void) {
	functions->HideTextdrawFromAll(this->nTextdrawId);
}

void CTextdraw::HideFromPlayer(CPlayer * pPlayer) {
	functions->HideTextdrawFromPlayer(this->nTextdrawId, pPlayer->GetID());
}

void CTextdraw::SetPositionForAll(int x, int y) {
	functions->MoveTextdrawForAll(this->nTextdrawId, x, y);
}

void CTextdraw::SetPositionForPlayer(CPlayer * pPlayer, int x, int y) {
	functions->MoveTextdrawForPlayer(this->nTextdrawId, pPlayer->GetID(), x, y);
}

void CTextdraw::SetColourForAll(unsigned int colour) {
	functions->SetTextdrawColourForAll(this->nTextdrawId, colour);
}

void CTextdraw::SetColourForPlayer(CPlayer * pPlayer, unsigned int colour) {
	functions->SetTextdrawColourForPlayer(this->nTextdrawId, pPlayer->GetID(), colour);
}

void CTextdraw::Delete() {
	functions->DestroyTextdraw(this->nTextdrawId);
	delete this;
}

void RegisterTextdraw()
{
	Class<CTextdraw> c(v, "CTextdraw_INTERNAL");
	c
		.Func(_SC("ShowForAll"), &CTextdraw::ShowForAll, 1, "x")
		.Func(_SC("ShowForPlayer"), &CTextdraw::ShowForPlayer, 2, "xx")
		.Func(_SC("HideFromAll"), &CTextdraw::HideFromAll, 1, "x")
		.Func(_SC("HideFromPlayer"), &CTextdraw::HideFromPlayer, 2, "xx")
		.Func(_SC("SetPosForAll"), &CTextdraw::SetPositionForAll, 3, "xii")
		.Func(_SC("SetPosForPlayer"), &CTextdraw::SetPositionForPlayer, 4, "xxii")
		.Func(_SC("SetColourForAll"), &CTextdraw::SetColourForAll, 2, "xi")
		.Func(_SC("SetColourForPlayer"), &CTextdraw::SetColourForPlayer, 3, "xxi")
		.Func(_SC("Delete"), &CTextdraw::Delete, 1, "x");

	RootTable(v).Bind(_SC("CTextdraw"), c);
}
