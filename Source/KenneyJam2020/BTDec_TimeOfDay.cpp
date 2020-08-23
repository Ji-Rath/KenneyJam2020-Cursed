// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDec_TimeOfDay.h"
#include "Kismet/GameplayStatics.h"
#include "KenneyJam2020GameModeBase.h"

bool UBTDec_TimeOfDay::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	AKenneyJam2020GameModeBase* GameMode = Cast<AKenneyJam2020GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameMode)
		return GameMode->TimeOfDay == DayCheck;

	return false;
}
