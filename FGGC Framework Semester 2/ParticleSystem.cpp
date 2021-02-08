#include "ParticleSystem.h"

void ParticleSystem::Update(float deltaTime)
{

}

void ParticleSystem::Draw()
{
}

void ParticleSystem::CreateParticle(vector3d position, vector3d velocity, vector3d colour, float mass, float lifeSpan)
{
	_particle.SetPosition(position);
	_particle.SetVelocity(velocity);
	_particle.SetMass(mass);
	_particles->push_back(_particle);
	
	_lifeSpan = lifeSpan;
}

void ParticleSystem::DestroyParticle()
{
	
}
