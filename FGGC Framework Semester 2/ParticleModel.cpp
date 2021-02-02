#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* transform, bool useConstAccel, vector3d initialVelocity, vector3d initialAcceleration, float mass, vector3d netForce)
{
	_velocity = initialVelocity;
	_position.x = transform->GetPosition().x;
	_position.y = transform->GetPosition().y;
	_position.z = transform->GetPosition().z;
	_mass = mass;
	_netForce = netForce;
	_weight = _mass * 9.81f;
}

ParticleModel::~ParticleModel()
{
}



void ParticleModel::Update(float deltaTime)
{
	if (_useConstAccel)
	{
		MoveConstAcceleration(deltaTime);
	}
	else
	{
		MoveConstVelocity(deltaTime);
	}

	if (_position.y <= 0)
	{
		_weight = 0;
	}
}

void ParticleModel::MoveConstVelocity(const float deltaTime)
{
	_position = _previousPosition + (_velocity * deltaTime);
}

void ParticleModel::MoveConstAcceleration(const float deltaTime)
{
	_position.x = _previousPosition.x + _previousVelocity.x * deltaTime + 0.5f * _accelleration.x * deltaTime * deltaTime;
	_position.y = _previousPosition.y + _previousVelocity.y * deltaTime + 0.5f * _accelleration.y * deltaTime * deltaTime;
	_position.z = _previousPosition.z + _previousVelocity.z * deltaTime + 0.5f * _accelleration.z * deltaTime * deltaTime;

	_velocity = _previousVelocity + _accelleration * deltaTime;
}

void ParticleModel::UpdateNetForce()
{
	// calculate net external force
	//for each force{ // for example:  thrust, brake force, friction force
	_netForce.x += 0;//force.x;
	_netForce.y += _weight;//force.y;
	_netForce.z += 0;//force.z;
	//}
}

void ParticleModel::UpdateAccel()
{
	// calculate  acceleration caused by net external force
	_accelleration.x = _netForce.x / _mass;
	_accelleration.y = _netForce.y / _mass;
	_accelleration.z = _netForce.z / _mass;

}

void ParticleModel::UpdateState(float deltaTime)
{
	UpdateNetForce();
	UpdateAccel();
	//MoveConstAcceleration(deltaTime);
}

void ParticleModel::MotionInFluid(float deltaTime)
{
	DragForce(_velocity, _dragFactor);
	UpdateState(deltaTime);
	MoveConstAcceleration(deltaTime);
}

void ParticleModel::DragForce(vector3d velocity, float dragFactor)
{
	if (isLaminar)
	{
		DragLamFlow();
	}
	else
	{
		DragTurbFlow();
	}
}

void ParticleModel::DragLamFlow()
{
	_drag.x = _dragFactor * _velocity.x;
	_drag.y = _dragFactor * _velocity.y;
	_drag.z = _dragFactor * _velocity.z;
}

void ParticleModel::DragTurbFlow()
{
	float magVelocity = _velocity.magnitude(_velocity);
	vector3d unitVelocity = _velocity.normalization();

	float dragMagnitude = _dragFactor * magVelocity * magVelocity;

	_drag.x = -dragMagnitude * unitVelocity.x;
	_drag.y = -dragMagnitude * unitVelocity.y;
	_drag.z = -dragMagnitude * unitVelocity.z;
}

void ParticleModel::SetVelocity(vector3d velocity)
{
	_velocity = velocity;
}

vector3d ParticleModel::GetVelocity()
{
	return _velocity;
}

void ParticleModel::SetAcceleration(vector3d acceleration)
{
	_accelleration = acceleration;
}

vector3d ParticleModel::GetAcceleration()
{
	return _accelleration;
}

void ParticleModel::ClearAcc()
{
	_netForce = { 0,0,0 };
}

void ParticleModel::AddForce(vector3d force)
{
	_netForce += force;
}

void ParticleModel::SetUsingConstAccel(bool useConstAccel)
{
	_useConstAccel = useConstAccel;
}

float ParticleModel::GetUsingConstAccel()
{
	return _useConstAccel;
}

void ParticleModel::SetPosition(vector3d position)
{
	_position = position;
}

vector3d ParticleModel::GetPosition()
{
	return _position;
}

void ParticleModel::Intergrate(float t)
{
	if (_inverseMass <= 0.0f) return;
	
	_position.addScaledVector(_velocity, t);
	vector3d newAcceleration = _accelleration;
	_velocity.addScaledVector(_netForce, t);
	_velocity *= powf(_damping, t);
	_accelleration = { 0,0,0 };
}

void ParticleModel::SetMass(float mass)
{
	_inverseMass = 1.0f / mass;
}

float ParticleModel::GetMass()
{
	return 1.0 / _inverseMass;
}

void ParticleModel::SetInverseMass(float inverseMass)
{
	_inverseMass = inverseMass;
}

float ParticleModel::GetInverseMass()
{
	return _inverseMass;
}

void ParticleModel::SetDamping(float damping)
{
	_damping = damping;
}

float ParticleModel::GetDamping()
{
	return _damping;
}
