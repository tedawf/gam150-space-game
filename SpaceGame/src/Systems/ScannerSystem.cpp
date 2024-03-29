#include "ScannerSystem.h"
#include "../ECS/Core.h"
#include "../Components/cScanner.h"
#include "../Components/cTransform.h"
#include "../Global.h"

void ScannerSystem::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cScanner>());
	Core::Get().SetSystemSignature<ScannerSystem>(signature);

	planetScan = hostileScan = bossScan = allyScan = 0;
}

void ScannerSystem::Update()
{
	cScanner* scannerComp;
	cTransform* transform;
	for (auto const& entity : entitiesList)
	{
		scannerComp = Core::Get().GetComponent<cScanner>(entity);
		transform = Core::Get().GetComponent<cTransform>(entity);

		if (scannerComp->_classification == ScannerType::RECIEVER)
		{
			scannerComp->_currTime -= g_dt;
			if (scannerComp->_currTime <= 0.0f)
			{
				markedForDestruction.insert(entity);
			}
		}
		else
		{
			//Check if on screen

			//Create Reciever object

			//Remove Component from sender  
			markedForRemoveComp.insert(entity);
		}

	}

	if (markedForDestruction.size() > 0)
	{
		for (auto const& entity : markedForDestruction)
		{
			Core::Get().EntityDestroyed(entity);
		}
		markedForDestruction.clear();
	}

	if (markedForRemoveComp.size() > 0)
	{
		for (auto const& entity : markedForRemoveComp)
		{
			Core::Get().RemoveComponent<cScanner>(entity);
		}
		markedForRemoveComp.clear();
	}
}

void ResetQuota(unsigned int planet, unsigned int hostile, unsigned int boss, unsigned int ally)
{
	std::shared_ptr<ScannerSystem> scannerSys(std::static_pointer_cast<ScannerSystem>(Core::Get().GetSystem<ScannerSystem>()));

	scannerSys->planetScan = planet;
	scannerSys->hostileScan = hostile;
	scannerSys->bossScan = boss;
	scannerSys->allyScan = ally;
}	