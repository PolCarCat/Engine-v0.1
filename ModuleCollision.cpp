#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	debug = false;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_WATER] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOX] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_WALL][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WATER] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_BOX] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_TRENCH] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_WATER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_BODY] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_TRENCH] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WATER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOX] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WATER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_BODY] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_WATER] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_BOX] = false;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_PLAYER_BODY] = true;
	matrix[COLLIDER_ENEMY_SHOT2][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_WATER][COLLIDER_WALL] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_WATER][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_WATER][COLLIDER_WATER] = false;
	matrix[COLLIDER_WATER][COLLIDER_BOX] = false;
	matrix[COLLIDER_WATER][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_WATER][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_BOX][COLLIDER_WALL] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOX][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOX][COLLIDER_WATER] = false;
	matrix[COLLIDER_BOX][COLLIDER_BOX] = false;
	matrix[COLLIDER_BOX][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_BOX][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_PLAYER_BODY][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER_FEET] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_WATER] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_BOX] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_TRENCH] = false;

	matrix[COLLIDER_TRENCH][COLLIDER_WALL] = false;
	matrix[COLLIDER_TRENCH][COLLIDER_PLAYER_FEET] = true;
	matrix[COLLIDER_TRENCH][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_TRENCH][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_TRENCH][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_TRENCH][COLLIDER_WATER] = false;
	matrix[COLLIDER_TRENCH][COLLIDER_BOX] = false;
	matrix[COLLIDER_TRENCH][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_TRENCH][COLLIDER_TRENCH] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleCollision::PostUpdate() {
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{

		c1 = colliders[i];
		// skip empty colliders
		if(c1 == nullptr || !c1->active || c1->to_delete || c1->type == COLLIDER_NONE)
			continue;

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			c2 = colliders[k];

			// skip empty colliders
			if(c2 == nullptr || c2->to_delete || !c2->active || c2->type == COLLIDER_NONE)
				continue;

			if(c1->CheckCollision(c2->rect))
			{
				if(matrix[c1->type][c2->type] && c1->callback) 
					c1->callback->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->callback) 
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if(App->input->keyboard[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)
		debug = !debug;

	if(debug == false)
		return;

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;

		if (colliders[i]->active == false || colliders[i]->to_delete == true)
			continue;
		
		switch(colliders[i]->type)
		{
			case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case COLLIDER_PLAYER_BODY: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case COLLIDER_PLAYER_FEET: // green_dark
			App->render->DrawQuad(colliders[i]->rect, 128, 255, 128, alpha);
			break;
			case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
			case COLLIDER_ENEMY_SHOT2: // darker magenta
			App->render->DrawQuad(colliders[i]->rect, 128, 255, 255, alpha);
			break;
			case COLLIDER_WATER: // roseta
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;
			case COLLIDER_BOX: //orange
			App->render->DrawQuad(colliders[i]->rect, 255, 102, 0, alpha);
			break;
			case COLLIDER_TRENCH: //black
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 0, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool ModuleCollision::EraseCollider(Collider* collider)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == collider && colliders[i] != nullptr)
		{
			colliders[i]->to_delete = true;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 0: Return true if there is an overlap
	// between argument "r" and property "rect"
	if (r.x <= rect.x + rect.w && r.x + r.w >= rect.x && r.y <= rect.y + rect.h && r.y + r.h >= rect.y)
		return true;
	return false;
}

bool ModuleCollision::CheckCollisionForCollider(Collider* col) {
	COLLIDER_TYPE type = col->type;
	SDL_Rect rect = col->rect;
	for (uint k = 0; k < MAX_COLLIDERS; ++k)
	{
		// skip empty colliders
		if (colliders[k] == nullptr || colliders[k]->to_delete == true)
			continue;

		Collider* c2 = colliders[k];

		if (matrix[type][c2->type] || matrix[c2->type][type])
			if (c2->CheckCollision(rect))
				return true;
	}
	return false;
}