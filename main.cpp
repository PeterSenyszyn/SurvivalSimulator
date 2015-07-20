#include <iostream>
#include <stdexcept>

#include <Application.hpp>

///Created by Peter Senyszyn
///Version 1.0 finished 11/5/14

int main()
{
    try
    {
        sf::Clock deltaClock;

        sf::Time lastUpdate = sf::Time::Zero;

        //144 fps max
        sf::Time timePerFrame = sf::seconds(1.f / 144.f);

        Application app;

        while (app.running())
        {
            lastUpdate += deltaClock.restart();

            while (lastUpdate > timePerFrame)
            {
                lastUpdate -= timePerFrame;

                app.processInput();
                app.update(timePerFrame);
                app.render();
            }
        }
    }

    catch (std::exception& e)
    {
        std::cout << "Exception when running application: " << e.what() << std::endl;
    }
}
