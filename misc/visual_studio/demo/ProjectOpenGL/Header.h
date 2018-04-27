#pragma once

#include <iostream>
#include <stdlib.h>     //for using the function sleep
#include <GL/glut.h>
#include <Box2D/Box2D.h>
//#include <SDL.h>

#include <al.h>
#include <alc.h>

#include <cstdlib>
#include "yse.hpp"
#if defined YSE_WINDOWS
#include <conio.h>
#else
#include "wincompat.h"
#endif