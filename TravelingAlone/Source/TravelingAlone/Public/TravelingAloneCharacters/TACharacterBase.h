#pragma once
#include "GameFramework/Character.h"
#include "TACharacterBase.generated.h"

class UTASkillSystemComponent;

UCLASS()
class TRAVELINGALONE_API ATACharacterBase: public ACharacter
{
	GENERATED_BODY()
public:
	//变量************************************************
	
	//是否可以移动？
	UPROPERTY(EditAnywhere,BlueprintReadWrite,DisplayName="是否可以移动",Category="MovementSettings")
	bool bIsCanMove = true;

	//函数*************************************************

	//构造函数
	ATACharacterBase();
	
	//重载参数获取和设置方法***************************************************

	//获取技能组件
	UTASkillSystemComponent* GetSkillSystemComponent() const {return TASkillSystemComponent;}
	
protected:
	//变量**************************************************************
	
	//技能组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Getter = "GetSkillSystemComponent",DisplayName="技能组件", Category = "TACharacterBaseComponents")
	UTASkillSystemComponent* TASkillSystemComponent = nullptr;
	
};