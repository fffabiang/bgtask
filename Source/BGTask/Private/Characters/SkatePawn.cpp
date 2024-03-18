// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SkatePawn.h"
#include "Core/BGTaskGameMode.h"


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

	if (bPlayerFallen)
		return;

	if (RootMesh)
	{
		// Move the skate while on the ground
		if (AllowMoveInput())
		{
			// Calculate the force to apply based on the input value
			FVector ForceToAdd = GetActorForwardVector() * Value.Get<float>() * MoveAcceleration;
			UE_LOG(LogTemp, Log, TEXT("Move: Force (%s) Value (%lf)"), *ForceToAdd.ToString(), Value.Get<float>());
			RootMesh->AddForce(ForceToAdd, NAME_None, true);
		}
		// Rotate pitch while on air
		else if (!IsNearGround())
		{
			UE_LOG(LogTemp, Log, TEXT("APPLYING PITCH ON AIR"));
		}
		
	}
}

void ASkatePawn::Steer(const FInputActionValue& Value)
{

	if (bPlayerFallen)
		return;

	if (RootMesh)
	{		

		FVector Velocity = RootMesh->GetComponentVelocity();
		float LinearVelocityXY = FVector(Velocity.X, Velocity.Y, 0).SizeSquared();

		if (FMath::IsNearlyZero(LinearVelocityXY, 1.0f))
		{
			// Actor is not moving, rotate adding local rotation
			bTickRotate = true;
			UE_LOG(LogTemp, Log, TEXT("Rotation using tick triggered"));

			if (Value.Get<float>() < 0)
				DirectionMultiplier = -1.0f;
			else
				DirectionMultiplier = 1.0f;

		}
		else
		{
			float YawRotation = Value.Get<float>() * SteerAcceleration;

			// Convert the rotation angle from degrees to radians
			float YawRotationRadians = FMath::DegreesToRadians(YawRotation);

			UE_LOG(LogTemp, Log, TEXT("Steer: YawRotation (%lf) Radians (%lf)"), YawRotation, YawRotationRadians);

			// Apply the rotation to the RootMesh
			RootMesh->AddTorqueInRadians(FVector(0.0f, 0.0f, YawRotationRadians), NAME_None, true);
		}
	}
}

void ASkatePawn::StopSteer()
{
	bTickRotate = false;
}

void ASkatePawn::Jump()
{

	if (bPlayerFallen)
		return;

	if (IsNearGround())
	{
		// Broadcast Jump event
		OnJumpTriggered.Broadcast();

		// Apply an impulse to simulate jumping
		FVector JumpImpulse = FVector(0.0f, 0.0f, JumpImpulseStrength);
		RootMesh->AddImpulse(JumpImpulse, NAME_None, true);
	}
}

void ASkatePawn::StopJumping()
{

}

bool ASkatePawn::IsNearGround()
{

	// Perform a raycast to check if the player is grounded
	FHitResult HitResult;
	FVector Start = GetActorLocation() + FVector(0.0f,0.0f,5.0f);
	FVector End = Start - FVector(0.0f, 0.0f, GroundCheckDistance);

	// Set up query parameters for the raycast
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// Perform the raycast
	bool bHitGround = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
	//UE_LOG(LogTemp, Log, TEXT("Near Ground Check (%s)"), bHitGround? *FString("TRUE") : *FString("FALSE"));
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);

	return bHitGround;
}

bool ASkatePawn::AllowMoveInput()
{
	if (RootMesh)
	{		
		FVector Velocity = RootMesh->GetComponentVelocity();
		float LinearVelocityXY = FVector(Velocity.X, Velocity.Y, 0).Size();
		return LinearVelocityXY <= MaxMoveSpeed && IsNearGround();
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


void ASkatePawn::CheckFallenOff()
{
	if (!bPlayerFallen)
	{
		// Check if the root mesh is in an unhandleable position
		FVector MeshLocation = RootMesh->GetComponentLocation();
		bool bIsFallenOff = IsMeshInImpossibleOrientation();

		// If the mesh is in an unhandleable position, make it disappear
		if (bIsFallenOff)
		{
			SpawnDeadSkater();
			OnFallTriggered.Broadcast();
			bPlayerFallen = true;

			ABGTaskGameMode* GameMode = GetWorld()->GetAuthGameMode<ABGTaskGameMode>();
			if (GameMode)
			{
				GameMode->GameOver();
			}
		}
	}
}

bool ASkatePawn::IsMovingOnGround()
{

	FVector Velocity = RootMesh->GetComponentVelocity();
	float LinearVelocityXY = FVector(Velocity.X, Velocity.Y, 0).Size();

	return IsNearGround() && LinearVelocityXY >= 10;
}

// Spawn the dead skater actor at the specified location
void ASkatePawn::SpawnDeadSkater()
{
	if (DeadSkaterClass)
	{		
		AActor* DeadSkaterActor = GetWorld()->SpawnActor<AActor>(DeadSkaterClass, GetActorLocation(), FRotator::ZeroRotator);
	}
}

bool ASkatePawn::IsMeshInImpossibleOrientation()
{
	// Get the mesh's rotation
	FRotator MeshRotation = RootMesh->GetComponentRotation();

	// Check if the mesh is upside-down (rotated more than 90 degrees around the X-axis)
	bool bIsUpsideDown = FMath::Abs(MeshRotation.Pitch) > 90.0f;

	// Check if the mesh is tilted sideways (rotated more than 45 degrees around the Z-axis)
	bool bIsTiltedSideways = FMath::Abs(MeshRotation.Roll) > 90.0f;

	// Return true if the mesh is in an impossible orientation
	return bIsUpsideDown || bIsTiltedSideways;
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

	// Perform rotation on tick only when player is still
	if (bTickRotate)
	{
		FRotator RotationDelta = FRotator(0.0f, TickRotationSpeed * DeltaTime * DirectionMultiplier, 0.0f);
		AddActorWorldRotation(RotationDelta);
	}

	// Adjust character mesh position if the player is moving (this is because the asset has a different offset than the other animations)
	if (BodyMesh)
	{		
		BodyMesh->SetRelativeLocation(IsMovingOnGround() ? MovingBodyPosition : DefaultBodyPosition);
		BodyMesh->SetRelativeRotation(IsMovingOnGround() ? MovingBodyRotation : DefaultBodyRotation);
	}

	// Check if the player has fallen off skate
	CheckFallenOff();

}

// Called to bind functionality to input
void ASkatePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

