// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSCameraComponent.h"

UROSCameraComponent::UROSCameraComponent() :
    Width(960),
    Height(540),
    Framerate(20),
    UseEngineFramerate(false),
    ServerPort(9090),
    TimePassed(0),
    messageSent(false)
{
    FieldOfView = 90.0;
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;

    auto owner = GetOwner();
    if (owner)
    {
        Color = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("ColorCapture"));
        Color->SetupAttachment(this);
        Color->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
        Color->TextureTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("ColorTarget"));
        Color->TextureTarget->InitAutoFormat(Width, Height);
        Color->FOVAngle = FieldOfView;
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("No owner!"));
    }



}

UROSCameraComponent::~UROSCameraComponent()
{
    delete CurrentImage;
}


void UROSCameraComponent::InitializeComponent()
{
    Super::InitializeComponent();
    FrameTime = 1.0f / Framerate;
}

void UROSCameraComponent::BeginPlay()
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

    // Initializing buffers for reading images from the GPU
    ImageColor.AddUninitialized(Width * Height);
    Color->TextureTarget->InitAutoFormat(Width, Height);


    // TODO: Are these necessary?
    // Reinit renderer
    Color->TextureTarget->InitAutoFormat(Width, Height);
    AspectRatio = Width / (float)Height;

    CurrentImage = new ImageData(Width, Height);


    // Initialize topics
    // TODO: allow topic selection from editor
    CameraInfoPublisher = NewObject<UTopic>(UTopic::StaticClass());
    ImagePublisher = NewObject<UTopic>(UTopic::StaticClass());

    CameraInfoPublisher->Init(rosinst->ROSIntegrationCore,
        TEXT("/unreal_ros/camera_info"),
        TEXT("sensor_msgs/CameraInfo"));
    CameraInfoPublisher->Advertise();

    ImagePublisher->Init(rosinst->ROSIntegrationCore,
        TEXT("unreal_ros/image_color"),
        TEXT("sensor_msgs/Image"));
    ImagePublisher->Advertise();

}

void UROSCameraComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UROSCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction)
{
    Super::TickComponent(DeltaTime, TickType, TickFunction);

    UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetOwner()->GetGameInstance());

    // Check for valid ROS instance
    if (!rosinst)
    {
        return;
    }

    // Check if instance is connected to ROS
    if (!rosinst->bConnectToROS)
    {
        return;
    }


    // Check for framerate
    TimePassed += DeltaTime;
    if (!UseEngineFramerate && TimePassed < FrameTime)
    {
        return;
    }
    TimePassed -= FrameTime;
    MEASURE_TIME("Tick");


    // CANDO: convert to grayscale to reduce latency?
    // Manual conversion using OpenCV transformation values
    // Y = 0.299 * R + 0.587 * G + 0.114 * B
    
    // Read image
    ReadImage(Color->TextureTarget, ImageColor);

    SaveImageData(ImageColor, CurrentImage->ImagePtr);

    FROSTime time = FROSTime::Now();

    // ROS message construction image
    TSharedPtr<ROSMessages::sensor_msgs::Image> ImageMessage(new ROSMessages::sensor_msgs::Image());

    ImageMessage->header.seq = 0;
    ImageMessage->header.time = time;
    ImageMessage->header.frame_id = ImageFrame;

    ImageMessage->height = Height;
    ImageMessage->width = Width;
    ImageMessage->encoding = TEXT("bgr8");
    ImageMessage->step = Width * 3;
    ImageMessage->data = &CurrentImage->ImagePtr[0];
    ImagePublisher->Publish(ImageMessage);



    // Construct and publish camera info

    // Camera info
    const float FOVX = Height > Width ? FieldOfView * Width / Height : FieldOfView;
    const float FOVY = Width > Height ? FieldOfView * Height / Width : FieldOfView;
    double halfFOVX = FOVX * PI / 360.0; // was M_PI on gcc
    double halfFOVY = FOVY * PI / 360.0; // was M_PI on gcc
    const double cX = Width / 2.0;
    const double cY = Height / 2.0;

    const double K0 = cX / std::tan(halfFOVX);
    const double K2 = cX;
    const double K4 = K0;
    const double K5 = cY;
    const double K8 = 1;

    const double P0 = K0;
    const double P2 = K2;
    const double P5 = K4;
    const double P6 = K5;
    const double P10 = 1;


    // ROS message construction camera info
    TSharedPtr<ROSMessages::sensor_msgs::CameraInfo> CamInfo(new ROSMessages::sensor_msgs::CameraInfo());

    CamInfo->header.seq = 0;
    CamInfo->header.time = time;
    //CamInfo->header.frame_id =
    CamInfo->height = Height;
    CamInfo->width = Width;
    CamInfo->distortion_model = TEXT("plumb_bob");

    CamInfo->D[0] = 0;
    CamInfo->D[1] = 0;
    CamInfo->D[2] = 0;
    CamInfo->D[3] = 0;
    CamInfo->D[4] = 0;

    CamInfo->K[0] = K0;
    CamInfo->K[1] = 0;
    CamInfo->K[2] = K2;
    CamInfo->K[3] = 0;
    CamInfo->K[4] = K4;
    CamInfo->K[5] = K5;
    CamInfo->K[6] = 0;
    CamInfo->K[7] = 0;
    CamInfo->K[8] = K8;

    CamInfo->R[0] = 1;
    CamInfo->R[1] = 0;
    CamInfo->R[2] = 0;
    CamInfo->R[3] = 0;
    CamInfo->R[4] = 1;
    CamInfo->R[5] = 0;
    CamInfo->R[6] = 0;
    CamInfo->R[7] = 0;
    CamInfo->R[8] = 1;

    CamInfo->P[0] = P0;
    CamInfo->P[1] = 0;
    CamInfo->P[2] = P2;
    CamInfo->P[3] = 0;
    CamInfo->P[4] = 0;
    CamInfo->P[5] = P5;
    CamInfo->P[6] = P6;
    CamInfo->P[7] = 0;
    CamInfo->P[8] = 0;
    CamInfo->P[9] = 0;
    CamInfo->P[10] = P10;
    CamInfo->P[11] = 0;

    CamInfo->binning_x = 0;
    CamInfo->binning_y = 0;

    CamInfo->roi.x_offset = 0;
    CamInfo->roi.y_offset = 0;
    CamInfo->roi.height = 0;
    CamInfo->roi.width = 0;
    CamInfo->roi.do_rectify = false;

    CameraInfoPublisher->Publish(CamInfo);

}

void UROSCameraComponent::ReadImage(UTextureRenderTarget2D* RenderTarget, TArray<FFloat16Color>& ImageData) const
{
    FTextureRenderTargetResource* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    RenderTargetResource->ReadFloat16Pixels(ImageData);
}

void UROSCameraComponent::SaveImageData(const TArray<FFloat16Color>& ImageData, uint8* Bytes) const
{
    const FFloat16Color* itI = ImageData.GetData();
    uint8_t* itO = Bytes;

    // Converts Float colors to bytes
    for (size_t i = 0; i < ImageData.Num(); ++i, ++itI, ++itO)
    {
        *itO = (uint8_t)std::round((float)itI->B * 255.f);
        *++itO = (uint8_t)std::round((float)itI->G * 255.f);
        *++itO = (uint8_t)std::round((float)itI->R * 255.f);
    }
}
