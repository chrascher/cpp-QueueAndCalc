#pragma once
#include "ExceptionBase.h"
class QueueOverFlowException :
	public ExceptionBase
{
public:
	QueueOverFlowException();
	~QueueOverFlowException();
};

