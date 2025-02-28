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
	
	//着色设置
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="着色设置",Category="TASaveGameSettingData")
	int32 ShadingQuality = 1;
	//阴影质量
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="阴影质量",Category="TASaveGameSettingData")
	int32 ShadowQuality = 1;
	//全局光照质量
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="全局光照质量",Category="TASaveGameSettingData")
	int32 GlobalIlluminationQuality = 1;
	//抗锯齿质量
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="抗锯齿质量",Category="TASaveGameSettingData")
	int32 AntiAliasingQuality = 1;
	//反射质量
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="反射质量",Category="TASaveGameSettingData")
	int32 ReflectionQuality = 1;
	//纹理质量
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="纹理质量",Category="TASaveGameSettingData")
	int32 TextureQuality = 1;
	//后期处理质量
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="后期处理质量",Category="TASaveGameSettingData")
	int32 PostProcessingQuality = 1;

	//全屏模式
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="全屏模式",Category="TASaveGameSettingData")
	TEnumAsByte<EWindowMode::Type> FullscreenMode = EWindowMode::Type::Fullscreen;
	//屏幕分辨率
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="屏幕分辨率",Category="TASaveGameSettingData")
	FIntPoint ScreenResolution = FIntPoint(1920,1080);
	//垂直同步
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="垂直同步",Category="TASaveGameSettingData")
	bool bIsVSyncEnabled = true;
	//帧率限制（0为不限制）
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="帧率限制",Category="TASaveGameSettingData")
	float FrameRateLimit = 0;
	
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
