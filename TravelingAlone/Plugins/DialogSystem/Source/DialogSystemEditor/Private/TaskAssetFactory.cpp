﻿#include "TaskAssetFactory.h"
#include "AssetClassParentFilter.h"
#include "ClassViewerModule.h"
#include "Kismet2/SClassPickerDialog.h"
#include "TaskAsset/TaskAsset.h"

//构造函数
UTaskAssetFactory::UTaskAssetFactory(const FObjectInitializer& ObjectInitializer):
Super(ObjectInitializer)
{
	SupportedClass = UTaskAsset::StaticClass();
}

//创建一个资产
UObject* UTaskAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	//返回创建一个我们自定义的对话资产
	if (InClass->IsChildOf(UTaskAsset::StaticClass()))
	{
		return NewObject<UTaskAsset>(InParent, GenericGraphClass, InName, Flags);
	}
	else
	{
		return nullptr;
	}
}

bool UTaskAssetFactory::ConfigureProperties()
{
	//取消当前的选择
	GenericGraphClass = nullptr;

	//加载一个类型选择器
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	//添加选项
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::Type::ClassPicker;

	TSharedRef<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilters.Add(Filter);
	
	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UTaskAsset::StaticClass());

	const FText TitleText = FText::FromString(TEXT("资产类型选择"));
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UTaskAsset::StaticClass());
	if ( bPressedOk )
	{
		GenericGraphClass = ChosenClass;
	}
	return bPressedOk;
}
