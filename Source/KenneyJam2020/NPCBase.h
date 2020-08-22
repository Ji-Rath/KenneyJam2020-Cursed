// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

class AInterestLocation;

UENUM()
enum Happiness
{
	Happy,
	Neutral,
	Sad
};

UCLASS()
class KENNEYJAM2020_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInterestLocation* HouseLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AInterestLocation* WorkLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<Happiness> PlayerRelation = Neutral;
};
