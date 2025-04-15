#include "AssetLib.h"


FSeaAnimationData SeaAnimationData;
FObstacleData TurtleData;
FObstacleData BoxData;

FBatteryData BatteryData;

void InitAsset()
{
	SeaAnimationData.SeaImage[0] = CP_Image_Load("./Assets/Sea.png");


	TurtleData.ObstacleImage = CP_Image_Load("./Assets/Turtle.png");
	TurtleData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	TurtleData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f,20.f);
	TurtleData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	TurtleData.Score = 100.f;

	BoxData.ObstacleImage = CP_Image_Load("./Assets/Box.png");
	BoxData.ObstacleImageSize = CP_Vector_Set(120.f, 30.f);
	BoxData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	BoxData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	BoxData.Score = 50.f;

	BatteryData.BatteryImage = CP_Image_Load("./Assets/Battery.png");
	BatteryData.BatteryImageSize = CP_Vector_Set(30.f, 30.f);
	BatteryData.bIsValid = false;
	BatteryData.Energy = 10.f;
}

