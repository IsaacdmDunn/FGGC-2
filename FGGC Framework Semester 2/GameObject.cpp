#include "GameObject.h"

GameObject::GameObject(string type, Geometry geometry, Material material) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;
	_position = XMFLOAT3();//
	_rotation = XMFLOAT3();//
	_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);//
	_transform = new Transform();
	_transform->SetPosition(0,0,0);
	_transform->SetRotation(0,0,0); 
	_transform->SetScale(1,1,1);
	//_debug.DebugMessage(type + " %d \n");
	_textureRV = nullptr;
	particleModel = new ParticleModel(_transform, { 0,0,0 }, { 0,0,0 }, 1000, { 0,0,0 });
	
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	XMFLOAT4 f = { 10, 45, 90, 45 };
	XMVECTOR v = { 0, 10, 10, 5 };

	//
	//XMLoadFloat4(&f);

	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	v = XMQuaternionRotationMatrix(rotation);
	XMStoreFloat4(&f, v);
	_quaternion.r = f.w;
	_quaternion.i = f.x;
	_quaternion.j = f.y;
	_quaternion.k = f.z;

	_quaternion.normalise();
	CalculateTransformMatrixRowMajor(translation, vector3d(_position.x, _position.y, _position.z), _quaternion);
	rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}

}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
