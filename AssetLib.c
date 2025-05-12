#include "AssetLib.h"
#include "BGM.h"
#include "GlobalVariables.h"


FSeaAnimationData SeaAnimationData;

FFarBackGroundImageAnimationData SkyAnimationData;

FFarBackGroundImageAnimationData FarBackgroundAnimationData;
FFarBackGroundImageAnimationData NearBackgroundAnimationData;

FFarBackGroundImageAnimationData SeaGullAnimationData[MAX_SEAGULL_NUM];

FObstacleData TurtleData;
FObstacleData BoxData;
FObstacleData BallData;
FObstacleData DolphinData;
FObstacleData CameraData;
FObstacleData IcecreamData;
FObstacleData StarFishData;
FObstacleData TubeData;
FObstacleData CrabData;
FObstacleData JellyfishData;
FObstacleData SharkData;
FObstacleData ReefData;
FObstacleData DrumData;
FObstacleData WhaleData;

FBatteryData BatteryData;

CP_Image WaveTop;

CP_Image LowBattery;
CP_Image HalfBattery;
CP_Image HighBattery;
CP_Image MaxBattery;

CP_Image DroneImage;

CP_Image Sand;
CP_Image Bridge;

CP_Image ScoreBoardBackground;
CP_Image ScoreBoardInGame;

