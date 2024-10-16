#pragma once

#include "Model.h"
#include "WorldTransform.h"

class Enemy {
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

private:
	// モデル
	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};

