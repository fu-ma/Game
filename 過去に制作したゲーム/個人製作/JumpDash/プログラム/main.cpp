#include"GameScene.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameScene *scene = new GameScene;

	scene->staticInit();
	while (true)//�Q�[�����[�v
	{
		if (scene->SceneTimeGetter() == 0)
		{
			scene->Init();
		}
		if (scene->Update() == false)
		{
			break;
		}
		if (scene->SceneTimeGetter() == 1)
		{
			scene->Draw();
		}
	}
	scene->SceneDelete();
	delete scene;
	scene = nullptr;
	return 0;
}