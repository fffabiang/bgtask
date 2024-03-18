// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleActor.h"
#include "Characters/SkatePawn.h"
#include "Core/BGTaskGameMode.h"

// Sets default values
AObstacleActor::AObstacleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set up root component
    ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
    RootComponent = ObstacleMesh;

    // Set up pass trigger box component
    PassTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PassTrigger"));
    PassTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PassTrigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    PassTrigger->SetupAttachment(RootComponent);
    PassTrigger->OnComponentEndOverlap.AddDynamic(this, &AObstacleActor::OnPassTriggerEndOverlap);

    // Add overlay material to mesh
    if (HighlightMaterial)
    {
        ObstacleMesh->SetOverlayMaterial(HighlightMaterial);
    }

    // Set default points
    Points = 0;

}

void AObstacleActor::OnPassTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    
    if (bPassed)
        return;
    
    ASkatePawn* PlayerCharacter = Cast<ASkatePawn>(OtherActor);
    if (PlayerCharacter)
    {
        ABGTaskGameMode* GameMode = GetWorld()->GetAuthGameMode<ABGTaskGameMode>();
        if (GameMode)
        {
            bPassed = true;
            GameMode->PassObstacle(this);
            ObstacleMesh->SetOverlayMaterial(nullptr);
        }
    }
}

// Called when the game starts or when spawned
void AObstacleActor::BeginPlay()
{
	Super::BeginPlay();

    if (HighlightMaterial)
    {
        ObstacleMesh->SetOverlayMaterial(HighlightMaterial);
    }

	
}

// Called every frame
void AObstacleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

