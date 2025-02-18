#include "TravelingGameFramework/TravelingGameInstance.h"
#include "DeveloperSettings/TravelingAloneDeveloperSetting.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/TravelingSaveGame.h"

bool UTravelingGameInstance::LoadTravelingGameSetting(bool bIsResetGameSetting,UTravelingSaveGame_Setting*& NewTravelingSaveGame_Setting)
{
	//判断是否要重置？
	if (bIsResetGameSetting)
	{
		TravelingSaveGameSetting = NewObject<UTravelingSaveGame_Setting>(this,UTravelingAloneDeveloperSettings::GetDFDeveloperSettings()->TravelingSaveGame_SettingClass);
		NewTravelingSaveGame_Setting = TravelingSaveGameSetting;
		return UGameplayStatics::SaveGameToSlot(TravelingSaveGameSetting,UTravelingSaveGame_Setting::GetTravelingAloneGameSettingString(),0);
	}
	//不重置的话，判断是否有设置存档的存在
	if (UGameplayStatics::DoesSaveGameExist(UTravelingSaveGame_Setting::GetTravelingAloneGameSettingString(),0))
	{
		TravelingSaveGameSetting = Cast<UTravelingSaveGame_Setting>(UGameplayStatics::LoadGameFromSlot(UTravelingSaveGame_Setting::GetTravelingAloneGameSettingString(),0));
		NewTravelingSaveGame_Setting = TravelingSaveGameSetting;
		return true;
	}
	//如果不存在的话需要创建一个新的游戏设置存档。
	TravelingSaveGameSetting = NewObject<UTravelingSaveGame_Setting>(this,UTravelingAloneDeveloperSettings::GetDFDeveloperSettings()->TravelingSaveGame_SettingClass);
	NewTravelingSaveGame_Setting = TravelingSaveGameSetting;
	return UGameplayStatics::SaveGameToSlot(TravelingSaveGameSetting,UTravelingSaveGame_Setting::GetTravelingAloneGameSettingString(),0);
	
}

bool UTravelingGameInstance::SaveTravelingGameSetting()
{
	//判断游戏设置是否有效
	if (TravelingSaveGameSetting)
	{return UGameplayStatics::SaveGameToSlot(TravelingSaveGameSetting,UTravelingSaveGame_Setting::GetTravelingAloneGameSettingString(),0);}
	return false;
}

bool UTravelingGameInstance::LoadTravelingSaveGameFromSlot(FString SlotId)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotId,0))
	{
		TravelingSaveGameCurrent = Cast<UTravelingSaveGame_Slot>(UGameplayStatics::LoadGameFromSlot(SlotId,0));
		return true;
	}
	UE_LOG(LogTemp, Log, TEXT("UTravelingGameInstance::LoadSaveGameFromSlot 游戏插槽%s不存在！"), *SlotId);
	return false;
}

bool UTravelingGameInstance::SaveTravelingGameToSlot(FString SlotId)
{
	if (TravelingSaveGameCurrent)
	{
		TravelingSaveGameCurrent->GetGameInfo();
		return UGameplayStatics::SaveGameToSlot(TravelingSaveGameCurrent,SlotId,0);
	}
	UE_LOG(LogTemp, Log, TEXT("UTravelingGameInstance::LoadSaveGameFromSlot 游戏存档不存在！"));
	return false;
}

void UTravelingGameInstance::AsyncAutoSaveGameToSlot()
{
	if (!TravelingSaveGameCurrent)
	{UE_LOG(LogTemp, Error, TEXT("UTravelingGameInstance::AsyncAutoSaveGameToSlot 存档对象都没有创建，无法自动保存！"));return;}
	//创建回调绑定
	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &UTravelingGameInstance::OnGameSaved);//绑定回调函数
	TravelingSaveGameCurrent->GetGameInfo();//获取存档信息
	if (OnAutoSaveGameStart.IsBound()){OnAutoSaveGameStart.Broadcast();}//调用委托，表示自动存档开始
	//进行异步存档
	UGameplayStatics::AsyncSaveGameToSlot(TravelingSaveGameCurrent,UTravelingSaveGame_Setting::GetTravelingAloneAutoSaveGameString(),0,SaveDelegate);
}

void UTravelingGameInstance::OnGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (OnAutoSaveGameResult.IsBound()){OnAutoSaveGameResult.Broadcast(bSuccess);}//调用委托，表示自动存档结束
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("UTravelingGameInstance::OnGameSaved 插槽%s异步保存成功！"), *SlotName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UTravelingGameInstance::OnGameSaved 插槽%s异步保存失败！"), *SlotName);
	}
}
