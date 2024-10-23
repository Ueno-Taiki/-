#include "GameScene.h"
#include "TextureManager.h"
#include "MathUtilityForText.h"
#include "PlayerBullet.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dモデル解放
	delete model_;
	delete player_;
	delete modelSkydome_;
	delete modelPlayer_life2_;
	delete modelPlayer_life1_;
	delete modelPlayer_life0_;
	delete item_;
	delete modelItem;
	delete subBullet_;
	delete modelSubBullet_;

	// 敵削除
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//3Dモデルデータの生成
	model_ = Model::Create();
	modelPlayer_life2_ = Model::CreateFromOBJ("player_life2", true);
	modelPlayer_life1_ = Model::CreateFromOBJ("player_life1", true);
	modelPlayer_life0_ = Model::CreateFromOBJ("player_life0", true);
	modelEnemy_ = Model::CreateFromOBJ("player", true);
	modelItem = Model::CreateFromOBJ("Item", true);
	modelAssist_ = Model::CreateFromOBJ("assist", true);
	modelSkydome_ = Model::CreateFromOBJ("SkyDome", true);

	//天球を生成
	skydome_ = new Skydome();
	//天球の初期化
	skydome_->Initialize(modelSkydome_, textureHandle_, &viewProjection_);

	//自キャラの生成
	player_ = new Player();
	//自キャラの座標
	Vector3 playerPosition = {-30, 0, 0};
	//自キャラの初期化
	player_->Initialize(modelPlayer_life2_, modelPlayer_life1_, modelPlayer_life0_, modelAssist_, &viewProjection_, playerPosition);

	for (int32_t i = 0; i < MAX; ++i) {
		//敵キャラの生成
		Enemy* newEnemy = new Enemy();
		//敵キャラの座標
		Vector3 enemyPosition = enemyPostion_[i];
		//敵キャラの初期化
		newEnemy->Initialize(modelEnemy_, &viewProjection_, enemyPosition);

		enemies_.push_back(newEnemy);
	}

	//アイテムの生成
	item_ = new Item();
	//アイテムの座標
	Vector3 itemPosition = {30, 0, 0};
	//アイテムの初期化
	item_->Initialize(modelItem, &viewProjection_, itemPosition);

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {
	switch (phase_) {
	case Phase::kPlay:
		// 自キャラの更新
		player_->Update();

		// 敵の更新
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		enemies_.remove_if([](Enemy* enemy) {
			if (enemy->isDead()) {
				delete enemy;
				return true;
			}
			return false;
		});

		//アイテムの更新
		item_->Update();

		// 全ての当たり判定を行う
		CheckAllCollisions();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	switch (phase_) {
	case Phase::kPlay:
		// 自キャラの描画
		player_->Draw();

		break;

	case Phase::kDeath:

		break;
	}

	//敵キャラの描画
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	//アイテムの描画
	item_->Draw();

	//天球の描画
	skydome_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

//衝突判定
void GameScene::CheckAllCollisions() {
#pragma region 自キャラと敵キャラの当たり判定

	{
		//判定対象1と2の座標
		AABB aabb1, aabb2;

		//自キャラの座標
		aabb1 = player_->GetAABB();

		// 自キャラと敵キャラの当たり判定
		for (Enemy* enemy : enemies_) {
			// 敵の座標
			aabb2 = enemy->GetAABB();

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				//自キャラの衝突時コールバックを呼び出す
				player_->OnCollision(enemy);
				//敵の衝突時コールバックを呼び出す
				enemy->OnCollision(player_);
			}
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定

	{
		// 判定対象1と2の座標
		AABB aabb1, aabb2;

		PlayerBullet* playerbullet = player_->GetBullet();

		// 自弾の座標
		aabb1 = playerbullet->GetAABB();

		// 自キャラと敵キャラの当たり判定
		for (Enemy* enemy : enemies_) {
			// 敵の座標
			aabb2 = enemy->GetAABB();

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2)) {
				// 自弾の衝突時コールバックを呼び出す
				playerbullet->OnCollision(player_);
				// 敵の衝突時コールバックを呼び出す
				enemy->OnCollision(player_);
			}
		}
	}
#pragma endregion
}
