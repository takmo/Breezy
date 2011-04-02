/*
	This file was based on the Gorilla Console Demo by Robin Southern.
	That demo was based on a code snippet by PixL.
	https://github.com/betajaen/gorilla
	http://www.ogre3d.org/tikiwiki/OgreConsole&structure=Cookbook
	http://www.ogre3d.org/forums/viewtopic.php?p=189903
*/
/*
File: BreezyConsole.cpp

Written by TechnoBulldog 2011, with snippets from Betajaen and PixL.

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

#ifndef __BREEZYCONSOLE_CPP__
#define __BREEZYCONSOLE_CPP__

#include "BreezyConsole.h"

static const char legalchars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+!\"'#%&/()=?[]\\*-_.:,;@$^~ ";

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	Console::Console()
	{
		_SetZero();
	}
	Console::~Console()
	{
	}

	bool Console::GetActive()
	{
		return active;
	}
	int Console::GetCurrentLines()
	{
		return currentlines;
	}
	Breezy::ConsoleListener * Console::GetListener()
	{
		return listener;
	}
	int Console::GetMaxCharacters()
	{
		return maxcharacters;
	}
	int Console::GetMaxLines()
	{
		return maxlines;
	}
	bool Console::GetRunning()
	{
		return running;
	}
	bool Console::GetVisible()
	{
		return visible;
	}
	void Console::RemoveListener()
	{
		listener = NULL;
	}
	void Console::SendText(Ogre::String text1)
	{
		Ogre::LogManager::getSingleton().logMessage("--BreezyConsole-- [ConsoleInput] " + text1);
		if(listener)
		{
			listener->TextEntered(text1);
		}
	}
	void Console::SetActive(bool activeyn)
	{
		if(visible) active = activeyn;
	}
	void Console::SetListener(Breezy::ConsoleListener * listener1)
	{
		listener = listener1;
	}
	void Console::SetVisible(bool vis)
	{
		visible = vis;
		layer->setVisible(visible);
		if(!visible) active = false;
	}
	bool Console::Start(Gorilla::Screen * screen1, Breezy::Input * input1, int fontsize, int lines, int characters)
	{
		screen = screen1;
		input = input1;
		maxlines = lines;
		maxcharacters = characters;

		layer = screen->createLayer(15);
		glyphdata = layer->_getGlyphData(fontsize);

		text = layer->createMarkupText(fontsize, 10, 10, Ogre::StringUtil::BLANK);
		text->width(screen->getWidth() - 10);
		background = layer->createRectangle(8, 8, screen->getWidth() - 16, glyphdata->mLineHeight + 5);
		background->background_gradient(Gorilla::Gradient_NorthSouth, Gorilla::rgb(128,128,128,128), Gorilla::rgb(64,64,64,128));
		background->border(2, Gorilla::rgb(128,128,128,128));

		input->PushInputListener(this);

		running = true;
		active = false;
		visible = true;
		
		Update();

		return true;
	}
	bool Console::Stop()
	{
		screen->destroy(layer);
		input->RemoveInputListener(this);
		return true;
	}
	void Console::Update()
	{
		currentlines = lines.size();
		Ogre::String out = "";
		background->height(lines.size() * glyphdata->mLineHeight + 5 + glyphdata->mLineHeight);
		while((signed int)lines.size() > maxlines) lines.pop_front();
		std::list<Ogre::String>::iterator it = lines.begin();
		for(int i = 0; i < (signed int)lines.size(); i++)
		{
			out += *it;
			out += "\n";
			it++;
		}
		out += "> ";
		out += currentline;
		out += "_";
		
		text->text(out);
	}
	void Console::WriteLine(Ogre::String text1)
	{
		Ogre::LogManager::getSingleton().logMessage("--BreezyConsole-- [ConsoleOutput] " + text1);
		lines.push_back(text1);
		Update();
	}

	bool Console::_SetZero()
	{
		listener = NULL;
		input = NULL;
		running = false;
		visible = false;
		active = false;
		maxlines = 0;
		currentlines = 0;
		maxcharacters = 0;
		currentline = "";
		screen = NULL;
		layer = NULL;
		text = NULL;
		background = NULL;
		glyphdata = NULL;
		return true;
	}

	void Console::KeyPressed(const OIS::KeyEvent &evt)
	{
		if(active)
		{
			if(evt.key == OIS::KC_BACK)
			{
				if(input->IsKeyDown(OIS::KC_LCONTROL) || input->IsKeyDown(OIS::KC_RCONTROL))
				{
					currentline = "";
					Update();
					return;
				}
				if(currentline.length() > 0)
				{
					currentline.erase(currentline.end() - 1);
					Update();
					return;
				}
			}
			if(evt.key == OIS::KC_RETURN || evt.key == OIS::KC_NUMPADENTER)
			{
				if(currentline.length() > 0)
				{
					SendText(currentline);
					currentline = Ogre::StringUtil::BLANK;
					Update();
					return;
				}
				return;
			}
			else
			{
				if((signed int)currentline.length() < maxcharacters)
				{
					for(int c=0;c<sizeof(legalchars);c++){
						if(legalchars[c] == evt.text){
							currentline += evt.text;
							break;
						}
					}
				}
				Update();
				return;
			}
		}
	}
	void Console::KeyReleased(const OIS::KeyEvent &evt){}
	void Console::MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id){}
	void Console::MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id){}
	void Console::MouseMoved(const OIS::MouseEvent &evt){}
	void Console::WindowClosed(Ogre::RenderWindow * window){}
	void Console::WindowResized(Ogre::RenderWindow * window)
	{
		text->width(screen->getWidth() - 10);
		background->width(screen->getWidth() - 16);
	}
};

#endif