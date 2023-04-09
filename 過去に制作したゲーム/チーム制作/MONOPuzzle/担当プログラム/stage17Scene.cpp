#include "stage17Scene.h"

stage17::stage17(ISceneChanger *changer) : BaseScene(changer) {
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
    testmodel[5].LoadObjModel("coinframe", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[6].LoadObjModel("coin", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[7].LoadObjModel("broken", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[8].LoadObjModel("transBlock", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());
    testmodel[9].LoadObjModel("frame", Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());

    player = new Player(&playerObj, &playerModel1, &playerModel2);

    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            mapBlock[y][x].InitObject3D(Raki_DX12B::Get()->GetDevice());
        }
    }

    Raki_LoadCSV::LoadCSVFileData(map, "csv/17.csv");
    //stageLoad(map, 1);

    NY_Object3D::SetObject3DManager(NY_Object3DManager::Get());

    sprite.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 1, true);
    trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 2, true);
    trouble[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 2, true);
    trouble[2].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 13, true);
    trouble[3].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 14, true);

    trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 18, true);
    trouble2[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 18, true);
    trouble2[2].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 29, true);
    trouble2[3].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 28, true);

    //結果
    trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 2, true);
    trouble3[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 2, true);
    trouble3[2].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 13, true);
    trouble3[3].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 14, true);

    saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 2, true);
    saisyoutedayo[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 13, true);
    waku.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 34, true);

    hikizan.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 30, true);
    ikoru.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 31, true);
    score[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0.5,0.5 }, 15, true);
    score[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0.5,0.5 }, 15, true);
    score[2].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0.5,0.5 }, 15, true);
    sound = Audio::LoadSound_wav("Resources/music/bgm.wav");
    esc = Audio::LoadSound_wav("Resources/music/esc.wav");
    coin = Audio::LoadSound_wav("Resources/music/coin.wav");
    bigJump = Audio::LoadSound_wav("Resources/music/big.wav");
    smallJump = Audio::LoadSound_wav("Resources/music/small.wav");
    star = Audio::LoadSound_wav("Resources/music/score.wav");
    result = Audio::LoadSound_wav("Resources/music/result.wav");
    blockBreak = Audio::LoadSound_wav("Resources/music/blockBreak.wav");

    Rady.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 32, true);
    Go.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 33, true);

    PlayerParticle::Get()->Init();
    BoomParticle::Get()->Init();
}

