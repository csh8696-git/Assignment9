#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Ass9PlayerController.generated.h"

class UAss9ChatInput;
class UUserWidget;

UCLASS()
class ASSIGNMNET9_API AAss9PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAss9PlayerController();

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAss9ChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UAss9ChatInput> ChatInputWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;

	FString ChatMessageString;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;
};
