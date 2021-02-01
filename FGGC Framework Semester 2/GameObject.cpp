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
	particleModel = new ParticleModel({ 0,0,0 }, { 0,0,0 }, { 0,0,0 });
}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	/*particleModel->SetPosition(vector3d(.0001, .00005, 0));
	particleModel->SetMass(10.0f);
	particleModel->SetVelocity(vector3d(1.0f, 3.0f, 0.0f));
	particleModel->SetAcceleration(vector3d(0.0f, -20.0f, 0.0f));
	particleModel->SetDamping(0.90f);
	particleModel->ClearAcc();
	particleModel->Intergrate(t);*/

	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}

	
	//_debug.DebugMessage();
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
