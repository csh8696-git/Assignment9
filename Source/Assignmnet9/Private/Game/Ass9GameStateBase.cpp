#include "Game/Ass9GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Ass9PlayerController.h"

void AAss9GameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			AAss9PlayerController* A9PC = Cast<AAss9PlayerController>(PC);
			if (IsValid(A9PC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				A9PC->PrintChatMessageString(NotificationString);
			}
		}
	}
}
