/*
File: BreezySample.cpp

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

#ifndef __BREEZYSAMPLE_CPP__
#define __BREEZYSAMPLE_CPP__

#include "BreezySample.h"

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	Sample::Sample()
	{
		_SetZero();
	}
	Sample::~Sample()
	{

	}
	void Sample::KeyPressed(const OIS::KeyEvent &evt)
	{

	}
	void Sample::KeyReleased(const OIS::KeyEvent &evt)
	{

	}
	void Sample::MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{

	}
	void Sample::MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{

	}
	void Sample::MouseMoved(const OIS::MouseEvent &evt)
	{

	}
	bool Sample::Start()
	{
		if(!_StartOgre("Breezy Sample Window")) return false; // GO OGRE.
		input = new Breezy::Input(); input->Start(window); // Go input.

		cont = true;
		while(cont)
		{
			root->_fireFrameStarted();

			input->Update(); // Update input.
			if(input->IsKeyDown(OIS::KC_ESCAPE)) cont = false;

			root->_fireFrameRenderingQueued();

			root->renderOneFrame();

			root->_fireFrameEnded();
		}

		input->Stop();
		delete input;

		_StopOgre();
		return true;
	}
	bool Sample::Stop()
	{
		std::cout << "Empty function is empty =P\n";
		return true;
	}
	void Sample::WindowClosed(Ogre::RenderWindow * win)
	{
		cont = false;
	}
	void Sample::WindowResized(Ogre::RenderWindow * win)
	{

	}
	bool Sample::_SetZero()
	{
		cont = 0;
		input = 0;
		camera = 0;
		window = 0;
		root = 0;
		sm = 0;
		viewport = 0;
		return true;
	}
	bool Sample::_StartOgre(Ogre::String title)
	{
		try
		{
#ifdef _DEBUG
			root = OGRE_NEW Ogre::Root("plugins_d.cfg");
#else
			root = OGRE_NEW Ogre::Root();
#endif

			// Resources - I get the gist of what it's doing, but it's still confusing.
			Ogre::ConfigFile cf;
			cf.load("resources.cfg");
			Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
			Ogre::String secName, typeName, archName;
			while(seci.hasMoreElements())
			{
				secName = seci.peekNextKey();
				Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
				Ogre::ConfigFile::SettingsMultiMap::iterator i;
				for(i = settings->begin(); i != settings->end(); ++i)
				{
					typeName = i->first; archName = i->second;
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
				}
			}
				
			// Load.
			if(root->restoreConfig())
			{
				window = root->initialise(true, title);
			}
			else
			{
				if(root->showConfigDialog())
				{
					window = root->initialise(true, title);
				}
				else
				{
					OGRE_DELETE root; return false;
				}
			}

			Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

			// Configure default render.
			sm = root->createSceneManager("OctreeSceneManager", "SceneManager0");
			camera = sm->createCamera("Camera0");
			viewport = window->addViewport(camera);
			viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

			return true;
		}
		catch(Ogre::Exception &e)
		{
			MessageBoxA(NULL, e.getFullDescription().c_str(), "Ogre Exception", MB_OK);
			if(root) OGRE_DELETE root;
			root = 0;
			return false;
		}
	}
	bool Sample::_StopOgre()
	{
		if(root) OGRE_DELETE root;
		root = 0;
		return true;
	}
};

#endif