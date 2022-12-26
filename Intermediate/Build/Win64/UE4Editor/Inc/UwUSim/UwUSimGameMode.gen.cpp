// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UwUSim/UwUSimGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUwUSimGameMode() {}
// Cross Module References
	UWUSIM_API UClass* Z_Construct_UClass_AUwUSimGameMode_NoRegister();
	UWUSIM_API UClass* Z_Construct_UClass_AUwUSimGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_UwUSim();
// End Cross Module References
	void AUwUSimGameMode::StaticRegisterNativesAUwUSimGameMode()
	{
	}
	UClass* Z_Construct_UClass_AUwUSimGameMode_NoRegister()
	{
		return AUwUSimGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AUwUSimGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUwUSimGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UwUSim,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUwUSimGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "UwUSimGameMode.h" },
		{ "ModuleRelativePath", "UwUSimGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUwUSimGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUwUSimGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AUwUSimGameMode_Statics::ClassParams = {
		&AUwUSimGameMode::StaticClass,
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
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AUwUSimGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUwUSimGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUwUSimGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AUwUSimGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AUwUSimGameMode, 2908466512);
	template<> UWUSIM_API UClass* StaticClass<AUwUSimGameMode>()
	{
		return AUwUSimGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AUwUSimGameMode(Z_Construct_UClass_AUwUSimGameMode, &AUwUSimGameMode::StaticClass, TEXT("/Script/UwUSim"), TEXT("AUwUSimGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUwUSimGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
