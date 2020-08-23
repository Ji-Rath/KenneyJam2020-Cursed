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

	virtual void BeginDestroy() override;

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
	AInterestLocation* TownSquareLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<Happiness> PlayerRelation = Neutral;

	//Friend NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ANPCBase* FriendRef;

	//Nemesis NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ANPCBase* EnemyRef;

	UFUNCTION(BlueprintImplementableEvent)
	void VillagerDeath();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowEmotion(UTexture2D* Texture, float Duration) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> SadEmote;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> HappyEmote;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> NeutralEmote;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSleeping = false;

	//Called to show emote bubble when player interacts with NPC
	UFUNCTION()
	void PlayerInteract();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACharacter* TalkingTo;
};
