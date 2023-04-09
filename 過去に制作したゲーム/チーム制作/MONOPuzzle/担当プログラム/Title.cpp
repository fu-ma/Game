#include"Title.h"

Title::Title(ISceneChanger *changer) : BaseScene(changer) {
    cam._eye = { 0,3,-5 };
    cam._target = { 0,0,5 };
    cam._up = { 0,1,0 };
    cam.UpdateViewMat();

    testmodel[0].LoadObjModel("stageBlock1", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[1].LoadObjModel("stageBlock2", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[2].LoadObjModel("goal", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());

    //敵のモデル読み込み
    testmodel[3].LoadObjModel("enemy", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[4].LoadObjModel("enemy2", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());

    testmodel[6].LoadObjModel("coin", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[7].LoadObjModel("broken", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());

    player = new Player(&playerObj, &playerModel1, &playerModel2);

    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            mapBlock[y][x].InitObject3D(Raki_DX12B::Get()->GetDevice());
        }
    }

    Raki_LoadCSV::LoadCSVFileData(map, "csv/1.csv");

    NY_Object3D::SetObject3DManager(NY_Object3DManager::Get());

    PlayerParticle::Get()->Init();
    Sprite::SetSpriteManager(SpriteManager::Get());


    //スプライトリソース読み込み
    SpriteManager::Get()->LoadSpriteTexture(0, L"Resources/texture/title.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(1, L"Resources/texture/backGround.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(2, L"Resources/texture/0.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(3, L"Resources/texture/1.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(4, L"Resources/texture/2.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(5, L"Resources/texture/3.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(6, L"Resources/texture/4.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(7, L"Resources/texture/5.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(8, L"Resources/texture/6.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(9, L"Resources/texture/7.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(10, L"Resources/texture/8.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(11, L"Resources/texture/9.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(12, L"Resources/texture/select.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(13, L"Resources/texture/trouble.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(14, L"Resources/texture/+.png", Raki_DX12B::Get()->GetDevice());

    SpriteManager::Get()->LoadSpriteTexture(15, L"Resources/texture/star.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(16, L"Resources/texture/ministar.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(17, L"Resources/texture/setumei.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(18, L"Resources/texture/00.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(19, L"Resources/texture/11.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(20, L"Resources/texture/22.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(21, L"Resources/texture/33.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(22, L"Resources/texture/44.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(23, L"Resources/texture/55.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(24, L"Resources/texture/66.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(25, L"Resources/texture/77.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(26, L"Resources/texture/88.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(27, L"Resources/texture/99.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(28, L"Resources/texture/++.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(29, L"Resources/texture/trouble2.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(30, L"Resources/texture/-.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(31, L"Resources/texture/=.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(32, L"Resources/texture/Rady.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(33, L"Resources/texture/Go.png", Raki_DX12B::Get()->GetDevice());
    SpriteManager::Get()->LoadSpriteTexture(34, L"Resources/texture/waku.png", Raki_DX12B::Get()->GetDevice());

    sprite[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 0, true);
    sprite[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 1, true);
    sound = Audio::LoadSound_wav("Resources/music/title.wav");
    ok = Audio::LoadSound_wav("Resources/music/ok.wav");
}

//初期化
void Title::Initialize() {

    //このゲームのゲームスピード(ブロックの速度)
    gameSpeed = GAMESPEED;

    //stageLoad(map, 1);
    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            if (map[y][x] == 1)
            {
                NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
            }
            if (map[y][x] == 2)
            {
                NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
            }
            if (map[y][x] == 3)
            {
                NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[6]);
            }
            if (map[y][x] == 4)
            {
                //壊せるブロックの差別化
                NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[7]);
            }
        }
    }
    //playerのモデル読み込み
    player->Initialize(Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());

    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            mapBlock[(LOAD_HEIGHT - 1) - y][x].position = { (float)x * BLOCK_SIZE BACKBLOCK,(float)y * BLOCK_SIZE - BLOCK_SIZE * 10,10 };
            drawFlag[y][x] = false;
        }
    }

    cam._eye = { 0,0,20 };
    cam._target = { 0,0,10 };
    cam._up = { 0,1,0 };
    Audio::volume = TITILEVOL;
    Audio::SetPlayRoopmode(sound,255);
    Audio::PlayLoadedSound(sound);

}

//更新
void Title::Update() {
    if (KeyInput::isKeyTrigger(DIK_SPACE) == true)
    {
        Audio::PlayLoadedSound(ok);
        Audio::StopLoadedSound(sound);
        mSceneChanger->ChangeScene(eScene_Game);
    }
    if (KeyInput::isKeyTrigger(DIK_R) == true)
    {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                BaseScene::Get()->cleaFlag[i][j] = false;
            }
        }
    }

    PlayerParticle::Get()->Update(player->GetPosition(), 2, 45,20, vec_center, color_black, cam._matView);

    //cam.UpdateViewMat();

    //更新
    player->moveUpdate();
    player->SetJump(0);

    //ステージループ
    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            if (x == 0 && mapBlock[y][x].position.x <= BACKBLOCK)
            {
                mapBlock[y][x].position.x = mapBlock[y][LOAD_WIDTH - 1].position.x + BLOCK_SIZE;
            }
            else if (mapBlock[y][x].position.x <= BACKBLOCK)
            {
                mapBlock[y][x].position.x = mapBlock[y][x - 1].position.x + BLOCK_SIZE;
            }
            mapBlock[y][x].position.x -= gameSpeed;
        }
    }

    //当たり判定
    //下のブロック
    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {

            if (Hit(player->GetPosition(), mapBlock[y][x].position, 1) == true &&
                player->GetCount() == 0 &&
                drawFlag[y][x] == false)
            {
                player->SetRoll(5);
                //壁だったら回転を止める
                if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                    mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                {
                    player->rotation0();
                }

                //ちょっと浮かせる
                if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                    mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                {
                    player->SetPositionY(mapBlock[y][x].position.y + 4.000000001);
                    //player->SetJump(0);
                    break;
                }
            }
            if (Hit(player->GetPosition(), mapBlock[y][x].position, 1) == true &&
                player->GetCount() == 1 &&
                drawFlag[y][x] == false)
            {
                player->SetRoll(-5);
                //壁だったら回転を止める
                if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                    mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                {
                    player->rotation0();
                }

                //ちょっと浮かせる
                if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                    mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                {
                    player->SetPositionY(mapBlock[y][x].position.y - 3.999999999);
                    break;
                }
            }
        }
    }

    if (player->GetJump() < 0)
    {
        player->count = 0;
    }
    if (player->GetJump() > 0)
    {
        player->count = 1;
    }

    cam.UpdateFollowingOnlyZVer2({ player->GetPosX() + 30,8,player->GetPosZ() }, { 0,0,CAMDISTANCE }, 0);
    //オブジェクト更新
    player->objUpdate(cam._matView);
    //NY_Object3D::UpdateObject3D(&Player, cam1._matView);
    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            NY_Object3D::UpdateObject3D(&mapBlock[y][x], cam._matView);
        }
    }
    for (int i = 0; i < MAX_SPRITE; i++)
    {
        sprite[i].UpdateSprite();
    }

}

//描画
void Title::Draw() {

    Raki_DX12B::Get()->StartDraw();

    SpriteManager::Get()->SetCommonBeginDraw(Raki_DX12B::Get()->GetGCommandList());
    sprite[1].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    NY_Object3DManager::Get()->SetCommonBeginDrawObject3D(Raki_DX12B::Get()->GetGCommandList());

    PlayerParticle::Get()->Draw();
    //player
    player->objDraw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            if ((mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                mapBlock[y][x].model.material.texFileName == "stageBlock2.png" ||
                mapBlock[y][x].model.material.texFileName == "coin.png" ||
                mapBlock[y][x].model.material.texFileName == "broken.png") &&
                drawFlag[y][x] == false)
            {
                NY_Object3D::DrawModel3D(&mapBlock[y][x], Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
            }
        }
    }

    SpriteManager::Get()->SetCommonBeginDraw(Raki_DX12B::Get()->GetGCommandList());
    sprite[0].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());


    Raki_DX12B::Get()->EndDraw();
}