void InitAsset()
{
	InGameBGM = CP_Sound_LoadMusic("./Assets/game_to_dance.mp3");
	MainMenuBGM = CP_Sound_LoadMusic("./Assets/Raz Burg - Sunlight - Instrumental Version.mp3");
	
	SFXBatteryRecharge = CP_Sound_Load("./Assets/GetBatterySFX.mp3");
	SFXJump = CP_Sound_Load("./Assets/JumpSFX.mp3");
	SFXCollision = CP_Sound_Load("./Assets/CollisionSFX.mp3");
	SFXCombo = CP_Sound_Load("./Assets/ComboSFX.mp3");
	SFXGameOver = CP_Sound_Load("./Assets/GameOver.mp3");
	SFXMedal = CP_Sound_Load("./Assets/MedalSFX.mp3");

	SeaAnimationData.SeaImage = CP_Image_Load("./Assets/Sea.png");

	SkyAnimationData.Image = CP_Image_Load("./Assets/Sky.png");
	SkyAnimationData.Position = CP_Vector_Set(0.f, 0.f);

	FarBackgroundAnimationData.Image = CP_Image_Load("./Assets/LandScape.png");
	FarBackgroundAnimationData.Position = CP_Vector_Set(0.f/*(float)CP_System_GetWindowWidth()*/, GameData.LaneMin.y - (float)CP_Image_GetHeight(FarBackgroundAnimationData.Image));

	NearBackgroundAnimationData.Image = CP_Image_Load("./Assets/BreakWater.png");
	NearBackgroundAnimationData.Position = CP_Vector_Set(0.f, GameData.LaneMax.y);

	WaveTop = CP_Image_Load("./Assets/BreakingWave.png");

	for (int i = 0;i < MAX_SEAGULL_NUM; i++)
	{
		SeaGullAnimationData[i].Image = CP_Image_Load("./Assets/SeaGull.png");
		SeaGullAnimationData[i].Timer = CP_Random_RangeFloat(0.f,2.f);
		SeaGullAnimationData[i].Index = CP_Random_RangeInt(0,1);
		SeaGullAnimationData[i].Position.x = CP_Random_RangeFloat((float)CP_System_GetWindowWidth(), CP_System_GetWindowWidth() + 1600.f);
		SeaGullAnimationData[i].Position.y = CP_Random_RangeFloat(100.f, CP_System_GetWindowHeight() / 2.f - 150.f);
		SeaGullAnimationData[i].PlayRatio = CP_Random_RangeFloat(0.4f, 2.f);
	}
	Sand = CP_Image_Load("./Assets/BreakWater.png");
	Bridge = CP_Image_Load("./Assets/Bridge.png");

	TurtleData.ObstacleImage = CP_Image_Load("./Assets/Turtle.png");
	TurtleData.ObstacleImageSize = CP_Vector_Set(100.f, 50.f);
	TurtleData.ObstacleCollisionStartOffset = CP_Vector_Set(20.f,20.f);
	TurtleData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	TurtleData.Score = 50.f;

	BoxData.ObstacleImage = CP_Image_Load("./Assets/Box.png");
	BoxData.ObstacleImageSize = CP_Vector_Set(120.f, 30.f);
	BoxData.ObstacleCollisionStartOffset = CP_Vector_Set(15.f, 20.f);
	BoxData.ObstacleCollisionSize = CP_Vector_Set(80.f, 10.f);
	BoxData.Score = 100.f;

	//TODO : Image Size and collision size tune needed
	BallData.ObstacleImage = CP_Image_Load("./Assets/Ball.png");
	BallData.ObstacleImageSize = CP_Vector_Set(100.f, 50.f);
	BallData.ObstacleCollisionStartOffset = CP_Vector_Set(40.f, 20.f);
	BallData.ObstacleCollisionSize = CP_Vector_Set(15.f, 30.f);
	BallData.Score = 80.f;

	DolphinData.ObstacleImage = CP_Image_Load("./Assets/Dolphin.png");
	DolphinData.ObstacleImageSize = CP_Vector_Set(200.f, 120.f);
	DolphinData.ObstacleCollisionStartOffset = CP_Vector_Set(30.f, 50.f);
	DolphinData.ObstacleCollisionSize = CP_Vector_Set(80.f, 40.f);
	DolphinData.Score = 200.f;

	CameraData.ObstacleImage = CP_Image_Load("./Assets/Camera.png");
	CameraData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	CameraData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 10.f);
	CameraData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	CameraData.Score = 50.f;

	IcecreamData.ObstacleImage = CP_Image_Load("./Assets/Icecream.png");
	IcecreamData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	IcecreamData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 10.f);
	IcecreamData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	IcecreamData.Score = 50.f;

	StarFishData.ObstacleImage = CP_Image_Load("./Assets/StarFish.png");
	StarFishData.ObstacleImageSize = CP_Vector_Set(100.f, 50.f);
	StarFishData.ObstacleCollisionStartOffset = CP_Vector_Set(25.f, 20.f);
	StarFishData.ObstacleCollisionSize = CP_Vector_Set(40.f, 30.f);
	StarFishData.Score = 80.f;

	TubeData.ObstacleImage = CP_Image_Load("./Assets/Tube.png");
	TubeData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	TubeData.ObstacleCollisionStartOffset = CP_Vector_Set(15.f, 10.f);
	TubeData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	TubeData.Score = 50.f;

	CrabData.ObstacleImage = CP_Image_Load("./Assets/Crab.png");
	CrabData.ObstacleImageSize = CP_Vector_Set(100.f, 50.f);
	CrabData.ObstacleCollisionStartOffset = CP_Vector_Set(20.f, 20.f);
	CrabData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	CrabData.Score = 80.f;

	JellyfishData.ObstacleImage = CP_Image_Load("./Assets/Jellyfish.png");
	JellyfishData.ObstacleImageSize = CP_Vector_Set(80.f, 50.f);
	JellyfishData.ObstacleCollisionStartOffset = CP_Vector_Set(10.f, 10.f);
	JellyfishData.ObstacleCollisionSize = CP_Vector_Set(50.f, 30.f);
	JellyfishData.Score = 50.f;

	SharkData.ObstacleImage = CP_Image_Load("./Assets/Shark.png");
	SharkData.ObstacleImageSize = CP_Vector_Set(150.f, 90.f);
	SharkData.ObstacleCollisionStartOffset = CP_Vector_Set(30.f, 40.f);
	SharkData.ObstacleCollisionSize = CP_Vector_Set(60.f, 30.f);
	SharkData.Score = 150.f;

	ReefData.ObstacleImage = CP_Image_Load("./Assets/Reef.png");
	ReefData.ObstacleImageSize = CP_Vector_Set(100.f, 60.f);
	ReefData.ObstacleCollisionStartOffset = CP_Vector_Set(30.f, 20.f);
	ReefData.ObstacleCollisionSize = CP_Vector_Set(20.f, 40.f);
	ReefData.Score = 60.f;

	DrumData.ObstacleImage = CP_Image_Load("./Assets/Drum.png");
	DrumData.ObstacleImageSize = CP_Vector_Set(200.f, 120.f);
	DrumData.ObstacleCollisionStartOffset = CP_Vector_Set(40.f, 40.f);
	DrumData.ObstacleCollisionSize = CP_Vector_Set(80.f, 40.f);
	DrumData.Score = 200.f;

	WhaleData.ObstacleImage = CP_Image_Load("./Assets/Whale.png");
	WhaleData.ObstacleImageSize = CP_Vector_Set(3600.f, 192.f);
	WhaleData.ObstacleCollisionStartOffset = CP_Vector_Set(650.f, 0.f);
	WhaleData.ObstacleCollisionSize = CP_Vector_Set(1000.f, 300.f);
	WhaleData.Score = 1000.f;

	BatteryData.BatteryImage = CP_Image_Load("./Assets/Battery.png");
	BatteryData.BatteryImageSize = CP_Vector_Set(30.f, 30.f);
	BatteryData.bIsValid = false;
	BatteryData.Energy = 10.f;

	LowBattery = CP_Image_Load("./Assets/25Battery.png");
	HalfBattery = CP_Image_Load("./Assets/50Battery.png");
	HighBattery = CP_Image_Load("./Assets/75Battery.png");
	MaxBattery = CP_Image_Load("./Assets/100Battery.png");

	DroneImage = CP_Image_Load("./Assets/Drone.png");
	ScoreBoardInGame = CP_Image_Load("./Assets/ScoreBoardIngame.png");
}

