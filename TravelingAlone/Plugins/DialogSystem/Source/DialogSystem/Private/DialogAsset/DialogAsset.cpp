#include "DialogAsset/DialogAsset.h"
#include "DialogAsset/DialogAssetObjectDataInfoBase.h"
#include "DialogAsset/DialogConditionBase.h"
#include "DialogAsset/DialogNodeEffectorBase.h"
#include "DialogAsset/RuntimeDialogGraph.h"
#include "DialogAsset/RuntimeDialogNodeInfos/RuntimeDialogEndNodeInfo.h"
#include "DialogAsset/RuntimeDialogNodeInfos/RuntimeDialogNodeInfo.h"
#include "UObject/ObjectSaveContext.h"

//初始化对话资产，判断是否可以使用此对话资产。
bool UDialogAsset::DialogAssetInit(AActor* Owning,AActor* PlayerActor)
{
	if(!Owning)
	{
		UE_LOG(LogTemp,Error,TEXT("UDialogAsset::DialogAssetInit 没有OwningActor，必须拥有此对象输入"));
		return false;
	}
	//初始化对话包中的内容
	Map_PinIDToPinNum.Empty();
	Map_NameIDToParticipant.Empty();
	Map_NameIDToParticipant.Add("OwningActor",Owning);
	if(PlayerActor){Map_NameIDToParticipant.Add("PlayerActor",PlayerActor);}
	
	//进行球体检测
	TArray<FHitResult> HitResults;
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(Radius);
	//设置检测
	bool bHit =Owning->GetWorld()->SweepMultiByChannel(
		HitResults,
		Owning->GetActorLocation(),
		Owning->GetActorLocation(),
		FQuat::Identity,
		CollisionChannel,
		SphereShape);
	
	//获取零时的数据，移除主要对象和玩家对象
	TMap<FName,FParticipantCondition> Map_IdToParticipant = Map_NameIDToParticipantCondition;
	Map_IdToParticipant.Remove("OwningActor");
	Map_IdToParticipant.Remove("PlayerActor");
	//保存已经使用过的对象
	TArray<AActor*> Actors;
	Actors.Add(Map_NameIDToParticipant["OwningActor"]);
	if (Map_NameIDToParticipant.Contains("PlayerActor"))
	{Actors.Add(Map_NameIDToParticipant["PlayerActor"]);}
	
	for(FHitResult HitResult:HitResults)
	{
		bool IsAdd = false;
		FName AddName = NAME_None;
		//循环所有的对象对应的条件
		for(TPair IdToParticipantCondition:Map_IdToParticipant)
		{
			//循环这个对象的所有条件，只要有一个不符合就是不成立
			bool CanUse = true;
			for (UParticipantConditionBase* ParticipantCondition:IdToParticipantCondition.Value.ParticipantConditionArray)
			{
				if(!ParticipantCondition->ParticipantConditionIsSucceed(this,HitResult.GetActor()))
				{CanUse = false;break;}
			}
			//如果此Actor通过条件就添加此对象到对应Map中
			if(CanUse)
			{
				if (Actors.Contains(HitResult.GetActor())){break;}//如果已经存在了就直接跳出。
				IsAdd = true;AddName = IdToParticipantCondition.Key;
				Actors.Add(HitResult.GetActor());
				Map_NameIDToParticipant.Add(IdToParticipantCondition.Key,HitResult.GetActor());
				break;
			}
		}
		//判断是否已经添加过，如果添加了一条，那么就找下一条
		if(IsAdd)
		{
			//在所有名称中移除这个名称，这个名称已经有了对象，所以要移除。
			Map_IdToParticipant.Remove(AddName);
		}
	}
	
	//循环判断是否符合所有条件，如果符合那就输出初始化成功。
	for (UDialogAssetConditionBase* DialogAssetCondition:DialogAssetConditionArray)
	{if(!DialogAssetCondition->DialogPacketConditionIsSucceed(this)){return false;}}

	//判断数据处理类是否存在，如果存在，那就根据类型生成，如果不存在，那就生成默认的对象
	if (DialogAssetObjectDataInfoClass)
	{DialogAssetObjectDataInfoBase = NewObject<UDialogAssetObjectDataInfoBase>(this,DialogAssetObjectDataInfoClass);}
	else{DialogAssetObjectDataInfoBase = NewObject<UDialogAssetObjectDataInfoBase>(this);}
	DialogAssetObjectDataInfoBase->DialogAssetObjectInit(this);
	
	return true;
}

