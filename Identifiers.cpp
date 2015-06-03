#include "Identifiers.h"

// ------------------------------------------------------------------------------------------------
#include <cstddef>
#include <limits>
#include <cfloat>
#include <cstring>
#include <locale>

// ------------------------------------------------------------------------------------------------
Sqrat::string CleanString(const SQChar * src)
{
    const unsigned sz = strlen(src);
    Sqrat::string str(sz, 0);

    for (unsigned i = 0; i < sz; ++i) {
        if ( std::isalnum( *(src + i) ) ) str += std::tolower( *(src + i) );
    }

    return str;
}

// ------------------------------------------------------------------------------------------------
const SQChar * GetKeyCodeName(SQInteger keycode)
{
    switch (keycode)
    {
        case SQMOD_KEYCODE_ABNT_C1:             return _SC("Abnt C1");
        case SQMOD_KEYCODE_ABNT_C2:             return _SC("Abnt C2");
        case SQMOD_KEYCODE_ADD:                 return _SC("Numpad +");
        case SQMOD_KEYCODE_ATTN:                return _SC("Attn");
        case SQMOD_KEYCODE_BACK:                return _SC("Backspace");
        case SQMOD_KEYCODE_CANCEL:              return _SC("Break");
        case SQMOD_KEYCODE_CLEAR:               return _SC("Clear");
        case SQMOD_KEYCODE_CRSEL:               return _SC("Cr Sel");
        case SQMOD_KEYCODE_DECIMAL:             return _SC("Numpad .");
        case SQMOD_KEYCODE_DIVIDE:              return _SC("Numpad /");
        case SQMOD_KEYCODE_EREOF:               return _SC("Er Eof");
        case SQMOD_KEYCODE_ESCAPE:              return _SC("Esc");
        case SQMOD_KEYCODE_EXECUTE:             return _SC("Execute");
        case SQMOD_KEYCODE_EXSEL:               return _SC("Ex Sel");
        case SQMOD_KEYCODE_ICO_CLEAR:           return _SC("IcoClr");
        case SQMOD_KEYCODE_ICO_HELP:            return _SC("IcoHlp");
        case SQMOD_KEYCODE_KEY_0:               return _SC("0");
        case SQMOD_KEYCODE_KEY_1:               return _SC("1");
        case SQMOD_KEYCODE_KEY_2:               return _SC("2");
        case SQMOD_KEYCODE_KEY_3:               return _SC("3");
        case SQMOD_KEYCODE_KEY_4:               return _SC("4");
        case SQMOD_KEYCODE_KEY_5:               return _SC("5");
        case SQMOD_KEYCODE_KEY_6:               return _SC("6");
        case SQMOD_KEYCODE_KEY_7:               return _SC("7");
        case SQMOD_KEYCODE_KEY_8:               return _SC("8");
        case SQMOD_KEYCODE_KEY_9:               return _SC("9");
        case SQMOD_KEYCODE_KEY_A:               return _SC("A");
        case SQMOD_KEYCODE_KEY_B:               return _SC("B");
        case SQMOD_KEYCODE_KEY_C:               return _SC("C");
        case SQMOD_KEYCODE_KEY_D:               return _SC("D");
        case SQMOD_KEYCODE_KEY_E:               return _SC("E");
        case SQMOD_KEYCODE_KEY_F:               return _SC("F");
        case SQMOD_KEYCODE_KEY_G:               return _SC("G");
        case SQMOD_KEYCODE_KEY_H:               return _SC("H");
        case SQMOD_KEYCODE_KEY_I:               return _SC("I");
        case SQMOD_KEYCODE_KEY_J:               return _SC("J");
        case SQMOD_KEYCODE_KEY_K:               return _SC("K");
        case SQMOD_KEYCODE_KEY_L:               return _SC("L");
        case SQMOD_KEYCODE_KEY_M:               return _SC("M");
        case SQMOD_KEYCODE_KEY_N:               return _SC("N");
        case SQMOD_KEYCODE_KEY_O:               return _SC("O");
        case SQMOD_KEYCODE_KEY_P:               return _SC("P");
        case SQMOD_KEYCODE_KEY_Q:               return _SC("Q");
        case SQMOD_KEYCODE_KEY_R:               return _SC("R");
        case SQMOD_KEYCODE_KEY_S:               return _SC("S");
        case SQMOD_KEYCODE_KEY_T:               return _SC("T");
        case SQMOD_KEYCODE_KEY_U:               return _SC("U");
        case SQMOD_KEYCODE_KEY_V:               return _SC("V");
        case SQMOD_KEYCODE_KEY_W:               return _SC("W");
        case SQMOD_KEYCODE_KEY_X:               return _SC("X");
        case SQMOD_KEYCODE_KEY_Y:               return _SC("Y");
        case SQMOD_KEYCODE_KEY_Z:               return _SC("Z");
        case SQMOD_KEYCODE_MULTIPLY:            return _SC("Numpad *");
        case SQMOD_KEYCODE_NONAME:              return _SC("NoName");
        case SQMOD_KEYCODE_NUMPAD0:             return _SC("Numpad 0");
        case SQMOD_KEYCODE_NUMPAD1:             return _SC("Numpad 1");
        case SQMOD_KEYCODE_NUMPAD2:             return _SC("Numpad 2");
        case SQMOD_KEYCODE_NUMPAD3:             return _SC("Numpad 3");
        case SQMOD_KEYCODE_NUMPAD4:             return _SC("Numpad 4");
        case SQMOD_KEYCODE_NUMPAD5:             return _SC("Numpad 5");
        case SQMOD_KEYCODE_NUMPAD6:             return _SC("Numpad 6");
        case SQMOD_KEYCODE_NUMPAD7:             return _SC("Numpad 7");
        case SQMOD_KEYCODE_NUMPAD8:             return _SC("Numpad 8");
        case SQMOD_KEYCODE_NUMPAD9:             return _SC("Numpad 9");
        case SQMOD_KEYCODE_OEM_1:               return _SC("OEM_1 (: ;)");
        case SQMOD_KEYCODE_OEM_102:             return _SC("OEM_102 (> <)");
        case SQMOD_KEYCODE_OEM_2:               return _SC("OEM_2 (? /)");
        case SQMOD_KEYCODE_OEM_3:               return _SC("OEM_3 (~ `)");
        case SQMOD_KEYCODE_OEM_4:               return _SC("OEM_4 ({ [)");
        case SQMOD_KEYCODE_OEM_5:               return _SC("OEM_5 (| \\)");
        case SQMOD_KEYCODE_OEM_6:               return _SC("OEM_6 (} ])");
        case SQMOD_KEYCODE_OEM_7:               return _SC("OEM_7 (\" ')");
        case SQMOD_KEYCODE_OEM_8:               return _SC("OEM_8 (ยง !)");
        case SQMOD_KEYCODE_OEM_ATTN:            return _SC("Oem Attn");
        case SQMOD_KEYCODE_OEM_AUTO:            return _SC("Auto");
        case SQMOD_KEYCODE_OEM_AX:              return _SC("Ax");
        case SQMOD_KEYCODE_OEM_BACKTAB:         return _SC("Back Tab");
        case SQMOD_KEYCODE_OEM_CLEAR:           return _SC("OemClr");
        case SQMOD_KEYCODE_OEM_COMMA:           return _SC("OEM_COMMA (< ,)");
        case SQMOD_KEYCODE_OEM_COPY:            return _SC("Copy");
        case SQMOD_KEYCODE_OEM_CUSEL:           return _SC("Cu Sel");
        case SQMOD_KEYCODE_OEM_ENLW:            return _SC("Enlw");
        case SQMOD_KEYCODE_OEM_FINISH:          return _SC("Finish");
        case SQMOD_KEYCODE_OEM_FJ_LOYA:         return _SC("Loya");
        case SQMOD_KEYCODE_OEM_FJ_MASSHOU:      return _SC("Mashu");
        case SQMOD_KEYCODE_OEM_FJ_ROYA:         return _SC("Roya");
        case SQMOD_KEYCODE_OEM_FJ_TOUROKU:      return _SC("Touroku");
        case SQMOD_KEYCODE_OEM_JUMP:            return _SC("Jump");
        case SQMOD_KEYCODE_OEM_MINUS:           return _SC("OEM_MINUS (_ -)");
        case SQMOD_KEYCODE_OEM_PA1:             return _SC("OemPa1");
        case SQMOD_KEYCODE_OEM_PA2:             return _SC("OemPa2");
        case SQMOD_KEYCODE_OEM_PA3:             return _SC("OemPa3");
        case SQMOD_KEYCODE_OEM_PERIOD:          return _SC("OEM_PERIOD (> .)");
        case SQMOD_KEYCODE_OEM_PLUS:            return _SC("OEM_PLUS (+ =)");
        case SQMOD_KEYCODE_OEM_RESET:           return _SC("Reset");
        case SQMOD_KEYCODE_OEM_WSCTRL:          return _SC("WsCtrl");
        case SQMOD_KEYCODE_PA1:                 return _SC("Pa1");
        case SQMOD_KEYCODE_PACKET:              return _SC("Packet");
        case SQMOD_KEYCODE_PLAY:                return _SC("Play");
        case SQMOD_KEYCODE_PROCESSKEY:          return _SC("Process");
        case SQMOD_KEYCODE_RETURN:              return _SC("Enter");
        case SQMOD_KEYCODE_SELECT:              return _SC("Select");
        case SQMOD_KEYCODE_SEPARATOR:           return _SC("Separator");
        case SQMOD_KEYCODE_SPACE:               return _SC("Space");
        case SQMOD_KEYCODE_SUBTRACT:            return _SC("Num -");
        case SQMOD_KEYCODE_TAB:                 return _SC("Tab");
        case SQMOD_KEYCODE_ZOOM:                return _SC("Zoom");
        case SQMOD_KEYCODE_ACCEPT:              return _SC("Accept");
        case SQMOD_KEYCODE_APPS:                return _SC("Context Menu");
        case SQMOD_KEYCODE_BROWSER_BACK:        return _SC("Browser Back");
        case SQMOD_KEYCODE_BROWSER_FAVORITES:   return _SC("Browser Favorites");
        case SQMOD_KEYCODE_BROWSER_FORWARD:     return _SC("Browser Forward");
        case SQMOD_KEYCODE_BROWSER_HOME:        return _SC("Browser Home");
        case SQMOD_KEYCODE_BROWSER_REFRESH:     return _SC("Browser Refresh");
        case SQMOD_KEYCODE_BROWSER_SEARCH:      return _SC("Browser Search");
        case SQMOD_KEYCODE_BROWSER_STOP:        return _SC("Browser Stop");
        case SQMOD_KEYCODE_CAPITAL:             return _SC("Caps Lock");
        case SQMOD_KEYCODE_CONVERT:             return _SC("Convert");
        case SQMOD_KEYCODE_DELETE:              return _SC("Delete");
        case SQMOD_KEYCODE_DOWN:                return _SC("Arrow Down");
        case SQMOD_KEYCODE_END:                 return _SC("End");
        case SQMOD_KEYCODE_F1:                  return _SC("F1");
        case SQMOD_KEYCODE_F10:                 return _SC("F10");
        case SQMOD_KEYCODE_F11:                 return _SC("F11");
        case SQMOD_KEYCODE_F12:                 return _SC("F12");
        case SQMOD_KEYCODE_F13:                 return _SC("F13");
        case SQMOD_KEYCODE_F14:                 return _SC("F14");
        case SQMOD_KEYCODE_F15:                 return _SC("F15");
        case SQMOD_KEYCODE_F16:                 return _SC("F16");
        case SQMOD_KEYCODE_F17:                 return _SC("F17");
        case SQMOD_KEYCODE_F18:                 return _SC("F18");
        case SQMOD_KEYCODE_F19:                 return _SC("F19");
        case SQMOD_KEYCODE_F2:                  return _SC("F2");
        case SQMOD_KEYCODE_F20:                 return _SC("F20");
        case SQMOD_KEYCODE_F21:                 return _SC("F21");
        case SQMOD_KEYCODE_F22:                 return _SC("F22");
        case SQMOD_KEYCODE_F23:                 return _SC("F23");
        case SQMOD_KEYCODE_F24:                 return _SC("F24");
        case SQMOD_KEYCODE_F3:                  return _SC("F3");
        case SQMOD_KEYCODE_F4:                  return _SC("F4");
        case SQMOD_KEYCODE_F5:                  return _SC("F5");
        case SQMOD_KEYCODE_F6:                  return _SC("F6");
        case SQMOD_KEYCODE_F7:                  return _SC("F7");
        case SQMOD_KEYCODE_F8:                  return _SC("F8");
        case SQMOD_KEYCODE_F9:                  return _SC("F9");
        case SQMOD_KEYCODE_FINAL:               return _SC("Final");
        case SQMOD_KEYCODE_HELP:                return _SC("Help");
        case SQMOD_KEYCODE_HOME:                return _SC("Home");
        case SQMOD_KEYCODE_ICO_00:              return _SC("Ico00 *");
        case SQMOD_KEYCODE_INSERT:              return _SC("Insert");
        case SQMOD_KEYCODE_JUNJA:               return _SC("Junja");
        case SQMOD_KEYCODE_KANA:                return _SC("Kana");
        case SQMOD_KEYCODE_KANJI:               return _SC("Kanji");
        case SQMOD_KEYCODE_LAUNCH_APP1:         return _SC("App1");
        case SQMOD_KEYCODE_LAUNCH_APP2:         return _SC("App2");
        case SQMOD_KEYCODE_LAUNCH_MAIL:         return _SC("Mail");
        case SQMOD_KEYCODE_LAUNCH_MEDIA_SELECT: return _SC("Media");
        case SQMOD_KEYCODE_LBUTTON:             return _SC("Left Button **");
        case SQMOD_KEYCODE_LCONTROL:            return _SC("Left Ctrl");
        case SQMOD_KEYCODE_LEFT:                return _SC("Arrow Left");
        case SQMOD_KEYCODE_LMENU:               return _SC("Left Alt");
        case SQMOD_KEYCODE_LSHIFT:              return _SC("Left Shift");
        case SQMOD_KEYCODE_LWIN:                return _SC("Left Win");
        case SQMOD_KEYCODE_MBUTTON:             return _SC("Middle Button **");
        case SQMOD_KEYCODE_MEDIA_NEXT_TRACK:    return _SC("Next Track");
        case SQMOD_KEYCODE_MEDIA_PLAY_PAUSE:    return _SC("Play / Pause");
        case SQMOD_KEYCODE_MEDIA_PREV_TRACK:    return _SC("Previous Track");
        case SQMOD_KEYCODE_MEDIA_STOP:          return _SC("Stop");
        case SQMOD_KEYCODE_MODECHANGE:          return _SC("Mode Change");
        case SQMOD_KEYCODE_NEXT:                return _SC("Page Down");
        case SQMOD_KEYCODE_NONCONVERT:          return _SC("Non Convert");
        case SQMOD_KEYCODE_NUMLOCK:             return _SC("Num Lock");
        case SQMOD_KEYCODE_OEM_FJ_JISHO:        return _SC("Jisho");
        case SQMOD_KEYCODE_PAUSE:               return _SC("Pause");
        case SQMOD_KEYCODE_PRINT:               return _SC("Print");
        case SQMOD_KEYCODE_PRIOR:               return _SC("Page Up");
        case SQMOD_KEYCODE_RBUTTON:             return _SC("Right Button **");
        case SQMOD_KEYCODE_RCONTROL:            return _SC("Right Ctrl");
        case SQMOD_KEYCODE_RIGHT:               return _SC("Arrow Right");
        case SQMOD_KEYCODE_RMENU:               return _SC("Right Alt");
        case SQMOD_KEYCODE_RSHIFT:              return _SC("Right Shift");
        case SQMOD_KEYCODE_RWIN:                return _SC("Right Win");
        case SQMOD_KEYCODE_SCROLL:              return _SC("Scrol Lock");
        case SQMOD_KEYCODE_SLEEP:               return _SC("Sleep");
        case SQMOD_KEYCODE_SNAPSHOT:            return _SC("Print Screen");
        case SQMOD_KEYCODE_UP:                  return _SC("Arrow Up");
        case SQMOD_KEYCODE_VOLUME_DOWN:         return _SC("Volume Down");
        case SQMOD_KEYCODE_VOLUME_MUTE:         return _SC("Volume Mute");
        case SQMOD_KEYCODE_VOLUME_UP:           return _SC("Volume Up");
        case SQMOD_KEYCODE_XBUTTON1:            return _SC("X Button 1 **");
        case SQMOD_KEYCODE_XBUTTON2:            return _SC("X Button 2 **");
        case SQMOD_KEYCODE_NONE:                return _SC("no mapping");
        default:                                return _SC("");
    }
}

bool IsModelWeapon(SQInteger id)
{
    switch (id)
    {
        case 258:
        case 259:
        case 260:
        case 261:
        case 262:
        case 263:
        case 264:
        case 265:
        case 266:
        case 267:
        case 268:
        case 269:
        case 270:
        case 271:
        case 272:
        case 273:
        case 274:
        case 275:
        case 276:
        case 277:
        case 278:
        case 279:
        case 280:
        case 281:
        case 282:
        case 283:
        case 284:
        case 285:
        case 286:
        case 287:
        case 288:
        case 289:
        case 290:
        case 291:
        case 292:
        case 293:
        case 294: return SQTrue;
        default: return SQFalse;
    }
}

bool IsModelActuallyWeapon(SQInteger id)
{
    switch (id)
    {
        case 259:
        case 260:
        case 261:
        case 262:
        case 263:
        case 264:
        case 265:
        case 266:
        case 267:
        case 268:
        case 269:
        case 270:
        case 271:
        case 272:
        case 274:
        case 275:
        case 276:
        case 277:
        case 278:
        case 279:
        case 280:
        case 281:
        case 282:
        case 283:
        case 284:
        case 285:
        case 286:
        case 287:
        case 288:
        case 289:
        case 290:
        case 291: return SQTrue;
        default: return SQFalse;
    }
}

