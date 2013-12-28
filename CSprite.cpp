#include "CSprite.h"
void CSprite::ShowForAll(void) {
	functions->ShowSpriteToAll(this->nSpriteId);
}

void CSprite::ShowForPlayer(CPlayer * pPlayer) {
	functions->ShowSpriteToPlayer(this->nSpriteId, pPlayer->GetID());
}

void CSprite::HideFromAll(void) {
	functions->HideSpriteFromAll(this->nSpriteId);
}

void CSprite::HideFromPlayer(CPlayer * pPlayer) {
	functions->HideSpriteFromPlayer(this->nSpriteId, pPlayer->GetID());
}

void CSprite::SetPositionForAll(int x, int y) {
	functions->MoveSpriteForAll(this->nSpriteId, x, y);
}

void CSprite::SetPositionForPlayer(CPlayer * pPlayer, int x, int y) {
	functions->MoveSpriteForPlayer(this->nSpriteId, pPlayer->GetID(), x, y);
}

void CSprite::SetRotationCenterForAll(int x, int y) {
	functions->SetSpriteCenterForAll(this->nSpriteId, x, y);
}

void CSprite::SetRotationCenterForPlayer(CPlayer * pPlayer, int x, int y) {
	functions->SetSpriteCenterForPlayer(this->nSpriteId, pPlayer->GetID(), x, y);
}

void CSprite::SetRotationForAll(float rotation) {
	functions->RotateSpriteForAll(this->nSpriteId, rotation);
}

void CSprite::SetRotationForPlayer(CPlayer * pPlayer, float rotation) {
	functions->RotateSpriteForPlayer(this->nSpriteId, pPlayer->GetID(), rotation);
}

void CSprite::SetAlphaForAll(unsigned int alpha) {
	functions->SetSpriteAlphaForAll(this->nSpriteId, (alpha > 255 ? 255 : alpha));
}

void CSprite::SetAlphaForPlayer(CPlayer * pPlayer, unsigned int alpha) {
	functions->SetSpriteAlphaForPlayer(this->nSpriteId, pPlayer->GetID(), (alpha > 255 ? 255 : alpha));
}

void CSprite::Delete() {
	functions->DestroySprite(this->nSpriteId);
	delete this;
}

void RegisterSprite()
{
	Class<CSprite> c(v);
	c
		.Func(_SC("ShowForAll"), &CSprite::ShowForAll)
		.Func(_SC("ShowForPlayer"), &CSprite::ShowForPlayer)
		.Func(_SC("HideFromAll"), &CSprite::HideFromAll)
		.Func(_SC("HideFromPlayer"), &CSprite::HideFromPlayer)
		.Func(_SC("SetPosForAll"), &CSprite::SetPositionForAll)
		.Func(_SC("SetPosForPlayer"), &CSprite::SetPositionForPlayer)
		.Func(_SC("SetCenterForAll"), &CSprite::SetRotationCenterForAll)
		.Func(_SC("SetCenterForPlayer"), &CSprite::SetRotationCenterForPlayer)
		.Func(_SC("RotateForAll"), &CSprite::SetRotationForAll)
		.Func(_SC("RotateForPlayer"), &CSprite::SetRotationForPlayer)
		.Func(_SC("SetAlphaForAll"), &CSprite::SetAlphaForAll)
		.Func(_SC("SetAlphaForPlayer"), &CSprite::SetAlphaForPlayer);

	RootTable(v).Bind(_SC("CSprite"), c);
}