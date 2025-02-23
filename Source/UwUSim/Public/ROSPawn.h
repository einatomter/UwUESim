// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/geometry_msgs/Pose.h"
#include "ROSIntegration/Public/rosgraph_msgs/Clock.h"
#include "ROSIntegration/Public/std_msgs/String.h"

//#include "ROSCameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

#include "ROSPawn.generated.h"

UCLASS()
class UWUSIM_API AROSPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AROSPawn();

	UPROPERTY(Transient)
	UTopic* ClockTopic;

	UPROPERTY(Transient)
	UTopic* PoseTopic;

	UFUNCTION(BlueprintCallable, Category = "ROSPawn Actions")
	FVector GetROSPosePosition();

	UFUNCTION(BlueprintCallable, Category = "ROSPawn Actions")
	FQuat GetROSPoseOrientation();

	UFUNCTION(BlueprintCallable, Category = "ROSPawn Actions")
	bool IsROSInitialized();

	ROSMessages::rosgraph_msgs::Clock ROSTimestamp;
	FROSTime ROSLocalTimestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USceneCaptureComponent2D* SceneCapture;

	USceneCaptureComponent2D* GetSceneCaptureComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	FVector ROSPosePosition;
	FQuat ROSPoseOrientation;

	bool RosInitialized;
	bool ReceivedTimestamp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
