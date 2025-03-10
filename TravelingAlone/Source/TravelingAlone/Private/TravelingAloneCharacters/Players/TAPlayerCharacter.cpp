#include "TravelingAloneCharacters/Players/TAPlayerCharacter.h"

void ATAPlayerCharacter::MoveInput(FVector2D InputVector)
{
	AddMovementInput(FVector(InputVector.X, InputVector.Y, 0));//添加移动输入
}
