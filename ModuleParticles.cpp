#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSound.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		Sint32 ticks = SDL_GetTicks();
		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(ticks >= p->born)
		{
			AnimationFrame frame = p->anim.GetCurrentFrame();
			App->render->Blit(graphics, (int)p->position.x - frame.pivot.x, (int)p->position.y - frame.pivot.y, &(frame.rect));
			if(p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

 void ModuleParticles::AddParticle(const Particle& particle, int x, int y, PARTICLE_TYPE particle_type, COLLIDER_TYPE collider_type, Mix_Chunk* on_end_sound, Sint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->position.x = x;
			p->position.y = y;
			p->born = SDL_GetTicks() + delay;
			p->particletype = particle_type;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame().rect, collider_type, this);
				p->collider->active = false;
			}
			active[i] = p;
			break;
		}
		
	}

}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1 && active[i]->particletype != EXPLOSION)
		{
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life),acceleration(p.acceleration)
{
	init_speed = p.speed;
}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	Sint32 ticks = SDL_GetTicks();

	if(life > 0)
	{
		if ((ticks - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	if (ticks >= born) {
		if (collider != nullptr)
			collider->active = true;
		position.x += speed.x;
		position.y += speed.y;
		speed.y = speed.y + acceleration.y;
	}

	if(collider != nullptr)
		collider->SetPos(position.x - anim.frames[anim.getFrameIndex()].pivot.x, position.y - anim.frames[anim.getFrameIndex()].pivot.y);

	return ret;
}

