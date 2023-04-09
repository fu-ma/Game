#pragma once
#include "Raki_DX12B.h"
#include "NY_Object3DMgr.h"
#include "NY_Object3D.h"
#include <string>
class Player
{
    //playerのモデル
    NY_Model3D playerModel1;
    NY_Model3D playerModel2;
    //playerのobj
    NY_Object3D *playerObj;
    //通常時の速度
    float jump;
    //ダッシュ時の加算速度(jump+(dash<-)=ダッシュ速度)
    float dash;
    //通常時の回転速度
    float roll;
    //ダッシュ時の回転加算速度(roll+(dash<-)=ダッシュ時の回転速度)
    float runawayRoll;
    //ダッシュしてるか
    bool dashFlag;
    //回転してるか
    //モデル読み込み
    int waitCount;
public:
    int count;
    bool hitFlag;
    bool isRollFlag;
    Player(NY_Object3D *playerObj, NY_Model3D *playerDownState, NY_Model3D *playerUpState);
    void PlayerLoadModel(const char *filename1, const char *filename2, ID3D12Device *dev, NY_Object3DManager *objmgr);
    void Initialize(ID3D12Device *dev, NY_Object3DManager *objmgr);
    void moveUpdate();
    bool SetNotRunaway() { return dashFlag = false; }
    void NotDownName();
    void NotUpName();
    int playerCount = 0;
    XMFLOAT3 GetPosition() { return playerObj->position; }
    float rotation0() { return playerObj->rotation.z = 0; }
    double SetPositionY(double blockPos) { return playerObj->position.y = blockPos; }
    double SetPositionX(double blockPos) { return playerObj->position.x = blockPos; }
    const float &GetJump() { return jump; }
    float SetJump(float num) { return jump = num; }
    float SetRoll(float num) { return roll = num; }
    string GetFileName() { return playerObj->model.material.texFileName; }
    float GetPosX() { return playerObj->position.x; }
    float GetPosZ() { return playerObj->position.z; }
    void objUpdate(XMMATRIX &matView);
    void objDraw(ID3D12GraphicsCommandList *cmd, ID3D12Device *dev);
    int GetCount() { return count %= 2; }
};

