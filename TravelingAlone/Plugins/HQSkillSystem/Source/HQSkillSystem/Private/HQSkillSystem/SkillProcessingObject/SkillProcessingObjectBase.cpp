#include "HQSkillSystem/SkillProcessingObject/SkillProcessingObjectBase.h"
#include "HQSkillSystem/SkillSystemComponent.h"
#include "HQSkillSystem/SkillProcessingObject/SkillActivateConditionBase.h"
#include "HQSkillSystem/SkillProcessingObject/SkillEffectBase.h"

UWorld* USkillProcessingObjectBase::GetWorld() const
{
	USkillSystemComponent* SkillSystemComponent = Cast<USkillSystemComponent>(GetOuter());
	if (SkillSystemComponent)
	{
		AActor* Actor = SkillSystemComponent->GetOwner();
		if (Actor){return Actor->GetWorld();}
	}
	return nullptr;
}

bool USkillProcessingObjectBase::CanActivateSkillStart(USkillSystemComponent* ActivateSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo)
{
	//循环所有的条件，只要有一条失败，就不能触发此技能
	for (USkillActivateConditionBase* SkillActivateCondition:SkillActivateConditionArray)
	{if (!SkillActivateCondition->SkillActivateCondition(ActivateSkillSystemComponent,NewHQSkillLInfo)){return false;}}
	return true;
}

void USkillProcessingObjectBase::SkillStart(USkillSystemComponent* ActivateSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo)
{
	OwnerSkillSystemComponent = ActivateSkillSystemComponent;
	HQSkillLInfo = NewHQSkillLInfo;
	SkillStartEvent(HQSkillLInfo);
}

void USkillProcessingObjectBase::SkillTriggerRepeatedly(FHQSkillInfo NewHQSkillLInfo)
{
	HQSkillLInfo = NewHQSkillLInfo;
	SkillTriggerRepeatedlyEvent(HQSkillLInfo);
}

void USkillProcessingObjectBase::SkillEnd(bool bIsNormalEnd)
{
	SkillEndEvent(bIsNormalEnd);
	OwnerSkillSystemComponent->RemoveEndSkill(HQSkillLInfo.SkillId);
	ConditionalBeginDestroy();//标记此对象需要被销毁
}

void USkillProcessingObjectBase::SkillApplyCoolDown(float MaxCD)
{
	USkillCDEffect* SkillCD = NewObject<USkillCDEffect>(OwnerSkillSystemComponent);
	SkillCD->SkillMaxCoolDown = MaxCD;
	OwnerSkillSystemComponent->SkillApplyCoolDown(HQSkillLInfo,SkillCD);
}









