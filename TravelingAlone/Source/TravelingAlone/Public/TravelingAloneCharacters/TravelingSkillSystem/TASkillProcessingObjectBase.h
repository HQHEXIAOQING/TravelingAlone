#pragma once
#include "TASkillSystemDataLibrary.h"
#include "HQSkillSystem/SkillProcessingObject/SkillProcessingObjectBase.h"
#include "TASkillProcessingObjectBase.generated.h"

UCLASS()
class TRAVELINGALONE_API UTASkillProcessingObjectBase : public USkillProcessingObjectBase
{
	GENERATED_BODY()
public:
	
	//函数*******************************************************

	//获取技能数据
	UFUNCTION(BlueprintCallable,BlueprintPure,DisplayName="获取技能数据",Category="TASkillProcessingObjectBase")
	bool GetTASkillDataInfo(FTASkillInfo& TASkillInfo);
};
