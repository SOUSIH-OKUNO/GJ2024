#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char kWindowTitle[] = "GC1B_02_オクノ_ソウシ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;
const float kEnemyRespawnPosY = 750.0f;
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
	{300.0f,300.0f},
	{0.0f,0.0f},
	{0.0f,0.0f},
	30.0f,
};

enum State {
	SWIM,
	JUMP
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
		{1280.0f,0.0f}
};

//シーン管理
enum Plaing {
	TITLE,
	INTRO,
	PLAY,
	RESULT,

};

int bgSpeed = 8;
int ringSpeedX = 15;
int redRingCurrentNums = 2;
int playerSwimCurrentNums = 10;
float playerToRingRed[kRingRedNums] = { -1 };
float scrollX = 0.0f;

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

//タイマー管理
int gameTimer = 0;

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
	int playerSwim1 = Novice::LoadTexture("./Resources/images/swim1.png");
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
	int playerJump7 = Novice::LoadTexture("./Resources/images/jump7.png");

	//読み込んだ画像を配列に格納
	int playerSwims[6]{ playerSwim1,playerSwim2,playerSwim3,playerSwim4,playerSwim5,playerSwim6 };
	int platerJumps[7]{ playerJump1,playerJump2,playerJump3,playerJump4,playerJump5,playerJump6,playerJump7 };
	int playerCurrentTexture = playerSwims[0]; //現在のプレイヤーの画像
	int playerState = State::SWIM; //プレイヤーの向き 最初は泳いでいる
	int freamCount = 0; //プレイヤーのアニメーション時間を計る変数
