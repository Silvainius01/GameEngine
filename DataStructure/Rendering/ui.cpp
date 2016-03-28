#include "ui.h"
#include <iostream>
using namespace std;

bool isUnitOnOverlay = false;
bool isBuildOnOverlay = false;
bool isResourceOnOverlay = false;

int overrideMouse = -1;
int entOnOverlay = 0;

float buildGrid[gridY][gridX];
float SCREEN[2] = { 995, 995 };

unsigned ui_Text;
unsigned ui_Human;
unsigned ui_Invader;
unsigned ui_TownCenter;
unsigned ui_Tower;
unsigned ui_Barracks;
unsigned ui_Overlay;
unsigned ui_Mouse;
unsigned ui_Background;
unsigned ui_Hotdog;
unsigned ui_Resource;
unsigned ui_Collector;
unsigned ui_Farm;
unsigned mouseTint = clr_CYAN;

float xSpace(float num, float den) { return (SCREEN[0] / den) * num; }
float ySpace(float num, float den) { return (SCREEN[1] / den) * num; }

void initUI()
{
	ui_Text = loadTextureMap("./source/assets/text.png", 13, 5);
	ui_Human = loadTextureMap("./source/assets/human.png", 2);
	ui_Invader = loadTextureMap("./source/assets/invader.png", 4, 2);
	ui_TownCenter = loadTextureMap("./source/assets/town_center.png", 2, 2);
	ui_Tower = loadTextureMap("./source/assets/Tower.png", 2, 2);
	ui_Barracks = loadTextureMap("./source/assets/barracks.png", 2);
	ui_Overlay = loadTextureMap("./source/assets/overlay.png");
	ui_Background = loadTextureMap("./source/assets/background.png");
	ui_Hotdog = loadTextureMap("./source/assets/hotdog.png", 2);
	ui_Resource = loadTextureMap("./source/assets/resources.png", 1, 2);
	ui_Collector = loadTextureMap("./source/assets/collector.png", 2);
}

void initBuildGrid()
{
	for (int y = 0; y < gridY; y++)
	{
		for (int x = 0; x < gridX; x++)
		{
			buildGrid[y][x] = x;
		}
	}
	
}

