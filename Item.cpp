#include "Item.h"
#include <cassert>
#include "Input.h"
#include "MathUtilityForText.h"

void Item::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) 
{
	// NULLポインタチャック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録
	model_ = model;

	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Item::Update() {
	// 敵移動
	worldTransform_.translation_.x -= Speed;
	// 行列計算
	worldTransform_.UpdateMatrix();
}

void Item::Draw() {
	model_->Draw(worldTransform_, *viewProjection_);
}
