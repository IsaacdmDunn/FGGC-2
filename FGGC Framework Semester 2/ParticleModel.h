#pragma once
#include "Vector3D.h"
#include "Transform.h"

class ParticleModel
{
protected:
	vector3d _position;
	vector3d _accelleration;
	vector3d _velocity;
	float _damping;
	float _inverseMass;
	float _mass;
	float _weight;
	vector3d _previousPosition;
	vector3d _previousVelocity;
	vector3d _netForce;
	bool _useConstAccel;
	float _dragFactor;
	vector3d _drag;
	bool _isLaminar;



public:
	ParticleModel(Transform* transform, vector3d initialVelocity, vector3d initialAcceleration, 
		float mass, vector3d netForce);
	~ParticleModel();

	/*void PositionUpdate(float deltaTime);
	void Update(float deltaTime);
	void MoveConstVelocity(const float deltaTime);
	void MoveConstAcceleration(const float deltaTime);
	void SetPrevPosition(vector3d previousPosition);
	vector3d GetPrevPosition();*/

	void Intergrate(float t);
	void SetMass(float mass);
	float GetMass();
	void SetInverseMass(float inverseMass);
	float GetInverseMass();
	void SetDamping(float damping);
	float GetDamping();
	void SetPosition(vector3d position);
	vector3d GetPosition();
	void SetVelocity(vector3d velocity);
	vector3d GetVelocity();
	void SetAcceleration(vector3d acceleration);
	vector3d GetAcceleration();
	void ClearAcc();
	void AddForce(vector3d force);
	void SetUsingConstAccel(bool useConstAccel);
	float GetUsingConstAccel();
	void SetUsingLaminarFlow(bool isLaminar);
	float GetUsingLaminarFlow();

	void Update(float deltaTime);
	void MoveConstVelocity(const float deltaTime);
	void MoveConstAcceleration(const float deltaTime);

	void UpdateNetForce();
	void UpdateAccel();
	void UpdateState(float deltaTime);

	void MotionInFluid(float deltaTime);
	void DragForce(vector3d velocity, float dragFactor);
	void DragLamFlow();
	void DragTurbFlow();

};