// ------------------------------------------------------------------------------------------------
const SQChar * GetSkinName(SQInteger id)
{
    switch(id)
    {
        case SQMOD_SKIN_TOMMY_VERCETTI:         return _SC("Tommy Vercetti");
        case SQMOD_SKIN_COP:                    return _SC("Cop");
        case SQMOD_SKIN_SWAT:                   return _SC("SWAT");
        case SQMOD_SKIN_FBI:                    return _SC("FBI");
        case SQMOD_SKIN_ARMY:                   return _SC("Army");
        case SQMOD_SKIN_PARAMEDIC:              return _SC("Paramedic");
        case SQMOD_SKIN_FIREMAN:                return _SC("Firefighter");
        case SQMOD_SKIN_GOLF_GUY_A:             return _SC("Golf Guy #1");
        case SQMOD_SKIN_BUM_LADY_A:             return _SC("Bum Lady #1");
        case SQMOD_SKIN_BUM_LADY_B:             return _SC("Bum Lady #2");
        case SQMOD_SKIN_PUNK_A:                 return _SC("Punk #1");
        case SQMOD_SKIN_LAWYER:                 return _SC("Lawyer");
        case SQMOD_SKIN_SPANISH_LADY_A:         return _SC("Spanish Lady #1");
        case SQMOD_SKIN_SPANISH_LADY_B:         return _SC("Spanish Lady #2");
        case SQMOD_SKIN_COOL_GUY_A:             return _SC("Cool Guy #1");
        case SQMOD_SKIN_ARABIC_GUY:             return _SC("Arabic Guy");
        case SQMOD_SKIN_BEACH_LADY_A:           return _SC("Beach Lady #1");
        case SQMOD_SKIN_BEACH_LADY_B:           return _SC("Beach Lady #2");
        case SQMOD_SKIN_BEACH_GUY_A:            return _SC("Beach Guy #1");
        case SQMOD_SKIN_BEACH_GUY_B:            return _SC("Beach Guy #2");
        case SQMOD_SKIN_OFFICE_LADY_A:          return _SC("Office Lady #1");
        case SQMOD_SKIN_WAITRESS_A:             return _SC("Waitress #1");
        case SQMOD_SKIN_FOOD_LADY:              return _SC("Food Lady");
        case SQMOD_SKIN_PROSTITUTE_A:           return _SC("Prostitute #1");
        case SQMOD_SKIN_BUM_LADY_C:             return _SC("Bum Lady #3");
        case SQMOD_SKIN_BUM_GUY_A:              return _SC("Bum Guy #1");
        case SQMOD_SKIN_GARBAGEMAN_A:           return _SC("Garbageman #1");
        case SQMOD_SKIN_TAXI_DRIVER_A:          return _SC("Taxi Driver #1");
        case SQMOD_SKIN_HATIAN_A:               return _SC("Haitian #1");
        case SQMOD_SKIN_CRIMINAL_A:             return _SC("Criminal #1");
        case SQMOD_SKIN_HOOD_LADY:              return _SC("Hood Lady");
        case SQMOD_SKIN_GRANNY_A:               return _SC("Granny #1");
        case SQMOD_SKIN_BUSINESS_MAN_A:         return _SC("Businessman #1");
        case SQMOD_SKIN_CHURCH_GUY:             return _SC("Church Guy");
        case SQMOD_SKIN_CLUB_LADY:              return _SC("Club Lady");
        case SQMOD_SKIN_CHURCH_LADY:            return _SC("Church Lady");
        case SQMOD_SKIN_PIMP:                   return _SC("Pimp");
        case SQMOD_SKIN_BEACH_LADY_C:           return _SC("Beach Lady #3");
        case SQMOD_SKIN_BEACH_GUY_C:            return _SC("Beach Guy #3");
        case SQMOD_SKIN_BEACH_LADY_D:           return _SC("Beach Lady #4");
        case SQMOD_SKIN_BEACH_GUY_D:            return _SC("Beach Guy #4");
        case SQMOD_SKIN_BUSINESS_MAN_B:         return _SC("Businessman #2");
        case SQMOD_SKIN_PROSTITUTE_B:           return _SC("Prostitute #2");
        case SQMOD_SKIN_BUM_LADY_D:             return _SC("Bum Lady #4");
        case SQMOD_SKIN_BUM_GUY_B:              return _SC("Bum Guy #2");
        case SQMOD_SKIN_HATIAN_B:               return _SC("Haitian #2");
        case SQMOD_SKIN_CONSTRUCTION_WORKER_A:  return _SC("Construction Worker #1");
        case SQMOD_SKIN_PUNK_B:                 return _SC("Punk #2");
        case SQMOD_SKIN_PROSTITUTE_C:           return _SC("Prostitute #3");
        case SQMOD_SKIN_GRANNY_B:               return _SC("Granny #2");
        case SQMOD_SKIN_PUNK_C:                 return _SC("Punk #3");
        case SQMOD_SKIN_BUSINESS_MAN_C:         return _SC("Businessman #3");
        case SQMOD_SKIN_SPANISH_LADY_C:         return _SC("Spanish Lady #3");
        case SQMOD_SKIN_SPANISH_LADY_D:         return _SC("Spanish Lady #4");
        case SQMOD_SKIN_COOL_GUY_B:             return _SC("Cool Guy #2");
        case SQMOD_SKIN_BUSINESS_MAN_D:         return _SC("Businessman #4");
        case SQMOD_SKIN_BEACH_LADY_E:           return _SC("Beach Lady #5");
        case SQMOD_SKIN_BEACH_GUY_E:            return _SC("Beach Guy #5");
        case SQMOD_SKIN_BEACH_LADY_F:           return _SC("Beach Lady #6");
        case SQMOD_SKIN_BEACH_GUY_F:            return _SC("Beach Guy #6");
        case SQMOD_SKIN_CONSTRUCTION_WORKER_B:  return _SC("Construction Worker #2");
        case SQMOD_SKIN_GOLF_GUY_B:             return _SC("Golf Guy #2");
        case SQMOD_SKIN_GOLF_LADY:              return _SC("Golf Lady");
        case SQMOD_SKIN_GOLF_GUY_C:             return _SC("Golf Guy #3");
        case SQMOD_SKIN_BEACH_LADY_G:           return _SC("Beach Lady #7");
        case SQMOD_SKIN_BEACH_GUY_G:            return _SC("Beach Guy #7");
        case SQMOD_SKIN_OFFICE_LADY_B:          return _SC("Office Lady #2");
        case SQMOD_SKIN_BUSINESS_MAN_E:         return _SC("Businessman #5");
        case SQMOD_SKIN_BUSINESS_MAN_F:         return _SC("Businessman #6");
        case SQMOD_SKIN_PROSTITUTE_D:           return _SC("Prostitute #2");
        case SQMOD_SKIN_BUM_LADY_E:             return _SC("Bum Lady #4");
        case SQMOD_SKIN_BUM_GUY_C:              return _SC("Bum Guy #3");
        case SQMOD_SKIN_SPANISH_GUY:            return _SC("Spanish Guy");
        case SQMOD_SKIN_TAXI_DRIVER_B:          return _SC("Taxi Driver #2");
        case SQMOD_SKIN_GYM_LADY:               return _SC("Gym Lady");
        case SQMOD_SKIN_GYM_GUY:                return _SC("Gym Guy");
        case SQMOD_SKIN_SKATE_LADY:             return _SC("Skate Lady");
        case SQMOD_SKIN_SKATE_GUY:              return _SC("Skate Guy");
        case SQMOD_SKIN_SHOPPER_A:              return _SC("Shopper #1");
        case SQMOD_SKIN_SHOPPER_B:              return _SC("Shopper #2");
        case SQMOD_SKIN_TOURIST_A:              return _SC("Tourist #1");
        case SQMOD_SKIN_TOURIST_B:              return _SC("Tourist #2");
        case SQMOD_SKIN_CUBAN_A:                return _SC("Cuban #1");
        case SQMOD_SKIN_CUBAN_B:                return _SC("Cuban #2");
        case SQMOD_SKIN_HATIAN_C:               return _SC("Haitian #3");
        case SQMOD_SKIN_HATIAN_D:               return _SC("Haitian #4");
        case SQMOD_SKIN_SHARK_A:                return _SC("Shark #1");
        case SQMOD_SKIN_SHARK_B:                return _SC("Shark #2");
        case SQMOD_SKIN_DIAZ_GUY_A:             return _SC("Diaz Guy #1");
        case SQMOD_SKIN_DIAZ_GUY_B:             return _SC("Diaz Guy #2");
        case SQMOD_SKIN_DBP_SECURITY_A:         return _SC("DBP Security #1");
        case SQMOD_SKIN_DBP_SECURITY_B:         return _SC("DBP Security #2");
        case SQMOD_SKIN_BIKER_A:                return _SC("Biker #1");
        case SQMOD_SKIN_BIKER_B:                return _SC("Biker #2");
        case SQMOD_SKIN_VERCETTI_GUY_A:         return _SC("Vercetti Guy #1");
        case SQMOD_SKIN_VERCETTI_GUY_B:         return _SC("Vercetti Guy #2");
        case SQMOD_SKIN_UNDERCOVER_COP_A:       return _SC("Undercover Cop #1");
        case SQMOD_SKIN_UNDERCOVER_COP_B:       return _SC("Undercover Cop #2");
        case SQMOD_SKIN_UNDERCOVER_COP_C:       return _SC("Undercover Cop #3");
        case SQMOD_SKIN_UNDERCOVER_COP_D:       return _SC("Undercover Cop #4");
        case SQMOD_SKIN_UNDERCOVER_COP_E:       return _SC("Undercover Cop #5");
        case SQMOD_SKIN_UNDERCOVER_COP_F:       return _SC("Undercover Cop #6");
        case SQMOD_SKIN_RICH_GUY:               return _SC("Rich Guy");
        case SQMOD_SKIN_COOL_GUY_C:             return _SC("Cool Guy #3");
        case SQMOD_SKIN_PROSTITUTE_E:           return _SC("Prostitute #3");
        case SQMOD_SKIN_PROSTITUTE_F:           return _SC("Prostitute #4");
        case SQMOD_SKIN_LOVE_FIST_A:            return _SC("Love Fist #1");
        case SQMOD_SKIN_KEN_ROSENBURG:          return _SC("Ken Rosenburg");
        case SQMOD_SKIN_CANDY_SUXX:             return _SC("Candy Suxx");
        case SQMOD_SKIN_HILARY:                 return _SC("Hilary");
        case SQMOD_SKIN_LOVE_FIST_B:            return _SC("Love Fist #2");
        case SQMOD_SKIN_PHIL:                   return _SC("Phil");
        case SQMOD_SKIN_ROCKSTAR_GUY:           return _SC("Rockstar Guy");
        case SQMOD_SKIN_SONNY:                  return _SC("Sonny");
        case SQMOD_SKIN_LANCE_A:                return _SC("Lance");
        case SQMOD_SKIN_MERCADES_A:             return _SC("Mercedes");
        case SQMOD_SKIN_LOVE_FIST_C:            return _SC("Love Fist #3");
        case SQMOD_SKIN_ALEX_SRUB:              return _SC("Alex Shrub");
        case SQMOD_SKIN_LANCE_COP:              return _SC("Lance (Cop)");
        case SQMOD_SKIN_LANCE_B:                return _SC("Lance");
        case SQMOD_SKIN_CORTEZ:                 return _SC("Cortez");
        case SQMOD_SKIN_LOVE_FIST_D:            return _SC("Love Fist #4");
        case SQMOD_SKIN_COLUMBIAN_GUY_A:        return _SC("Columbian Guy #1");
        case SQMOD_SKIN_HILARY_ROBBER:          return _SC("Hilary (Robber)");
        case SQMOD_SKIN_MERCADES_B:             return _SC("Mercedes");
        case SQMOD_SKIN_CAM:                    return _SC("Cam");
        case SQMOD_SKIN_CAM_ROBBER:             return _SC("Cam (Robber)");
        case SQMOD_SKIN_PHIL_ONE_ARM:           return _SC("Phil (One Arm)");
        case SQMOD_SKIN_PHIL_ROBBER:            return _SC("Phil (Robber)");
        case SQMOD_SKIN_COOL_GUY_D:             return _SC("Cool Guy #4");
        case SQMOD_SKIN_PIZZAMAN:               return _SC("Pizza Man");
        case SQMOD_SKIN_TAXI_DRIVER_C:          return _SC("Taxi Driver #1");
        case SQMOD_SKIN_TAXI_DRIVER_D:          return _SC("Taxi Driver #2");
        case SQMOD_SKIN_SAILOR_A:               return _SC("Sailor #1");
        case SQMOD_SKIN_SAILOR_B:               return _SC("Sailor #2");
        case SQMOD_SKIN_SAILOR_C:               return _SC("Sailor #3");
        case SQMOD_SKIN_CHEF:                   return _SC("Chef");
        case SQMOD_SKIN_CRIMINAL_B:             return _SC("Criminal #2");
        case SQMOD_SKIN_FRENCH_GUY:             return _SC("French Guy");
        case SQMOD_SKIN_GARBAGEMAN_B:           return _SC("Garbageman #2");
        case SQMOD_SKIN_HATIAN_E:               return _SC("Haitian #5");
        case SQMOD_SKIN_WAITRESS_B:             return _SC("Waitress #2");
        case SQMOD_SKIN_SONNY_GUY_A:            return _SC("Sonny Guy #1");
        case SQMOD_SKIN_SONNY_GUY_B:            return _SC("Sonny Guy #2");
        case SQMOD_SKIN_SONNY_GUY_C:            return _SC("Sonny Guy #3");
        case SQMOD_SKIN_COLUMBIAN_GUY_B:        return _SC("Columbian Guy #2");
        case SQMOD_SKIN_THUG_A:                 return _SC("Haitian #6");
        case SQMOD_SKIN_BEACH_GUY_H:            return _SC("Beach Guy #8");
        case SQMOD_SKIN_GARBAGEMAN_C:           return _SC("Garbageman #3");
        case SQMOD_SKIN_GARBAGEMAN_D:           return _SC("Garbageman #4");
        case SQMOD_SKIN_GARBAGEMAN_E:           return _SC("Garbageman #5");
        case SQMOD_SKIN_TRANNY:                 return _SC("Tranny");
        case SQMOD_SKIN_THUG_B:                 return _SC("Thug #5");
        case SQMOD_SKIN_SPANDEX_GUY_A:          return _SC("SpandEx Guy #1");
        case SQMOD_SKIN_SPANDEX_GUY_B:          return _SC("SpandEx Guy #2");
        case SQMOD_SKIN_STRIPPER_A:             return _SC("Stripper #1");
        case SQMOD_SKIN_STRIPPER_B:             return _SC("Stripper #2");
        case SQMOD_SKIN_STRIPPER_C:             return _SC("Stripper #3");
        case SQMOD_SKIN_STORE_CLERK:            return _SC("Store Clerk");
        default:                                return _SC("");
    }
}

