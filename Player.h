#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"
#include "MathUtilityForText.h"

class Enemy;

class Player{
public:
	/// </summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

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

	//移動範囲
	void MoveRange();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//AABBを取得
	AABB GetAABB();

	PlayerBullet* GetBullet() { return bullet_; }

	//衝突判定
	void OnCollision(const Enemy* enemy);

private:
	// モデル
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_ = {};

	//弾
	PlayerBullet* bullet_ = nullptr;
	//弾のフラグ
	bool isBulletShot_ = false;

	//キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	//デスフラグ
	bool isDead_ = false;
};

