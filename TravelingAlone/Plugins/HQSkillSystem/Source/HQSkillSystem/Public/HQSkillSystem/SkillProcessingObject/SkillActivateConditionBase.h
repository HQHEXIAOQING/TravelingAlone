#pragma once
#include "HQSkillSystem/SkillSystemComponent.h"
#include "HQSkillSystem/HQSkillLibrary/HQSkillStructLibrary.h"
#include "SkillActivateConditionBase.generated.h"

UCLASS(Blueprintable,BlueprintType,EditInlineNew,Abstract)
class HQSKILLSYSTEM_API USkillActivateConditionBase:public UObject
{
	GENERATED_BODY()
public:
	//函数*****************************************************

	//条件判断
	virtual bool SkillActivateCondition(USkillSystemComponent* NewSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo){return SkillActivateConditionEvent();}
	UFUNCTION(BlueprintImplementableEvent,DisplayName="条件判断事件",Category="SkillActivateConditionBase")
	bool SkillActivateConditionEvent();
	
};

//技能处于CD中就不使用
UCLASS(NotBlueprintable)
class HQSKILLSYSTEM_API USkillCondition_CD:public USkillActivateConditionBase
{
	GENERATED_BODY()
public:
	//函数*****************************************************

	//判断此技能在这个角色身上是否处于CD中，如果处于CD中，那么就是失败
	virtual bool SkillActivateCondition(USkillSystemComponent* NewSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo)override
	{if (NewSkillSystemComponent->Map_SkillToSkillCDEffect.Contains(NewHQSkillLInfo.SkillId)){return false;}return true;}
	
};