// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/BGTaskGameMode.h"
#include "Characters/BGTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABGTaskGameMode::ABGTaskGameMode()
{

}

void ABGTaskGameMode::PassObstacle(AObstacleActor* ObstaclePassed)
{
	if (ObstaclePassed)
	{
		PassedObstacles++;
		PlayerScore += ObstaclePassed->Points;
	}
}

 
