#include "AssetLib.h"
#include "BGM.h"

FSeaAnimationData SeaAnimationData;

FObstacleData TurtleData;
FObstacleData BoxData;
FObstacleData BallData;
FObstacleData DolpinData;
FObstacleData CameraData;
FObstacleData IcecreamData;
FObstacleData StarFishData;
FObstacleData TubeData;
FObstacleData CrabData;
FObstacleData JellyfishData;


FBatteryData BatteryData;

void InitAsset()
{
	InGameBGM = CP_Sound_LoadMusic("./Assets/Ikoliks - Ride the Wave.mp3");
	MainMenuBGM = CP_Sound_LoadMusic("./Assets/Raz Burg - Sunlight - Instrumental Version.mp3");
	
	SFXBatteryRecharge = CP_Sound_Load("./Assets/GetBatterySFX.mp3");
	SFXJump = CP_Sound_Load("./Assets/JumpSFX.mp3");
	SFXCollision = CP_Sound_Load("./Assets/Collision.mp3");
	SFXCombo = CP_Sound_Load("./Assets/ComboSFX.mp3");

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
	//TODO : Image Size and collision size tune needed
	BallData.ObstacleImage = CP_Image_Load("./Assets/Ball.png");
	BallData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	BallData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	BallData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	BallData.Score = 50.f;

	DolpinData.ObstacleImage = CP_Image_Load("./Assets/Dolpin.png");
	DolpinData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	DolpinData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	DolpinData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	DolpinData.Score = 50.f;

	CameraData.ObstacleImage = CP_Image_Load("./Assets/Camera.png");
	CameraData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	CameraData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	CameraData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	CameraData.Score = 50.f;

	IcecreamData.ObstacleImage = CP_Image_Load("./Assets/Icecream.png");
	IcecreamData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	IcecreamData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	IcecreamData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	IcecreamData.Score = 50.f;

	StarFishData.ObstacleImage = CP_Image_Load("./Assets/StarFish.png");
	StarFishData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	StarFishData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	StarFishData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	StarFishData.Score = 50.f;

	TubeData.ObstacleImage = CP_Image_Load("./Assets/Tube.png");
	TubeData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	TubeData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	TubeData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	TubeData.Score = 50.f;

	CrabData.ObstacleImage = CP_Image_Load("./Assets/Crab.png");
	CrabData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	CrabData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	CrabData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	CrabData.Score = 50.f;

	JellyfishData.ObstacleImage = CP_Image_Load("./Assets/Jellyfish.png");
	JellyfishData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	JellyfishData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 20.f);
	JellyfishData.ObstacleCollisionSize = CP_Vector_Set(100.f, 10.f);
	JellyfishData.Score = 50.f;

	BatteryData.BatteryImage = CP_Image_Load("./Assets/Battery.png");
	BatteryData.BatteryImageSize = CP_Vector_Set(30.f, 30.f);
	BatteryData.bIsValid = false;
	BatteryData.Energy = 10.f;
}

