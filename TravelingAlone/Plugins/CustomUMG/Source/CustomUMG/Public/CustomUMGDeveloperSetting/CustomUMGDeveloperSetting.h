#pragma once
#include "CustomUMGDeveloperSetting.generated.h"

UCLASS(Config = Game ,DefaultConfig,meta =(DisplayName = "自定义UMG界面配置"))
class CUSTOMUMG_API UCustomUMGDeveloperSetting : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	//变量*****************************************

	//文本设置
	
	//自定义字体样式设置
	UPROPERTY(EditAnywhere, Config,BlueprintReadOnly, Category=SlateStyleRules, meta=(AllowedClasses="/Script/Engine.Font", DisplayName="自定义字体样式设置"))
	TSoftObjectPtr<const UObject> FontObject;
	//获取独旅游戏配置信息
	UFUNCTION(BlueprintCallable,BlueprintPure, meta=(Static, NoDestructor),DisplayName="获取自定义界面设置",Category="CustomUMGDeveloperSetting")
	static const UCustomUMGDeveloperSetting* GetCustomUMGDFDeveloperSettings() { return GetDefault<UCustomUMGDeveloperSetting>(); }
	
};