// ------------------------------------------------------------------------------------------------
SQInteger GetSkinID(const SQChar * name)
{
    // Clone the string into a clean editable version
    Sqrat::string str = CleanString(name);
    // See if we still have a valid name after the cleanup
    if(str.empty()) return SQMOD_UNKNOWN;
    // Grab the actual length of the string
    unsigned len = str.length();
    // Get the most significant characters used to identify a skin
    SQChar a = str[0], b = 0, c = 0, d = str[len-1];
    // Look for deeper specifiers
    if (str.length() >= 3)
    {
        b = str[1];
        c = str[2];
    }
    else if (str.length() >= 2)
    {
        b = str[1];
    }
    // Search for a pattern in the name
    switch (a)
    {
        // [A]lex Srub, [A]rabic guy, [A]rmy
        case 'a':
            switch (b)
            {
                // [Al]ex [S]rub
                case 'l':
                case 's': return SQMOD_SKIN_ALEX_SRUB;
                // [A]rabic [g]uy
                case 'g': return SQMOD_SKIN_ARABIC_GUY;
                // [Ara]bic guy, [Arm]y
                case 'r':
                    if (c == 'a') return SQMOD_SKIN_ARABIC_GUY;
                    else if (c == 'm') return SQMOD_SKIN_ARMY;
            }
        // [B]each guy (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)/(#8|H)
        // [B]each lady (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)
        // [B]iker (#1|A)/(#2|B)
        // [B]um guy (#1|A)/(#2|B)/(#3|C)
        // [B]um lady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
        // [B]usiness man (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
        case 'b':
            // [Be]ach [g]uy (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)/(#8|H)
            if (b == 'e' && (c == 'g' || (len > 4 && str[5] == 'g')))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_BEACH_GUY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_BEACH_GUY_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_BEACH_GUY_C;
                    case '4':
                    case 'd': return SQMOD_SKIN_BEACH_GUY_D;
                    case '5':
                    case 'e': return SQMOD_SKIN_BEACH_GUY_E;
                    case '6':
                    case 'f': return SQMOD_SKIN_BEACH_GUY_F;
                    case '7':
                    case 'g': return SQMOD_SKIN_BEACH_GUY_G;
                    case '8':
                    case 'h': return SQMOD_SKIN_BEACH_GUY_H;
                }
            }
            // [Be]ach [l]ady (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)
            else if (b == 'e' && (c == 'l' || (len > 4 && str[5] == 'l')))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_BEACH_LADY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_BEACH_LADY_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_BEACH_LADY_C;
                    case '4':
                    case 'd': return SQMOD_SKIN_BEACH_LADY_D;
                    case '5':
                    case 'e': return SQMOD_SKIN_BEACH_LADY_E;
                    case '6':
                    case 'f': return SQMOD_SKIN_BEACH_LADY_F;
                    case '7':
                    case 'g': return SQMOD_SKIN_BEACH_LADY_G;
                }
            }
            // [Bi]ker (#1|A)/(#2|B)
            else if (b == 'i' && (d == '1' || d == 'a')) return SQMOD_SKIN_BIKER_A;
            else if (b == 'i' && (d == '2' || d == 'b')) return SQMOD_SKIN_BIKER_B;
            // [Bum] [g]uy (#1|A)/(#2|B)/(#3|C)
            // [Bum] [l]ady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
            else if (b == 'u' && (c && (c == 'm' || c == 'g' || c == 'l')))
            {
                // [Bum] [g]uy (#1|A)/(#2|B)/(#3|C)
                if (c == 'g' || (len > 2 && str[3] == 'g'))
                {
                    if (d == '1' || d == 'a') return SQMOD_SKIN_BUM_GUY_A;
                    else if (d == '2' || d == 'b') return SQMOD_SKIN_BUM_GUY_B;
                    else if (d == '3' || d == 'c') return SQMOD_SKIN_BUM_GUY_C;
                }
                // [Bum] [l]ady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
                else if (c == 'l' || (len > 2 && str[3] == 'l'))
                {
                    if (d == '1' || d == 'a') return SQMOD_SKIN_BUM_LADY_A;
                    else if (d == '2' || d == 'b') return SQMOD_SKIN_BUM_LADY_B;
                    else if (d == '2' || d == 'c') return SQMOD_SKIN_BUM_LADY_C;
                    else if (d == '3' || d == 'd') return SQMOD_SKIN_BUM_LADY_D;
                    else if (d == '4' || d == 'e') return SQMOD_SKIN_BUM_LADY_E;
                }
            }
            // [Bus]iness [m]an (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
            else if (b == 'u' && (c == 's' || (len > 8 && str[9] == 'm')))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_BUSINESS_MAN_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_BUSINESS_MAN_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_BUSINESS_MAN_C;
                    case '4':
                    case 'd': return SQMOD_SKIN_BUSINESS_MAN_D;
                    case '5':
                    case 'e': return SQMOD_SKIN_BUSINESS_MAN_E;
                    case '6':
                    case 'f': return SQMOD_SKIN_BUSINESS_MAN_F;
                }
            }
        // [C]am, [C]am (Robber), [C]andy Suxx, [C]hef
        // [C]hurch guy, [C]hurch lady, [C]lub lady
        // [C]olumbian guy (#1|A)/(#2|B),
        // [C]onstruction worker (#1|A)/(#2|B)
        // [C]ool guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
        // [C]op, [C]ortez
        // [C]riminal (#1|A)/(#2|B)
        // [C]uban (#1|A)/(#2|B)
        case 'c':
            // [Ca]m, [Ca]m (Robber), [Ca]ndy Suxx
            if (b == 'a')
            {
                // [Cam] ([R]obbe[r])
                if (c && (c == 'm' || c == 'r') && d == 'r') return SQMOD_SKIN_CAM_ROBBER;
                // [Cam]
                else if (c == 'm') return SQMOD_SKIN_CAM;
                // [Can]dy [S]ux[x]
                else if (c && (c == 'n' || c == 's' || d == 'x')) return SQMOD_SKIN_CANDY_SUXX;
            }
            // [Ch]ef, [Ch]urch guy, [Ch]urch lady
            else if (b == 'h')
            {
                // [Che][f]
                if (c && (c == 'e' || d == 'f')) return SQMOD_SKIN_CHEF;
                // [Chu]rch [g]uy
                else if (c && ((c == 'u' && len > 5 && str[6] == 'g') || (c == 'g')))
                    return SQMOD_SKIN_CHURCH_GUY;
                // [Chu]rch [l]ady
                else if (c && ((c == 'u' && len > 5 && str[6] == 'l') || (c == 'l')))
                    return SQMOD_SKIN_CHURCH_LADY;
            }
            // [Cl]ub [l]ady
            else if (b == 'l') return SQMOD_SKIN_CLUB_LADY;
            // [Co]lumbian guy (#1|A)/(#2|B)
            // [Co]nstruction worker (#1|A)/(#2|B)
            // [Co]ol guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
            // [Co]p, [Co]rtez
            else if (b == 'o')
            {
                // [Col]umbian [g]uy (#1|A)/(#2|B)
                if (c && ((c == 'l' && len > 8 && str[9] == 'g') || (c == 'g')))
                {
                    if (d == '1' || d == 'a') return SQMOD_SKIN_COLUMBIAN_GUY_A;
                    else if (d == '2' || d == 'b') return SQMOD_SKIN_COLUMBIAN_GUY_B;
                }
                // [Con]struction [w]orker (#1|A)/(#2|B)
                else if (c && (c == 'n' || (len > 11 && str[12] == 'g')))
                {
                    if (d == '1' || d == 'a') return SQMOD_SKIN_CONSTRUCTION_WORKER_A;
                    else if (d == '2' || d == 'b') return SQMOD_SKIN_CONSTRUCTION_WORKER_B;
                }
                // [Coo]l guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
                else if (c == 'o')
                {
                    switch (d)
                    {
                        case '1':
                        case 'a': return SQMOD_SKIN_COOL_GUY_A;
                        case '2':
                        case 'b': return SQMOD_SKIN_COOL_GUY_B;
                        case '3':
                        case 'c': return SQMOD_SKIN_COOL_GUY_C;
                        case '4':
                        case 'd': return SQMOD_SKIN_COOL_GUY_D;
                    }
                }
                // [Cop]
                else if (c == 'p') return SQMOD_SKIN_COP;
                // [Cor]te[z]
                else if (c && (c == 'r' || c == 'z' || d == 'z')) return SQMOD_SKIN_CORTEZ;
            }
            // [Cr]iminal (#1|A)/(#2|B)
            else if (b == 'r' && (d == '1' || d == 'a')) return SQMOD_SKIN_CRIMINAL_A;
            else if (b == 'r' && (d == '2' || d == 'b')) return SQMOD_SKIN_CRIMINAL_B;
            // [Cu]ban (#1|A)/(#2|B)
            else if (b == 'u' && (d == '1' || d == 'a')) return SQMOD_SKIN_CUBAN_A;
            else if (b == 'u' && (d == '2' || d == 'b')) return SQMOD_SKIN_CUBAN_B;
        // [D]BP security (#1|A)/(#2|B)
        // [D]iaz guy (#1|A)/(#2|B)
        case 'd':
            switch (b)
            {
                // [DB]P [s]ecurity (#1|A)/(#2|B)
                case 'b':
                case 's':
                    if (d == '1' || d == 'a') return SQMOD_SKIN_DBP_SECURITY_A;
                    else if (d == '2' || d == 'b') return SQMOD_SKIN_DBP_SECURITY_B;
                // [Di]a[z] [g]uy (#1|A)/(#2|B)
                case 'i':
                case 'z':
                case 'g':
                    if (d == '1' || d == 'a') return SQMOD_SKIN_DIAZ_GUY_A;
                    else if (d == '2' || d == 'b') return SQMOD_SKIN_DIAZ_GUY_B;
            }
        // [F]BI, [F]ireman, [F]ood lady, [F]rench guy
        case 'f':
            switch (b)
            {
                // [FB]I
                case 'b': return SQMOD_SKIN_FBI;
                // [Fi]re[m]an
                case 'i':
                case 'm': return SQMOD_SKIN_FIREMAN;
                // [Fo]od [l]ady
                case 'o':
                case 'l': return SQMOD_SKIN_FOOD_LADY;
                // [Fr]ench [g]uy
                case 'r':
                case 'g': return SQMOD_SKIN_FRENCH_GUY;
            }
        // [G]arbageman (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
        // [G]olf guy (#1|A)/(#2|B)/(#3|C)
        // [G]olf lady
        // [G]ranny (#1|A)/(#2|B)
        // [G]ym guy, [G]ym lady
        case 'g':
            // [Ga]rbage[m]an (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
            if (b && (b == 'a' || b == 'm'))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_GARBAGEMAN_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_GARBAGEMAN_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_GARBAGEMAN_C;
                    case '4':
                    case 'd': return SQMOD_SKIN_GARBAGEMAN_D;
                    case '5':
                    case 'e': return SQMOD_SKIN_GARBAGEMAN_E;
                }
            }
            // [Go]lf [g]uy (#1|A)/(#2|B)/(#3|C)
            else if (b == 'o' && ((c == 'g') || (len > 3 && str[4] == 'g')))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_GOLF_GUY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_GOLF_GUY_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_GOLF_GUY_C;
                }
            }
            // [Go]lf [l]ady
            else if (b == 'o' && ((c == 'l') || (len > 3 && str[4] == 'l')))
                return SQMOD_SKIN_GOLF_LADY;
            // [Gr]anny (#1|A)/(#2|B)
            else if (b == 'r')
            {
                if (d == '1' || d == 'a') return SQMOD_SKIN_GRANNY_A;
                else if (d == '2' || d == 'b') return SQMOD_SKIN_GRANNY_B;
            }
            // [Gy]m [g]uy
            else if (b && (b == 'g' || (b == 'y' && len > 2 && str[3] == 'g')))
                return SQMOD_SKIN_GYM_GUY;
            // [Gy]m [l]ady
            else if (b && (b == 'l' || (b == 'y' && len > 2 && str[3] == 'l')))
                return SQMOD_SKIN_GYM_LADY;
        // [H]atian (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
        // [H]ilary, [H]ilary (Robber), [H]ood lady
        case 'h':
            // [H]atian (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
            if (b == 'a')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_HATIAN_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_HATIAN_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_HATIAN_C;
                    case '4':
                    case 'd': return SQMOD_SKIN_HATIAN_D;
                    case '5':
                    case 'e': return SQMOD_SKIN_HATIAN_E;
                }
            }
            // [Hi]lary ([R]obbe[r])
            else if (b && (b == 'i' || b == 'r') && d == 'r') return SQMOD_SKIN_HILARY_ROBBER;
            // [Hi]lary
            else if (b == 'i') return SQMOD_SKIN_HILARY;
            // [Ho]od [l]ady
            if (b && (b == 'o' || b == 'l')) return SQMOD_SKIN_HOOD_LADY;
        // [K]en Rosenburg
        case 'k':
            return SQMOD_SKIN_KEN_ROSENBURG;
        // [L]ance (#1|A)/(#1|B)
        // [L]ance (Cop)
        // [L]awyer
        // [L]ove Fist (#1|A)/(#2|B)/(#3|C)/(#3|D)
        case 'l':
            //[Lan]ce ([C]o[p])
            if ((b == 'a') && (c == 'n') && ((len > 4 && str[5] == 'c') || d == 'p'))
                return SQMOD_SKIN_LANCE_COP;
            else if (b && (b == 'c' ||  (b == 'a' && (c == 'n'))))
                return SQMOD_SKIN_LANCE_COP;
            // [La]nce (#1|A)/(#1|B)
            else if (b == 'a' && c == 'n')
            {
                if (d == '1' || d == 'a') return SQMOD_SKIN_LANCE_A;
                else if (d == '2' || d == 'b') return SQMOD_SKIN_LANCE_B;
            }
            // [Law]yer
            else if (b && (b == 'w' || (b == 'a' && c == 'w'))) return SQMOD_SKIN_LAWYER;
            // [Lo]ve [F]ist (#1|A)/(#2|B)/(#3|C)/(#3|D)
            else if (b && (b == 'o' || b == 'f'))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_LOVE_FIST_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_LOVE_FIST_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_LOVE_FIST_C;
                    case 'd': return SQMOD_SKIN_LOVE_FIST_D;
                }
            }
        // [M]ercades
        case 'm':
            if (d == 'b') return SQMOD_SKIN_MERCADES_B;
            else return SQMOD_SKIN_MERCADES_A;
        // [O]ffice lady (#1|A)/(#2|B)
        case 'o':
            if (d == '1' || d == 'a') return SQMOD_SKIN_OFFICE_LADY_A;
            else if (d == '2' || d == 'b') return SQMOD_SKIN_OFFICE_LADY_B;
        // [P]aramedic, [P]hil,  [P]hil (One arm), [P]hil (Robber)
        // [P]imp, [P]izzaman
        // [P]rostitute (#1|A)/(#2|B)/(#2|C)/(#2|D)/(#3|D)/(#4|D)
        // [P]unk (#1|A)/(#2|B)/(#3|C)
        case 'p':
            // [Pa]ramedic
            if (b == 'a') return SQMOD_SKIN_PARAMEDIC;
            // [Ph]il (One arm), [Ph]il (Robber)
            else if (b == 'h')
            {
                // [Ph]il ([O]ne ar[m])
                if (b == 'o' || (c == 'o') || (len > 3 && str[4] == 'o') || d == 'm')
                    return SQMOD_SKIN_PHIL_ONE_ARM;
                // [Ph]il ([R]obbe[r])
                else if (c && (c == 'r' || d == 'r' || (len > 3 && str[4] == 'r')))
                    return SQMOD_SKIN_PHIL_ROBBER;
                // [Phi]l
                else if (c == 'i') return SQMOD_SKIN_PHIL;
            }
            // [Pim][p]
            else if (b == 'i' && ((c == 'm') || d == 'p')) return SQMOD_SKIN_PIMP;
            // [Piz]zama[n]
            else if (b == 'i' && ((c == 'z') || d == 'n')) return SQMOD_SKIN_PIZZAMAN;
            // [Pr]ostitute (#1|A)/(#2|B)/(#2|C)/(#2|D)/(#3|D)/(#4|D)
            else if (b == 'r')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_PROSTITUTE_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_PROSTITUTE_B;
                    case 'c': return SQMOD_SKIN_PROSTITUTE_C;
                    case 'd': return SQMOD_SKIN_PROSTITUTE_D;
                    case '3':
                    case 'e': return SQMOD_SKIN_PROSTITUTE_E;
                    case '4':
                    case 'f': return SQMOD_SKIN_PROSTITUTE_F;
                }
            }
            // [Pu]nk (#1|A)/(#2|B)/(#3|C)
            else if (b == 'u')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_PUNK_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_PUNK_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_PUNK_C;
                }
            }
        // [R]ich guy, [R]ockstar guy
        case 'r':
            // [Ri]ch guy
            if (b == 'i') return SQMOD_SKIN_RICH_GUY;
            // [Ro]ckstar guy
            else if (b == 'o') return SQMOD_SKIN_ROCKSTAR_GUY;
        // [S]ailor (#1|A)/(#2|B)/(#3|C)
        // [S]hark (#1|A)/(#2|B)
        // [S]hopper (#1|A)/(#2|B)
        // [S]kate guy, [S]kate lady, [S]onny
        // [S]onny guy (#1|A)/(#2|B)/(#3|C)
        // [S]pandEx (#1|A)/(#2|B)
        // [S]panish guy
        // [S]panish lady (#1|A)/(#2|B)/(#3|C)/(#4|D)
        // [S]tore clerk
        // [S]tripper (#1|A)/(#2|B)/(#3|C)
        // [S]wat
        case 's':
            // [Sa]ilor (#1|A)/(#2|B)/(#3|C)
            if (b == 'a')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SAILOR_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SAILOR_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_SAILOR_C;
                }
            }
            // [S]hark (#1|A)/(#2|B)
            else if (b == 'h' && c == 'a')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SHARK_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SHARK_B;
                }
            }
            // [S]hopper (#1|A)/(#2|B)
            else if (b == 'h' && c == 'o')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SHOPPER_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SHOPPER_B;
                }
            }
            // [Sk]ate [g]uy
            else if (b == 'k' && ((c == 'g') || (len > 4 && str[5] == 'g')))
                return SQMOD_SKIN_SKATE_GUY;
            // [Sk]ate [l]ady
            else if (b == 'k' && ((c == 'l') || (len > 4 && str[5] == 'l')))
                return SQMOD_SKIN_SKATE_LADY;
            // [So]nny
            // [So]nny guy (#1|A)/(#2|B)/(#3|C)
            else if (b == 'o')
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SONNY_GUY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SONNY_GUY_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_SONNY_GUY_C;
                }
            }
            else if (b == 'g')
            {
                                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SONNY_GUY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SONNY_GUY_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_SONNY_GUY_C;
                }
            }
            // [Sp]andE[x] (#1|A)/(#2|B)
            else if (b == 'p' && ((c == 'x') || (len > 5 && str[6] == 'x')))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SPANDEX_GUY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SPANDEX_GUY_B;
                }
            }
            // [Sp]anish [g]uy
            else if (b == 'p' && ((c == 'g') || (len > 6 && str[7] == 'g')))
                return SQMOD_SKIN_SPANISH_GUY;
            // [Sp]anish [l]ady (#1|A)/(#2|B)/(#3|C)/(#4|D)
            else if (b == 'p' && ((c == 'l') || (len > 6 && str[7] == 'l')))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_SPANISH_LADY_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_SPANISH_LADY_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_SPANISH_LADY_C;
                    case '4':
                    case 'd': return SQMOD_SKIN_SPANISH_LADY_D;
                }
            }
            // [Sto]re clerk
            else if ((b == 't') && (c == 'o')) return SQMOD_SKIN_STORE_CLERK;
            // [Str]ipper (#1|A)/(#2|B)/(#3|C)
            else if ((b == 't') && (c == 'r'))
            {
                switch (d)
                {
                    case '1':
                    case 'a': return SQMOD_SKIN_STRIPPER_A;
                    case '2':
                    case 'b': return SQMOD_SKIN_STRIPPER_B;
                    case '3':
                    case 'c': return SQMOD_SKIN_STRIPPER_C;
                }
            }
            // [Sw]at
            else if (b == 'w') return SQMOD_SKIN_SWAT;
        // [T]axi driver (#1|A)/(#1|B)/(#2|C)/(#2|D)
        // [T]hug (#1|A)/(#2|B)
        // [T]ommy Vercetti
        // [T]ourist (#1|A)/(#2|B)
        // [T]ranny
        case 't':
            switch (b)
            {
                // [Ta]xi driver (#1|A)/(#1|B)/(#2|C)/(#2|D)
                case 'a':
                    switch (d)
                    {
                        case '1':
                        case 'a': return SQMOD_SKIN_TAXI_DRIVER_A;
                        case '2':
                        case 'b': return SQMOD_SKIN_TAXI_DRIVER_B;
                        case 'c': return SQMOD_SKIN_TAXI_DRIVER_C;
                        case 'd': return SQMOD_SKIN_TAXI_DRIVER_D;
                    }
                // [Th]ug (#1|A)/(#2|B)
                case 'h':
                    switch (d)
                    {
                        case '1':
                        case 'a': return SQMOD_SKIN_THUG_A;
                        case '5':
                        case 'b': return SQMOD_SKIN_THUG_B;
                    }
                // [To]mmy [V]ercetti
                // [To]urist (#1|A)/(#2|B)
                case 'v': return SQMOD_SKIN_TOMMY_VERCETTI;
                case 'o':
                    if (c == 'm') return SQMOD_SKIN_TOMMY_VERCETTI;
                    else if (c == 'u' && (d == '1' || d == 'a')) return SQMOD_SKIN_TOURIST_A;
                    else if (c == 'u' && (d == '2' || d == 'b')) return SQMOD_SKIN_TOURIST_B;
                case 'r': return SQMOD_SKIN_TRANNY;
            }
        // [U]ndercover cop (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
        case 'u':
            switch (d)
            {
                case '1':
                case 'a': return SQMOD_SKIN_UNDERCOVER_COP_A;
                case '2':
                case 'b': return SQMOD_SKIN_UNDERCOVER_COP_B;
                case '3':
                case 'c': return SQMOD_SKIN_UNDERCOVER_COP_C;
                case '4':
                case 'd': return SQMOD_SKIN_UNDERCOVER_COP_D;
                case '5':
                case 'e': return SQMOD_SKIN_UNDERCOVER_COP_E;
                case '6':
                case 'f': return SQMOD_SKIN_UNDERCOVER_COP_F;
            }
        // [V]ercetti guy (#1|A)/(#2|B)
        case 'v':
            switch (d)
            {
                case '1':
                case 'a': return SQMOD_SKIN_VERCETTI_GUY_A;
                case '2':
                case 'b': return SQMOD_SKIN_VERCETTI_GUY_B;
            }
        // [W]aitress (#1|A)/(#2|B)
        case 'w':
            switch (d)
            {
                case '1':
                case 'a': return SQMOD_SKIN_WAITRESS_A;
                case '2':
                case 'b': return SQMOD_SKIN_WAITRESS_B;
            }
        // Default to unknown
        default: return SQMOD_UNKNOWN;
    }
}

// ------------------------------------------------------------------------------------------------
bool IsSkinValid(SQInteger id)
{
    if (strcmp(GetSkinName(id), _SC("")) != 0) return SQTrue;
    return SQFalse;
}

// ------------------------------------------------------------------------------------------------
const SQChar * GetVehicleName(SQInteger id)
{
    switch(id)
    {
        case SQMOD_VEHICLE_LANDSTALKER:         return _SC("Landstalker");
        case SQMOD_VEHICLE_IDAHO:               return _SC("Idaho");
        case SQMOD_VEHICLE_STINGER:             return _SC("Stinger");
        case SQMOD_VEHICLE_LINERUNNER:          return _SC("Linerunner");
        case SQMOD_VEHICLE_PERENNIAL:           return _SC("Perennial");
        case SQMOD_VEHICLE_SENTINEL:            return _SC("Sentinel");
        case SQMOD_VEHICLE_RIO:                 return _SC("Rio");
        case SQMOD_VEHICLE_FIRETRUCK:           return _SC("Firetruck");
        case SQMOD_VEHICLE_TRASHMASTER:         return _SC("Trashmaster");
        case SQMOD_VEHICLE_STRETCH:             return _SC("Stretch");
        case SQMOD_VEHICLE_MANANA:              return _SC("Manana");
        case SQMOD_VEHICLE_INFERNUS:            return _SC("Infernus");
        case SQMOD_VEHICLE_VOODOO:              return _SC("Voodoo");
        case SQMOD_VEHICLE_PONY:                return _SC("Pony");
        case SQMOD_VEHICLE_MULE:                return _SC("Mule");
        case SQMOD_VEHICLE_CHEETAH:             return _SC("Cheetah");
        case SQMOD_VEHICLE_AMBULANCE:           return _SC("Ambulance");
        case SQMOD_VEHICLE_FBIWASHINGTON:       return _SC("FBI Washington");
        case SQMOD_VEHICLE_MOONBEAM:            return _SC("Moonbeam");
        case SQMOD_VEHICLE_ESPERANTO:           return _SC("Esperanto");
        case SQMOD_VEHICLE_TAXI:                return _SC("Taxi");
        case SQMOD_VEHICLE_WASHINGTON:          return _SC("Washington");
        case SQMOD_VEHICLE_BOBCAT:              return _SC("Bobcat");
        case SQMOD_VEHICLE_MRWHOOPEE:           return _SC("Mr. Whoopee");
        case SQMOD_VEHICLE_BFINJECTION:         return _SC("BF Injection");
        case SQMOD_VEHICLE_HUNTER:              return _SC("Hunter");
        case SQMOD_VEHICLE_POLICE:              return _SC("Police");
        case SQMOD_VEHICLE_ENFORCER:            return _SC("Enforcer");
        case SQMOD_VEHICLE_SECURICAR:           return _SC("Securicar");
        case SQMOD_VEHICLE_BANSHEE:             return _SC("Banshee");
        case SQMOD_VEHICLE_PREDATOR:            return _SC("Predator");
        case SQMOD_VEHICLE_BUS:                 return _SC("Bus");
        case SQMOD_VEHICLE_RHINO:               return _SC("Rhino");
        case SQMOD_VEHICLE_BARRACKSOL:          return _SC("Barracks OL");
        case SQMOD_VEHICLE_CUBANHERMES:         return _SC("Cuban Hermes");
        case SQMOD_VEHICLE_HELICOPTER:          return _SC("Helicopter");
        case SQMOD_VEHICLE_ANGEL:               return _SC("Angel");
        case SQMOD_VEHICLE_COACH:               return _SC("Coach");
        case SQMOD_VEHICLE_CABBIE:              return _SC("Cabbie");
        case SQMOD_VEHICLE_STALLION:            return _SC("Stallion");
        case SQMOD_VEHICLE_RUMPO:               return _SC("Rumpo");
        case SQMOD_VEHICLE_RCBANDIT:            return _SC("RC Bandit");
        case SQMOD_VEHICLE_HEARSE:              return _SC("Romero's Hearse");
        case SQMOD_VEHICLE_PACKER:              return _SC("Packer");
        case SQMOD_VEHICLE_SENTINELXS:          return _SC("Sentinel XS");
        case SQMOD_VEHICLE_ADMIRAL:             return _SC("Admiral");
        case SQMOD_VEHICLE_SQUALO:              return _SC("Squalo");
        case SQMOD_VEHICLE_SEASPARROW:          return _SC("Sea Sparrow");
        case SQMOD_VEHICLE_PIZZABOY:            return _SC("Pizza Boy");
        case SQMOD_VEHICLE_GANGBURRITO:         return _SC("Gang Burrito");
        case SQMOD_VEHICLE_AIRTRAIN:            return _SC("Airtrain");
        case SQMOD_VEHICLE_DEADDODO:            return _SC("Deaddodo");
        case SQMOD_VEHICLE_SPEEDER:             return _SC("Speeder");
        case SQMOD_VEHICLE_REEFER:              return _SC("Reefer");
        case SQMOD_VEHICLE_TROPIC:              return _SC("Tropic");
        case SQMOD_VEHICLE_FLATBED:             return _SC("Flatbed");
        case SQMOD_VEHICLE_YANKEE:              return _SC("Yankee");
        case SQMOD_VEHICLE_CADDY:               return _SC("Caddy");
        case SQMOD_VEHICLE_ZEBRACAB:            return _SC("Zebra Cab");
        case SQMOD_VEHICLE_TOPFUN:              return _SC("Top Fun");
        case SQMOD_VEHICLE_SKIMMER:             return _SC("Skimmer");
        case SQMOD_VEHICLE_PCJ600:              return _SC("PCJ-600");
        case SQMOD_VEHICLE_FAGGIO:              return _SC("Faggio");
        case SQMOD_VEHICLE_FREEWAY:             return _SC("Freeway");
        case SQMOD_VEHICLE_RCBARON:             return _SC("RC Baron");
        case SQMOD_VEHICLE_RCRAIDER:            return _SC("RC Raider");
        case SQMOD_VEHICLE_GLENDALE:            return _SC("Glendale");
        case SQMOD_VEHICLE_OCEANIC:             return _SC("Oceanic");
        case SQMOD_VEHICLE_SANCHEZ:             return _SC("Sanchez");
        case SQMOD_VEHICLE_SPARROW:             return _SC("Sparrow");
        case SQMOD_VEHICLE_PATRIOT:             return _SC("Patriot");
        case SQMOD_VEHICLE_LOVEFIST:            return _SC("Love Fist");
        case SQMOD_VEHICLE_COASTGUARD:          return _SC("Coast Guard");
        case SQMOD_VEHICLE_DINGHY:              return _SC("Dinghy");
        case SQMOD_VEHICLE_HERMES:              return _SC("Hermes");
        case SQMOD_VEHICLE_SABRE:               return _SC("Sabre");
        case SQMOD_VEHICLE_SABRETURBO:          return _SC("Sabre Turbo");
        case SQMOD_VEHICLE_PHOENIX:             return _SC("Phoenix");
        case SQMOD_VEHICLE_WALTON:              return _SC("Walton");
        case SQMOD_VEHICLE_REGINA:              return _SC("Regina");
        case SQMOD_VEHICLE_COMET:               return _SC("Comet");
        case SQMOD_VEHICLE_DELUXO:              return _SC("Deluxo");
        case SQMOD_VEHICLE_BURRITO:             return _SC("Burrito");
        case SQMOD_VEHICLE_SPANDEXPRESS:        return _SC("Spand Express");
        case SQMOD_VEHICLE_MARQUIS:             return _SC("Marquis");
        case SQMOD_VEHICLE_BAGGAGEHANDLER:      return _SC("Baggage Handler");
        case SQMOD_VEHICLE_KAUFMANCAB:          return _SC("Kaufman Cab");
        case SQMOD_VEHICLE_MAVERICK:            return _SC("Maverick");
        case SQMOD_VEHICLE_VCNMAVERICK:         return _SC("VCN Maverick");
        case SQMOD_VEHICLE_RANCHER:             return _SC("Rancher");
        case SQMOD_VEHICLE_FBIRANCHER:          return _SC("FBI Rancher");
        case SQMOD_VEHICLE_VIRGO:               return _SC("Virgo");
        case SQMOD_VEHICLE_GREENWOOD:           return _SC("Greenwood");
        case SQMOD_VEHICLE_CUBANJETMAX:         return _SC("Cuban Jetmax");
        case SQMOD_VEHICLE_HOTRINGRACER1:       return _SC("Hotring Racer #1");
        case SQMOD_VEHICLE_SANDKING:            return _SC("Sandking");
        case SQMOD_VEHICLE_BLISTACOMPACT:       return _SC("Blista Compact");
        case SQMOD_VEHICLE_POLICEMAVERICK:      return _SC("Police Maverick");
        case SQMOD_VEHICLE_BOXVILLE:            return _SC("Boxville");
        case SQMOD_VEHICLE_BENSON:              return _SC("Benson");
        case SQMOD_VEHICLE_MESAGRANDE:          return _SC("Mesa Grande");
        case SQMOD_VEHICLE_RCGOBLIN:            return _SC("RC Goblin");
        case SQMOD_VEHICLE_HOTRINGRACER2:       return _SC("Hotring Racer #2");
        case SQMOD_VEHICLE_HOTRINGRACER3:       return _SC("Hotring Racer #3");
        case SQMOD_VEHICLE_BLOODRINGBANGER1:    return _SC("Bloodring Banger #1");
        case SQMOD_VEHICLE_BLOODRINGBANGER2:    return _SC("Bloodring Banger #2");
        case SQMOD_VEHICLE_POLICECHEETAH:       return _SC("Vice Squad Cheetah");
        default:                                return _SC("");
    }
}

