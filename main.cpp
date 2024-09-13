#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char kWindowTitle[] = "GC1B_02_オクノ_ソウシ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;
const float kEnemyRespawnPosY = 2000.0f;
const int kRingRedNums = 2;

float Distance(float x1, float y1, float x2, float y2) {
	float X = (x2 - x1) * (x2 - x1);
	float Y = (y2 - y1) * (y2 - y1);
	return sqrtf(X + Y);
}

//スコア総合計
float TotalPoint(float s1, float s2, float s3) {
	float X = (s1 + s2 + s3);
	return X;
}

//各色の合計
float Point(float target, float point) {
	float X = (target * point);
	return X;
}
struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;
	float radius = 0.0f;
};

struct Player {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float radius;
};

struct Image {
	Vector2 pos;
};

Player player{
	{600.0f,300.0f},
	{0.0f,0.0f},
	{0.0f,0.0f},
	96.0f,
};

Vector2 CloudRight{
	0.0f,0.0f,0.0f
};

Vector2 CloudLeft{
	0.0f,0.0f,0.0f
};

enum PlayerState {
	FLYINGRIGHT,
	FLYINGLEFT
};

Vector2 ringRED[2]{
	{
200.0f,2500.0f,50.0f
}

};

Vector2 ringYELLOW[2]{
	{
600.0f,3000.0f,50.0f}
};

Vector2 ringORANGE[2]{
	{
	1000.0f,3500.0f,50.0f}
};

struct Image background[2]{
		{0.0f,0.0f },
		{0.0f,720.0f}
};

Vector2 Parachute{
	0.0f,0.0f,64.0f
};

Vector2 Backpack{
	0.0f,0.0f,64.0f
};

Vector2 Boots{
	0.0f,0.0f,64.0f
};

Vector2 Kann{
	0.0f,0.0f,64.0f
};

Vector2 Zenn{
	0.0f,0.0f,64.0f
};

Vector2 Sou{
	0.0f,0.0f,64.0f
};

Vector2 Bi{
	0.0f,0.0f,64.0f
};

Vector2 DanderTop1{
	0.0f,0.0f,64.0f
};
Vector2 DanderTop2{
	0.0f,0.0f,64.0f
};

Vector2 DanderBottom1{
	0.0f,0.0f,64.0f
};

Vector2 DanderBottom2{
	0.0f,0.0f,64.0f
};

Vector2 Ita{
	0.0f,0.0f,64.0f
};

//シーン管理
enum Plaing {
	TITLE,
	INTRO,
	PLAY,
	PUSH,
	GEAR,
	GAMEOVER,
	RESULT,

};

//各種速度
int bgSpeed = 5;
int ringSpeed = 12;
int itemSpeed = 12;
int itaSpeed = 12;
int cloudSpeed = 10;
int itaGetSpeed = 3;


int redRingCurrentNums = 2;
int playerSwimCurrentNums = 10;
float playerToRingRed[kRingRedNums] = { -1 };
float scrollX = 0.0f;

//アイテムの取得確認
bool IsParachuteGet = false;
bool IsBackpackGet = false;
bool IsBootsGet = false;
bool IsItaHit = false;

//各リングのヒット確認
int isPlayerHitR = 0;
int isPlayerHitY = 0;
int isPlayerHitO = 0;

//各リングのヒット数
int ringRCount = 0;
int ringYCount = 0;
int ringOCount = 0;

//各リングの点数
int ringRedPoint = 300;
int ringOrangePoint = 200;
int ringYellowPoint = 100;

//アニメーションのフラグ
int saveTimer = 0;
int ringRedTimer = 0;
int ringRedAnimationIndex = 0;
int ringOrangeAnimationIndex = 0;
int ringYellowAnimationIndex = 0;
int ringAnimationTimer = 0;
int itaAnimationTimer = 0;

//タイマー管理
int gameTimer = 0;
int parachuteResTimer = 0;
int backpackResTimer = 0;
int bootsResTimer = 0;
int spaceTimer = 0;
int gearTimer = 0;
int kannTimer = 0;
int zennTimer = 0;
int souTimer = 0;
int biTimer = 0;


