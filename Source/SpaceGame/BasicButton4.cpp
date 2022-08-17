// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicButton4.h"

// Sets default values
ABasicButton4::ABasicButton4()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicButton4::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicButton4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicButton4::OnInteract_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("AMAZING!"));
}

