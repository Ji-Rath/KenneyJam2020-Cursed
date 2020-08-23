// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class ANPCBase;

UCLASS()
class KENNEYJAM2020_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	float SpringArmInteractLength = 500.f;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxInteract;

	UPROPERTY(EditAnywhere)
	float SpringArmSpeed = 5.f;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SacrificeMessage(ANPCBase* NPCReference);

	UPROPERTY(EditAnywhere);
	USoundBase* SoundNPC;

private:
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Interact();

	float SpringArmLength;

	ANPCBase* InteractRef;

	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	bool bInteracting;

};
