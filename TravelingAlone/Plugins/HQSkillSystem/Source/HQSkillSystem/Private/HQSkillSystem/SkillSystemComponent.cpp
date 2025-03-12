#include "HQSkillSystem/SkillSystemComponent.h"
#include "HQSkillSystem/SkillProcessingObject/SkillEffectBase.h"
#include "HQSkillSystem/SkillProcessingObject/SkillProcessingObjectBase.h"

bool USkillSystemComponent::ActivateSkill(FHQSkillInfo NewHQSkillLInfo,TSubclassOf<USkillProcessingObjectBase> ActivateSkillClass)
{
	if (Map_SkillIDToSkillObject.Contains(NewHQSkillLInfo.SkillId))//判断技能是否还在执行中
	{
		//判断此技能是否可以激活
		if (Map_SkillIDToSkillObject[NewHQSkillLInfo.SkillId]->CanActivateSkillStart(this,NewHQSkillLInfo))
		{Map_SkillIDToSkillObject[NewHQSkillLInfo.SkillId]->SkillTriggerRepeatedly(NewHQSkillLInfo);return true;}//技能重复触发
		return false;
	}else
	{
		TObjectPtr<USkillProcessingObjectBase> Skill = NewObject<USkillProcessingObjectBase>(this, ActivateSkillClass);
		if (Skill->CanActivateSkillStart(this,NewHQSkillLInfo))//判断激活条件是否满足
		{
			Skill->SkillStart(this,NewHQSkillLInfo);//触发技能开始
			Map_SkillIDToSkillObject.Add(NewHQSkillLInfo.SkillId,Skill);//在已执行的技能中添加此技能
			ActivateSkillEvent(Skill);
			return true;
		}else{Skill->ConditionalBeginDestroy();}//如果条件不满足应该直接销毁此对象。
		return false;
	}
}

void USkillSystemComponent::RemoveEndSkill(FName RemoveSkillId)
{
	if (Map_SkillIDToSkillObject.Contains(RemoveSkillId))//判断技能是否还存在
	{Map_SkillIDToSkillObject.Remove(RemoveSkillId);}//存在就移除就可以了
}

void USkillSystemComponent::SkillApplyCoolDown(FHQSkillInfo CoolDownSkillID,USkillCDEffect* NewSkillCDEffect)
{
	//判断此技能是否已经添加过CD效果了，如果添加过，重复添加的情况下移除第一个对象并且设置第一个对象销毁
	if (Map_SkillToSkillCDEffect.Contains(CoolDownSkillID.SkillId))
	{
		GetWorld()->GetTimerManager().ClearTimer(Map_SkillToSkillCDEffect[CoolDownSkillID.SkillId]->CDTimerHandle);//清除此定时器
		Map_SkillToSkillCDEffect[CoolDownSkillID.SkillId]->ConditionalBeginDestroy();//标记销毁
		Map_SkillToSkillCDEffect.Remove(CoolDownSkillID.SkillId);
	}
	Map_SkillToSkillCDEffect.Add(CoolDownSkillID.SkillId,NewSkillCDEffect);
	NewSkillCDEffect->InitSkillEffect(this,CoolDownSkillID);
	SkillApplyCoolDownEvent(CoolDownSkillID.SkillId);
}

void USkillSystemComponent::SkillCoolDownEnd(FName CoolDownSkillID)
{
	//判断技能CD是否存在，存在就移除此技能CD
	if (Map_SkillToSkillCDEffect.Contains(CoolDownSkillID))
	{
		Map_SkillToSkillCDEffect.Remove(CoolDownSkillID);
		SkillCoolDownEndEvent(CoolDownSkillID);
	}
}

float USkillSystemComponent::GetResidueCoolDown(FName CoolDownSkillID,bool& bIsSucceed)
{
	if (Map_SkillToSkillCDEffect.Contains(CoolDownSkillID))
	{bIsSucceed = true;return Map_SkillToSkillCDEffect[CoolDownSkillID]->GetResidueCoolDown();}
	bIsSucceed = false;return -1;
}




















