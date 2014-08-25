#include "CSprite.h"
void CSprite::ShowForAll(void) {
	functions->ShowSprite(this->nSpriteId, -1);
}

void CSprite::ShowForPlayer(CPlayer * pPlayer) {
	functions->ShowSprite(this->nSpriteId, pPlayer->GetID());
}

void CSprite::HideFromAll(void) {
	functions->HideSprite(this->nSpriteId, -1);
}

void CSprite::HideFromPlayer(CPlayer * pPlayer) {
	functions->HideSprite(this->nSpriteId, pPlayer->GetID());
}

void CSprite::SetPositionForAll(int x, int y) {
	functions->MoveSprite(this->nSpriteId, -1, x, y);
}

void CSprite::SetPositionForPlayer(CPlayer * pPlayer, int x, int y) {
	functions->MoveSprite(this->nSpriteId, pPlayer->GetID(), x, y);
}

void CSprite::SetRotationCenterForAll(int x, int y) {
	functions->SetSpriteCenter(this->nSpriteId, -1, x, y);
}

void CSprite::SetRotationCenterForPlayer(CPlayer * pPlayer, int x, int y) {
	functions->SetSpriteCenter(this->nSpriteId, pPlayer->GetID(), x, y);
}

void CSprite::SetRotationForAll(float rotation) {
	functions->RotateSprite(this->nSpriteId, -1, rotation);
}

void CSprite::SetRotationForPlayer(CPlayer * pPlayer, float rotation) {
	functions->RotateSprite(this->nSpriteId, pPlayer->GetID(), rotation);
}

void CSprite::SetAlphaForAll(unsigned int alpha) {
	functions->SetSpriteAlpha(this->nSpriteId, -1, (alpha > 255 ? 255 : alpha));
}

void CSprite::SetAlphaForPlayer(CPlayer * pPlayer, unsigned int alpha) {
	functions->SetSpriteAlpha(this->nSpriteId, pPlayer->GetID(), (alpha > 255 ? 255 : alpha));
}

void CSprite::Delete() {
	functions->DestroySprite(this->nSpriteId);
	delete this;
}

void RegisterSprite()
{
	Class<CSprite> c(v, "CSprite_INTERNAL");
	c
		.Func(_SC("ShowForAll"), &CSprite::ShowForAll, 1, "x")
		.Func(_SC("ShowForPlayer"), &CSprite::ShowForPlayer, 2, "xx")
		.Func(_SC("HideFromAll"), &CSprite::HideFromAll, 1, "x")
		.Func(_SC("HideFromPlayer"), &CSprite::HideFromPlayer, 2, "xx")
		.Func(_SC("SetPosForAll"), &CSprite::SetPositionForAll, 3, "xii")
		.Func(_SC("SetPosForPlayer"), &CSprite::SetPositionForPlayer, 4, "xxii")
		.Func(_SC("SetCenterForAll"), &CSprite::SetRotationCenterForAll, 3, "xii")
		.Func(_SC("SetCenterForPlayer"), &CSprite::SetRotationCenterForPlayer, 4, "xxii")
		.Func(_SC("RotateForAll"), &CSprite::SetRotationForAll, 2, "xn")
		.Func(_SC("RotateForPlayer"), &CSprite::SetRotationForPlayer, 3, "xxn")
		.Func(_SC("SetAlphaForAll"), &CSprite::SetAlphaForAll, 2, "xi")
		.Func(_SC("SetAlphaForPlayer"), &CSprite::SetAlphaForPlayer, 3, "xxi")
		.Func(_SC("Delete"), &CSprite::Delete, 1, "x");

	RootTable(v).Bind(_SC("CSprite"), c);
}
