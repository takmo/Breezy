/*
File: BreezySample.h

Copyright (c) 2011 TechnoBulldog

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#ifndef __BREEZYSAMPLE_H__
#define __BREEZYSAMPLE_H__

#include "Breezy.h"
#include "Gorilla.h"

#include <iostream>
#include <OIS/OIS.h>				// OIS
#include <OGRE/Ogre.h>				// OGRE

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	/** Class: BreezySample - A sample window for testing. **/
	class Sample : public Breezy::InputListener
	{
	public:
		Sample();			// Constructor
		~Sample();			// Destructor.

		void KeyPressed(const OIS::KeyEvent &evt);		// CALLBACK.
		void KeyReleased(const OIS::KeyEvent &evt);		// CALLBACK.
		void MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);	// CALLBACK.
		void MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);	// CALLBACK.
		void MouseMoved(const OIS::MouseEvent &evt);	// CALLBACK.
		bool Start();									// Start the object.
		bool Stop();									// Stop the object.
		void WindowClosed(Ogre::RenderWindow * win);	// CALLBACK.
		void WindowResized(Ogre::RenderWindow * win);	// CALLBACK.

	protected:
		bool _SetZero();					// Set all variables to zero.
		bool _StartOgre(Ogre::String title);// Start Ogre.
		bool _StopOgre();					// Stop Ogre.

	protected:
		bool cont;						// Should we continue with the main loop?
		Breezy::Input * input;			// The Breezy::Input system.
		Ogre::Camera * camera;			// Ogre::Camera.
		Ogre::RenderWindow * window;	// The current window we are getting input from.
		Ogre::Root * root;				// Ogre::Root.
		Ogre::SceneManager * sm;		// Ogre::SceneManager.
		Ogre::Viewport * viewport;		// Ogre::Viewport.
	};
};

#endif