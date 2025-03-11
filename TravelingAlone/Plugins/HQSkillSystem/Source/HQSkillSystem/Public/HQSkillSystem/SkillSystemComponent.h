#pragma once
#include "SkillSystemComponent.generated.h"

class USkillCDEffect;
struct FHQSkillInfo;
class USkillProcessingObjectBase;

UCLASS(Blueprintable,BlueprintType)
class HQSKILLSYSTEM_API USkillSystemComponent:public UActorComponent
{
	GENERATED_BODY()
public:
	//变量*********************************************

	//当前激活的所有技能
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="当前激活的所有技能",Category="SkillSystemComponent")
	TMap<FName,USkillProcessingObjectBase*> Map_SkillIDToSkillObject;
	//当前激活的技能对应CD效果器
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="当前激活的技能对应CD效果器",Category="SkillSystemComponent")
	TMap<FName,USkillCDEffect*> Map_SkillToSkillCDEffect;
	
	//函数*********************************************

	//激活技能
	UFUNCTION(BlueprintCallable,DisplayName="激活技能",Category="SkillSystemComponentFunction")
	virtual bool ActivateSkill(FHQSkillInfo NewHQSkillLInfo,TSubclassOf<USkillProcessingObjectBase> ActivateSkill);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="激活技能事件",meta=(ToolTip = "这里的激活事件只会在技能第一次被激活时调用。"),Category="SkillSystemComponent")
	void ActivateSkillEvent(USkillProcessingObjectBase* CurrentActivateSkill);
	//移除结束技能（将已经结束的技能进行移除）
	virtual void RemoveEndSkill(FName RemoveSkillId);
	
	//技能应用冷却
	UFUNCTION(BlueprintCallable,DisplayName="技能应用冷却",Category="SkillSystemComponentFunction")
	virtual void SkillApplyCoolDown(FHQSkillInfo CoolDownSkillInfo,USkillCDEffect* NewSkillCDEffect);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="技能应用冷却事件",Category="SkillSystemComponent")
	void SkillApplyCoolDownEvent(FName CoolDownSkillID);
	//技能冷却结束
	UFUNCTION(BlueprintCallable,DisplayName="技能冷却结束",Category="SkillSystemComponentFunction")
	virtual void SkillCoolDownEnd(FName CoolDownSkillID);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="技能冷却结束事件",Category="SkillSystemComponent")
	void SkillCoolDownEndEvent(FName CoolDownSkillID);
	//获取对应技能剩余冷却
	UFUNCTION(BlueprintCallable,BlueprintPure,DisplayName="获取对应技能剩余冷却",Category="SkillSystemComponentFunction")
	float GetResidueCoolDown(FName CoolDownSkillID,bool& bIsSucceed);
};











