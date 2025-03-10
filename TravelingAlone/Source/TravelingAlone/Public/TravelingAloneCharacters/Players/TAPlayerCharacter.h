#pragma once
#include "TravelingAloneCharacters/TACharacterBase.h"
#include "TAPlayerCharacter.generated.h"

UCLASS()
class TRAVELINGALONE_API ATAPlayerCharacter: public ATACharacterBase
{
	GENERATED_BODY()
public:
	//函数**********************************************

	UFUNCTION(BlueprintCallable,DisplayName="移动输入", Category = "TAPlayerCharacter")
	void MoveInput(FVector2D InputVector);
	
};
