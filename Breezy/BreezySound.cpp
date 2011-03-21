/*
File: BreezySound.cpp

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

#ifndef __BREEZYSOUND_CPP__
#define __BREEZYSOUND_CPP__

#include "BreezySound.h"

/** Namespace: Breezy - The entire framework. **/
namespace Breezy
{
	Sound::Sound()
	{
		_SetZero();
	}
	Sound::~Sound()
	{
		if(source)
			alDeleteSources(1, &source);alGetError();
		source = 0;
		hasaudio = false;
	}
	bool Sound::HasAudio()
	{
		return hasaudio;
	}
	bool Sound::PauseSound()
	{
		if(source)
		{
			ALint state = NULL;
			alGetSourcei(source, AL_SOURCE_STATE, &state);alGetError();
			if(state == AL_PLAYING)
			{
				alSourcePause(source);alGetError();
				return true;
			}
			else
			{
				Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could not pause sound. Not currently playing.");
				return false;
			}
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could not pause sound, invalid source. Did you successfully add a sound?");
			return false;
		}
	}
	bool Sound::PlaySound()
	{
		if(source)
		{
			ALint state = NULL;
			alGetSourcei(source, AL_SOURCE_STATE, &state);alGetError();
			if(state != AL_PLAYING)
			{
				alSourcePlay(source);alGetError();
				return true;
			}
			else
			{
				Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could not play sound. Sound already playing.");
				return false;
			}
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could not play sound, invalid source. Did you successfully add a sound?");
			return false;
		}
	}
	bool Sound::RemoveSound()
	{
		if(source)
		{
			alDeleteSources(1, &source);alGetError();
			return true;
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Cannot remove sound. Invalid source. Did you successfully add a sound?");
			return false;
		}
	}
	bool Sound::SetLocation(Ogre::Vector3 loc) // EXTREMELY EXPERIMENTAL I WOULDN'T EVEN BRUSH MY TEETH WITH IT!
	{
		if(source)
		{
			alSource3f(source, AL_POSITION, loc.x, loc.y, loc.z);alGetError(); // WARNING MAY TASTE LIKE BUGS!
			return true;
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Cannot set sound location. Invalid source. Did you successfully add a sound?");
			return false;
		}
	}
	bool Sound::SetSound(Ogre::String filename) // DOES NOT WORK!
	{
		ALuint buffer;
		ALenum format;
		alGenBuffers(1, &buffer);alGetError();
		alGenSources(1, &source);alGetError();

		// Begin that there Ogg stuff.
		long ldata; char cbuffer[4096]; std::string data = "";
		OggVorbis_File ogg;
		FILE * track = 0;
		fopen_s(&track, filename.c_str(), "rb");
		long rate;
		if(track)
		{
			ov_open(track, &ogg, NULL, 0);
			vorbis_info * info = ov_info(&ogg, -1);
			if(info->channels == 2) format = AL_FORMAT_STEREO16;
			else format = AL_FORMAT_MONO16;
			rate = info->rate; 
			do{ldata = ov_read(&ogg, cbuffer, 4096, 0, 2, 1, NULL); data.insert(data.end(), cbuffer, cbuffer + ldata);}while(ldata > 0);
			ov_clear(&ogg);
			alBufferData(buffer, format, data.data(), static_cast<ALsizei>(data.size()), rate);alGetError();
			fclose(track);
			alSourcei(source, AL_BUFFER, buffer);alGetError();
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could not OGG file for reading.");
			return false;
		}
		// End that there Ogg stuff.

		return true;
	}
	bool Sound::StopSound()
	{
		if(source)
		{
			ALint state = NULL;
			alGetSourcei(source, AL_SOURCE_STATE, &state);alGetError();
			if(state != AL_STOPPED)
			{
				alSourceStop(source);alGetError();
				return true;
			}
			else
			{
				Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could stop sound. Sound already stopped.");
				return false;
			}
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("--BreezySound-- Could not stop sound, invalid source. Did you successfully add a sound?");
			return false;
		}
	}
	bool Sound::_SetZero()
	{
		hasaudio = false;
		source = NULL;
		return true;
	}
};

#endif