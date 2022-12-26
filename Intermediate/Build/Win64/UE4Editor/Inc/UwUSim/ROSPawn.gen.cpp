// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UwUSim/Public/ROSPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeROSPawn() {}
// Cross Module References
	UWUSIM_API UClass* Z_Construct_UClass_AROSPawn_NoRegister();
	UWUSIM_API UClass* Z_Construct_UClass_AROSPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_UwUSim();
// End Cross Module References
	void AROSPawn::StaticRegisterNativesAROSPawn()
	{
	}
	UClass* Z_Construct_UClass_AROSPawn_NoRegister()
	{
		return AROSPawn::StaticClass();
	}
	struct Z_Construct_UClass_AROSPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AROSPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_UwUSim,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AROSPawn_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ROSPawn.h" },
		{ "ModuleRelativePath", "Public/ROSPawn.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AROSPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AROSPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AROSPawn_Statics::ClassParams = {
		&AROSPawn::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AROSPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AROSPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AROSPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AROSPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AROSPawn, 1777252542);
	template<> UWUSIM_API UClass* StaticClass<AROSPawn>()
	{
		return AROSPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AROSPawn(Z_Construct_UClass_AROSPawn, &AROSPawn::StaticClass, TEXT("/Script/UwUSim"), TEXT("AROSPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AROSPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