//スコア管理
int currentNumber = 0;
const int digitLength = 4;
int eachNumber[digitLength] = { 0 };
const int kNumberImageNum = 10;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	//画像の読み込み
	//プレイヤーアニメーション
	/*int playerSwim1 = Novice::LoadTexture("./Resources/images/swim1.png");
	int playerSwim2 = Novice::LoadTexture("./Resources/images/swim2.png");
	int playerSwim3 = Novice::LoadTexture("./Resources/images/swim3.png");
	int playerSwim4 = Novice::LoadTexture("./Resources/images/swim4.png");
	int playerSwim5 = Novice::LoadTexture("./Resources/images/swim5.png");
	int playerSwim6 = Novice::LoadTexture("./Resources/images/swim6.png");
	int playerJump1 = Novice::LoadTexture("./Resources/images/jump1.png");
	int playerJump2 = Novice::LoadTexture("./Resources/images/jump2.png");
	int playerJump3 = Novice::LoadTexture("./Resources/images/jump3.png");
	int playerJump4 = Novice::LoadTexture("./Resources/images/jump4.png");
	int playerJump5 = Novice::LoadTexture("./Resources/images/jump5.png");
	int playerJump6 = Novice::LoadTexture("./Resources/images/jump6.png");
	int playerJump7 = Novice::LoadTexture("./Resources/images/jump7.png");*/
	int playerFlyRight1 = Novice::LoadTexture("./Resources/images/PlayerFlyRight1.png");
	int playerFlyRight2 = Novice::LoadTexture("./Resources/images/PlayerFlyRight2.png");
	int playerFlyLeft1 = Novice::LoadTexture("./Resources/images/PlayerFlyLeft1.png");
	int playerFlyLeft2 = Novice::LoadTexture("./Resources/images/PlayerFlyLeft2.png");

	//読み込んだ画像を配列に格納
	int playerFlyingRight[2]{ playerFlyRight1,playerFlyRight2 };
	int playerFlyingLeft[2]{ playerFlyLeft1,playerFlyLeft2 };
	int playerCurrentTexture = playerFlyingRight[0]; //現在のプレイヤーの画像
	int playerState = PlayerState::FLYINGRIGHT; //プレイヤーの向き 最初は泳いでいる
	int freamCount = 0; //プレイヤーのアニメーション時間を計る変数
	//	int isPlayerMoving = 0; //プレイヤーが動いているか
	int playerAnimationIndex = 0; //何個目の画像かを記憶する変数

	//画像管理
	int titleBlackHandle = Novice::LoadTexture("./Resources/images/skyfallBlack.png");
	int titleYellowHandle = Novice::LoadTexture("./Resources/images/skyfallYellow.png");
	int clearBlackHandle = Novice::LoadTexture("./Resources/images/clearBrack.png");
	int clearYellowHandle = Novice::LoadTexture("./Resources/images/clearYellow.png");
	int introBlackHandle = Novice::LoadTexture("./Resources/images/setumeiBlack.png");
	int introYellowHandle = Novice::LoadTexture("./Resources/images/setumeiYellow.png");
	int sky1 = Novice::LoadTexture("./Resources/images/sky1.png");
	int sky2 = Novice::LoadTexture("./Resources/images/sky2.png");
	int ringYellow1 = Novice::LoadTexture("./Resources/images/ring_yellow_1.png");
	int ringYellow2 = Novice::LoadTexture("./Resources/images/ring_yellow_2.png");
	int ringOrange1 = Novice::LoadTexture("./Resources/images/ring_orange_1.png");
	int ringOrange2 = Novice::LoadTexture("./Resources/images/ring_orange_2.png");
	int ringRed1 = Novice::LoadTexture("./Resources/images/ring_red_1.png");
	int ringRed2 = Novice::LoadTexture("./Resources/images/ring_red_2.png");
	int orangeRingSheet = Novice::LoadTexture("./Resources/images/ring_orange-sheet.png");
	int redRingSheet = Novice::LoadTexture("./Resources/images/ring_red-sheet.png");
	int yellowRingSheet = Novice::LoadTexture("./Resources/images/ring_yellow-sheet.png");
	int progress = Novice::LoadTexture("./Resources/images/alt.png");
	int startTxt = Novice::LoadTexture("./Resources/images/startTxt.png");
	int cloudRight = Novice::LoadTexture("./Resources/images/cloudRight.png");
	int cloudLeft = Novice::LoadTexture("./Resources/images/cloudLeft.png");
	int bootsTxt = Novice::LoadTexture("./Resources/images/boots.png");
	int backpackTxt = Novice::LoadTexture("./Resources/images/backpack.png");
	int parachuteTxt = Novice::LoadTexture("./Resources/images/parachute.png");
	int blackParachuteTxt = Novice::LoadTexture("./Resources/images/blackParachute.png");
	int blackBackpackTxt = Novice::LoadTexture("./Resources/images/blackBackpack.png");
	int blackBootsTxt = Novice::LoadTexture("./Resources/images/blackBoots.png");

	int space1Txt = Novice::LoadTexture("./Resources/images/space1.png");
	int space2Txt = Novice::LoadTexture("./Resources/images/space2.png");
	int push = Novice::LoadTexture("./Resources/images/ose.png");
	int kann = Novice::LoadTexture("./Resources/images/kann.png");
	int zenn = Novice::LoadTexture("./Resources/images/zenn.png");
	int sou = Novice::LoadTexture("./Resources/images/sou.png");
	int bi = Novice::LoadTexture("./Resources/images/bi.png");
	int gearBgTxt = Novice::LoadTexture("./Resources/images/gearBg.png");
	int dangerTxt=Novice::LoadTexture("./Resources/images/danger.png");
	int itaTxt=Novice::LoadTexture("./Resources/images/ita.png");


	//効果音管理

	int startAudioHandle = Novice::LoadAudio("./Resources/sounds/start.mp3");
	//	int jumpAudioHandle = Novice::LoadAudio("./Resources/sounds/jump.mp3");
	int effectSound1 = Novice::LoadAudio("./Resources/sounds/effectSound1.mp3");
	int effectSound2 = Novice::LoadAudio("./Resources/sounds/effectSound2.mp3");
	int effectSound3 = Novice::LoadAudio("./Resources/sounds/effectSound3.mp3");
	//BGM管理
	int titleAudioHandle = Novice::LoadAudio("./Resources/sounds/titleBGM.mp3");
	int playAudioHandle = Novice::LoadAudio("./Resources/sounds/playBGM.mp3");
	int clearAudioHandle = Novice::LoadAudio("./Resources/sounds/clearBGM.mp3");

	//プレイハンドルの宣言
	int playStartHandle = -1;
	//int playJumpHandle = -1;
	int playClearHandle = -1;
	int playTitleHandle = -1;
	int playPlayingHandle = -1;

	//宣言
	int gameScene = 0;
	int titleTimer = 0;
	int introTimer = 0;
	int clearTimer = 0;
	int resetTimer = 0;
	float resetPosition = 600.0f;
	float screenY = 0.0f;
	int distance1 = 0;
	int distance2 = 0;
	int distance3 = 0;
	int isOrangeRing1Alive = 1;
	int isRedRing1Alive = 1;
	int isYellowRing1Alive = 1;
	int picSize = 64;
	int OrangeRingTime = 0;
	int RedRingTime = 0;
	int YellowRingTime = 0;
	int playerProgressX = 1150;
	int playerProgressY = 4;
	int respawnRed = 0;
	int respawnOrange = 0;
	int respawnYellow = 0;

	float parachuteDistance = 0.0f;
	float backpackDistance = 0.0f;
	float bootsDistance = 0.0f;
	float itaDistance = 0.0f;

	player.acceleration.y = -2.0f;

	//定数
	const int kClearTimerLimit = 80;
	const int kTitleTimerLimit = 80;
	const int kIntroTimerLimit = 80;
	const int kSpaceTimerLimit = 80;

	//配列に格納
	int ringOrange[2] = { ringOrange1,ringOrange2 };
	int ringYellow[2] = { ringYellow1,ringYellow2 };
	int ringRed[2] = { ringRed1,ringRed2 };
	int ringOrangeCurrentTexture = ringOrange[0];
	int ringYellowCurrentTexture = ringYellow[0];
	int ringRedCurrentTexture = ringRed[0];

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//スコア
	int numberHandle[kNumberImageNum] = { 0 };
	for (int i = 0; i < kNumberImageNum; i++) {
		char numberStr[256];
		sprintf_s(numberStr, "./Resources/images/number/%d.png", i);
		numberHandle[i] = Novice::LoadTexture(numberStr);
	}
	int scorePosX[digitLength] = { 0 };
	int scorePosY[digitLength] = { 0 };
	for (int i = 0; i < 4; i++) {
		scorePosX[i] = 670 + 72 * i;
		scorePosY[i] = 450;
	}


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//各リングのポイント
		float redSum = Point(float(ringRedPoint), float(ringRCount));
		float orangeSum = Point(float(ringOrangePoint), float(ringOCount));
		float yellowSum = Point(float(ringYellowPoint), float(ringYCount));

		//ポイントの総合計
		float totalSum = TotalPoint(redSum, orangeSum, yellowSum);
		currentNumber = int(totalSum);

		switch (gameScene) {

		case TITLE:

			//初期化
			ringRED[0].x = 200.0f;
			ringRED[0].y = 1500.0f;
			ringYELLOW[0].x = 600.0f;
			ringYELLOW[0].y = 2500.0f;
			ringORANGE[0].x = 1000.0f;
			ringORANGE[0].y = 3500.0f;
			ringRCount = 0;
			ringOCount = 0;
			ringYCount = 0;
			saveTimer = 0;
			ringAnimationTimer = 0;
			gameTimer = 0;
			respawnRed = 0;
			respawnOrange = 0;
			respawnYellow = 0;
			ringSpeed = 12;
			//雲
			cloudSpeed = 12;
			CloudRight.x = kWindowWidth - 540;
			CloudRight.y = -500;
			CloudLeft.x = 0;
			CloudLeft.y = -500;
			//アイテムの初期化
			Parachute.y = 2000;
			Parachute.x = 300;
			Backpack.y = 3000;
			Backpack.x = 600;
			Boots.y = 4000;
			Boots.x = 900;
			itemSpeed = 12;


			IsParachuteGet = false;
			IsBackpackGet = false;
			IsBootsGet = false;

			//加速板
			itaSpeed = 12;
			itaGetSpeed = 1;
			Ita.x = float(rand()%900+200);
			Ita.y = 2000;

			//ケースPUSH
			DanderTop1.x = 0;
			DanderTop2.x = -1280;
			DanderTop1.y = 10;
			DanderTop2.y = 10;
			DanderBottom1.x = 0;
			DanderBottom2.x = 1280;
			DanderBottom1.y = 582;
			DanderBottom2.y = 582;
			

			//ケースGEAR
			Kann.x = -128;
			Kann.y = -128;
			Zenn.x = 1408;
			Zenn.y = -128;
			Sou.x = -128;
			Sou.y = 848;
			Bi.x = 1408;
			Bi.y = 848;
			gearTimer = 0;
			kannTimer = 0;
			zennTimer = 0;
			souTimer = 0;
			biTimer = 0;


			Novice::StopAudio(playClearHandle);

			if (Novice::CheckHitKey(DIK_RETURN) && !preKeys[DIK_RETURN]) {
				playStartHandle = Novice::PlayAudio(startAudioHandle, false, 3.0f);
				gameScene = INTRO;
			}
			break;

		case INTRO:
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				playStartHandle = Novice::PlayAudio(startAudioHandle, false, 3.0f);
				gameScene = PLAY;
			}
			break;

		case PLAY:

			Novice::StopAudio(playTitleHandle);

			gameTimer++;

			if (gameTimer % 100 == 0) {
				playerProgressY += 9;
			}

			if (playerState == PlayerState::FLYINGRIGHT) {
				playerCurrentTexture = playerFlyingRight[playerAnimationIndex];
			}
			else if (playerState == PlayerState::FLYINGLEFT) {
				playerCurrentTexture = playerFlyingLeft[playerAnimationIndex];
			}

		
			///プレイヤーの移動
			if (keys[DIK_LEFT]) {
				player.position.x -= 15;
				playerState = PlayerState::FLYINGLEFT;
			}
			if (player.position.x <= player.radius+200) {
				player.position.x = player.radius+200;
			}
			if (keys[DIK_RIGHT]) {
				playerState = PlayerState::FLYINGRIGHT;
				player.position.x += 15;
			}
			if (player.position.x >= kWindowWidth - player.radius-100) {
				player.position.x = kWindowWidth - player.radius-100;
			}

			freamCount++;
			if (freamCount % 10 == 0) { //7フレームおきに画像を更新する
				playerAnimationIndex++; //画像の番号を1個進める
				if (playerAnimationIndex > 1) {
					playerAnimationIndex = 0; //画像が最後まで来たら一番最初に戻す
				}
			}

			player.velocity.y += player.acceleration.y;
			player.position.y += player.velocity.y;
			if (player.position.y <= player.radius) {
				player.position.y = player.radius;
			}

			screenY = (player.position.y - 250) * -1;



			//アイテムの移動

			if (gameTimer >= 360) {
				Parachute.y -= itemSpeed;
				Backpack.y -= itemSpeed;
				Boots.y -= itemSpeed;

				if (Parachute.y <= -100 && IsParachuteGet == false) {
					parachuteResTimer++;
					if (parachuteResTimer >= 300) {
						Parachute.x= float(rand() % 900 + 200);
						Parachute.y = 1000;
						parachuteResTimer = 0;
					}

				}
				if (Backpack.y <= -100 && IsBackpackGet == false) {
					backpackResTimer++;
					if (backpackResTimer >= 300) {
						Backpack.x= float(rand() % 900 + 200);
						Backpack.y = 1000;
						backpackResTimer = 0;
					}

				}
				if (Boots.y <= -100 && IsBootsGet == false) {
					bootsResTimer++;
					if (bootsResTimer >= 300) {
						Boots.x= float(rand() % 900 + 200);
						Boots.y = 1000;
						bootsResTimer = 0;
					}

				}


			}

			/*	Novice::ScreenPrintf(15, 15, "%f", Parachute.y);
				Novice::ScreenPrintf(15, 30, "%d", IsParachuteGet);
				Novice::ScreenPrintf(15, 45, "%f", Backpack.y);
				Novice::ScreenPrintf(15, 60, "%d", IsBackpackGet);
				Novice::ScreenPrintf(15, 75, "%f", Boots.y);
				Novice::ScreenPrintf(15, 90, "%d", IsBootsGet);*/


				//アイテムの当たり判定
			parachuteDistance = Distance(player.position.x, player.position.y, Parachute.x, Parachute.y);
			backpackDistance = Distance(player.position.x, player.position.y, Backpack.x, Backpack.y);
			bootsDistance = Distance(player.position.x, player.position.y, Boots.x, Boots.y);

			if (parachuteDistance <= player.radius + Parachute.radius) {
				IsParachuteGet = true;
				Parachute.y = -1000;
			}
			if (backpackDistance <= player.radius + Backpack.radius) {
				IsBackpackGet = true;
				Backpack.y = -1000;
			}
			if (bootsDistance <= player.radius + Boots.radius) {
				IsBootsGet = true;
				Boots.y = -1000;
			}


			//リングのアニメーション
			saveTimer++;
			if (saveTimer % 20 == 0) { //20フレームおきに画像を更新する
				ringRedAnimationIndex++; //画像の番号を1個進める
				if (ringRedAnimationIndex >= 2) {
					ringRedAnimationIndex = 0; //画像が最後まで来たら一番最初に戻す
				}
			}
			if (saveTimer % 20 == 0) { //20フレームおきに画像を更新する
				ringOrangeAnimationIndex++; //画像の番号を1個進める
				if (ringOrangeAnimationIndex >= 2) {
					ringOrangeAnimationIndex = 0; //画像が最後まで来たら一番最初に戻す
				}
			}
			if (saveTimer % 20 == 0) { //20フレームおきに画像を更新する
				ringYellowAnimationIndex++; //画像の番号を1個進める
				if (ringYellowAnimationIndex >= 2) {
					ringYellowAnimationIndex = 0; //画像が最後まで来たら一番最初に戻す
				}
			}

			ringOrangeCurrentTexture = ringOrange[ringOrangeAnimationIndex];
			ringYellowCurrentTexture = ringYellow[ringYellowAnimationIndex];
			ringRedCurrentTexture = ringRed[ringRedAnimationIndex];

			//加速板

			Novice::ScreenPrintf(50, 50, "%f", Ita.x);
			Novice::ScreenPrintf(50, 65, "%f", Ita.y);
			Ita.y -= itaSpeed;

			itaDistance = Distance(Ita.x, Ita.y, player.position.x, player.position.y);
			if (itaDistance <= Ita.radius + player.radius) {
				IsItaHit = true;
				Ita.x = float(rand() % 900 + 200);
				Ita.y = 3000;
					
			}

			if (IsItaHit == true) {
				ringSpeed += itaGetSpeed;
				cloudSpeed += itaGetSpeed;
				itemSpeed += itaGetSpeed;
				itaSpeed += itaGetSpeed;
				IsItaHit = false;
			}

			if (Ita.y <= -100) {
				Ita.x = float(rand() % 900 + 200);
				Ita.y = 2000;
			}


			//背景スクロール
			background[0].pos.y -= bgSpeed;
			if (background->pos.y <= -kWindowHeight) {
				background->pos.y = kWindowHeight;
			}
			background[1].pos.y -= bgSpeed;
			if (background[1].pos.y <= -kWindowHeight) {
				background[1].pos.y = kWindowHeight;
			}
			//雲の移動処理
			CloudRight.y -= cloudSpeed;
			if (CloudRight.y <= -500) {
				CloudRight.y = 2000;
			}

			CloudLeft.y -= cloudSpeed;
			if (CloudLeft.y <= -500) {
				CloudLeft.y = 1000;
			}

			//画面は端まで行ったら戻る処理
			if (gameTimer >= 240) {
				ringRED[0].y -= ringSpeed;

				if (ringRED[0].y <= -100) {
					ringRED[0].y = 2000;
					ringRED[0].x = float(rand() % 900 + 200);
					respawnRed += 1;
				}

				ringORANGE[0].y -= ringSpeed;

				if (ringORANGE[0].y <= -100) {
					ringORANGE[0].y = 2000;
					ringORANGE[0].x = float(rand() % 900 + 200);
					respawnOrange += 1;
				}


				ringYELLOW[0].y -= ringSpeed;

				if (ringYELLOW[0].y <= -100) {
					ringYELLOW[0].y =2000;
					ringYELLOW[0].x = float(rand() % 900 + 200);
					respawnYellow += 1;
				}

			}

			if (gameTimer >= 2400) {
				if (IsParachuteGet == false || IsBackpackGet == false || IsBootsGet == false) {
					gameScene = GAMEOVER;
				}
				else
					gameScene = PUSH;

			}
			break;

		case PUSH:
			Novice::StopAudio(playTitleHandle);

			gameTimer++;

			if (gameTimer % 100 == 0) {
				playerProgressY += 9;
			}

			if (playerState == PlayerState::FLYINGRIGHT) {
				playerCurrentTexture = playerFlyingRight[playerAnimationIndex];
			}
			else if (playerState == PlayerState::FLYINGLEFT) {
				playerCurrentTexture = playerFlyingLeft[playerAnimationIndex];
			}

			//DANGER
			DanderTop1.x += 10;
			DanderTop2.x += 10;
			DanderBottom1.x -= 10;
			DanderBottom2.x -= 10;
			

			if (DanderTop1.x >= 1280) {
				DanderTop1.x = -1280;
			}
			if (DanderTop2.x >= 1280) {
				DanderTop2.x = -1280;
			}
			if (DanderBottom1.x <= -1280) {
				DanderBottom1.x = 1280;
			}
			if (DanderBottom2.x <= -1280) {
				DanderBottom2.x = 1280;
			}
			
			

			///プレイヤーの移動
			if (keys[DIK_LEFT]) {
				player.position.x -= 15;
				playerState = PlayerState::FLYINGLEFT;
			}
			if (player.position.x <= player.radius+200) {
				player.position.x = player.radius+200;
			}
			if (keys[DIK_RIGHT]) {
				playerState = PlayerState::FLYINGRIGHT;
				player.position.x += 15;
			}
			if (player.position.x >= kWindowWidth - player.radius-200) {
				player.position.x = kWindowWidth - player.radius - 200;
			}

			freamCount++;
			if (freamCount % 10 == 0) { //7フレームおきに画像を更新する
				playerAnimationIndex++; //画像の番号を1個進める
				if (playerAnimationIndex > 1) {
					playerAnimationIndex = 0; //画像が最後まで来たら一番最初に戻す
				}
			}
			player.velocity.y += player.acceleration.y;
			player.position.y += player.velocity.y;
			if (player.position.y <= player.radius) {
				player.position.y = player.radius;
			}

			screenY = (player.position.y - 300) * -1;

			//背景スクロール
			background[0].pos.y -= bgSpeed;
			if (background->pos.y <= -kWindowHeight) {
				background->pos.y = kWindowHeight;
			}
			background[1].pos.y -= bgSpeed;
			if (background[1].pos.y <= -kWindowHeight) {
				background[1].pos.y = kWindowHeight;
			}



			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				gameScene = GEAR;
			}


			break;

		case GEAR:
			gearTimer++;
			kannTimer++;
			zennTimer++;
			souTimer++;
			biTimer++;

			if (gearTimer >= 240) {
				gearTimer = 0;
				gameScene = RESULT;
			}

			if (kannTimer >= 30) {
				Kann.x += 20;
				Kann.y += 12;
				if (Kann.x >= 512) {
					Kann.x = 512;
					Kann.y = 232;
				}
			}

			if (zennTimer >= 50) {
				Zenn.x -= 20;
				Zenn.y += 12;
				if (Zenn.x <= 640) {
					Zenn.x = 640;
					Zenn.y = 232;
				}
			}

			if (souTimer >= 70) {
				Sou.x += 20;
				Sou.y -= 12;
				if (Sou.x >= 512) {
					Sou.x = 512;
					Sou.y = 360;
				}
			}

			if (biTimer >= 90) {
				Bi.x -= 20;
				Bi.y -= 12;
				if (Bi.x <= 640) {
					Bi.x = 640;
					Bi.y = 360;
				}
			}

			break;

		case GAMEOVER:

			Novice::StopAudio(playPlayingHandle);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				playStartHandle = Novice::PlayAudio(startAudioHandle, false, 3.0f);
				gameScene = TITLE;
				gameTimer = resetTimer;
				player.position.x = resetPosition;

				playerProgressX = 1150;
				playerProgressY = 4;
			}


			break;

		case RESULT:


			Novice::StopAudio(playPlayingHandle);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				playStartHandle = Novice::PlayAudio(startAudioHandle, false, 3.0f);
				gameScene = TITLE;
				gameTimer = resetTimer;
				player.position.x = resetPosition;

				playerProgressX = 1150;
				playerProgressY = 4;	//プログレス初期化
			}

			break;

		}

		///
		/// ↑更新処理ここまで
		///
		/// ↓サウンド処理ここから
		///
		switch (gameScene) {
		case TITLE:
			if (!Novice::IsPlayingAudio(playTitleHandle)) {
				playTitleHandle = Novice::PlayAudio(titleAudioHandle, false, 1.0f);
			}
			break;

		case PLAY:
			if (!Novice::IsPlayingAudio(playPlayingHandle)) {
				playPlayingHandle = Novice::PlayAudio(playAudioHandle, false, 1.0f);
			}

			if (isPlayerHitR == 1) {
				Novice::PlayAudio(effectSound1, false, 1.0f);
				isPlayerHitR = 0;

			}
			if (isPlayerHitO == 1) {
				Novice::PlayAudio(effectSound2, false, 1.0f);

				isPlayerHitO = 0;

			}
			if (isPlayerHitY == 1) {
				Novice::PlayAudio(effectSound3, false, 1.0f);
				isPlayerHitY = 0;
			}


			break;

		case PUSH:

			break;

		case GEAR:

			break;
		case GAMEOVER:


			break;

		case RESULT:
			if (!Novice::IsPlayingAudio(playClearHandle)) {

				playClearHandle = Novice::PlayAudio(clearAudioHandle, true, 2.0f);
			}
			break;
		}

		///
		/// ↑サウンド処理ここまで
		///
		/// ↓描画処理ここから
		///
		switch (gameScene)
		{
		case TITLE:
			titleTimer++;
			if (titleTimer == kTitleTimerLimit)
			{
				titleTimer = 0;
			}
			if (titleTimer <= kTitleTimerLimit / 2) {
				Novice::DrawSprite(0, 0, titleBlackHandle, 1, 1, 0, WHITE);
			}
			else if (titleTimer <= kTitleTimerLimit) {
				Novice::DrawSprite(0, 0, titleYellowHandle, 1, 1, 0, WHITE);
			}
			if (titleTimer == kTitleTimerLimit) {
				titleTimer = 0;
			}




			break;

		case INTRO:
			introTimer++;
			if (introTimer == kIntroTimerLimit)
			{
				introTimer = 0;
			}
			if (introTimer <= kIntroTimerLimit / 2) {
				Novice::DrawSprite(0, 0, introBlackHandle, 1, 1, 0, WHITE);
			}
			else if (introTimer <= kIntroTimerLimit) {
				Novice::DrawSprite(0, 0, introYellowHandle, 1, 1, 0, WHITE);
			}
			if (introTimer == kIntroTimerLimit) {
				introTimer = 0;
			}
			break;

		case PLAY:
			//背景描画
			Novice::DrawSprite(int(background[0].pos.x), int(background[0].pos.y), sky1, 1, 1, 0, WHITE);
			Novice::DrawSprite(int(background[1].pos.x), int(background[1].pos.y), sky2, 1, 1, 0, WHITE);
			if (gameTimer <= 180 && gameTimer % 30) {
				Novice::DrawSprite(130, 250, startTxt, 1.6f, 1.6f, 0, WHITE);
			}

			Novice::DrawSprite(1150, 10, progress, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(playerProgressX, playerProgressY, playerFlyLeft1, 0.5, 0.5, 0.0f, WHITE);


			distance1 =
				(int(screenY) - int(ringORANGE[0].y)) * (int(screenY) - int(ringORANGE[0].y)) +
				(int(player.position.x - player.radius) - int(ringORANGE[0].x)) *
				(int(player.position.x - player.radius) - int(ringORANGE[0].x));
			distance2 = (int(screenY) - int(ringRED[0].y)) * (int(screenY) - int(ringRED[0].y)) +
				(int(player.position.x - player.radius) - int(ringRED[0].x)) *
				(int(player.position.x - player.radius) - int(ringRED[0].x));
			distance3 = (int(screenY) - int(ringYELLOW[0].y)) * (int(screenY) - int(ringYELLOW[0].y)) +
				(int(player.position.x - player.radius) - int(ringYELLOW[0].x)) *
				(int(player.position.x - player.radius) - int(ringYELLOW[0].x));


			if (distance1 <= (player.radius + 32) * (player.radius + 32)) {
				isOrangeRing1Alive = 0;
				isPlayerHitO = 1;
			}
			if (isOrangeRing1Alive == 0) {
				OrangeRingTime++;
				Novice::DrawSpriteRect(
					int(ringORANGE[0].x), int(ringORANGE[0].y), picSize * (OrangeRingTime / 2), 0, picSize, picSize, orangeRingSheet, 64.0f / 896.0f * 2, 2, 0, 0xFFFFFFFF);
			}
			if (OrangeRingTime == 30) {
				ringOCount += 1;
				isOrangeRing1Alive = 1;
				OrangeRingTime = 0;
			}
			if (isOrangeRing1Alive == 1) {

				if (respawnOrange <= 15) {
					Novice::DrawSprite(
						int(ringORANGE[0].x), int(ringORANGE[0].y), ringOrangeCurrentTexture, 1.0f,
						1.0f, 0.0f, WHITE);
				}

			}
			if (distance2 <= (player.radius + 32) * (player.radius + 32)) {
				isRedRing1Alive = 0;
				isPlayerHitR = 1;
			}
			if (isRedRing1Alive == 0) {
				RedRingTime++;
				Novice::DrawSpriteRect(
					int(ringRED[0].x), int(ringRED[0].y), picSize * (RedRingTime / 2), 0, picSize,
					picSize,
					redRingSheet, 64.0f / 704.0f * 2, 2, 0, 0xFFFFFFFF);
			}

			if (isRedRing1Alive == 1) {
				if (respawnRed <= 15) {
					Novice::DrawSprite(
						int(ringRED[0].x), int(ringRED[0].y), ringRedCurrentTexture, 1.0f, 1.0f, 0.0f,
						WHITE);
				}

			}

			if (RedRingTime == 30) {
				ringRCount += 1;
				isRedRing1Alive = 1;
				RedRingTime = 0;
			}
			if (distance3 <= (player.radius + 32) * (player.radius + 32)) {
				isYellowRing1Alive = 0;
				isPlayerHitY = 1;
			}

			if (isYellowRing1Alive == 0) {

				YellowRingTime++;
				Novice::DrawSpriteRect(
					int(ringYELLOW[0].x), int(ringYELLOW[0].y), picSize * (YellowRingTime / 2), 0,
					picSize,
					picSize, yellowRingSheet, 64.0f / 832.0f * 2, 2, 0, 0xFFFFFFFF);
			}
			if (isYellowRing1Alive == 1) {

				if (respawnYellow <= 15) {
					Novice::DrawSprite(
						int(ringYELLOW[0].x), int(ringYELLOW[0].y), ringYellowCurrentTexture, 1.0f,
						1.0f, 0.0f, WHITE);
				}

			}
			if (YellowRingTime == 30) {
				ringYCount += 1;
				isYellowRing1Alive = 1;
				YellowRingTime = 0;
			}

			//アイテム
			if (IsParachuteGet == false) {
				Novice::DrawSprite(int(Parachute.x - Parachute.radius), int(Parachute.y - Parachute.radius), parachuteTxt, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawSprite(50, 100, blackParachuteTxt, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawBox(50, 100, 128, 128, 0.0f,BLACK, kFillModeWireFrame);
			}

			else{
				Novice::DrawBox(50, 100, 128, 128, 0.0f, WHITE, kFillModeSolid);
				Novice::DrawSprite(50, 100, parachuteTxt, 1.0f, 1.0f, 0.0f, WHITE);
			}
			

			if (IsBackpackGet == false) {
				Novice::DrawSprite(int(Backpack.x - Backpack.radius), int(Backpack.y - Backpack.radius), backpackTxt, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawSprite(50, 306, blackBackpackTxt, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawBox(50, 306, 128, 128, 0.0f, BLACK, kFillModeWireFrame);

			}

			else{
				Novice::DrawBox(50, 306, 128, 128, 0.0f, WHITE, kFillModeSolid);
				Novice::DrawSprite(50, 306, backpackTxt, 1.0f, 1.0f, 0.0f, WHITE);
			}
				

			if (IsBootsGet == false) {
				Novice::DrawSprite(int(Boots.x - Boots.radius), int(Boots.y - Boots.radius), bootsTxt, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawSprite(50, 512, blackBootsTxt, 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawBox(50, 512, 128, 128, 0.0f, BLACK, kFillModeWireFrame);

			}

			else {
				Novice::DrawBox(50, 512, 128, 128, 0.0f, WHITE, kFillModeSolid);
				Novice::DrawSprite(50, 512, bootsTxt, 1.0f, 1.0f, 0.0f, WHITE);

			}

			//加速板
			itaAnimationTimer++;
			if (itaAnimationTimer >= 30) {
				itaAnimationTimer = 0;
			}

			Novice::DrawSpriteRect(int(Ita.x-Ita.radius), int(Ita.y-Ita.radius), 128 * (itaAnimationTimer / 5),
				0, 128, 128, itaTxt, 128.0f / 896.0f, 1.0f, 0.0f, 0xFFFFFFFF);


			//自機
			Novice::DrawSprite(int(player.position.x) - int(player.radius), int(screenY) - int(player.radius), playerCurrentTexture, 1.5, 1.5, 0.0f, WHITE);

			//雲
			Novice::DrawSprite(int(CloudRight.x), int(CloudRight.y), cloudRight, 2.0f, 2.0f, 0.0f, WHITE);
			Novice::DrawSprite(int(CloudLeft.x), int(CloudLeft.y), cloudLeft, 2.0f, 2.0f, 0.0f, WHITE);
			break;

		case PUSH:

			Novice::ScreenPrintf(50, 50, "%d", gameScene);

			//背景描画
			Novice::DrawSprite(int(background[0].pos.x), int(background[0].pos.y), sky1, 1, 1, 0, WHITE);
			Novice::DrawSprite(int(background[1].pos.x), int(background[1].pos.y), sky2, 1, 1, 0, WHITE);

			//自機
			Novice::DrawSprite(int(player.position.x) - int(player.radius), int(screenY) - int(player.radius), playerCurrentTexture, 1.5, 1.5, 0.0f, WHITE);

			//DANGER
			Novice::DrawSprite(int(DanderTop1.x),int( DanderTop1.y), dangerTxt, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(int(DanderTop2.x),int( DanderTop2.y), dangerTxt, 1.0f, 1.0f, 0.0f, WHITE);

			Novice::DrawSprite(int(DanderBottom1.x),int( DanderBottom1.y), dangerTxt, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(int(DanderBottom2.x),int( DanderBottom2.y), dangerTxt, 1.0f, 1.0f, 0.0f, WHITE);


			//スペース
			spaceTimer++;
			if (spaceTimer == kSpaceTimerLimit)
			{
				spaceTimer = 0;
			}
			if (spaceTimer <= kSpaceTimerLimit / 2) {
				Novice::DrawSprite(448, 200, space1Txt, 1, 1, 0, WHITE);
			}
			else if (spaceTimer <= kSpaceTimerLimit) {
				Novice::DrawSprite(448, 200, space2Txt, 1, 1, 0, WHITE);
			}

			if (spaceTimer == kSpaceTimerLimit) {
				spaceTimer = 0;
			}
		

			Novice::DrawSprite(512+rand()%10-10, 452+rand() % 5 - 5, push, 1.0f, 1.0f, 0.0f, WHITE);

			break;
		case GEAR:
			Novice::DrawSprite(0, 0, gearBgTxt, 1.0f, 1.0f, 0.0f, WHITE);

			Novice::ScreenPrintf(50, 65, "%d", gameScene);

		
				Novice::DrawSprite(int(Kann.x), int(Kann.y), kann, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(int(Zenn.x), int(Zenn.y), zenn, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(int(Sou.x), int(Sou.y), sou, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(int(Bi.x), int(Bi.y), bi, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case RESULT:
			clearTimer++;
			if (clearTimer <= kClearTimerLimit / 2) {
				Novice::DrawSprite(0, 0, clearBlackHandle, 1, 1, 0, WHITE);
			}
			else if (clearTimer <= kClearTimerLimit) {
				Novice::DrawSprite(0, 0, clearYellowHandle, 1, 1, 0, WHITE);
			}
			if (clearTimer == kClearTimerLimit) {
				clearTimer = 0;
			}

			for (int i = 0; i < digitLength; i++) {

				eachNumber[i] = currentNumber / int(pow(10, digitLength - 1 - i));
				currentNumber = int(totalSum) % int(pow(10, digitLength - 1 - i));
				if (totalSum <= 0) {
					Novice::DrawSprite(scorePosX[i], scorePosY[i], numberHandle[0], 3.5f, 3.5f, 0.0f, WHITE);
				}
				else
					Novice::DrawSprite(scorePosX[i], scorePosY[i], numberHandle[eachNumber[i]], 3.5f, 3.5f, 0.0f, WHITE);

			}

			break;
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}