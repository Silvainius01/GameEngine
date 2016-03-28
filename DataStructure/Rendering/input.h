#pragma once
#include "sfwdraw.h"

#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_H 72
#define KEY_I 73
#define KEY_M 77
#define KEY_O 79
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_W 87
#define KEY_LSHIFT 340
#define KEY_RSHIFT 344
#define KEY_RCTRL 345
#define KEY_LCTRL 341

const int bindIndex = 4;
extern int bindings[bindIndex];

extern bool startDCT;
extern float tmr_DoubleClick;

extern int checkBindings(bool retShf = false, bool carry = false);
extern int checkKeys();
extern int checkMouse(bool doesLeftCarry = true);
