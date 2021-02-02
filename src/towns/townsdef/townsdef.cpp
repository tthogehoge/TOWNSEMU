/* LICENSE>>
Copyright 2020 Soji Yamakawa (CaptainYS, http://www.ysflight.com)

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

<< LICENSE */
#include <unordered_map>
#include "townsdef.h"



std::string TownsTypeToStr(unsigned int townsType)
{
	switch(townsType)
	{
	case FMR_50_60:
		return "R50";
	case FMR_50S:
		return "R50S";
	case FMR_70:
		return "R70";
	case TOWNSTYPE_MODEL1_2:
		return "MODEL2";
	case TOWNSTYPE_1F_2F:
		return "2F";
	case TOWNSTYPE_10F_20F:
		return "20F";
	case TOWNSTYPE_2_UX:
		return "UX";
	case TOWNSTYPE_2_CX:
		return "CX";
	case TOWNSTYPE_2_UG:
		return "UG";
	case TOWNSTYPE_2_HG:
		return "HG";
	case TOWNSTYPE_2_HR:
		return "HR";
	case TOWNSTYPE_2_UR:
		return "UR";
	case TOWNSTYPE_2_MA:
		return "MA";
	case TOWNSTYPE_2_MX:
		return "MX";
	case TOWNSTYPE_2_ME:
		return "ME";
	case TOWNSTYPE_2_MF_FRESH:
		return "MF";
	case TOWNSTYPE_2_HC:
		return "HC";
	}
	return "UNKNOWN";
}
unsigned int StrToTownsType(std::string str)
{
	if("R50"==str)
	{
		return FMR_50_60;
	}
	if("R50S"==str)
	{
		return FMR_50S;
	}
	if("R70"==str)
	{
		return FMR_70;
	}
	if("MODEL2"==str)
	{
		return TOWNSTYPE_MODEL1_2;
	}
	if("2F"==str)
	{
		return TOWNSTYPE_1F_2F;
	}
	if("20F"==str)
	{
		return TOWNSTYPE_10F_20F;
	}
	if("UX"==str)
	{
		return TOWNSTYPE_2_UX;
	}
	if("CX"==str)
	{
		return TOWNSTYPE_2_CX;
	}
	if("UG"==str)
	{
		return TOWNSTYPE_2_UG;
	}
	if("HG"==str)
	{
		return TOWNSTYPE_2_HG;
	}
	if("HR"==str)
	{
		return TOWNSTYPE_2_HR;
	}
	if("UR"==str)
	{
		return TOWNSTYPE_2_UR;
	}
	if("MA"==str)
	{
		return TOWNSTYPE_2_MA;
	}
	if("MX"==str)
	{
		return TOWNSTYPE_2_MX;
	}
	if("ME"==str)
	{
		return TOWNSTYPE_2_ME;
	}
	if("MF"==str || "FRESH"==str)
	{
		return TOWNSTYPE_2_MF_FRESH;
	}
	if("HC"==str)
	{
		return TOWNSTYPE_2_HC;
	}
	return TOWNSTYPE_UNKNOWN;
}

unsigned int TownsStrToKeyComb(std::string str)
{
	if("NONE"==str || "none"==str)
	{
		return BOOT_KEYCOMB_NONE;
	}
	if("CD"==str || "cd"==str)
	{
		return BOOT_KEYCOMB_CD;
	}
	if("F0"==str || "f0"==str)
	{
		return BOOT_KEYCOMB_F0;
	}
	if("F1"==str || "f1"==str)
	{
		return BOOT_KEYCOMB_F1;
	}
	if("F2"==str || "f2"==str)
	{
		return BOOT_KEYCOMB_F2;
	}
	if("F3"==str || "f3"==str)
	{
		return BOOT_KEYCOMB_F3;
	}
	if("H0"==str || "h0"==str)
	{
		return BOOT_KEYCOMB_H0;
	}
	if("H1"==str || "h1"==str)
	{
		return BOOT_KEYCOMB_H1;
	}
	if("H2"==str || "h2"==str)
	{
		return BOOT_KEYCOMB_H2;
	}
	if("H3"==str || "h3"==str)
	{
		return BOOT_KEYCOMB_H3;
	}
	if("H4"==str || "h4"==str)
	{
		return BOOT_KEYCOMB_H4;
	}
	if("ICM"==str || "icm"==str)
	{
		return BOOT_KEYCOMB_ICM;
	}
	if("DEBUG"==str || "debug"==str)
	{
		return BOOT_KEYCOMB_DEBUG;
	}
	if("PADA"==str || "pada"==str)
	{
		return BOOT_KEYCOMB_PAD_A;
	}
	if("PADB"==str || "padb"==str)
	{
		return BOOT_KEYCOMB_PAD_B;
	}
	return BOOT_KEYCOMB_NONE;
}

