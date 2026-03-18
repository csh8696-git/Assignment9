#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Ass9PlayerState.generated.h"



UCLASS()
class ASSIGNMNET9_API AAss9PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AAss9PlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfoString();

public:
	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

	int32 MaxGuessCount;
};
