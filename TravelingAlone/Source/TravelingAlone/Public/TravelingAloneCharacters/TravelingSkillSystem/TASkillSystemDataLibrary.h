#pragma once
#include "HQSkillSystem/HQSkillLibrary/HQSkillStructLibrary.h"
#include "TASkillSystemDataLibrary.generated.h"

class USkillProcessingObjectBase;
UENUM()
enum ESkillType
{
	EST_Basic UMETA(DisplayName = "基础类型"),
};

USTRUCT(BlueprintType)
struct FTASkillBaseInfo :public FTableRowBase
{
	GENERATED_BODY()

	//技能类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能类型",Category="TASkillBaseInfo")
	TEnumAsByte<ESkillType> SkillType = ESkillType::EST_Basic;
	//技能名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能名称",Category="TASkillBaseInfo")
	FText SkillName = FText::FromString(TEXT("技能名称"));
	//技能图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能图标",Category="TASkillBaseInfo")
	UTexture2D* SkillIcon = nullptr;
	//技能介绍
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能介绍",Category="TASkillBaseInfo")
	FText SkillIntroduce = FText::FromString(TEXT("技能介绍"));
	//技能触发类
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能触发类",Category="TASkillBaseInfo")
	TSubclassOf<USkillProcessingObjectBase> SkillProcessingClass = nullptr;
	//技能可触发次数(默认值)
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能可触发次数",Category="TASkillBaseInfo")
	int32 SkillMaxTiggerNum = 1;
	
};

USTRUCT(BlueprintType)
struct FTASkillEntityInfo
{
	GENERATED_BODY()
	//技能命名ID（用来查找此技能对应的静态基础数据）
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能命名ID",Category="TASkillEntityInfo")
	FName SkillFNameId = NAME_None;
	//技能等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能等级",Category="TASkillEntityInfo")
	int32 SkillLevel = 1;
	
};

USTRUCT(BlueprintType)
struct FTASkillInfo
{
	GENERATED_BODY()

	//技能基本数据（由数据表格中获取，不需要手动配置）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="技能基本数据",Category="TASkillBaseInfo")
	FTASkillBaseInfo SkillBaseInfo;
	//技能实体数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能实体数据",Category="TASkillEntityInfo")
	FTASkillEntityInfo SkillEntityInfo;
	
};
