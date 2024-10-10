#include <cassert>
#include "Player.h"
#include "Input.h"
#include "MathUtilityForText.h"

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	//NULLポインタチャック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録
	model_ = model;
	viewProjection_ = viewProjection;

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Player::Update()
{
	//移動入力
	InputMove();

	//弾を撃つ

	
	//行列計算
	worldTransform_.UpdateMatrix();
}

void Player::Draw()
{
	//3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}

//自動移動
void Player::InputMove() {
	//上に上昇
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		velocity_ = {0.0f, 0.2f, 0.0f};
	} else {
		velocity_ = {0.0f, -0.2f, 0.0f};
	}
	worldTransform_.translation_ += velocity_;
}

//弾を撃つ
void Player::BulletShot() {}