//初期化
void stage17::Initialize() {

    //このゲームのゲームスピード(ブロックの速度)
    gameSpeed = GAMESPEED;
    count = 0;
    coinCount = 0;
    coinframCount = 0;
    troubleCount = 0;
    nannteCount = 0;

    troubleCount2 = 0;
    nannteCount2 = 0;

    troubleCount3 = 0;
    nannteCount3 = 0;

    troubleCount4 = speedClea;

    waitCount = 0;
    numCount = 2;
    //最初透明になるかならないか
    transCount = 0;
    if (troubleCount == 0)
    {
        troubleFlag[0] = false;
        troubleFlag[1] = false;
    }

    if (troubleCount == 0)
    {
        troubleFlag2[0] = false;
        troubleFlag2[1] = false;
    }

    if (troubleCount3 == 0)
    {
        troubleFlag3[0] = false;
        troubleFlag3[1] = false;
    }


    gameStopFlag = false;
    cleaFlag = false;

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
                if (coinframCount % 2 == 0)
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[6]);
                }
                if (coinframCount % 2 == 1)
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[5]);
                }
                coinCount++;
            }
            if (map[y][x] == 4)
            {
                //壊せるブロックの差別化
                NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[7]);
            }
            if (map[y][x] == 5)
            {
                //切り替えブロック
                if (transCount % 2 == 0)
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[8]);
                }
                if (transCount % 2 == 1)
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[9]);
                }
            }
        }
    }

    //playerのモデル読み込み
    player->Initialize(Raki_DX12B::Get()->GetDevice(), NY_Object3DManager::Get());


    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            mapBlock[(LOAD_HEIGHT - 1) - y][x].position = { (float)x * BLOCK_SIZE BACKBLOCK + (float)GAMESPEED,(float)y * BLOCK_SIZE - BLOCK_SIZE * 10,10 };
            drawFlag[y][x] = false;
        }
    }

    cam._eye = { 0,0,20 };
    cam._target = { 0,0,10 };
    cam._up = { 0,1,0 };
    trouble[0].spdata.position = { 32,70,0 };
    trouble[1].spdata.position = { 64,70,0 };
    trouble[2].spdata.position = { 120,70,0 };
    trouble[3].spdata.position = { 0,70,0 };
    trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount, true);
    trouble[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount, true);

    trouble2[0].spdata.position = { 32,130,0 };
    trouble2[1].spdata.position = { 64,130,0 };
    trouble2[2].spdata.position = { 120,130,0 };
    trouble2[3].spdata.position = { 0,130,0 };
    trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16, true);
    trouble2[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16, true);

    trouble3[0].spdata.position = { 908,150,0 };
    trouble3[1].spdata.position = { 940,150,0 };
    trouble3[2].spdata.position = { 996,150,0 };
    trouble3[3].spdata.position = { 876,150,0 };
    trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount, true);
    trouble3[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount, true);

    saisyoutedayo[0].spdata.position = { 1035,75,0 };
    saisyoutedayo[1].spdata.position = { 1095,75,0 };

    saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 2, true);
    saisyoutedayo[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 13, true);

    waku.CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, 34, true);
    waku.spdata.position = { 1025,62,0 };

    hikizan.spdata.position = { 500,200,0 };

    ikoru.spdata.position = { 760,200,0 };


    score[0].spdata.position = { -400,360,0 };
    score[1].spdata.position = { -300,360,0 };
    score[2].spdata.position = { -200,360,0 };
    Audio::volume = GAMEVOL;
    Audio::SetPlayRoopmode(sound, 255);
    Audio::PlayLoadedSound(sound);
}

