/*
	This file was based on the Gorilla Console Demo by Robin Southern.
	That demo was based on a code snippet by PixL.
	https://github.com/betajaen/gorilla
	http://www.ogre3d.org/tikiwiki/OgreConsole&structure=Cookbook
	http://www.ogre3d.org/forums/viewtopic.php?p=189903
*/
/*
File: BreezyConsole.h

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

#ifndef __BREEZYCONSOLE_H__
#define __BREEZYCONSOLE_H__

#include "BreezyInput.h"
#include "Gorilla.h"
#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	/** Class: ConsoleListener - A class for a ConsoleListener. **/
	class ConsoleListener
	{
	public:
		virtual void TextEntered(Ogre::String text) = 0;
	};

	/** Class: Console - A class for a simple Console **/
	class Console : public Breezy::InputListener
	{
	public:
		Console();	// Constructor.
		~Console();	// Destructor.

		bool GetActive();										// Get the active status.
		int GetCurrentLines();									// Get the current number of lines.
		Breezy::ConsoleListener * GetListener();				// Get the current ConsoleListener.
		int GetMaxCharacters();									// Get the max character count.
		int GetMaxLines();										// Get the max lines visible.
		bool GetRunning();										// Is the console running?
		bool GetVisible();										// Get the visible status.
		void RemoveListener();									// Remove the current ConsoleListener.
		void SendText(Ogre::String text1);						// Send text to be handled by the console.
		void SetActive(bool activeyn);							// Set the console active or inactive.
		void SetListener(Breezy::ConsoleListener * listener1);	// Set the current ConsoleListener.
		void SetVisible(bool vis);								// Set the console to visible or not.
		bool Start(Gorilla::Screen * screen1, Breezy::Input * input1, int fontsize, int lines, int characters); // Start, obviously. Pass the fontsize you'd like to use.
		bool Stop();											// Need I say more?
		void Update();											// Update the display.
		void WriteLine(Ogre::String text1);						// Write a line of text and start a new line.

		void KeyPressed(const OIS::KeyEvent &evt);
		void KeyReleased(const OIS::KeyEvent &evt);
		void MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
		void MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
		void MouseMoved(const OIS::MouseEvent &evt);
		void WindowClosed(Ogre::RenderWindow * window);
		void WindowResized(Ogre::RenderWindow * window);

	protected:
		bool _SetZero();	// Nullify everything.

	protected:
		Breezy::ConsoleListener * listener;			// The currecnt console listener.
		Breezy::Input * input;						// The input object.
		bool running;								// Is it running?
		bool visible;								// Is it visible?
		bool active;								// Is it active?
		int maxlines;								// Max lines.
		int currentlines;							// The current amount of lines.
		int maxcharacters;							// Max characters.
		std::list<Ogre::String> lines;				// The storage data for the lines.
		Ogre::String currentline;					// The current line.
		Gorilla::Screen * screen;					// The Gorilla screen that this is on.
		Gorilla::Layer * layer;						// The Gorilla Layer.
		Gorilla::MarkupText * text;					// The text.
		Gorilla::Rectangle * background;			// The background behind it.
		Gorilla::GlyphData * glyphdata;				// The data for the glyphs.
	};
};

#endif