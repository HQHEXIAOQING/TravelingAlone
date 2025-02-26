#include "TravelingGameFramework/TravelingGameInstance.h"
#include "DeveloperSettings/TravelingAloneDeveloperSetting.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SaveGame/TravelingSaveGame.h"

void UTravelingGameInstance::GoToGameMain()
{
	//如果存档存在，说明是从存档进入的游戏，如果不存在，那就是默认进入游戏，这个时候需要创建一个游戏存档对象，此时对象数据为空，需要跑一次自动存储事件
	if (TravelingSaveGameCurrent){return;}
	else
	{
		TravelingSaveGameCurrent = NewObject<UTravelingSaveGame_Slot>(this,UTravelingAloneDeveloperSettings::GetDFDeveloperSettings()->TravelingSaveGame_SlotClass);
		AsyncAutoSaveGameToSlot();//异步保存游戏
	}
	
}

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
	UE_LOG(LogTemp, Warning, TEXT("UTravelingGameInstance::LoadSaveGameFromSlot 游戏插槽%s不存在！"), *SlotId);
	return false;
}

bool UTravelingGameInstance::SaveTravelingGameToSlot(FTravelingSaveGameBase NewTravelingSaveGameBase)
{
	if (TravelingSaveGameCurrent)
	{
		TravelingSaveGameCurrent->TravelingSaveGameBase = NewTravelingSaveGameBase;//设置存档基本信息
		TravelingSaveGameCurrent->GetGameInfo();//获取其他存档数据
		return UGameplayStatics::SaveGameToSlot(TravelingSaveGameCurrent,NewTravelingSaveGameBase.SaveSlotId,0);
	}
	UE_LOG(LogTemp, Warning, TEXT("UTravelingGameInstance::LoadSaveGameFromSlot 游戏存档不存在！"));
	return false;
}

void UTravelingGameInstance::AsyncAutoSaveGameToSlot()
{
	if (!TravelingSaveGameCurrent)
	{UE_LOG(LogTemp, Error, TEXT("UTravelingGameInstance::AsyncAutoSaveGameToSlot 存档对象都没有创建，无法自动保存！"));return;}
	//创建回调绑定
	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &UTravelingGameInstance::OnGameSaved);//绑定回调函数
	
	FString SlotNameId = UTravelingSaveGame_Setting::GetTravelingAloneAutoSaveGameString();
	//TODO::这里是存档中基本数据的设置
	//设置自动存档基本数据
	FTravelingSaveGameBase TravelingSaveGameBase;
	TravelingSaveGameBase.SaveSlotId = SlotNameId;
	TravelingSaveGameBase.SaveTime = UKismetMathLibrary::Now();
	TravelingSaveGameBase.SaveSlotName = FText::FromString(TEXT("自动存档"));
	TravelingSaveGameSetting->Map_SaveGameIdToInfo.Add(SlotNameId,TravelingSaveGameBase);
	TravelingSaveGameCurrent->GetGameInfo();//获取存档信息
	TravelingSaveGameCurrent->TravelingSaveGameBase = TravelingSaveGameBase;//设置此存档基本数据
	AutoSaveGameStart();//调用委托，表示自动存档开始
	UGameplayStatics::AsyncSaveGameToSlot(TravelingSaveGameCurrent,SlotNameId,0,SaveDelegate);//进行异步存档保存
	SaveTravelingGameSetting();//保存游戏设置
}

void UTravelingGameInstance::OnGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	AutoSaveGameResult(bSuccess);//调用委托，表示自动存档结束
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("UTravelingGameInstance::OnGameSaved 插槽%s异步保存成功！"), *SlotName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UTravelingGameInstance::OnGameSaved 插槽%s异步保存失败！"), *SlotName);
	}
}
