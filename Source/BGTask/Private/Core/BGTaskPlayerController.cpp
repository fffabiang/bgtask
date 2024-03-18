// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BGTaskPlayerController.h"

#include "Characters/SkatePawn.h"
#include "Kismet/GameplayStatics.h"


void ABGTaskPlayerController::EnableSkateMapping(bool enable)
{
	EnableMappingContext(enable, SkateMappingContext);
}

void ABGTaskPlayerController::EnableGameOverMapping(bool enable)
{
	EnableMappingContext(enable, GameOverMappingContext);
}

void ABGTaskPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABGTaskPlayerController::BeginPlay()
{
	Super::BeginPlay();

	EnableMappingContext(true, SkateMappingContext);
}

void ABGTaskPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{

		//Accelerate
		EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &ABGTaskPlayerController::OnAccelerateTriggered);

		//Steer
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &ABGTaskPlayerController::OnSteerTriggered);
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Completed, this, &ABGTaskPlayerController::OnSteerReleased);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABGTaskPlayerController::OnJumpTriggered);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABGTaskPlayerController::OnJumpCanceled);

		// Game Over mapping
		EnhancedInputComponent->BindAction(RestartLevelAction, ETriggerEvent::Triggered, this, &ABGTaskPlayerController::OnRestartLevelTriggered);		

	}
}

bool ABGTaskPlayerController::EnableMappingContext(bool enable, UInputMappingContext* IMC)
{
	bool contextUpdated = false;

	if (IMC != nullptr)
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{

			bool mappingContextExists = Subsystem->HasMappingContext(IMC);

			if (enable && !mappingContextExists)
			{
				UE_LOG(LogTemp, Log, TEXT("Enabling IMC %s"), *(IMC->GetName()));
				Subsystem->AddMappingContext(IMC, 0);
				contextUpdated = true;
			}
			else if (mappingContextExists && !enable)
			{
				UE_LOG(LogTemp, Log, TEXT("Disabling IMC %s"), *(IMC->GetName()));
				Subsystem->RemoveMappingContext(IMC);
				contextUpdated = true;
			}
			else
			{
				// Context already set in that value (return true regardless)
				UE_LOG(LogTemp, Warning, TEXT("Context exists (%d) cant update to (%d)."), mappingContextExists ? 1 : 0, enable ? 1 : 0);
				contextUpdated = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cant get EnhancedInput system. Aborting input context update."));
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid IMC reference passed."));
	}

	return contextUpdated;
}

void ABGTaskPlayerController::OnAccelerateTriggered(const FInputActionValue& Value)
{
	ASkatePawn* SkatePawn = Cast<ASkatePawn>(GetPawn());
	if (SkatePawn)
	{
		SkatePawn->Move(Value);
	}
}

void ABGTaskPlayerController::OnSteerTriggered(const FInputActionValue& Value)
{
	ASkatePawn* SkatePawn = Cast<ASkatePawn>(GetPawn());
	if (SkatePawn)
	{
		SkatePawn->Steer(Value);
	}
}

void ABGTaskPlayerController::OnJumpTriggered()
{
	ASkatePawn* SkatePawn = Cast<ASkatePawn>(GetPawn());
	if (SkatePawn)
	{
		SkatePawn->Jump();
	}
}

void ABGTaskPlayerController::OnJumpCanceled()
{
}

void ABGTaskPlayerController::OnSteerReleased()
{
	ASkatePawn* SkatePawn = Cast<ASkatePawn>(GetPawn());
	if (SkatePawn)
	{
		SkatePawn->StopSteer();
	}
}

void ABGTaskPlayerController::OnRestartLevelTriggered()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}
