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
#include "Item.h"
#include "SubBullet.h"
#include "Skydome.h"

enum class Phase {
	kPlay,
	kDeath
};

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

	bool IsFinished() const { return finished_; }

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
	Model* modelPlayer_life2_ = nullptr;
	Model* modelPlayer_life1_ = nullptr;
	Model* modelPlayer_life0_ = nullptr;

	//アイテム
	Item* item_ = nullptr;
	//アイテムの3Dモデル
	Model* modelItem = nullptr;
	//アイテムフラグ
	bool isGetItem_ = false;

	SubBullet* subBullet_ = nullptr;
	Model* modelSubBullet_ = nullptr;

	Player* assist_ = nullptr;
	Model* modelAssist_ = nullptr;

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

	//天球
	Skydome* skydome_ = nullptr;
	//天球の3Dモデル
	Model* modelSkydome_ = nullptr;

	bool finished_ = false;

	Phase phase_;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
