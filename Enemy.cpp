#include <cassert>
#include "Enemy.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	//NULLポインタチャック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	viewProjection_ = viewProjection;

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Enemy::Update()
{
	//行列計算
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