char itc(int a)
{
	switch (a)
	{
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	case 0: return '0';
	}
}
char ktc(int index, bool shift)
{
	switch (index)
	{
	case 0:
		if (shift) { return 'A'; }
		return 'a';
	case 1:
		if (shift) { return 'B'; }
		return 'b';
	case 2:
		if (shift) { return 'C'; }
		return 'c';
	case 3:
		if (shift) { return 'D'; }
		return 'd';
	case 4:
		if (shift) { return 'E'; }
		return 'e';
	case 5:
		if (shift) { return 'F'; }
		return 'f';
	case 6:
		if (shift) { return 'G'; }
		return 'g';
	case 7:
		if (shift) { return 'H'; }
		return 'h';
	case 8:
		if (shift) { return 'I'; }
		return 'i';
	case 9:
		if (shift) { return 'J'; }
		return 'j';
	case 10:
		if (shift) { return 'K'; }
		return 'k';
	case 11:
		if (shift) { return 'L'; }
		return 'l';
	case 12:
		if (shift) { return 'M'; }
		return 'm';
	case 13:
		if (shift) { return 'N'; }
		return 'n';
	case 14:
		if (shift) { return 'O'; }
		return 'o';
	case 15:
		if (shift) { return 'P'; }
		return 'p';
	case 16:
		if (shift) { return 'Q'; }
		return 'q';
	case 17:
		if (shift) { return 'R'; }
		return 'r';
	case 18:
		if (shift) { return 'S'; }
		return 's';
	case 19:
		if (shift) { return 'T'; }
		return 't';
	case 20:
		if (shift) { return 'U'; }
		return 'u';
	case 21:
		if (shift) { return 'V'; }
		return 'v';
	case 22:
		if (shift) { return 'W'; }
		return 'w';
	case 23:
		if (shift) { return 'X'; }
		return 'x';
	case 24:
		if (shift) { return 'Y'; }
		return 'y';
	case 25:
		if (shift) { return 'Z'; }
		return 'z';
	case 26:return '0';
	case 27:return '1';
	case 28:return '2';
	case 29:return '3';
	case 30:return '4';
	case 31:return '5';
	case 32:return '6';
	case 33:return '7';
	case 34:return '8';
	case 35:return '9';
	case 47:return ' ';
	default: return '\0';
	}
}
int cti(char a)
{
	switch (a)
	{
	case 'A': return 0;
	case 'B': return 1;
	case 'C': return 2;
	case 'D': return 3;
	case 'E': return 4;
	case 'F': return 5;
	case 'G': return 6;
	case 'H': return 7;
	case 'I': return 8;
	case 'J': return 9;
	case 'K': return 10;
	case 'L': return 11;
	case 'M': return 12;
	case 'N': return 13;
	case 'O': return 14;
	case 'P': return 15;
	case 'Q': return 16;
	case 'R': return 17;
	case 'S': return 18;
	case 'T': return 19;
	case 'U': return 20;
	case 'V': return 21;
	case 'W': return 22;
	case 'X': return 23;
	case 'Y': return 24;
	case 'Z': return 25;
	case 'a': return 26;
	case 'b': return 27;
	case 'c': return 28;
	case 'd': return 29;
	case 'e': return 30;
	case 'f': return 31;
	case 'g': return 32;
	case 'h': return 33;
	case 'i': return 34;
	case 'j': return 35;
	case 'k': return 36;
	case 'l': return 37;
	case 'm': return 38;
	case 'n': return 39;
	case 'o': return 40; 
	case 'p': return 41;  
	case 'q': return 42;
	case 'r': return 43;
	case 's': return 44;
	case 't': return 45;
	case 'u': return 46;
	case 'v': return 47;
	case 'w': return 48; 
	case 'x': return 49; 
	case 'y': return 50; 
	case 'z': return 51;
	case '1': return 52;
	case '2': return 53;
	case '3': return 54;
	case '4': return 55;
	case '5': return 56;
	case '6': return 57;
	case '7': return 58;
	case '8': return 59;
	case '9': return 60;
	case '0': return 61;
	case ':': return 62;
	case '\n': return -2;
	default: return -1;
	}
}
float centerLine(const char *string, int startIndex, float x, float spc)
{
	int sltc = 1;

	for (int a = startIndex; string[a] != '\n' && string[a] != '\0'; a++)
	{
		sltc = a - startIndex + 1;
	}

	if (startIndex != 0) { spc += 1; }

	sltc *= spc;
	return sltc / 2;
}
float leftLine(const char *string, int startIndex, float x, float spc)
{
	int sltl;

	for (int a = startIndex; string[a] != '/n' && string[a] != '/0'; a++)
	{
		sltl = a - startIndex;
	}

	sltl *= spc;

	return x - sltl;
}
void drawText(const char *string, float x, float y, const int multH, const int multW, bool drawUp, TextAlign ta, unsigned tint)
{
	int CTI;
	int lineCount = -1;
	float spc = (9 * multW);
	float xKeep = x;
	for (int a = 0; a < strlen(string); a++)
	{
		CTI = cti(string[a]);
		if (a != 0) { x += spc; }
		if (CTI == -1) { continue; }
		else if (CTI == -2 || a == 0)
		{
			int index = a;
			int redux;
			lineCount++;
			if (a != 0) { index = a + 1; }
			switch (ta)
			{
			case CENTER:
				redux = centerLine(string, index, xKeep, spc);
				break;
			case RIGHT:
				redux = 0;
				break;
			case LEFT:
				redux = leftLine(string, index, xKeep, spc);
				break;
			}

			x = xKeep - redux - (spc * lineCount);

			if (a != 0)
			{
				if (drawUp) { y += (9 * multH) + ySpace(1); continue; }
				else { y -= (9 * multH) + ySpace(1); continue; }
			}
		}

		drawTexture(ui_Text, x, y, 9 * multW, 9 * multH, 0, false, CTI, tint);
	}
}

void drawBox(float x, float y, float h, float w, unsigned tint)
{
	drawLine(x, y, x + w, y, tint);
	drawLine(x, y, x, y + h, tint);
	drawLine(x + w, y, x + w, y + h, tint);
	drawLine(x, y + h, x + w, y + h, tint);
}

