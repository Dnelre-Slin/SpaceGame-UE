// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDoubleDoorComponent.h"

// Sets default values for this component's properties
UInteractiveDoubleDoorComponent::UInteractiveDoubleDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UStaticMesh>BasicDoorMeshConstructor(TEXT("StaticMesh'/Game/Meshes/BasicDoor.BasicDoor'"));
	UStaticMesh* BasicDoorMesh = BasicDoorMeshConstructor.Object;

	FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

	UStaticMeshComponent* door1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh1"));
	door1->AttachToComponent(this, rules);
	door1->SetStaticMesh(BasicDoorMesh);
	door1->AddLocalOffset(FVector(50, 0, 0));

	UStaticMeshComponent* door2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh2"));
	door2->AttachToComponent(this, rules);
	door2->SetStaticMesh(BasicDoorMesh);
	door2->AddLocalOffset(FVector(-50, 0, 0));
	// ...
}


// Called when the game starts
void UInteractiveDoubleDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractiveDoubleDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractiveDoubleDoorComponent::TestButton()
{
	AActor* ownerActor = this->GetOwner();

	if (ownerActor != nullptr)
	{
		USceneComponent* extraComp = CreateDefaultSubobject<USceneComponent>(TEXT("ExtraComp"));
		extraComp->SetHiddenInGame(false, true);
		ownerActor->SetRootComponent(extraComp);
		//UActorComponent* comp = ownerActor->AddComponent(FName("StaticMeshComponent"), true, FTransform::Identity, nullptr);
		//if (comp == nullptr)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("No Sigar"))
		//}
	}
}

void UInteractiveDoubleDoorComponent::SetupAutoComponents()
{
	AActor* ownerActor = this->GetOwner();

	if (ownerActor != nullptr)
	{
		//USceneComponent* extraComp = CreateDefaultSubobject<USceneComponent>(TEXT("ExtraComp"));
		//extraComp->SetHiddenInGame(false, true);
		//ownerActor->SetRootComponent(extraComp);
		//FTransform transform;
		//transform.SetLocation(FVector(50, 0, 0));
		//UActorComponent* comp = ownerActor->AddComponent(FName("StaticMeshComponent"), false, transform, nullptr);
		//if (comp == nullptr)
		//{
		//	UE_LOG(LogTemp, Log, TEXT("No Sigar"))
		//}

		////static ConstructorHelpers::FObjectFinder<UStaticMesh>BasicDoorMeshConstructor(TEXT("StaticMesh'/Game/Meshes/BasicDoor.BasicDoor'"));
		////UStaticMesh* BasicDoorMesh = BasicDoorMeshConstructor.Object;

		//FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);

		//UStaticMeshComponent* door1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh1"));
		////door1->AttachToComponent(this, rules);
		////door1->SetStaticMesh(BasicDoorMesh);
	}
}

