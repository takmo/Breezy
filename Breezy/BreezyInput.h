/*
File: BreezyInput.h

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

#ifndef __BREEZYINPUT_H__
#define __BREEZYINPUT_H__

#include <iostream>
#include <OIS/OIS.h>				// OIS
#include <OGRE/Ogre.h>				// OGRE

#include "BreezyInputListener.h"	// Abstract input listener.

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	/** Class: Input - The input management object. **/
	class Input : public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener
	{
	public:
		Input();			// Constructor
		~Input();			// Destructor.

		OIS::InputManager * GetInputManager();			// Get the OIS::InputManager object.
		OIS::Keyboard * GetKeyboard();					// Get the OIS::Keyboard object.
		OIS::Mouse * GetMouse();						// Get the OIS::Mouse object.
		int GetMouseHeight();							// Get the width of the mouse area.
		int GetMouseWidth();							// Get the height of the mouse area.
		int GetMouseX();								// Get the X location of the mouse.
		int GetMouseY();								// Get the Y location of the mouse.
		int GetMouseZ();								// Get the Z location of the mouse. (wut?)
		Ogre::RenderWindow * GetWindow();				// Get the Ogre::RenderWindow object.
		bool IsKeyDown(OIS::KeyCode key);				// Return true if the key is down.
		bool IsKeyUp(OIS::KeyCode key);					// Return false if the key is down.
		bool IsMouseButtonDown(OIS::MouseButtonID id);	// Return true if the mouse button is down.
		bool IsMouseButtonUp(OIS::MouseButtonID id);	// return false if the mouse button is down.
		bool IsRunning();								// True if running;
		bool keyPressed(const OIS::KeyEvent &evt);		// CALLBACK.
		bool keyReleased(const OIS::KeyEvent &evt);		// CALLBACK.
		bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);	// CALLBACK.
		bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);	// CALLBACK.
		bool mouseMoved(const OIS::MouseEvent &evt);	// CALLBACK.
		bool PushInputListener(InputListener * listener);	// Add an input listener.
		bool RemoveInputListener(InputListener * listener);	// Remove an input listener.
		bool Start(Ogre::RenderWindow * win, bool exclusive = true);			// Start the object.
		bool Stop();									// Stop the object.
		void windowClosed(Ogre::RenderWindow * win);	// CALLBACK.
		void windowResized(Ogre::RenderWindow * win);	// CALLBACK.
		bool Update();									// Update the input.

	protected:
		bool _SetZero();					// Set all variables to zero.

	protected:
		bool running;							// Is the object running?
		OIS::InputManager * manager;					// The input manager object.
		OIS::Keyboard * keyboard;					// The keyboard object.
		OIS::Mouse * mouse;							// The mouse object.
		Ogre::RenderWindow * window;					// The current window we are getting input from.
		std::vector<InputListener*> listeners;	// Holds the list of listeners.
	};
};

#endif