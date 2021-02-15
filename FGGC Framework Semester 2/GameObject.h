#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Debug.h"
#include "Transform.h"
#include "ParticleModel.h"
#include "Quarternion.h"

using namespace DirectX;
using namespace std;

struct Geometry
{
	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * indexBuffer;
	int numberOfIndices;

	UINT vertexBufferStride;
	UINT vertexBufferOffset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
	float specularPower;
};

class GameObject
{
public:
	GameObject(string type, Geometry geometry, Material material);
	~GameObject();

	string GetType() const { return _type; }

	Geometry GetGeometryData() const { return _geometry; }

	Material GetMaterial() const { return _material; }

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }
	ID3D11ShaderResourceView * GetTextureRV() const { return _textureRV; }
	bool HasTexture() const { return _textureRV ? true : false; }

	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

	Transform* _transform;
	ParticleModel* particleModel;
private:
	XMFLOAT3 _position;
	XMFLOAT3 _rotation;
	XMFLOAT3 _scale;

	string _type;

	XMFLOAT4X4 _world;

	Geometry _geometry;
	Material _material;

	ID3D11ShaderResourceView * _textureRV;

	GameObject * _parent;
	Debug _debug;
	Quaternion _quaternion;
};

