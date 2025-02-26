#pragma once
#include "TravelingGameInstance.generated.h"

struct FTravelingSaveGameBase;
class UTravelingSaveGame_Slot;
class UTravelingSaveGame_Setting;

UCLASS(Blueprintable,BlueprintType,DisplayName="独旅游戏实例")
class TRAVELINGALONE_API UTravelingGameInstance:public UGameInstance
{
	GENERATED_BODY()
public:
	//变量***********************************************
	
	//游戏设置存档
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="游戏设置存档",Category="TravelingGameInstance")
	UTravelingSaveGame_Setting* TravelingSaveGameSetting = nullptr;
	//当前游戏存档数据
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="当前游戏存档数据",Category="TravelingGameInstance")
	UTravelingSaveGame_Slot* TravelingSaveGameCurrent = nullptr;
	
	//函数*********************************************

	//进入游戏初始化事件（在进入游戏后调用的事件）
	UFUNCTION(BlueprintCallable,DisplayName="进入游戏初始化事件",Category="TravelingGameInstance")
	void GoToGameMain();
	//加载游戏设置
	UFUNCTION(BlueprintCallable,DisplayName="加载游戏设置",Category="TravelingGameInstance")
	bool LoadTravelingGameSetting(bool bIsResetGameSetting,UTravelingSaveGame_Setting*& NewTravelingSaveGame_Setting);
	//保存游戏设置
	UFUNCTION(BlueprintCallable,DisplayName="保存游戏设置",Category="TravelingGameInstance")
	bool SaveTravelingGameSetting();
	//加载游戏存档
	UFUNCTION(BlueprintCallable,DisplayName="加载游戏存档",Category="TravelingGameInstance")
	bool LoadTravelingSaveGameFromSlot(FString SlotId);
	//保存游戏至插槽
	UFUNCTION(BlueprintCallable,DisplayName="保存游戏至插槽",Category="TravelingGameInstance")
	bool SaveTravelingGameToSlot(FTravelingSaveGameBase NewTravelingSaveGameBase);
	
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
	
	//委托**********************************************

	//*******以下为自动存档的相关委托**********
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAutoSaveGameStart);//开始进行自动保存
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAutoSaveGameResult,bool,Result);//自动保存结束
	//保存开始
	UPROPERTY(BlueprintAssignable,DisplayName="自动保存开始",Category="TravelingGameInstance")
	FAutoSaveGameStart OnAutoSaveGameStart;
	//保存结束
	UPROPERTY(BlueprintAssignable,DisplayName="自动保存结束",Category="TravelingGameInstance")
	FAutoSaveGameResult OnAutoSaveGameResult;
	//*******以上为自动存档的相关委托**********

	
private:
    //异步存档回调事件
	void OnGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
