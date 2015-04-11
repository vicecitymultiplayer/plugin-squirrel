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

		void SetPositionForAll(int x, int y);
		void SetPositionForPlayer(CPlayer * pPlayer, int x, int y);

		void SetRotationCenterForAll(int x, int y);
		void SetRotationCenterForPlayer(CPlayer * pPlayer, int x, int y);

		void SetRotationForAll(float rotation);
		void SetRotationForPlayer(CPlayer * pPlayer, float rotation);

		void SetAlphaForAll(unsigned int alpha);
		void SetAlphaForPlayer(CPlayer * pPlayer, unsigned int alpha);
		
		void SetRelativityForAll(bool bIsRelative);
		void SetRelativityForPlayer(CPlayer * pPlayer, bool bIsRelative);

		void Delete(void);

	public:
		int nSpriteId;
};

void RegisterSprite();