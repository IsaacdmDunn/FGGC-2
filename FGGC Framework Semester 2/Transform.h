#pragma once

#include "Vector3D.h"

class Transform 
{
private:
	
	vector3d position;
	vector3d rotation;
	vector3d scale;
public:
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	vector3d GetPosition();
	vector3d GetRotation();
	vector3d GetScale();
	void Update();
};