SQInteger GetVehicleID(const SQChar * name)
{
    // Clone the string into a clean editable version
    Sqrat::string str = CleanString(name);
    // See if we still have a valid name after the cleanup
    if(str.empty()) return SQMOD_UNKNOWN;
    // Grab the actual length of the string
    unsigned len = str.length();
    // Get the most significant characters used to identify a vehicle
    SQChar a = str[0], b = 0, c = 0, d = str[len-1];
    // Look for deeper specifiers
    if(str.length() >= 3)
    {
        c = str[2];
        b = str[1];
    }
    else if(str.length() >= 2)
    {
        b = str[1];
    }
    // Search for a pattern in the name
    switch (a)
    {
        // [A]dmiral
        // [A]irtrain
        // [A]mbulance
        // [A]ngel
        case 'a':
            switch (b)
            {
                // [Ad]miral
                case 'd': return SQMOD_VEHICLE_ADMIRAL;
                // [Ai]rtrain
                case 'i': return SQMOD_VEHICLE_AIRTRAIN;
                // [Am]bulance
                case 'm': return SQMOD_VEHICLE_AMBULANCE;
                // [An]gel
                case 'n': return SQMOD_VEHICLE_ANGEL;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }

        // [B]aggage Handler
        // [B]anshee
        // [B]arracks OL
        // [B]enson
        // [B]F Injection
        // [B]lista Compact
        // [B]loodring Banger #1
        // [B]loodring Banger #2
        // [B]obcat
        // [B]oxville
        // [B]urrito
        // [B]us
        case 'b':
            switch (b)
            {
                // [Ba]ggage Handler
                // [Ba]nshee
                // [Ba]rracks OL
                case 'a':
                    // [Bag]gage Handler
                    if (c == 'g') return SQMOD_VEHICLE_BAGGAGEHANDLER;
                    // [Ban]shee
                    else if (c == 'n') return SQMOD_VEHICLE_BANSHEE;
                    // [Bar]racks OL
                    else if (c == 'r') return SQMOD_VEHICLE_BARRACKS;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Be]nson
                case 'e': return SQMOD_VEHICLE_BENSON;
                // [BF] [I]njection
                case 'f':
                case 'i': return SQMOD_VEHICLE_BFINJECTION;
                // [Bl]ista Compact
                // [Bl]oodring Banger #1
                // [Bl]oodring Banger #2
                case 'l':
                    // [Bli]sta [C]ompact
                    if (b == 'c' || c == 'i') return SQMOD_VEHICLE_BLISTACOMPACT;
                    // [Blo]odring [B]anger (#1|A)
                    else if ((b == 'b' || c == 'o') && (d == '1' || d == 'a')) return SQMOD_VEHICLE_BLOODRINGBANGER1;
                    // [Blo]odring [B]anger (#2|B)
                    else if ((b == 'b' || c == 'o') && (d == '2' || d == 'b')) return SQMOD_VEHICLE_BLOODRINGBANGER2;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Bo]bcat
                // [Bo]xville
                case 'o':
                    // [Bob]cat
                    if (c == 'b') return SQMOD_VEHICLE_BOBCAT;
                    // [Box]ville
                    else if (c == 'x') return SQMOD_VEHICLE_BOXVILLE;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Bu]rrito
                // [Bu]s
                case 'u':
                    // [Bur]rito
                    if (c == 'r') return SQMOD_VEHICLE_BURRITO;
                    // [Bus]
                    else if (c == 's') return SQMOD_VEHICLE_BUS;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [C]abbie
        // [C]addy
        // [C]heetah
        // [C]oach
        // [C]oast Guard
        // [C]omet
        // [C]uban Hermes
        // [C]uban Jetmax
        case 'c':
            switch (b)
            {
                // [Ca]bbie
                // [Ca]ddy
                case 'a':
                    // [Cab]bie
                    if (c == 'b') return SQMOD_VEHICLE_CABBIE;
                    // [Cad]dy
                    else if (c == 'd') return SQMOD_VEHICLE_CADDY;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Ch]eetah
                case 'h': return SQMOD_VEHICLE_CHEETAH;
                // [Co]ach
                // [Co]ast Guard
                // [Co]met
                case 'o':
                    // [Coa]c[h]
                    if (c == 'a' && d == 'h') return SQMOD_VEHICLE_COACH;
                    // [Coa]s[t] Guar[d]
                    else if (c == 'a' && (d == 't' || d == 'd')) return SQMOD_VEHICLE_COASTGUARD;
                    // [Co]met
                    else if (c == 'm') return SQMOD_VEHICLE_COMET;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Cu]ban Hermes
                // [Cu]ban Jetmax
                case 'u':
                    // [Cub]an [H]erme[s]
                    if ((len > 4 && str[5] == 'h') || (d == 's' || d == 'h')) return SQMOD_VEHICLE_CUBANHERMES;
                    // [Cub]an [J]etma[x]
                    if ((len > 4 && str[5] == 'j') || (d == 'x' || d == 'j')) return SQMOD_VEHICLE_CUBANJETMAX;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [D]eaddodo
        // [D]eluxo
        // [D]inghy
        case 'd':
            switch (b)
            {
                // [De]addodo
                // [De]luxo
                case 'e':
                    // [Dea]ddodo
                    if (c == 'a') return SQMOD_VEHICLE_DEADDODO;
                    // [Del]uxo
                    else if (c == 'l') return SQMOD_VEHICLE_DELUXO;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Di]nghy
                case 'i': return SQMOD_VEHICLE_DINGHY;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [E]speranto
        // [E]nforcer
        case 'e':
            // [Es]peranto
            if (b && b == 's') return SQMOD_VEHICLE_ESPERANTO;
            // [En]forcer
            else if (b && b == 'n') return SQMOD_VEHICLE_ENFORCER;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [F]aggio
        // [F]BI Rancher
        // [F]BI Washington
        // [F]iretruck
        // [F]latbed
        // [F]reeway
        case 'f':
            switch (b)
            {
                // [Fa]ggio
                case 'a': return SQMOD_VEHICLE_FAGGIO;
                // [FB]I Rancher
                // [FB]I Washington
                case 'b':
                    // [FB]I [R]anche[r]
                    if ((len > 2 && str[3] == 'r') || d == 'r') return SQMOD_VEHICLE_FBIRANCHER;
                    // [FB]I [W]ashingto[n]
                    else if ((len > 2 && str[3] == 'w') || (d == 'n' || d == 'w')) return SQMOD_VEHICLE_FBIWASHINGTON;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Fi]retruck
                case 'i': return SQMOD_VEHICLE_FIRETRUCK;
                // [Fl]atbed
                case 'l': return SQMOD_VEHICLE_FLATBED;
                // [Fr]eeway
                case 'r': return SQMOD_VEHICLE_FREEWAY;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [G]ang Burrito
        // [G]lendale
        // [G]reenwood
        case 'g':
            switch (b)
            {
                // [Ga]ng Burrito
                case 'a': return SQMOD_VEHICLE_GANGBURRITO;
                // [Gl]endale
                case 'l': return SQMOD_VEHICLE_GLENDALE;
                // [Gr]eenwood
                case 'r': return SQMOD_VEHICLE_GREENWOOD;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [H]elicopter
        // [H]ermes
        // [H]otring Racer (#1|A)(#2|B)(#3|C)
        // [H]unter
        case 'h':
            switch (b)
            {
                // [He]licopter
                // [He]rmes
                case 'e':
                    // [Hel]icopter
                    if (c == 'l') return SQMOD_VEHICLE_HELICOPTER;
                    // [Her]mes
                    else if (c == 'r') return SQMOD_VEHICLE_HERMES;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Ho]tring Racer (#1|A)(#2|B)(#3|C)
                case 'o':
                    switch (d)
                    {
                        case '1':
                        case 'a': return SQMOD_VEHICLE_HOTRINGRACER1;
                        case '2':
                        case 'b': return SQMOD_VEHICLE_HOTRINGRACER2;
                        case '3':
                        case 'c': return SQMOD_VEHICLE_HOTRINGRACER3;
                        // Default to unknwon
                        default: return SQMOD_UNKNOWN;
                    }
                // [Hu]nter
                case 'u': return SQMOD_VEHICLE_HUNTER;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [I]daho
        // [I]nfernus
        case 'i':
            // [Id]aho
            if (b && b == 'd') return SQMOD_VEHICLE_IDAHO;
            // [In]fernus
            else if (b && b == 'n') return SQMOD_VEHICLE_INFERNUS;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [K]aufman Cab
        case 'k': return SQMOD_VEHICLE_KAUFMANCAB;
        // [L]andstalker
        // [L]inerunner
        // [L]ove Fist
        case 'l':
            switch (b)
            {
                // [La]ndstalker
                case 'a': return SQMOD_VEHICLE_LANDSTALKER;
                // [Li]nerunner
                case 'i': return SQMOD_VEHICLE_LINERUNNER;
                // [Lo]ve Fist
                case 'o': return SQMOD_VEHICLE_LOVEFIST;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;

            }
        // [M]anana
        // [M]arquis
        // [M]averick
        // [M]esa Grande
        // [M]oonbeam
        // [M]r. Whoopee
        // [M]ule
        case 'm':
            switch (b)
            {
                // [Ma]nana
                // [Ma]rquis
                // [Ma]verick
                case 'a':
                    // [Man]ana
                    if (c == 'n') return SQMOD_VEHICLE_MANANA;
                    // [Mar]quis
                    else if (c == 'r') return SQMOD_VEHICLE_MARQUIS;
                    // [Mav]erick
                    else if (c == 'v') return SQMOD_VEHICLE_MAVERICK;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Me]sa Grande
                case 'e': return SQMOD_VEHICLE_MESAGRANDE;
                // [Mo]onbeam
                case 'o': return SQMOD_VEHICLE_MOONBEAM;
                // [Mr]. Whoopee
                case 'r': return SQMOD_VEHICLE_MRWHOOPEE;
                // [Mu]le
                case 'u': return SQMOD_VEHICLE_MULE;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [O]ceanic
        case 'o': return SQMOD_VEHICLE_OCEANIC;
        // [P]acker
        // [P]atriot
        // [P]CJ-600
        // [P]erennial
        // [P]hoenix
        // [P]izza Boy
        // [P]olice
        // [P]olice Maverick
        // [P]ony
        // [P]redator
        case 'p':
            switch (b)
            {
                // [Pa]cker
                // [Pa]triot
                case 'a':
                    // [Pac]ker
                    if (c == 'c') return SQMOD_VEHICLE_PACKER;
                    // [Pat]riot
                    else if (c == 't') return SQMOD_VEHICLE_PATRIOT;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [PC]J-600
                case 'c': return SQMOD_VEHICLE_PCJ600;
                // [Pe]rennial
                case 'e': return SQMOD_VEHICLE_PERENNIAL;
                // [Ph]oenix
                case 'h': return SQMOD_VEHICLE_PHOENIX;
                // [Pi]zza Boy
                case 'i':
                // [Po]lice
                // [Po]lice Maverick
                // [Po]ny
                case 'o':
                    // [Po]lice
                    if (d == 'e') return SQMOD_VEHICLE_POLICE;
                    // [Po]lice Maverick
                    else if ((len > 5 && str[6] == 'm') || (d == 'k' || d == 'm')) return SQMOD_VEHICLE_POLICEMAVERICK;
                    // [Po]ny
                    else if (c == 'n') return SQMOD_VEHICLE_PONY;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Pr]edator
                case 'r': return SQMOD_VEHICLE_PREDATOR;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [R]ancher
        // [R]C Bandit
        // [R]C Baron
        // [R]C Goblin
        // [R]C Raider
        // [R]eefer
        // [R]egina
        // [R]hino
        // [R]io
        // [R]omero's Hearse
        // [R]umpo
        case 'r':
            switch (b)
            {
                // [Ra]ncher
                case 'a': return SQMOD_VEHICLE_RANCHER;
                // [RC] Bandit
                // [RC] Baron
                // [RC] Goblin
                // [RC] Raider
                case 'c':
                    // [RC] [B]andi[t]
                    if (c == 'b' && d == 't') return SQMOD_VEHICLE_RCBANDIT;
                    // [RC] [B]aro[n]
                    else if (c == 'b' && d == 'n') return SQMOD_VEHICLE_RCBARON;
                    // [RC] [G]oblin
                    else if (c == 'g') return SQMOD_VEHICLE_RCGOBLIN;
                    // [RC] [R]aide[r]
                    else if (c == 'r' || d == 'r') return SQMOD_VEHICLE_RCRAIDER;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Re]efer
                // [Re]gina
                case 'e':
                    // [Ree]fer
                    if (c == 'e' || d == 'r') return SQMOD_VEHICLE_REEFER;
                    // [Reg]ina
                    else if (c == 'g' || d == 'a') return SQMOD_VEHICLE_REGINA;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Rh]ino
                case 'h': return SQMOD_VEHICLE_RHINO;
                // [Ri]o
                case 'i': return SQMOD_VEHICLE_RIO;
                // [Ro]mero's Hearse
                case 'o': return SQMOD_VEHICLE_HEARSE;
                // [Ru]mpo
                case 'u': return SQMOD_VEHICLE_RUMPO;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [S]abre
        // [S]abre Turbo
        // [S]anchez
        // [S]andking
        // [S]ea Sparrow
        // [S]ecuricar
        // [S]entinel
        // [S]entinel XS
        // [S]kimmer
        // [S]pand Express
        // [S]parrow
        // [S]peeder
        // [S]qualo
        // [S]tallion
        // [S]tinger
        // [S]tretch
        case 's':
            switch (b)
            {
                // [Sa]bre
                // [Sa]bre Turbo
                // [Sa]nchez
                // [Sa]ndking
                case 'a':
                    // [Sab]r[e]
                    if (c == 'b' && d == 'e') return SQMOD_VEHICLE_SABRE;
                    // [Sab]re [T]urb[o]
                    else if ((c == 'b' && d == 'o') || (len > 4 && str[5 ]== 't')) return SQMOD_VEHICLE_SABRETURBO;
                    // [Sa]n[c]he[z]
                    else if (d == 'c' || d == 'z') return SQMOD_VEHICLE_SANCHEZ;
                    // [Sa]n[d]kin[g]
                    else if (d == 'd' || d == 'g') return SQMOD_VEHICLE_SANDKING;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Se]a Sparrow
                // [Se]curicar
                // [Se]ntinel
                // [Se]ntinel XS
                case 'e':
                    // [Sea] Sparro[w]
                    if (c == 'e' || d == 'w') return SQMOD_VEHICLE_SEASPARROW;
                    // [Sec]urica[r]
                    else if (c == 'c' || d == 'r') return SQMOD_VEHICLE_SECURICAR;
                    // [Sen]tine[l]
                    else if (c == 'n' && d == 'l') return SQMOD_VEHICLE_SENTINEL;
                    // [Sen]tinel X[S]
                    else if (c == 'n' && d == 's') return SQMOD_VEHICLE_SENTINELXS;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Sk]immer
                case 'k': return SQMOD_VEHICLE_SKIMMER;
                // [Sp]and Express
                // [Sp]arrow
                // [Sp]eeder
                case 'p':
                    // [Spa]nd [E]xpres[s]
                    if (c == 'a' || ((len > 4 && str[5] == 'e') || d == 's')) return SQMOD_VEHICLE_SPANDEXPRESS;
                    // [Spa]rro[w]
                    else if (d == 'w' && (c == 'a' && d == 'w')) return SQMOD_VEHICLE_SPARROW;
                    // [Spe]ede[r]
                    else if (c == 'e' || d == 'r') return SQMOD_VEHICLE_SPEEDER;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Sq]ualo
                case 'q': return SQMOD_VEHICLE_SQUALO;
                // [St]allion
                // [St]inger
                // [St]retch
                case 't':
                    // [Sta]llion
                    if (c == 'a') return SQMOD_VEHICLE_STALLION;
                    // [Sti]nger
                    if (c == 'i') return SQMOD_VEHICLE_STINGER;
                    // [Str]etch
                    if (c == 'r') return SQMOD_VEHICLE_STRETCH;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [T]axi
        // [T]op Fun
        // [T]rashmaster
        // [T]ropic
        case 't':
            switch (b)
            {
                // [Ta]xi
                case 'a': return SQMOD_VEHICLE_TAXI;
                // [To]p Fun
                case 'o': return SQMOD_VEHICLE_TOPFUN;
                // [Tr]ashmaster
                // [Tr]opic
                case 'r':
                    // [Tr]ashmaster
                    if (c == 'a') return SQMOD_VEHICLE_TRASHMASTER;
                    // [Tr]opic
                    if (c == 'o') return SQMOD_VEHICLE_TROPIC;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [V]CN Maverick
        // [V]ice Squad Cheetah
        // [V]irgo
        // [V]oodoo
        case 'v':
            switch (b)
            {
                // [VC]N Maverick
                case 'c': return SQMOD_VEHICLE_VCNMAVERICK;
                // [Vi]ce Squad Cheetah
                // [Vi]rgo
                case 'i':
                    // [Vic]e Squad Cheetah
                    if (c == 'a') return SQMOD_VEHICLE_VICECHEE;
                    // [Vir]go
                    if (c == 'o') return SQMOD_VEHICLE_VIRGO;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Vo]odoo
                case 'o': return SQMOD_VEHICLE_VOODOO;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [W]alton
        // [W]ashington
        case 'w':
            // [Wa]lton
            if (b == 'a' && c == 'l') return SQMOD_VEHICLE_WALTON;
            // [Wa]shington
            else if (b == 'a' && c == 's') return SQMOD_VEHICLE_WASHINGTON;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [Y]ankee
        case 'y': return SQMOD_VEHICLE_YANKEE;
        // [Z]ebra Cab
        case 'z': return SQMOD_VEHICLE_ZEBRACAB;
        // Default to unknwon
        default: return SQMOD_UNKNOWN;
    }
}

bool IsVehicleValid(SQInteger id)
{
    if (strcmp(GetVehicleName(id), _SC("")) != 0) return SQTrue;
    return SQFalse;
}

// ------------------------------------------------------------------------------------------------
const SQChar * GetWeaponName(SQInteger id)
{
    switch (id)
    {
        case SQMOD_WEAPON_UNARMED:          return _SC("Unarmed");
        case SQMOD_WEAPON_BRASSKNUCKLES:    return _SC("Brass Knuckles");
        case SQMOD_WEAPON_SCREWDRIVER:      return _SC("Screwdriver");
        case SQMOD_WEAPON_GOLFCLUB:         return _SC("Golf Club");
        case SQMOD_WEAPON_NIGHTSTICK:       return _SC("Nightstick");
        case SQMOD_WEAPON_KNIFE:            return _SC("Knife");
        case SQMOD_WEAPON_BASEBALLBAT:      return _SC("Baseball Bat");
        case SQMOD_WEAPON_HAMMER:           return _SC("Hammer");
        case SQMOD_WEAPON_MEATCLEAVER:      return _SC("Meat Cleaver");
        case SQMOD_WEAPON_MACHETE:          return _SC("Machete");
        case SQMOD_WEAPON_KATANA:           return _SC("Katana");
        case SQMOD_WEAPON_CHAINSAW:         return _SC("Chainsaw");
        case SQMOD_WEAPON_GRENADE:          return _SC("Grenade");
        case SQMOD_WEAPON_REMOTE:           return _SC("Remote Detonation Grenade");
        case SQMOD_WEAPON_TEARGAS:          return _SC("Tear Gas");
        case SQMOD_WEAPON_MOLOTOV:          return _SC("Molotov Cocktails");
        case SQMOD_WEAPON_ROCKET:           return _SC("Rocket");
        case SQMOD_WEAPON_COLT45:           return _SC("Colt .45");
        case SQMOD_WEAPON_PYTHON:           return _SC("Python");
        case SQMOD_WEAPON_SHOTGUN:          return _SC("Pump-Action Shotgun");
        case SQMOD_WEAPON_SPAS12:           return _SC("SPAS-12 Shotgun");
        case SQMOD_WEAPON_STUBBY:           return _SC("Stubby Shotgun");
        case SQMOD_WEAPON_TEC9:             return _SC("TEC-9");
        case SQMOD_WEAPON_UZI:              return _SC("Uzi");
        case SQMOD_WEAPON_INGRAM:           return _SC("Silenced Ingram");
        case SQMOD_WEAPON_MP5:              return _SC("MP5");
        case SQMOD_WEAPON_M4:               return _SC("M4");
        case SQMOD_WEAPON_RUGER:            return _SC("Ruger");
        case SQMOD_WEAPON_SNIPER:           return _SC("Sniper Rifle");
        case SQMOD_WEAPON_LASERSCOPE:       return _SC("Laserscope Sniper Rifle");
        case SQMOD_WEAPON_ROCKETLAUNCHER:   return _SC("Rocket Launcher");
        case SQMOD_WEAPON_FLAMETHROWER:     return _SC("Flamethrower");
        case SQMOD_WEAPON_M60:              return _SC("M60");
        case SQMOD_WEAPON_MINIGUN:          return _SC("Minigun");
        case SQMOD_WEAPON_BOMB:             return _SC("Bomb");
        case SQMOD_WEAPON_HELICANNON:       return _SC("Helicannon");
        case SQMOD_WEAPON_CAMERA:           return _SC("Camera");
        case SQMOD_WEAPON_VEHICLE:          return _SC("Vehicle");
        case SQMOD_WEAPON_EXPLOSION1:       return _SC("Explosion");
        case SQMOD_WEAPON_DRIVEBY:          return _SC("Driveby");
        case SQMOD_WEAPON_DROWNED:          return _SC("Drowned");
        case SQMOD_WEAPON_FALL:             return _SC("Fall");
        case SQMOD_WEAPON_EXPLOSION2:       return _SC("Explosion");
        case SQMOD_WEAPON_SUICIDE:          return _SC("Suicide");
        default:                            return _SC("");
    }
}

