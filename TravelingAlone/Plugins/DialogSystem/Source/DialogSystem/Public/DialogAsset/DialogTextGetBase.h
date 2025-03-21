#pragma once
#include "DialogTextGetBase.generated.h"

//对话内容获取
UCLASS(Blueprintable,BlueprintType,Abstract)
class DIALOGSYSTEM_API UDialogTextGetBase:public UObject
{
	GENERATED_BODY()
public:
	UDialogTextGetBase(){}
	virtual bool GetDialogText(UDialogAsset* AtDialogAsset,URuntimeDialogNodeInfo* AtNodeInfo,const FText& InText,FText& OutText)
	{return GetDialogTextEvent(AtDialogAsset,AtNodeInfo,InText,OutText);}
	UFUNCTION(BlueprintImplementableEvent,DisplayName="获取文本事件",Category = "DialogTextGetBase")
	bool GetDialogTextEvent(UDialogAsset* AtDialogAsset,URuntimeDialogNodeInfo* AtNodeInfo,const FText& InText,FText& OutText);
};

//对话内容获取(示例)
UCLASS(NotBlueprintable,NotBlueprintType,Abstract)
class DIALOGSYSTEM_API UDialogTextGetTest:public UDialogTextGetBase
{
	GENERATED_BODY()
	virtual bool GetDialogText(UDialogAsset* AtDialogAsset, URuntimeDialogNodeInfo* AtNodeInfo,const FText& InText, FText& OutText) override
	{
		FFormatNamedArguments Args;//创建格式化文本数据
		Args.Add(TEXT("Name"), FFormatArgumentValue(FText::FromString("John Doe")));
		Args.Add(TEXT("Age"), FFormatArgumentValue(30));
		OutText = FText::Format(InText,Args);
		return GetDialogTextEvent(AtDialogAsset,AtNodeInfo,InText,OutText);
	}
};
