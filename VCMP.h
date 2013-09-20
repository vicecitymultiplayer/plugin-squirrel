/*
   Project: Vice City Multiplayer 0.4 Server / Plugin kit
   File: plugin.h

   Copyright 2011 Ago Allikmaa (maxorator)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#if !defined _MSC_VER || _MSC_VER >= 1600
#include <stdint.h>
#endif

struct ServerSettings {
	unsigned int uStructSize;
	char szServerName[128];
	unsigned int uMaxPlayers;
	unsigned int uPort;
	unsigned int uFlags;
};

struct PluginInfo {
	unsigned int uStructSize;
	int nPluginId;
	char szName[32];
	unsigned int uPluginVer;
};

//PLUGIN SYSTEM
typedef unsigned int (*PFunc_GetServerVersion) (void);
typedef unsigned int (*PFunc_GetServerSettings) (ServerSettings* pstSettings);
typedef unsigned int (*PFunc_ExportFunctions) (int nPluginId, void** ppFunctionList, unsigned int uSize);
typedef unsigned int (*PFunc_GetNumberOfPlugins) (void);
typedef unsigned int (*PFunc_GetPluginInfo) (int nPluginId, PluginInfo* pstPluginInfo);
typedef int (*PFunc_FindPlugin) (char* pszPluginName);
typedef void** (*PFunc_GetPluginExports) (int nPluginId, unsigned int* puSize);
typedef int (*PFunc_GetTime) (uint64_t* pullTime);

//MESSAGES
typedef int (*PFunc_printf) (const char* pszFormat, ...);
typedef int (*PFunc_SendCustomCommand) (unsigned int uCmdType, const char* pszFormat, ...);
typedef int (*PFunc_SendClientMessage) (int nPlayerId, unsigned int uColour, const char* pszFormat, ...);
typedef int (*PFunc_SendGameMessage) (int nPlayerId, int nType, const char* pszFormat, ... );

//SERVER SETTINGS
typedef int (*PFunc_SetServerName) (const char* pszText);
typedef int (*PFunc_GetServerName) (char* pszBuffer, int nBufferLen);
typedef int (*PFunc_SetMaxPlayers) (int nMaxPlayers);
typedef int (*PFunc_GetMaxPlayers) (void);
typedef int (*PFunc_SetServerPassword) (char* pszBuffer);
typedef int (*PFunc_GetServerPassword) (char* pszBuffer, int nBufferLen);
typedef int (*PFunc_SetGameModeText) (const char* pszText);
typedef int (*PFunc_GetGameModeText) (char* pszBuffer, int nBufferLen);

//WORLD: settings
typedef int (*PFunc_SetWorldBounds) (float fMaxX, float fMinX, float fMaxY, float fMinY);
typedef int (*PFunc_GetWorldBounds) (float* pfMaxX, float* pfMinX, float* pfMaxY, float* pfMinY);
typedef int (*PFunc_SetWastedSettings) (unsigned int dwDeathTimer, unsigned int dwFadeTimer, float fFadeInSpeed, float fFadeOutSpeed, unsigned int dwFadeColour, unsigned int dwCorpseFadeStart, unsigned int dwCorpseFadeTime);
typedef int (*PFunc_GetWastedSettings) (unsigned int* pdwDeathTimer, unsigned int* pdwFadeTimer, float* pfFadeInSpeed, float* pfFadeOutSpeed, unsigned int* pdwFadeColour, unsigned int* pdwCorpseFadeStart, unsigned int* pdwCorpseFadeTime);
typedef int (*PFunc_SetTimeRate) (unsigned int uTimeRate);
typedef unsigned int (*PFunc_GetTimeRate) (void);
typedef int (*PFunc_SetHour) (int nHour);
typedef int (*PFunc_GetHour) (void);
typedef int (*PFunc_SetMinute) (int nMinute);
typedef int (*PFunc_GetMinute) (void);
typedef int (*PFunc_SetWeather) (int nWeather);
typedef int (*PFunc_GetWeather) (void);
typedef int (*PFunc_SetGravity) (float fGravity);
typedef float (*PFunc_GetGravity) (void);
typedef int (*PFunc_SetGamespeed) (float fGamespeed);
typedef float (*PFunc_GetGamespeed) (void);
typedef int (*PFunc_SetWaterLevel) (float fWaterLevel);
typedef float (*PFunc_GetWaterLevel) (void);
typedef int (*PFunc_SetMaxHeight) (float fHeight);
typedef float (*PFunc_GetMaxHeight) (void);

//WORLD: toggles
typedef int (*PFunc_ToggleSyncFrameLimiter) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledSyncFrameLimiter) (void);
typedef int (*PFunc_ToggleFrameLimiter) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledFrameLimiter) (void);
typedef int (*PFunc_ToggleTaxiBoostJump) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledTaxiBoostJump) (void);
typedef int (*PFunc_ToggleDriveOnWater) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledDriveOnWater) (void);
typedef int (*PFunc_ToggleFastSwitch) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledFastSwitch) (void);
typedef int (*PFunc_ToggleFriendlyFire) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledFriendlyFire) (void);
typedef int (*PFunc_ToggleDisableDriveby) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledDisableDriveby) (void);
typedef int (*PFunc_TogglePerfectHandling) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPerfectHandling) (void);
typedef int (*PFunc_ToggleFlyingCars) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledFlyingCars) (void);
typedef int (*PFunc_ToggleJumpSwitch) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledJumpSwitch) (void);
typedef int (*PFunc_ToggleShowMarkers) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledShowMarkers) (void);
typedef int (*PFunc_ToggleStuntBike) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledStuntBike) (void);
typedef int (*PFunc_ToggleShootInAir) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledShootInAir) (void);
typedef int (*PFunc_ToggleShowNametags) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledShowNametags) (void);
typedef int (*PFunc_ToggleJoinMessages) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledJoinMessages) (void);
typedef int (*PFunc_ToggleDeathMessages) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledDeathMessages) (void);
typedef int (*PFunc_ToggleChatTagsByDefaultEnabled) (unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledChatTagsByDefault) (void);

//MISC
typedef int (*PFunc_CreateExplosion) (int nWorldId, int nType, float fPosX, float fPosY, float fPosZ, int nSourcePlayerId, unsigned int bGroundLevel);
typedef int (*PFunc_PlaySound) (int nWorldId, int nSoundId, float fPosX, float fPosY, float fPosZ);
typedef int (*PFunc_HideMapObject) (int nModelId, int nTenthX, int nTenthY, int nTenthZ);
typedef int (*PFunc_ShowMapObject) (int nModelId, int nTenthX, int nTenthY, int nTenthZ);
typedef int (*PFunc_ShowAllMapObjects) (void);

//KEYBINDS
typedef int (*PFunc_GetKeyBindUnusedSlot) (void);
typedef unsigned int (*PFunc_GetKeyBindData) (int nBindId, unsigned int* pbOnRelease, int* nKeyOne, int* pnKeyTwo, int* pnKeyThree);
typedef unsigned int (*PFunc_RegisterKeyBind) (int nBindId, unsigned int bOnRelease, int nKeyOne, int nKeyTwo, int nKeyThree);
typedef unsigned int (*PFunc_RemoveKeyBind) (int nBindId);
typedef void (*PFunc_RemoveAllKeyBinds) (void);

//BLIPS
typedef int (*PFunc_CreateCoordBlip) (int nIndex, int nWorld, float fX, float fY, float fZ, int nScale, unsigned int uColour, int nSprite);
typedef void (*PFunc_DestroyCoordBlip) (int nIndex);
typedef unsigned int (*PFunc_GetCoordBlipInfo) (int nIndex, int* pnWorld, float* pfX, float* pfY, float* pfZ, int* pnScale, unsigned int* puColour, int* pnSprite);

//CLASSES
typedef int (*PFunc_SetUseClasses) (unsigned int bToggle);
typedef unsigned int (*PFunc_GetUseClasses) (void);
typedef int (*PFunc_GetPlayerClass) (int nPlayerId);
typedef int (*PFunc_AddPlayerClass) (int nTeamId, unsigned int uColour, int nModelId, float fSpawnX, float fSpawnY, float fSpawnZ, float fAngleZ, int nWep1, int nWep1Ammo, int nWep2, int nWep2Ammo, int nWep3, int nWep3Ammo);
typedef int (*PFunc_SetSpawnPlayerPos) (float fPosX, float fPosY, float fPosZ);
typedef int (*PFunc_SetSpawnCameraPos) (float fPosX, float fPosY, float fPosZ);
typedef int (*PFunc_SetSpawnCameraLookAt) (float fPosX, float fPosY, float fPosZ);

//ADMIN
typedef unsigned int (*PFunc_IsPlayerAdmin) (int nPlayerId);
typedef int (*PFunc_SetPlayerAdmin) (int nPlayerId, unsigned int bToggle);
typedef int (*PFunc_GetPlayerIP) (int nPlayerId, char* pszBuffer, int nBufferLen);
typedef int (*PFunc_KickPlayer) (int nPlayerId);
typedef int (*PFunc_BanPlayer) (int nPlayerId);
typedef int (*PFunc_BanIP) (char* pszIPAddress);
typedef int (*PFunc_UnbanIP) (char* pszIPAddress);
typedef unsigned int (*PFunc_IsIPBanned) (char* pszIPAddress);

//PLAYERS: basic
typedef int (*PFunc_GetPlayerIDFromName) (char* pszName);
typedef unsigned int (*PFunc_IsPlayerConnected) (int nPlayerId);
typedef unsigned int (*PFunc_IsPlayerSpawned) (int nPlayerId);
typedef unsigned int (*PFunc_IsPlayerStreamedForPlayer) (int nCheckPlayer, int nPlayerId);
typedef unsigned int (*PFunc_GetPlayerKey) (int nPlayerId);
typedef int (*PFunc_SetPlayerWorld) (int nPlayerId, int nWorld);
typedef int (*PFunc_GetPlayerWorld) (int nPlayerId);
typedef int (*PFunc_SetPlayerSecWorld) (int nPlayerId, int nSecWorld);
typedef int (*PFunc_GetPlayerSecWorld) (int nPlayerId);
typedef int (*PFunc_GetPlayerUniqueWorld) (int nPlayerId);
typedef unsigned int (*PFunc_IsPlayerWorldCompatible) (int nPlayerId, int nWorld);
typedef int (*PFunc_GetPlayerState) (int nPlayerId);
typedef int (*PFunc_GetPlayerName) (int nPlayerId, char* szBuffer, int nBufferLen);
typedef int (*PFunc_SetPlayerTeam) (int nPlayerId, int nTeamId);
typedef int (*PFunc_GetPlayerTeam) (int nPlayerId);
typedef int (*PFunc_SetPlayerSkin) (int nPlayerId, int nSkinId);
typedef int (*PFunc_GetPlayerSkin) (int nPlayerId);
typedef int (*PFunc_SetPlayerColour) (int nPlayerId, unsigned int uColour);
typedef unsigned int (*PFunc_GetPlayerColour) (int nPlayerId);
typedef int (*PFunc_ForcePlayerSpawn) (int nPlayerId);
typedef int (*PFunc_ForcePlayerSelect) (int nPlayerId);
typedef int (*PFunc_ForceAllSelect) (void);

//PLAYERS: score, ping, money, typing
typedef int (*PFunc_GivePlayerMoney) (int nPlayerId, int nAmount);
typedef int (*PFunc_SetPlayerMoney) (int nPlayerId, int nAmount);
typedef int (*PFunc_GetPlayerMoney) (int nPlayerId);
typedef int (*PFunc_SetPlayerScore) (int nPlayerId, int nScore);
typedef int (*PFunc_GetPlayerScore) (int nPlayerId);
typedef int (*PFunc_GetPlayerPing) (int nPlayerId);
typedef unsigned int (*PFunc_IsPlayerTyping) (int nPlayerId);

//PLAYERS: health and location
typedef int (*PFunc_SetPlayerHealth) (int nPlayerId, float fHealth);
typedef float (*PFunc_GetPlayerHealth) (int nPlayerId);
typedef int (*PFunc_SetPlayerArmour) (int nPlayerId, float fArmour);
typedef float (*PFunc_GetPlayerArmour) (int nPlayerId);
typedef int (*PFunc_SetPlayerImmunityFlags) (int nPlayerId, int nFlags);
typedef int (*PFunc_GetPlayerImmunityFlags) (int nPlayerId);
typedef int (*PFunc_SetPlayerPos) (int nPlayerId, float fPosX, float fPosY, float fPosZ);
typedef int (*PFunc_GetPlayerPos) (int nPlayerId, float* pfPosX, float* pfPosY, float* pfPosZ);
typedef int (*PFunc_SetPlayerSpeed) (int nPlayerId, float fSpeedX, float fSpeedY, float fSpeedZ);
typedef int (*PFunc_GetPlayerSpeed) (int nPlayerId, float* pfSpeedX, float* pfSpeedY, float* pfSpeedZ);
typedef int (*PFunc_AddPlayerSpeed) (int nPlayerId, float fSpeedX, float fSpeedY, float fSpeedZ);
typedef int (*PFunc_SetPlayerHeading) (int nPlayerId, float fAngleZ);
typedef float (*PFunc_GetPlayerHeading) (int nPlayerId);
typedef int (*PFunc_SetPlayerAlpha) (int nPlayerId, int nAlpha, int nFadeTime);
typedef int (*PFunc_GetPlayerAlpha) (int nPlayerId);

//PLAYERS: vehicle
typedef int (*PFunc_PutPlayerInVehicle) (int nPlayerId, int nVehicleId, int nSlot, unsigned int bMakeRoom, unsigned int bWarp);
typedef int (*PFunc_RemovePlayerFromVehicle) (int nPlayerId);
typedef int (*PFunc_GetPlayerInVehicleStatus) (int nPlayerId);
typedef int (*PFunc_GetPlayerInVehicleSlot) (int nPlayerId);
typedef int (*PFunc_GetPlayerVehicleID) (int nPlayerId);

//PLAYERS: toggles
typedef int (*PFunc_TogglePlayerControllable) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerControllable) (int nPlayerId);
typedef int (*PFunc_TogglePlayerDriveby) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerDriveby) (int nPlayerId);
typedef int (*PFunc_TogglePlayerWhiteScanlines) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerWhiteScanlines) (int nPlayerId);
typedef int (*PFunc_TogglePlayerGreenScanlines) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerGreenScanlines) (int nPlayerId);
typedef int (*PFunc_TogglePlayerWidescreen) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerWidescreen) (int nPlayerId);
typedef int (*PFunc_TogglePlayerShowMarkers) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerShowMarkers) (int nPlayerId);
typedef int (*PFunc_TogglePlayerAttackPriv) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerAttackPriv) (int nPlayerId);
typedef int (*PFunc_TogglePlayerHasMarker) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerHasMarker) (int nPlayerId);
typedef int (*PFunc_TogglePlayerChatTagsEnabled) (int nPlayerId, unsigned int bToggle);
typedef unsigned int (*PFunc_EnabledPlayerChatTags) (int nPlayerId);

//PLAYERS: weapons
typedef int (*PFunc_GivePlayerWeapon) (int nPlayerId, int nWeaponId, int nAmmo);
typedef int (*PFunc_SetPlayerWeapon) (int nPlayerId, int nWeaponId, int nAmmo);
typedef int (*PFunc_GetPlayerWeapon) (int nPlayerId);
typedef int (*PFunc_GetPlayerWeaponAmmo) (int nPlayerId);
typedef int (*PFunc_SetPlayerWeaponSlot) (int nPlayerId, int nSlot);
typedef int (*PFunc_GetPlayerWeaponSlot) (int nPlayerId);
typedef int (*PFunc_GetPlayerWeaponAtSlot) (int nPlayerId, int nSlot);
typedef int (*PFunc_GetPlayerAmmoAtSlot) (int nPlayerId, int nSlot);
typedef int (*PFunc_RemovePlayerWeapon) (int nPlayerId, int nWeaponId);
typedef int (*PFunc_RemoveAllWeapons) (int nPlayerId);

//PLAYERS: camera
typedef int (*PFunc_SetCameraPosition) (int nPlayerId, float fPosX, float fPosY, float fPosZ, float fLookX, float fLookY, float fLookZ);
typedef int (*PFunc_RestoreCamera) (int nPlayerId);
typedef unsigned int (*PFunc_IsCameraLocked) (int nPlayerId);

//PLAYERS: misc
typedef int (*PFunc_SetPlayerAnimation) (int nPlayerId, int nGroupId, int nAnimationId);
typedef int (*PFunc_SetPlayerWantedLevel) (int nPlayerId, int nLevel);
typedef int (*PFunc_GetPlayerStandingOnVehicle) (int nPlayerId);
typedef int (*PFunc_GetPlayerStandingOnObject) (int nPlayerId);
typedef unsigned int (*PFunc_IsPlayerAway) (int nPlayerId);
typedef int (*PFunc_GetPlayerSpectateTarget) (int nPlayerId);
typedef int (*PFunc_SetPlayerSpectateTarget) (int nPlayerId, int nTargetId);

//VEHICLES
typedef int (*PFunc_CreateVehicle) (int nModelId, int nWorld, float fPosX, float fPosY, float fPosZ, float fAngleZ, int nColour1, int nColour2);
typedef int (*PFunc_DeleteVehicle) (int nVehicleId);
typedef int (*PFunc_GetVehicleSyncSource) (int nVehicleId);
typedef int (*PFunc_GetVehicleSyncType) (int nVehicleId);
typedef unsigned int (*PFunc_IsVehicleStreamedForPlayer) (int nVehicleId, int nPlayerId);
typedef int (*PFunc_SetVehicleWorld) (int nVehicleId, int nWorld);
typedef int (*PFunc_GetVehicleWorld) (int nVehicleId);
typedef int (*PFunc_GetVehicleModel) (int nVehicleId);
typedef int (*PFunc_GetVehicleOccupant) (int nVehicleId, int nSlotIndex);
typedef int (*PFunc_RespawnVehicle) (int nVehicleId);
typedef int (*PFunc_SetVehicleImmunityFlags) (int nVehicleId, int nImmuFlags);
typedef int (*PFunc_GetVehicleImmunityFlags) (int nVehicleId);
typedef int (*PFunc_KillVehicle) (int nVehicleId);
typedef unsigned int (*PFunc_IsVehicleWrecked) (int nVehicleId);
typedef int (*PFunc_SetVehiclePos) (int nVehicleId, float fPosX, float fPosY, float fPosZ, unsigned int bRemoveOccupants);
typedef int (*PFunc_GetVehiclePos) (int nVehicleId, float* pfPosX, float* pfPosY, float* pfPosZ);
typedef int (*PFunc_SetVehicleRot) (int nVehicleId, float fX, float fY, float fZ, float fW);
typedef int (*PFunc_SetVehicleRotEuler) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_GetVehicleRot) (int nVehicleId, float* pfX, float* pfY, float *pfZ, float *pfW);
typedef int (*PFunc_GetVehicleRotEuler) (int nVehicleId, float* pfX, float* pfY, float *pfZ);
typedef int (*PFunc_SetVehicleSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_GetVehicleSpeed) (int nVehicleId, float* pfX, float* pfY, float* pfZ);
typedef int (*PFunc_AddVehicleSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_SetVehicleRelSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_GetVehicleRelSpeed) (int nVehicleId, float* pfX, float* pfY, float* pfZ);
typedef int (*PFunc_AddVehicleRelSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_SetVehicleTurnSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_GetVehicleTurnSpeed) (int nVehicleId, float* pfX, float* pfY, float* pfZ);
typedef int (*PFunc_AddVehicleTurnSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_SetVehicleRelTurnSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_GetVehicleRelTurnSpeed) (int nVehicleId, float* pfX, float* pfY, float* pfZ);
typedef int (*PFunc_AddVehicleRelTurnSpeed) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_SetVehicleSpawnPos) (int nVehicleId, float fPosX, float fPosY, float fPosZ, float fAngleZ);
typedef int (*PFunc_GetVehicleSpawnPos) (int nVehicleId, float* pfPosX, float* pfPosY, float* pfPosZ, float* pfAngleZ);
typedef int (*PFunc_SetVehicleSpawnRot) (int nVehicleId, float fX, float fY, float fZ, float fW);
typedef int (*PFunc_SetVehicleSpawnRotEuler) (int nVehicleId, float fX, float fY, float fZ);
typedef int (*PFunc_GetVehicleSpawnRot) (int nVehicleId, float* pfX, float* pfY, float* pfZ, float* pfW);
typedef int (*PFunc_GetVehicleSpawnRotEuler) (int nVehicleId, float* pfX, float* pfY, float* pfZ);
typedef int (*PFunc_SetVehicleIdleRespawnTimer) (int nVehicleId, unsigned int uTimer);
typedef unsigned int (*PFunc_GetVehicleIdleRespawnTimer) (int nVehicleId);
typedef int (*PFunc_SetVehicleHealth) (int nVehicleId, float fHealth);
typedef float (*PFunc_GetVehicleHealth) (int nVehicleId);
typedef int (*PFunc_SetVehicleColour) (int nVehicleId, int nColour1, int nColour2);
typedef int (*PFunc_GetVehicleColour) (int nVehicleId, int* pnColour1, int* pnColour2);
typedef int (*PFunc_SetVehicleDoorsLocked) (int nVehicleId, unsigned int bToggle);
typedef unsigned int (*PFunc_GetVehicleDoorsLocked) (int nVehicleId);
typedef int (*PFunc_SetVehiclePartStatus) (int nVehicleId, int nPartId, int nStatus);
typedef int (*PFunc_GetVehiclePartStatus) (int nVehicleId, int nPartId);
typedef int (*PFunc_SetVehicleTyreStatus) (int nVehicleId, int nTyreId, int nStatus);
typedef int (*PFunc_GetVehicleTyreStatus) (int nVehicleId, int nTyreId);
typedef int (*PFunc_SetVehicleDamageData) (int nVehicleId, unsigned int uDamageData);
typedef unsigned int (*PFunc_GetVehicleDamageData) (int nVehicleId);
typedef int (*PFunc_SetVehicleAlarm) (int nVehicleId, unsigned int bToggle);
typedef unsigned int (*PFunc_GetVehicleAlarm) (int nVehicleId);
typedef int (*PFunc_SetVehicleLights) (int nVehicleId, unsigned int bToggle);
typedef unsigned int (*PFunc_GetVehicleLights) (int nVehicleId);

//VEHICLES: handling
typedef int (*PFunc_ResetAllVehicleHandlings) (void);
typedef unsigned int (*PFunc_ExistsHandlingRule) (int nModelIndex, int nRuleIndex);
typedef int (*PFunc_SetHandlingRule) (int nModelIndex, int nRuleIndex, double fValue);
typedef double (*PFunc_GetHandlingRule) (int nModelIndex, int nRuleIndex);
typedef int (*PFunc_ResetHandlingRule) (int nModelIndex, int nRuleIndex);
typedef int (*PFunc_ResetHandling) (int nModelIndex);
typedef unsigned int (*PFunc_ExistsInstHandlingRule) (int nVehicleId, int nRuleIndex);
typedef int (*PFunc_SetInstHandlingRule) (int nVehicleId, int nRuleIndex, double fValue);
typedef double (*PFunc_GetInstHandlingRule) (int nVehicleId, int nRuleIndex);
typedef int (*PFunc_ResetInstHandlingRule) (int nVehicleId, int nRuleIndex);
typedef int (*PFunc_ResetInstHandling) (int nVehicleId);

//PICKUPS
typedef int (*PFunc_CreatePickup) (int nModel, int nWorld, int nQuantity, float fPosX, float fPosY, float fPosZ, int nAlpha, unsigned int bAutomatic);
typedef int (*PFunc_DeletePickup) (int nPickupId);
typedef unsigned int (*PFunc_IsPickupStreamedForPlayer) (int nPickupId, int nPlayerId);
typedef int (*PFunc_SetPickupWorld) (int nPickupId, int nWorld);
typedef int (*PFunc_GetPickupWorld) (int nPickupId);
typedef int (*PFunc_PickupGetAlpha) (int nPickupId);
typedef int (*PFunc_PickupSetAlpha) (int nPickupId, int nAlpha);
typedef unsigned int (*PFunc_PickupIsAutomatic) (int nPickupId);
typedef int (*PFunc_PickupSetAutomatic) (int nPickupId, unsigned int bToggle);
typedef int (*PFunc_SetPickupAutoTimer) (int nPickupId, int nTimer);
typedef int (*PFunc_GetPickupAutoTimer) (int nPickupId);
typedef int (*PFunc_PickupRefresh) (int nPickupId);
typedef int (*PFunc_PickupGetPos) (int nPickupId, float* pfPosX, float* pfPosY, float* pfPosZ);
typedef int (*PFunc_PickupSetPos) (int nPickupId, float fPosX, float fPosY, float fPosZ);
typedef int (*PFunc_PickupGetModel) (int nPickupId);
typedef int (*PFunc_PickupGetQuantity) (int nPickupId);

//OBJECTS
typedef int (*PFunc_CreateObject) (int nModelId, int nWorld, float fPosX, float fPosY, float fPosZ, int nAlpha);
typedef int (*PFunc_DeleteObject) (int nObjectId);
typedef unsigned int (*PFunc_IsObjectStreamedForPlayer) (int nObjectId, int nPlayerId);
typedef int (*PFunc_GetObjectModel) (int nObjectId);
typedef int (*PFunc_SetObjectWorld) (int nObjectId, int nWorld);
typedef int (*PFunc_GetObjectWorld) (int nObjectId);
typedef int (*PFunc_SetObjectAlpha) (int nObjectId, int nAlpha, int nTime);
typedef int (*PFunc_GetObjectAlpha) (int nObjectId);
typedef int (*PFunc_MoveObjectTo) (int nObjectId, float fX, float fY, float fZ, int nTime);
typedef int (*PFunc_MoveObjectBy) (int nObjectId, float fX, float fY, float fZ, int nTime);
typedef int (*PFunc_SetObjectPos) (int nObjectId, float fX, float fY, float fZ);
typedef int (*PFunc_GetObjectPos) (int nObjectId, float* pfPosX, float* pfPosY, float* pfPosZ);
typedef int (*PFunc_RotObjectTo) (int nObjectId, float fX, float fY, float fZ, float fW, int nTime);
typedef int (*PFunc_RotObjectToEuler) (int nObjectId, float fX, float fY, float fZ, int nTime);
typedef int (*PFunc_RotObjectBy) (int nObjectId, float fX, float fY, float fZ, float fW, int nTime);
typedef int (*PFunc_RotObjectByEuler) (int nObjectId, float fX, float fY, float fZ, int nTime);
typedef int (*PFunc_GetObjectRot) (int nObjectId, float* pfX, float* pfY, float *pfZ, float *pfW);
typedef int (*PFunc_GetObjectRotEuler) (int nObjectId, float* pfX, float* pfY, float *pfZ);
typedef int (*PFunc_SetObjectShotReport) (int nObjectId, unsigned int bToggle);
typedef unsigned int (*PFunc_IsObjectShotReport) (int nObjectId);
typedef int (*PFunc_SetObjectBumpReport) (int nObjectId, unsigned int bToggle);
typedef unsigned int (*PFunc_IsObjectBumpReport) (int nObjectId);

struct PluginFuncs {
	unsigned int 				uStructSize;

	PFunc_GetServerVersion		GetServerVersion;
	PFunc_GetServerSettings		GetServerSettings;
	PFunc_ExportFunctions		ExportFunctions;
	PFunc_GetNumberOfPlugins	GetNumberOfPlugins;
	PFunc_GetPluginInfo			GetPluginInfo;
	PFunc_FindPlugin			FindPlugin;
	PFunc_GetPluginExports		GetPluginExports;
	PFunc_GetTime				GetTime;

	PFunc_printf		printf;
	PFunc_SendCustomCommand		SendCustomCommand;
	PFunc_SendClientMessage		SendClientMessage;
	PFunc_SendGameMessage		SendGameMessage;

	PFunc_SetServerName		SetServerName;
	PFunc_GetServerName		GetServerName;
	PFunc_SetMaxPlayers		SetMaxPlayers;
	PFunc_GetMaxPlayers		GetMaxPlayers;
	PFunc_SetServerPassword		SetServerPassword;
	PFunc_GetServerPassword		GetServerPassword;
	PFunc_SetGameModeText		SetGameModeText;
	PFunc_GetGameModeText		GetGameModeText;

	PFunc_SetWorldBounds		SetWorldBounds;
	PFunc_GetWorldBounds		GetWorldBounds;
	PFunc_SetWastedSettings		SetWastedSettings;
	PFunc_GetWastedSettings		GetWastedSettings;
	PFunc_SetTimeRate		SetTimeRate;
	PFunc_GetTimeRate		GetTimeRate;
	PFunc_SetHour		SetHour;
	PFunc_GetHour		GetHour;
	PFunc_SetMinute		SetMinute;
	PFunc_GetMinute		GetMinute;
	PFunc_SetWeather		SetWeather;
	PFunc_GetWeather		GetWeather;
	PFunc_SetGravity		SetGravity;
	PFunc_GetGravity		GetGravity;
	PFunc_SetGamespeed		SetGamespeed;
	PFunc_GetGamespeed		GetGamespeed;
	PFunc_SetWaterLevel		SetWaterLevel;
	PFunc_GetWaterLevel		GetWaterLevel;
	PFunc_SetMaxHeight		SetMaxHeight;
	PFunc_GetMaxHeight		GetMaxHeight;

	PFunc_ToggleSyncFrameLimiter		ToggleSyncFrameLimiter;
	PFunc_EnabledSyncFrameLimiter		EnabledSyncFrameLimiter;
	PFunc_ToggleFrameLimiter		ToggleFrameLimiter;
	PFunc_EnabledFrameLimiter		EnabledFrameLimiter;
	PFunc_ToggleTaxiBoostJump		ToggleTaxiBoostJump;
	PFunc_EnabledTaxiBoostJump		EnabledTaxiBoostJump;
	PFunc_ToggleDriveOnWater		ToggleDriveOnWater;
	PFunc_EnabledDriveOnWater		EnabledDriveOnWater;
	PFunc_ToggleFastSwitch		ToggleFastSwitch;
	PFunc_EnabledFastSwitch		EnabledFastSwitch;
	PFunc_ToggleFriendlyFire		ToggleFriendlyFire;
	PFunc_EnabledFriendlyFire		EnabledFriendlyFire;
	PFunc_ToggleDisableDriveby		ToggleDisableDriveby;
	PFunc_EnabledDisableDriveby		EnabledDisableDriveby;
	PFunc_TogglePerfectHandling		TogglePerfectHandling;
	PFunc_EnabledPerfectHandling		EnabledPerfectHandling;
	PFunc_ToggleFlyingCars		ToggleFlyingCars;
	PFunc_EnabledFlyingCars		EnabledFlyingCars;
	PFunc_ToggleJumpSwitch		ToggleJumpSwitch;
	PFunc_EnabledJumpSwitch		EnabledJumpSwitch;
	PFunc_ToggleShowMarkers		ToggleShowMarkers;
	PFunc_EnabledShowMarkers		EnabledShowMarkers;
	PFunc_ToggleStuntBike		ToggleStuntBike;
	PFunc_EnabledStuntBike		EnabledStuntBike;
	PFunc_ToggleShootInAir		ToggleShootInAir;
	PFunc_EnabledShootInAir		EnabledShootInAir;
	PFunc_ToggleShowNametags		ToggleShowNametags;
	PFunc_EnabledShowNametags		EnabledShowNametags;
	PFunc_ToggleJoinMessages		ToggleJoinMessages;
	PFunc_EnabledJoinMessages		EnabledJoinMessages;
	PFunc_ToggleDeathMessages		ToggleDeathMessages;
	PFunc_EnabledDeathMessages		EnabledDeathMessages;
	PFunc_ToggleChatTagsByDefaultEnabled		ToggleChatTagsByDefaultEnabled;
	PFunc_EnabledChatTagsByDefault		EnabledChatTagsByDefault;

	PFunc_CreateExplosion		CreateExplosion;
	PFunc_PlaySound		PlaySound;
	PFunc_HideMapObject		HideMapObject;
	PFunc_ShowMapObject		ShowMapObject;
	PFunc_ShowAllMapObjects		ShowAllMapObjects;

	PFunc_GetKeyBindUnusedSlot		GetKeyBindUnusedSlot;
	PFunc_GetKeyBindData		GetKeyBindData;
	PFunc_RegisterKeyBind		RegisterKeyBind;
	PFunc_RemoveKeyBind		RemoveKeyBind;
	PFunc_RemoveAllKeyBinds		RemoveAllKeyBinds;

	PFunc_CreateCoordBlip		CreateCoordBlip;
	PFunc_DestroyCoordBlip		DestroyCoordBlip;
	PFunc_GetCoordBlipInfo		GetCoordBlipInfo;

	PFunc_SetUseClasses		SetUseClasses;
	PFunc_GetUseClasses		GetUseClasses;
	PFunc_GetPlayerClass		GetPlayerClass;
	PFunc_AddPlayerClass		AddPlayerClass;
	PFunc_SetSpawnPlayerPos		SetSpawnPlayerPos;
	PFunc_SetSpawnCameraPos		SetSpawnCameraPos;
	PFunc_SetSpawnCameraLookAt		SetSpawnCameraLookAt;

	PFunc_IsPlayerAdmin		IsPlayerAdmin;
	PFunc_SetPlayerAdmin		SetPlayerAdmin;
	PFunc_GetPlayerIP		GetPlayerIP;
	PFunc_KickPlayer		KickPlayer;
	PFunc_BanPlayer		BanPlayer;
	PFunc_BanIP		BanIP;
	PFunc_UnbanIP		UnbanIP;
	PFunc_IsIPBanned		IsIPBanned;

	PFunc_GetPlayerIDFromName		GetPlayerIDFromName;
	PFunc_IsPlayerConnected		IsPlayerConnected;
	PFunc_IsPlayerSpawned		IsPlayerSpawned;
	PFunc_IsPlayerStreamedForPlayer		IsPlayerStreamedForPlayer;
	PFunc_GetPlayerKey		GetPlayerKey;
	PFunc_SetPlayerWorld		SetPlayerWorld;
	PFunc_GetPlayerWorld		GetPlayerWorld;
	PFunc_SetPlayerSecWorld		SetPlayerSecWorld;
	PFunc_GetPlayerSecWorld		GetPlayerSecWorld;
	PFunc_GetPlayerUniqueWorld		GetPlayerUniqueWorld;
	PFunc_IsPlayerWorldCompatible		IsPlayerWorldCompatible;
	PFunc_GetPlayerState		GetPlayerState;
	PFunc_GetPlayerName		GetPlayerName;
	PFunc_SetPlayerTeam		SetPlayerTeam;
	PFunc_GetPlayerTeam		GetPlayerTeam;
	PFunc_SetPlayerSkin		SetPlayerSkin;
	PFunc_GetPlayerSkin		GetPlayerSkin;
	PFunc_SetPlayerColour		SetPlayerColour;
	PFunc_GetPlayerColour		GetPlayerColour;
	PFunc_ForcePlayerSpawn		ForcePlayerSpawn;
	PFunc_ForcePlayerSelect		ForcePlayerSelect;
	PFunc_ForceAllSelect		ForceAllSelect;

	PFunc_GivePlayerMoney		GivePlayerMoney;
	PFunc_SetPlayerMoney		SetPlayerMoney;
	PFunc_GetPlayerMoney		GetPlayerMoney;
	PFunc_SetPlayerScore		SetPlayerScore;
	PFunc_GetPlayerScore		GetPlayerScore;
	PFunc_GetPlayerPing		GetPlayerPing;
	PFunc_IsPlayerTyping		IsPlayerTyping;

	PFunc_SetPlayerHealth		SetPlayerHealth;
	PFunc_GetPlayerHealth		GetPlayerHealth;
	PFunc_SetPlayerArmour		SetPlayerArmour;
	PFunc_GetPlayerArmour		GetPlayerArmour;
	PFunc_SetPlayerImmunityFlags		SetPlayerImmunityFlags;
	PFunc_GetPlayerImmunityFlags		GetPlayerImmunityFlags;
	PFunc_SetPlayerPos		SetPlayerPos;
	PFunc_GetPlayerPos		GetPlayerPos;
	PFunc_SetPlayerSpeed		SetPlayerSpeed;
	PFunc_GetPlayerSpeed		GetPlayerSpeed;
	PFunc_AddPlayerSpeed		AddPlayerSpeed;
	PFunc_SetPlayerHeading		SetPlayerHeading;
	PFunc_GetPlayerHeading		GetPlayerHeading;
	PFunc_SetPlayerAlpha		SetPlayerAlpha;
	PFunc_GetPlayerAlpha		GetPlayerAlpha;

	PFunc_PutPlayerInVehicle		PutPlayerInVehicle;
	PFunc_RemovePlayerFromVehicle		RemovePlayerFromVehicle;
	PFunc_GetPlayerInVehicleStatus		GetPlayerInVehicleStatus;
	PFunc_GetPlayerInVehicleSlot		GetPlayerInVehicleSlot;
	PFunc_GetPlayerVehicleID		GetPlayerVehicleID;

	PFunc_TogglePlayerControllable		TogglePlayerControllable;
	PFunc_EnabledPlayerControllable		EnabledPlayerControllable;
	PFunc_TogglePlayerDriveby		TogglePlayerDriveby;
	PFunc_EnabledPlayerDriveby		EnabledPlayerDriveby;
	PFunc_TogglePlayerWhiteScanlines		TogglePlayerWhiteScanlines;
	PFunc_EnabledPlayerWhiteScanlines		EnabledPlayerWhiteScanlines;
	PFunc_TogglePlayerGreenScanlines		TogglePlayerGreenScanlines;
	PFunc_EnabledPlayerGreenScanlines		EnabledPlayerGreenScanlines;
	PFunc_TogglePlayerWidescreen		TogglePlayerWidescreen;
	PFunc_EnabledPlayerWidescreen		EnabledPlayerWidescreen;
	PFunc_TogglePlayerShowMarkers		TogglePlayerShowMarkers;
	PFunc_EnabledPlayerShowMarkers		EnabledPlayerShowMarkers;
	PFunc_TogglePlayerAttackPriv		TogglePlayerAttackPriv;
	PFunc_EnabledPlayerAttackPriv		EnabledPlayerAttackPriv;
	PFunc_TogglePlayerHasMarker		TogglePlayerHasMarker;
	PFunc_EnabledPlayerHasMarker		EnabledPlayerHasMarker;
	PFunc_TogglePlayerChatTagsEnabled		TogglePlayerChatTagsEnabled;
	PFunc_EnabledPlayerChatTags		EnabledPlayerChatTags;

	PFunc_GivePlayerWeapon		GivePlayerWeapon;
	PFunc_SetPlayerWeapon		SetPlayerWeapon;
	PFunc_GetPlayerWeapon		GetPlayerWeapon;
	PFunc_GetPlayerWeaponAmmo		GetPlayerWeaponAmmo;
	PFunc_SetPlayerWeaponSlot		SetPlayerWeaponSlot;
	PFunc_GetPlayerWeaponSlot		GetPlayerWeaponSlot;
	PFunc_GetPlayerWeaponAtSlot		GetPlayerWeaponAtSlot;
	PFunc_GetPlayerAmmoAtSlot		GetPlayerAmmoAtSlot;
	PFunc_RemovePlayerWeapon		RemovePlayerWeapon;
	PFunc_RemoveAllWeapons		RemoveAllWeapons;

	PFunc_SetCameraPosition		SetCameraPosition;
	PFunc_RestoreCamera		RestoreCamera;
	PFunc_IsCameraLocked		IsCameraLocked;

	PFunc_SetPlayerAnimation		SetPlayerAnimation;
	PFunc_SetPlayerWantedLevel		SetPlayerWantedLevel;
	PFunc_GetPlayerStandingOnVehicle		GetPlayerStandingOnVehicle;
	PFunc_GetPlayerStandingOnObject		GetPlayerStandingOnObject;
	PFunc_IsPlayerAway		IsPlayerAway;
	PFunc_GetPlayerSpectateTarget		GetPlayerSpectateTarget;
	PFunc_SetPlayerSpectateTarget		SetPlayerSpectateTarget;

	PFunc_CreateVehicle		CreateVehicle;
	PFunc_DeleteVehicle		DeleteVehicle;
	PFunc_GetVehicleSyncSource		GetVehicleSyncSource;
	PFunc_GetVehicleSyncType		GetVehicleSyncType;
	PFunc_IsVehicleStreamedForPlayer		IsVehicleStreamedForPlayer;
	PFunc_SetVehicleWorld		SetVehicleWorld;
	PFunc_GetVehicleWorld		GetVehicleWorld;
	PFunc_GetVehicleModel		GetVehicleModel;
	PFunc_GetVehicleOccupant		GetVehicleOccupant;
	PFunc_RespawnVehicle		RespawnVehicle;
	PFunc_SetVehicleImmunityFlags		SetVehicleImmunityFlags;
	PFunc_GetVehicleImmunityFlags		GetVehicleImmunityFlags;
	PFunc_KillVehicle		KillVehicle;
	PFunc_IsVehicleWrecked		IsVehicleWrecked;
	PFunc_SetVehiclePos		SetVehiclePos;
	PFunc_GetVehiclePos		GetVehiclePos;
	PFunc_SetVehicleRot		SetVehicleRot;
	PFunc_SetVehicleRotEuler		SetVehicleRotEuler;
	PFunc_GetVehicleRot		GetVehicleRot;
	PFunc_GetVehicleRotEuler		GetVehicleRotEuler;
	PFunc_SetVehicleSpeed		SetVehicleSpeed;
	PFunc_GetVehicleSpeed		GetVehicleSpeed;
	PFunc_AddVehicleSpeed		AddVehicleSpeed;
	PFunc_SetVehicleRelSpeed		SetVehicleRelSpeed;
	PFunc_GetVehicleRelSpeed		GetVehicleRelSpeed;
	PFunc_AddVehicleRelSpeed		AddVehicleRelSpeed;
	PFunc_SetVehicleTurnSpeed		SetVehicleTurnSpeed;
	PFunc_GetVehicleTurnSpeed		GetVehicleTurnSpeed;
	PFunc_AddVehicleTurnSpeed		AddVehicleTurnSpeed;
	PFunc_SetVehicleRelTurnSpeed		SetVehicleRelTurnSpeed;
	PFunc_GetVehicleRelTurnSpeed		GetVehicleRelTurnSpeed;
	PFunc_AddVehicleRelTurnSpeed		AddVehicleRelTurnSpeed;
	PFunc_SetVehicleSpawnPos		SetVehicleSpawnPos;
	PFunc_GetVehicleSpawnPos		GetVehicleSpawnPos;
	PFunc_SetVehicleSpawnRot		SetVehicleSpawnRot;
	PFunc_SetVehicleSpawnRotEuler		SetVehicleSpawnRotEuler;
	PFunc_GetVehicleSpawnRot		GetVehicleSpawnRot;
	PFunc_GetVehicleSpawnRotEuler		GetVehicleSpawnRotEuler;
	PFunc_SetVehicleIdleRespawnTimer		SetVehicleIdleRespawnTimer;
	PFunc_GetVehicleIdleRespawnTimer		GetVehicleIdleRespawnTimer;
	PFunc_SetVehicleHealth		SetVehicleHealth;
	PFunc_GetVehicleHealth		GetVehicleHealth;
	PFunc_SetVehicleColour		SetVehicleColour;
	PFunc_GetVehicleColour		GetVehicleColour;
	PFunc_SetVehicleDoorsLocked		SetVehicleDoorsLocked;
	PFunc_GetVehicleDoorsLocked		GetVehicleDoorsLocked;
	PFunc_SetVehiclePartStatus		SetVehiclePartStatus;
	PFunc_GetVehiclePartStatus		GetVehiclePartStatus;
	PFunc_SetVehicleTyreStatus		SetVehicleTyreStatus;
	PFunc_GetVehicleTyreStatus		GetVehicleTyreStatus;
	PFunc_SetVehicleDamageData		SetVehicleDamageData;
	PFunc_GetVehicleDamageData		GetVehicleDamageData;
	PFunc_SetVehicleAlarm		SetVehicleAlarm;
	PFunc_GetVehicleAlarm		GetVehicleAlarm;
	PFunc_SetVehicleLights		SetVehicleLights;
	PFunc_GetVehicleLights		GetVehicleLights;

	PFunc_ResetAllVehicleHandlings		ResetAllVehicleHandlings;
	PFunc_ExistsHandlingRule		ExistsHandlingRule;
	PFunc_SetHandlingRule		SetHandlingRule;
	PFunc_GetHandlingRule		GetHandlingRule;
	PFunc_ResetHandlingRule		ResetHandlingRule;
	PFunc_ResetHandling		ResetHandling;
	PFunc_ExistsInstHandlingRule		ExistsInstHandlingRule;
	PFunc_SetInstHandlingRule		SetInstHandlingRule;
	PFunc_GetInstHandlingRule		GetInstHandlingRule;
	PFunc_ResetInstHandlingRule		ResetInstHandlingRule;
	PFunc_ResetInstHandling		ResetInstHandling;

	PFunc_CreatePickup		CreatePickup;
	PFunc_DeletePickup		DeletePickup;
	PFunc_IsPickupStreamedForPlayer		IsPickupStreamedForPlayer;
	PFunc_SetPickupWorld		SetPickupWorld;
	PFunc_GetPickupWorld		GetPickupWorld;
	PFunc_PickupGetAlpha		PickupGetAlpha;
	PFunc_PickupSetAlpha		PickupSetAlpha;
	PFunc_PickupIsAutomatic		PickupIsAutomatic;
	PFunc_PickupSetAutomatic		PickupSetAutomatic;
	PFunc_SetPickupAutoTimer		SetPickupAutoTimer;
	PFunc_GetPickupAutoTimer		GetPickupAutoTimer;
	PFunc_PickupRefresh		PickupRefresh;
	PFunc_PickupGetPos		PickupGetPos;
	PFunc_PickupSetPos		PickupSetPos;
	PFunc_PickupGetModel		PickupGetModel;
	PFunc_PickupGetQuantity		PickupGetQuantity;

	PFunc_CreateObject		CreateObject;
	PFunc_DeleteObject		DeleteObject;
	PFunc_IsObjectStreamedForPlayer		IsObjectStreamedForPlayer;
	PFunc_GetObjectModel		GetObjectModel;
	PFunc_SetObjectWorld		SetObjectWorld;
	PFunc_GetObjectWorld		GetObjectWorld;
	PFunc_SetObjectAlpha		SetObjectAlpha;
	PFunc_GetObjectAlpha		GetObjectAlpha;
	PFunc_MoveObjectTo		MoveObjectTo;
	PFunc_MoveObjectBy		MoveObjectBy;
	PFunc_SetObjectPos		SetObjectPos;
	PFunc_GetObjectPos		GetObjectPos;
	PFunc_RotObjectTo		RotObjectTo;
	PFunc_RotObjectToEuler		RotObjectToEuler;
	PFunc_RotObjectBy		RotObjectBy;
	PFunc_RotObjectByEuler		RotObjectByEuler;
	PFunc_GetObjectRot		GetObjectRot;
	PFunc_GetObjectRotEuler		GetObjectRotEuler;
	PFunc_SetObjectShotReport		SetObjectShotReport;
	PFunc_IsObjectShotReport		IsObjectShotReport;
	PFunc_SetObjectBumpReport		SetObjectBumpReport;
	PFunc_IsObjectBumpReport		IsObjectBumpReport;
};

typedef int (*PCback_OnInitServer) (void);
typedef void (*PCback_OnShutdownServer) (void);
typedef void (*PCback_OnFrame) (float fElapsedTime);
typedef void (*PCback_OnPlayerConnect) (int nPlayerId);
typedef void (*PCback_OnPlayerDisconnect) (int nPlayerId, int nReason);
typedef void (*PCback_OnPlayerBeginTyping) (int nPlayerId);
typedef void (*PCback_OnPlayerEndTyping) (int nPlayerId);
typedef int (*PCback_OnPlayerRequestClass) (int nPlayerId, int nOffset);
typedef int (*PCback_OnPlayerRequestSpawn) (int nPlayerId);
typedef void (*PCback_OnPlayerSpawn) (int nPlayerId);
typedef void (*PCback_OnPlayerDeath) (int nPlayerId, int nKillerId, int nReason, int nBodyPart);
typedef void (*PCback_OnPlayerUpdate) (int nPlayerId, int nUpdateType);
typedef int (*PCback_OnPlayerRequestEnter) (int nPlayerId, int nVehicleId, int nSlotId);
typedef void (*PCback_OnPlayerEnterVehicle) (int nPlayerId, int nVehicleId, int nSlotId);
typedef void (*PCback_OnPlayerExitVehicle) (int nPlayerId, int nVehicleId);
typedef int (*PCback_OnPickupClaimPicked) (int nPickupId, int nPlayerId);
typedef void (*PCback_OnPickupPickedUp) (int nPickupId, int nPlayerId);
typedef void (*PCback_OnPickupRespawn) (int nPickupId);
typedef void (*PCback_OnVehicleUpdate) (int nVehicleId, int nUpdateType);
typedef void (*PCback_OnVehicleExplode) (int nVehicleId);
typedef void (*PCback_OnVehicleRespawn) (int nVehicleId);
typedef void (*PCback_OnObjectShot) (int nObjectId, int nPlayerId, int nWeapon);
typedef void (*PCback_OnObjectBump) (int nObjectId, int nPlayerId);
typedef int (*PCback_OnPublicMessage) (int nPlayerId, const char* pszText);
typedef int (*PCback_OnCommandMessage) (int nPlayerId, const char* pszText);
typedef int (*PCback_OnPrivateMessage) (int nPlayerId, int nTargetId, const char* pszText);
typedef int (*PCback_OnInternalCommand) (unsigned int uCmdType, const char* pszText);
typedef int (*PCback_OnLoginAttempt) (char* pszPlayerName, const char* pszUserPassword, const char* pszIpAddress);
typedef void (*PCback_OnEntityPoolChange) (int nEntityType, int nEntityId, unsigned int bDeleted);
typedef void (*PCback_OnKeyBindDown) (int nPlayerId, int nBindId);
typedef void (*PCback_OnKeyBindUp) (int nPlayerId, int nBindId);
typedef void (*PCback_OnPlayerAwayChange) (int nPlayerId, unsigned int bNewStatus);
typedef void (*PCback_OnPlayerSpectate) (int nPlayerId, int nTargetId);
typedef void (*PCback_OnPlayerCrashReport) (int nPlayerId, const char* pszReport);

struct PluginCallbacks {
	unsigned int				uStructSize;

	PCback_OnInitServer		OnInitServer;
	PCback_OnShutdownServer		OnShutdownServer;
	PCback_OnFrame		OnFrame;
	PCback_OnPlayerConnect		OnPlayerConnect;
	PCback_OnPlayerDisconnect		OnPlayerDisconnect;
	PCback_OnPlayerBeginTyping		OnPlayerBeginTyping;
	PCback_OnPlayerEndTyping		OnPlayerEndTyping;
	PCback_OnPlayerRequestClass		OnPlayerRequestClass;
	PCback_OnPlayerRequestSpawn		OnPlayerRequestSpawn;
	PCback_OnPlayerSpawn		OnPlayerSpawn;
	PCback_OnPlayerDeath		OnPlayerDeath;
	PCback_OnPlayerUpdate		OnPlayerUpdate;
	PCback_OnPlayerRequestEnter		OnPlayerRequestEnter;
	PCback_OnPlayerEnterVehicle		OnPlayerEnterVehicle;
	PCback_OnPlayerExitVehicle		OnPlayerExitVehicle;
	PCback_OnPickupClaimPicked		OnPickupClaimPicked;
	PCback_OnPickupPickedUp		OnPickupPickedUp;
	PCback_OnPickupRespawn		OnPickupRespawn;
	PCback_OnVehicleUpdate		OnVehicleUpdate;
	PCback_OnVehicleExplode		OnVehicleExplode;
	PCback_OnVehicleRespawn		OnVehicleRespawn;
	PCback_OnObjectShot		OnObjectShot;
	PCback_OnObjectBump		OnObjectBump;
	PCback_OnPublicMessage		OnPublicMessage;
	PCback_OnCommandMessage		OnCommandMessage;
	PCback_OnPrivateMessage		OnPrivateMessage;
	PCback_OnInternalCommand		OnInternalCommand;
	PCback_OnLoginAttempt		OnLoginAttempt;
	PCback_OnEntityPoolChange		OnEntityPoolChange;
	PCback_OnKeyBindDown		OnKeyBindDown;
	PCback_OnKeyBindUp		OnKeyBindUp;
	PCback_OnPlayerAwayChange		OnPlayerAwayChange;
	PCback_OnPlayerSpectate		OnPlayerSpectate;
	PCback_OnPlayerCrashReport		OnPlayerCrashReport;
};