// ------------------------------------------------------------------------------------------------
SQInteger GetWeaponID(const SQChar * name)
{
    // Clone the string into a clean editable version
    Sqrat::string str = CleanString(name);
    // See if we still have a valid name after the cleanup
    if(str.length() < 1) return SQMOD_UNKNOWN;
    // Grab the actual length of the string
    unsigned len = str.length();
    // Get the most significant characters used to identify a weapon
    SQChar a = str[0], b = 0, c = 0, d = str[len-1];
    // Look for deeper specifiers
    if(str.length() >= 3)
    {
        c = str[2];
        b = str[1];
    }
    else if(str.length() >= 2)
    {
        b = str[1];
    }
    // Search for a pattern in the name
    switch(a)
    {
        // [B]aseball Bat
        // [B]omb
        // [B]rass Knuckles
        case 'b':
            // [Ba]seball Bat
            if (b == 'a') return SQMOD_WEAPON_BASEBALLBAT;
            // [Bo]mb
            else if (b == 'o') return SQMOD_WEAPON_BOMB;
            // [Br]ass Knuckles
            else if (b == 'r') return SQMOD_WEAPON_BRASSKNUCKLES;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [C]amera
        // [C]hainsaw
        // [C]olt .45
        case 'c':
            // [Ca]mera
            if (b == 'a') return SQMOD_WEAPON_CAMERA;
            // [Ch]ainsaw
            else if (b == 'h') return SQMOD_WEAPON_CHAINSAW;
            // [Co]lt .45
            else if (b == 'o') return SQMOD_WEAPON_COLT45;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [D]riveby
        // [D]rowned
        case 'd':
            // [Dr]iveby
            if (b == 'r' && (c == 'i' || d == 'y')) return SQMOD_WEAPON_DRIVEBY;
            // [Dr]owned
            else if (b == 'r' && (c == 'o' || d == 'd')) return SQMOD_WEAPON_DROWNED;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [E]xplosion
        case 'e': return SQMOD_WEAPON_EXPLOSION2;
        // [F]all
        // [F]lamethrower
        case 'f':
            // [Fa]ll
            if (b == 'a') return SQMOD_WEAPON_FALL;
            // [Fl]amethrower
            else if (b == 'l') return SQMOD_WEAPON_FLAMETHROWER;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [G]olf Club
        // [G]renade
        case 'g':
            // [Go]lf Club
            if (b == 'o') return SQMOD_WEAPON_GOLFCLUB;
            // [Gr]enade
            else if (b == 'r') return SQMOD_WEAPON_GRENADE;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [H]ammer
        // [H]elicannon
        case 'h':
            // [Ha]mmer
            if (b == 'a') return SQMOD_WEAPON_HAMMER;
            // [He]licannon
            else if (b == 'e') return SQMOD_WEAPON_HELICANNON;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [K]atana
        // [K]nife
        case 'k':
            // [Ka]tana
            if (b == 'a') return SQMOD_WEAPON_KATANA;
            // [Kn]ife
            else if (b == 'n') return SQMOD_WEAPON_KNIFE;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [L]aserscope Sniper Rifle
        case 'l': return SQMOD_WEAPON_LASERSCOPE;
        // [M]4
        // [M]60
        // [M]achete
        // [M]eat Cleaver
        // [M]inigun
        // [M]olotov Cocktails
        // [M]P5
        case 'm':
            // [M4]
            if (b == '4') return SQMOD_WEAPON_M4;
            // [M6]0
            else if (b == '6') return SQMOD_WEAPON_M60;
            // [Ma]chete
            else if (b == 'a') return SQMOD_WEAPON_MACHETE;
            // [Me]at Cleaver
            else if (b == 'e') return SQMOD_WEAPON_MEATCLEAVER;
            // [Mi]nigun
            else if (b == 'i') return SQMOD_WEAPON_MINIGUN;
            // [Mo]lotov Cocktails
            else if (b == 'o') return SQMOD_WEAPON_MOLOTOV;
            // [MP]5
            else if (b == 'p') return SQMOD_WEAPON_MP5;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [N]ightstick
        case 'n': return SQMOD_WEAPON_NIGHTSTICK;
        // [P]ump-Action Shotgun
        // [P]ython
        case 'p':
            // [Pu]mp-Action Shotgun
            if (b == 'u') return SQMOD_WEAPON_SHOTGUN;
            // [Py]thon
            else if (b == 'y') return SQMOD_WEAPON_PYTHON;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [R]emote Detonation Grenade
        // [R]ocket
        // [R]ocket Launcher
        // [R]uger
        case 'r':
            // [Re]mote Detonation Grenade
            if (b == 'e') return SQMOD_WEAPON_REMOTE;
            // [Ro]cke[t]
            else if (b == 'o' && d == 't') return SQMOD_WEAPON_ROCKET;
            // [Ro]cket [L]aunche[r]
            else if (b == 'o' && (d == 'r' || d == 'l' || (len > 5 && str[6] == 'l'))) return SQMOD_WEAPON_ROCKETLAUNCHER;
            // [Ru]ger
            else if (b == 'u') return SQMOD_WEAPON_RUGER;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [S]crewdriver
        // [S]ilenced Ingram
        // [S]niper Rifle
        // [S]PAS-12 Shotgun
        // [S]tubby Shotgun
        // [S]uicide
        case 's':
            // [Sc]rewdriver
            if (b == 'c') return SQMOD_WEAPON_SCREWDRIVER;
            // [Si]lenced Ingram
            else if (b == 'i') return SQMOD_WEAPON_INGRAM;
            // [Sn]iper Rifle
            else if (b == 'n') return SQMOD_WEAPON_SNIPER;
            // [SP]AS-12 Shotgun
            else if (b == 'p') return SQMOD_WEAPON_SPAS12;
            // [St]ubby Shotgun
            else if (b == 't') return SQMOD_WEAPON_STUBBY;
            // [Su]icide
            else if (b == 'u') return SQMOD_WEAPON_SUICIDE;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [T]ear Gas
        // [T]EC-9
        case 't':
            // [Tea]r Ga[s]
            if (b == 'e' && (c == 'a' || d == 's')) return SQMOD_WEAPON_TEARGAS;
            // [TEC]-[9]
            else if (b == 'e' && (c == 'c' || d == '9')) return SQMOD_WEAPON_TEC9;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [U]narmed
        // [U]zi
        case 'u':
            // [Un]armed
            if (b == 'n') return SQMOD_WEAPON_UNARMED;
            // [Uz]i
            else if (b == 'z') return SQMOD_WEAPON_UZI;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [V]ehicle
        case 'v': return SQMOD_WEAPON_VEHICLE;
        // Default to unknwon
        default: return SQMOD_UNKNOWN;
    }
}

// ------------------------------------------------------------------------------------------------
bool IsWeaponValid(SQInteger id)
{
    if (strcmp(GetWeaponName(id), _SC("")) != 0) return SQTrue;
    else return SQFalse;
}

// ------------------------------------------------------------------------------------------------
bool IsWeaponNatural(SQInteger id)
{
    switch (id)
    {
        case SQMOD_WEAPON_VEHICLE:
        case SQMOD_WEAPON_DRIVEBY:
        case SQMOD_WEAPON_DROWNED:
        case SQMOD_WEAPON_FALL:
        case SQMOD_WEAPON_EXPLOSION2:
        case SQMOD_WEAPON_SUICIDE: return SQTrue;
        default: return SQFalse;
    }
}

// ------------------------------------------------------------------------------------------------
SQInteger WeaponToModel(SQInteger id)
{
    switch (id)
    {
        case SQMOD_WEAPON_UNARMED:          return 293;
        case SQMOD_WEAPON_BRASSKNUCKLES:    return 259;
        case SQMOD_WEAPON_SCREWDRIVER:      return 260;
        case SQMOD_WEAPON_GOLFCLUB:         return 261;
        case SQMOD_WEAPON_NIGHTSTICK:       return 262;
        case SQMOD_WEAPON_KNIFE:            return 263;
        case SQMOD_WEAPON_BASEBALLBAT:      return 264;
        case SQMOD_WEAPON_HAMMER:           return 265;
        case SQMOD_WEAPON_MEATCLEAVER:      return 266;
        case SQMOD_WEAPON_MACHETE:          return 267;
        case SQMOD_WEAPON_KATANA:           return 268;
        case SQMOD_WEAPON_CHAINSAW:         return 269;
        case SQMOD_WEAPON_GRENADE:          return 270;
        case SQMOD_WEAPON_REMOTE:           return 291;
        case SQMOD_WEAPON_TEARGAS:          return 271;
        case SQMOD_WEAPON_MOLOTOV:          return 272;
        case SQMOD_WEAPON_ROCKET:           return 273;
        case SQMOD_WEAPON_COLT45:           return 274;
        case SQMOD_WEAPON_PYTHON:           return 275;
        case SQMOD_WEAPON_SHOTGUN:          return 277;
        case SQMOD_WEAPON_SPAS12:           return 278;
        case SQMOD_WEAPON_STUBBY:           return 279;
        case SQMOD_WEAPON_TEC9:             return 281;
        case SQMOD_WEAPON_UZI:              return 282;
        case SQMOD_WEAPON_INGRAM:           return 283;
        case SQMOD_WEAPON_MP5:              return 284;
        case SQMOD_WEAPON_M4:               return 280;
        case SQMOD_WEAPON_RUGER:            return 276;
        case SQMOD_WEAPON_SNIPER:           return 285;
        case SQMOD_WEAPON_LASERSCOPE:       return 286;
        case SQMOD_WEAPON_ROCKETLAUNCHER:   return 287;
        case SQMOD_WEAPON_FLAMETHROWER:     return 288;
        case SQMOD_WEAPON_M60:              return 289;
        case SQMOD_WEAPON_MINIGUN:          return 290;
        case SQMOD_WEAPON_BOMB:             return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_HELICANNON:       return 294;
        case SQMOD_WEAPON_CAMERA:           return 292;
        case SQMOD_WEAPON_VEHICLE:          return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_EXPLOSION1:       return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_DRIVEBY:          return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_DROWNED:          return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_FALL:             return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_EXPLOSION2:       return SQMOD_UNKNOWN;
        case SQMOD_WEAPON_SUICIDE:          return SQMOD_UNKNOWN;
        default:                            return SQMOD_UNKNOWN;
    }
}

// ------------------------------------------------------------------------------------------------
const SQChar * GetDistrictName ( SQFloat x, SQFloat y )
{
    if( x > -1613.03f && y > 413.218f && x < -213.73f && y < 1677.32f )
        return "Downtown Vice City";
    else if( x > 163.656f && y > -351.153f && x < 1246.03f && y < 1398.85f )
        return "Vice Point";
    else if( x > -103.97f && y > -930.526f && x < 1246.03f && y < -351.153f )
        return "Washington Beach";
    else if( x > -253.206f && y > -1805.37f && x < 1254.9f && y < -930.526f )
        return "Ocean Beach";
    else if( x > -1888.21f && y > -1779.61f && x < -1208.21f && y < 230.39f )
        return "Escobar International Airport";
    else if( x > -748.206f && y > -818.266f && x < -104.505f && y < -241.467f )
        return "Starfish Island";
    else if( x > -213.73f && y > 797.605f && x < 163.656f && y < 1243.47f )
        return "Prawn Island";
    else if( x > -213.73f && y > -241.429f && x < 163.656f && y < 797.605f )
        return "Leaf Links";
    else if( x > -1396.76f && y > -42.9113f && x < -1208.21f && y < 230.39f )
        return "Junkyard";
    else if( x > -1208.21f && y > -1779.61f &&  x < -253.206f && y < -898.738f )
        return "Viceport";
    else if( x > -1208.21f && y > -898.738f && x < -748.206f && y < -241.467f )
        return "Little Havana";
    else if( x > -1208.21f && y > -241.467f && x < -578.289f && y < 412.66f )
        return "Little Haiti";
    else
        return "Vice City";
}

