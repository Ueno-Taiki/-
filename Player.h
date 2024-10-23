#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"
#include "SubBullet.h"
#include "MathUtilityForText.h"
#include <list>

class Enemy;

class Player{
public:
	/// </summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model1, Model* model2, Model* model3, Model* model4, ViewProjection* viewProjection, const Vector3& position);

	/// </summary>
	/// 初期化
	/// </summary>
	void Update();

	/// </summary>
	/// 初期化
	/// </summary>
	void Draw();

	// 移動入力
	void InputMove();

	//攻撃
	void Attack();

	//複数弾
	void SubAttack();

	//ダメージ
	void Damage();

	//移動範囲
	void MoveRange();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//AABBを取得
	AABB GetAABB();

	PlayerBullet* GetBullet() { return bullet_; }

	//衝突判定
	void OnCollision(const Enemy* enemy);

	int playerLife = 2;
	int damage = 1;

	static const int kAttackInterval = 60;

private:
	// モデル
	Model* model_ = nullptr;
	Model* model1_ = nullptr;
	Model* model2_ = nullptr;
	Model* model3_ = nullptr;
	Model* model4_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_ = {};

	//弾
	std::list<PlayerBullet*> bullets_;
	PlayerBullet* bullet_ = nullptr;
	SubBullet* subBullet_ = nullptr;
	//弾のフラグ
	bool isBulletShot_ = false;
	bool isSubBulletShot_ = false;

	//アイテムフラグ
	bool isGetItem_ = false;

	//発射タイマー
	int32_t AttackTimer_ = 0;

	//キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	//デスフラグ
	bool isDead_ = false;
};

