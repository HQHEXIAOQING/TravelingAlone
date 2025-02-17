#pragma once
#include "CoreMinimal.h"
#include "CustomUMGSturctLibrary.generated.h"


//自定义控件结构**************************************************

//按钮结构
USTRUCT(BlueprintType,Blueprintable,DisplayName="自定义按钮设置",Category="CustomButton")
struct FCustomButton
{
	GENERATED_BODY()

	//动态材质接口（请确保材质中有Texture纹理的参数存在，为了能修改纹理参数）
	UPROPERTY(BlueprintReadWrite,EditAnywhere,DisplayName="材质接口",Category="CustomButton")
	TSoftObjectPtr<UMaterialInstance> Material = nullptr;
	//纹理
	UPROPERTY(BlueprintReadWrite,EditAnywhere,DisplayName="纹理",Category="CustomButton")
	TSoftObjectPtr<UTexture2D> Texture = nullptr;
	//按钮笔刷样式
	UPROPERTY(BlueprintReadWrite,EditAnywhere,DisplayName="按钮笔刷样式",Category="CustomButton")
	FSlateBrush ButtonTexture;
};