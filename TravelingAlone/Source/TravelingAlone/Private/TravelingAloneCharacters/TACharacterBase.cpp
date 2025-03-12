#include "TravelingAloneCharacters/TACharacterBase.h"
#include "TravelingAloneCharacters/TravelingSkillSystem/TASkillSystemComponent.h"

ATACharacterBase::ATACharacterBase()
{
	TASkillSystemComponent = CreateDefaultSubobject<UTASkillSystemComponent>(TEXT("SkillSystemComponent"));

}
