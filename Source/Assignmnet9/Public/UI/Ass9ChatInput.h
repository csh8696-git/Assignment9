#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Ass9ChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class ASSIGNMNET9_API UAss9ChatInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;
};
