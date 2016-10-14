// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <Windows.h>
#endif

#include <GL/gl.h>

#define GLM_FORCE_RADIANS
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL2/SDL_events.h>

#include <chrono>
#include <type_traits>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <vector>


// TODO: reference additional headers your program requires here
