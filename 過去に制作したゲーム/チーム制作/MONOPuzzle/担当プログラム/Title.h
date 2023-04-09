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
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    //void Finalize() override ;   //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;          //�`�揈�����I�[�o�[���C�h�B

    //�V�[���Ŏg���C���X�^���X

    //�J����
    NY_Camera cam;
    //���f��
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
/// �����蔻��
/// </summary>
/// <param name="position1"></param>
/// <param name="position2"></param>
/// <param name="change">��̕ǂ����̕�(true�Ȃ牺�̕ǁAfalse�Ȃ��̕�)</param>
/// <returns>�������Ă��邩</returns>

};

