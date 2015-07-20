#include <SoundPlayer.hpp>

#include <SFML/Audio/Listener.hpp>

#include <cmath>

namespace
{
    // Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer()
{
    //m_soundBuffers.load(SoundEffect::ButtonHover, "Assets/buttonhover.wav");
    //m_soundBuffers.load(SoundEffect::ButtonClick, "Assets/buttonclick.wav");
}

void SoundPlayer::play(SoundEffect::ID effect)
{
    play(effect, getListenerPosition());
}

void SoundPlayer::play(SoundEffect::ID effect, sf::Vector2f position)
{
    sf::Sound sound;

    sound.setBuffer(m_soundBuffers.get(effect));
    sound.setPosition(position.x, -position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);

    sound.play();

    m_sounds.push_back(sound);
}

void SoundPlayer::removeStoppedSounds()
{
    m_sounds.remove_if([] (const sf::Sound& s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    sf::Vector3f position = sf::Listener::getPosition();

    return sf::Vector2f(position.x, -position.y);
}
