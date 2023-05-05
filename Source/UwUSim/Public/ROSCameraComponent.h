// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/sensor_msgs/CameraInfo.h"
#include "ROSIntegration/Public/sensor_msgs/Image.h"

#include "ROSPawn.h"

#include "StopTime.h"
#include "ImageData.h"

#include "ROSCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class UWUSIM_API UROSCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
    UROSCameraComponent();
    ~UROSCameraComponent();

    UPROPERTY(EditAnywhere, Category = "Vision Component")
        uint32 Width;
    UPROPERTY(EditAnywhere, Category = "Vision Component")
        uint32 Height;
    UPROPERTY(EditAnywhere, Category = "Vision Component")
        float Framerate;
    UPROPERTY(EditAnywhere, Category = "Vision Component")
        bool UseEngineFramerate;
    UPROPERTY(EditAnywhere, Category = "Vision Component")
        int32 ServerPort;

    // Camera for color
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Component")
        USceneCaptureComponent2D* SceneCapture;

    UPROPERTY(BlueprintReadWrite, Category = "Vision Component")
        FString ImageFrame = TEXT("/unreal_ros/image_frame");

    // TODO: remove, unused
    UPROPERTY(BlueprintReadWrite, Category = "Vision Component")
        FString ImageOpticalFrame = TEXT("/unreal_ros/image_optical_frame");

    //UPROPERTY(Transient, EditAnywhere, Category = "Vision Component")
    UPROPERTY(Transient)
        UTopic* CameraInfoPublisher;

    //UPROPERTY(Transient, EditAnywhere, Category = "Vision Component")
    UPROPERTY(Transient)
        UTopic* ImagePublisher;

protected:

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

    float FrameTime, TimePassed;
    bool messageSent;

private:
    AROSPawn* owner = Cast<AROSPawn>(GetOwner());

    // Private data container
    ImageData* CurrentImage;

    TArray<FFloat16Color> ImageColor;

    void ReadImage(UTextureRenderTarget2D* RenderTarget, TArray<FFloat16Color>& ImageData) const;
    void ReadImage2(UTextureRenderTarget2D* RenderTarget, TArray<FFloat16Color>& ImageData) const;
    void SaveImageData(const TArray<FFloat16Color>& ImageData, uint8* Bytes, bool bMono = false) const;

};
