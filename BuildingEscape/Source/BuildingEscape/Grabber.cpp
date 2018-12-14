// John deere confidential

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty !!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point this tick



	ActorLocation = GetOwner()->GetActorLocation().ToString();
	ActorRotation = GetOwner()->GetInstigatorController()->GetControlRotation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("Location: %s  Rotation: %s"), *ActorLocation, *ActorRotation);
	// Ray-cast out to reach distance

	// See what we hit
}

