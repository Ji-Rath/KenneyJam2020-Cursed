// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"
#include "KenneyJam2020GameModeBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPCBase::BeginDestroy()
{
	Super::BeginDestroy();

	//Add actor to dead array
	AKenneyJam2020GameModeBase* GameMode = Cast<AKenneyJam2020GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameMode)
		GameMode->DeadNPCArray.Add(this);

	//Update status of other NPC's
	TArray<AActor*> NPCArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCBase::GetClass(), NPCArray);
	for (AActor* NPC : NPCArray)
	{
		NPC = Cast<ANPCBase>(NPC);
		if (FriendRef == this)
		{
			PlayerRelation = Sad;
		}
		else if (EnemyRef == this)
		{
			PlayerRelation = Happy;
		}
	}
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::PlayerInteract()
{
	int32 RandInt = FMath::RandRange(0, 2);
	switch (PlayerRelation)
	{
	case Happy:
		ShowEmotion(HappyEmote[RandInt], 5.f);
		break;
	case Neutral:
		ShowEmotion(NeutralEmote[RandInt], 5.f);
		break;
	case Sad:
		ShowEmotion(SadEmote[RandInt], 5.f);
		break;
	}
}

