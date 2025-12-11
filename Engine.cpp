#include "Engine.h"
#include "Particle.h"

Engine::Engine()
{
	m_Window.create(VideoMode(1920, 1080), "Particles");
}

void Engine::run()
{
	sf::Clock clock;
	Time time;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		time = clock.restart();
		float dt = time.asSeconds();

		input();
		update(dt);
		draw();
		//cout << "DRAW" << endl;
	}
}

void Engine::input()
{
	Event event;

	while (m_Window.pollEvent(event)) 
	{

		if (event.type == Event::Closed) 
		{
			m_Window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		{
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed) 
		{
			if (event.mouseButton.button == Mouse::Button::Left) 
			{
				for (int i = 0; i < 5; i++)
				{
					int temp = rand() % (50 - 25 + 1) + 25;
					Particle part(m_Window, temp, Vector2i(event.mouseButton.x, event.mouseButton.y));            //Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition);
					m_particles.push_back(part);

				}
			}
		
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (int i = 0; i < m_particles.size(); i = i)
	{
		if (m_particles.at(i).getTTL() <= 0)
		{
			m_particles.erase(m_particles.begin()+i);

		}
		else //if not dead
		{
			m_particles.at(i).update(dtAsSeconds);
			i++;
		}

	}
}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));	
	}
	m_Window.display();
}