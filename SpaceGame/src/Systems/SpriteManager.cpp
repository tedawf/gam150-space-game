#include "SpriteManager.h"
#include "AEEngine.h"

void SpriteManager::RegisterComponent(SpriteComponent& sprite)
{
	// Add sprite component to list
	spriteComponentList.push_back(sprite);
}

void SpriteManager::UpdateComponents()
{
	for (auto i : spriteComponentList)
	{
		// Draw mesh
		AEGfxMeshDraw(i._mesh, AE_GFX_MDM_TRIANGLES);
	}
}

//AEGfxMeshStart();

	//// 1 triangle at a time
	//// X, Y, Color, texU, texV
	//AEGfxTriAdd(
	//	-25.5f, -25.5f, 0xFFFF0000, 0.0f, 0.0f,
	//	25.5f, 0.0f, 0xFFFF0000, 0.0f, 0.0f,
	//	-25.5f, 25.5f, 0xFFFF0000, 0.0f, 0.0f);
	////AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);

	//// Saving the mesh (list of triangles) in pMesh1

	//AEGfxVertexList* pMesh1 = AEGfxMeshEnd();