//	int isPlayerMoving = 0; //プレイヤーが動いているか
	int playerAnimationIndex = 0; //何個目の画像かを記憶する変数

	//画像管理
	int titleBlackHandle = Novice::LoadTexture("./Resources/images/DolphinJumpBlack.png");
	int titleYellowHandle = Novice::LoadTexture("./Resources/images/DolphinJumpYellow.png");
	int clearBlackHandle = Novice::LoadTexture("./Resources/images/clearBrack.png");
	int clearYellowHandle = Novice::LoadTexture("./Resources/images/clearYellow.png");
	int introBlackHandle = Novice::LoadTexture("./Resources/images/introkuro.png");
	int introYellowHandle = Novice::LoadTexture("./Resources/images/introkiiro.png");
	int sea1 = Novice::LoadTexture("./Resources/images/sea.png");
	int ringYellow1 = Novice::LoadTexture("./Resources/images/ring_yellow_1.png");
	int ringYellow2 = Novice::LoadTexture("./Resources/images/ring_yellow_2.png");
	int ringOrange1 = Novice::LoadTexture("./Resources/images/ring_orange_1.png");
	int ringOrange2 = Novice::LoadTexture("./Resources/images/ring_orange_2.png");
	int ringRed1 = Novice::LoadTexture("./Resources/images/ring_red_1.png");
	int ringRed2 = Novice::LoadTexture("./Resources/images/ring_red_2.png");
	int orangeRingSheet = Novice::LoadTexture("./Resources/images/ring_orange-sheet.png");
	int redRingSheet = Novice::LoadTexture("./Resources/images/ring_red-sheet.png");
	int yellowRingSheet = Novice::LoadTexture("./Resources/images/ring_yellow-sheet.png");
	int progress = Novice::LoadTexture("./Resources/images/progress.png");
	int spaceText = Novice::LoadTexture("./Resources/images/SPACE-Sheet.png");
	int deText = Novice::LoadTexture("./Resources/images/de.png");
	int jumpText = Novice::LoadTexture("./Resources/images/jumpText.png");

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
	float resetPosition = 300.0f;
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
	int playerProgressX = 990;
	int playerProgressY = 4;
	int respawnRed = 0;
	int respawnOrange = 0;
	int respawnYellow = 0;

	player.acceleration.y = -2.0f;

	//定数
	const int kClearTimerLimit = 80;
	const int kTitleTimerLimit = 80;
	const int kIntroTimerLimit = 80;

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

			//リング初期化
			ringRED[0].x = 3500.0f;
			ringRED[0].y = 100.0f;
			ringYELLOW[0].x = 3950.0f;
			ringYELLOW[0].y = 150.0f;
			ringORANGE[0].x = 4350.0f;
			ringORANGE[0].y = 200.0f;
			ringRCount = 0;
			ringOCount = 0;
			ringYCount = 0;
			saveTimer = 0;
			ringAnimationTimer = 0;
			gameTimer = 0;
			respawnRed = 0;
			respawnOrange = 0;
			respawnYellow = 0;

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
				playerProgressX += 10;
			}

			if (playerState == State::SWIM) {
				playerCurrentTexture = playerSwims[playerAnimationIndex];
			}
			else if (playerState == State::JUMP) {
				playerCurrentTexture = platerJumps[playerAnimationIndex];
			}

			/*if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				playJumpHandle = Novice::PlayAudio(jumpAudioHandle, false, 2.0f);
				player.velocity.y = 30.0f;
				playerState = State::JUMP;
				isPlayerMoving = 1;
				if (player.position.y >= 500) {
					player.velocity.y = 0;
				}
			}*/
			///プレイヤーの移動
			if (keys[DIK_LEFT]) {
				player.position.x -= 10;
			}
			if (player.position.x <=player.radius) {
				player.position.x = player.radius;
			}
			if (keys[DIK_RIGHT]) {
				player.position.x += 10;
			}
			if (player.position.x >=kWindowWidth-player.radius) {
				player.position.x = kWindowWidth - player.radius-player.radius;
			}

			freamCount++;
			if (freamCount % 10 == 0) { //7フレームおきに画像を更新する
				playerAnimationIndex++; //画像の番号を1個進める
				if (playerAnimationIndex > 5) {
					playerAnimationIndex = 0; //画像が最後まで来たら一番最初に戻す
				}
			}
			player.velocity.y += player.acceleration.y;
			player.position.y += player.velocity.y;
			if (player.position.y <= player.radius) {
				player.position.y = player.radius;
			}

			//screenY = (player.position.y - 500) * -1;

			if (gameTimer >= 1800) {
				gameScene = RESULT;
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

			//背景スクロール
			background[0].pos.y -= bgSpeed;
			if (background->pos.y <= -kWindowHeight) {
				background->pos.y = kWindowHeight;
			}
			background[1].pos.y -= bgSpeed;
			if (background[1].pos.y <= -kWindowHeight) {
				background[1].pos.y = kWindowHeight;
			}

			//画面は端まで行ったら戻る処理
			ringRED[0].y -= ringSpeedX;

			if (ringRED[0].y <= -100) {
				ringRED[0].y = kWindowHeight / 2 + kEnemyRespawnPosY;
				ringRED[0].x = float(rand() % 1000 + 64);
				respawnRed += 1;
			}

			ringORANGE[0].y -= ringSpeedX;

			if (ringORANGE[0].y<= -100) {
				ringORANGE[0].y = kWindowHeight / 2 + kEnemyRespawnPosY;
				ringORANGE[0].x = float(rand() % 1000 + 64);
				respawnOrange += 1;
			}


			ringYELLOW[0].y-= ringSpeedX;

			if (ringYELLOW[0].y <= -100) {
				ringYELLOW[0].y = kWindowHeight / 2 + kEnemyRespawnPosY;
				ringYELLOW[0].x = float(rand() % 1000 + 64);
				respawnYellow += 1;
			}

			break;

		case RESULT:


			Novice::StopAudio(playPlayingHandle);

			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				playStartHandle = Novice::PlayAudio(startAudioHandle, false, 3.0f);
				gameScene = TITLE;
				gameTimer = resetTimer;
				player.position.x = resetPosition;

				playerProgressX = 990;
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
			Novice::DrawSprite(int(background[0].pos.x), int(background[0].pos.y), sea1, 1, 1, 0, WHITE);
			Novice::DrawSprite(int(background[1].pos.x), int(background[1].pos.y), sea1, 1, 1, 0, WHITE);
			if (gameTimer <= 120) {
				Novice::DrawSprite(170, 190, spaceText, 1.8f, 1.8f, 0, WHITE);
				Novice::DrawSprite(525, 200, deText, 1.4f, 1.4f, 0, WHITE);
				Novice::DrawSprite(690, 205, jumpText, 1.6f, 1.6f, 0, WHITE);
			}

			Novice::DrawSprite(1000, 10, progress, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(playerProgressX, playerProgressY, playerSwim6, 1.5, 1.5, 0.0f, WHITE);
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

			//自機
			Novice::DrawSprite(int(player.position.x) - int(player.radius), int(screenY) - int(player.radius), playerCurrentTexture, 3, 3, 0.0f, WHITE);
			Novice::ScreenPrintf(15, 15, "%f", player.position.y);
			Novice::ScreenPrintf(15, 30, "%d", gameTimer);
			Novice::ScreenPrintf(15, 45, "%d", playerState);

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