#include <cassert>
#include "PlayerBullet.h"
#include "Player.h"
#include "TextureManager.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	model_ = Model::CreateFromOBJ("player", true);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	worldTransform_.translation_.x += 1.0f;

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//ワールド座標を取得
Vector3 PlayerBullet::GetWorldPosition() const { 
	// ワールド座標を入れる変数
	Vector3 worldPos = {};
	// ワールド行列の平行移動成文を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//AABBを取得
AABB PlayerBullet::GetAABB() const {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb = {};

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

//衝突判定
void PlayerBullet::OnCollision(const Player* player) {
	(void)player;
	//当たったら死ぬ
	isDead_ = true;
}