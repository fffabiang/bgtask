// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ObstacleActor.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

#include "BGTaskGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBasicGameModeEvent);


UCLASS(minimalapi)
class ABGTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABGTaskGameMode();

	// Properties

	// Number of obstacles for the player to win the game
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int WinningObstacles = 10;

	// Time in seconds that the player can play
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float PlayTime = 60.0f;

	// Keeping track of obstacles passed by the player
	UPROPERTY(BlueprintReadOnly)
	int PassedObstacles = 0;

	// Player score after passing all obstacles
	UPROPERTY(BlueprintReadOnly)
	int PlayerScore = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USoundBase* FailSound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USoundBase* ClockSound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USoundBase* BGM_Sound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USoundBase* ObstaclePassedSound;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FBasicGameModeEvent OnGameOverTriggered;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FBasicGameModeEvent OnWinTriggered;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UAudioComponent* ClockAudioComponent;

	// Functions

	void PassObstacle(AObstacleActor* ObstaclePassed);

	void GameOver();


protected:

	void BeginPlay() override;

	FTimerHandle GameTimerHandle;

private:

	bool bGameFinished = false;




};



