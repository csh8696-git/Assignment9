#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Ass9PlayerController.generated.h"



UCLASS()
class ASSIGNMNET9_API AAss9PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAss9PlayerController();

	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
};
