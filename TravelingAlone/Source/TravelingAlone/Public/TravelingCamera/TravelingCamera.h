#pragma once
#include "TravelingCamera.generated.h"

class ATAPlayerCharacter;

UCLASS()
class TRAVELINGALONE_API ATravelingCamera: public APawn
{
	GENERATED_BODY()
public:
	//函数****************************************************

	//相机初始化
	UFUNCTION(BlueprintCallable,DisplayName="相机初始化", Category="TravelingCameraFunction")
	void InitTravelingCamera(ATAPlayerCharacter* NewPlayerCharacter);

	//自定义读取方法*****************************************************************

	//设置和获取控制角色对象
	void SetPlayerCharacter(ATAPlayerCharacter* NewPlayerCharacter){PlayerCharacter = NewPlayerCharacter;}
	ATAPlayerCharacter* GetPlayerCharacter() const{return PlayerCharacter;}
	
protected:
	//变量*************************************************
	
	//控制对象(游戏中实际控制的玩家角色而不是摄像机)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Setter = "SetPlayerCharacter",Getter = "GetPlayerCharacter",DisplayName="控制对象", Category = "TravelingCameraBase")
	ATAPlayerCharacter* PlayerCharacter = nullptr;
	
};
