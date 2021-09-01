// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ScrubRacer/ScrubRacerGameModeBase.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Character Movement"));

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<AScrubRacerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	BoxCollider->OnComponentHit.AddDynamic(this, &APlayerPawn::OnHit);

	if (GetController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Has controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO CONTROLLER"));
	}
}

void APlayerPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	if (HitComponent != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Component %s"), *HitComponent->GetName());
		// UE_LOG(LogTemp, Warning, HitComponent->GetName());
	}
	if (OtherActor != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Other Actor %s"), *OtherActor->GetName());
	}
	// Hit.GetComponent()->GetName();
	if (OtherActor && !OtherActor->GetName().Equals("Floor"))
	{
		Speed = 0.0f;
		UE_LOG(LogTemp, Warning, TEXT("WE'VE BEEN HIT"));
	}
	// Game over
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveLeft", this, &APlayerPawn::MoveLeft);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);
}

void APlayerPawn::MoveLeft(float Value)
{
	Move(Value);
}

void APlayerPawn::MoveRight(float Value)
{
	Move(Value);
}

void APlayerPawn::Move(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move: %f"), Value * Speed);
	AddActorLocalOffset(FVector(0, Value * Speed, 0));
}
