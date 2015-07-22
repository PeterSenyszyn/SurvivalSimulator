#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <State.hpp>

class SettingsState : public State
{
public:
    SettingsState(StateStack& stack, Context context);

    virtual void initGui();

    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);
    virtual void draw();

private:
    void updateSettings();

    sf::Vector2u parseResolution(std::string str)
    {
        std::stringstream ss;

        std::replace(str.begin(), str.end(), 'x', ' ');

        ss << str;

        sf::Vector2u res;

        ss >> res.x >> res.y;

        return res;
    }

    float parseFps(std::string str)
    {
        auto replace = [](std::string& str, const std::string& from, const std::string& to)
        {
            size_t start_pos = str.find(from);

            if (start_pos == std::string::npos)
                return false;

            str.replace(start_pos, from.length(), to);

            return true;
        };

        std::stringstream ss;

        replace(str, "FPS", " ");

        ss << str;

        float fps;

        ss >> fps;

        return fps;
    }

private:
    sfg::ComboBox::Ptr m_resolutionComboBox;
    sfg::ComboBox::Ptr m_maxRefreshRate;

    sfg::Button::Ptr m_saveButton;
};

#endif // SETTINGSSTATE_H
