// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSPawn.h"

// Sets default values
AROSPawn::AROSPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

FVector AROSPawn::GetROSPosePosition()
{
    return ROSPosePosition;
}

FQuat AROSPawn::GetROSPoseOrientation()
{
    return ROSPoseOrientation;
}

bool AROSPawn::IsROSInitialized()
{
    return RosInitialized;
}

// Called when the game starts or when spawned
void AROSPawn::BeginPlay()
{
	Super::BeginPlay();

    RosInitialized = false;
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
    
    // Check for valid ROS instance
    if (!rosinst)
    {
        UE_LOG(LogActor, Warning, TEXT("UnrealROSInstance not existing."));
        return;
    }

    // Check if instance is connected to ROS
    if (!rosinst->bConnectToROS)
    {
        UE_LOG(LogActor, Warning, TEXT("Connect to ROS is disabled"));
        return;
    }

    RosInitialized = true;

	PoseTopic = NewObject<UTopic>(UTopic::StaticClass());
    PoseTopic->Init(rosinst->ROSIntegrationCore, TEXT("/x3/pose_raw"), TEXT("geometry_msgs/Pose"));

    // Create a std::function callback object
    // TODO use std::bind to create callback function outside of BeginPlay
    std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = [this](TSharedPtr<FROSBaseMsg> msg) -> void
    {
        auto Concrete = StaticCastSharedPtr<ROSMessages::geometry_msgs::Pose>(msg);
        if (Concrete.IsValid())
        {
            ROSPosePosition.X = Concrete->position.x;
            ROSPosePosition.Y = -Concrete->position.y;
            ROSPosePosition.Z = Concrete->position.z;

            ROSPoseOrientation.W = Concrete->orientation.w;
            ROSPoseOrientation.X = Concrete->orientation.x;
            ROSPoseOrientation.Y = Concrete->orientation.y;
            ROSPoseOrientation.Z = Concrete->orientation.z;

            //UE_LOG(LogTemp, Log, TEXT("Pose: %lf %lf %lf"), Concrete->position.x, Concrete->position.y, Concrete->position.z);
        }
        return;
    };

    PoseTopic->Subscribe(SubscribeCallback);
}

// Called every frame
void AROSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AROSPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