std::string TownsKeyCombToStr(unsigned int keycomb)
{
	switch(keycomb)
	{
	case BOOT_KEYCOMB_NONE:
		break;
	case BOOT_KEYCOMB_CD:
		return "CD";
	case BOOT_KEYCOMB_F0:
		return "F0";
	case BOOT_KEYCOMB_F1:
		return "F1";
	case BOOT_KEYCOMB_F2:
		return "F2";
	case BOOT_KEYCOMB_F3:
		return "F3";
	case BOOT_KEYCOMB_H0:
		return "H0";
	case BOOT_KEYCOMB_H1:
		return "H1";
	case BOOT_KEYCOMB_H2:
		return "H2";
	case BOOT_KEYCOMB_H3:
		return "H3";
	case BOOT_KEYCOMB_H4:
		return "H4";
	case BOOT_KEYCOMB_ICM:
		return "ICM";
	case BOOT_KEYCOMB_DEBUG:
		return "DEBUG";
	case BOOT_KEYCOMB_PAD_A:
		return "PADA";
	case BOOT_KEYCOMB_PAD_B:
		return "PADB";
	}
	return "NONE";
}

unsigned int TownsStrToGamePortEmu(std::string str)
{
	if("NONE"==str || "none"==str)
	{
		return TOWNS_GAMEPORTEMU_NONE;
	}
	if("MOUSE"==str || "mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE;
	}
	if("KEY"==str || "key"==str)
	{
		return TOWNS_GAMEPORTEMU_KEYBOARD;
	}
	if("PHYS0"==str || "phys0"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL0;
	}
	if("PHYS1"==str || "phys1"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL1;
	}
	if("PHYS2"==str || "phys2"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL2;
	}
	if("PHYS3"==str || "phys3"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL3;
	}
	if("PHYS4"==str || "phys4"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL4;
	}
	if("PHYS5"==str || "phys5"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL5;
	}
	if("PHYS6"==str || "phys6"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL6;
	}
	if("PHYS7"==str || "phys7"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL7;
	}
	if("ANA0"==str || "ana0"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG0;
	}
	if("ANA1"==str || "ana1"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG1;
	}
	if("ANA2"==str || "ana2"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG2;
	}
	if("ANA3"==str || "ana3"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG3;
	}
	if("ANA4"==str || "ana4"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG4;
	}
	if("ANA5"==str || "ana5"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG5;
	}
	if("ANA6"==str || "ana6"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG6;
	}
	if("ANA7"==str || "ana7"==str)
	{
		return TOWNS_GAMEPORTEMU_ANALOG7;
	}
	if("PHYS0CYB"==str || "phys0cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL0_AS_CYBERSTICK;
	}
	if("PHYS1CYB"==str || "phys1cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL1_AS_CYBERSTICK;
	}
	if("PHYS2CYB"==str || "phys2cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL2_AS_CYBERSTICK;
	}
	if("PHYS3CYB"==str || "phys3cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL3_AS_CYBERSTICK;
	}
	if("PHYS4CYB"==str || "phys4cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL4_AS_CYBERSTICK;
	}
	if("PHYS5CYB"==str || "phys5cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL5_AS_CYBERSTICK;
	}
	if("PHYS6CYB"==str || "phys6cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL6_AS_CYBERSTICK;
	}
	if("PHYS7CYB"==str || "phys7cyb"==str)
	{
		return TOWNS_GAMEPORTEMU_PHYSICAL7_AS_CYBERSTICK;
	}

	if("KEYMOUSE"==str || "keymouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_KEY;
	}
	if("NUMPADMOUSE"==str || "numpadmouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_NUMPAD;
	}


	if("PHYS0MOUSE"==str || "phys0mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL0;
	}
	if("PHYS1MOUSE"==str || "phys1mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL1;
	}
	if("PHYS2MOUSE"==str || "phys2mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL2;
	}
	if("PHYS3MOUSE"==str || "phys3mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL3;
	}
	if("PHYS4MOUSE"==str || "phys4mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL4;
	}
	if("PHYS5MOUSE"==str || "phys5mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL5;
	}
	if("PHYS6MOUSE"==str || "phys6mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL6;
	}
	if("PHYS7MOUSE"==str || "phys7mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL7;
	}

	if("ANA0MOUSE"==str || "ana0mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG0;
	}
	if("ANA1MOUSE"==str || "ana1mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG1;
	}
	if("ANA2MOUSE"==str || "ana2mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG2;
	}
	if("ANA3MOUSE"==str || "ana3mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG3;
	}
	if("ANA4MOUSE"==str || "ana4mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG4;
	}
	if("ANA5MOUSE"==str || "ana5mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG5;
	}
	if("ANA6MOUSE"==str || "ana6mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG6;
	}
	if("ANA7MOUSE"==str || "ana7mouse"==str)
	{
		return TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG7;
	}

	return TOWNS_GAMEPORTEMU_NONE;
}

