#pragma once

#include"CollisionPrimitive.h"

/// <summary>
/// �����蔻��w���p�[�N���X
/// </summary>
class Collision
{
public:
	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_ (���ʏ�̍ŋߐړ_)</param>
	/// <returns>�������Ă邩�ۂ�</returns>
	static bool CheckSphere2Plane(const Sphere &sphere, const Plane &plane, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// �_�ƎO�p�`�̍ŋߐړ_�����߂�
	/// </summary>
	/// <param name="sphere">�_</param>
	/// <param name="plane">�O�p�`</param>
	/// <param name="inter">�ŋߐړ_ (�o�͗p)</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR &point, const Triangle &triangle, DirectX::XMVECTOR *closest);

	/// <summary>
	/// ���Ɩ@���t���O�p�`�̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">�O�p�`</param>
	/// <param name="inter">��_ (���ʏ�̍ŋߐړ_)</param>
	/// <returns>�������Ă邩�ۂ�</returns>
	static bool CheckSphere2Triangle(const Sphere &sphere, const Triangle &triangle, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// ���C�ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="sphere">���C</param>
	/// <param name="plane">����</param>
	/// <param name="inter">���� (�o�͗p)</param>
	/// <param name="inter">��_ (�o�͗p)</param>
	/// <returns>�������Ă邩�ۂ�</returns>
	static bool CheckRay2Plane(const Ray &ray, const Plane &plane, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	/// <summary>
	/// ���C�Ɩ@���t���O�p�`�̓����蔻��
	/// </summary>
	/// <param name="sphere">���C</param>
	/// <param name="plane">�O�p�`</param>
	/// <param name="inter">���� (�o�͗p)</param>
	/// <param name="inter">��_ (�o�͗p)</param>
	/// <returns>�������Ă邩�ۂ�</returns>
	static bool CheckRay2Triangle(const Ray &ray, const Triangle &triangle, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	///<summary>
	/// ���C�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="sphere">���C</param>
	/// <param name="plane">��</param>
	/// <param name="inter">���� (�o�͗p)</param>
	/// <param name="inter">��_ (�o�͗p)</param>
	/// <returns>�������Ă邩�ۂ�</returns>
	static bool CheckRay2Sphere(const Ray &ray, const Sphere &sphere, float *distance = nullptr, DirectX::XMVECTOR *inter = nullptr);

	/// ���Ƌ��̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">��</param>
	/// <param name="inter">�������Ă��邩 (���ʏ�̍ŋߐړ_)</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Sphere(const Sphere &sphere1, const Sphere &sphere2, float r1, float r2);

};