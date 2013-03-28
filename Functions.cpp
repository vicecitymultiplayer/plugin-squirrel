#include "Functions.h"

void RegisterGlobals()
{
	RootTable(v)
		.Func( _SC("ClientMessage"), ClientMessage )
		.Func( _SC("ClientMessageToAll"), ClientMessageToAll )
		.Func( _SC("Announce"), GameMessage )
		.Func( _SC("AnnounceAll"), GameMessageToAll )
		
		.Func( _SC("SetServerName"), SetServerName )
		.Func( _SC("SetMaxPlayers"), SetMaxPlayers )
		.Func( _SC("SetPassword"), SetServerPassword )
		.Func( _SC("SetGameModeName"), SetGameModeText )
		.Func( _SC("SetTimeRate"), SetTimeRate )
		.Func( _SC("SetHour"), SetHour )
		.Func( _SC("SetMinute"), SetMinute )
		.Func( _SC("SetTime"), SetTime )
		.Func( _SC("SetWeather"), SetWeather )
		.Func( _SC("SetGravity"), SetGravity )
		.Func( _SC("SetGamespeed"), SetGamespeed )
		.Func( _SC("SetWaterLevel"), SetWaterLevel )
		.Func( _SC("SetMaxHeight"), SetMaxHeight )

		.Func( _SC("GetServerName"), GetServerName )
		.Func( _SC("GetMaxPlayers"), GetMaxPlayers )
		.Func( _SC("GetPassword"), GetServerPassword )
		.Func( _SC("GetGameModeName"), GetGameModeText )
		.Func( _SC("GetTimeRate"), GetTimeRate )
		.Func( _SC("GetHour"), GetHour )
		.Func( _SC("GetMinute"), GetMinute )
		.Func( _SC("GetWeather"), GetWeather )
		.Func( _SC("GetGravity"), GetGravity )
		.Func( _SC("GetGamespeed"), GetGamespeed )
		.Func( _SC("GetWaterLevel"), GetWaterLevel )
		.Func( _SC("GetMaxHeight"), GetMaxHeight )

		.Func( _SC("SetSyncFrameLimiter"), ToggleSyncFrameLimiter )
		.Func( _SC("SetFrameLimiter"), ToggleFrameLimiter )
		.Func( _SC("SetTaxiBoostJump"), ToggleTaxiBoostJump )
		.Func( _SC("SetDriveOnWater"), ToggleDriveOnWater )
		.Func( _SC("SetFastSwitch"), ToggleFastSwitch )
		.Func( _SC("SetFriendlyFire"), ToggleFriendlyFire )
		.Func( _SC("SetDrivebyEnabled"), ToggleDisableDriveby )
		.Func( _SC("SetPerfectHandling"), TogglePerfectHandling )
		.Func( _SC("SetFlyingCars"), ToggleFlyingCars )
		.Func( _SC("SetJumpSwitch"), ToggleJumpSwitch )
		.Func( _SC("SetShowOnRadar"), ToggleShowOnRadar )
		.Func( _SC("SetStuntBike"), ToggleStuntBike )
		.Func( _SC("SetShootInAir"), ToggleShootInAir )
		.Func( _SC("SetShowNametags"), ToggleShowNametags )
		.Func( _SC("SetJoinMessages"), ToggleJoinMessages )
		.Func( _SC("SetDeathMessages"), ToggleDeathMessages )

		.Func( _SC("GetSyncFrameLimiter"), EnabledSyncFrameLimiter )
		.Func( _SC("GetFrameLimiter"), EnabledFrameLimiter )
		.Func( _SC("GetTaxiBoostJump"), EnabledTaxiBoostJump )
		.Func( _SC("GetDriveOnWater"), EnabledDriveOnWater )
		.Func( _SC("GetFastSwitch"), EnabledFastSwitch )
		.Func( _SC("GetFriendlyFire"), EnabledFriendlyFire )
		.Func( _SC("GetDrivebyEnabled"), EnabledDisableDriveby )
		.Func( _SC("GetPerfectHandling"), EnabledPerfectHandling )
		.Func( _SC("GetFlyingCars"), EnabledFlyingCars )
		.Func( _SC("GetJumpSwitch"), EnabledJumpSwitch )
		.Func( _SC("GetShowOnRadar"), EnabledShowOnRadar )
		.Func( _SC("GetStuntBike"), EnabledStuntBike )
		.Func( _SC("GetShootInAir"), EnabledShootInAir )
		.Func( _SC("GetShowNametags"), EnabledShowNametags )
		.Func( _SC("GetJoinMessages"), EnabledJoinMessages )
		.Func( _SC("GetDeathMessages"), EnabledDeathMessages )

		.Func( _SC("CreateExplosion"), CreateExplosion )
		.Func( _SC("PlaySound"), PlayGameSound )

		.Func( _SC("SetUseClasses"), SetUseClasses )
		.Func( _SC("UsingClasses"), UsingClasses )
		.Func( _SC("AddClass"), AddClass )

		.Func( _SC("SetSpawnPlayerPos"), SetSpawnPlayerPos )
		.Func( _SC("SetSpawnCameraPos"), SetSpawnCameraPos )
		.Func( _SC("SetSpawnCameraLook"), SetSpawnCameraLook )

		.Func( _SC("BanIP"), BanIP )
		.Func( _SC("UnbanIP"), UnbanIP )
		.Func( _SC("IsIPBanned"), IsIPBanned )

		.Func( _SC("GetPlayerIDFromName"), GetPlayerIDFromName )
		.Func( _SC("IsWorldCompatibleWithPlayer"), IsWorldCompatibleWithPlayer )

		.Func( _SC("CreateVehicle"), CreateVehicle )
		.Func( _SC("CreatePickup"), CreatePickup )
		.Func( _SC("CreateObject"), CreateObject )

		.Func( _SC("FindPickup"), FindPickup )
		.Func( _SC("FindObject"), FindObject )
		.Func( _SC("FindVehicle"), FindVehicle )
		.Func( _SC("FindPlayer"), FindPlayer )

		.Func( _SC("SetWorldBounds"), SetWorldBounds )
		.Func( _SC("GetWorldBounds"), GetWorldBounds )

		.Func( _SC("SetWastedSettings"), SetWastedSettings )
		.Func( _SC("GetWastedSettings"), GetWastedSettings )

		.Func( _SC("HideMapObject"), HideMapObject )
		.Func( _SC("ShowMapObject"), ShowMapObject )
		.Func( _SC("ShowAllMapObjects"), ShowAllMapObjects )

		.Func( _SC("ForceAllSelect"), ForceAllSelect )

		.Func( _SC("ResetAllVehicleHandling"), ResetAllVehicleHandling )
		.Func( _SC("IsHandlingRuleSet"), IsHandlingRuleSet )
		.Func( _SC("SetHandlingRule"), SetHandlingRule )
		.Func( _SC("GetHandlingRule"), GetHandlingRule )
		.Func( _SC("ResetHandlingRule"), ResetHandlingRule )
		.Func( _SC("ResetVehicleHandling"), ResetVehicleHandling )

		// Compatibility functions
		.Func( _SC( "GetCinematicBorder" ), GetCinematicBorder )
		.Func( _SC( "GetGreenScanLines" ), GetGreenScanLines )
		.Func( _SC( "GetWhiteScanLines" ), GetWhiteScanLines )
		.Func( _SC( "SetCinematicBorder" ), SetCinematicBorder )
		.Func( _SC( "SetGreenScanLines" ), SetGreenScanLines )
		.Func( _SC( "SetWhiteScanLines" ), SetWhiteScanLines )
		.Func( _SC( "KickPlayer" ), KickPlayer )
		.Func( _SC( "BanPlayer" ), BanPlayer )
		.Func( _SC( "Message" ), Message )
		.Func( _SC( "MessagePlayer" ), MessagePlayer )
		.Func( _SC( "MessageAllExcept" ), MessageAllExcept )
		.Func( _SC( "PrivMessage" ), PrivMessage )
		.Func( _SC( "PrivMessageAll" ), PrivMessageAll )
		.Func( _SC( "SendPlayerMessage" ), SendPlayerMessage )

		.Func( _SC( "GetWeaponName" ), GetWeaponName )
		.Func( _SC( "GetDistrictName" ), GetDistrictName )
		.Func( _SC( "GetSkinName" ), GetSkinName )
		.Func( _SC( "GetWeaponID" ), GetWeaponID )
		.Func( _SC( "GetTickCount" ), SQGetTickCount )

		.Func( _SC( "InPoly" ), InPoly )
		.Func( _SC( "DistanceFromPoint" ), DistanceFromPoint )
		.Func( _SC( "ReloadScripts" ), ReloadScripts )

		.Func( _SC( "GetVehicleModelFromName" ), GetVehicleModelFromName )
		.Func( _SC( "GetVehicleNameFromModel" ), GetVehicleNameFromModel )

		.Func( _SC( "GetTime" ), GetTime )
		.Func( _SC( "GetFullTime" ), GetFullTime )
		
		.Func( _SC( "GetWeatherRate" ), GetWeatherRate )
		.Func( _SC( "SetWeatherRate" ), SetWeatherRate )
		.Func( _SC( "GetWeatherLock" ), GetWeatherLock )
		.Func( _SC( "SetWeatherLock" ), SetWeatherLock )

		.Func( _SC( "NewTimer" ), NewTimer );
}

