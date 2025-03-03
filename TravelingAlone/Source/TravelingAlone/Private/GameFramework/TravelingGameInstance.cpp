#include "TravelingGameFramework/TravelingGameInstance.h"
#include "DeveloperSettings/TravelingAloneDeveloperSetting.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SaveGame/TravelingSaveGame.h"

void UTravelingGameInstance::PreGoToGameMain(bool bNewIsNewGame,FString NewCurrentSaveGameId)
{
	bIsNewGame = bNewIsNewGame;//设置当前游戏内容
	CurrentSaveGameId = NewCurrentSaveGameId;//设置新的游戏存档Id
}

void UTravelingGameInstance::GoToGameMain()
{
	TravelingSaveGameCurrent = Cast<UTravelingSaveGame_Slot>(UGameplayStatics::LoadGameFromSlot(CurrentSaveGameId,0));
	if (!TravelingSaveGameCurrent)
	{
		TravelingSaveGameCurrent = NewObject<UTravelingSaveGame_Slot>(this,UTravelingAloneDeveloperSettings::GetDFDeveloperSettings()->TravelingSaveGame_SlotClass);//创建游戏存档
		FTravelingSaveGameBase NewTravelingSaveGameBase;//设置基本数据
		NewTravelingSaveGameBase.SaveSlotId = CurrentSaveGameId;
		NewTravelingSaveGameBase.SaveSlotName = FText::FromString(TEXT("NewGame"));
		NewTravelingSaveGameBase.SaveTime = UKismetMathLibrary::Now();
		TravelingSaveGameCurrent->TravelingSaveGameBase = NewTravelingSaveGameBase;//设置存档基本数据
	}
	AsyncAutoSaveGameToSlot();//无论是否存档加载的游戏，在进入游戏主世界时都需要进行第一次异步保存。
}

void UTravelingGameInstance::ApplyGameRenderSetting(FTASaveGameSettingData_RenderSetting NewRenderSetting)
{
	TravelingSaveGameSetting->TASaveGameSettingData.RenderSetting = NewRenderSetting;//更新游戏设置数据
	UGameUserSettings* GameUserSetting = UGameUserSettings::GetGameUserSettings();//获取游戏用户设置
	GameUserSetting->SetShadingQuality(NewRenderSetting.ShadingQuality);//设置着色质量
	GameUserSetting->SetShadowQuality(NewRenderSetting.ShadowQuality);//设置阴影质量
	GameUserSetting->SetGlobalIlluminationQuality(NewRenderSetting.GlobalIlluminationQuality);//设置全局光照信息
	GameUserSetting->SetAntiAliasingQuality(NewRenderSetting.AntiAliasingQuality);//设置抗锯齿
	GameUserSetting->SetReflectionQuality(NewRenderSetting.ReflectionQuality);//设置反射质量
	GameUserSetting->SetTextureQuality(NewRenderSetting.TextureQuality);//设置纹理质量
	GameUserSetting->SetPostProcessingQuality(NewRenderSetting.PostProcessingQuality);//设置后期处理质量

	GameUserSetting->SetFullscreenMode(NewRenderSetting.FullscreenMode);//设置全屏模式
	GameUserSetting->SetScreenResolution(NewRenderSetting.ScreenResolution);//设置屏幕分辨率
	GameUserSetting->SetVSyncEnabled(NewRenderSetting.bIsVSyncEnabled);//设置垂直同步
	GameUserSetting->SetFrameRateLimit(NewRenderSetting.FrameRateLimit);//设置帧率限制

	//应用设置
	GameUserSetting->ApplyNonResolutionSettings();//应用非分辨率设置。
	GameUserSetting->ApplyResolutionSettings(false);//应用分辨率设置
	GameUserSetting->ApplySettings(false);//应用设置。

	SaveTravelingGameSetting();//保存游戏设置存档
	
}

