#include "Application.h"
#include"GameStateManager/GameStateBase.h"

void Application::Run()
{
    Init();
    sf::Clock clock;
    float deltaTime = 0.f;
    while (m_window->isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window->close();
        }

        /*animation.Update(deltaTime);*/
        Update(deltaTime);
        Render();
    }
}

Application::~Application()
{
    if (m_window != nullptr) {
        delete m_window;
    }

}

void Application::Init()
{
    m_window = new sf::RenderWindow(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), TITLE);
    m_window->setFramerateLimit(60);
    m_window->setVerticalSyncEnabled(false);
    /*m_sprite.setTexture(*ResourceManager::GetInstance()->getTexture("Meow-Knight_Take_Damage"));
    m_sprite.setScale(5, 5);*/
    GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_INTRO);
    WConnect->setWindow(m_window);
}

void Application::Update(float deltaTime)
{
    if (GameStateMachine::GetInstance()->NeedToChangeState()) {
        GameStateMachine::GetInstance()->PerformStateChange();
    }
    GameStateMachine::GetInstance()->currentState()->Update(deltaTime);

    //Change state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_MENU);
    }

}

void Application::Render()
{
    m_window->clear(sf::Color::White);
    // Drawing
   /* window.draw(animation);*/
    GameStateMachine::GetInstance()->currentState()->Render(m_window);
    m_window->display();
}

sf::RenderWindow* Application::getWindow()
{
    return m_window;
}
