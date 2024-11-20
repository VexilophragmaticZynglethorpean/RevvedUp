#include "Core/Global.h"
#include "Util/Path.h"

sf::RenderWindow&
Global::getWindow()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Attribute::Debug;

    static sf::RenderWindow window(sf::VideoMode(800, 600),
                                   "RevvedUp",
                                   sf::Style::Titlebar | sf::Style::Resize |
                                     sf::Style::Close,
                                   settings);

    sf::Image icon;
    icon.loadFromFile(Util::getExecutablePath() / "assets/icon.png");

    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    return window;
}

sf::Clock&
Global::getClock()
{
    static sf::Clock clock;
    return clock;
}
