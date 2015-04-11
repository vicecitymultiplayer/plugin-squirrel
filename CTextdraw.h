#include "main.h"
#include "CPlayer.h"
#pragma once

class CTextdraw
{
	public:
		void ShowForAll(void);
		void ShowForPlayer(CPlayer * pPlayer);

		void HideFromAll(void);
		void HideFromPlayer(CPlayer * pPlayer);

		void SetPositionForAll(int x, int y);
		void SetPositionForPlayer(CPlayer * pPlayer, int x, int y);

		void SetColourForAll(unsigned int alpha);
		void SetColourForPlayer(CPlayer * pPlayer, unsigned int colour);
		
		void SetRelativityForAll(bool bIsRelative);
		void SetRelativityForPlayer(CPlayer * pPlayer, bool bIsRelative);

		void Delete(void);

	public:
		int nTextdrawId;
};

void RegisterTextdraw();