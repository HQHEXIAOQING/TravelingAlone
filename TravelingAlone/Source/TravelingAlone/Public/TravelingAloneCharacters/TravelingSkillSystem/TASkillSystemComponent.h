#pragma once
#include "TASkillSystemDataLibrary.h"
#include "HQSkillSystem/SkillSystemComponent.h"
#include "TASkillSystemComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class TRAVELINGALONE_API UTASkillSystemComponent: public USkillSystemComponent
{
	GENERATED_BODY()
public:
	//变量***************************************************
	
	//技能数据所在表格
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能数据所在表格",Category="TASkillSystemComponent")
	UDataTable* SkillDataTable = nullptr;
	//拥有的技能以及对应数据
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="拥有的技能以及对应数据",Category="TASkillSystemComponent")
	TMap<FName,FTASkillInfo> Map_TASkillIDToSkillInfo;

	//添加拥有的技能
	UFUNCTION(BlueprintCallable,DisplayName="添加拥有的技能",Category="SkillSystemComponentFunction")
	bool AddTASkillInfo(FTASkillEntityInfo NewTASkillEntityInfo);
	//添加拥有的技能
	UFUNCTION(BlueprintCallable,DisplayName="移除拥有的技能",Category="SkillSystemComponentFunction")
	void RemoveTASkillInfo(FName RemoveSkillId);
	
};
