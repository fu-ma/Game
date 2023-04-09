#pragma once
#include "BaseScene.h"
#include "ISceneChanger.h"
#include "NY_Object3D.h"
#include "Raki_Input.h"
#include"Player.h"
#include"Raki_LoadCSV.h"
#include"Audio.h"
#include"PlayerParticle.h"

class Title : public BaseScene {
    SoundData sound;
    SoundData ok;
    float gameSpeed;
    bool Hit(XMFLOAT3 &position1, XMFLOAT3 &position2, int change)
    {
        if (change == 1)
        {
            if ((position1.x <= position2.x + BLOCK_SIZE) &&
                (position1.x + BLOCK_SIZE >= position2.x) &&
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
        if (change == 2)
        {
            if ((position1.x < position2.x + 2) &&
                (position1.x + 2.5 > position2.x) &&
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
    Title(ISceneChanger *changer);
    void Initialize() override;    //初期化処理をオーバーライド。
    //void Finalize() override ;   //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
    void Draw() override;          //描画処理をオーバーライド。

    //シーンで使うインスタンス

    //カメラ
    NY_Camera cam;
    //モデル
    NY_Model3D testmodel[MAX_MODEL];
    Sprite sprite[MAX_SPRITE];

    //player
    Player *player;
    NY_Model3D playerModel1;
    NY_Model3D playerModel2;
    NY_Object3D playerObj;

    int testCount = 0;

    NY_Object3D mapBlock[LOAD_HEIGHT][LOAD_WIDTH];
    int map[LOAD_HEIGHT][LOAD_WIDTH];
    bool drawFlag[LOAD_HEIGHT][LOAD_WIDTH];

    /// <summary>
/// あたり判定
/// </summary>
/// <param name="position1"></param>
/// <param name="position2"></param>
/// <param name="change">上の壁か下の壁(trueなら下の壁、falseなら上の壁)</param>
/// <returns>当たっているか</returns>

};

