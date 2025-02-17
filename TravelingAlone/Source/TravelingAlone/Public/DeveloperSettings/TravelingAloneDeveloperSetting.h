#pragma once
#include "TravelingAloneDeveloperSetting.generated.h"

class UTravelingSaveGame_Slot;
class UTravelingSaveGame_Setting;

UCLASS(Config = Game,DefaultConfig,meta =(DisplayName = "独旅游戏配置信息"))
class TRAVELINGALONE_API UTravelingAloneDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	//变量*****************************************

	//存档相关设置
	//游戏设置存档类
	UPROPERTY(EditAnywhere,Config, BlueprintReadOnly,DisplayName = "游戏设置存档类", Category="SaveGameSetting")
	TSubclassOf<UTravelingSaveGame_Setting> TravelingSaveGame_SettingClass = nullptr;
	//游戏存档类
	UPROPERTY(EditAnywhere,Config, BlueprintReadOnly,DisplayName = "游戏存档类", Category="SaveGameSetting")
	TSubclassOf<UTravelingSaveGame_Slot> TravelingSaveGame_SlotClass = nullptr;

	//获取独旅游戏配置信息
	UFUNCTION(BlueprintCallable, meta=(Static, NoDestructor),DisplayName="获取独旅游戏配置信息",Category="DFDeveloperSettings")
	static const UTravelingAloneDeveloperSettings* GetDFDeveloperSettings() { return GetDefault<UTravelingAloneDeveloperSettings>(); }
	
};