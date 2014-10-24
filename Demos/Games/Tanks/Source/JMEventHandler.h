/****************************************************
Author: 
	Jack McCallum

Class: 
	JMF::EventHandler : public EventListener

Description: 
	Base class for all event handlers.
	Event handlers distribute their events too all listeners.

****************************************************/

#pragma once
#ifndef JMF_EVENT_HANDLER
#define JMF_EVENT_HANDLER

// Dependencies
#include "JMEventListener.h"
#include "StdAfx.h"

	class JMEventHandler
	{
	public:
		// Add a listener to the list of listeners
		void addListener(JMEventListener* listener);

		// Remove a listener from the list of listeners, this does not delete it
		void removeListener(JMEventListener* listener);

		// Clear the listener list, this does not delete them
		void removeAll();

	protected:
		// This list keeps track of all listeners
		std::list<JMEventListener*> listenerList;

		// Listener list iterator
		std::list<JMEventListener*>::iterator listenerIter;

	};

#endif