//获取首个对话节点信息
URuntimeDialogNode* UDialogAsset::GetDialogNodeFromFirst(URuntimeDialogNodeInfo* &DialogNodeInfo)
{
	URuntimeDialogNode* StartDialogNode = Cast<URuntimeDialogNode>(RuntimeDialogGraph->Map_NodeIdToNode["0"]);
	if (!StartDialogNode->OutputDialogPinArray[0]->Connection||!RuntimeDialogGraph->Map_NodeIdToNode.Find(StartDialogNode->OutputDialogPinArray[0]->Connection->NodeId))
	{
		UE_LOG(LogTemp,Error,TEXT("%s______这里的第一句话对象不存在，请检查对应的对话资产"),*this->GetName());
		return nullptr;
	}
	URuntimeDialogNode* DialogNode = RuntimeDialogGraph->Map_NodeIdToNode[StartDialogNode->OutputDialogPinArray[0]->Connection->NodeId];
	//判断引脚使用次数，并添加选项使用次数。
	if(Map_PinIDToPinNum.Find(StartDialogNode->OutputDialogPinArray[0]->DialogPinId))
	{
		int32 NewNum = *Map_PinIDToPinNum.Find(StartDialogNode->OutputDialogPinArray[0]->DialogPinId)+1;
		Map_PinIDToPinNum.Add(StartDialogNode->OutputDialogPinArray[0]->DialogPinId,NewNum);
	}
	else{Map_PinIDToPinNum.Add(StartDialogNode->OutputDialogPinArray[0]->DialogPinId,1);}

	//设置输出参数。
	DialogNodeInfo = Cast<URuntimeDialogNodeInfo>(DialogNode->RuntimeDialogNodeInfoBase);
	return DialogNode;
}

//获取对话节点
bool UDialogAsset::GetDialogNodeFromDialogId(FName DialogNodeId,URuntimeDialogNodeInfo* &DialogNodeInfo,URuntimeDialogNode* &DialogNode)
{
	DialogNode = Cast<URuntimeDialogNode>(RuntimeDialogGraph->Map_NodeIdToNode[DialogNodeId]);
	DialogNodeInfo = Cast<URuntimeDialogNodeInfo>(DialogNode->RuntimeDialogNodeInfoBase);
	return DialogNode&&DialogNodeInfo;
}

//获取结束节点
bool UDialogAsset::GetDialogEndNodeFromDialogId(FName DialogNodeId,URuntimeDialogEndNodeInfo* &DialogNodeInfo,URuntimeDialogNode* &DialogNode)
{
	DialogNode = Cast<URuntimeDialogNode>(RuntimeDialogGraph->Map_NodeIdToNode[DialogNodeId]);
	DialogNodeInfo = Cast<URuntimeDialogEndNodeInfo>(DialogNode->RuntimeDialogNodeInfoBase);
	return DialogNode&&DialogNodeInfo;
}

