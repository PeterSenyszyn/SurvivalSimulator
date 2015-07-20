#include <MusicPlayer.hpp>

MusicPlayer::MusicPlayer() :
    m_volume(100.f)
{
    //m_fileNames[Music::IntroMusic] = "Assets/intromusic.ogg";
}

void MusicPlayer::play(Music::ID music)
{
    std::string filename = m_fileNames[music];

    if (!m_music.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    m_music.setVolume(m_volume);
    m_music.setLoop(true);
    m_music.play();
}

void MusicPlayer::stop()
{
    m_music.stop();
}

void MusicPlayer::setVolume(float volume)
{
    m_volume = volume;
}

void MusicPlayer::setPaused(bool paused)
{
    if (paused)
        m_music.pause();

    else
        m_music.play();
}
