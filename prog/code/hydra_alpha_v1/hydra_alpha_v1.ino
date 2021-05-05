// Author: John-William Lebel, 2021-04-18, creation

#include "projectConfig.h"

// program selection
#ifdef PROGRAMMING_TANK_ALPHA_BOARD
#include "src/tank/tank_alpha_v1.hpp"
#endif

#ifdef PROGRAMMING_ESP_CAM_BOARD
#include "src/cam/espcam_alpha_v1.hpp"
#endif

#ifdef PROGRAMMING_REMOTE_BOARD
#include "src/remote/remote_v1.hpp"
#endif