// Dark Trace Studio Works


#include "UI/Interaction/TSA_PromptWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTSA_PromptWidget::SetPromptText(const FText& Text)
{
	Text_Prompt->SetText(Text);
}

void UTSA_PromptWidget::SetKeyImage(const FSlateBrush Brush)
{
	Image_Key->SetBrush(Brush);
}