void drawMouse(unsigned sprite, int index, float h, float w, float multH, float multW)
{
	drawTexture(sprite, getMouseX(), getMouseY(), w * multW, h * multH, 0, true, index, mouseTint); 
}

/*******************************************************************\
* IMPORTTANT NOTE:                                                *
*                                                                 *
*  This function was desined to print at a 3:1 h/w ratio!         *
*  While it CAN print other ratios, they might not look as good!  *
*  Also: It draws from the TOP-LEFT corner!                       *
\*******************************************************************/
void sfw::drawChar(char a, float x, float y, float h, float w)
{
	switch (a)
	{
	case 'A':
		drawLine(x, y + h, x + (w / 2), y); //Left Diag
		drawLine(x + w, y + h, x + (w / 2), y); //Right diag
		drawLine(x + (w / 4), y + (h / 2), x + ((w / 4) * 3), y + (h / 2)); //Center Line
		break;
	case 'B':
		drawLine(x, y, x, y + h); //spine
		drawLine(x, y, x + (w / 4), y); //Top-Top flat
		drawLine(x + (w / 4), y, x + w, y + (h / 6)); //Top-Top Diag
		drawLine(x + w, y + (h / 6), x + w, y + ((h / 6) * 2)); //Top-Left flat
		drawLine(x + w, y + ((h / 6) * 2), x + (w / 4), y + ((h / 6) * 3));//Top-Bot diag
		drawLine(x, y + (h / 2), x + (w / 4), y + (h / 2)); //Mid Flat
		drawLine(x + (w / 4), y + ((h / 6) * 3), x + w, y + ((h / 6) * 4)); //Bot-Top diag
		drawLine(x + w, y + ((h / 6) * 4), x + w, y + ((h / 6) * 5)); //Bot-Left flat
		drawLine(x + w, y + ((h / 6) * 5), x + (w / 4), y + ((h / 6) * 6)); //Bot-Bot diag
		drawLine(x, y + h, x + (w / 4), y + h); //Bot-Bot flat
		break;
	case 'C':
		drawLine(x + w, y, x + ((w / 3) * 2), y); // 2/3 -> 1/3 //Top flat
		drawLine(x, y + (h / 3), x + ((w / 3) * 2), y); //top-spine connector
		drawLine(x, y + (h / 3), x, y + ((h / 3) * 2)); //Spine
		drawLine(x, y + ((h / 3) * 2), x + ((w / 3) * 2), y + h); //spine-bot connector
		drawLine(x + ((w / 3) * 2), y + h, x + w, y + h); //Bot flat
		break;
	case 'D':
		drawLine(x, y, x, y + h); //spine
		drawLine(x, y, x + (w / 4), y); //Top flat
		drawLine(x + (w / 4), y, x + w, y + ((h / 7) * 2)); //Top-Sode connector
		drawLine(x + w, y + ((h / 7) * 2), x + w, y + ((h / 7) * 5)); //right side
		drawLine(x + w, y + ((h / 7) * 5), x + (w / 4), y + h); //bot- Side connector
		drawLine(x, y + h, x + (w / 4), y + h); //bot flat
		break;
	case 'E':
		drawLine(x, y, x + w, y); //Top flat
		drawLine(x, y, x, y + h - 1); //Spine
		drawLine(x, y + (h / 2), x + (w / 2), y + (h / 2)); //Mid flat
		drawLine(x, y + h - 1, x + w, y + h - 1); //bot flat
		break;
	case 'F':
		drawLine(x, y, x + w, y); //Top flat
		drawLine(x, y, x, y + h); //spine
		drawLine(x, y + (h / 2), x + ((w / 3) * 2), y + (h / 2)); //Mid Flat
		break;
	case 'G': //Note to self: ,ake it fancier
		drawLine(x, y, x + w, y); //top flat
		drawLine(x, y, x, y + h); //Spine
		drawLine(x, y + h - 1, x + w, y + h - 1); //bot flat
		drawLine(x + w, y + h - 1, x + w, y + (h / 2)); //right side
		drawLine(x + w, y + (h / 2), x + (w / 2), y + (h / 2)); //Center "G-line"
		break;
	case 'H':
		drawLine(x, y, x, y + h); //Left side
		drawLine(x + w, y, x + w, y + h); //Right side
		drawLine(x, y + (h / 2), x + w, y + (h / 2)); //Center flat
		break;
	case 'I':
		drawLine(x, y, x + w, y); //Top flat
		drawLine(x + (w / 2), y, x + (w / 2), y + h); //Spine
		drawLine(x, y + h, x + w, y + h); //bot flat
		break;
	case 'J':
		drawLine(x + w, y, x + w, y + ((h / 4) * 3)); //Spine
		drawLine(x + w, y + ((h / 4) * 3), x + ((w / 3) * 2), y + h); //spine-bot connecotr
		drawLine(x + ((w / 3) * 2), y + h, x + (w / 3), y + h); //Bot flat
		drawLine(x, y + ((h / 4) * 3), x + (w / 3), y + h); //Hook
		break;
	case 'K':
		drawLine(x, y, x, y + h); //Spine
		drawLine(x, y + (h / 2), x + w, y); //Top diag
		drawLine(x, y + (h / 2), x + w, y + h); //Bot diag
		break;
	case 'L':
		drawLine(x, y, x, y + h); //Spine
		drawLine(x, y + h - 1, x + w, y + h - 1); //bot Flat
		break;
	case 'M':
		drawLine(x, y, x, y + h); //Left side
		drawLine(x + w, y, x + w, y + h); //Left-Mid diag
		drawLine(x, y, x + (w / 2), y + (h / 2));//Right-Mid Diag
		drawLine(x + (w / 2), y + (h / 2), x + w, y); //Right side
		break;
	case 'N':
		drawLine(x, y, x, y + h); //Left side
		drawLine(x + w, y, x + w, y + h);//Left-Right diag
		drawLine(x, y, x + w, y + h);//Right diag
		break;
	case 'O':
		drawLine(x + (w / 3) + 1, y, x + ((w / 3) * 2), y); //Top flat
		drawLine(x, y + (h / 3), x, y + ((h / 3) * 2)); //Left flat
		drawLine(x + w, y + (h / 3), x + w, y + ((h / 3) * 2)); //right flat
		drawLine(x + (w / 3), y + h, x + ((w / 3) * 2), y + h); // bot flat
		drawLine(x + (w / 3), y + 1, x, y + (h / 3)); //T-L connector
		drawLine(x, y + ((h / 3) * 2), x + (w / 3), y + h); //L-B Connector
		drawLine(x + ((w / 3) * 2), y + 1, x + w, y + (h / 3)); //T-R Connector
		drawLine(x + w, y + ((h / 3) * 2), x + ((w / 3) * 2), y + h); //R-B Connector
		break;
	case 'P': //Note to self: make it fancier
		drawLine(x, y, x, y + h); //Spine
		drawLine(x, y, x + w, y); //top flat
		drawLine(x + w, y, x + w, y + (h / 3)); //right side
		drawLine(x + w, y + (h / 3), x, y + (h / 3)); //Mid flat
		break;
	case 'Q':
		drawChar('O', x, y, h, w);//lel
		drawLine(x + (w / 2), y + ((h / 3) * 2), x + w, y + h); //Slicer diag
		break;
	case 'R':
		drawChar('P', x, y, h, w); //lel
		drawLine(x + ((w / 3) * 2), y + (h / 3), x + w, y + h); //Mid-Bot diag
		break;
	case 'S':
		drawLine(x + (w / 3), y, x + w, y); //Top flat
		drawLine(x + (w / 3), y, x, y + (h / 4)); //T-L connector
		drawLine(x, y + (h / 4), x, y + (h / 3)); //Left side
		drawLine(x, y + (h / 3), x + (w / 3), y + (h / 2) + 1); //L-M Connector
		drawLine(x + (w / 3), y + (h / 2), x + ((w / 3) * 2), y + (h / 2)); //mid flat
		drawLine(x + ((w / 3) * 2), y + (h / 2), x + w, y + ((h / 4) * 3) - 1); //M-R Connector
		drawLine(x + w, y + ((h / 4) * 3), x + w, y + ((h / 3) * 2)); //Right side
		drawLine(x + w, y + ((h / 4) * 3), x + ((w / 3) * 2), y + h); //R-B Connector
		drawLine(x + ((w / 3) * 2), y + h, x, y + h); //Bot flat
		break;
	case 'T':
		drawLine(x, y, x + w, y); //Top flat
		drawLine(x + (w / 2), y, x + (w / 2), y + h); //Spine
		break;
	case 'U':
		drawLine(x, y, x, y + ((h / 3) * 2)); //left side
		drawLine(x, y + ((h / 3) * 2), x + (w / 3) - 1, y + h); //L-B Connector
		drawLine(x + (w / 3), y + h, x + ((w / 3) * 2) + 1, y + h); //Bot flat
		drawLine(x + w, y + ((h / 3) * 2), x + ((w / 3) * 2) + 1, y + h);//R-B connector
		drawLine(x + w, y, x + w, y + ((h / 3) * 2)); //Right side
		break;
	case 'V':
		drawLine(x, y, x + (w / 2), y + h);//Left diag
		drawLine(x + w, y, x + (w / 2), y + h); //Right Diag
		break;
	case 'W':
		drawLine(x, y, x, y + h);//Left side
		drawLine(x, y + h, x + (w / 2), y + (h / 2)); //left diag
		drawLine(x + w, y + h, x + (w / 2), y + (h / 2));//Right diag
		drawLine(x + w, y, x + w, y + h);//Right side
		break;
	case 'X':
		drawLine(x, y, x + w, y + h); //Left diag
		drawLine(x + w, y, x, y + h); //Right diag
		break;
	case 'Y':
		drawLine(x, y, x + (w / 2), y + (h / 2));//Left diag
		drawLine(x + w, y, x + (w / 2), y + (h / 2));//Right diag
		drawLine(x + (w / 2), y + (h / 2), x + (w / 2), y + h); //Spine
		break;
	case 'Z':
		drawLine(x, y, x + w, y);//Top flat
		drawLine(x + w, y, x, y + h);//Diag
		drawLine(x, y + h - 1, x + w, y + h - 1);//bot flat
		break;
	case '0':
		drawChar('O', x, y, h, w); //Lel
		drawLine(x + w, y + (h / 3), x, y + ((h / 3) * 2)); //Diag
		break;
	case '1':
		drawLine(x + (w / 2), y, x + (w / 2), y + h); //Spine
		drawLine(x + (w / 5), y + h, x + ((w / 5) * 4), y + h); //Bot flat
		drawLine(x + (w / 2), y, x + (w / 6), y + (w / 4)); //Diag tip
		break;
	case '2':
		drawLine(x, y + (h / 5), x + ((w / 5) * 2), y);//Left-Top diag
		drawLine(x + ((w / 5) * 2), y, x + ((w / 5) * 4), y); //Top flat
		drawLine(x + ((w / 5) * 4), y, x + w, y + (h / 5)); //Right flat
		drawLine(x + w, y + (h / 5), x, y + h); //Right-Bot diag
		drawLine(x, y + h, x + w, y + h);//Bot flat
		break;
	case '3':
		drawLine(x, y, x + ((w / 5) * 3), y);//Top Flat
		drawLine(x + ((w / 5) * 3), y, x + w, y + (h / 4)); //Top-down diag 1
		drawLine(x + w, y + (h / 4), x + ((w / 5) * 2), y + (h / 2)); //Top-Down diag 2
		drawLine(x + ((w / 5) * 2), y + (h / 2), x + w, y + ((h / 4) * 3)); //Top-Down diag 3
		drawLine(x + w, y + ((h / 4) * 3), x + ((w / 5) * 3), y + h); //Top-Down 3 diag
		drawLine(x, y + h, x + ((w / 5) * 3), y + h);
		break;
	case '4':
		drawLine(x, y + (h / 2), x + w, y + (h / 2));//Middle flat
		drawLine(x, y + (h / 2), x + ((w / 5) * 4), y); //Mid-Top diag
		drawLine(x + ((w / 5) * 4), y, x + ((w / 5) * 4), y + h);//Spine
		break;
	case '5':
		drawLine(x, y, x + w, y); //top flat
		drawLine(x, y, x, y + (h / 2));//Left side;
		drawLine(x, y + (h / 2), x + w, y + (h / 2));//Mid flat
		drawLine(x + w, y + (h / 2), x + w, y + ((h / 5) * 3));//Right side;
		drawLine(x + w, y + ((h / 5) * 4), x + ((w / 3) * 2), y + h);//Right-Bot diag
		drawLine(x + ((w / 3) * 2), y + h, x + (w / 3), y + h);//Bot flat
		drawLine(x + w, y + ((h / 5) * 3), x + w, y + ((h / 5) * 4));
		drawLine(x + (w / 3), y + h, x, y + ((h / 5) * 4));//Bot-Left diag
		break;
	case '6':
		drawChar('O', x, y + ((h / 3)), ((h / 3) * 2), w); //Lel
		drawLine(x + (w / 3) + 1, y + ((h / 3)), x + w, y);//Top diag
		break;
	case '7':
		drawLine(x, y, x + w, y);//Top flat
		drawLine(x + w, y, x + (w / 3), y + h);//Diag
		break;
	case '8':
		drawChar('O', x, y + ((h / 2)), (h / 2), w); //Lel
		drawChar('O', x, y, (h / 2), w); //Double Lel
		break;
	case '9':
		drawChar('O', x, y, ((h / 3) * 2), w); //Lel
		drawLine(x + ((w / 3) * 2), y + ((h / 3) * 2), x + (w / 4), y + h); //Diag
		break;
	case '(':
		drawLine(x + (w / 2), y, x, y + (h / 3)); //Mid-Left diag
		drawLine(x, y + (h / 3), x, y + ((h / 3) * 2)); //left side
		drawLine(x, y + ((h / 3) * 2), x + (w / 2), y + h); //Mid-Right diag
		break;
	case ')':
		drawLine(x + (w / 2), y, x + w, y + (h / 3)); //Mid-Left diag
		drawLine(x + w, y + (h / 3), x + w, y + ((h / 3) * 2)); //left side
		drawLine(x + w, y + ((h / 3) * 2), x + (w / 2), y + h); //Mid-Right diag
		break;
	case '-':
		drawLine(x + (w / 4), y + ((h / 7) * 3), x + ((w / 4) * 3), y + ((h / 7) * 3)); //Top
		drawLine(x + (w / 4), y + ((h / 7) * 3), x + (w / 4), y + ((h / 7) * 4)); //Left
		drawLine(x + ((w / 4) * 3), y + ((h / 7) * 3), x + ((w / 4) * 3), y + ((h / 7) * 4)); //Right
		drawLine(x + (w / 4), y + ((h / 7) * 4), x + ((w / 4) * 3), y + ((h / 7) * 4)); //Bot
		break;
	case '#':
		drawBox(x, y, h, w);
		break;
	case '?':
		drawLine(x, y, x + (w / 2), y + (h / 3)); //Diag
		drawLine(x + (w / 2), y + (h / 3), x + (w / 2), y + (h / 2)); //Spine
		drawLine(x + (w / 2), y + (h / 2), x + (w / 4), y + ((h / 3) * 2)); //Diag 2
		drawLine(x + (w / 4), y + ((h / 3) * 2), x + (w / 4), y + ((h / 5) * 4));//straight
		drawLine(x + (w / 5), y + ((h / 10) * 9), x + (w / 5), y + h); //Left
		drawLine(x + ((w / 5) * 2.5), y + ((h / 10) * 9), x + ((w / 5) * 2.5), y + h); //Right
		drawLine(x + (w / 5), y + ((h / 10) * 9), x + ((w / 5) * 2.5), y + ((h / 10) * 9)); //Top
		drawLine(x + ((w / 5) * 2.5), y + h, x + (w / 5), y + h); //Bot
		break;
	case ':':
		drawChar('O', x + (w / 3), y, h / 3, w / 3); //Lel
		drawChar('O', x + (w / 3), y + ((h / 3) * 2), h / 3, w / 3); //Double lel
		break;
	case '\'':
		drawLine(x + (w / 3), y, x + ((w / 3) * 2), y);
		drawLine(x + ((w / 3) * 2), y, x, y + (h / 4));
		drawLine(x + (w / 3), y, x, y + (h / 4));
		break;
	case '\\':
		drawLine(x, y, x + w, y + h);
		break;
	case '/':
		drawLine(x + w, y, x, y + h);
		break;
	case '.':
		drawBox(x + (w / 3), y + ((h / 5) * 4), h / 5, w / 3);
		break;
	case ',':
		drawChar('\'', x, y + ((h / 4) * 3), h, w);
		break;
	case ';':
		drawChar('O', x + (w / 3), y, h / 3, w / 3); //Lel
		drawChar('\'', x, y + ((h / 4) * 3), h, w);
		break;
	case ']':
		drawLine(x + (w / 2), y, x + w, y);
		drawLine(x + w, y, x + w, y + h);
		drawLine(x + w, y + h, x + (w / 2), y + h);
		break;
	case '[':
		drawLine(x + (w / 2), y, x, y);
		drawLine(x, y, x, y + h);
		drawLine(x, y + h, x + (w / 2), y + h);
		break;
	case '=':
		drawBox(x, y + (h / 5), (h / 5), w);
		drawBox(x, y + ((h / 5) * 3), (h / 5), w);
		break;
	case '`':
		drawLine(x + (w / 4), y, x + ((w / 4) * 3), y);
		drawLine(x + ((w / 4) * 3), y, x + ((w / 5) * 4), y + (h / 3));
		drawLine(x + (w / 4), y, x + ((w / 5) * 4), y + (h / 3));
		break;
	default: //Any unrecognized character or space print a blank, well, space.
		break;
	}
}

