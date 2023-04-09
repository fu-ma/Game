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
    //�ʏ펞�̑��x
    jump = -0.5;
    //�_�b�V�����̉��Z���x(jump+(dash<-)=�_�b�V�����x)
    dash = 1.5;
    //�ʏ펞�̉�]���x
    roll = 5;
    //�_�b�V�����̉�]���Z���x(roll+(dash<-)=�_�b�V�����̉�]���x)
    runawayRoll = 95;
    //�_�b�V�����Ă邩
    dashFlag = false;
    //��]���Ă邩
    isRollFlag = false;
    count = 0;
    hitFlag = false;
    waitCount = 0;

    //player3D�I�u�W�F�N�g�̏�����
    playerObj->InitObject3D(dev);

    //player�Ƀ��f�����C���|�[�g
    NY_Object3D::SetLoadedModelData(playerObj, playerModel1);

    //player�̏����ʒu
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
    //�󒆂̏���
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
    //�I�u�W�F�N�g�X�V
    NY_Object3D::UpdateObject3D(playerObj, matView);
}

void Player::NotDownName()
{
}
