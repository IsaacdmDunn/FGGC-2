#include "Transform.h"

void Transform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

vector3d Transform::GetPosition()
{
	return position;
}

vector3d Transform::GetRotation()
{
	return rotation;
}

vector3d Transform::GetScale()
{
	return scale;
}

void Transform::Update()
{
}
