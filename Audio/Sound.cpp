#include "Sound.hpp"

namespace SE
{
	Sound::Sound(const std::string& filepath) :
    m_play(false)
	{
		m_buffer.loadFromFile(filepath);

		m_sound.setBuffer(m_buffer);
	}
}
