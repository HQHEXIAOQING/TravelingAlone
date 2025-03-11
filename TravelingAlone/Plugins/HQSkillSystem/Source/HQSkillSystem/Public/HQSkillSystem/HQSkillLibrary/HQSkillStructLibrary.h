#pragma once
#include "HQSkillStructLibrary.generated.h"

//技能数据
USTRUCT(BlueprintType)
struct FHQSkillInfo
{
	GENERATED_BODY()
	//技能命名
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="技能命名",Category="HQSkillLInfo")
	FName SkillId = NAME_None;
	//发起目标
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="发起目标",Category="HQSkillLInfo")
	TObjectPtr<AActor> Instigator = nullptr;
	//技能目标对象（可能为空）
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能目标",Category="HQSkillLInfo")
	TObjectPtr<AActor> Target = nullptr;
	//技能附带数据（可能为空）用于扩展此技能需要附带的其他数据内容
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能附带数据",Category="HQSkillLInfo")
	TObjectPtr<UObject> OptionalObject = nullptr;
	
};
