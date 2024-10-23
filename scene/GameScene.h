#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//衝突判定
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// 3Dモデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//自キャラ
	Player* player_ = nullptr;
	//自キャラの3Dモデル
	Model* modelPlayer_ = nullptr;

	//敵の数
	static inline const int MAX = 10;
	//敵キャラ
	std::list<Enemy*> enemies_;
	//敵の位置
	Vector3 enemyPostion_[MAX] = {
	    {30.0f, 0.0f, 0.0f},
        {25.0f, 1.0f, 0.0f},
        {25.0f, 2.0f, 0.0f},
        {0.0f,  0.0f, 0.0f},
        {0.0f,  0.0f, 0.0f},
	    {0.0f,  0.0f, 0.0f},
        {0.0f,  0.0f, 0.0f},
        {0.0f,  0.0f, 0.0f},
        {0.0f,  0.0f, 0.0f},
        {0.0f,  0.0f, 0.0f}
    };
	//敵キャラの3Dモデル
	Model* modelEnemy_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	//弾のフラグ
	bool isBulletShot_ = true;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
