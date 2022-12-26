// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UwUSim/Public/ROSCameraComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeROSCameraComponent() {}
// Cross Module References
	UWUSIM_API UClass* Z_Construct_UClass_UROSCameraComponent_NoRegister();
	UWUSIM_API UClass* Z_Construct_UClass_UROSCameraComponent();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent();
	UPackage* Z_Construct_UPackage__Script_UwUSim();
// End Cross Module References
	void UROSCameraComponent::StaticRegisterNativesUROSCameraComponent()
	{
	}
	UClass* Z_Construct_UClass_UROSCameraComponent_NoRegister()
	{
		return UROSCameraComponent::StaticClass();
	}
	struct Z_Construct_UClass_UROSCameraComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UROSCameraComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCameraComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_UwUSim,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UROSCameraComponent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Mobility Rendering LOD Trigger PhysicsVolume" },
		{ "IncludePath", "ROSCameraComponent.h" },
		{ "ModuleRelativePath", "Public/ROSCameraComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UROSCameraComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UROSCameraComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UROSCameraComponent_Statics::ClassParams = {
		&UROSCameraComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UROSCameraComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UROSCameraComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UROSCameraComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UROSCameraComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UROSCameraComponent, 2182164375);
	template<> UWUSIM_API UClass* StaticClass<UROSCameraComponent>()
	{
		return UROSCameraComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UROSCameraComponent(Z_Construct_UClass_UROSCameraComponent, &UROSCameraComponent::StaticClass, TEXT("/Script/UwUSim"), TEXT("UROSCameraComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UROSCameraComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
