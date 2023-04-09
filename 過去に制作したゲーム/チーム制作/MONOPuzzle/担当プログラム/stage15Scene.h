#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include "NY_Object3D.h"
#include "NY_Camera.h"
#include "Raki_Input.h"
#include"Player.h"
#include"Raki_LoadCSV.h"
#include"Audio.h"
#include"PlayerParticle.h"
#include"BoomParticle.h"

#define speedClea 3
#define normalClea 6

class stage15 : public BaseScene {
    SoundData sound;
    SoundData esc;
    SoundData coin;
    SoundData bigJump;
    SoundData smallJump;
    SoundData star;
    SoundData result;
    SoundData blockBreak;

    //player
    Player *player;

    NY_Model3D playerModel1;
    NY_Model3D playerModel2;
    NY_Object3D playerObj;

    Sprite sprite;
    Sprite trouble[4];
    Sprite trouble2[4];
    Sprite trouble3[4];
    Sprite hikizan;
    Sprite ikoru;
    Sprite saisyoutedayo[2];
    Sprite waku;

    Sprite Rady;
    Sprite Go;

    Sprite score[3];

    bool troubleFlag3[2] = { false };
    bool troubleFlag2[2] = { false };
    bool troubleFlag[2] = { false };
    bool cleaFlag;

    int troubleCount = 0;
    int troubleCount2 = 0;
    int troubleCount3 = 0;
    int troubleCount4 = 0;

    int nannteCount = 0;
    int nannteCount2 = 0;
    int nannteCount3 = 0;

    int numCount = 2;

    float gameSpeed;
    bool gameStopFlag;

    int count;
    int transCount;

    bool drawFlag[LOAD_HEIGHT][LOAD_WIDTH];
    NY_Object3D mapBlock[LOAD_HEIGHT][LOAD_WIDTH];
    int map[LOAD_HEIGHT][LOAD_WIDTH];
    int waitCount;

    int coinCount;
    int coinframCount;
    /// <summary>
/// あたり判定
/// </summary>
/// <param name="position1"></param>
/// <param name="position2"></param>
/// <param name="change">上の壁か下の壁(trueなら下の壁、falseなら上の壁)</param>
/// <returns>当たっているか</returns>

    bool Hit(XMFLOAT3 &position1, XMFLOAT3 &position2, int change)
    {
        if (change == 1)
        {
            if ((position1.x < position2.x + BLOCK_SIZE) &&
                (position1.x + BLOCK_SIZE > position2.x) &&
                (position1.y < position2.y + BLOCK_SIZE) &&
                (position1.y + BLOCK_SIZE > position2.y))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if (change == 2)
        {
            if ((position1.x < position2.x + BLOCK_SIZE * 1.25) &&
                (position1.x + BLOCK_SIZE > position2.x) &&
                (position1.y <= position2.y + BLOCK_SIZE * 1.25) &&
                (position1.y + BLOCK_SIZE >= position2.y))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if (change == 3)
        {
            if ((position1.x < position2.x + BLOCK_SIZE) &&
                (position1.x + BLOCK_SIZE > position2.x) &&
                (position1.y <= position2.y + BLOCK_SIZE) &&
                (position1.y + BLOCK_SIZE >= position2.y))
            {
                return true;
            }
            else
            {
                return false;
            }

        }
    }

public:
    stage15::stage15(ISceneChanger *changer);
    void Initialize() override;    //初期化処理をオーバーライド。
    //void Finalize() override;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
    void Draw() override;            //描画処理をオーバーライド。

    //カメラ
    NY_Camera cam;
    //モデル
    NY_Model3D testmodel[MAX_MODEL];
};