//更新
void stage17::Update() {
    if (KeyInput::isKeyTrigger(DIK_ESCAPE) == true)
    {
        mSceneChanger->ChangeScene(eScene_Game);
        Audio::StopLoadedSound(sound);
        Audio::PlayLoadedSound(esc);
    }

    //cam.UpdateViewMat();
    //更新
    count++;
    if (count > 180)
    {
        PlayerParticle::Get()->Update(player->GetPosition(), 2, 45, 20, vec_center, color_black, cam._matView);

        if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == false && coinCount != 0)
        {
            transCount++;
            troubleCount++;
            nannteCount++;
            troubleCount2++;
            nannteCount2++;
            troubleCount3++;
            nannteCount3++;
        }
        if (coinCount <= 0)
        {
            waitCount++;
            if (waitCount > 10)
            {
                trouble[0].spdata.position = { 340 - 40,150,0 };
                trouble[1].spdata.position = { 372 - 40,150,0 };
                trouble[2].spdata.position = { 428 - 40,150,0 };
                trouble[3].spdata.position = { 308 - 40,150,0 };
                hikizan.spdata.position = { 540 - 40,150,0 };
                trouble2[0].spdata.position = { 640 - 40,150,0 };
                trouble2[1].spdata.position = { 672 - 40,150,0 };
                trouble2[2].spdata.position = { 722 - 40,150,0 };
                trouble2[3].spdata.position = { 600 - 40,150,0 };
                ikoru.spdata.position = { 812 - 40,150,0 };
                trouble3[0].spdata.position = { 908 - 40,150,0 };
                trouble3[1].spdata.position = { 940 - 40,150,0 };
                trouble3[2].spdata.position = { 996 - 40,150,0 };
                trouble3[3].spdata.position = { 876 - 40,150,0 };
            }
            if (waitCount > 150)
            {
                gameStopFlag = true;
                score[0].spdata.rotation += 3;
                score[1].spdata.rotation += 3;
                score[2].spdata.rotation += 3;
                score[0].spdata.position.x += 5;
                score[1].spdata.position.x += 5;
                score[2].spdata.position.x += 5;
            }
        }
        if (score[2].spdata.position.x == 340 && troubleCount - troubleCount2 <= speedClea)
        {
            Audio::PlayLoadedSound(star);
        }
        if (score[1].spdata.position.x == 640 && troubleCount - troubleCount2 <= speedClea)
        {
            Audio::PlayLoadedSound(star);
        }
        if (score[0].spdata.position.x == 940 && troubleCount - troubleCount2 <= speedClea)
        {
            Audio::PlayLoadedSound(star);
            Audio::PlayLoadedSound(result);
        }
        if (score[2].spdata.position.x == 340 && troubleCount - troubleCount2 <= normalClea && troubleCount - troubleCount2 > speedClea)
        {
            Audio::PlayLoadedSound(star);
        }
        if (score[1].spdata.position.x == 640 && troubleCount - troubleCount2 <= normalClea && troubleCount - troubleCount2 > speedClea)
        {
            Audio::PlayLoadedSound(star);
        }
        if (score[2].spdata.position.x == 340 && troubleCount - troubleCount2 > normalClea)
        {
            Audio::PlayLoadedSound(star);
        }


        //最速クリア
        if (troubleCount - troubleCount2 <= speedClea)
        {
            if (score[2].spdata.position.x > 340)
            {

                score[2].spdata.position.x = 340;
                score[2].spdata.rotation = 0;
            }
            if (score[1].spdata.position.x > 640)
            {

                score[1].spdata.position.x = 640;
                score[1].spdata.rotation = 0;
            }
            if (score[0].spdata.position.x > 940)
            {

                score[0].spdata.position.x = 940;
                score[0].spdata.rotation = 0;
                cleaFlag = true;
            }

            if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == true)
            {
                BaseScene::Get()->cleaFlag[16][0] = true;
                BaseScene::Get()->cleaFlag[16][1] = true;
                BaseScene::Get()->cleaFlag[16][2] = true;

                Audio::PlayLoadedSound(result);

                score[2].spdata.position.x = 340;
                score[1].spdata.position.x = 640;
                score[0].spdata.position.x = 940;
            }
        }
        else if (troubleCount - troubleCount2 <= normalClea)
        {
            if (score[2].spdata.position.x > 340)
            {

                score[2].spdata.position.x = 340;
                score[2].spdata.rotation = 0;
            }
            if (score[1].spdata.position.x > 640)
            {

                score[1].spdata.position.x = 640;
                score[1].spdata.rotation = 0;
                cleaFlag = true;
            }

            if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == true)
            {
                BaseScene::Get()->cleaFlag[16][0] = true;
                BaseScene::Get()->cleaFlag[16][1] = true;
                Audio::PlayLoadedSound(star);
                score[2].spdata.position.x = 340;
                score[1].spdata.position.x = 640;
                score[0].spdata.position.x = 2000;
            }
        }
        else
        {
            if (score[2].spdata.position.x > 340)
            {

                score[2].spdata.position.x = 340;
                score[2].spdata.rotation = 0;
                cleaFlag = true;
            }

            if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == true)
            {
                BaseScene::Get()->cleaFlag[16][0] = true;
                Audio::PlayLoadedSound(star);
                score[2].spdata.position.x = 340;
                score[1].spdata.position.x = 2000;
                score[0].spdata.position.x = 2000;
            }
        }
        if (KeyInput::isKeyTrigger(DIK_SPACE) == true && cleaFlag == true)
        {
            Audio::StopLoadedSound(result);
            Audio::StopLoadedSound(star);
            mSceneChanger->ChangeScene(eScene_Game);
            Audio::StopLoadedSound(sound);
        }


        if (gameStopFlag == false && coinCount != 0)
        {
            player->moveUpdate();
        }

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
                if (gameStopFlag == false)
                {
                    mapBlock[y][x].position.x -= gameSpeed;
                }
            }
        }

        //当たり判定
        //下のブロック
        for (int y = 0; y < LOAD_HEIGHT; y++)
        {
            for (int x = 0; x < LOAD_WIDTH; x++)
            {
                if (mapBlock[y][x].model.material.texFileName == "frame.png" &&
                    transCount % 2 == 0)
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[8]);
                }

                if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                    transCount % 2 == 1)
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[9]);
                }


                if (coinframCount % 2 == 0 && mapBlock[y][x].model.material.texFileName == "coinframe.png")
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[6]);
                }
                if (coinframCount % 2 == 1 && mapBlock[y][x].model.material.texFileName == "coin.png")
                {
                    NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[5]);
                }

                //コインに当たった時
                if (Hit(player->GetPosition(), mapBlock[y][x].position, 2) == true &&
                    drawFlag[y][x] == false && mapBlock[y][x].model.material.texFileName == "coin.png" &&
                    (player->GetJump() == -3 || player->GetJump() == 3))
                {
                    coinCount--;
                    BoomParticle::Get()->Spawn(player->GetPosition(), 2, 1, 15);
                    Audio::StopLoadedSound(coin);
                    Audio::PlayLoadedSound(coin);
                    drawFlag[y][x] = true;
                }

                if (Hit(player->GetPosition(), mapBlock[y][x].position, 1) == true &&
                    player->GetCount() == 0 &&
                    drawFlag[y][x] == false)
                {
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                    {
                        coinframCount = 0;
                    }
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock2.png" ||
                        mapBlock[y][x].model.material.texFileName == "transBlock.png")
                    {
                        coinframCount = 1;
                    }

                    player->SetRoll(5);
                    //壁だったら回転を止める
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                        mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                    {
                        player->rotation0();
                        player->SetJump(-0.5);
                    }

                    //壊れるブロックでかつスピードが遅い時
                    if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                        player->GetJump() == -0.5)
                    {
                        player->rotation0();
                    }

                    if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                        transCount % 2 == 0)
                    {
                        player->rotation0();
                        player->SetJump(-0.5);
                    }

                    if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == false)
                    {
                        if (x == 0 && mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                        {
                            if (map[y][LOAD_WIDTH - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][LOAD_WIDTH - 1], testmodel[1]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[1]);
                            }
                            player->SetJump(3);
                            Audio::PlayLoadedSound(bigJump);
                            player->count++;
                        }
                        else if (x == LOAD_WIDTH - 1 && mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[1]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
                            if (map[y][0] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][0], testmodel[1]);
                            }
                            player->SetJump(3);
                            Audio::PlayLoadedSound(bigJump);
                            player->count++;
                        }
                        else if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[1]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[1]);
                            }
                            player->SetJump(3);
                            Audio::PlayLoadedSound(bigJump);
                            player->count++;
                        }
                        else if (x == 0 && mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                        {
                            if (map[y][LOAD_WIDTH - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][LOAD_WIDTH - 1], testmodel[0]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[0]);
                            }
                            player->SetJump(0.5);
                            Audio::PlayLoadedSound(smallJump);

                            player->count++;
                        }
                        else if (x == LOAD_WIDTH - 1 && mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[0]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
                            if (map[y][0] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][0], testmodel[0]);
                            }
                            player->SetJump(0.5);
                            Audio::PlayLoadedSound(smallJump);
                            player->count++;
                        }
                        else if (mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[0]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[0]);
                            }
                            player->SetJump(0.5);
                            Audio::PlayLoadedSound(smallJump);
                            player->count++;
                        }
                        if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                            transCount % 2 == 0)
                        {
                            transCount++;
                            player->SetJump(0.5);
                            Audio::PlayLoadedSound(smallJump);
                        }
                        if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                            player->GetJump() == 0.5)
                        {
                            player->SetPositionY(mapBlock[y][x].position.y - 4);
                        }
                    }
                    //壊れるブロック壊す
                    if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                        player->GetJump() == -3)
                    {
                        Audio::StopLoadedSound(blockBreak);
                        Audio::PlayLoadedSound(blockBreak);
                        BoomParticle::Get()->Spawn(player->GetPosition(), 2, 1, 15);
                        if (x == 0)
                        {
                            if (mapBlock[y][LOAD_WIDTH - 1].model.material.texFileName == "broken.png")
                            {
                                drawFlag[y][LOAD_WIDTH - 1] = true;
                            }
                            drawFlag[y][x] = true;
                        }
                        else if (x == LOAD_WIDTH - 1)
                        {
                            if (mapBlock[y][x - 1].model.material.texFileName == "broken.png")
                            {
                                drawFlag[y][x - 1] = true;
                            }
                            drawFlag[y][x] = true;
                        }
                        else
                        {
                            if (mapBlock[y][x - 1].model.material.texFileName == "broken.png")
                            {
                                drawFlag[y][x - 1] = true;
                            }
                            drawFlag[y][x] = true;
                        }
                    }

                    //ちょっと浮かせる
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                        mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                    {
                        player->SetPositionY(mapBlock[y][x].position.y + 4.000000001);
                        //player->SetJump(0);
                        break;
                    }

                    //ちょっと浮かせる壊れるバージョン
                    if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                        player->GetJump() == -0.5)
                    {
                        player->SetPositionY(mapBlock[y][x].position.y + 4.000000001);
                        break;
                    }

                    if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                        transCount % 2 == 0)
                    {
                        player->SetPositionY(mapBlock[y][x].position.y + 4.000000001);
                        break;
                    }
                }

                if (Hit(player->GetPosition(), mapBlock[y][x].position, 1) == true &&
                    player->GetCount() == 1 &&
                    drawFlag[y][x] == false)
                {
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                    {
                        coinframCount = 0;
                    }
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock2.png" ||
                        mapBlock[y][x].model.material.texFileName == "transBlock.png")
                    {
                        coinframCount = 1;
                    }

                    player->SetRoll(-5);
                    //壁だったら回転を止める
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                        mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                    {
                        player->rotation0();
                        player->SetJump(0.5);
                    }

                    //壊れるブロックでかつスピードが遅い時
                    if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                        player->GetJump() == 0.5)
                    {
                        player->rotation0();
                    }

                    if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                        transCount % 2 == 0)
                    {
                        player->rotation0();
                        player->SetJump(0.5);
                    }

                    if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == false)
                    {
                        if (x == 0 && mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                        {
                            if (map[y][LOAD_WIDTH - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][LOAD_WIDTH - 1], testmodel[1]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[1]);
                            }
                            player->SetJump(-3);
                            Audio::PlayLoadedSound(bigJump);
                            player->count++;
                        }
                        else if (x == LOAD_WIDTH - 1 && mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[1]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
                            if (map[y][0] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][0], testmodel[1]);
                            }
                            player->SetJump(-3);
                            Audio::PlayLoadedSound(bigJump);
                            player->count++;
                        }
                        else if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[1]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[1]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[1]);
                            }
                            player->SetJump(-3);
                            Audio::PlayLoadedSound(bigJump);
                            player->count++;
                        }
                        else if (x == 0 && mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                        {
                            if (map[y][LOAD_WIDTH - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][LOAD_WIDTH - 1], testmodel[0]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[0]);
                            }
                            player->SetJump(-0.5);
                            Audio::PlayLoadedSound(smallJump);
                            player->count++;
                        }
                        else if (x == LOAD_WIDTH - 1 && mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[0]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
                            if (map[y][0] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][0], testmodel[0]);
                            }
                            player->SetJump(-0.5);
                            Audio::PlayLoadedSound(smallJump);
                            player->count++;
                        }
                        else if (mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                        {
                            if (map[y][x - 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x - 1], testmodel[0]);
                            }
                            NY_Object3D::SetLoadedModelData(&mapBlock[y][x], testmodel[0]);
                            if (map[y][x + 1] != 0)
                            {
                                NY_Object3D::SetLoadedModelData(&mapBlock[y][x + 1], testmodel[0]);
                            }
                            player->SetJump(-0.5);
                            Audio::PlayLoadedSound(smallJump);
                            player->count++;
                        }
                        if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                            transCount % 2 == 0)
                        {
                            transCount++;
                            player->SetJump(-0.5);
                            Audio::PlayLoadedSound(smallJump);
                        }
                        if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                            player->GetJump() == -0.5)
                        {
                            player->SetPositionY(mapBlock[y][x].position.y + 4);
                        }
                    }
                    //壊れるブロック壊す
                    if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                        player->GetJump() == 3)
                    {
                        Audio::StopLoadedSound(blockBreak);
                        Audio::PlayLoadedSound(blockBreak);
                        BoomParticle::Get()->Spawn(player->GetPosition(), 2, 1, 15);
                        if (x == 0)
                        {
                            if (mapBlock[y][LOAD_WIDTH - 1].model.material.texFileName == "broken.png")
                            {
                                drawFlag[y][LOAD_WIDTH - 1] = true;
                            }
                            drawFlag[y][x] = true;
                        }
                        else if (x == LOAD_WIDTH - 1)
                        {
                            if (mapBlock[y][x - 1].model.material.texFileName == "broken.png")
                            {
                                drawFlag[y][x - 1] = true;
                            }
                            drawFlag[y][x] = true;
                        }
                        else
                        {
                            if (mapBlock[y][x - 1].model.material.texFileName == "broken.png")
                            {
                                drawFlag[y][x - 1] = true;
                            }
                            drawFlag[y][x] = true;
                        }
                    }

                    //ちょっと浮かせる
                    if (mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                        mapBlock[y][x].model.material.texFileName == "stageBlock2.png")
                    {
                        player->SetPositionY(mapBlock[y][x].position.y - 3.999999999);
                        break;
                    }
                    //ちょっと浮かせる壊れるバージョン
                    if (mapBlock[y][x].model.material.texFileName == "broken.png" &&
                        player->GetJump() == 0.5)
                    {
                        player->SetPositionY(mapBlock[y][x].position.y - 3.999999999);
                        break;
                    }
                    if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                        transCount % 2 == 0)
                    {
                        player->SetPositionY(mapBlock[y][x].position.y - 3.999999999);
                        break;
                    }

                }
            }
        }

        if (KeyInput::isKeyTrigger(DIK_SPACE) == true && gameStopFlag == false && coinCount != 0)
        {
            if (player->GetJump() == 3 || player->GetJump() == -3)
            {
                troubleCount2--;
                nannteCount2--;
                Audio::PlayLoadedSound(bigJump);
            }
            else if (player->GetJump() == 0.5 || player->GetJump() == -0.5)
            {
                troubleCount3--;
                nannteCount3--;
                Audio::PlayLoadedSound(smallJump);
            }
        }


        if (troubleCount > 0)
        {
            if (troubleCount < 10 || (troubleCount > 10 && troubleCount < 20) || (troubleCount > 20 && troubleCount < 30) ||
                (troubleCount > 30 && troubleCount < 40) || (troubleCount > 40 && troubleCount < 50) || (troubleCount > 50 && troubleCount < 60) ||
                (troubleCount > 60 && troubleCount < 70) || (troubleCount > 70 && troubleCount < 80) || (troubleCount > 80 && troubleCount < 90) ||
                (troubleCount > 90 && troubleCount < 100))
            {
                trouble[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + nannteCount, true);
            }
            if (troubleCount == 10 || troubleCount == 20 || troubleCount == 30 || troubleCount == 40 || troubleCount == 50 ||
                troubleCount == 60 || troubleCount == 70 || troubleCount == 80 || troubleCount == 90)
            {
                trouble[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount, true);
                nannteCount = 0;
            }
            if (troubleCount == 10)
            {
                troubleFlag[0] = true;
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 1, true);
            }
            if (troubleCount == 20)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 2, true);
            }
            if (troubleCount == 30)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 3, true);
            }
            if (troubleCount == 40)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 4, true);
            }
            if (troubleCount == 50)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 5, true);
            }
            if (troubleCount == 60)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 6, true);
            }
            if (troubleCount == 70)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 7, true);
            }
            if (troubleCount == 80)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 8, true);
            }
            if (troubleCount == 90)
            {
                trouble[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 9, true);
            }
            if (troubleCount > 99)
            {
                troubleFlag[1] = true;
                troubleCount = 100;
            }

        }

        if (troubleCount2 > 0)
        {
            if (troubleCount2 < 10 || (troubleCount2 > 10 && troubleCount2 < 20) || (troubleCount2 > 20 && troubleCount2 < 30) ||
                (troubleCount2 > 30 && troubleCount2 < 40) || (troubleCount2 > 40 && troubleCount2 < 50) || (troubleCount2 > 50 && troubleCount2 < 60) ||
                (troubleCount2 > 60 && troubleCount2 < 70) || (troubleCount2 > 70 && troubleCount2 < 80) || (troubleCount2 > 80 && troubleCount2 < 90) ||
                (troubleCount2 > 90 && troubleCount2 < 100))
            {
                trouble2[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + nannteCount2, true);
            }
            if (troubleCount2 == 10 || troubleCount2 == 20 || troubleCount2 == 30 || troubleCount2 == 40 || troubleCount2 == 50 ||
                troubleCount2 == 60 || troubleCount2 == 70 || troubleCount2 == 80 || troubleCount2 == 90)
            {
                trouble2[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16, true);
                nannteCount2 = 0;
            }
            if (troubleCount2 == 10)
            {
                troubleFlag2[0] = true;
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 1, true);
            }
            if (troubleCount2 == 20)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 2, true);
            }
            if (troubleCount2 == 30)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 3, true);
            }
            if (troubleCount2 == 40)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 4, true);
            }
            if (troubleCount2 == 50)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 5, true);
            }
            if (troubleCount2 == 60)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 6, true);
            }
            if (troubleCount2 == 70)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 7, true);
            }
            if (troubleCount2 == 80)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 8, true);
            }
            if (troubleCount2 == 90)
            {
                trouble2[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 16 + 9, true);
            }
            if (troubleCount2 > 99)
            {
                troubleFlag2[1] = true;
                troubleCount2 = 100;
            }

        }

        if (troubleCount3 > 0)
        {
            if (troubleCount3 < 10 || (troubleCount3 > 10 && troubleCount3 < 20) || (troubleCount3 > 20 && troubleCount3 < 30) ||
                (troubleCount3 > 30 && troubleCount3 < 40) || (troubleCount3 > 40 && troubleCount3 < 50) || (troubleCount3 > 50 && troubleCount3 < 60) ||
                (troubleCount3 > 60 && troubleCount3 < 70) || (troubleCount3 > 70 && troubleCount3 < 80) || (troubleCount3 > 80 && troubleCount3 < 90) ||
                (troubleCount3 > 90 && troubleCount3 < 100))
            {
                trouble3[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + nannteCount3, true);
            }
            if (troubleCount3 == 10 || troubleCount3 == 20 || troubleCount3 == 30 || troubleCount3 == 40 || troubleCount3 == 50 ||
                troubleCount3 == 60 || troubleCount3 == 70 || troubleCount3 == 80 || troubleCount3 == 90)
            {
                trouble3[1].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount, true);
                nannteCount3 = 0;
            }
            if (troubleCount3 == 10)
            {
                troubleFlag3[0] = true;
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 1, true);
            }
            if (troubleCount3 == 20)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 2, true);
            }
            if (troubleCount3 == 30)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 3, true);
            }
            if (troubleCount3 == 40)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 4, true);
            }
            if (troubleCount3 == 50)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 5, true);
            }
            if (troubleCount3 == 60)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 6, true);
            }
            if (troubleCount3 == 70)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 7, true);
            }
            if (troubleCount3 == 80)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 8, true);
            }
            if (troubleCount3 == 90)
            {
                trouble3[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 9, true);
            }
            if (troubleCount3 > 99)
            {
                troubleFlag3[1] = true;
                troubleCount3 = 100;
            }

        }
        if (troubleCount4 == 1)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 1, true);
        }
        if (troubleCount4 == 2)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 2, true);
        }
        if (troubleCount4 == 3)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 3, true);
        }
        if (troubleCount4 == 4)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 4, true);
        }
        if (troubleCount4 == 5)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 5, true);
        }
        if (troubleCount4 == 6)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 6, true);
        }
        if (troubleCount4 == 7)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 7, true);
        }
        if (troubleCount4 == 8)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 8, true);
        }
        if (troubleCount4 == 9)
        {
            saisyoutedayo[0].CreateSprite(Raki_DX12B::Get()->GetDevice(), { 1,1 }, { 0,0 }, numCount + 9, true);
        }



        if (player->GetJump() < 0)
        {
            player->count = 0;
        }
        if (player->GetJump() > 0)
        {
            player->count = 1;
        }

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

    sprite.UpdateSprite();

    trouble[0].UpdateSprite();
    trouble[1].UpdateSprite();
    trouble[2].UpdateSprite();
    trouble[3].UpdateSprite();
    trouble2[0].UpdateSprite();
    trouble2[1].UpdateSprite();
    trouble2[2].UpdateSprite();
    trouble2[3].UpdateSprite();
    trouble3[0].UpdateSprite();
    trouble3[1].UpdateSprite();
    trouble3[2].UpdateSprite();
    trouble3[3].UpdateSprite();

    saisyoutedayo[0].UpdateSprite();
    saisyoutedayo[1].UpdateSprite();

    waku.UpdateSprite();

    hikizan.UpdateSprite();
    ikoru.UpdateSprite();

    score[0].UpdateSprite();
    score[1].UpdateSprite();
    score[2].UpdateSprite();

    Rady.UpdateSprite();
    Go.UpdateSprite();
    BoomParticle::Get()->Update(cam._matView);
}

