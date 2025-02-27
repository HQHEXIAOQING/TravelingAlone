#pragma once
#include "TravelingSaveGameLibrary.generated.h"

//结构体*******************************************

//存档基本信息
USTRUCT(BlueprintType,Blueprintable,DisplayName="游戏存档基本信息")
struct FTravelingSaveGameBase
{
	GENERATED_BODY()
	//存档插槽Id
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="存档插槽Id",Category="SaveGameSetting")
	FString SaveSlotId = FString(TEXT("SlotId"));
	//存档名称
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="存档名称",Category="SaveGameSetting")
	FText SaveSlotName = FText::FromString(TEXT("未命名"));
	//存档时间
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="存档时间",Category="SaveGameSetting")
	FDateTime SaveTime;
	
};

//游戏基本设置
USTRUCT(BlueprintType,Blueprintable,DisplayName="游戏设置数据")
struct FTASaveGameSettingData_BaseSetting
{
	GENERATED_BODY()
};

//游戏渲染设置
USTRUCT(BlueprintType,Blueprintable,DisplayName="游戏渲染设置")
struct FTASaveGameSettingData_RenderSetting
{
	GENERATED_BODY()
};

//游戏声音设置
USTRUCT(BlueprintType,Blueprintable,DisplayName="游戏声音设置")
struct FTASaveGameSettingData_SoundSetting
{
	GENERATED_BODY()
};

//游戏设置数据
USTRUCT(BlueprintType,Blueprintable,DisplayName="游戏设置数据")
struct FTASaveGameSettingData
{
	GENERATED_BODY()
	//基本设置
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="基本设置",Category="TASaveGameSettingData")
	FTASaveGameSettingData_BaseSetting BaseSetting;
	//渲染设置
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="渲染设置",Category="TASaveGameSettingData")
	FTASaveGameSettingData_RenderSetting RenderSetting;
	//声音设置
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="声音设置",Category="TASaveGameSettingData")
	FTASaveGameSettingData_SoundSetting SoundSetting;
};
