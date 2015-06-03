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

void CSprite::SetRelativityForAll(bool bIsRelative) {
	functions->SetSpriteRelativity(this->nSpriteId, -1, bIsRelative);
}

void CSprite::SetRelativityForPlayer(CPlayer * pPlayer, bool bIsRelative) {
	functions->SetSpriteRelativity(this->nSpriteId, pPlayer->GetID(), bIsRelative);
}

void CSprite::Delete() {
	functions->DestroySprite(this->nSpriteId);
	delete this;
}

void RegisterSprite()
{
	Class<CSprite> c(v, "CSprite_INTERNAL");
	c
		.Func(_SC("ShowForAll"), &CSprite::ShowForAll )
		.Func(_SC("ShowForPlayer"), &CSprite::ShowForPlayer )
		.Func(_SC("HideFromAll"), &CSprite::HideFromAll )
		.Func(_SC("HideFromPlayer"), &CSprite::HideFromPlayer )
		.Func(_SC("SetPosForAll"), &CSprite::SetPositionForAll )
		.Func(_SC("SetPosForPlayer"), &CSprite::SetPositionForPlayer )
		.Func(_SC("SetCenterForAll"), &CSprite::SetRotationCenterForAll )
		.Func(_SC("SetCenterForPlayer"), &CSprite::SetRotationCenterForPlayer )
		.Func(_SC("RotateForAll"), &CSprite::SetRotationForAll )
		.Func(_SC("RotateForPlayer"), &CSprite::SetRotationForPlayer )
		.Func(_SC("SetAlphaForAll"), &CSprite::SetAlphaForAll )
		.Func(_SC("SetAlphaForPlayer"), &CSprite::SetAlphaForPlayer )
		.Func(_SC("SetRelativeForAll"), &CSprite::SetRelativityForAll )
		.Func(_SC("SetRelativeForPlayer"), &CSprite::SetRelativityForPlayer )
		.Func(_SC("Delete"), &CSprite::Delete );

	RootTable(v).Bind(_SC("CSprite"), c);
}
