// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SkatePawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBasicSkatePawnEvent);


UCLASS()
class BGTASK_API ASkatePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkatePawn();

	// Parameters
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float MoveAcceleration = 600.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float MaxMoveSpeed = 800.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float SteerAcceleration = 100.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float TickRotationSpeed = 10.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float JumpImpulseStrength = 200.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float GroundCheckDistance = 2.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<AActor> DeadSkaterClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector DefaultBodyPosition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector MovingBodyPosition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FRotator MovingBodyRotation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FRotator DefaultBodyRotation;	

	// Components

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* RootMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USkeletalMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FBasicSkatePawnEvent OnJumpTriggered;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FBasicSkatePawnEvent OnFallTriggered;

	// Functions

	void Move(const FInputActionValue& Value);

	void Steer(const FInputActionValue& Value);

	void StopSteer();

	void Jump();

	void StopJumping();

	UFUNCTION(BlueprintPure)
	bool IsNearGround();

	UFUNCTION(BlueprintPure)
	bool IsMovingOnGround();

	UFUNCTION(BlueprintPure)
	bool AllowMoveInput();
 

private:
	bool ShouldSteer();	

	void CheckFallenOff();
	void SpawnDeadSkater();
	bool IsMeshInImpossibleOrientation();
	
	bool bTickRotate;
	float DirectionMultiplier = 1.0f;

	bool bPlayerFallen = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
