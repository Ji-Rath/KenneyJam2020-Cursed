// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMoveState.generated.h"

UENUM()
enum MoveState
{
	Walk,
	Run
};

/**
 * Set movement state for NPC
 */
UCLASS()
class KENNEYJAM2020_API UBTTask_SetMoveState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<MoveState> MovingState = Walk;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
