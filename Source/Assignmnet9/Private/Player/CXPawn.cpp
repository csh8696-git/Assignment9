// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CXPawn.h"
#include "Assignmnet9.h"

// Sets default values
ACXPawn::ACXPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACXPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = Assignment9FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CSPawn::BeginPlay() %s [%s]"),
		*Assignment9FunctionLibrary::GetNetModeString(this), *NetRoleString);
	Assignment9FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ACXPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = Assignment9FunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CSPawn::PossessedBy() %s [%s]"), 
		*Assignment9FunctionLibrary::GetNetModeString(this), *NetRoleString);
	Assignment9FunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

// Called every frame
void ACXPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACXPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

