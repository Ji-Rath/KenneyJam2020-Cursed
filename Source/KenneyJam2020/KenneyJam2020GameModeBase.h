// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KenneyJam2020GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KENNEYJAM2020_API AKenneyJam2020GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	//Whether player is in a cutscene
	bool bCutScene = false;

	//0 = SunRise, 1 = MidDay, 2 = SunSet, 3 = Midnight
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TimeOfDay = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ANPCBase*> DeadNPCArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
