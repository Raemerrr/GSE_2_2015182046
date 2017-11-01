#pragma once

#include "targetver.h"
#include "Windows.h"

#include <stdio.h>
#include <tchar.h>
#include <random>
#include <ctime>
#include <iostream>

#define MAX_OBJECTS_SIZE 10
#define MAX_OBJECTS_COUNT 10
#define MAX_BUILDING_COUNT 1
#define MAX_BUILDING_SIZE 30

enum OBJECT { OBJECT_CHARACTER = 1, OBJECT_BUILDING, OBJECT_BULLET, OBJECT_ARROW };


//srand((unsigned)time(NULL));

