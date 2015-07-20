#pragma once

#include <SFML/Audio.hpp>

namespace SE
{
	class Sound
	{
	public:
		Sound(const std::string& filepath);

        const void setPlay(bool play) { m_play = play; }
        const bool getPlay() const { return m_play; }

		sf::Sound& getSound() { return m_sound; }

	private:
		sf::SoundBuffer m_buffer;
		sf::Sound m_sound;

		bool m_play;
	};

	class Music
	{
    public:
        Music(const std::string& filepath, bool loop) :
        m_play(false)
        {
            m_music.openFromFile(filepath);
            m_music.setLoop(loop);
        }

        const void setPlay(bool play) { m_play = play; }
        const bool getPlay() const { return m_play; }

        sf::Music& getMusic() { return m_music; }

    private:
        sf::Music m_music;

        bool m_play;
	};
}
