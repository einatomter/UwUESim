// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSSensors.h"

// Sets default values for this component's properties
UROSSensors::UROSSensors()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UROSSensors::BeginPlay()
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

    // Initialize topics
    
    // Pressure
    //PressurePublisher = NewObject<UTopic>(UTopic::StaticClass());
    //PressurePublisher->Init(rosinst->ROSIntegrationCore, TEXT("/unreal_ros/pressure"), TEXT("std_msgs/Float32"));

    //ImuSubscriber = NewObject<UTopic>(UTopic::StaticClass());
    //ImuSubscriber->Init(rosinst->ROSIntegrationCore, TEXT("/x3/floatpressure"), TEXT("std_msgs/Float32"));
    
    // IMU
    ImuPublisher = NewObject<UTopic>(UTopic::StaticClass());
    ImuPublisher->Init(rosinst->ROSIntegrationCore, TEXT("/unreal_ros/imu"), TEXT("sensor_msgs/Imu"));

    ImuSubscriber = NewObject<UTopic>(UTopic::StaticClass());
    ImuSubscriber->Init(rosinst->ROSIntegrationCore, TEXT("/x3/imu"), TEXT("sensor_msgs/Imu"));


    // Imu Callback function
    std::function<void(TSharedPtr<FROSBaseMsg>)> CallbackImu = [this](TSharedPtr<FROSBaseMsg> msg) -> void
    {
        auto Concrete = StaticCastSharedPtr<ROSMessages::sensor_msgs::Imu>(msg);
        if (Concrete.IsValid())
        {
            // Construct message
            TSharedPtr<ROSMessages::sensor_msgs::Imu> ImuMessage(new ROSMessages::sensor_msgs::Imu());

            // Header
            ImuMessage->header.seq = 0;
            ImuMessage->header.time = FROSTime::Now();
            ImuMessage->header.frame_id = Concrete->header.frame_id;

            // Orientation
            ImuMessage->orientation.x = Concrete->orientation.x;
            ImuMessage->orientation.y = Concrete->orientation.y;
            ImuMessage->orientation.z = Concrete->orientation.z;
            ImuMessage->orientation.w = Concrete->orientation.w;

            ImuMessage->orientation_covariance = Concrete->orientation_covariance;

            // Angular velocity
            ImuMessage->angular_velocity.x = Concrete->angular_velocity.x;
            ImuMessage->angular_velocity.y = Concrete->angular_velocity.y;
            ImuMessage->angular_velocity.z = Concrete->angular_velocity.z;

            ImuMessage->angular_velocity_covariance = Concrete->angular_velocity_covariance;

            // Linear acceleration
            ImuMessage->linear_acceleration.x = Concrete->linear_acceleration.x;
            ImuMessage->linear_acceleration.y = Concrete->linear_acceleration.y;
            ImuMessage->linear_acceleration.z = Concrete->linear_acceleration.z;

            ImuMessage->linear_acceleration_covariance = Concrete->linear_acceleration_covariance;


            ImuPublisher->Publish(ImuMessage);

            //UE_LOG(LogTemp, Log, TEXT("A: %lf %lf %lf"), 
            //    Concrete->linear_acceleration.x,
            //    Concrete->linear_acceleration.y,
            //    Concrete->linear_acceleration.z);

            //UE_LOG(LogTemp, Log, TEXT("G: %lf %lf %lf"),
            //    Concrete->angular_velocity.x,
            //    Concrete->angular_velocity.y,
            //    Concrete->angular_velocity.z);
        }
        return;
    };

    ImuSubscriber->Subscribe(CallbackImu);

}


// Called every frame
void UROSSensors::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

