﻿#pragma once
#include "CoreMinimal.h"
#include "RuntimeDialogNodeInfoBase.h"
#include "UObject/Object.h"
#include "NodeType.h"
#include "RuntimeDialogGraph.generated.h"

//引脚信息
UCLASS(BlueprintType)
class DIALOGSYSTEM_API URuntimeDialogPin: public UObject
{
	GENERATED_BODY()
public:
	//引脚名称
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="引脚名称",Category="RuntimeDialogPin")
	FName DialogPinName;
	//引脚Id
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="引脚Id",Category="RuntimeDialogPin")
	FGuid DialogPinId;
	//关联的引脚（输出引脚链接的引脚对象）
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="关联引脚",Category="RuntimeDialogPin") 
	URuntimeDialogPin* Connection = nullptr;
	
	//引脚所在的节点Id
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="引脚所在的节点Id",Category="RuntimeDialogPin")
	FName NodeId = "None";
	//构造函数中需要传入一个所在对象的Id
	URuntimeDialogPin(){}
};

//节点信息
UCLASS(BlueprintType)
class DIALOGSYSTEM_API URuntimeDialogNode: public UObject
{
	GENERATED_BODY()
public:
	//节点类型
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="节点类型",Category="RuntimeDialogNode")
	EDialogNodeType DialogNodeType = EDialogNodeType::UnKnown;
	//输入引脚
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="输入引脚",Category="RuntimeDialogNode")
	URuntimeDialogPin* InputDialogPin = nullptr;
	//输出引脚组
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="输出引脚组",Category="RuntimeDialogNode")
	TArray<URuntimeDialogPin*> OutputDialogPinArray;
	//节点位置
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="节点位置",Category="RuntimeDialogNode")
	FVector2D DialogNodePosition;
	//节点信息
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="节点信息",Category="RuntimeDialogNode")
	URuntimeDialogNodeInfoBase* RuntimeDialogNodeInfoBase = nullptr;
};

//图表信息
UCLASS(BlueprintType)
class DIALOGSYSTEM_API URuntimeDialogGraph: public UObject
{
	GENERATED_BODY()
public:
	//Id对应的节点
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,DisplayName="节点Id对应节点",Category="RuntimeDialogGraph")
	TMap<FName,URuntimeDialogNode*> Map_NodeIdToNode;
};
