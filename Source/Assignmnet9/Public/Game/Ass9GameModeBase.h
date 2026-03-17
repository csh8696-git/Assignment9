#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Ass9GameModeBase.generated.h"

class AAss9PlayerController;

UCLASS()
class ASSIGNMNET9_API AAss9GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	virtual void BeginPlay() override;

	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString,
		const FString& InGuessNumberString);

	void PrintChatMessageString(AAss9PlayerController* InChattingPlayerController,
		const FString& InChatMessageString);

	void IncreaseGuessCount(AAss9PlayerController* InChattingPlayerController);

	void ResetGame();

	void JudgeGame(AAss9PlayerController* InChattingPlayerController, int32 InStrikeCount);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<AAss9PlayerController>> AllPlayerControllers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game|Rules")
	int32 BaseballNumberLength = 3;
};