std::string TownsGamePortEmuToStr(unsigned int emu)
{
	switch(emu)
	{
	case TOWNS_GAMEPORTEMU_NONE:
		return "NONE";
	case TOWNS_GAMEPORTEMU_MOUSE:
		return "MOUSE";
	case TOWNS_GAMEPORTEMU_KEYBOARD:
		return "KEY";
	case TOWNS_GAMEPORTEMU_PHYSICAL0:
		return "PHYS0";
	case TOWNS_GAMEPORTEMU_PHYSICAL1:
		return "PHYS1";
	case TOWNS_GAMEPORTEMU_PHYSICAL2:
		return "PHYS2";
	case TOWNS_GAMEPORTEMU_PHYSICAL3:
		return "PHYS3";
	case TOWNS_GAMEPORTEMU_PHYSICAL4:
		return "PHYS4";
	case TOWNS_GAMEPORTEMU_PHYSICAL5:
		return "PHYS5";
	case TOWNS_GAMEPORTEMU_PHYSICAL6:
		return "PHYS6";
	case TOWNS_GAMEPORTEMU_PHYSICAL7:
		return "PHYS7";
	case TOWNS_GAMEPORTEMU_ANALOG0:
		return "ANA0";
	case TOWNS_GAMEPORTEMU_ANALOG1:
		return "ANA1";
	case TOWNS_GAMEPORTEMU_ANALOG2:
		return "ANA2";
	case TOWNS_GAMEPORTEMU_ANALOG3:
		return "ANA3";
	case TOWNS_GAMEPORTEMU_ANALOG4:
		return "ANA4";
	case TOWNS_GAMEPORTEMU_ANALOG5:
		return "ANA5";
	case TOWNS_GAMEPORTEMU_ANALOG6:
		return "ANA6";
	case TOWNS_GAMEPORTEMU_ANALOG7:
		return "ANA7";
	case TOWNS_GAMEPORTEMU_PHYSICAL0_AS_CYBERSTICK:
		return "PHYS0CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL1_AS_CYBERSTICK:
		return "PHYS1CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL2_AS_CYBERSTICK:
		return "PHYS2CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL3_AS_CYBERSTICK:
		return "PHYS3CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL4_AS_CYBERSTICK:
		return "PHYS4CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL5_AS_CYBERSTICK:
		return "PHYS5CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL6_AS_CYBERSTICK:
		return "PHYS6CYB";
	case TOWNS_GAMEPORTEMU_PHYSICAL7_AS_CYBERSTICK:
		return "PHYS7CYB";

	case TOWNS_GAMEPORTEMU_MOUSE_BY_KEY:
		return "KEYMOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_NUMPAD:
		return "NUMPADMOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL0:
		return "PHYS0MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL1:
		return "PHYS1MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL2:
		return "PHYS2MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL3:
		return "PHYS3MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL4:
		return "PHYS4MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL5:
		return "PHYS5MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL6:
		return "PHYS6MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_PHYSICAL7:
		return "PHYS7MOUSE";

	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG0:
		return "ANA0MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG1:
		return "ANA1MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG2:
		return "ANA2MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG3:
		return "ANA3MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG4:
		return "ANA4MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG5:
		return "ANA5MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG6:
		return "ANA6MOUSE";
	case TOWNS_GAMEPORTEMU_MOUSE_BY_ANALOG7:
		return "ANA7MOUSE";
	}
	return "NONE";
}

unsigned int TownsStrToApp(std::string str)
{
	if("WINGCOMMANDER1"==str || "WC1"==str)
	{
		return TOWNS_APPSPECIFIC_WINGCOMMANDER1;
	}
	if("WINGCOMMANDER2"==str || "WC2"==str)
	{
		return TOWNS_APPSPECIFIC_WINGCOMMANDER2;
	}
	if("SUPERDAISEN"==str)
	{
		return TOWNS_APPSPECIFIC_SUPERDAISEN;
	}
	if("LEMMINGS"==str)
	{
		return TOWNS_APPSPECIFIC_LEMMINGS;
	}
	if("LEMMINGS2"==str)
	{
		return TOWNS_APPSPECIFIC_LEMMINGS2;
	}
	if("STRIKECOMMANDER"==str)
	{
		return TOWNS_APPSPECIFIC_STRIKECOMMANDER;
	}
	if("AMARANTH3"==str)
	{
		return TOWNS_APPSPECIFIC_AMARANTH3;
	}
	if("ULTIMAUNDERWORLD"==str)
	{
		return TOWNS_APPSPECIFIC_ULTIMAUNDERWORLD;
	}
	if("OPERATIONWOLF"==str || "OPERATION_WOLF"==str)
	{
		return TOWNS_APPSPECIFIC_OPERATIONWOLF;
	}
	if("BRANDISH"==str)
	{
		return TOWNS_APPSPECIFIC_BRANDISH;
	}
	if("AIRWARRIORV2"==str || "AIRWARV2"==str)
	{
		return TOWNS_APPSPECIFIC_AIRWARRIOR_V2;
	}
	return TOWNS_APPSPECIFIC_NONE;
}
std::string TownsAppToStr(unsigned int i)
{
	switch(i)
	{
	default:
		return "NONE";
	case TOWNS_APPSPECIFIC_WINGCOMMANDER1:
		return "WINGCOMMANDER1";
	case TOWNS_APPSPECIFIC_WINGCOMMANDER2:
		return "WINGCOMMANDER2";
	case TOWNS_APPSPECIFIC_SUPERDAISEN:
		return "SUPERDAISEN";
	case TOWNS_APPSPECIFIC_LEMMINGS:
		return "LEMMINGS";
	case TOWNS_APPSPECIFIC_LEMMINGS2:
		return "LEMMINGS2";
	case TOWNS_APPSPECIFIC_STRIKECOMMANDER:
		return "STRIKECOMMANDER";
	case TOWNS_APPSPECIFIC_AMARANTH3:
		return "AMARANTH3";
	case TOWNS_APPSPECIFIC_ULTIMAUNDERWORLD:
		return "ULTIMAUNDERWORLD";
	case TOWNS_APPSPECIFIC_OPERATIONWOLF:
		return "OPERATIONWOLF";
	case TOWNS_APPSPECIFIC_BRANDISH:
		return "BRANDISH";
	case TOWNS_APPSPECIFIC_AIRWARRIOR_V2:
		return "AIRWARRIORV2";
	}
}

