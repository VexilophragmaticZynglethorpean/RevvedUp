#include "Core/WindowManager.h"
#include "Util/Path.h"

namespace {
const sf::String TITLE = "Race";
const std::string ICON_PATH = Util::getExecutablePath() / "assets/icon.png";
bool isFullScreen = false;
}

sf::RenderWindow&
WindowManager::getWindow()
{
    static sf::RenderWindow window(sf::VideoMode::getDesktopMode(), TITLE);

    sf::Image icon;
    icon.loadFromFile(ICON_PATH);

    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    return window;
}

void
WindowManager::toggleFullScreen(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return;
    if (event.key.code != sf::Keyboard::F11)
        return;

    isFullScreen = !isFullScreen;

    sf::RenderWindow& window = getWindow();
    if (isFullScreen) {
        window.close();
        window.create(
          sf::VideoMode::getFullscreenModes()[0], TITLE, sf::Style::Fullscreen);
    } else {
        window.close();
        window.create(sf::VideoMode::getDesktopMode(), TITLE);
    }
}

void
WindowManager::resizeWindow(const sf::Event& event)
{
    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
    WindowManager::getWindow().setView(sf::View(visibleArea));
}
