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
