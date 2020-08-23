// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ShowEmote.h"
#include "AIController.h"
#include "NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindObjectLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	int32 RandInt = FMath::RandRange(0, 2);
	ANPCBase* NPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (IsValid(NPC))
	{
		NPC->ShowEmotion(NPC->HappyEmote[RandInt], 5.f);

		ANPCBase* FriendNPC = Cast<ANPCBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
		if (IsValid(FriendNPC))
		{
			FriendNPC->ShowEmotion(FriendNPC->HappyEmote[RandInt], 5.f);
			FriendNPC->TalkingTo = NPC;
		}
	}

	return EBTNodeResult::Succeeded;
}