// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSTwistPublisher.h"

// Sets default values for this component's properties
UROSTwistPublisher::UROSTwistPublisher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TeleopPublisherTopicName = TEXT("/cmd_vel");
}


void UROSTwistPublisher::PublishTwist(FVector Linear, float Yaw)
{
	if (TeleopPublisherTopic)
	{
		TSharedPtr<ROSMessages::geometry_msgs::Twist> TwistMsg(new ROSMessages::geometry_msgs::Twist());

		// Linear component
		TwistMsg->linear.x = Linear.X;
		TwistMsg->linear.y = Linear.Y;
		TwistMsg->linear.z = Linear.Z;

		// Convert FQuat to FRotator to get Euler angles
		TwistMsg->angular.x = 0;
		TwistMsg->angular.y = 0;
		TwistMsg->angular.z = Yaw;

		TeleopPublisherTopic->Publish(TwistMsg);
	}
}

// Called when the game starts
void UROSTwistPublisher::BeginPlay()
{
	Super::BeginPlay();

	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());

	// Check for valid ROS instance
	if (!rosinst)
	{
		UE_LOG(LogActorComponent, Warning, TEXT("UnrealROSInstance not existing."));
		return;
	}

	// Check if instance is connected to ROS
	if (!rosinst->bConnectToROS)
	{
		UE_LOG(LogActorComponent, Warning, TEXT("Connect to ROS is disabled"));
		return;
	}

	TeleopPublisherTopic = NewObject<UTopic>(UTopic::StaticClass());
	TeleopPublisherTopic->Init(rosinst->ROSIntegrationCore, TeleopPublisherTopicName, TEXT("geometry_msgs/Twist"));
	TeleopPublisherTopic->Advertise();
}


// Called every frame
void UROSTwistPublisher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

