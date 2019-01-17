// John deere confidential

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();

	// Called when grab is released
	void Release();

	// Find attached phyusics handle
	void FindPhysicsHandleComponent();

	// Setup attachedinput component
	void SetupInputComponent();

	//return hit for first physics body in reach

	const FHitResult GetFirstPhysicsBodyInReach();

};
