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

	// Components

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* RootMesh;

	// Functions

	void Move(const FInputActionValue& Value);

	void Steer(const FInputActionValue& Value);

	void Jump();

	void StopJumping();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};