#include "Player.h"

void Player::PlayerLoadModel(const char *filename1, const char *filename2, ID3D12Device *dev, NY_Object3DManager *objmgr)
{
    playerModel1.LoadObjModel(filename1, dev, objmgr);
    playerModel2.LoadObjModel(filename2, dev, objmgr);

}

Player::Player(NY_Object3D *playerObj, NY_Model3D *playerDownState, NY_Model3D *playerUpState)
{
    this->playerObj = playerObj;
    playerModel1 = *playerDownState;
    playerModel2 = *playerUpState;
}

void Player::Initialize(ID3D12Device *dev, NY_Object3DManager *objmgr)
{
    PlayerLoadModel("stageBlock1", "stageBlock2", dev, objmgr);
    //通常時の速度
    jump = -0.5;
    //ダッシュ時の加算速度(jump+(dash<-)=ダッシュ速度)
    dash = 1.5;
    //通常時の回転速度
    roll = 5;
    //ダッシュ時の回転加算速度(roll+(dash<-)=ダッシュ時の回転速度)
    runawayRoll = 95;
    //ダッシュしてるか
    dashFlag = false;
    //回転してるか
    isRollFlag = false;
    count = 0;
    hitFlag = false;
    waitCount = 0;

    //player3Dオブジェクトの初期化
    playerObj->InitObject3D(dev);

    //playerにモデルをインポート
    NY_Object3D::SetLoadedModelData(playerObj, playerModel1);

    //playerの初期位置
    playerObj->position = { 0, -32, 10 };
    playerObj->rotation = { 0, 0, 0 };

}

void Player::moveUpdate()
{
    playerObj->position.y += jump;
    waitCount++;
    if (isRollFlag == true)
    {
        playerObj->rotation.z += roll;
    }

    if (hitFlag == true)
    {
        count++;
        hitFlag = false;
    }
    //空中の処理
    if (KeyInput::isKeyTrigger(DIK_SPACE) == true&& waitCount >20)
    {
        isRollFlag = true;
        //roll = -roll;
        //if (jump >= 0)
        jump = -jump;
    }

}

void Player::NotUpName()
{
}

void Player::objDraw(ID3D12GraphicsCommandList *cmd, ID3D12Device *dev)
{
    if (playerCount == 0)
    {
        NY_Object3D::DrawModel3D(playerObj, cmd, dev);
    }
}

void Player::objUpdate(XMMATRIX &matView)
{
    //オブジェクト更新
    NY_Object3D::UpdateObject3D(playerObj, matView);
}

void Player::NotDownName()
{
}
