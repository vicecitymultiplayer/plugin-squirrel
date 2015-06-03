#include "CTextdraw.h"
void CTextdraw::ShowForAll(void) {
	functions->ShowTextdraw(this->nTextdrawId, -1);
}

void CTextdraw::ShowForPlayer(CPlayer * pPlayer) {
	functions->ShowTextdraw(this->nTextdrawId, pPlayer->GetID());
}

void CTextdraw::HideFromAll(void) {
	functions->HideTextdraw(this->nTextdrawId, -1);
}

void CTextdraw::HideFromPlayer(CPlayer * pPlayer) {
	functions->HideTextdraw(this->nTextdrawId, pPlayer->GetID());
}

void CTextdraw::SetPositionForAll(int x, int y) {
	functions->MoveTextdraw(this->nTextdrawId, -1, x, y);
}

void CTextdraw::SetPositionForPlayer(CPlayer * pPlayer, int x, int y) {
	functions->MoveTextdraw(this->nTextdrawId, pPlayer->GetID(), x, y);
}

void CTextdraw::SetColourForAll(unsigned int colour) {
	functions->SetTextdrawColour(this->nTextdrawId, -1, colour);
}

void CTextdraw::SetColourForPlayer(CPlayer * pPlayer, unsigned int colour) {
	functions->SetTextdrawColour(this->nTextdrawId, pPlayer->GetID(), colour);
}

void CTextdraw::SetRelativityForAll(bool bIsRelative) {
	functions->SetTextdrawRelativity(this->nTextdrawId, -1, bIsRelative);
}

void CTextdraw::SetRelativityForPlayer(CPlayer * pPlayer, bool bIsRelative) {
	functions->SetTextdrawRelativity(this->nTextdrawId, pPlayer->GetID(), bIsRelative);
}

void CTextdraw::Delete() {
	functions->DestroyTextdraw(this->nTextdrawId);
	delete this;
}

void RegisterTextdraw()
{
	Class<CTextdraw> c(v, "CTextdraw_INTERNAL");
	c
		.Func(_SC("ShowForAll"), &CTextdraw::ShowForAll )
		.Func(_SC("ShowForPlayer"), &CTextdraw::ShowForPlayer )
		.Func(_SC("HideFromAll"), &CTextdraw::HideFromAll )
		.Func(_SC("HideFromPlayer"), &CTextdraw::HideFromPlayer )
		.Func(_SC("SetPosForAll"), &CTextdraw::SetPositionForAll )
		.Func(_SC("SetPosForPlayer"), &CTextdraw::SetPositionForPlayer )
		.Func(_SC("SetColourForAll"), &CTextdraw::SetColourForAll )
		.Func(_SC("SetColourForPlayer"), &CTextdraw::SetColourForPlayer )
		.Func(_SC("SetRelativeForAll"), &CTextdraw::SetRelativityForAll )
		.Func(_SC("SetRelativeForPlayer"), &CTextdraw::SetRelativityForPlayer )
		.Func(_SC("Delete"), &CTextdraw::Delete );

	RootTable(v).Bind(_SC("CTextdraw"), c);
}
