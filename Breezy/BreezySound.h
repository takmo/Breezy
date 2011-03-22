/*
File: BreezySound.h

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

#ifndef __BREEZYSOUND_H__
#define __BREEZYSOUND_H__

#include <al.h>						// OpenAL
#include <alc.h>					// OpenAL Context
#include <OGRE/Ogre.h>				// OGRE
#include <vorbis/vorbisfile.h>		// Vorbisfile

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	/** Class: Sound - A class for managing an OpenAL sound. **/
	class Sound
	{
	public:
		Sound();			// Constructor
		~Sound();			// Destructor.

		int GetState();						// Returns the AL state of the source.
		bool HasAudio();					// True if audio is set for this object.
		bool PauseSound();					// Pause playing the sound.
		bool PlaySound();					// Play the sound.
		bool RemoveSound();					// Remove the sound.
		bool SetLocation(Ogre::Vector3 loc);// Set the location of the sound.
		bool SetSound(Ogre::String file);	// Set the sound.
		bool StopSound();					// Stop playing the sound.

	protected:
		bool _SetZero();					// Set all variables to zero.

	protected:
		bool hasaudio;				// Is the object running?
		ALuint source;				// The audio source.
	};
};

#endif