#pragma once
#include "UObject/Object.h"
#include "DialogAssetObjectDataInfoBase.generated.h"

class UDialogAsset;
UCLASS(Blueprintable,BlueprintType,Abstract)
class DIALOGSYSTEM_API UDialogAssetObjectDataInfoBase : public UObject
{
	GENERATED_BODY()
public:
	
	//对话资产
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="对话资产",Category="RuntimeTaskNodeInfoBase")
	UDialogAsset* DialogAsset = nullptr;
	
	//函数********************************************************
	
	//初始化对话数据
	UFUNCTION(BlueprintCallable,DisplayName="初始化对话数据",Category="DialogAssetObjectDataInfoBase")
	void DialogAssetObjectInit(UDialogAsset* NewDialogAsset);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="初始化对话数据事件",Category="DialogAssetObjectDataInfoBase")
	void DialogAssetObjectInitEvent();

	
};
