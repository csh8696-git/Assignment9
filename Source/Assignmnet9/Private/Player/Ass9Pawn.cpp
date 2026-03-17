// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ass9Pawn.h"

// Sets default values
AAss9Pawn::AAss9Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAss9Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAss9Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAss9Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

