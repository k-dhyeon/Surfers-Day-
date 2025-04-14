#include "AssetLib.h"


CP_Image SeaImage[SEA_IMAGE_NUM];
FObstacleData TurtleData;
FObstacleData BoxData;
void InitAsset()
{
	SeaImage[0] = CP_Image_Load("./Assets/SeaBase.png");


	TurtleData.ObstacleImage = CP_Image_Load("./Assets/Turtle.png");
	TurtleData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	TurtleData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f,20.f);
	TurtleData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);

	BoxData.ObstacleImage = CP_Image_Load("./Assets/Box.png");
	BoxData.ObstacleImageSize = CP_Vector_Set(120.f, 30.f);
	BoxData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	BoxData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
}
