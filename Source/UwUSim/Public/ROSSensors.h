// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/sensor_msgs/Imu.h"
#include "ROSIntegration/Public/std_msgs/Float32.h"

#include "ROSSensors.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UWUSIM_API UROSSensors : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UROSSensors();

	//UPROPERTY(Transient, EditAnywhere, Category = "Sensor Component")
	UPROPERTY(Transient)
		UTopic* PressureSubscriber;

	UPROPERTY(Transient)
		UTopic* PressurePublisher;

	//UPROPERTY(Transient, EditAnywhere, Category = "Sensor Component")
	UPROPERTY(Transient)
		UTopic* ImuSubscriber;

	UPROPERTY(Transient)
		UTopic* ImuPublisher;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ROSMessages::sensor_msgs::Imu ImuMsg;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
