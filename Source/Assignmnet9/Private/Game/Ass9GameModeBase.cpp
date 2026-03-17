#include "Game/Ass9GameModeBase.h"
#include "Game/Ass9GameStateBase.h"
#include "Player/Ass9PlayerController.h"
#include "Player/Ass9PlayerState.h"
#include "EngineUtils.h"

void AAss9GameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AAss9PlayerController* Ass9PlayerController = Cast<AAss9PlayerController>(NewPlayer);
	if (IsValid(Ass9PlayerController) == true)
	{
		AllPlayerControllers.Add(Ass9PlayerController);

		AAss9PlayerState* A9PS = Ass9PlayerController->GetPlayerState<AAss9PlayerState>();
		if (IsValid(A9PS) == true)
		{
			A9PS->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		AAss9GameStateBase* Ass9GameStateBase = GetGameState<AAss9GameStateBase>();
		if (IsValid(Ass9GameStateBase) == true)
		{
			Ass9GameStateBase->MulticastRPCBroadcastLoginMessage(A9PS->PlayerNameString);
		}
	}
}

void AAss9GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
}

FString AAss9GameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; i++)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 Num) { return Num > 0; });

	FString Result;
	for (int32 i = 1; i <= BaseballNumberLength; i++)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}
	return Result;
}

bool AAss9GameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {
		if (InNumberString.Len() != BaseballNumberLength)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}
		//

		if (bIsUnique == false)
		{
			break;
		}

		bCanPlay = true;

	} while (false);

	return bCanPlay;
}

FString AAss9GameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; i++)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%d S %d B"), StrikeCount, BallCount);
}

void AAss9GameModeBase::PrintChatMessageString(AAss9PlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		IncreaseGuessCount(InChattingPlayerController);
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		for (TActorIterator<AAss9PlayerController> It(GetWorld()); It; ++It)
		{
			AAss9PlayerController* Ass9PlayerController = *It;
			if (IsValid(Ass9PlayerController) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				Ass9PlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
	else
	{
		for (TActorIterator<AAss9PlayerController> It(GetWorld()); It; ++It)
		{
			AAss9PlayerController* Ass9PlayerController = *It;
			if (IsValid(Ass9PlayerController) == true)
			{
				Ass9PlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}

void AAss9GameModeBase::IncreaseGuessCount(AAss9PlayerController* InChattingPlayerController)
{
	AAss9PlayerState* A9PS = InChattingPlayerController->GetPlayerState<AAss9PlayerState>();
	if (IsValid(A9PS) == true)
	{
		A9PS->CurrentGuessCount++;
	}
}

void AAss9GameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();

	for (const auto& Ass9PlayerController : AllPlayerControllers)
	{
		AAss9PlayerState* A9PS = Ass9PlayerController->GetPlayerState<AAss9PlayerState>();
		if (IsValid(A9PS) == true)
		{
			A9PS->CurrentGuessCount = 0;
		}
	}
}

void AAss9GameModeBase::JudgeGame(AAss9PlayerController* InChattingPlayerController, int32 InStrikeCount)
{
	if (3 == InStrikeCount)
	{
		AAss9PlayerState* A9PS = InChattingPlayerController->GetPlayerState<AAss9PlayerState>();
		for (const auto& Ass9PlayerController : AllPlayerControllers)
		{
			if (IsValid(A9PS) == true)
			{
				FString CombinedMessageString = A9PS->PlayerNameString + TEXT(" has won the game.");
				Ass9PlayerController->NotificationText = FText::FromString(CombinedMessageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& Ass9PlayerController : AllPlayerControllers)
		{
			AAss9PlayerState* A9PS = Ass9PlayerController->GetPlayerState<AAss9PlayerState>();
			if (IsValid(A9PS) == true)
			{
				if (A9PS->CurrentGuessCount < A9PS->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (true == bIsDraw)
		{
			for (const auto& Ass9PlayerController : AllPlayerControllers)
			{
				Ass9PlayerController->NotificationText = FText::FromString(TEXT("Draw..."));

				ResetGame();
			}
		}
	}
}

