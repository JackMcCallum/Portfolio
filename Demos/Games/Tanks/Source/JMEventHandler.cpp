#include "StdAfx.h"
#include "JMEventHandler.h"

	// ------------------------------------------------------------------------------------------------------------
	void JMEventHandler::addListener(JMEventListener* listener)
	{
		listenerList.push_back(listener);
	}
	// ------------------------------------------------------------------------------------------------------------
	void JMEventHandler::removeListener(JMEventListener* listener)
	{
		listenerList.remove(listener);
	}
	// ------------------------------------------------------------------------------------------------------------
	void JMEventHandler::removeAll()
	{
		listenerList.clear();
	}
