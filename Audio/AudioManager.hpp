#pragma once

#include <map>
#include <iostream>
#include <memory>

#include "Sound.hpp"

namespace SE
{
	//Use this manager to create sounds and music using factory functions
	//Do not attempt to construct local objects and pass it to the maps
	class AudioManager
	{
	public:
		void createSound(const std::string& filepath, const std::string& id);
		void createMusic(const std::string& filepath, bool loop, const std::string& id);

		void deleteSound(const std::string& id)
		{
			auto iter = m_sounds.find(id); if (iter != m_sounds.end()) m_sounds.erase(iter);
		}

		void deleteMusic(const std::string& id)
		{
			auto iter = m_music.find(id); if (iter != m_music.end()) m_music.erase(iter);
		}

		std::unique_ptr<Sound>& getSound(const std::string& id);
		std::unique_ptr<Music>& getMusic(const std::string& id);

        void update(sf::Time dt);

	private:
		//Map for the sounds
		std::map<std::string, std::unique_ptr<Sound> > m_sounds;

		//Map for (larger) audio files
		std::map<std::string, std::unique_ptr<Music> > m_music;
	};
}
