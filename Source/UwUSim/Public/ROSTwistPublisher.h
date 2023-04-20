// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/Twist.h"

#include "ROSTwistPublisher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UWUSIM_API UROSTwistPublisher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UROSTwistPublisher();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ROS")
	FString TeleopPublisherTopicName;

	UPROPERTY(Transient)
	UTopic* TeleopPublisherTopic;

	UFUNCTION(BlueprintCallable, Category = "ROS")
	void PublishTwist(FVector Linear, float Yaw);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
