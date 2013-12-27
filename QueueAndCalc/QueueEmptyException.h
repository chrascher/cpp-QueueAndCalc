#pragma once
#include "ExceptionBase.h"
class QueueEmptyException :
	public ExceptionBase
{
public:
	QueueEmptyException();
	virtual ~QueueEmptyException();


};

