#pragma once

#include "targetver.h"
#include "Windows.h"

#include <stdio.h>
#include <tchar.h>
#include <random>
#include <ctime>
#include <iostream>

#define MAX_SCREEN_WIDTH 500
#define MAX_SCEEN_HEIGHT 800

#define MAX_OBJECTS_COUNT 10
#define MAX_OBJECTS_SIZE 30
#define MAX_OBJECTS_LIFE 100

#define MAX_BUILDING_COUNT 6
#define MAX_BUILDING_SIZE 100
#define MAX_BUILDING_LIFE 500

#define MAX_BULLET_COUNT (MAX_BUILDING_COUNT*100)
#define MAX_BULLET_SIZE 4
#define MAX_BULLET_LIFE 15

#define MAX_ARROW_COUNT (MAX_OBJECTS_COUNT*100)
#define MAX_ARROW_SIZE 4
#define MAX_ARROW_LIFE 10

#define LEVEL_GOD 0			//ºôµù
#define LEVEL_SKY 0.1		//Ä³¸¯ÅÍ
#define LEVEL_GROUND 0.2	//¿¡·Î¿ì, ºÒ·¿
#define LEVEL_UNDERGROUND 0.3


enum OBJECT { OBJECT_CHARACTER = 1, OBJECT_BUILDING, OBJECT_BULLET, OBJECT_ARROW };
//enum SettingNum { SET_POSITION = 1, SET_SETRGB, SET_DIREC, SET_LIFE, SET_LIFETIME, SET_FIXEDLIFE, SET_TEAMNUM };


//srand((unsigned)time(NULL));

