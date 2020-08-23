// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetMoveState.h"
#include "NPCBase.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_SetMoveState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANPCBase* NPCCharacter = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetCharacter());
	if(MovingState == Walk)
		NPCCharacter->GetCharacterMovement()->MaxWalkSpeed = NPCCharacter->WalkSpeed;
	else
		NPCCharacter->GetCharacterMovement()->MaxWalkSpeed = NPCCharacter->RunSpeed;

	return EBTNodeResult::Succeeded;
}
