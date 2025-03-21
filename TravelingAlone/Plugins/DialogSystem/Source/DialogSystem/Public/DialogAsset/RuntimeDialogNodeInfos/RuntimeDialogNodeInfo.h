#pragma once
#include "DialogAsset/RuntimeDialogNodeInfoBase.h"
#include "DialogAsset/DialogTextGetBase.h"
#include "RuntimeDialogNodeInfo.generated.h"

class UDialogNodeConditionBase;
//输出引脚数据
USTRUCT(BlueprintType)
struct FDialogOutPinData
{
	GENERATED_BODY()
	//引脚名称
	UPROPERTY(EditAnywhere,BlueprintReadOnly,DisplayName="引脚名称",Category="DialogOutPinData")
	FText DialogNodeTitle = FText::FromString(TEXT("默认输出"));
	//执行条件组（全部符合才能使用此引脚）
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(EditInline = "true"),DisplayName="执行条件组",Category="DialogOutPinData")
	TArray<UDialogNodeConditionBase*> DialogNodeCondition;
};

//***********************************************************************
//对话节点信息
UCLASS(Blueprintable)
class DIALOGSYSTEM_API URuntimeDialogNodeInfo : public URuntimeDialogNodeInfoBase
{
	GENERATED_BODY()
public:
	//使用此节点的对象
	UPROPERTY(EditAnywhere,BlueprintReadWrite,DisplayName="对话对象ID",Category="RuntimeDialogNodeInfo")
	FName DialogActorId = TEXT("");
	//节点标题
	UPROPERTY(EditAnywhere,BlueprintReadOnly,DisplayName="节点标题",Category="RuntimeDialogNodeInfo")
	FText DialogNodeTitle = FText::FromString(TEXT("对话节点"));
	//输出选项数据
	UPROPERTY(EditAnywhere,BlueprintReadOnly,DisplayName="输出选项数据",Category="RuntimeDialogNodeInfo")
	TArray<FDialogOutPinData> DialogOutPinArray;
	//是否刷新任务包选项
	UPROPERTY(EditAnywhere,BlueprintReadOnly,DisplayName="是否刷新任务包选项",Category="RuntimeDialogNodeInfo")
	bool bIsUpdateTask = false;

	//对话文本后处理方法
	UPROPERTY(EditAnywhere,DisplayName="名词对应转换方法",Category="TextPostSetting")
	TSubclassOf<UDialogTextGetBase> DialogTextGetClass = nullptr;
	
	//对话节点颜色
	UPROPERTY(EditAnywhere,BlueprintReadOnly,DisplayName="对话节点颜色",Category="DialogNode")
	FLinearColor DialogNodeColor = FLinearColor::Green;
	URuntimeDialogNodeInfo()
	{DialogOutPinArray.Add(FDialogOutPinData());}
	
	UFUNCTION(BlueprintCallable,BlueprintPure,DisplayName="获取完整对话内容",Category="RuntimeDialogNodeInfo")
	FText GetIntegrityDialogNodeText(UDialogAsset* DialogAsset)
	{
		if (!DialogTextGetClass){return GetDialogText();}
		FText DialogNodeText;
		UDialogTextGetBase* DialogTextGet = NewObject<UDialogTextGetBase>(GetTransientPackage(),DialogTextGetClass);//创建临时对象
		DialogTextGet->GetDialogText(DialogAsset,this,GetDialogText(),DialogNodeText);
		DialogTextGet->ConditionalBeginDestroy();//通知对象可以进行销毁 
		return DialogNodeText;
	}

	//获取默认文本
	FText GetDialogText(){return DialogText;}
protected:
	//对话内容
	UPROPERTY(EditAnywhere,DisplayName="对话内容",Category="RuntimeDialogNodeInfo")
	FText DialogText = FText::FromString(TEXT("对话节点"));
	
};