bool UDialogAsset::GetOutputPinFromDialogNode(URuntimeDialogNode* DialogNode,TMap<URuntimeDialogPin*, FDialogOutPinData>& Map_OutPinToOutPinData, bool& IsPlayerOption)
{
	if(!DialogNode){return false;}
	URuntimeDialogNodeInfo* DialogNodeInfo = Cast<URuntimeDialogNodeInfo>(DialogNode->RuntimeDialogNodeInfoBase);
	if(!DialogNodeInfo){return false;}
	
	TArray<FDialogOutPinData> OutPinDateArray = DialogNodeInfo->DialogOutPinArray;
	TArray<URuntimeDialogPin*> OutPinArray = DialogNode->OutputDialogPinArray;
	int32 OutPinNum = 0;
	int32 OutPinNPCBool = 0;//用来判断第一次进入是否是NPC
	for(FDialogOutPinData OutPinDate:OutPinDateArray)
	{
		//判断寻找下一个节点是否存在。
		URuntimeDialogNode* NextDialogNode = *RuntimeDialogGraph->Map_NodeIdToNode.Find(OutPinArray[OutPinNum]->Connection->NodeId);
		if(!NextDialogNode)
		{
			UE_LOG(LogTemp,Error,TEXT("%s,这个选项下的对话节点没有了，这是一个错误！"),*OutPinDate.DialogNodeTitle.ToString());
			return false;
		}
		//循环判断所有条件
		bool CanUse = true;
		for (UDialogNodeConditionBase* DialogNodeCondition:OutPinDate.DialogNodeCondition)
		{
			//如果有一个条件不符合就跳出和这个循环
			if(!DialogNodeCondition->DialogNodeConditionIsSucceed(this,DialogNode,NextDialogNode))
			{CanUse = false;break;}
		}

		OutPinNPCBool++;
		//有效就添加这个引脚对应数据
		if(CanUse)
		{
			//如果下一句是结束节点，那么就直接添加
			if(NextDialogNode->DialogNodeType == EDialogNodeType::DialogEndNode||NextDialogNode->DialogNodeType == EDialogNodeType::DialogJumpNode)
			{
				Map_OutPinToOutPinData.Add(OutPinArray[OutPinNum],OutPinDateArray[OutPinNum]);
				IsPlayerOption =true;
			}
			//如果是对话节点，判断是否是玩家
			if(NextDialogNode->DialogNodeType == EDialogNodeType::DialogNode)
			{
				URuntimeDialogNodeInfo* NextDialogNodeInfo = Cast<URuntimeDialogNodeInfo>(NextDialogNode->RuntimeDialogNodeInfoBase);
				if(NextDialogNodeInfo->DialogActorId == "PlayerActor")
				{
					//如果是玩家就添加一条
					Map_OutPinToOutPinData.Add(OutPinArray[OutPinNum],OutPinDateArray[OutPinNum]);
					IsPlayerOption =true;
				}else
				{
					//如果第一次进来就是NPC，那么就直接添加NPC的这个选项后跳出。
					if (OutPinNPCBool == 1)
					{
						//如果不是玩家就设置一条，然后跳出此函数。
						Map_OutPinToOutPinData.Empty();
						Map_OutPinToOutPinData.Add(OutPinArray[OutPinNum],OutPinDateArray[OutPinNum]);
						IsPlayerOption =false;
						return true;	
					}
				}
			}
		}
		OutPinNum++;
	}
	//全部找完，没有跳出，那么就跳出。
	return true;
}

//对话节点开始执行(输入当前引脚。)
bool UDialogAsset::DialogNodeInit(URuntimeDialogNode* DialogNode,URuntimeDialogPin* DialogNodePin)
{
	if(DialogNodePin)
	{
		int32 NewNum = 1;
		if(Map_PinIDToPinNum.Find(DialogNodePin->DialogPinId))
		{
			NewNum = Map_PinIDToPinNum[DialogNodePin->DialogPinId]+1;
		}
		Map_PinIDToPinNum.Add(DialogNodePin->DialogPinId,NewNum);
	}
	if (!DialogNode){return false;}
	if(DialogNode->DialogNodeType == EDialogNodeType::DialogEndNode||DialogNode->DialogNodeType == EDialogNodeType::DialogStartNode)
	{
		TArray<UDialogNodeEffectorBase*> EndEffectors =	DialogNode->RuntimeDialogNodeInfoBase->DialogNodeEffectorArray;
		for (UDialogNodeEffectorBase* DialogNodeEffector:EndEffectors)
		{
			if(!DialogNodeEffector){continue;}
			DialogNodeEffector->DialogNodeEffectorPlay(this,Map_NameIDToParticipant["PlayerActor"]);
		}
		return true;
	}
	TArray<UDialogNodeEffectorBase*> Effectors;
	if(DialogNode->DialogNodeType == EDialogNodeType::DialogNode||DialogNode->DialogNodeType == EDialogNodeType::DialogJumpNode)
	{
		URuntimeDialogNodeInfo* NodeInfo=Cast<URuntimeDialogNodeInfo>(DialogNode->RuntimeDialogNodeInfoBase);
		Effectors =	DialogNode->RuntimeDialogNodeInfoBase->DialogNodeEffectorArray;
		//循环触发所有的效果
		for (UDialogNodeEffectorBase* DialogNodeEffector:Effectors)
		{
			if(!DialogNodeEffector){continue;}
			DialogNodeEffector->DialogNodeEffectorPlay(this,Map_NameIDToParticipant[NodeInfo->DialogActorId]);
		}
		return true;
	}
	return false;
}

void UDialogAsset::PreSave(FObjectPreSaveContext SaveContext)
{
	//如果指向的位置有函数，我应该调用一下这个函数，这里指向的是APP中保存数据的函数。
	if(_OnPreSaveListener)
	{
		_OnPreSaveListener();
	}
	Super::PreSave(SaveContext);
}