void UTravelingGameInstance::RestGameRenderSetting()
{
	UGameUserSettings* GameUserSetting = UGameUserSettings::GetGameUserSettings();//获取游戏设置
	GameUserSetting->ResetToCurrentSettings();//重置你游戏设置为系统设置
	FTASaveGameSettingData_RenderSetting NewRenderSetting;//设置新数据
	{
		NewRenderSetting.ShadingQuality = GameUserSetting->GetShadingQuality();
		NewRenderSetting.ShadowQuality = GameUserSetting->GetShadowQuality();
		NewRenderSetting.GlobalIlluminationQuality = GameUserSetting->GetGlobalIlluminationQuality();
		NewRenderSetting.AntiAliasingQuality = GameUserSetting->GetAntiAliasingQuality();
		NewRenderSetting.ReflectionQuality = GameUserSetting->GetReflectionQuality();
		NewRenderSetting.TextureQuality = GameUserSetting->GetTextureQuality();
		NewRenderSetting.PostProcessingQuality = GameUserSetting->GetPostProcessingQuality();
	
		NewRenderSetting.FullscreenMode = GameUserSetting->GetFullscreenMode();
		NewRenderSetting.ScreenResolution = GameUserSetting->GetScreenResolution();
		NewRenderSetting.bIsVSyncEnabled = GameUserSetting->bUseVSync;
		NewRenderSetting.FrameRateLimit = GameUserSetting->GetFrameRateLimit();
	}//游戏初始化数据设置

	TravelingSaveGameSetting->TASaveGameSettingData.RenderSetting = NewRenderSetting;//更新游戏设置数据
	SaveTravelingGameSetting();//保存游戏设置存档
	
	//应用设置
	GameUserSetting->ApplyNonResolutionSettings();//应用非分辨率设置。
	GameUserSetting->ApplyResolutionSettings(false);//应用分辨率设置
	GameUserSetting->ApplySettings(false);//应用设置。
	
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
	RestGameRenderSetting();//第一次游戏刷新游戏设置（这个函数中也会保存一次游戏设置存档，所以这里不再需要做保存的操作了！）
	return true;
	
}

bool UTravelingGameInstance::SaveTravelingGameSetting()
{
	//判断游戏设置是否有效
	if (TravelingSaveGameSetting)
	{
		UpdateGameSettingShow();//游戏设置变化时更新游戏设置显示
		return UGameplayStatics::SaveGameToSlot(TravelingSaveGameSetting,UTravelingSaveGame_Setting::GetTravelingAloneGameSettingString(),0);
	}
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

bool UTravelingGameInstance::DeleteTravelingSaveGameFromSlot(FString SlotId)
{
	if (TravelingSaveGameSetting->Map_SaveGameIdToInfo.Contains(SlotId))
	{
		if (UGameplayStatics::DeleteGameInSlot(SlotId,0))
		{
			TravelingSaveGameSetting->Map_SaveGameIdToInfo.Remove(SlotId);
			SaveTravelingGameSetting();//对游戏设置进行保存
			return true;
		}//判断是否删除成功
		else{UE_LOG(LogTemp, Warning, TEXT("UTravelingGameInstance::DeleteTravelingSaveGameFromSlot 此存档删除失败了！"));}//做错误打印
	}
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

FString UTravelingGameInstance::GetNewSaveGameSlotName()
{
	if (TravelingSaveGameSetting)
	{
		int32 NewIndex = TravelingSaveGameSetting->SaveGameSlotIndex++;
		return FString::Printf(TEXT("NewGameSlot_%d"),NewIndex);
	}else{UE_LOG(LogTemp, Warning, TEXT("UTravelingGameInstance::GetNewSaveGameSlotName 游戏设置存档不存在了！"));}
	return FString();
}

void UTravelingGameInstance::AsyncAutoSaveGameToSlot()
{
	if (!TravelingSaveGameCurrent)
	{UE_LOG(LogTemp, Error, TEXT("UTravelingGameInstance::AsyncAutoSaveGameToSlot 存档对象都没有创建，无法自动保存！"));return;}
	//创建回调绑定
	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &UTravelingGameInstance::OnGameSaved);//绑定回调函数
	
	//TODO::这里是存档中基本数据的设置
	TravelingSaveGameCurrent->GetGameInfo();//获取存档信息
	TravelingSaveGameCurrent->TravelingSaveGameBase.SaveTime = UKismetMathLibrary::Now();//设置当前保存最新时间
	TravelingSaveGameSetting->Map_SaveGameIdToInfo.Add(CurrentSaveGameId,TravelingSaveGameCurrent->TravelingSaveGameBase);//在游戏设置中重新刷新这一条存档数据
	AutoSaveGameStart();//调用委托，表示自动存档开始
	UGameplayStatics::AsyncSaveGameToSlot(TravelingSaveGameCurrent,CurrentSaveGameId,0,SaveDelegate);//进行异步存档保存
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
