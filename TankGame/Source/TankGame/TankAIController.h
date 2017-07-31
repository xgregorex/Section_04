// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank * GetControlledTank() const;
	ATank * GetPlayerTank() const;
	void BeginPlay() override;
	void Tick( float DeltaTime ) override;
	
};
