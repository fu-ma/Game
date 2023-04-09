#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"DirectXCommon.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;


class Model
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};

	//�萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//�A���r�G���g�W��
		float pad1;			//�p�f�B���O
		XMFLOAT3 diffuse;	//�f�B�t���[�Y�W��
		float pad2;			//�p�f�B���O
		XMFLOAT3 specular;	//�X�y�L�����[�W��
		float alpha;		//�A���t�@
	};

	//�}�e���A��
	struct Material
	{
		std::string name;			//�}�e���A����
		XMFLOAT3 ambient;			//�A���r�G���g�e���x
		XMFLOAT3 diffuse;			//�f�B�t���[�Y�e���x
		XMFLOAT3 specular;			//�X�y�L�����[�e���x
		float alpha;				//�A���t�@
		std::string textureFilename;//�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

	// �e�N�X�`��
	struct Texture
	{
		// �e�N�X�`���o�b�t�@
		ComPtr<ID3D12Resource> texbuff;
		// �}�e���A���p�̒萔�o�b�t�@
		ConstBufferDataB1 constbuff;
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootSignature;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(GPU)
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	};

private:
	DirectXCommon *dxCommon;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;

	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;

	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

public:
	//�R���X�g���N�^
	Model();
	//�����t���R���X�g���N�^
	Model(DirectXCommon *dxCommon);

	bool Initialize();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel(const std::string &directoryPath, const std::string &filename);

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string &directoryPath, const std::string &filename);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	bool LoadTexture(const std::string &directoryPath, const std::string &filename);

public:
	Material material;
	Texture texture;
	const D3D12_VERTEX_BUFFER_VIEW GetVBView() { return vbView; }
	const D3D12_INDEX_BUFFER_VIEW &GetIBView() { return ibView; }
	const vector<unsigned short> &GetIndices() { return indices; }
	const CD3DX12_GPU_DESCRIPTOR_HANDLE &GetGpuHandleSRV() { return texture.gpuDescHandleSRV; }
	const ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return descHeap; }
};