std::string TownsKeyCodeToStr(unsigned int keyCode)
{
	static std::unordered_map <unsigned,std::string> map;
	if(map.empty())
	{
		map[TOWNS_JISKEY_NULL]="TOWNS_JISKEY_NULL";

		map[TOWNS_JISKEY_BREAK]="TOWNS_JISKEY_BREAK";
		map[TOWNS_JISKEY_COPY]="TOWNS_JISKEY_COPY";
		map[TOWNS_JISKEY_PF01]="TOWNS_JISKEY_PF01";
		map[TOWNS_JISKEY_PF02]="TOWNS_JISKEY_PF02";
		map[TOWNS_JISKEY_PF03]="TOWNS_JISKEY_PF03";
		map[TOWNS_JISKEY_PF04]="TOWNS_JISKEY_PF04";
		map[TOWNS_JISKEY_PF05]="TOWNS_JISKEY_PF05";
		map[TOWNS_JISKEY_PF06]="TOWNS_JISKEY_PF06";
		map[TOWNS_JISKEY_PF07]="TOWNS_JISKEY_PF07";
		map[TOWNS_JISKEY_PF08]="TOWNS_JISKEY_PF08";
		map[TOWNS_JISKEY_PF09]="TOWNS_JISKEY_PF09";
		map[TOWNS_JISKEY_PF10]="TOWNS_JISKEY_PF10";
		map[TOWNS_JISKEY_PF11]="TOWNS_JISKEY_PF11";
		map[TOWNS_JISKEY_PF12]="TOWNS_JISKEY_PF12";

		map[TOWNS_JISKEY_PF13]="TOWNS_JISKEY_PF13";
		map[TOWNS_JISKEY_PF14]="TOWNS_JISKEY_PF14";
		map[TOWNS_JISKEY_PF15]="TOWNS_JISKEY_PF15";
		map[TOWNS_JISKEY_PF16]="TOWNS_JISKEY_PF16";
		map[TOWNS_JISKEY_PF17]="TOWNS_JISKEY_PF17";
		map[TOWNS_JISKEY_PF18]="TOWNS_JISKEY_PF18";
		map[TOWNS_JISKEY_PF19]="TOWNS_JISKEY_PF19";
		map[TOWNS_JISKEY_PF20]="TOWNS_JISKEY_PF20";

		map[TOWNS_JISKEY_KANJI_DIC]="TOWNS_JISKEY_KANJI_DIC";
		map[TOWNS_JISKEY_ERASE_WORD]="TOWNS_JISKEY_ERASE_WORD";
		map[TOWNS_JISKEY_ADD_WORD]="TOWNS_JISKEY_ADD_WORD";
		map[TOWNS_JISKEY_PREV]="TOWNS_JISKEY_PREV";
		map[TOWNS_JISKEY_HOME]="TOWNS_JISKEY_HOME";
		map[TOWNS_JISKEY_NEXT]="TOWNS_JISKEY_NEXT";
		map[TOWNS_JISKEY_CHAR_PITCH]="TOWNS_JISKEY_CHAR_PITCH";
		map[TOWNS_JISKEY_DELETE]="TOWNS_JISKEY_DELETE";
		map[TOWNS_JISKEY_INSERT]="TOWNS_JISKEY_INSERT";

		map[TOWNS_JISKEY_UP]="TOWNS_JISKEY_UP";
		map[TOWNS_JISKEY_LEFT]="TOWNS_JISKEY_LEFT";
		map[TOWNS_JISKEY_RIGHT]="TOWNS_JISKEY_RIGHT";
		map[TOWNS_JISKEY_DOWN]="TOWNS_JISKEY_DOWN";

		map[TOWNS_JISKEY_EXECUTE]="TOWNS_JISKEY_EXECUTE";

		map[TOWNS_JISKEY_ESC]="TOWNS_JISKEY_ESC";
		map[TOWNS_JISKEY_1]="TOWNS_JISKEY_1";
		map[TOWNS_JISKEY_2]="TOWNS_JISKEY_2";
		map[TOWNS_JISKEY_3]="TOWNS_JISKEY_3";
		map[TOWNS_JISKEY_4]="TOWNS_JISKEY_4";
		map[TOWNS_JISKEY_5]="TOWNS_JISKEY_5";
		map[TOWNS_JISKEY_6]="TOWNS_JISKEY_6";
		map[TOWNS_JISKEY_7]="TOWNS_JISKEY_7";
		map[TOWNS_JISKEY_8]="TOWNS_JISKEY_8";
		map[TOWNS_JISKEY_9]="TOWNS_JISKEY_9";
		map[TOWNS_JISKEY_0]="TOWNS_JISKEY_0";
		map[TOWNS_JISKEY_MINUS]="TOWNS_JISKEY_MINUS";
		map[TOWNS_JISKEY_HAT]="TOWNS_JISKEY_HAT";
		map[TOWNS_JISKEY_BACKSLASH]="TOWNS_JISKEY_BACKSLASH";
		map[TOWNS_JISKEY_BACKSPACE]="TOWNS_JISKEY_BACKSPACE";

		map[TOWNS_JISKEY_TAB]="TOWNS_JISKEY_TAB";
		map[TOWNS_JISKEY_Q]="TOWNS_JISKEY_Q";
		map[TOWNS_JISKEY_W]="TOWNS_JISKEY_W";
		map[TOWNS_JISKEY_E]="TOWNS_JISKEY_E";
		map[TOWNS_JISKEY_R]="TOWNS_JISKEY_R";
		map[TOWNS_JISKEY_T]="TOWNS_JISKEY_T";
		map[TOWNS_JISKEY_Y]="TOWNS_JISKEY_Y";
		map[TOWNS_JISKEY_U]="TOWNS_JISKEY_U";
		map[TOWNS_JISKEY_I]="TOWNS_JISKEY_I";
		map[TOWNS_JISKEY_O]="TOWNS_JISKEY_O";
		map[TOWNS_JISKEY_P]="TOWNS_JISKEY_P";
		map[TOWNS_JISKEY_AT]="TOWNS_JISKEY_AT";
		map[TOWNS_JISKEY_LEFT_SQ_BRACKET]="TOWNS_JISKEY_LEFT_SQ_BRACKET";
		map[TOWNS_JISKEY_RETURN]="TOWNS_JISKEY_RETURN";

		map[TOWNS_JISKEY_CTRL]="TOWNS_JISKEY_CTRL";
		map[TOWNS_JISKEY_A]="TOWNS_JISKEY_A";
		map[TOWNS_JISKEY_S]="TOWNS_JISKEY_S";
		map[TOWNS_JISKEY_D]="TOWNS_JISKEY_D";
		map[TOWNS_JISKEY_F]="TOWNS_JISKEY_F";
		map[TOWNS_JISKEY_G]="TOWNS_JISKEY_G";
		map[TOWNS_JISKEY_H]="TOWNS_JISKEY_H";
		map[TOWNS_JISKEY_J]="TOWNS_JISKEY_J";
		map[TOWNS_JISKEY_K]="TOWNS_JISKEY_K";
		map[TOWNS_JISKEY_L]="TOWNS_JISKEY_L";
		map[TOWNS_JISKEY_SEMICOLON]="TOWNS_JISKEY_SEMICOLON";
		map[TOWNS_JISKEY_COLON]="TOWNS_JISKEY_COLON";
		map[TOWNS_JISKEY_RIGHT_SQ_BRACKET]="TOWNS_JISKEY_RIGHT_SQ_BRACKET";

		map[TOWNS_JISKEY_SHIFT]="TOWNS_JISKEY_SHIFT";
		map[TOWNS_JISKEY_Z]="TOWNS_JISKEY_Z";
		map[TOWNS_JISKEY_X]="TOWNS_JISKEY_X";
		map[TOWNS_JISKEY_C]="TOWNS_JISKEY_C";
		map[TOWNS_JISKEY_V]="TOWNS_JISKEY_V";
		map[TOWNS_JISKEY_B]="TOWNS_JISKEY_B";
		map[TOWNS_JISKEY_N]="TOWNS_JISKEY_N";
		map[TOWNS_JISKEY_M]="TOWNS_JISKEY_M";
		map[TOWNS_JISKEY_COMMA]="TOWNS_JISKEY_COMMA";
		map[TOWNS_JISKEY_DOT]="TOWNS_JISKEY_DOT";
		map[TOWNS_JISKEY_SLASH]="TOWNS_JISKEY_SLASH";
		map[TOWNS_JISKEY_DOUBLEQUOTE]="TOWNS_JISKEY_DOUBLEQUOTE";

		map[TOWNS_JISKEY_HIRAGANA]="TOWNS_JISKEY_HIRAGANA";
		map[TOWNS_JISKEY_CAPS]="TOWNS_JISKEY_CAPS";
		map[TOWNS_JISKEY_SPACE]="TOWNS_JISKEY_SPACE";
		map[TOWNS_JISKEY_KANA_KANJI]="TOWNS_JISKEY_KANA_KANJI";
		map[TOWNS_JISKEY_KATAKANA]="TOWNS_JISKEY_KATAKANA";
		map[TOWNS_JISKEY_CANCEL]="TOWNS_JISKEY_CANCEL";
		map[TOWNS_JISKEY_NO_CONVERT]="TOWNS_JISKEY_NO_CONVERT";
		map[TOWNS_JISKEY_CONVERT]="TOWNS_JISKEY_CONVERT";

		map[TOWNS_JISKEY_NUM_STAR]="TOWNS_JISKEY_NUM_STAR";
		map[TOWNS_JISKEY_NUM_SLASH]="TOWNS_JISKEY_NUM_SLASH";
		map[TOWNS_JISKEY_NUM_PLUS]="TOWNS_JISKEY_NUM_PLUS";
		map[TOWNS_JISKEY_NUM_MINUS]="TOWNS_JISKEY_NUM_MINUS";
		map[TOWNS_JISKEY_NUM_7]="TOWNS_JISKEY_NUM_7";
		map[TOWNS_JISKEY_NUM_8]="TOWNS_JISKEY_NUM_8";
		map[TOWNS_JISKEY_NUM_9]="TOWNS_JISKEY_NUM_9";
		map[TOWNS_JISKEY_NUM_EQUAL]="TOWNS_JISKEY_NUM_EQUAL";
		map[TOWNS_JISKEY_NUM_4]="TOWNS_JISKEY_NUM_4";
		map[TOWNS_JISKEY_NUM_5]="TOWNS_JISKEY_NUM_5";
		map[TOWNS_JISKEY_NUM_6]="TOWNS_JISKEY_NUM_6";
		map[TOWNS_JISKEY_NUM_DOT]="TOWNS_JISKEY_NUM_DOT";
		map[TOWNS_JISKEY_NUM_1]="TOWNS_JISKEY_NUM_1";
		map[TOWNS_JISKEY_NUM_2]="TOWNS_JISKEY_NUM_2";
		map[TOWNS_JISKEY_NUM_3]="TOWNS_JISKEY_NUM_3";
		map[TOWNS_JISKEY_NUM_RETURN]="TOWNS_JISKEY_NUM_RETURN";
		map[TOWNS_JISKEY_NUM_0]="TOWNS_JISKEY_NUM_0";
		map[TOWNS_JISKEY_NUM_000]="TOWNS_JISKEY_NUM_000";

		map[TOWNS_JISKEY_ALT]="TOWNS_JISKEY_ALT";
	}
	auto found=map.find(keyCode);
	if(map.end()!=found)
	{
		return found->second;
	}
	return "TOWNS_JISKEY_NULL";
}