/************************************************************************\
* Sends an array of chars to drawChar().                               *
* spcX is how far apart the chars are drawn inaddition to their width. *
\************************************************************************/
void sfw::drawStringHor(char text[], float x, float y, float h, float w, float spcX)
{
	float spc = spcX;

	for (int i = 0; text[i] != '\0'; ++i)
	{
		if (!i) { spcX = 0; }
		else { spcX += spc + w; }
		drawChar(text[i], x + spcX, y, h, w);
	}
}
/*************************************************************************\
* Sends an array of chars to drawChar().                                *
* spcX is how far apart the chars are drawn inaddition to their height. *
\*************************************************************************/
void sfw::drawStringVer(char text[], float x, float y, float h, float w, float spcY)
{
	float spc = spcY;

	for (int i = 0; text[i] != '\0'; ++i)
	{
		if (!i) { spcY = 0; }
		else { spcY += spc + h; }
		drawChar(text[i], x, y + spcY, h, w);
	}
}

void sfw::graphPoly(int terms, float coef[], float length, float X, float Y, bool lengthIsHeight, bool useNegativeX)
{
	//ax^n + bx^n-1 + ... + c
	float carry = 0;
	float temp;
	float fTemp;
	float xKeep = X;
	float yVal = 0;
	float prevY = Y;
	float prevX = X;
	X = 0;
	if (terms < 1) { terms = 1; }

	for (int a = 0; a < length; a++)
	{
		if (useNegativeX) { X = -X; }

		if (terms == 1)
		{
			yVal = coef[0] + Y;
		}
		else if (terms == 2)
		{
			yVal = (X * coef[1]) + coef[0] + Y;
		}
		else
		{
			carry = 0;
			for (int b = terms; b != 2; b--)
			{
				if (coef[b - 1] != 0)
				{
					fTemp = X;
					for (int c = 0; c < b - 2; c++) { fTemp *= X; }
					fTemp *= coef[b - 1];
					carry += fTemp;
				}
			}
			temp = (X * coef[1]) + coef[0] + Y;
			yVal = carry + temp;
		}

		X += xKeep;


		drawLine(X, yVal, X - 1, yVal - 1);
		if (lengthIsHeight)
		{
			if (yVal >= length + Y) { drawLine(X, yVal, X + 1, length + Y); a = length; }
			else if (yVal <= -length + Y) { drawLine(X, yVal, X + 1, -length + Y); a = length; }
		}
		drawLine(prevX, prevY, X, yVal);
		prevX = X;

		prevY = yVal;
		X -= xKeep;
		X = abs(X) + 1;
	}
}