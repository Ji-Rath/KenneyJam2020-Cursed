// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "NPCBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	//Setup camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	BoxInteract = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere Interact"));
	BoxInteract->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APlayerBase::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &APlayerBase::OnEndOverlap);

	SpringArmLength = SpringArm->TargetArmLength;
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Manage spring arm length transitions when interacting
	if (bInteracting && SpringArm->TargetArmLength >= SpringArmInteractLength)
	{
		SpringArm->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArm->TargetArmLength, SpringArmInteractLength, DeltaTime, SpringArmSpeed);
	}
	else
	{
		SpringArm->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArm->TargetArmLength, SpringArmLength, DeltaTime, SpringArmSpeed);
	}
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerBase::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerBase::Interact);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void APlayerBase::MoveForward(float AxisValue)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(GetControlRotation()) * 1000.f, AxisValue);
}

void APlayerBase::MoveRight(float AxisValue)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotation()) * 1000.f, AxisValue);
}

void APlayerBase::Interact()
{
	//If interact NPC is valid, show random emote bubble based on relation
	if (IsValid(InteractRef))
	{
		if (!InteractRef->bSleeping)
		{
			InteractRef->PlayerInteract();
			bInteracting = true;
			InteractRef->TalkingTo = this;
		}
		else
		{
			SacrificeMessage(InteractRef);
		}
		if(SoundNPC)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundNPC, GetActorLocation());
	}
}

void APlayerBase::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<ANPCBase>(OtherActor))
	{
		InteractRef = Cast<ANPCBase>(OtherActor);
	}
}

void APlayerBase::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<ANPCBase>(OtherActor))
	{
		InteractRef = nullptr;
		bInteracting = false;
	}
}

