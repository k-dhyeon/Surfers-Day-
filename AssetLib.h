#pragma once

#include "CProcessing.h"
#include "GameStruct.h"


#define OBSTACLE_NUM 13
#define MAX_SEAGULL_NUM 5
extern FSeaAnimationData SeaAnimationData;

extern FFarBackGroundImageAnimationData SkyAnimationData;

extern FFarBackGroundImageAnimationData FarBackgroundAnimationData;
FFarBackGroundImageAnimationData NearBackgroundAnimationData;

extern FFarBackGroundImageAnimationData SeaGullAnimationData[];

extern FObstacleData TurtleData;
extern FObstacleData BoxData;
extern FObstacleData BallData;
extern FObstacleData DolphinData;
extern FObstacleData CameraData;
extern FObstacleData IcecreamData;
extern FObstacleData StarFishData;
extern FObstacleData TubeData;
extern FObstacleData CrabData;
extern FObstacleData JellyfishData;
extern FObstacleData SharkData;
extern FObstacleData ReefData;
extern FObstacleData DrumData;

extern FBatteryData BatteryData;

extern CP_Image WaveTop;

extern CP_Image LowBattery;
extern CP_Image HalfBattery;
extern CP_Image HighBattery;
extern CP_Image MaxBattery;

extern CP_Image DroneImage;
extern CP_Image Sand;
extern CP_Image Bridge;

void InitAsset();