#include "RenderSystem.h"
#include "AEEngine.h"
#include "../ECS/Core.h"
#include "../Components/cTransform.h"
#include "../Components/cSprite.h"

#include "../Components/cSprite.h"
#include "../Components/cTransform.h"

void RenderSystem::Init()
{
}

void RenderSystem::Update()
{
}

void RenderSystem::Render()
{
	cTransform* transform;
	cSprite* sprite;

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		sprite = Core::Get().GetComponent<cSprite>(entity);

		// Set transform
		AEMtx33 trans, rot, scale;
		// Calculate the identity matrix
		AEMtx33Identity(&trans);
		AEMtx33Identity(&rot);
		AEMtx33Identity(&scale);

		// Compute the scaling matrix
		AEMtx33Scale(&scale, transform->scale.x, transform->scale.y);

		// Compute the rotation matrix 
		AEMtx33Rot(&rot, transform->rotation);

		// Compute the translation matrix
		AEMtx33Trans(&trans, transform->position.x, transform->position.y);

		// Concatenate the 3 matrix in the correct order in the object instance's "transform" matrix
		// Order of matrix concatenation: Translation*Rotation*Scaling
		AEMtx33Concat(&transform->transform, &rot, &scale);
		AEMtx33Concat(&transform->transform, &trans, &transform->transform);

		// Set blend mode to blend so we can render transparency
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		// Use textures
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		// Render at position
		AEGfxSetTransform(transform->transform.m);

		// Position texture
		AEGfxTextureSet(sprite->texture, 0.0f, 0.0f);

		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		AEGfxSetTransparency(1.0f);

		//Draw
		AEGfxMeshDraw(sprite->mesh, AE_GFX_MDM_TRIANGLES);
	}
}