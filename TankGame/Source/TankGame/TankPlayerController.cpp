// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankGame.h"
#include "GameFramework/Controller.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

void ATankPlayerController::AimTowardCrosshair()
{
	if( !GetControlledTank() ){ return; }

	FVector HitLocation; //Out parameter
	if( GetSightRayHitLocation( HitLocation ) )
	{
		GetControlledTank()->AimAt( HitLocation );
	}
}

//returns true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector &HitLocation ) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize( ViewportSizeX, ViewportSizeY );
	auto ScreenLocation = FVector2D( ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation );
	
	FVector LookDirection;
	if( GetLookDirection( ScreenLocation, LookDirection ) )
	{
		GetLookVectorHitLocation( LookDirection, HitLocation );
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector &LookDirection ) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld( ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection );
}

bool ATankPlayerController::GetLookVectorHitLocation( FVector LookDirection, FVector &HitLocation ) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if( GetWorld()->LineTraceSingleByChannel( HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility ) )
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector( 0 );
	return false;
}

