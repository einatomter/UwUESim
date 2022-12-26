// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageData.h"

ImageData::ImageData(const uint32 Width, const uint32 Height) :
	ImageSize(Width* Height * 3 * sizeof(uint8))
	//ImageWidth(Width), 
	//ImageHeight(Height)
{
	ImageBuffer.resize(ImageSize);

	// TODO: Revisit, may not need to declare pointer until publishing
	ImagePtr = &ImageBuffer[0];
}

ImageData::~ImageData()
{
}
