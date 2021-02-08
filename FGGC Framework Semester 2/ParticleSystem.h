#pragma once

#include "Vector3D.h"
#include "ParticleModel.h"

class ParticleSystem {
	int _numParticles;
	float _lifeSpan;
	std::vector<ParticleModel>* _particles;
	ParticleModel _particle;
public:
	void Update(float deltaTime);
	void Draw();
	void CreateParticle(vector3d postion, vector3d velocity, vector3d colour, float mass, float lifeSpan);
	void DestroyParticle();
};
