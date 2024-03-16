// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SkatePawn.h"

// Sets default values
ASkatePawn::ASkatePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	SetRootComponent(RootMesh);


}

void ASkatePawn::Move(const FInputActionValue& Value)
{
}

void ASkatePawn::Steer(const FInputActionValue& Value)
{
}

void ASkatePawn::Jump()
{
}

void ASkatePawn::StopJumping()
{
}

// Called when the game starts or when spawned
void ASkatePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkatePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkatePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

