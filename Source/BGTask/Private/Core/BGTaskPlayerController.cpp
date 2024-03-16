// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BGTaskPlayerController.h"

void ABGTaskPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABGTaskPlayerController::BeginPlay()
{
	Super::BeginPlay();
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

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABGTaskPlayerController::OnJumpTriggered);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABGTaskPlayerController::OnJumpCanceled);


	}
}

void ABGTaskPlayerController::OnAccelerateTriggered(const FInputActionValue& Value)
{

}

void ABGTaskPlayerController::OnSteerTriggered(const FInputActionValue& Value)
{
}

void ABGTaskPlayerController::OnJumpTriggered()
{
}

void ABGTaskPlayerController::OnJumpCanceled()
{
}
