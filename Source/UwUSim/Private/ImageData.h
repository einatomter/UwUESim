// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <cmath>
#include <vector>


/**
 *
 */
class UWUSIM_API ImageData
{
public:
    ImageData(const uint32 Width, const uint32 Height);
    ImageData(const uint32 Width, const uint32 Height, bool mono);
    ~ImageData();

    const uint32 ImageSize;         // Size of image
    std::vector<uint8> ImageBuffer;   // Image data

    //uint32 ImageWidth;  // Width of the images
    //uint32 ImageHeight; // Height of the images
    uint8* ImagePtr;    // Pointer to the beginning of the image

};