std::string TownsKeyboardModeToStr(unsigned int keyboardMode)
{
	switch(keyboardMode)
	{
	case TOWNS_KEYBOARD_MODE_DIRECT:
		return "DIRECT";
	case TOWNS_KEYBOARD_MODE_TRANSLATION1:
		return "TRANS1";
	case TOWNS_KEYBOARD_MODE_TRANSLATION2:
		return "TRANS2";
	case TOWNS_KEYBOARD_MODE_TRANSLATION3:
		return "TRANS3";
	}
	return "DEFAULT";
}
unsigned int TownsStrToKeyboardMode(std::string str)
{
	if(str=="DIRECT")
	{
		return TOWNS_KEYBOARD_MODE_DIRECT;
	}
	else if(str=="TRANS1")
	{
		return TOWNS_KEYBOARD_MODE_TRANSLATION1;
	}
	else if(str=="TRANS2")
	{
		return TOWNS_KEYBOARD_MODE_TRANSLATION2;
	}
	else if(str=="TRANS3")
	{
		return TOWNS_KEYBOARD_MODE_TRANSLATION3;
	}
	return TOWNS_KEYBOARD_MODE_DEFAULT;
}

unsigned int TownsStrToKeyCode(std::string str)
{
	static std::unordered_map <std::string,unsigned> map;
	if(map.empty())
	{
		map["TOWNS_JISKEY_NULL"]=TOWNS_JISKEY_NULL;

		map["TOWNS_JISKEY_BREAK"]=TOWNS_JISKEY_BREAK;
		map["TOWNS_JISKEY_COPY"]=TOWNS_JISKEY_COPY;
		map["TOWNS_JISKEY_PF01"]=TOWNS_JISKEY_PF01;
		map["TOWNS_JISKEY_PF02"]=TOWNS_JISKEY_PF02;
		map["TOWNS_JISKEY_PF03"]=TOWNS_JISKEY_PF03;
		map["TOWNS_JISKEY_PF04"]=TOWNS_JISKEY_PF04;
		map["TOWNS_JISKEY_PF05"]=TOWNS_JISKEY_PF05;
		map["TOWNS_JISKEY_PF06"]=TOWNS_JISKEY_PF06;
		map["TOWNS_JISKEY_PF07"]=TOWNS_JISKEY_PF07;
		map["TOWNS_JISKEY_PF08"]=TOWNS_JISKEY_PF08;
		map["TOWNS_JISKEY_PF09"]=TOWNS_JISKEY_PF09;
		map["TOWNS_JISKEY_PF10"]=TOWNS_JISKEY_PF10;
		map["TOWNS_JISKEY_PF11"]=TOWNS_JISKEY_PF11;
		map["TOWNS_JISKEY_PF12"]=TOWNS_JISKEY_PF12;

		map["TOWNS_JISKEY_PF13"]=TOWNS_JISKEY_PF13;
		map["TOWNS_JISKEY_PF14"]=TOWNS_JISKEY_PF14;
		map["TOWNS_JISKEY_PF15"]=TOWNS_JISKEY_PF15;
		map["TOWNS_JISKEY_PF16"]=TOWNS_JISKEY_PF16;
		map["TOWNS_JISKEY_PF17"]=TOWNS_JISKEY_PF17;
		map["TOWNS_JISKEY_PF18"]=TOWNS_JISKEY_PF18;
		map["TOWNS_JISKEY_PF19"]=TOWNS_JISKEY_PF19;
		map["TOWNS_JISKEY_PF20"]=TOWNS_JISKEY_PF20;

		map["TOWNS_JISKEY_KANJI_DIC"]=TOWNS_JISKEY_KANJI_DIC;
		map["TOWNS_JISKEY_ERASE_WORD"]=TOWNS_JISKEY_ERASE_WORD;
		map["TOWNS_JISKEY_ADD_WORD"]=TOWNS_JISKEY_ADD_WORD;
		map["TOWNS_JISKEY_PREV"]=TOWNS_JISKEY_PREV;
		map["TOWNS_JISKEY_HOME"]=TOWNS_JISKEY_HOME;
		map["TOWNS_JISKEY_NEXT"]=TOWNS_JISKEY_NEXT;
		map["TOWNS_JISKEY_CHAR_PITCH"]=TOWNS_JISKEY_CHAR_PITCH;
		map["TOWNS_JISKEY_DELETE"]=TOWNS_JISKEY_DELETE;
		map["TOWNS_JISKEY_INSERT"]=TOWNS_JISKEY_INSERT;

		map["TOWNS_JISKEY_UP"]=TOWNS_JISKEY_UP;
		map["TOWNS_JISKEY_LEFT"]=TOWNS_JISKEY_LEFT;
		map["TOWNS_JISKEY_RIGHT"]=TOWNS_JISKEY_RIGHT;
		map["TOWNS_JISKEY_DOWN"]=TOWNS_JISKEY_DOWN;

		map["TOWNS_JISKEY_EXECUTE"]=TOWNS_JISKEY_EXECUTE;

		map["TOWNS_JISKEY_ESC"]=TOWNS_JISKEY_ESC;
		map["TOWNS_JISKEY_1"]=TOWNS_JISKEY_1;
		map["TOWNS_JISKEY_2"]=TOWNS_JISKEY_2;
		map["TOWNS_JISKEY_3"]=TOWNS_JISKEY_3;
		map["TOWNS_JISKEY_4"]=TOWNS_JISKEY_4;
		map["TOWNS_JISKEY_5"]=TOWNS_JISKEY_5;
		map["TOWNS_JISKEY_6"]=TOWNS_JISKEY_6;
		map["TOWNS_JISKEY_7"]=TOWNS_JISKEY_7;
		map["TOWNS_JISKEY_8"]=TOWNS_JISKEY_8;
		map["TOWNS_JISKEY_9"]=TOWNS_JISKEY_9;
		map["TOWNS_JISKEY_0"]=TOWNS_JISKEY_0;
		map["TOWNS_JISKEY_MINUS"]=TOWNS_JISKEY_MINUS;
		map["TOWNS_JISKEY_HAT"]=TOWNS_JISKEY_HAT;
		map["TOWNS_JISKEY_BACKSLASH"]=TOWNS_JISKEY_BACKSLASH;
		map["TOWNS_JISKEY_BACKSPACE"]=TOWNS_JISKEY_BACKSPACE;

		map["TOWNS_JISKEY_TAB"]=TOWNS_JISKEY_TAB;
		map["TOWNS_JISKEY_Q"]=TOWNS_JISKEY_Q;
		map["TOWNS_JISKEY_W"]=TOWNS_JISKEY_W;
		map["TOWNS_JISKEY_E"]=TOWNS_JISKEY_E;
		map["TOWNS_JISKEY_R"]=TOWNS_JISKEY_R;
		map["TOWNS_JISKEY_T"]=TOWNS_JISKEY_T;
		map["TOWNS_JISKEY_Y"]=TOWNS_JISKEY_Y;
		map["TOWNS_JISKEY_U"]=TOWNS_JISKEY_U;
		map["TOWNS_JISKEY_I"]=TOWNS_JISKEY_I;
		map["TOWNS_JISKEY_O"]=TOWNS_JISKEY_O;
		map["TOWNS_JISKEY_P"]=TOWNS_JISKEY_P;
		map["TOWNS_JISKEY_AT"]=TOWNS_JISKEY_AT;
		map["TOWNS_JISKEY_LEFT_SQ_BRACKET"]=TOWNS_JISKEY_LEFT_SQ_BRACKET;
		map["TOWNS_JISKEY_RETURN"]=TOWNS_JISKEY_RETURN;

		map["TOWNS_JISKEY_CTRL"]=TOWNS_JISKEY_CTRL;
		map["TOWNS_JISKEY_A"]=TOWNS_JISKEY_A;
		map["TOWNS_JISKEY_S"]=TOWNS_JISKEY_S;
		map["TOWNS_JISKEY_D"]=TOWNS_JISKEY_D;
		map["TOWNS_JISKEY_F"]=TOWNS_JISKEY_F;
		map["TOWNS_JISKEY_G"]=TOWNS_JISKEY_G;
		map["TOWNS_JISKEY_H"]=TOWNS_JISKEY_H;
		map["TOWNS_JISKEY_J"]=TOWNS_JISKEY_J;
		map["TOWNS_JISKEY_K"]=TOWNS_JISKEY_K;
		map["TOWNS_JISKEY_L"]=TOWNS_JISKEY_L;
		map["TOWNS_JISKEY_SEMICOLON"]=TOWNS_JISKEY_SEMICOLON;
		map["TOWNS_JISKEY_COLON"]=TOWNS_JISKEY_COLON;
		map["TOWNS_JISKEY_RIGHT_SQ_BRACKET"]=TOWNS_JISKEY_RIGHT_SQ_BRACKET;

		map["TOWNS_JISKEY_SHIFT"]=TOWNS_JISKEY_SHIFT;
		map["TOWNS_JISKEY_Z"]=TOWNS_JISKEY_Z;
		map["TOWNS_JISKEY_X"]=TOWNS_JISKEY_X;
		map["TOWNS_JISKEY_C"]=TOWNS_JISKEY_C;
		map["TOWNS_JISKEY_V"]=TOWNS_JISKEY_V;
		map["TOWNS_JISKEY_B"]=TOWNS_JISKEY_B;
		map["TOWNS_JISKEY_N"]=TOWNS_JISKEY_N;
		map["TOWNS_JISKEY_M"]=TOWNS_JISKEY_M;
		map["TOWNS_JISKEY_COMMA"]=TOWNS_JISKEY_COMMA;
		map["TOWNS_JISKEY_DOT"]=TOWNS_JISKEY_DOT;
		map["TOWNS_JISKEY_SLASH"]=TOWNS_JISKEY_SLASH;
		map["TOWNS_JISKEY_DOUBLEQUOTE"]=TOWNS_JISKEY_DOUBLEQUOTE;

		map["TOWNS_JISKEY_HIRAGANA"]=TOWNS_JISKEY_HIRAGANA;
		map["TOWNS_JISKEY_CAPS"]=TOWNS_JISKEY_CAPS;
		map["TOWNS_JISKEY_SPACE"]=TOWNS_JISKEY_SPACE;
		map["TOWNS_JISKEY_KANA_KANJI"]=TOWNS_JISKEY_KANA_KANJI;
		map["TOWNS_JISKEY_KATAKANA"]=TOWNS_JISKEY_KATAKANA;
		map["TOWNS_JISKEY_CANCEL"]=TOWNS_JISKEY_CANCEL;
		map["TOWNS_JISKEY_NO_CONVERT"]=TOWNS_JISKEY_NO_CONVERT;
		map["TOWNS_JISKEY_CONVERT"]=TOWNS_JISKEY_CONVERT;

		map["TOWNS_JISKEY_NUM_STAR"]=TOWNS_JISKEY_NUM_STAR;
		map["TOWNS_JISKEY_NUM_SLASH"]=TOWNS_JISKEY_NUM_SLASH;
		map["TOWNS_JISKEY_NUM_PLUS"]=TOWNS_JISKEY_NUM_PLUS;
		map["TOWNS_JISKEY_NUM_MINUS"]=TOWNS_JISKEY_NUM_MINUS;
		map["TOWNS_JISKEY_NUM_7"]=TOWNS_JISKEY_NUM_7;
		map["TOWNS_JISKEY_NUM_8"]=TOWNS_JISKEY_NUM_8;
		map["TOWNS_JISKEY_NUM_9"]=TOWNS_JISKEY_NUM_9;
		map["TOWNS_JISKEY_NUM_EQUAL"]=TOWNS_JISKEY_NUM_EQUAL;
		map["TOWNS_JISKEY_NUM_4"]=TOWNS_JISKEY_NUM_4;
		map["TOWNS_JISKEY_NUM_5"]=TOWNS_JISKEY_NUM_5;
		map["TOWNS_JISKEY_NUM_6"]=TOWNS_JISKEY_NUM_6;
		map["TOWNS_JISKEY_NUM_DOT"]=TOWNS_JISKEY_NUM_DOT;
		map["TOWNS_JISKEY_NUM_1"]=TOWNS_JISKEY_NUM_1;
		map["TOWNS_JISKEY_NUM_2"]=TOWNS_JISKEY_NUM_2;
		map["TOWNS_JISKEY_NUM_3"]=TOWNS_JISKEY_NUM_3;
		map["TOWNS_JISKEY_NUM_RETURN"]=TOWNS_JISKEY_NUM_RETURN;
		map["TOWNS_JISKEY_NUM_0"]=TOWNS_JISKEY_NUM_0;
		map["TOWNS_JISKEY_NUM_000"]=TOWNS_JISKEY_NUM_000;

		map["TOWNS_JISKEY_ALT"]=TOWNS_JISKEY_ALT;
	}
	auto found=map.find(str);
	if(map.end()!=found)
	{
		return found->second;
	}
	return TOWNS_JISKEY_NULL;
}

std::string TownsMemCardTypeToStr(unsigned int memCardType)
{
	switch(memCardType)
	{
	default:
	case TOWNS_MEMCARD_TYPE_NONE:
		return "NONE";
	case TOWNS_MEMCARD_TYPE_OLD:
		return "OLD";
	case TOWNS_MEMCARD_TYPE_JEIDA4:
		return "JEIDA4";
	}

}