// ------------------------------------------------------------------------------------------------
void RegisterIdentifiers()
{
    Sqrat::ConstTable().Enum(_SC("SQMOD"), Sqrat::Enumeration()
        .Const(_SC("SUCCESS"),      SQMOD_SUCCESS)
        .Const(_SC("FAILURE"),      SQMOD_FAILURE)
        .Const(_SC("UNKNOWN"),      SQMOD_UNKNOWN)
        .Const(_SC("ARCH"),         SQMOD_ARCHITECTURE)
        .Const(_SC("PLATFORM"),     SQMOD_PLATFORM)
        .Const(_SC("MIN_CHAR"),     std::numeric_limits<SQChar>::min())
        .Const(_SC("MAX_CHAR"),     std::numeric_limits<SQChar>::max())
        .Const(_SC("MIN_SHORT"),    std::numeric_limits<int16_t>::min())
        .Const(_SC("MAX_SHORT"),    std::numeric_limits<int16_t>::max())
        .Const(_SC("MIN_USHORT"),   std::numeric_limits<uint16_t>::min())
        .Const(_SC("MAX_USHORT"),   std::numeric_limits<uint16_t>::max())
        .Const(_SC("MIN_INT"),      std::numeric_limits<SQInteger>::min())
        .Const(_SC("MAX_INT"),      std::numeric_limits<SQInteger>::max())
        .Const(_SC("MIN_INT32"),    std::numeric_limits<SQInt32>::min())
        .Const(_SC("MAX_INT32"),    std::numeric_limits<SQInt32>::max())
        .Const(_SC("MIN_FLOAT"),    std::numeric_limits<SQFloat>::min())
        .Const(_SC("MAX_FLOAT"),    std::numeric_limits<SQFloat>::max())
    );

    Sqrat::ConstTable().Enum(_SC("EARCHITECTURE"), Sqrat::Enumeration()
        .Const(_SC("UNKNOWN"),      SQMOD_ARCH_ID_UNKNOWN)
        .Const(_SC("X32_BIT"),      SQMOD_ARCH_ID_32_BIT)
        .Const(_SC("X64_BIT"),      SQMOD_ARCH_ID_64_BIT)
    );

    Sqrat::ConstTable().Enum(_SC("EPLATFORM"), Sqrat::Enumeration()
        .Const(_SC("UNKNOWN"),      SQMOD_PLAT_ID_UNKNOWN)
        .Const(_SC("WINDOWS"),      SQMOD_PLAT_ID_WINDOWS)
        .Const(_SC("LINUX"),        SQMOD_PLAT_ID_LINUX)
        .Const(_SC("MACOS"),        SQMOD_PLAT_ID_MACOS)
        .Const(_SC("UNIX"),         SQMOD_PLAT_ID_UNIX)
    );

    Sqrat::ConstTable().Enum(_SC("EVEHICLEUPD"), Sqrat::Enumeration()
        .Const(_SC("DRIVER"),       SQMOD_VEHICLEUPD_DRIVER)
        .Const(_SC("OTHER"),        SQMOD_VEHICLEUPD_OTHER)
    );

    Sqrat::ConstTable().Enum(_SC("EPLAYERUPD"), Sqrat::Enumeration()
        .Const(_SC("ONFOOT"),       SQMOD_PLAYERUPD_ONFOOT)
        .Const(_SC("AIM"),          SQMOD_PLAYERUPD_AIM)
        .Const(_SC("DRIVER"),       SQMOD_PLAYERUPD_DRIVER)
        .Const(_SC("PASSENGER"),    SQMOD_PLAYERUPD_PASSENGER)
    );

    Sqrat::ConstTable().Enum(_SC("EPARTREASON"), Sqrat::Enumeration()
        .Const(_SC("TIMEOUT"),      SQMOD_PARTREASON_TIMEOUT)
        .Const(_SC("DISCONNECTED"), SQMOD_PARTREASON_DISCONNECTED)
        .Const(_SC("KICKEDBANNED"), SQMOD_PARTREASON_KICKEDBANNED)
        .Const(_SC("CRASHED"),      SQMOD_PARTREASON_CRASHED)
    );

    Sqrat::ConstTable().Enum(_SC("EBODYPART"), Sqrat::Enumeration()
        .Const(_SC("BODY"),         SQMOD_BODYPART_BODY)
        .Const(_SC("TORSO"),        SQMOD_BODYPART_TORSO)
        .Const(_SC("LEFTARM"),      SQMOD_BODYPART_LEFTARM)
        .Const(_SC("LARM"),         SQMOD_BODYPART_LEFTARM)
        .Const(_SC("RIGHTARM"),     SQMOD_BODYPART_RIGHTARM)
        .Const(_SC("RARM"),         SQMOD_BODYPART_RIGHTARM)
        .Const(_SC("LEFTLEG"),      SQMOD_BODYPART_LEFTLEG)
        .Const(_SC("LLEG"),         SQMOD_BODYPART_LEFTLEG)
        .Const(_SC("RIGHTLEG"),     SQMOD_BODYPART_RIGHTLEG)
        .Const(_SC("RLEG"),         SQMOD_BODYPART_RIGHTLEG)
        .Const(_SC("HEAD"),         SQMOD_BODYPART_HEAD)
    );

    Sqrat::ConstTable().Enum(_SC("EPLAYERSTATE"), Sqrat::Enumeration()
        .Const(_SC("NONE"),                     SQMOD_PLAYER_STATE_NONE)
        .Const(_SC("NORMAL"),                   SQMOD_PLAYER_STATE_NORMAL)
        .Const(_SC("SHOOTING"),                 SQMOD_PLAYER_STATE_SHOOTING)
        .Const(_SC("DRIVER"),                   SQMOD_PLAYER_STATE_DRIVER)
        .Const(_SC("PASSENGER"),                SQMOD_PLAYER_STATE_PASSENGER)
        .Const(_SC("ENTERING_AS_DRIVER"),       SQMOD_PLAYER_STATE_ENTERING_AS_DRIVER)
        .Const(_SC("ENTERING_AS_PASSENGER"),    SQMOD_PLAYER_STATE_ENTERING_AS_PASSENGER)
        .Const(_SC("EXITING_VEHICLE"),          SQMOD_PLAYER_STATE_EXITING_VEHICLE)
        .Const(_SC("UNSPAWNED"),                SQMOD_PLAYER_STATE_UNSPAWNED)
    );

    Sqrat::ConstTable().Enum(_SC("EPLAYERACTION"), Sqrat::Enumeration()
        .Const(_SC("NONE"),                     SQMOD_PLAYER_ACTION_NONE)
        .Const(_SC("NORMAL"),                   SQMOD_PLAYER_ACTION_NORMAL)
        .Const(_SC("AIMING"),                   SQMOD_PLAYER_ACTION_AIMING)
        .Const(_SC("SHOOTING"),                 SQMOD_PLAYER_ACTION_SHOOTING)
        .Const(_SC("JUMPING"),                  SQMOD_PLAYER_ACTION_JUMPING)
        .Const(_SC("LYING_ON_GROUND"),          SQMOD_PLAYER_ACTION_LYING_ON_GROUND)
        .Const(_SC("GETTING_UP"),               SQMOD_PLAYER_ACTION_GETTING_UP)
        .Const(_SC("JUMPING_FROM_VEHICLE"),     SQMOD_PLAYER_ACTION_JUMPING_FROM_VEHICLE)
        .Const(_SC("DRIVING"),                  SQMOD_PLAYER_ACTION_DRIVING)
        .Const(_SC("DYING"),                    SQMOD_PLAYER_ACTION_DYING)
        .Const(_SC("WASTED"),                   SQMOD_PLAYER_ACTION_WASTED)
        .Const(_SC("ENTERING_VEHICLE"),         SQMOD_PLAYER_ACTION_ENTERING_VEHICLE)
        .Const(_SC("EXITING_VEHICLE"),          SQMOD_PLAYER_ACTION_EXITING_VEHICLE)
    );

    Sqrat::ConstTable().Enum(_SC("EWEATHER"), Sqrat::Enumeration()
        .Const(_SC("MOSTLYCLEAR"),      SQMOD_WEATHER_MOSTLYCLEAR)
        .Const(_SC("OVERCAST"),         SQMOD_WEATHER_OVERCAST)
        .Const(_SC("THUNDERSTORM"),     SQMOD_WEATHER_THUNDERSTORM)
        .Const(_SC("STORM"),            SQMOD_WEATHER_STORM)
        .Const(_SC("STORMY"),           SQMOD_WEATHER_STORMY)
        .Const(_SC("FOGGY"),            SQMOD_WEATHER_FOGGY)
        .Const(_SC("FOG"),              SQMOD_WEATHER_FOG)
        .Const(_SC("CLEAR"),            SQMOD_WEATHER_CLEAR)
        .Const(_SC("SUNNY"),            SQMOD_WEATHER_SUNNY)
        .Const(_SC("RAIN"),             SQMOD_WEATHER_RAIN)
        .Const(_SC("RAINY"),            SQMOD_WEATHER_RAINY)
        .Const(_SC("DARKCLOUDY"),       SQMOD_WEATHER_DARKCLOUDY)
        .Const(_SC("LIGHTCLOUDY"),      SQMOD_WEATHER_LIGHTCLOUDY)
        .Const(_SC("OVERCASTCLOUDY"),   SQMOD_WEATHER_OVERCASTCLOUDY)
        .Const(_SC("BLACKCLOUDS"),      SQMOD_WEATHER_BLACKCLOUDS)
    );

    Sqrat::ConstTable().Enum(_SC("EWEAPON"), Sqrat::Enumeration()
        .Const(_SC("UNKNWON"),          SQMOD_UNKNOWN)
        .Const(_SC("UNARMED"),          SQMOD_WEAPON_UNARMED)
        .Const(_SC("BRASSKNUCKLES"),    SQMOD_WEAPON_BRASSKNUCKLES)
        .Const(_SC("SCREWDRIVER"),      SQMOD_WEAPON_SCREWDRIVER)
        .Const(_SC("GOLFCLUB"),         SQMOD_WEAPON_GOLFCLUB)
        .Const(_SC("NIGHTSTICK"),       SQMOD_WEAPON_NIGHTSTICK)
        .Const(_SC("KNIFE"),            SQMOD_WEAPON_KNIFE)
        .Const(_SC("BASEBALLBAT"),      SQMOD_WEAPON_BASEBALLBAT)
        .Const(_SC("HAMMER"),           SQMOD_WEAPON_HAMMER)
        .Const(_SC("MEATCLEAVER"),      SQMOD_WEAPON_MEATCLEAVER)
        .Const(_SC("MACHETE"),          SQMOD_WEAPON_MACHETE)
        .Const(_SC("KATANA"),           SQMOD_WEAPON_KATANA)
        .Const(_SC("CHAINSAW"),         SQMOD_WEAPON_CHAINSAW)
        .Const(_SC("GRENADE"),          SQMOD_WEAPON_GRENADE)
        .Const(_SC("REMOTE"),           SQMOD_WEAPON_REMOTE)
        .Const(_SC("TEARGAS"),          SQMOD_WEAPON_TEARGAS)
        .Const(_SC("MOLOTOV"),          SQMOD_WEAPON_MOLOTOV)
        .Const(_SC("ROCKET"),           SQMOD_WEAPON_ROCKET)
        .Const(_SC("COLT45"),           SQMOD_WEAPON_COLT45)
        .Const(_SC("PYTHON"),           SQMOD_WEAPON_PYTHON)
        .Const(_SC("SHOTGUN"),          SQMOD_WEAPON_SHOTGUN)
        .Const(_SC("SPAS12"),           SQMOD_WEAPON_SPAS12)
        .Const(_SC("STUBBY"),           SQMOD_WEAPON_STUBBY)
        .Const(_SC("TEC9"),             SQMOD_WEAPON_TEC9)
        .Const(_SC("UZI"),              SQMOD_WEAPON_UZI)
        .Const(_SC("INGRAM"),           SQMOD_WEAPON_INGRAM)
        .Const(_SC("MP5"),              SQMOD_WEAPON_MP5)
        .Const(_SC("M4"),               SQMOD_WEAPON_M4)
        .Const(_SC("RUGER"),            SQMOD_WEAPON_RUGER)
        .Const(_SC("SNIPER"),           SQMOD_WEAPON_SNIPER)
        .Const(_SC("LASERSCOPE"),       SQMOD_WEAPON_LASERSCOPE)
        .Const(_SC("ROCKETLAUNCHER"),   SQMOD_WEAPON_ROCKETLAUNCHER)
        .Const(_SC("FLAMETHROWER"),     SQMOD_WEAPON_FLAMETHROWER)
        .Const(_SC("M60"),              SQMOD_WEAPON_M60)
        .Const(_SC("MINIGUN"),          SQMOD_WEAPON_MINIGUN)
        .Const(_SC("BOMB"),             SQMOD_WEAPON_BOMB)
        .Const(_SC("HELICANNON"),       SQMOD_WEAPON_HELICANNON)
        .Const(_SC("CAMERA"),           SQMOD_WEAPON_CAMERA)
        .Const(_SC("VEHICLE"),          SQMOD_WEAPON_VEHICLE)
        .Const(_SC("EXPLOSION1"),       SQMOD_WEAPON_EXPLOSION1)
        .Const(_SC("DRIVEBY"),          SQMOD_WEAPON_DRIVEBY)
        .Const(_SC("DROWNED"),          SQMOD_WEAPON_DROWNED)
        .Const(_SC("FALL"),             SQMOD_WEAPON_FALL)
        .Const(_SC("EXPLOSION2"),       SQMOD_WEAPON_EXPLOSION2)
        .Const(_SC("SUICIDE"),          SQMOD_WEAPON_SUICIDE)
    );

    Sqrat::ConstTable().Enum(_SC("EVEHICLE"), Sqrat::Enumeration()
        .Const(_SC("UNKNOWN"),          SQMOD_UNKNOWN)
        .Const(_SC("LANDSTALKER"),      SQMOD_VEHICLE_LANDSTALKER)
        .Const(_SC("IDAHO"),            SQMOD_VEHICLE_IDAHO)
        .Const(_SC("STINGER"),          SQMOD_VEHICLE_STINGER)
        .Const(_SC("LINERUNNER"),       SQMOD_VEHICLE_LINERUNNER)
        .Const(_SC("PERENNIAL"),        SQMOD_VEHICLE_PERENNIAL)
        .Const(_SC("SENTINEL"),         SQMOD_VEHICLE_SENTINEL)
        .Const(_SC("RIO"),              SQMOD_VEHICLE_RIO)
        .Const(_SC("FIRETRUCK"),        SQMOD_VEHICLE_FIRETRUCK)
        .Const(_SC("TRASHMASTER"),      SQMOD_VEHICLE_TRASHMASTER)
        .Const(_SC("STRETCH"),          SQMOD_VEHICLE_STRETCH)
        .Const(_SC("MANANA"),           SQMOD_VEHICLE_MANANA)
        .Const(_SC("INFERNUS"),         SQMOD_VEHICLE_INFERNUS)
        .Const(_SC("VOODOO"),           SQMOD_VEHICLE_VOODOO)
        .Const(_SC("PONY"),             SQMOD_VEHICLE_PONY)
        .Const(_SC("MULE"),             SQMOD_VEHICLE_MULE)
        .Const(_SC("CHEETAH"),          SQMOD_VEHICLE_CHEETAH)
        .Const(_SC("AMBULANCE"),        SQMOD_VEHICLE_AMBULANCE)
        .Const(_SC("FBIWASHINGTON"),    SQMOD_VEHICLE_FBIWASHINGTON)
        .Const(_SC("MOONBEAM"),         SQMOD_VEHICLE_MOONBEAM)
        .Const(_SC("ESPERANTO"),        SQMOD_VEHICLE_ESPERANTO)
        .Const(_SC("TAXI"),             SQMOD_VEHICLE_TAXI)
        .Const(_SC("WASHINGTON"),       SQMOD_VEHICLE_WASHINGTON)
        .Const(_SC("BOBCAT"),           SQMOD_VEHICLE_BOBCAT)
        .Const(_SC("MRWHOOPEE"),        SQMOD_VEHICLE_MRWHOOPEE)
        .Const(_SC("BFINJECTION"),      SQMOD_VEHICLE_BFINJECTION)
        .Const(_SC("HUNTER"),           SQMOD_VEHICLE_HUNTER)
        .Const(_SC("POLICE"),           SQMOD_VEHICLE_POLICE)
        .Const(_SC("ENFORCER"),         SQMOD_VEHICLE_ENFORCER)
        .Const(_SC("SECURICAR"),        SQMOD_VEHICLE_SECURICAR)
        .Const(_SC("BANSHEE"),          SQMOD_VEHICLE_BANSHEE)
        .Const(_SC("PREDATOR"),         SQMOD_VEHICLE_PREDATOR)
        .Const(_SC("BUS"),              SQMOD_VEHICLE_BUS)
        .Const(_SC("RHINO"),            SQMOD_VEHICLE_RHINO)
        .Const(_SC("BARRACKSOL"),       SQMOD_VEHICLE_BARRACKSOL)
        .Const(_SC("BARRACKS"),         SQMOD_VEHICLE_BARRACKS)
        .Const(_SC("CUBANHERMES"),      SQMOD_VEHICLE_CUBANHERMES)
        .Const(_SC("HELICOPTER"),       SQMOD_VEHICLE_HELICOPTER)
        .Const(_SC("ANGEL"),            SQMOD_VEHICLE_ANGEL)
        .Const(_SC("COACH"),            SQMOD_VEHICLE_COACH)
        .Const(_SC("CABBIE"),           SQMOD_VEHICLE_CABBIE)
        .Const(_SC("STALLION"),         SQMOD_VEHICLE_STALLION)
        .Const(_SC("RUMPO"),            SQMOD_VEHICLE_RUMPO)
        .Const(_SC("RCBANDIT"),         SQMOD_VEHICLE_RCBANDIT)
        .Const(_SC("HEARSE"),           SQMOD_VEHICLE_HEARSE)
        .Const(_SC("PACKER"),           SQMOD_VEHICLE_PACKER)
        .Const(_SC("SENTINELXS"),       SQMOD_VEHICLE_SENTINELXS)
        .Const(_SC("ADMIRAL"),          SQMOD_VEHICLE_ADMIRAL)
        .Const(_SC("SQUALO"),           SQMOD_VEHICLE_SQUALO)
        .Const(_SC("SEASPARROW"),       SQMOD_VEHICLE_SEASPARROW)
        .Const(_SC("PIZZABOY"),         SQMOD_VEHICLE_PIZZABOY)
        .Const(_SC("GANGBURRITO"),      SQMOD_VEHICLE_GANGBURRITO)
        .Const(_SC("AIRTRAIN"),         SQMOD_VEHICLE_AIRTRAIN)
        .Const(_SC("DEADDODO"),         SQMOD_VEHICLE_DEADDODO)
        .Const(_SC("SPEEDER"),          SQMOD_VEHICLE_SPEEDER)
        .Const(_SC("REEFER"),           SQMOD_VEHICLE_REEFER)
        .Const(_SC("TROPIC"),           SQMOD_VEHICLE_TROPIC)
        .Const(_SC("FLATBED"),          SQMOD_VEHICLE_FLATBED)
        .Const(_SC("YANKEE"),           SQMOD_VEHICLE_YANKEE)
        .Const(_SC("CADDY"),            SQMOD_VEHICLE_CADDY)
        .Const(_SC("ZEBRA"),            SQMOD_VEHICLE_ZEBRA)
        .Const(_SC("ZEBRACAB"),         SQMOD_VEHICLE_ZEBRACAB)
        .Const(_SC("TOPFUN"),           SQMOD_VEHICLE_TOPFUN)
        .Const(_SC("SKIMMER"),          SQMOD_VEHICLE_SKIMMER)
        .Const(_SC("PCJ600"),           SQMOD_VEHICLE_PCJ600)
        .Const(_SC("PCJ"),              SQMOD_VEHICLE_PCJ)
        .Const(_SC("FAGGIO"),           SQMOD_VEHICLE_FAGGIO)
        .Const(_SC("FREEWAY"),          SQMOD_VEHICLE_FREEWAY)
        .Const(_SC("RCBARON"),          SQMOD_VEHICLE_RCBARON)
        .Const(_SC("RCRAIDER"),         SQMOD_VEHICLE_RCRAIDER)
        .Const(_SC("GLENDALE"),         SQMOD_VEHICLE_GLENDALE)
        .Const(_SC("OCEANIC"),          SQMOD_VEHICLE_OCEANIC)
        .Const(_SC("SANCHEZ"),          SQMOD_VEHICLE_SANCHEZ)
        .Const(_SC("SPARROW"),          SQMOD_VEHICLE_SPARROW)
        .Const(_SC("PATRIOT"),          SQMOD_VEHICLE_PATRIOT)
        .Const(_SC("LOVEFIST"),         SQMOD_VEHICLE_LOVEFIST)
        .Const(_SC("COASTGUARD"),       SQMOD_VEHICLE_COASTGUARD)
        .Const(_SC("DINGHY"),           SQMOD_VEHICLE_DINGHY)
        .Const(_SC("HERMES"),           SQMOD_VEHICLE_HERMES)
        .Const(_SC("SABRE"),            SQMOD_VEHICLE_SABRE)
        .Const(_SC("SABRETURBO"),       SQMOD_VEHICLE_SABRETURBO)
        .Const(_SC("PHOENIX"),          SQMOD_VEHICLE_PHOENIX)
        .Const(_SC("WALTON"),           SQMOD_VEHICLE_WALTON)
        .Const(_SC("REGINA"),           SQMOD_VEHICLE_REGINA)
        .Const(_SC("COMET"),            SQMOD_VEHICLE_COMET)
        .Const(_SC("DELUXO"),           SQMOD_VEHICLE_DELUXO)
        .Const(_SC("BURRITO"),          SQMOD_VEHICLE_BURRITO)
        .Const(_SC("SPANDEX"),          SQMOD_VEHICLE_SPANDEX)
        .Const(_SC("SPANDEXPRESS"),     SQMOD_VEHICLE_SPANDEXPRESS)
        .Const(_SC("MARQUIS"),          SQMOD_VEHICLE_MARQUIS)
        .Const(_SC("BAGGAGE"),          SQMOD_VEHICLE_BAGGAGE)
        .Const(_SC("BAGGAGEHANDLER"),   SQMOD_VEHICLE_BAGGAGEHANDLER)
        .Const(_SC("KAUFMAN"),          SQMOD_VEHICLE_KAUFMAN)
        .Const(_SC("KAUFMANCAB"),       SQMOD_VEHICLE_KAUFMANCAB)
        .Const(_SC("MAVERICK"),         SQMOD_VEHICLE_MAVERICK)
        .Const(_SC("VCNMAVERICK"),      SQMOD_VEHICLE_VCNMAVERICK)
        .Const(_SC("RANCHER"),          SQMOD_VEHICLE_RANCHER)
        .Const(_SC("FBIRANCHER"),       SQMOD_VEHICLE_FBIRANCHER)
        .Const(_SC("VIRGO"),            SQMOD_VEHICLE_VIRGO)
        .Const(_SC("GREENWOOD"),        SQMOD_VEHICLE_GREENWOOD)
        .Const(_SC("CUBANJETMAX"),      SQMOD_VEHICLE_CUBANJETMAX)
        .Const(_SC("HOTRING1"),         SQMOD_VEHICLE_HOTRING1)
        .Const(_SC("HOTRINGRACER1"),    SQMOD_VEHICLE_HOTRINGRACER1)
        .Const(_SC("SANDKING"),         SQMOD_VEHICLE_SANDKING)
        .Const(_SC("BLISTA"),           SQMOD_VEHICLE_BLISTA)
        .Const(_SC("BLISTAC"),          SQMOD_VEHICLE_BLISTAC)
        .Const(_SC("BLISTACOMPACT"),    SQMOD_VEHICLE_BLISTACOMPACT)
        .Const(_SC("COMPACT"),          SQMOD_VEHICLE_COMPACT)
        .Const(_SC("POLICEMAV"),        SQMOD_VEHICLE_POLICEMAV)
        .Const(_SC("POLICEMAVERICK"),   SQMOD_VEHICLE_POLICEMAVERICK)
        .Const(_SC("BOXVILLE"),         SQMOD_VEHICLE_BOXVILLE)
        .Const(_SC("BENSON"),           SQMOD_VEHICLE_BENSON)
        .Const(_SC("MESA"),             SQMOD_VEHICLE_MESA)
        .Const(_SC("MESAGRANDE"),       SQMOD_VEHICLE_MESAGRANDE)
        .Const(_SC("RCGOBLIN"),         SQMOD_VEHICLE_RCGOBLIN)
        .Const(_SC("HOTRING2"),         SQMOD_VEHICLE_HOTRING2)
        .Const(_SC("HOTRINGRACER2"),    SQMOD_VEHICLE_HOTRINGRACER2)
        .Const(_SC("HOTRING3"),         SQMOD_VEHICLE_HOTRING3)
        .Const(_SC("HOTRINGRACER3"),    SQMOD_VEHICLE_HOTRINGRACER3)
        .Const(_SC("BLOODRING1"),       SQMOD_VEHICLE_BLOODRING1)
        .Const(_SC("BLOODRINGBANGER1"), SQMOD_VEHICLE_BLOODRINGBANGER1)
        .Const(_SC("BLOODRING2"),       SQMOD_VEHICLE_BLOODRING2)
        .Const(_SC("BLOODRINGBANGER2"), SQMOD_VEHICLE_BLOODRINGBANGER2)
        .Const(_SC("VICECHEE"),         SQMOD_VEHICLE_VICECHEE)
        .Const(_SC("POLICECHEETAH"),    SQMOD_VEHICLE_POLICECHEETAH)
        .Const(_SC("FBICHEETAH"),       SQMOD_VEHICLE_FBICHEETAH)
        .Const(_SC("CHEETAH2"),         SQMOD_VEHICLE_CHEETAH2)
    );

    Sqrat::ConstTable().Enum(_SC("ESKIN"), Sqrat::Enumeration()
        .Const(_SC("UNKNOWN"),                  SQMOD_UNKNOWN)
        .Const(_SC("TOMMY_VERCETTI"),           SQMOD_SKIN_TOMMY_VERCETTI)
        .Const(_SC("COP"),                      SQMOD_SKIN_COP)
        .Const(_SC("SWAT"),                     SQMOD_SKIN_SWAT)
        .Const(_SC("FBI"),                      SQMOD_SKIN_FBI)
        .Const(_SC("ARMY"),                     SQMOD_SKIN_ARMY)
        .Const(_SC("PARAMEDIC"),                SQMOD_SKIN_PARAMEDIC)
        .Const(_SC("FIREMAN"),                  SQMOD_SKIN_FIREMAN)
        .Const(_SC("GOLF_GUY_A"),               SQMOD_SKIN_GOLF_GUY_A)
        .Const(_SC("BUM_LADY_A"),               SQMOD_SKIN_BUM_LADY_A)
        .Const(_SC("BUM_LADY_B"),               SQMOD_SKIN_BUM_LADY_B)
        .Const(_SC("PUNK_A"),                   SQMOD_SKIN_PUNK_A)
        .Const(_SC("LAWYER"),                   SQMOD_SKIN_LAWYER)
        .Const(_SC("SPANISH_LADY_A"),           SQMOD_SKIN_SPANISH_LADY_A)
        .Const(_SC("SPANISH_LADY_B"),           SQMOD_SKIN_SPANISH_LADY_B)
        .Const(_SC("COOL_GUY_A"),               SQMOD_SKIN_COOL_GUY_A)
        .Const(_SC("ARABIC_GUY"),               SQMOD_SKIN_ARABIC_GUY)
        .Const(_SC("BEACH_LADY_A"),             SQMOD_SKIN_BEACH_LADY_A)
        .Const(_SC("BEACH_LADY_B"),             SQMOD_SKIN_BEACH_LADY_B)
        .Const(_SC("BEACH_GUY_A"),              SQMOD_SKIN_BEACH_GUY_A)
        .Const(_SC("BEACH_GUY_B"),              SQMOD_SKIN_BEACH_GUY_B)
        .Const(_SC("OFFICE_LADY_A"),            SQMOD_SKIN_OFFICE_LADY_A)
        .Const(_SC("WAITRESS_A"),               SQMOD_SKIN_WAITRESS_A)
        .Const(_SC("FOOD_LADY"),                SQMOD_SKIN_FOOD_LADY)
        .Const(_SC("PROSTITUTE_A"),             SQMOD_SKIN_PROSTITUTE_A)
        .Const(_SC("BUM_LADY_C"),               SQMOD_SKIN_BUM_LADY_C)
        .Const(_SC("BUM_GUY_A"),                SQMOD_SKIN_BUM_GUY_A)
        .Const(_SC("GARBAGEMAN_A"),             SQMOD_SKIN_GARBAGEMAN_A)
        .Const(_SC("TAXI_DRIVER_A"),            SQMOD_SKIN_TAXI_DRIVER_A)
        .Const(_SC("HATIAN_A"),                 SQMOD_SKIN_HATIAN_A)
        .Const(_SC("CRIMINAL_A"),               SQMOD_SKIN_CRIMINAL_A)
        .Const(_SC("HOOD_LADY"),                SQMOD_SKIN_HOOD_LADY)
        .Const(_SC("GRANNY_A"),                 SQMOD_SKIN_GRANNY_A)
        .Const(_SC("BUSINESS_MAN_A"),           SQMOD_SKIN_BUSINESS_MAN_A)
        .Const(_SC("CHURCH_GUY"),               SQMOD_SKIN_CHURCH_GUY)
        .Const(_SC("CLUB_LADY"),                SQMOD_SKIN_CLUB_LADY)
        .Const(_SC("CHURCH_LADY"),              SQMOD_SKIN_CHURCH_LADY)
        .Const(_SC("PIMP"),                     SQMOD_SKIN_PIMP)
        .Const(_SC("BEACH_LADY_C"),             SQMOD_SKIN_BEACH_LADY_C)
        .Const(_SC("BEACH_GUY_C"),              SQMOD_SKIN_BEACH_GUY_C)
        .Const(_SC("BEACH_LADY_D"),             SQMOD_SKIN_BEACH_LADY_D)
        .Const(_SC("BEACH_GUY_D"),              SQMOD_SKIN_BEACH_GUY_D)
        .Const(_SC("BUSINESS_MAN_B"),           SQMOD_SKIN_BUSINESS_MAN_B)
        .Const(_SC("PROSTITUTE_B"),             SQMOD_SKIN_PROSTITUTE_B)
        .Const(_SC("BUM_LADY_D"),               SQMOD_SKIN_BUM_LADY_D)
        .Const(_SC("BUM_GUY_B"),                SQMOD_SKIN_BUM_GUY_B)
        .Const(_SC("HATIAN_B"),                 SQMOD_SKIN_HATIAN_B)
        .Const(_SC("CONSTRUCTION_WORKER_A"),    SQMOD_SKIN_CONSTRUCTION_WORKER_A)
        .Const(_SC("PUNK_B"),                   SQMOD_SKIN_PUNK_B)
        .Const(_SC("PROSTITUTE_C"),             SQMOD_SKIN_PROSTITUTE_C)
        .Const(_SC("GRANNY_B"),                 SQMOD_SKIN_GRANNY_B)
        .Const(_SC("PUNK_C"),                   SQMOD_SKIN_PUNK_C)
        .Const(_SC("BUSINESS_MAN_C"),           SQMOD_SKIN_BUSINESS_MAN_C)
        .Const(_SC("SPANISH_LADY_C"),           SQMOD_SKIN_SPANISH_LADY_C)
        .Const(_SC("SPANISH_LADY_D"),           SQMOD_SKIN_SPANISH_LADY_D)
        .Const(_SC("COOL_GUY_B"),               SQMOD_SKIN_COOL_GUY_B)
        .Const(_SC("BUSINESS_MAN_D"),           SQMOD_SKIN_BUSINESS_MAN_D)
        .Const(_SC("BEACH_LADY_E"),             SQMOD_SKIN_BEACH_LADY_E)
        .Const(_SC("BEACH_GUY_E"),              SQMOD_SKIN_BEACH_GUY_E)
        .Const(_SC("BEACH_LADY_F"),             SQMOD_SKIN_BEACH_LADY_F)
        .Const(_SC("BEACH_GUY_F"),              SQMOD_SKIN_BEACH_GUY_F)
        .Const(_SC("CONSTRUCTION_WORKER_B"),    SQMOD_SKIN_CONSTRUCTION_WORKER_B)
        .Const(_SC("GOLF_GUY_B"),               SQMOD_SKIN_GOLF_GUY_B)
        .Const(_SC("GOLF_LADY"),                SQMOD_SKIN_GOLF_LADY)
        .Const(_SC("GOLF_GUY_C"),               SQMOD_SKIN_GOLF_GUY_C)
        .Const(_SC("BEACH_LADY_G"),             SQMOD_SKIN_BEACH_LADY_G)
        .Const(_SC("BEACH_GUY_G"),              SQMOD_SKIN_BEACH_GUY_G)
        .Const(_SC("OFFICE_LADY_B"),            SQMOD_SKIN_OFFICE_LADY_B)
        .Const(_SC("BUSINESS_MAN_E"),           SQMOD_SKIN_BUSINESS_MAN_E)
        .Const(_SC("BUSINESS_MAN_F"),           SQMOD_SKIN_BUSINESS_MAN_F)
        .Const(_SC("PROSTITUTE_D"),             SQMOD_SKIN_PROSTITUTE_D)
        .Const(_SC("BUM_LADY_E"),               SQMOD_SKIN_BUM_LADY_E)
        .Const(_SC("BUM_GUY_C"),                SQMOD_SKIN_BUM_GUY_C)
        .Const(_SC("SPANISH_GUY"),              SQMOD_SKIN_SPANISH_GUY)
        .Const(_SC("TAXI_DRIVER_B"),            SQMOD_SKIN_TAXI_DRIVER_B)
        .Const(_SC("GYM_LADY"),                 SQMOD_SKIN_GYM_LADY)
        .Const(_SC("GYM_GUY"),                  SQMOD_SKIN_GYM_GUY)
        .Const(_SC("SKATE_LADY"),               SQMOD_SKIN_SKATE_LADY)
        .Const(_SC("SKATE_GUY"),                SQMOD_SKIN_SKATE_GUY)
        .Const(_SC("SHOPPER_A"),                SQMOD_SKIN_SHOPPER_A)
        .Const(_SC("SHOPPER_B"),                SQMOD_SKIN_SHOPPER_B)
        .Const(_SC("TOURIST_A"),                SQMOD_SKIN_TOURIST_A)
        .Const(_SC("TOURIST_B"),                SQMOD_SKIN_TOURIST_B)
        .Const(_SC("CUBAN_A"),                  SQMOD_SKIN_CUBAN_A)
        .Const(_SC("CUBAN_B"),                  SQMOD_SKIN_CUBAN_B)
        .Const(_SC("HATIAN_C"),                 SQMOD_SKIN_HATIAN_C)
        .Const(_SC("HATIAN_D"),                 SQMOD_SKIN_HATIAN_D)
        .Const(_SC("SHARK_A"),                  SQMOD_SKIN_SHARK_A)
        .Const(_SC("SHARK_B"),                  SQMOD_SKIN_SHARK_B)
        .Const(_SC("DIAZ_GUY_A"),               SQMOD_SKIN_DIAZ_GUY_A)
        .Const(_SC("DIAZ_GUY_B"),               SQMOD_SKIN_DIAZ_GUY_B)
        .Const(_SC("DBP_SECURITY_A"),           SQMOD_SKIN_DBP_SECURITY_A)
        .Const(_SC("DBP_SECURITY_B"),           SQMOD_SKIN_DBP_SECURITY_B)
        .Const(_SC("BIKER_A"),                  SQMOD_SKIN_BIKER_A)
        .Const(_SC("BIKER_B"),                  SQMOD_SKIN_BIKER_B)
        .Const(_SC("VERCETTI_GUY_A"),           SQMOD_SKIN_VERCETTI_GUY_A)
        .Const(_SC("VERCETTI_GUY_B"),           SQMOD_SKIN_VERCETTI_GUY_B)
        .Const(_SC("UNDERCOVER_COP_A"),         SQMOD_SKIN_UNDERCOVER_COP_A)
        .Const(_SC("UNDERCOVER_COP_B"),         SQMOD_SKIN_UNDERCOVER_COP_B)
        .Const(_SC("UNDERCOVER_COP_C"),         SQMOD_SKIN_UNDERCOVER_COP_C)
        .Const(_SC("UNDERCOVER_COP_D"),         SQMOD_SKIN_UNDERCOVER_COP_D)
        .Const(_SC("UNDERCOVER_COP_E"),         SQMOD_SKIN_UNDERCOVER_COP_E)
        .Const(_SC("UNDERCOVER_COP_F"),         SQMOD_SKIN_UNDERCOVER_COP_F)
        .Const(_SC("RICH_GUY"),                 SQMOD_SKIN_RICH_GUY)
        .Const(_SC("COOL_GUY_C"),               SQMOD_SKIN_COOL_GUY_C)
        .Const(_SC("PROSTITUTE_E"),             SQMOD_SKIN_PROSTITUTE_E)
        .Const(_SC("PROSTITUTE_F"),             SQMOD_SKIN_PROSTITUTE_F)
        .Const(_SC("LOVE_FIST_A"),              SQMOD_SKIN_LOVE_FIST_A)
        .Const(_SC("KEN_ROSENBURG"),            SQMOD_SKIN_KEN_ROSENBURG)
        .Const(_SC("CANDY_SUXX"),               SQMOD_SKIN_CANDY_SUXX)
        .Const(_SC("HILARY"),                   SQMOD_SKIN_HILARY)
        .Const(_SC("LOVE_FIST_B"),              SQMOD_SKIN_LOVE_FIST_B)
        .Const(_SC("PHIL"),                     SQMOD_SKIN_PHIL)
        .Const(_SC("ROCKSTAR_GUY"),             SQMOD_SKIN_ROCKSTAR_GUY)
        .Const(_SC("SONNY"),                    SQMOD_SKIN_SONNY)
        .Const(_SC("LANCE_A"),                  SQMOD_SKIN_LANCE_A)
        .Const(_SC("MERCADES_A"),               SQMOD_SKIN_MERCADES_A)
        .Const(_SC("LOVE_FIST_C"),              SQMOD_SKIN_LOVE_FIST_C)
        .Const(_SC("ALEX_SRUB"),                SQMOD_SKIN_ALEX_SRUB)
        .Const(_SC("LANCE_COP"),                SQMOD_SKIN_LANCE_COP)
        .Const(_SC("LANCE_B"),                  SQMOD_SKIN_LANCE_B)
        .Const(_SC("CORTEZ"),                   SQMOD_SKIN_CORTEZ)
        .Const(_SC("LOVE_FIST_D"),              SQMOD_SKIN_LOVE_FIST_D)
        .Const(_SC("COLUMBIAN_GUY_A"),          SQMOD_SKIN_COLUMBIAN_GUY_A)
        .Const(_SC("HILARY_ROBBER"),            SQMOD_SKIN_HILARY_ROBBER)
        .Const(_SC("MERCADES_B"),               SQMOD_SKIN_MERCADES_B)
        .Const(_SC("CAM"),                      SQMOD_SKIN_CAM)
        .Const(_SC("CAM_ROBBER"),               SQMOD_SKIN_CAM_ROBBER)
        .Const(_SC("PHIL_ONE_ARM"),             SQMOD_SKIN_PHIL_ONE_ARM)
        .Const(_SC("PHIL_ROBBER"),              SQMOD_SKIN_PHIL_ROBBER)
        .Const(_SC("COOL_GUY_D"),               SQMOD_SKIN_COOL_GUY_D)
        .Const(_SC("PIZZAMAN"),                 SQMOD_SKIN_PIZZAMAN)
        .Const(_SC("TAXI_DRIVER_C"),            SQMOD_SKIN_TAXI_DRIVER_C)
        .Const(_SC("TAXI_DRIVER_D"),            SQMOD_SKIN_TAXI_DRIVER_D)
        .Const(_SC("SAILOR_A"),                 SQMOD_SKIN_SAILOR_A)
        .Const(_SC("SAILOR_B"),                 SQMOD_SKIN_SAILOR_B)
        .Const(_SC("SAILOR_C"),                 SQMOD_SKIN_SAILOR_C)
        .Const(_SC("CHEF"),                     SQMOD_SKIN_CHEF)
        .Const(_SC("CRIMINAL_B"),               SQMOD_SKIN_CRIMINAL_B)
        .Const(_SC("FRENCH_GUY"),               SQMOD_SKIN_FRENCH_GUY)
        .Const(_SC("GARBAGEMAN_B"),             SQMOD_SKIN_GARBAGEMAN_B)
        .Const(_SC("HATIAN_E"),                 SQMOD_SKIN_HATIAN_E)
        .Const(_SC("WAITRESS_B"),               SQMOD_SKIN_WAITRESS_B)
        .Const(_SC("SONNY_GUY_A"),              SQMOD_SKIN_SONNY_GUY_A)
        .Const(_SC("SONNY_GUY_B"),              SQMOD_SKIN_SONNY_GUY_B)
        .Const(_SC("SONNY_GUY_C"),              SQMOD_SKIN_SONNY_GUY_C)
        .Const(_SC("COLUMBIAN_GUY_B"),          SQMOD_SKIN_COLUMBIAN_GUY_B)
        .Const(_SC("THUG_A"),                   SQMOD_SKIN_THUG_A)
        .Const(_SC("BEACH_GUY_H"),              SQMOD_SKIN_BEACH_GUY_H)
        .Const(_SC("GARBAGEMAN_C"),             SQMOD_SKIN_GARBAGEMAN_C)
        .Const(_SC("GARBAGEMAN_D"),             SQMOD_SKIN_GARBAGEMAN_D)
        .Const(_SC("GARBAGEMAN_E"),             SQMOD_SKIN_GARBAGEMAN_E)
        .Const(_SC("TRANNY"),                   SQMOD_SKIN_TRANNY)
        .Const(_SC("THUG_B"),                   SQMOD_SKIN_THUG_B)
        .Const(_SC("SPANDEX_GUY_A"),            SQMOD_SKIN_SPANDEX_GUY_A)
        .Const(_SC("SPANDEX_GUY_B"),            SQMOD_SKIN_SPANDEX_GUY_B)
        .Const(_SC("STRIPPER_A"),               SQMOD_SKIN_STRIPPER_A)
        .Const(_SC("STRIPPER_B"),               SQMOD_SKIN_STRIPPER_B)
        .Const(_SC("STRIPPER_C"),               SQMOD_SKIN_STRIPPER_C)
        .Const(_SC("STORE_CLERK"),              SQMOD_SKIN_STORE_CLERK)
    );

    Sqrat::ConstTable().Enum(_SC("EKEYCODE"), Sqrat::Enumeration()
        .Const(_SC("ABNT_C1"),              SQMOD_KEYCODE_ABNT_C1)
        .Const(_SC("ABNT_C2"),              SQMOD_KEYCODE_ABNT_C2)
        .Const(_SC("ADD"),                  SQMOD_KEYCODE_ADD)
        .Const(_SC("ATTN"),                 SQMOD_KEYCODE_ATTN)
        .Const(_SC("BACK"),                 SQMOD_KEYCODE_BACK)
        .Const(_SC("CANCEL"),               SQMOD_KEYCODE_CANCEL)
        .Const(_SC("CLEAR"),                SQMOD_KEYCODE_CLEAR)
        .Const(_SC("CRSEL"),                SQMOD_KEYCODE_CRSEL)
        .Const(_SC("DECIMAL"),              SQMOD_KEYCODE_DECIMAL)
        .Const(_SC("DIVIDE"),               SQMOD_KEYCODE_DIVIDE)
        .Const(_SC("EREOF"),                SQMOD_KEYCODE_EREOF)
        .Const(_SC("ESCAPE"),               SQMOD_KEYCODE_ESCAPE)
        .Const(_SC("EXECUTE"),              SQMOD_KEYCODE_EXECUTE)
        .Const(_SC("EXSEL"),                SQMOD_KEYCODE_EXSEL)
        .Const(_SC("ICO_CLEAR"),            SQMOD_KEYCODE_ICO_CLEAR)
        .Const(_SC("ICO_HELP"),             SQMOD_KEYCODE_ICO_HELP)
        .Const(_SC("KEY_0"),                SQMOD_KEYCODE_KEY_0)
        .Const(_SC("KEY_1"),                SQMOD_KEYCODE_KEY_1)
        .Const(_SC("KEY_2"),                SQMOD_KEYCODE_KEY_2)
        .Const(_SC("KEY_3"),                SQMOD_KEYCODE_KEY_3)
        .Const(_SC("KEY_4"),                SQMOD_KEYCODE_KEY_4)
        .Const(_SC("KEY_5"),                SQMOD_KEYCODE_KEY_5)
        .Const(_SC("KEY_6"),                SQMOD_KEYCODE_KEY_6)
        .Const(_SC("KEY_7"),                SQMOD_KEYCODE_KEY_7)
        .Const(_SC("KEY_8"),                SQMOD_KEYCODE_KEY_8)
        .Const(_SC("KEY_9"),                SQMOD_KEYCODE_KEY_9)
        .Const(_SC("KEY_A"),                SQMOD_KEYCODE_KEY_A)
        .Const(_SC("KEY_B"),                SQMOD_KEYCODE_KEY_B)
        .Const(_SC("KEY_C"),                SQMOD_KEYCODE_KEY_C)
        .Const(_SC("KEY_D"),                SQMOD_KEYCODE_KEY_D)
        .Const(_SC("KEY_E"),                SQMOD_KEYCODE_KEY_E)
        .Const(_SC("KEY_F"),                SQMOD_KEYCODE_KEY_F)
        .Const(_SC("KEY_G"),                SQMOD_KEYCODE_KEY_G)
        .Const(_SC("KEY_H"),                SQMOD_KEYCODE_KEY_H)
        .Const(_SC("KEY_I"),                SQMOD_KEYCODE_KEY_I)
        .Const(_SC("KEY_J"),                SQMOD_KEYCODE_KEY_J)
        .Const(_SC("KEY_K"),                SQMOD_KEYCODE_KEY_K)
        .Const(_SC("KEY_L"),                SQMOD_KEYCODE_KEY_L)
        .Const(_SC("KEY_M"),                SQMOD_KEYCODE_KEY_M)
        .Const(_SC("KEY_N"),                SQMOD_KEYCODE_KEY_N)
        .Const(_SC("KEY_O"),                SQMOD_KEYCODE_KEY_O)
        .Const(_SC("KEY_P"),                SQMOD_KEYCODE_KEY_P)
        .Const(_SC("KEY_Q"),                SQMOD_KEYCODE_KEY_Q)
        .Const(_SC("KEY_R"),                SQMOD_KEYCODE_KEY_R)
        .Const(_SC("KEY_S"),                SQMOD_KEYCODE_KEY_S)
        .Const(_SC("KEY_T"),                SQMOD_KEYCODE_KEY_T)
        .Const(_SC("KEY_U"),                SQMOD_KEYCODE_KEY_U)
        .Const(_SC("KEY_V"),                SQMOD_KEYCODE_KEY_V)
        .Const(_SC("KEY_W"),                SQMOD_KEYCODE_KEY_W)
        .Const(_SC("KEY_X"),                SQMOD_KEYCODE_KEY_X)
        .Const(_SC("KEY_Y"),                SQMOD_KEYCODE_KEY_Y)
        .Const(_SC("KEY_Z"),                SQMOD_KEYCODE_KEY_Z)
        .Const(_SC("MULTIPLY"),             SQMOD_KEYCODE_MULTIPLY)
        .Const(_SC("NONAME"),               SQMOD_KEYCODE_NONAME)
        .Const(_SC("NUMPAD0"),              SQMOD_KEYCODE_NUMPAD0)
        .Const(_SC("NUMPAD1"),              SQMOD_KEYCODE_NUMPAD1)
        .Const(_SC("NUMPAD2"),              SQMOD_KEYCODE_NUMPAD2)
        .Const(_SC("NUMPAD3"),              SQMOD_KEYCODE_NUMPAD3)
        .Const(_SC("NUMPAD4"),              SQMOD_KEYCODE_NUMPAD4)
        .Const(_SC("NUMPAD5"),              SQMOD_KEYCODE_NUMPAD5)
        .Const(_SC("NUMPAD6"),              SQMOD_KEYCODE_NUMPAD6)
        .Const(_SC("NUMPAD7"),              SQMOD_KEYCODE_NUMPAD7)
        .Const(_SC("NUMPAD8"),              SQMOD_KEYCODE_NUMPAD8)
        .Const(_SC("NUMPAD9"),              SQMOD_KEYCODE_NUMPAD9)
        .Const(_SC("OEM_1"),                SQMOD_KEYCODE_OEM_1)
        .Const(_SC("OEM_102"),              SQMOD_KEYCODE_OEM_102)
        .Const(_SC("OEM_2"),                SQMOD_KEYCODE_OEM_2)
        .Const(_SC("OEM_3"),                SQMOD_KEYCODE_OEM_3)
        .Const(_SC("OEM_4"),                SQMOD_KEYCODE_OEM_4)
        .Const(_SC("OEM_5"),                SQMOD_KEYCODE_OEM_5)
        .Const(_SC("OEM_6"),                SQMOD_KEYCODE_OEM_6)
        .Const(_SC("OEM_7"),                SQMOD_KEYCODE_OEM_7)
        .Const(_SC("OEM_8"),                SQMOD_KEYCODE_OEM_8)
        .Const(_SC("OEM_ATTN"),             SQMOD_KEYCODE_OEM_ATTN)
        .Const(_SC("OEM_AUTO"),             SQMOD_KEYCODE_OEM_AUTO)
        .Const(_SC("OEM_AX"),               SQMOD_KEYCODE_OEM_AX)
        .Const(_SC("OEM_BACKTAB"),          SQMOD_KEYCODE_OEM_BACKTAB)
        .Const(_SC("OEM_CLEAR"),            SQMOD_KEYCODE_OEM_CLEAR)
        .Const(_SC("OEM_COMMA"),            SQMOD_KEYCODE_OEM_COMMA)
        .Const(_SC("OEM_COPY"),             SQMOD_KEYCODE_OEM_COPY)
        .Const(_SC("OEM_CUSEL"),            SQMOD_KEYCODE_OEM_CUSEL)
        .Const(_SC("OEM_ENLW"),             SQMOD_KEYCODE_OEM_ENLW)
        .Const(_SC("OEM_FINISH"),           SQMOD_KEYCODE_OEM_FINISH)
        .Const(_SC("OEM_FJ_LOYA"),          SQMOD_KEYCODE_OEM_FJ_LOYA)
        .Const(_SC("OEM_FJ_MASSHOU"),       SQMOD_KEYCODE_OEM_FJ_MASSHOU)
        .Const(_SC("OEM_FJ_ROYA"),          SQMOD_KEYCODE_OEM_FJ_ROYA)
        .Const(_SC("OEM_FJ_TOUROKU"),       SQMOD_KEYCODE_OEM_FJ_TOUROKU)
        .Const(_SC("OEM_JUMP"),             SQMOD_KEYCODE_OEM_JUMP)
        .Const(_SC("OEM_MINUS"),            SQMOD_KEYCODE_OEM_MINUS)
        .Const(_SC("OEM_PA1"),              SQMOD_KEYCODE_OEM_PA1)
        .Const(_SC("OEM_PA2"),              SQMOD_KEYCODE_OEM_PA2)
        .Const(_SC("OEM_PA3"),              SQMOD_KEYCODE_OEM_PA3)
        .Const(_SC("OEM_PERIOD"),           SQMOD_KEYCODE_OEM_PERIOD)
        .Const(_SC("OEM_PLUS"),             SQMOD_KEYCODE_OEM_PLUS)
        .Const(_SC("OEM_RESET"),            SQMOD_KEYCODE_OEM_RESET)
        .Const(_SC("OEM_WSCTRL"),           SQMOD_KEYCODE_OEM_WSCTRL)
        .Const(_SC("PA1"),                  SQMOD_KEYCODE_PA1)
        .Const(_SC("PACKET"),               SQMOD_KEYCODE_PACKET)
        .Const(_SC("PLAY"),                 SQMOD_KEYCODE_PLAY)
        .Const(_SC("PROCESSKEY"),           SQMOD_KEYCODE_PROCESSKEY)
        .Const(_SC("RETURN"),               SQMOD_KEYCODE_RETURN)
        .Const(_SC("SELECT"),               SQMOD_KEYCODE_SELECT)
        .Const(_SC("SEPARATOR"),            SQMOD_KEYCODE_SEPARATOR)
        .Const(_SC("SPACE"),                SQMOD_KEYCODE_SPACE)
        .Const(_SC("SUBTRACT"),             SQMOD_KEYCODE_SUBTRACT)
        .Const(_SC("TAB"),                  SQMOD_KEYCODE_TAB)
        .Const(_SC("ZOOM"),                 SQMOD_KEYCODE_ZOOM)
        .Const(_SC("ACCEPT"),               SQMOD_KEYCODE_ACCEPT)
        .Const(_SC("APPS"),                 SQMOD_KEYCODE_APPS)
        .Const(_SC("BROWSER_BACK"),         SQMOD_KEYCODE_BROWSER_BACK)
        .Const(_SC("BROWSER_FAVORITES"),    SQMOD_KEYCODE_BROWSER_FAVORITES)
        .Const(_SC("BROWSER_FORWARD"),      SQMOD_KEYCODE_BROWSER_FORWARD)
        .Const(_SC("BROWSER_HOME"),         SQMOD_KEYCODE_BROWSER_HOME)
        .Const(_SC("BROWSER_REFRESH"),      SQMOD_KEYCODE_BROWSER_REFRESH)
        .Const(_SC("BROWSER_SEARCH"),       SQMOD_KEYCODE_BROWSER_SEARCH)
        .Const(_SC("BROWSER_STOP"),         SQMOD_KEYCODE_BROWSER_STOP)
        .Const(_SC("CAPITAL"),              SQMOD_KEYCODE_CAPITAL)
        .Const(_SC("CONVERT"),              SQMOD_KEYCODE_CONVERT)
        .Const(_SC("DELETE"),               SQMOD_KEYCODE_DELETE)
        .Const(_SC("DOWN"),                 SQMOD_KEYCODE_DOWN)
        .Const(_SC("END"),                  SQMOD_KEYCODE_END)
        .Const(_SC("F1"),                   SQMOD_KEYCODE_F1)
        .Const(_SC("F10"),                  SQMOD_KEYCODE_F10)
        .Const(_SC("F11"),                  SQMOD_KEYCODE_F11)
        .Const(_SC("F12"),                  SQMOD_KEYCODE_F12)
        .Const(_SC("F13"),                  SQMOD_KEYCODE_F13)
        .Const(_SC("F14"),                  SQMOD_KEYCODE_F14)
        .Const(_SC("F15"),                  SQMOD_KEYCODE_F15)
        .Const(_SC("F16"),                  SQMOD_KEYCODE_F16)
        .Const(_SC("F17"),                  SQMOD_KEYCODE_F17)
        .Const(_SC("F18"),                  SQMOD_KEYCODE_F18)
        .Const(_SC("F19"),                  SQMOD_KEYCODE_F19)
        .Const(_SC("F2"),                   SQMOD_KEYCODE_F2)
        .Const(_SC("F20"),                  SQMOD_KEYCODE_F20)
        .Const(_SC("F21"),                  SQMOD_KEYCODE_F21)
        .Const(_SC("F22"),                  SQMOD_KEYCODE_F22)
        .Const(_SC("F23"),                  SQMOD_KEYCODE_F23)
        .Const(_SC("F24"),                  SQMOD_KEYCODE_F24)
        .Const(_SC("F3"),                   SQMOD_KEYCODE_F3)
        .Const(_SC("F4"),                   SQMOD_KEYCODE_F4)
        .Const(_SC("F5"),                   SQMOD_KEYCODE_F5)
        .Const(_SC("F6"),                   SQMOD_KEYCODE_F6)
        .Const(_SC("F7"),                   SQMOD_KEYCODE_F7)
        .Const(_SC("F8"),                   SQMOD_KEYCODE_F8)
        .Const(_SC("F9"),                   SQMOD_KEYCODE_F9)
        .Const(_SC("FINAL"),                SQMOD_KEYCODE_FINAL)
        .Const(_SC("HELP"),                 SQMOD_KEYCODE_HELP)
        .Const(_SC("HOME"),                 SQMOD_KEYCODE_HOME)
        .Const(_SC("ICO_00"),               SQMOD_KEYCODE_ICO_00)
        .Const(_SC("INSERT"),               SQMOD_KEYCODE_INSERT)
        .Const(_SC("JUNJA"),                SQMOD_KEYCODE_JUNJA)
        .Const(_SC("KANA"),                 SQMOD_KEYCODE_KANA)
        .Const(_SC("KANJI"),                SQMOD_KEYCODE_KANJI)
        .Const(_SC("LAUNCH_APP1"),          SQMOD_KEYCODE_LAUNCH_APP1)
        .Const(_SC("LAUNCH_APP2"),          SQMOD_KEYCODE_LAUNCH_APP2)
        .Const(_SC("LAUNCH_MAIL"),          SQMOD_KEYCODE_LAUNCH_MAIL)
        .Const(_SC("LAUNCH_MEDIA_SELECT"),  SQMOD_KEYCODE_LAUNCH_MEDIA_SELECT)
        .Const(_SC("LBUTTON"),              SQMOD_KEYCODE_LBUTTON)
        .Const(_SC("LCONTROL"),             SQMOD_KEYCODE_LCONTROL)
        .Const(_SC("LEFT"),                 SQMOD_KEYCODE_LEFT)
        .Const(_SC("LMENU"),                SQMOD_KEYCODE_LMENU)
        .Const(_SC("LSHIFT"),               SQMOD_KEYCODE_LSHIFT)
        .Const(_SC("LWIN"),                 SQMOD_KEYCODE_LWIN)
        .Const(_SC("MBUTTON"),              SQMOD_KEYCODE_MBUTTON)
        .Const(_SC("MEDIA_NEXT_TRACK"),     SQMOD_KEYCODE_MEDIA_NEXT_TRACK)
        .Const(_SC("MEDIA_PLAY_PAUSE"),     SQMOD_KEYCODE_MEDIA_PLAY_PAUSE)
        .Const(_SC("MEDIA_PREV_TRACK"),     SQMOD_KEYCODE_MEDIA_PREV_TRACK)
        .Const(_SC("MEDIA_STOP"),           SQMOD_KEYCODE_MEDIA_STOP)
        .Const(_SC("MODECHANGE"),           SQMOD_KEYCODE_MODECHANGE)
        .Const(_SC("NEXT"),                 SQMOD_KEYCODE_NEXT)
        .Const(_SC("NONCONVERT"),           SQMOD_KEYCODE_NONCONVERT)
        .Const(_SC("NUMLOCK"),              SQMOD_KEYCODE_NUMLOCK)
        .Const(_SC("OEM_FJ_JISHO"),         SQMOD_KEYCODE_OEM_FJ_JISHO)
        .Const(_SC("PAUSE"),                SQMOD_KEYCODE_PAUSE)
        .Const(_SC("PRINT"),                SQMOD_KEYCODE_PRINT)
        .Const(_SC("PRIOR"),                SQMOD_KEYCODE_PRIOR)
        .Const(_SC("RBUTTON"),              SQMOD_KEYCODE_RBUTTON)
        .Const(_SC("RCONTROL"),             SQMOD_KEYCODE_RCONTROL)
        .Const(_SC("RIGHT"),                SQMOD_KEYCODE_RIGHT)
        .Const(_SC("RMENU"),                SQMOD_KEYCODE_RMENU)
        .Const(_SC("RSHIFT"),               SQMOD_KEYCODE_RSHIFT)
        .Const(_SC("RWIN"),                 SQMOD_KEYCODE_RWIN)
        .Const(_SC("SCROLL"),               SQMOD_KEYCODE_SCROLL)
        .Const(_SC("SLEEP"),                SQMOD_KEYCODE_SLEEP)
        .Const(_SC("SNAPSHOT"),             SQMOD_KEYCODE_SNAPSHOT)
        .Const(_SC("UP"),                   SQMOD_KEYCODE_UP)
        .Const(_SC("VOLUME_DOWN"),          SQMOD_KEYCODE_VOLUME_DOWN)
        .Const(_SC("VOLUME_MUTE"),          SQMOD_KEYCODE_VOLUME_MUTE)
        .Const(_SC("VOLUME_UP"),            SQMOD_KEYCODE_VOLUME_UP)
        .Const(_SC("XBUTTON1"),             SQMOD_KEYCODE_XBUTTON1)
        .Const(_SC("XBUTTON2"),             SQMOD_KEYCODE_XBUTTON2)
        .Const(_SC("NONE"),                 SQMOD_KEYCODE_NONE)
    );

    Sqrat::ConstTable().Enum(_SC("EASCII"), Sqrat::Enumeration()
        .Const(_SC("NUL"),                  SQMOD_ASCII_NUL)
        .Const(_SC("SOH"),                  SQMOD_ASCII_SOH)
        .Const(_SC("STX"),                  SQMOD_ASCII_STX)
        .Const(_SC("ETX"),                  SQMOD_ASCII_ETX)
        .Const(_SC("EOT"),                  SQMOD_ASCII_EOT)
        .Const(_SC("ENQ"),                  SQMOD_ASCII_ENQ)
        .Const(_SC("ACK"),                  SQMOD_ASCII_ACK)
        .Const(_SC("BEL"),                  SQMOD_ASCII_BEL)
        .Const(_SC("BS"),                   SQMOD_ASCII_BS)
        .Const(_SC("TAB"),                  SQMOD_ASCII_TAB)
        .Const(_SC("LF"),                   SQMOD_ASCII_LF)
        .Const(_SC("VT"),                   SQMOD_ASCII_VT)
        .Const(_SC("FF"),                   SQMOD_ASCII_FF)
        .Const(_SC("CR"),                   SQMOD_ASCII_CR)
        .Const(_SC("SO"),                   SQMOD_ASCII_SO)
        .Const(_SC("SI"),                   SQMOD_ASCII_SI)
        .Const(_SC("DLE"),                  SQMOD_ASCII_DLE)
        .Const(_SC("DC1"),                  SQMOD_ASCII_DC1)
        .Const(_SC("DC2"),                  SQMOD_ASCII_DC2)
        .Const(_SC("DC3"),                  SQMOD_ASCII_DC3)
        .Const(_SC("DC4"),                  SQMOD_ASCII_DC4)
        .Const(_SC("NAK"),                  SQMOD_ASCII_NAK)
        .Const(_SC("SYN"),                  SQMOD_ASCII_SYN)
        .Const(_SC("ETB"),                  SQMOD_ASCII_ETB)
        .Const(_SC("CAN"),                  SQMOD_ASCII_CAN)
        .Const(_SC("EM"),                   SQMOD_ASCII_EM)
        .Const(_SC("SUB"),                  SQMOD_ASCII_SUB)
        .Const(_SC("ESC"),                  SQMOD_ASCII_ESC)
        .Const(_SC("FS"),                   SQMOD_ASCII_FS)
        .Const(_SC("GS"),                   SQMOD_ASCII_GS)
        .Const(_SC("RS"),                   SQMOD_ASCII_RS)
        .Const(_SC("US"),                   SQMOD_ASCII_US)
        .Const(_SC("SPACE"),                SQMOD_ASCII_SPACE)
        .Const(_SC("EXCLAMATION_POINT"),    SQMOD_ASCII_EXCLAMATION_POINT)
        .Const(_SC("DOUBLE_QUOTES"),        SQMOD_ASCII_DOUBLE_QUOTES)
        .Const(_SC("NUMBER_SIGN"),          SQMOD_ASCII_NUMBER_SIGN)
        .Const(_SC("DOLLAR_SIGN"),          SQMOD_ASCII_DOLLAR_SIGN)
        .Const(_SC("PERCENT_SIGN"),         SQMOD_ASCII_PERCENT_SIGN)
        .Const(_SC("AMPERSAND"),            SQMOD_ASCII_AMPERSAND)
        .Const(_SC("SINGLE_QUOTE"),         SQMOD_ASCII_SINGLE_QUOTE)
        .Const(_SC("OPENING_PARENTHESIS"),  SQMOD_ASCII_OPENING_PARENTHESIS)
        .Const(_SC("CLOSING_PARENTHESIS"),  SQMOD_ASCII_CLOSING_PARENTHESIS)
        .Const(_SC("ASTERISK"),             SQMOD_ASCII_ASTERISK)
        .Const(_SC("PLUS"),                 SQMOD_ASCII_PLUS)
        .Const(_SC("COMMA"),                SQMOD_ASCII_COMMA)
        .Const(_SC("MINUS"),                SQMOD_ASCII_MINUS)
        .Const(_SC("PERIOD"),               SQMOD_ASCII_PERIOD)
        .Const(_SC("SLASH"),                SQMOD_ASCII_SLASH)
        .Const(_SC("ZERO"),                 SQMOD_ASCII_ZERO)
        .Const(_SC("ONE"),                  SQMOD_ASCII_ONE)
        .Const(_SC("TWO"),                  SQMOD_ASCII_TWO)
        .Const(_SC("THREE"),                SQMOD_ASCII_THREE)
        .Const(_SC("FOUR"),                 SQMOD_ASCII_FOUR)
        .Const(_SC("FIVE"),                 SQMOD_ASCII_FIVE)
        .Const(_SC("SIX"),                  SQMOD_ASCII_SIX)
        .Const(_SC("SEVEN"),                SQMOD_ASCII_SEVEN)
        .Const(_SC("EIGHT"),                SQMOD_ASCII_EIGHT)
        .Const(_SC("NINE"),                 SQMOD_ASCII_NINE)
        .Const(_SC("COLON"),                SQMOD_ASCII_COLON)
        .Const(_SC("EMICOLON"),             SQMOD_ASCII_EMICOLON)
        .Const(_SC("LESS_THAN_SIGN"),       SQMOD_ASCII_LESS_THAN_SIGN)
        .Const(_SC("EQUAL_SIGN"),           SQMOD_ASCII_EQUAL_SIGN)
        .Const(_SC("GREATER_THAN_SIGN"),    SQMOD_ASCII_GREATER_THAN_SIGN)
        .Const(_SC("QUESTION_MARK"),        SQMOD_ASCII_QUESTION_MARK)
        .Const(_SC("AT"),                   SQMOD_ASCII_AT)
        .Const(_SC("UPPER_A"),              SQMOD_ASCII_UPPER_A)
        .Const(_SC("UPPER_B"),              SQMOD_ASCII_UPPER_B)
        .Const(_SC("UPPER_C"),              SQMOD_ASCII_UPPER_C)
        .Const(_SC("UPPER_D"),              SQMOD_ASCII_UPPER_D)
        .Const(_SC("UPPER_E"),              SQMOD_ASCII_UPPER_E)
        .Const(_SC("UPPER_F"),              SQMOD_ASCII_UPPER_F)
        .Const(_SC("UPPER_G"),              SQMOD_ASCII_UPPER_G)
        .Const(_SC("UPPER_H"),              SQMOD_ASCII_UPPER_H)
        .Const(_SC("UPPER_I"),              SQMOD_ASCII_UPPER_I)
        .Const(_SC("UPPER_J"),              SQMOD_ASCII_UPPER_J)
        .Const(_SC("UPPER_K"),              SQMOD_ASCII_UPPER_K)
        .Const(_SC("UPPER_L"),              SQMOD_ASCII_UPPER_L)
        .Const(_SC("UPPER_M"),              SQMOD_ASCII_UPPER_M)
        .Const(_SC("UPPER_N"),              SQMOD_ASCII_UPPER_N)
        .Const(_SC("UPPER_O"),              SQMOD_ASCII_UPPER_O)
        .Const(_SC("UPPER_P"),              SQMOD_ASCII_UPPER_P)
        .Const(_SC("UPPER_Q"),              SQMOD_ASCII_UPPER_Q)
        .Const(_SC("UPPER_R"),              SQMOD_ASCII_UPPER_R)
        .Const(_SC("UPPER_S"),              SQMOD_ASCII_UPPER_S)
        .Const(_SC("UPPER_T"),              SQMOD_ASCII_UPPER_T)
        .Const(_SC("UPPER_U"),              SQMOD_ASCII_UPPER_U)
        .Const(_SC("UPPER_V"),              SQMOD_ASCII_UPPER_V)
        .Const(_SC("UPPER_W"),              SQMOD_ASCII_UPPER_W)
        .Const(_SC("UPPER_X"),              SQMOD_ASCII_UPPER_X)
        .Const(_SC("UPPER_Y"),              SQMOD_ASCII_UPPER_Y)
        .Const(_SC("UPPER_Z"),              SQMOD_ASCII_UPPER_Z)
        .Const(_SC("OPENING_BRACKET"),      SQMOD_ASCII_OPENING_BRACKET)
        .Const(_SC("BACKSLASH"),            SQMOD_ASCII_BACKSLASH)
        .Const(_SC("CLOSING_BRACKET"),      SQMOD_ASCII_CLOSING_BRACKET)
        .Const(_SC("CARET"),                SQMOD_ASCII_CARET)
        .Const(_SC("UNDERSCORE"),           SQMOD_ASCII_UNDERSCORE)
        .Const(_SC("GRAVE_ACCENT"),         SQMOD_ASCII_GRAVE_ACCENT)
        .Const(_SC("LOWER_A"),              SQMOD_ASCII_LOWER_A)
        .Const(_SC("LOWER_B"),              SQMOD_ASCII_LOWER_B)
        .Const(_SC("LOWER_C"),              SQMOD_ASCII_LOWER_C)
        .Const(_SC("LOWER_D"),              SQMOD_ASCII_LOWER_D)
        .Const(_SC("LOWER_E"),              SQMOD_ASCII_LOWER_E)
        .Const(_SC("LOWER_F"),              SQMOD_ASCII_LOWER_F)
        .Const(_SC("LOWER_G"),              SQMOD_ASCII_LOWER_G)
        .Const(_SC("LOWER_H"),              SQMOD_ASCII_LOWER_H)
        .Const(_SC("LOWER_I"),              SQMOD_ASCII_LOWER_I)
        .Const(_SC("LOWER_J"),              SQMOD_ASCII_LOWER_J)
        .Const(_SC("LOWER_K"),              SQMOD_ASCII_LOWER_K)
        .Const(_SC("LOWER_L"),              SQMOD_ASCII_LOWER_L)
        .Const(_SC("LOWER_M"),              SQMOD_ASCII_LOWER_M)
        .Const(_SC("LOWER_N"),              SQMOD_ASCII_LOWER_N)
        .Const(_SC("LOWER_O"),              SQMOD_ASCII_LOWER_O)
        .Const(_SC("LOWER_P"),              SQMOD_ASCII_LOWER_P)
        .Const(_SC("LOWER_Q"),              SQMOD_ASCII_LOWER_Q)
        .Const(_SC("LOWER_R"),              SQMOD_ASCII_LOWER_R)
        .Const(_SC("LOWER_S"),              SQMOD_ASCII_LOWER_S)
        .Const(_SC("LOWER_T"),              SQMOD_ASCII_LOWER_T)
        .Const(_SC("LOWER_U"),              SQMOD_ASCII_LOWER_U)
        .Const(_SC("LOWER_V"),              SQMOD_ASCII_LOWER_V)
        .Const(_SC("LOWER_W"),              SQMOD_ASCII_LOWER_W)
        .Const(_SC("LOWER_X"),              SQMOD_ASCII_LOWER_X)
        .Const(_SC("LOWER_Y"),              SQMOD_ASCII_LOWER_Y)
        .Const(_SC("LOWER_Z"),              SQMOD_ASCII_LOWER_Z)
        .Const(_SC("OPENING_BRACE"),        SQMOD_ASCII_OPENING_BRACE)
        .Const(_SC("VERTICAL_BAR"),         SQMOD_ASCII_VERTICAL_BAR)
        .Const(_SC("CLOSING_BRACE"),        SQMOD_ASCII_CLOSING_BRACE)
        .Const(_SC("TILDE"),                SQMOD_ASCII_TILDE)
        .Const(_SC("UNDEFINED"),            SQMOD_ASCII_UNDEFINED)
    );

    Sqrat::RootTable(v)
        .Func(_SC("GetKeyCodeName"), GetKeyCodeName )
        .Func(_SC("IsModelWeapon"), IsModelWeapon )
        .Func(_SC("IsModelActuallyWeapon"), IsModelActuallyWeapon )
        .Func(_SC("GetSkinName"), GetSkinName )
        .Func(_SC("GetSkinID"), GetSkinID )
        .Func(_SC("IsSkinValid"), IsSkinValid )
        .Func(_SC("GetVehicleModelFromName"), GetVehicleID )
        .Func(_SC("GetVehicleNameFromModel"), GetVehicleName )
        .Func(_SC("IsVehicleValid"), IsVehicleValid )
        .Func(_SC("GetWeaponName"), GetWeaponName )
        .Func(_SC("GetWeaponID"), GetWeaponID )
        .Func(_SC("IsWeaponValid"), IsWeaponValid )
        .Func(_SC("IsWeaponNatural"), IsWeaponNatural )
        .Func(_SC("WeaponToModel"), WeaponToModel )
        .Func(_SC("GetDistrictName"), GetDistrictName );
}
