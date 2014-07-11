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
		.Func(_SC("ShowForAll"), &CTextdraw::ShowForAll)
		.Func(_SC("ShowForPlayer"), &CTextdraw::ShowForPlayer)
		.Func(_SC("HideFromAll"), &CTextdraw::HideFromAll)
		.Func(_SC("HideFromPlayer"), &CTextdraw::HideFromPlayer)
		.Func(_SC("SetPosForAll"), &CTextdraw::SetPositionForAll)
		.Func(_SC("SetPosForPlayer"), &CTextdraw::SetPositionForPlayer)
		.Func(_SC("SetColourForAll"), &CTextdraw::SetColourForAll)
		.Func(_SC("SetColourForPlayer"), &CTextdraw::SetColourForPlayer)
		.Func(_SC("Delete"), &CTextdraw::Delete);

	RootTable(v).Bind(_SC("CTextdraw"), c);
}