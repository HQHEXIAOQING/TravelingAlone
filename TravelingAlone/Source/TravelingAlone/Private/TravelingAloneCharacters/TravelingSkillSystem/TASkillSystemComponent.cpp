#include "TravelingAloneCharacters/TravelingSkillSystem/TASkillSystemComponent.h"

bool UTASkillSystemComponent::AddTASkillInfo(FTASkillEntityInfo NewTASkillEntityInfo)
{
	if (Map_TASkillIDToSkillInfo.Contains(NewTASkillEntityInfo.SkillFNameId)){return false;}//如果已经存在对应数据了，那就直接跳出
	
	//判断基本数据是否存在
	if (!SkillDataTable){return false;}
	if (!SkillDataTable->GetRowNames().Contains(NewTASkillEntityInfo.SkillFNameId)){return false;}
	//创建技能数据
	FTASkillInfo TASkillInfo;
	TASkillInfo.SkillEntityInfo = NewTASkillEntityInfo;
	TASkillInfo.SkillBaseInfo = *SkillDataTable->FindRow<FTASkillBaseInfo>(NewTASkillEntityInfo.SkillFNameId,TEXT("UTASkillSystemComponent::ActivateTravelingSkill 这里在对应的表格中没有找到对应的数据！"));
	Map_TASkillIDToSkillInfo.Add(NewTASkillEntityInfo.SkillFNameId,TASkillInfo);
	return true;
}

void UTASkillSystemComponent::RemoveTASkillInfo(FName RemoveSkillId)
{
	if (!Map_TASkillIDToSkillInfo.Contains(RemoveSkillId)){return;}
	Map_TASkillIDToSkillInfo.Remove(RemoveSkillId);
}

