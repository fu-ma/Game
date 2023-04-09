#pragma once

#include"CollisionPrimitive.h"

/// <summary>
/// 当たり判定ヘルパークラス
/// </summary>
class Collision
{
public:
	/// <summary>
	/// 球と平面の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">交点 (平面上の最近接点)</param>
	/// <returns>交差してるか否か</returns>
	static bool CheckSphere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// 点と三角形の最近接点を求める
	/// </summary>
	/// <param name="sphere">点</param>
	/// <param name="plane">三角形</param>
	/// <param name="inter">最近接点 (出力用)</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point, const Triangle &triangle, DirectX::XMVECTOR *closest);

	/// <summary>
	/// 球と法線付き三角形の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">三角形</param>
	/// <param name="inter">交点 (平面上の最近接点)</param>
	/// <returns>交差してるか否か</returns>
	static bool CheckSphere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// レイと平面の当たり判定
	/// </summary>
	/// <param name="sphere">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">距離 (出力用)</param>
	/// <param name="inter">交点 (出力用)</param>
	/// <returns>交差してるか否か</returns>
	static bool CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// レイと法線付き三角形の当たり判定
	/// </summary>
	/// <param name="sphere">レイ</param>
	/// <param name="plane">三角形</param>
	/// <param name="inter">距離 (出力用)</param>
	/// <param name="inter">交点 (出力用)</param>
	/// <returns>交差してるか否か</returns>
	static bool CheckRay2Triangle(const Ray &ray, const Triangle &triangle, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	///<summary>
	/// レイと球の当たり判定
	/// </summary>
	/// <param name="sphere">レイ</param>
	/// <param name="plane">球</param>
	/// <param name="inter">距離 (出力用)</param>
	/// <param name="inter">交点 (出力用)</param>
	/// <returns>交差してるか否か</returns>
	static bool CheckRay2Sphere(const Ray &ray, const Sphere &sphere, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">球</param>
	/// <param name="inter">当たっているか (平面上の最近接点)</param>
	/// <returns>当たっているか否か</returns>
	static bool CheckSphere2Sphere(const Sphere &sphere1, const Sphere &sphere2, float r1, float r2);

};