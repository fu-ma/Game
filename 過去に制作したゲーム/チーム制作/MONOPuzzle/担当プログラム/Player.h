#pragma once
#include "Raki_DX12B.h"
#include "NY_Object3DMgr.h"
#include "NY_Object3D.h"
#include <string>
class Player
{
    //player�̃��f��
    NY_Model3D playerModel1;
    NY_Model3D playerModel2;
    //player��obj
    NY_Object3D *playerObj;
    //�ʏ펞�̑��x
    float jump;
    //�_�b�V�����̉��Z���x(jump+(dash<-)=�_�b�V�����x)
    float dash;
    //�ʏ펞�̉�]���x
    float roll;
    //�_�b�V�����̉�]���Z���x(roll+(dash<-)=�_�b�V�����̉�]���x)
    float runawayRoll;
    //�_�b�V�����Ă邩
    bool dashFlag;
    //��]���Ă邩
    //���f���ǂݍ���
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

