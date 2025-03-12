#pragma once
#include "TravelingAloneCharacters/TACharacterBase.h"
#include "TAPlayerCharacter.generated.h"

class USkillProcessingObjectBase;
struct FHQSkillInfo;

UCLASS()
class TRAVELINGALONE_API ATAPlayerCharacter: public ATACharacterBase
{
	GENERATED_BODY()
public:
	//函数**********************************************

	//移动输入
	UFUNCTION(BlueprintCallable,DisplayName="移动输入", Category = "TAPlayerCharacter")
	void MoveInput(FVector2D InputVector);
	//瞬步输入（翻滚）
	UFUNCTION(BlueprintCallable,DisplayName="瞬步输入", Category = "TAPlayerCharacter")
	void RollInput(FHQSkillInfo NewHQSkillLInfo,TSubclassOf<USkillProcessingObjectBase> ActivateSkill);
};
