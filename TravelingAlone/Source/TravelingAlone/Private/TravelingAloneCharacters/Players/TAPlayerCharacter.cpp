#include "TravelingAloneCharacters/Players/TAPlayerCharacter.h"

void ATAPlayerCharacter::MoveInput(FVector2D InputVector)
{
	if (bIsCanMove){AddMovementInput(FVector(InputVector.X, InputVector.Y, 0));}//添加移动输入
}

void ATAPlayerCharacter::RollInput()
{
	//TODO::这里需要些一个瞬步的技能效果
}
