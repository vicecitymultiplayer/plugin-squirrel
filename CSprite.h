#include "main.h"
#include "CPlayer.h"
#pragma once

class CSprite
{
	public:
		void ShowForAll(void);
		void ShowForPlayer(CPlayer * pPlayer);

		void HideFromAll(void);
		void HideFromPlayer(CPlayer * pPlayer);

		void SetPositionForAll(float x, float y);
		void SetPositionForPlayer(CPlayer * pPlayer, float x, float y);

		void SetRotationCenterForAll(float x, float y);
		void SetRotationCenterForPlayer(CPlayer * pPlayer, float x, float y);

		void SetRotationForAll(float rotation);
		void SetRotationForPlayer(CPlayer * pPlayer, float rotation);

		void SetAlphaForAll(unsigned int alpha);
		void SetAlphaForPlayer(CPlayer * pPlayer, unsigned int alpha);
		
		void Delete(void);

	public:
		int nSpriteId;
};

void RegisterSprite();