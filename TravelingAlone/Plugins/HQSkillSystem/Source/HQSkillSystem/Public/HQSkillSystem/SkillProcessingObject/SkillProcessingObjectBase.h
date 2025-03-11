#pragma once
#include "HQSkillSystem/HQSkillLibrary/HQSkillStructLibrary.h"
#include "SkillProcessingObjectBase.generated.h"

class USkillActivateConditionBase;
class USkillSystemComponent;

//技能处理对象
UCLASS(Blueprintable,BlueprintType)
class HQSKILLSYSTEM_API USkillProcessingObjectBase:public UObject
{
	GENERATED_BODY()
public:
	//变量****************************************************************

	//技能激活条件组
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(EditInline = "true"),DisplayName="技能激活条件组",Category="SkillProcessingObject")
	TArray<TObjectPtr<USkillActivateConditionBase>> SkillActivateConditionArray;
	//触发此技能的技能组件（触发来源）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="触发来源组件",Category="SkillProcessingObject")
	USkillSystemComponent* OwnerSkillSystemComponent = nullptr;
	//技能所带数据
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,DisplayName="技能所带数据",Category="SkillProcessingObject")
	FHQSkillInfo HQSkillLInfo;
	
	//重载事件*************************************************************
	
	//重载获取世界的方法
	virtual UWorld* GetWorld() const override;
	
	//函数***************************************************************

	//是否可以激活技能
	virtual bool CanActivateSkillStart(USkillSystemComponent* ActivateSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo);
	//技能开始
	UFUNCTION(DisplayName="技能开始",Category="SkillProcessingObject")
	virtual void SkillStart(USkillSystemComponent* ActivateSkillSystemComponent,FHQSkillInfo NewHQSkillLInfo);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="技能开始事件",Category="SkillProcessingObject")
	void SkillStartEvent(FHQSkillInfo NewHQSkillLInfo);
	//技能重复触发
	UFUNCTION(DisplayName="技能重复触发",Category="SkillProcessingObject")
	virtual void SkillTriggerRepeatedly(FHQSkillInfo NewHQSkillLInfo);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="技能重复触发事件",Category="SkillProcessingObject")
	void SkillTriggerRepeatedlyEvent(FHQSkillInfo NewHQSkillLInfo);
	//技能结束（是否正常结束的）
	UFUNCTION(BlueprintCallable,DisplayName="技能结束",Category="SkillProcessingObject")
	virtual void SkillEnd(bool bIsNormalEnd);
	UFUNCTION(BlueprintImplementableEvent,DisplayName="技能结束事件",Category="SkillProcessingObject")
	void SkillEndEvent(bool bIsNormalEnd);

	//技能应用冷却
	UFUNCTION(BlueprintCallable,DisplayName="技能应用冷却",Category="SkillProcessingObject")
	virtual void SkillApplyCoolDown(float MaxCD);
	
};
