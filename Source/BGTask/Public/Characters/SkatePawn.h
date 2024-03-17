// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SkatePawn.generated.h"

UCLASS()
class BGTASK_API ASkatePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkatePawn();

	// Parameters
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float MoveSpeed = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float MaxMoveSpeed = 800.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float SteerSpeed = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float TickRotationSpeed = 10.0f;

	// Components

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* RootMesh;

	// Functions

	void Move(const FInputActionValue& Value);

	void Steer(const FInputActionValue& Value);

	void StopSteer();

	void Jump();

	void StopJumping();

private:
	bool ShouldMove();
	bool ShouldSteer();
	
	bool bTickRotate;
	float DirectionMultiplier = 1.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
