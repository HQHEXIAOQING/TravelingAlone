#pragma once
#include "TravelingGameInstance.generated.h"

struct FTASaveGameSettingData_RenderSetting;
struct FTravelingSaveGameBase;
class UTravelingSaveGame_Slot;
class UTravelingSaveGame_Setting;

UCLASS(Blueprintable,BlueprintType,DisplayName="独旅游戏实例")
class TRAVELINGALONE_API UTravelingGameInstance:public UGameInstance
{
	GENERATED_BODY()
public:
	 virtual void Init() override;//游戏实例初始化内容
	//变量***********************************************
	
	//游戏设置存档
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="游戏设置存档",Category="TravelingGameInstance")
	UTravelingSaveGame_Setting* TravelingSaveGameSetting = nullptr;
	//当前游戏存档数据
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="当前游戏存档数据",Category="TravelingGameInstance")
	UTravelingSaveGame_Slot* TravelingSaveGameCurrent = nullptr;
	//当前游戏插槽Id
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="当前游戏插槽Id",Category="TravelingGameInstance")
	FString CurrentSaveGameId = FString("");
	
	//函数*********************************************

	//进入游戏前初始化事件（在进入游戏前需要处理和设置的内容）
	UFUNCTION(BlueprintCallable,DisplayName="进入游戏初始化事件",Category="TravelingGameInstance")
	void PreGoToGameMain(FString NewCurrentSaveGameId);
	//进入游戏初始化事件（在进入游戏后调用的事件，只有在主世界中调用搞得事件，请不要在主世界之外调用）
	UFUNCTION(BlueprintCallable,DisplayName="进入游戏事件",Category="TravelingGameInstance")
	void GoToGameMain();

	//应用游戏设置
	UFUNCTION(BlueprintCallable,DisplayName="应用游戏渲染设置",Category="TravelingGameInstance")
	void ApplyGameRenderSetting(FTASaveGameSettingData_RenderSetting NewRenderSetting);
	//重置游戏渲染设置
	UFUNCTION(BlueprintCallable,DisplayName="重置游戏渲染设置",Category="TravelingGameInstance")
	void RestGameRenderSetting();

	//加载游戏设置
	UFUNCTION(BlueprintCallable,DisplayName="加载游戏设置",Category="TravelingGameInstance")
	bool LoadTravelingGameSetting(bool bIsResetGameSetting,UTravelingSaveGame_Setting*& NewTravelingSaveGame_Setting);
	//保存游戏设置
	UFUNCTION(BlueprintCallable,DisplayName="保存游戏设置",Category="TravelingGameInstance")
	bool SaveTravelingGameSetting();

	//加载游戏存档
	UFUNCTION(BlueprintCallable,DisplayName="加载游戏存档",Category="TravelingGameInstance")
	bool LoadTravelingSaveGameFromSlot(FString SlotId);
	//删除游戏存档
	UFUNCTION(BlueprintCallable,DisplayName="删除游戏存档",Category="TravelingGameInstance")
	bool DeleteTravelingSaveGameFromSlot(FString SlotId);
	//保存游戏至插槽
	UFUNCTION(BlueprintCallable,DisplayName="保存游戏至插槽",Category="TravelingGameInstance")
	bool SaveTravelingGameToSlot(FTravelingSaveGameBase NewTravelingSaveGameBase);
	//获取新的存档Id
	UFUNCTION(BlueprintCallable,BlueprintPure,DisplayName="获取新的存档Id",Category="TravelingGameInstance")
	FString GetNewSaveGameSlotName();
	
	//自动存档游戏
	UFUNCTION(BlueprintCallable,DisplayName="自动存档游戏（异步）",Category="TravelingGameInstance")
	void AsyncAutoSaveGameToSlot();
	//自动保存开始
	void AutoSaveGameStart(){if (OnAutoSaveGameStart.IsBound()){OnAutoSaveGameStart.Broadcast();}AutoSaveGameStartEvent();}
	UFUNCTION(BlueprintImplementableEvent,DisplayName="自动保存开始",Category="TravelingGameInstance")
	void AutoSaveGameStartEvent();
	//自动保存结束
	void AutoSaveGameResult(bool Result){if (OnAutoSaveGameResult.IsBound()){OnAutoSaveGameResult.Broadcast(Result);}AutoSaveGameResultEvent(Result);}
	UFUNCTION(BlueprintImplementableEvent,DisplayName="自动保存结束",Category="TravelingGameInstance")
	void AutoSaveGameResultEvent(bool Result);

	//更新游戏设置数据
	void UpdateGameSettingShow(){if (OnGameSettingChanged.IsBound()){OnGameSettingChanged.Broadcast(TravelingSaveGameSetting);}UpdateGameSettingShowEvent(TravelingSaveGameSetting);}
	UFUNCTION(BlueprintImplementableEvent,DisplayName="更新游戏设置数据事件",Category="TravelingGameInstance")
	void UpdateGameSettingShowEvent(UTravelingSaveGame_Setting* NewTravelingSaveGame_Setting);
	
	//委托**********************************************

	//*******以下为自动存档的相关委托**********
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAutoSaveGameStart);//开始进行自动保存
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAutoSaveGameResult,bool,Result);//自动保存结束
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameSettingChanged,UTravelingSaveGame_Setting*,NewTravelingSaveGame_Setting);//游戏设置数据发生变化
	//保存开始
	UPROPERTY(BlueprintAssignable,DisplayName="自动保存开始",Category="TravelingGameInstance")
	FAutoSaveGameStart OnAutoSaveGameStart;
	//保存结束
	UPROPERTY(BlueprintAssignable,DisplayName="自动保存结束",Category="TravelingGameInstance")
	FAutoSaveGameResult OnAutoSaveGameResult;
	//游戏设置数据发生变化
	UPROPERTY(BlueprintAssignable,DisplayName="游戏设置数据发生变化",Category="TravelingGameInstance")
	FGameSettingChanged OnGameSettingChanged;
	//*******以上为自动存档的相关委托**********

	
private:
    //异步存档回调事件
	void OnGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
