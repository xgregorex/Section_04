// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankGame.h"
#include "Tank.h"
#include "GameFramework/Controller.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if( GetPlayerTank() )
	{
		GetControlledTank()->AimAt( GetPlayerTank()->GetActorLocation() );
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if( !PlayerPawn ) { return nullptr; }
	return Cast<ATank>( PlayerPawn );
}



