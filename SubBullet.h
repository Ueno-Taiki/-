#pragma once

#include "Model.h"
#include "WorldTransform.h"

class SubBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	const float GetPositon() const { return worldTransform_.translation_.x; }

	// 弾
	
	static const int32_t kLifeTime = 60 * 2;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