void RegisterConstants()
{
	ConstTable(v)
		.Const( _SC("WEP_FIST"), 0 )
		.Const( _SC("WEP_BRASSKNUCKLES"), 1 )
		.Const( _SC("WEP_SCREWDRIVER"), 2 )
		.Const( _SC("WEP_GOLFCLUB"), 3 )
		.Const( _SC("WEP_NIGHTSTICK"), 4 )
		.Const( _SC("WEP_KNIFE"), 5 )
		.Const( _SC("WEP_BASEBALLBAT"), 6 )
		.Const( _SC("WEP_HAMMER"), 7 )
		.Const( _SC("WEP_MEATCLEAVER"), 8 )
		.Const( _SC("WEP_MACHETE"), 9 )
		.Const( _SC("WEP_KATANA"), 10 )
		.Const( _SC("WEP_CHAINSAW"), 11 )
		.Const( _SC("WEP_GRENADE"), 12 )
		.Const( _SC("WEP_REMOTE"), 13 )
		.Const( _SC("WEP_TEARGAS"), 14 )
		.Const( _SC("WEP_MOLOTOV"), 15 )
		.Const( _SC("WEP_ROCKET"), 16 )
		.Const( _SC("WEP_COLT"), 17 )
		.Const( _SC("WEP_COLT45"), 17 )
		.Const( _SC("WEP_PYTHON"), 18 )
		.Const( _SC("WEP_SHOTGUN"), 19 )
		.Const( _SC("WEP_SPAZ"), 20 )
		.Const( _SC("WEP_SPAS12"), 20 )
		.Const( _SC("WEP_STUBBY"), 21 )
		.Const( _SC("WEP_TEC9"), 22 )
		.Const( _SC("WEP_UZI"), 23 )
		.Const( _SC("WEP_INGRAM"), 24 )
		.Const( _SC("WEP_MP5"), 25 )
		.Const( _SC("WEP_M4"), 26 )
		.Const( _SC("WEP_RUGER"), 27 )
		.Const( _SC("WEP_SNIPER"), 28 )
		.Const( _SC("WEP_LASERSCOPE"), 29 )
		.Const( _SC("WEP_ROCKETLAUNCHER"), 30 )
		.Const( _SC("WEP_RPG"), 30 )
		.Const( _SC("WEP_FLAMETHROWER"), 31 )
		.Const( _SC("WEP_M60"), 32 )
		.Const( _SC("WEP_MINIGUN"), 33 )

		.Const( _SC("WEATHER_MOSTLYCLEAR"), 0 )
		.Const( _SC("WEATHER_OVERCAST"), 1 )
		.Const( _SC("WEATHER_THUNDERSTORM"), 2 )
		.Const( _SC("WEATHER_STORM"), 2 )
		.Const( _SC("WEATHER_STORMY"), 2 )
		.Const( _SC("WEATHER_FOGGY"), 3 )
		.Const( _SC("WEATHER_FOG"), 3 )
		.Const( _SC("WEATHER_CLEAR"), 4 )
		.Const( _SC("WEATHER_SUNNY"), 4 )
		.Const( _SC("WEATHER_RAIN"), 5 )
		.Const( _SC("WEATHER_RAINY"), 5 )
		.Const( _SC("WEATHER_DARKCLOUDY"), 6 )
		.Const( _SC("WEATHER_LIGHTCLOUDY"), 7 )
		.Const( _SC("WEATHER_OVERCASTCLOUDY"), 8 )
		.Const( _SC("WEATHER_BLACKCLOUDS"), 9 )

		.Const( _SC("VEH_LANDSTALKER"), 130 )
		.Const( _SC("VEH_IDAHO"), 131 )
		.Const( _SC("VEH_STINGER"), 132 )
		.Const( _SC("VEH_LINERUNNER"), 133 )
		.Const( _SC("VEH_PERENNIAL"), 134 )
		.Const( _SC("VEH_SENTINEL"), 135 )
		.Const( _SC("VEH_RIO"), 136 )
		.Const( _SC("VEH_FIRETRUCK"), 137 )
		.Const( _SC("VEH_TRASHMASTER"), 138 )
		.Const( _SC("VEH_STRETCH"), 139 )
		.Const( _SC("VEH_MANANA"), 140 )
		.Const( _SC("VEH_INFERNUS"), 141 )
		.Const( _SC("VEH_VOODOO"), 142 )
		.Const( _SC("VEH_PONY"), 143 )
		.Const( _SC("VEH_MULE"), 144 )
		.Const( _SC("VEH_CHEETAH"), 145 )
		.Const( _SC("VEH_AMBULANCE"), 146 )
		.Const( _SC("VEH_FBIWASHINGTON"), 147 )
		.Const( _SC("VEH_MOONBEAM"), 148 )
		.Const( _SC("VEH_ESPERANTO"), 149 )
		.Const( _SC("VEH_TAXI"), 150 )
		.Const( _SC("VEH_WASHINGTON"), 151 )
		.Const( _SC("VEH_BOBCAT"), 152 )
		.Const( _SC("VEH_MRWHOOPEE"), 153 )
		.Const( _SC("VEH_BFINJECTION"), 154 )
		.Const( _SC("VEH_HUNTER"), 155 )
		.Const( _SC("VEH_POLICE"), 156 )
		.Const( _SC("VEH_ENFORCER"), 157 )
		.Const( _SC("VEH_SECURICAR"), 158 )
		.Const( _SC("VEH_BANSHEE"), 159 )
		.Const( _SC("VEH_PREDATOR"), 160 )
		.Const( _SC("VEH_BUS"), 161 )
		.Const( _SC("VEH_RHINO"), 162 )
		.Const( _SC("VEH_BARRACKSOL"), 163 )
		.Const( _SC("VEH_BARRACKS"), 163 )
		.Const( _SC("VEH_CUBANHERMES"), 164 )
		.Const( _SC("VEH_HELICOPTER"), 165 )
		.Const( _SC("VEH_ANGEL"), 166 )
		.Const( _SC("VEH_COACH"), 167 )
		.Const( _SC("VEH_CABBIE"), 168 )
		.Const( _SC("VEH_STALLION"), 169 )
		.Const( _SC("VEH_RUMPO"), 170 )
		.Const( _SC("VEH_RCBANDIT"), 171 )
		.Const( _SC("VEH_HEARSE"), 172 )
		.Const( _SC("VEH_PACKER"), 173 )
		.Const( _SC("VEH_SENTINELXS"), 174 )
		.Const( _SC("VEH_ADMIRAL"), 175 )
		.Const( _SC("VEH_SQUALO"), 176 )
		.Const( _SC("VEH_SEASPARROW"), 177 )
		.Const( _SC("VEH_PIZZABOY"), 178 )
		.Const( _SC("VEH_GANGBURRITO"), 179 )
		.Const( _SC("VEH_AIRTRAIN"), 180 )
		.Const( _SC("VEH_DEADDODO"), 181 )
		.Const( _SC("VEH_SPEEDER"), 182 )
		.Const( _SC("VEH_REEFER"), 183 )
		.Const( _SC("VEH_TROPIC"), 184 )
		.Const( _SC("VEH_FLATBED"), 185 )
		.Const( _SC("VEH_YANKEE"), 186 )
		.Const( _SC("VEH_CADDY"), 187 )
		.Const( _SC("VEH_ZEBRA"), 188 )
		.Const( _SC("VEH_ZEBRACAB"), 188 )
		.Const( _SC("VEH_TOPFUN"), 189 )
		.Const( _SC("VEH_SKIMMER"), 190 )
		.Const( _SC("VEH_PCJ600"), 191 )
		.Const( _SC("VEH_PCJ"), 191 )
		.Const( _SC("VEH_FAGGIO"), 192 )
		.Const( _SC("VEH_FREEWAY"), 193 )
		.Const( _SC("VEH_RCBARON"), 194 )
		.Const( _SC("VEH_RCRAIDER"), 195 )
		.Const( _SC("VEH_GLENDALE"), 196 )
		.Const( _SC("VEH_OCEANIC"), 197 )
		.Const( _SC("VEH_SANCHEZ"), 198 )
		.Const( _SC("VEH_SPARROW"), 199 )
		.Const( _SC("VEH_PATRIOT"), 200 )
		.Const( _SC("VEH_LOVEFIST"), 201 )
		.Const( _SC("VEH_COASTGUARD"), 202 )
		.Const( _SC("VEH_DINGHY"), 203 )
		.Const( _SC("VEH_HERMES"), 204 )
		.Const( _SC("VEH_SABRE"), 205 )
		.Const( _SC("VEH_SABRETURBO"), 206 )
		.Const( _SC("VEH_PHOENIX"), 207 )
		.Const( _SC("VEH_WALTON"), 208 )
		.Const( _SC("VEH_REGINA"), 209 )
		.Const( _SC("VEH_COMET"), 210 )
		.Const( _SC("VEH_DELUXO"), 211 )
		.Const( _SC("VEH_BURRITO"), 212 )
		.Const( _SC("VEH_SPANDEX"), 213 )
		.Const( _SC("VEH_SPANDEXPRESS"), 213 )
		.Const( _SC("VEH_MARQUIS"), 214 )
		.Const( _SC("VEH_BAGGAGE"), 215 )
		.Const( _SC("VEH_BAGGAGEHANDLER"), 215 )
		.Const( _SC("VEH_KAUFMAN"), 216 )
		.Const( _SC("VEH_KAUFMANCAB"), 216 )
		.Const( _SC("VEH_MAVERICK"), 217 )
		.Const( _SC("VEH_VCNMAVERICK"), 218 )
		.Const( _SC("VEH_RANCHER"), 219 )
		.Const( _SC("VEH_FBIRANCHER"), 220 )
		.Const( _SC("VEH_VIRGO"), 221 )
		.Const( _SC("VEH_GREENWOOD"), 222 )
		.Const( _SC("VEH_CUBANJETMAX"), 223 )
		.Const( _SC("VEH_HOTRING1"), 224 )
		.Const( _SC("VEH_HOTRINGRACER1"), 224 )
		.Const( _SC("VEH_SANDKING"), 225 )
		.Const( _SC("VEH_BLISTA"), 226 )
		.Const( _SC("VEH_BLISTAC"), 226 )
		.Const( _SC("VEH_BLISTACOMPACT"), 226 )
		.Const( _SC("VEH_COMPACT"), 226 )
		.Const( _SC("VEH_POLICEMAV"), 227 )
		.Const( _SC("VEH_POLICEMAVERICK"), 227 )
		.Const( _SC("VEH_BOXVILLE"), 228 )
		.Const( _SC("VEH_BENSON"), 229 )
		.Const( _SC("VEH_MESA"), 230 )
		.Const( _SC("VEH_MESAGRANDE"), 230 )
		.Const( _SC("VEH_RCGOBLIN"), 231 )
		.Const( _SC("VEH_HOTRING2"), 232 )
		.Const( _SC("VEH_HOTRINGRACER2"), 232 )
		.Const( _SC("VEH_HOTRING3"), 233 )
		.Const( _SC("VEH_HOTRINGRACER3"), 233 )
		.Const( _SC("VEH_BLOODRING1"), 234 )
		.Const( _SC("VEH_BLOODRINGBANGER1"), 234 )
		.Const( _SC("VEH_BLOODRING2"), 235 )
		.Const( _SC("VEH_BLOODRINGBANGER2"), 235 )
		.Const( _SC("VEH_VICECHEE"), 236 )
		.Const( _SC("VEH_POLICECHEETAH"), 236 )
		.Const( _SC("VEH_FBICHEETAH"), 236 )
		.Const( _SC("VEH_CHEETAH2"), 236 )

		.Const( _SC("UPDATE_PLAYER_ONFOOT"), 0 )
		.Const( _SC("UPDATE_PLAYER_FOOT"), 0 )
		.Const( _SC("UPDATE_PLAYER_AIM"), 1 )
		.Const( _SC("UPDATE_PLAYER_DRIVER"), 2 )
		.Const( _SC("UPDATE_PLAYER_PASSENGER"), 3 )

		.Const( _SC("UPDATE_VEHICLE_DRIVER"), 0 )
		.Const( _SC("UPDATE_VEHICLE_OTHER"), 1 )

		.Const( _SC("BODYPART_BODY"), 0 )
		.Const( _SC("BODYPART_TORSO"), 1 )
		.Const( _SC("BODYPART_LEFTARM"), 2 )
		.Const( _SC("BODYPART_LARM"), 2 )
		.Const( _SC("BODYPART_RIGHTARM"), 3 )
		.Const( _SC("BODYPART_RARM"), 3 )
		.Const( _SC("BODYPART_LEFTLEG"), 4 )
		.Const( _SC("BODYPART_LLEG"), 4 )
		.Const( _SC("BODYPART_RIGHTLEG"), 5 )
		.Const( _SC("BODYPART_RLEG"), 5 )
		.Const( _SC("BODYPART_HEAD"), 6 )

		.Const( _SC("PARTREASON_QUIT"), 0 )
		.Const( _SC("PARTREASON_TIMEOUT"), 1 )
		.Const( _SC("PARTREASON_KICKEDBANNED"), 2 )
		.Const( _SC("PARTREASON_CRASHED"), 3 );
}