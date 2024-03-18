// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/BGTaskGameMode.h"
#include "Characters/BGTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Core/BGTaskPlayerController.h"
#include "Kismet/GameplayStatics.h"

ABGTaskGameMode::ABGTaskGameMode()
{

}

void ABGTaskGameMode::PassObstacle(AObstacleActor* ObstaclePassed)
{
	if (ObstaclePassed)
	{
		PassedObstacles++;
		PlayerScore += ObstaclePassed->Points;

		if (PassedObstacles >= WinningObstacles)
		{
			if (bGameFinished)
				return;

			bGameFinished = true;

			GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
			ABGTaskPlayerController* PlayerController = Cast< ABGTaskPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (PlayerController)
			{
				PlayerController->EnableSkateMapping(false);
				PlayerController->EnableGameOverMapping(true);
			}
			OnWinTriggered.Broadcast();
		}
	}
}

void ABGTaskGameMode::GameOver()
{

	if (bGameFinished)
		return;

	bGameFinished = true;

	GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
	PlayTime = 0.0f;

	ABGTaskPlayerController* PlayerController = Cast< ABGTaskPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		PlayerController->EnableSkateMapping(false);
		PlayerController->EnableGameOverMapping(true);
	}

	OnGameOverTriggered.Broadcast();

}

void ABGTaskGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, [this]() {	
		//UE_LOG(LogTemp, Log, TEXT("PlayTime (%f)"), PlayTime);
		PlayTime -= 0.1f;
		if (PlayTime <= 0.0f)
		{			
			GameOver();
		}
	}, 0.1f, true);
}

 
