// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ObstacleActor.generated.h"

UCLASS()
class BGTASK_API AObstacleActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleActor();

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	int Points;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UBoxComponent* PassTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UStaticMeshComponent* ObstacleMesh;


private:
	UFUNCTION()
	void OnPassTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool bPassed = false;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