//描画
void stage17::Draw() {

    Raki_DX12B::Get()->StartDraw();

    SpriteManager::Get()->SetCommonBeginDraw(Raki_DX12B::Get()->GetGCommandList());
    sprite.Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    NY_Object3DManager::Get()->SetCommonBeginDrawObject3D(Raki_DX12B::Get()->GetGCommandList());
    PlayerParticle::Get()->Draw();
    BoomParticle::Get()->Draw();
    //player
    player->objDraw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    for (int y = 0; y < LOAD_HEIGHT; y++)
    {
        for (int x = 0; x < LOAD_WIDTH; x++)
        {
            if ((mapBlock[y][x].model.material.texFileName == "stageBlock1.png" ||
                mapBlock[y][x].model.material.texFileName == "stageBlock2.png" ||
                mapBlock[y][x].model.material.texFileName == "coin.png" ||
                mapBlock[y][x].model.material.texFileName == "coinframe.png" ||
                mapBlock[y][x].model.material.texFileName == "broken.png") &&
                drawFlag[y][x] == false)
            {
                NY_Object3D::DrawModel3D(&mapBlock[y][x], Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
            }
            if (mapBlock[y][x].model.material.texFileName == "transBlock.png" &&
                transCount % 2 == 0)
            {
                NY_Object3D::DrawModel3D(&mapBlock[y][x], Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
            }
            if (mapBlock[y][x].model.material.texFileName == "frame.png" &&
                transCount % 2 == 1)
            {
                NY_Object3D::DrawModel3D(&mapBlock[y][x], Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
            }
        }
    }

    SpriteManager::Get()->SetCommonBeginDraw(Raki_DX12B::Get()->GetGCommandList());
    if (troubleFlag[0] == true)
    {
        trouble[0].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }
    trouble[1].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    trouble[2].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    if (troubleFlag[1] == true)
    {
        trouble[3].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }

    if (troubleFlag2[0] == true)
    {
        trouble2[0].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }
    trouble2[1].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    trouble2[2].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    waku.Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    saisyoutedayo[0].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    saisyoutedayo[1].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    if (troubleFlag2[1] == true)
    {
        trouble2[3].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }
    if (waitCount > 100)
    {
        if (troubleFlag3[0] == true)
        {
            trouble3[0].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
        }
        trouble3[1].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
        trouble3[2].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
        if (troubleFlag3[1] == true)
        {
            trouble3[3].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
        }
    }


    if (waitCount > 10)
    {
        hikizan.Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }
    if (waitCount > 10)
    {
        ikoru.Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }

    score[0].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    score[1].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    score[2].Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());

    if (count < 180)
    {
        Rady.Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }
    if (count > 180 && count < 230)
    {
        Go.Draw(Raki_DX12B::Get()->GetGCommandList(), Raki_DX12B::Get()->GetDevice());
    }

    Raki_DX12B::Get()->EndDraw();
}