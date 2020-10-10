#pragma once
enum class PaymentType
{
	CASH =0,
	CREDIT_CARD = 1,
	CHECK = 2,
	OTHER  = 3
};

enum class DialogMode
{
	CREATE_NEW_MODE,
	UPDATE_MODE
};