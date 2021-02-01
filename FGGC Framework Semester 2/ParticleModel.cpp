#include "ParticleModel.h"

ParticleModel::ParticleModel(vector3d velocity, vector3d position, vector3d _previousPosition)
{
	_velocity = velocity;
	_position = position;
}

ParticleModel::~ParticleModel()
{
}



void ParticleModel::Update(float deltaTime)
{
	//MoveConstVelocity(deltaTime);
	MoveConstAcceleration(deltaTime);
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
	_previousVelocity = _velocity;
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
	_forceAccumalation = { 0,0,0 };
}

void ParticleModel::AddForce(vector3d force)
{
	_forceAccumalation += force;
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
	_velocity.addScaledVector(_forceAccumalation, t);
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
