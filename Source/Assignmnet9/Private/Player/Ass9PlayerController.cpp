#include "Player/Ass9PlayerController.h"
#include "Assignmnet9.h"
#include "Net/UnrealNetwork.h"

AAss9PlayerController::AAss9PlayerController()
{
	bReplicates = true;
}

void AAss9PlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	Assignment9FunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void AAss9PlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AAss9PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}