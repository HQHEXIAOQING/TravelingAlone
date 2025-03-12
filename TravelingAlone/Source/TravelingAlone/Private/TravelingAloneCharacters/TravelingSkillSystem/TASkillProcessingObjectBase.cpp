#include "TravelingAloneCharacters/TravelingSkillSystem/TASkillProcessingObjectBase.h"
#include "TravelingAloneCharacters/TravelingSkillSystem/TASkillSystemComponent.h"

bool UTASkillProcessingObjectBase::GetTASkillDataInfo(FTASkillInfo& TASkillInfo)
{
	TASkillInfo = FTASkillInfo();
	if (!OwnerSkillSystemComponent){return false;}//如果组件无效就表示此技能触发失败了！
	//判断是否为自定义的技能组件
	UTASkillSystemComponent* TASkillSystemComponent = Cast<UTASkillSystemComponent>(OwnerSkillSystemComponent);
	if (!TASkillSystemComponent){return false;}
	
	if (!TASkillSystemComponent->Map_TASkillIDToSkillInfo.Contains(HQSkillLInfo.SkillId)){return false;}//没有技能数据就输出为否
	
	TASkillInfo = TASkillSystemComponent->Map_TASkillIDToSkillInfo[HQSkillLInfo.SkillId];//设置对应数据
	return true;
	
}
