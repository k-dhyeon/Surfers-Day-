#pragma once

#include "CProcessing.h"
#include "GameStruct.h"


#define OBSTACLE_NUM 10
#define MAX_SEAGULL_NUM 5
extern FSeaAnimationData SeaAnimationData;

extern FFarBackGroundImageAnimationData SkyAnimationData;

extern FFarBackGroundImageAnimationData FarBackgroundAnimationData;

extern FFarBackGroundImageAnimationData SeaGullAnimationData[];

extern FObstacleData TurtleData;
extern FObstacleData BoxData;
extern FObstacleData BallData;
extern FObstacleData DolpinData;
extern FObstacleData CameraData;
extern FObstacleData IcecreamData;
extern FObstacleData StarFishData;
extern FObstacleData TubeData;
extern FObstacleData CrabData;
extern FObstacleData JellyfishData;

extern FBatteryData BatteryData;

void InitAsset();