#include "Player/Ass9PlayerController.h"
#include "Player/Ass9PlayerState.h"
#include "Game/Ass9GameModeBase.h"
#include "UI/Ass9ChatInput.h"
#include "Assignmnet9.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

AAss9PlayerController::AAss9PlayerController()
{
	bReplicates = true;
}


void AAss9PlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AAss9PlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		AAss9GameModeBase* A9GM = Cast<AAss9GameModeBase>(GM);
		if (IsValid(A9GM) == true)
		{
			A9GM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void AAss9PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UAss9ChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void AAss9PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void AAss9PlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	if (IsLocalController() == true)
	{
		AAss9PlayerState* A9PS = GetPlayerState<AAss9PlayerState>();
		if (IsValid(A9PS) == true)
		{
			if (InChatMessageString.Len() == 3)
			{
				FString CombinedMessageString = A9PS->GetPlayerInfoString()
					+ TEXT(": ") + InChatMessageString;

				ServerRPCPrintChatMessageString(CombinedMessageString);
			}
			else
			{
				ClientRPCPrintChatMessageString(TEXT("Please enter a three-digit number"));
			}
		}
	}
}

void AAss9PlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	Assignment9FunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}