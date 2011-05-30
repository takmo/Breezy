/*
File: BreezyInput.cpp

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

#ifndef __BREEZYINPUT_CPP__
#define __BREEZYINPUT_CPP__

#include "BreezyInput.h"

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	Input::Input()
	{
		_SetZero();
	}
	Input::~Input()
	{
		Stop();
	}
	OIS::InputManager * Input::GetInputManager()
	{
		return manager;
	}
	OIS::Keyboard * Input::GetKeyboard()
	{
		return keyboard;
	}
	OIS::Mouse * Input::GetMouse()
	{
		return mouse;
	}
	int Input::GetMouseHeight()
	{
		return mouse->getMouseState().height;
	}
	int Input::GetMouseWidth()
	{
		return mouse->getMouseState().width;
	}
	int Input::GetMouseX()
	{
		return mouse->getMouseState().X.abs;
	}
	int Input::GetMouseY()
	{
		return mouse->getMouseState().Y.abs;
	}
	int Input::GetMouseZ()
	{
		return mouse->getMouseState().Z.abs;
	}
	Ogre::RenderWindow * Input::GetWindow()
	{
		return window;
	}
	bool Input::IsKeyDown(OIS::KeyCode key)
	{
		if(keyboard->isKeyDown(key)) return true;
		return false;
	}
	bool Input::IsKeyUp(OIS::KeyCode key)
	{
		if(!keyboard->isKeyDown(key)) return true;
		return false;
	}
	bool Input::IsMouseButtonDown(OIS::MouseButtonID id)
	{
		if(mouse->getMouseState().buttonDown(id)) return true;
		return false;
	}
	bool Input::IsMouseButtonUp(OIS::MouseButtonID id)
	{
		if(!mouse->getMouseState().buttonDown(id)) return true;
		return false;
	}
	bool Input::IsRunning()
	{
		return running;
	}
	bool Input::keyPressed(const OIS::KeyEvent &evt)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->KeyPressed(evt);
		}
		return true;
	}
	bool Input::keyReleased(const OIS::KeyEvent &evt)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->KeyReleased(evt);
		}
		return true;
	}
	bool Input::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->MousePressed(evt, id);
		}
		return true;
	}
	bool Input::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->MouseReleased(evt, id);
		}
		return true;
	}
	bool Input::mouseMoved(const OIS::MouseEvent &evt)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->MouseMoved(evt);
		}
		return true;
	}
	bool Input::PushInputListener(InputListener * listener)
	{
		listeners.push_back(listener);
		return true;
	}
	bool Input::RemoveInputListener(InputListener * listener)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			if(listeners[i] == listener)
			{
				listeners.erase(listeners.begin() + i);
				return true;
			}
		}
		return true;
	}
	bool Input::Start(Ogre::RenderWindow * win, bool exclusive)
	{
		window = win;
		OIS::ParamList pl;
		size_t windowHnd=0;
		std::ostringstream windowHndStr;
		window->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		if(!exclusive)
		{
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		}
		manager = OIS::InputManager::createInputSystem(pl);
		keyboard = static_cast<OIS::Keyboard*>(manager->createInputObject(OIS::OISKeyboard, true));
		mouse = static_cast<OIS::Mouse*>(manager->createInputObject(OIS::OISMouse, true));
		keyboard->setBuffered(true);
		mouse->setBuffered(true);
		keyboard->setEventCallback(this);
		mouse->setEventCallback(this);
		Ogre::WindowEventUtilities::addWindowEventListener(window, this);
		windowResized(window);
		running = true;
		return true;
	}
	bool Input::Stop()
	{
		if(running)
		{
			Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
			for(unsigned int i = 0; i < listeners.size();)
			{
				listeners.pop_back();
			}
			manager->destroyInputObject(mouse);
			manager->destroyInputObject(keyboard);
			mouse = 0;
			keyboard = 0;
			OIS::InputManager::destroyInputSystem(manager);
			manager = 0;
			running = false;
		}
		return true;
	}
	void Input::windowClosed(Ogre::RenderWindow * win)
	{
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->WindowClosed(win);
		}
		//Stop();
	}
	void Input::windowResized(Ogre::RenderWindow * win)
	{
		unsigned int width, height, depth;
		int left, top;
		win->getMetrics(width, height, depth, left, top);
		const OIS::MouseState &ms = mouse->getMouseState();
		ms.width = width;
		ms.height = height;
		for(unsigned int i = 0; i < listeners.size(); i++)
		{
			listeners[i]->WindowResized(win);
		}
	}
	bool Input::Update()
	{
		if(!mouse || !keyboard) return false;
		mouse->capture();
		keyboard->capture();
		Ogre::WindowEventUtilities::messagePump();
		return true;
	}
	bool Input::_SetZero()
	{
		running = 0;
		manager = 0;
		keyboard = 0;
		mouse = 0;
		window = 0;
		
		return true;
	}
};

#endif