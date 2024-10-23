#include "SubBullet.h"
#include <cassert>
#include "Player.h"
#include "TextureManager.h"

void SubBullet::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	model_ = Model::CreateFromOBJ("player", true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

}

void SubBullet::Update() {
	worldTransform_.translation_.x += 1.0f;

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void SubBullet::Draw(const ViewProjection& viewProjection) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
