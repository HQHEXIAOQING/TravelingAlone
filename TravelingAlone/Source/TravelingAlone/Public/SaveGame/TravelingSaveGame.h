#pragma once
#include "TravelingSaveGameLibrary.h"
#include "GameFramework/SaveGame.h"
#include "TravelingSaveGame.generated.h"

UCLASS(Blueprintable,BlueprintType,DisplayName="游戏插槽存储")
class TRAVELINGALONE_API UTravelingSaveGame_Slot:public USaveGame
{
	GENERATED_BODY()
public:

	
	//函数*******************************************

	//获取游戏信息
	virtual void GetGameInfo(){}
};

UCLASS(Blueprintable,BlueprintType,DisplayName="游戏全局设置")
class TRAVELINGALONE_API UTravelingSaveGame_Setting:public USaveGame
{
	GENERATED_BODY()
public:

	//存储变量*********************************************
	
	//所有保存的存档和相关基础信息
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,DisplayName="存档以及相关基本信息",Category="SaveGameSetting")
	TMap<FString,FTravelingSaveGameBase> Map_SaveGameIdToInfo;
	
	//静态函数****************************************

	//返回游戏自动存档名称
	UFUNCTION(BlueprintCallable,BlueprintPure,DisplayName="获取自动存档名称",Category="TravelingSaveGame_Setting")
	static FString GetTravelingAloneAutoSaveGameString(){return FString(TEXT("AutoSaveGameString"));}
	//返回游戏设置存档名称
	UFUNCTION(BlueprintCallable,BlueprintPure,DisplayName="获取游戏设置存档名称",Category="TravelingSaveGame_Setting")
	static FString GetTravelingAloneGameSettingString(){return FString(TEXT("SaveGameSettingString"));}
};