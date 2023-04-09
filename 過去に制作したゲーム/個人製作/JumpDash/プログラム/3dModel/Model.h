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
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:
	// 頂点データ構造体
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

	//定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient;	//アンビエント係数
		float pad1;			//パディング
		XMFLOAT3 diffuse;	//ディフューズ係数
		float pad2;			//パディング
		XMFLOAT3 specular;	//スペキュラー係数
		float alpha;		//アルファ
	};

	//マテリアル
	struct Material
	{
		std::string name;			//マテリアル名
		XMFLOAT3 ambient;			//アンビエント影響度
		XMFLOAT3 diffuse;			//ディフューズ影響度
		XMFLOAT3 specular;			//スペキュラー影響度
		float alpha;				//アルファ
		std::string textureFilename;//テクスチャファイル名
		//コンストラクタ
		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

	// テクスチャ
	struct Texture
	{
		// テクスチャバッファ
		ComPtr<ID3D12Resource> texbuff;
		// マテリアル用の定数バッファ
		ConstBufferDataB1 constbuff;
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootSignature;
		// シェーダリソースビューのハンドル(CPU)
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// シェーダリソースビューのハンドル(GPU)
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	};

private:
	DirectXCommon *dxCommon;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;

	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;

	// 頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;

public:
	//コンストラクタ
	Model();
	//引数付きコンストラクタ
	Model(DirectXCommon *dxCommon);

	bool Initialize();

	/// <summary>
	/// モデル作成
	/// </summary>
	void CreateModel(const std::string &directoryPath, const std::string &filename);

	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string &directoryPath, const std::string &filename);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
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

