#include "TravelingAloneCharacters/Players/TAPlayerCharacter.h"
#include "HQSkillSystem/HQSkillLibrary/HQSkillStructLibrary.h"
#include "TravelingAloneCharacters/TravelingSkillSystem/TASkillSystemComponent.h"

void ATAPlayerCharacter::MoveInput(FVector2D InputVector)
{
	if (bIsCanMove){AddMovementInput(FVector(InputVector.X, InputVector.Y, 0));}//添加移动输入
}

void ATAPlayerCharacter::RollInput(FHQSkillInfo NewHQSkillLInfo,TSubclassOf<USkillProcessingObjectBase> ActivateSkill)
{
	TASkillSystemComponent->ActivateSkill(NewHQSkillLInfo,ActivateSkill);//激活瞬步技能
}





