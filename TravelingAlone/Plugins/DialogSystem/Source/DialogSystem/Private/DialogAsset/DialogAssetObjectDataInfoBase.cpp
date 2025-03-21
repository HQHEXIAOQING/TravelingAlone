#include "DialogAsset/DialogAssetObjectDataInfoBase.h"

void UDialogAssetObjectDataInfoBase::DialogAssetObjectInit(UDialogAsset* NewDialogAsset)
{
	DialogAsset = NewDialogAsset;
	DialogAssetObjectInitEvent();
}
