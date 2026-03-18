#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Ass9GameStateBase.generated.h"



UCLASS()
class ASSIGNMNET9_API AAss9GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString
		= FString(TEXT("XXXXXX")));
};
