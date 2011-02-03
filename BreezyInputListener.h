/*
File: BreezyInputListener.h

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

#ifndef __BREEZYINPUTLISTENER_H__
#define __BREEZYINPUTLISTENER_H__

#include <OIS/OIS.h>								// OIS
#include <OGRE/Ogre.h>								// OGRE

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	/** Class: Listener - The input callback object. **/
	class InputListener
	{
	public:
		virtual void KeyPressed(const OIS::KeyEvent &evt) = 0;
		virtual void KeyReleased(const OIS::KeyEvent &evt) = 0;
		virtual void MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
		virtual void MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
		virtual void MouseMoved(const OIS::MouseEvent &evt) = 0;
		virtual void WindowClosed(Ogre::RenderWindow * window) = 0;
		virtual void WindowResized(Ogre::RenderWindow * window) = 0;
	};
};

#endif