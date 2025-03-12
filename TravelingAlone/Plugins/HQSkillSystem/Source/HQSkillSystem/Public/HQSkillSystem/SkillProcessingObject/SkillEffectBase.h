#pragma once
#include "HQSkillSystem/SkillSystemComponent.h"
#include "HQSkillSystem/HQSkillLibrary/HQSkillStructLibrary.h"
#include "SkillEffectBase.generated.h"

UCLASS(Blueprintable,BlueprintType,EditInlineNew,Abstract)
class HQSKILLSYSTEM_API USkillEffectBase:public UObject
{
	GENERATED_BODY()
public:
	//变量*****************************************************

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="技能组件",Category="SkillEffectBase")
	USkillSystemComponent* SkillSystemComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="技能数据",Category="SkillEffectBase")
	FHQSkillInfo HQSkillLInfo;
	
	//函数*****************************************************

	//效果开始
	virtual void InitSkillEffect(USkillSystemComponent* NewSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo)
	{SkillSystemComponent = NewSkillSystemComponent;HQSkillLInfo = NewHQSkillLInfo;InitSkillEffectEvent();}
	UFUNCTION(BlueprintImplementableEvent,DisplayName="效果开始事件",Category="SkillEffectBase")
	void InitSkillEffectEvent();
	
};

//演示**********************************************************

//技能CD效果器(不允许蓝图继承)
UCLASS(NotBlueprintable)
class HQSKILLSYSTEM_API USkillCDEffect : public USkillEffectBase
{
	GENERATED_BODY()
public:
	//变量*****************************************************

	//技能最大冷却（秒计）
	UPROPERTY(EditAnywhere, BlueprintReadWrite,DisplayName="技能最大冷却",Category="SkillEffectBase")
	float SkillMaxCoolDown = 1;
	//开始时间
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="开始时间",Category="SkillEffectBase")
	float CoolDownStartTime = 1;
	//CD定时器
	FTimerHandle CDTimerHandle;
	
	//函数*****************************************************

	//效果开始
	virtual void InitSkillEffect(USkillSystemComponent* NewSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo)override
	{
		SkillSystemComponent = NewSkillSystemComponent;
		HQSkillLInfo = NewHQSkillLInfo;
		CoolDownStartTime = SkillSystemComponent->GetWorld()->GetTimeSeconds();
		SkillSystemComponent->GetWorld()->GetTimerManager().SetTimer(CDTimerHandle,this,&USkillCDEffect::CDTimerHandleEvent,SkillMaxCoolDown,false);
		InitSkillEffectEvent();
	}
	//CD结束事件
	void CDTimerHandleEvent()
	{
		SkillSystemComponent->GetWorld()->GetTimerManager().ClearTimer(CDTimerHandle);
		SkillSystemComponent->SkillCoolDownEnd(HQSkillLInfo.SkillId);
		ConditionalBeginDestroy();//添加标记销毁
	}
	//获取剩余时间
	float GetResidueCoolDown(){return SkillMaxCoolDown - (SkillSystemComponent->GetWorld()->GetTimeSeconds() - CoolDownStartTime);}
};

