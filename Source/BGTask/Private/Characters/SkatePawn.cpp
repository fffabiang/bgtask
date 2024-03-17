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
	if (RootMesh && ShouldMove())
	{

		// Calculate the force to apply based on the input value
		FVector ForceToAdd = GetActorForwardVector() * Value.Get<float>() * MoveSpeed;

		UE_LOG(LogTemp, Log, TEXT("Move: Force (%s) Value (%lf)"), *ForceToAdd.ToString(), Value.Get<float>());

		// Apply the force to the RootMesh
		RootMesh->AddForce(ForceToAdd, NAME_None, true);
	}
}

void ASkatePawn::Steer(const FInputActionValue& Value)
{
	if (RootMesh)
	{		

		float YawRotation = Value.Get<float>() * SteerSpeed;

		// Convert the rotation angle from degrees to radians
		float YawRotationRadians = FMath::DegreesToRadians(YawRotation);

		UE_LOG(LogTemp, Log, TEXT("Steer: YawRotation (%lf) Radians (%lf)"), YawRotation, YawRotationRadians);

		// Apply the rotation to the RootMesh
		RootMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, YawRotationRadians), NAME_None, true);

	}
}

void ASkatePawn::Jump()
{
}

void ASkatePawn::StopJumping()
{
}

bool ASkatePawn::ShouldMove()
{
	if (RootMesh)
	{		
		FVector Velocity = RootMesh->GetComponentVelocity();
		float LinearVelocityXY = FVector(Velocity.X, Velocity.Y, 0).Size();
		return LinearVelocityXY <= MaxMoveSpeed;
	}
	else
	{
		return false;
	}
}

bool ASkatePawn::ShouldSteer()
{
	if (RootMesh)
	{
		FVector Velocity = RootMesh->GetComponentVelocity();

		return true;
		
	}
	else
	{
		return false;
	}
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

