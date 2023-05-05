// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSPawn.h"

// Sets default values
AROSPawn::AROSPawn()
{
	PrimaryActorTick.bCanEverTick = true;

    // Create and attach the scene capture component
    SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
    SceneCapture->TextureTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("ColorTarget"));
    SceneCapture->TextureTarget->InitAutoFormat(1920, 1080);
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

USceneCaptureComponent2D* AROSPawn::GetSceneCaptureComponent()
{
    return SceneCapture;
}

// Called when the game starts or when spawned
void AROSPawn::BeginPlay()
{
	Super::BeginPlay();

    RosInitialized = false;
    ReceivedTimestamp = false;

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

    // Initialize Clock topic
    ClockTopic = NewObject<UTopic>(UTopic::StaticClass());
    ClockTopic->Init(rosinst->ROSIntegrationCore, TEXT("/clock"), TEXT("rosgraph_msgs/Clock"));
    ClockTopic->Subscribe([this](TSharedPtr<FROSBaseMsg> msg) {
        auto Concrete = StaticCastSharedPtr<ROSMessages::rosgraph_msgs::Clock>(msg);
        if (Concrete.IsValid())
        {
            //if (ReceivedTimestamp == false)
            //{
            //    ReceivedTimestamp = true;
            //    ROSLocalTimestamp.SetUseSimTime(true);
            //    ROSLocalTimestamp.SetSimTime(Concrete->_Clock);
            //}
            //else
                //UE_LOG(LogTemp, Log, TEXT("Local clock: %u %u"), ROSLocalTimestamp._Sec, ROSLocalTimestamp._NSec);

            ROSTimestamp._Clock = Concrete->_Clock;
            //UE_LOG(LogTemp, Log, TEXT("Clock: %u %u"), Concrete->_Clock._Sec, Concrete->_Clock._NSec);
        }
        return;
        });


    // Initialize Pose topic
	PoseTopic = NewObject<UTopic>(UTopic::StaticClass());
    PoseTopic->Init(rosinst->ROSIntegrationCore, TEXT("/x3/pose_raw"), TEXT("geometry_msgs/Pose"));

    // Define lambda as callback function
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

