#include "UI/Ass9ChatInput.h"
#include "Player/Ass9PlayerController.h"
#include "Components/EditableTextBox.h"

void UAss9ChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(
		this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(
			this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UAss9ChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(
		this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(
			this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UAss9ChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			AAss9PlayerController* OwningAss9PlayerController = Cast<AAss9PlayerController>(OwningPlayerController);
			if (IsValid(OwningAss9PlayerController) == true)
			{
				OwningAss9PlayerController->SetChatMessageString(Text.ToString());

				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}
