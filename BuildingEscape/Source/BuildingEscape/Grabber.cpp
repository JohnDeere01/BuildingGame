// John deere confidential

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();	
}

// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error, no component found: You need to add ""PhysicsHandler"" to %s"), *(GetOwner()->GetName()));
	}
}

// Look for attached Input Component (only appears at run time)
void UGrabber::SetupInputComponent()
{
	
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error, no component found: You need to add ""PhysicsHandler"" to %s"), *(GetOwner()->GetName()));
	}
}




void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"));

	/// Try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	/// If we hit something then attach a physics handle
	if (ActorHit)
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // Allow rotation
		);
	}
	
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key released"));

	//TODO release physics handle
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PlayerViewPointLocation = GetOwner()->GetActorLocation();
	PlayerViewPointRotation = GetOwner()->GetInstigatorController()->GetControlRotation();
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// LINE TRACE and see if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);

	}
		

	// Get the player view point this tick



}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	PlayerViewPointLocation = GetOwner()->GetActorLocation();
	PlayerViewPointRotation = GetOwner()->GetInstigatorController()->GetControlRotation();
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	//Set up querry parrameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
	
	

	return Hit;
}
