// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "GameFramework/ForceFeedbackEffect.h"

#include "BGTaskHUD.h"

#include "BGTaskPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BGTASK_API ABGTaskPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Parameters

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* SkateMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Gameplay", meta = (AllowPrivateAccess = "true"))
	class UInputAction* AccelerateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Gameplay", meta = (AllowPrivateAccess = "true"))
	class UInputAction* SteerAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Gameplay", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;


protected:

	void PostInitializeComponents() override;
	virtual void BeginPlay();
	virtual void SetupInputComponent() override;


private:
	bool EnableMappingContext(bool enable, UInputMappingContext* IMC);

	void OnAccelerateTriggered(const FInputActionValue& Value);
	void OnSteerTriggered(const FInputActionValue& Value);
	void OnJumpTriggered();
	void OnJumpCanceled();

	
};
