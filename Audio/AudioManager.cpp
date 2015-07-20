#include "AudioManager.hpp"

namespace SE
{
	void AudioManager::createSound(const std::string& filepath, const std::string& id)
	{
		auto temp = std::unique_ptr<Sound>(new Sound(filepath));

		m_sounds[id] = std::move(temp);
	}

	void AudioManager::createMusic(const std::string& filepath, bool loop, const std::string& id)
	{
		auto temp = std::unique_ptr<Music>(new Music(filepath, loop));

		m_music[id] = std::move(temp);
	}

	std::unique_ptr<Sound>& AudioManager::getSound(const std::string& id)
	{
		auto iter = m_sounds.find(id);

		if (iter != m_sounds.end()) return iter->second;
	}

	std::unique_ptr<Music>& AudioManager::getMusic(const std::string& id)
	{
		auto iter = m_music.find(id);

		if (iter != m_music.end()) return iter->second;
	}

	void AudioManager::update(sf::Time dt)
	{
	    for (const auto& iter : m_sounds)
        {
            if (iter.second->getPlay())
            {
                if (iter.second->getSound().getStatus() != sf::SoundSource::Playing)
                    iter.second->getSound().play();
            }

            else
            {
                if (iter.second->getSound().getStatus() == sf::SoundSource::Playing)
                    iter.second->getSound().stop();
            }
        }

        for (const auto& iter : m_music)
        {
            if (iter.second->getPlay())
            {
                if (iter.second->getMusic().getStatus() != sf::SoundSource::Playing)
                    iter.second->getMusic().play();
            }

            else
            {
                if (iter.second->getMusic().getStatus() == sf::SoundSource::Playing)
                    iter.second->getMusic().stop();
            }
        }
	}
}
