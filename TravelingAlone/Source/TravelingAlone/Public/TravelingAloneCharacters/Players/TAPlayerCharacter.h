#pragma once
#include "TravelingAloneCharacters/TACharacterBase.h"
#include "TAPlayerCharacter.generated.h"

UCLASS()
class TRAVELINGALONE_API ATAPlayerCharacter: public ATACharacterBase
{
	GENERATED_BODY()
public:
	//变量*******************************************************

	//是否可以移动？
	UPROPERTY(EditAnywhere,BlueprintReadWrite,DisplayName="是否可以移动",Category="MovementSettings")
	bool bIsCanMove = true;
	
	//函数**********************************************

	//移动输入
	UFUNCTION(BlueprintCallable,DisplayName="移动输入", Category = "TAPlayerCharacter")
	void MoveInput(FVector2D InputVector);
	//瞬步输入（翻滚）
	UFUNCTION(BlueprintCallable,DisplayName="瞬步输入", Category = "TAPlayerCharacter")
	void RollInput();
};
