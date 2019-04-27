#include "Menu.h"

namespace sis
{
	Menu::Menu(sf::RenderWindow *window, AssetManager *assets) :
		current_choice_(0),
		menuTextsSize_(sizeof(menuTexts_) / sizeof(*menuTexts_)),
		delayTime_(0.2),
		choice_selected_(false)
	{
		menuTexts_[0] = "New Game";
		menuTexts_[1] = "Settings";
		menuTexts_[2] = "Scoreboard";
		menuTexts_[3] = "Exit";

		this->window_ = window;
		this->assets_ = assets;
		backgroundSprite_.setTexture(assets_->getTexture(MENU_BACKGROUND));
		text_.setFont(assets_->getFont(MENU_FONT));
		text_.setCharacterSize(60);
	}

	Menu::~Menu()
	{
	}

	void Menu::handleInput()
	{
		if (clock_.getElapsedTime().asSeconds() < delayTime_)
			return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if(current_choice_ > 0)
				--current_choice_;
			clock_.restart();
			return;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if(current_choice_ < menuTextsSize_ - 1)
				++current_choice_;
			clock_.restart();
			return;
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			choice_selected_ = true;
	}

	void Menu::draw()
	{
		window_->clear();
		window_->draw(backgroundSprite_);

		for (int i = 0; i < menuTextsSize_; ++i)
		{
			text_.setString(menuTexts_[i]);
			text_.setPosition(sf::Vector2f(WINDOW_WIDTH / 7, i * WINDOW_HEIGHT / 8));
			if (current_choice_ == i)
				text_.setFillColor(sf::Color::Yellow);
			else
				text_.setFillColor(sf::Color::White);
			window_->draw(text_);
		}

		window_->display();
	}

	int Menu::processMenu()
	{
		while (!choice_selected_)
		{
			handleInput();
			draw();
		}
		return current_choice_;
	}
}