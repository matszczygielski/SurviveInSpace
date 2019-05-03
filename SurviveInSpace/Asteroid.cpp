#include "Asteroid.h"

namespace sis
{
	Asteroid::Asteroid(sf::RenderWindow *window, AssetManager *assets):
		animation_counter_(0)
	{
		this->window_ = window;
		this->assets_ = assets;
		
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> intDistWidth(1, WINDOW_WIDTH);
		std::uniform_real_distribution<float> floatDist0_1(0, 1);

		pose_.rotation = 360 * floatDist0_1(rng);
		speed_ = 120 + 50 * floatDist0_1(rng);
		animation_speed_ = speed_ / 300;

		if (intDistWidth(rng) % 2 == 0)
		{
			sprite_.setTexture(assets_->getTexture(ASTEROID));
			sprite_.setRotation(pose_.rotation - 135);
		}
		else
		{
			sprite_.setTexture(assets_->getTexture(ASTEROID_SMALL));
			sprite_.setRotation(pose_.rotation + 135);
		}

		pose_.x = intDistWidth(rng);
		pose_.y = 0;
		sprite_.setPosition(sf::Vector2f(pose_.x, pose_.y));
		

		dx_ = cos(pose_.rotation * PI / 180);
		dy_ = -sin(pose_.rotation * PI / 180);
	}

	void Asteroid::update(float dt)
	{
		this->move(dt);
		this->animate();
	}

	void Asteroid::move(float dt)
	{
		float dx = dx_ * speed_ * dt;
		float dy = dy_ * speed_ * dt;
		pose_.x += dx;
		pose_.y += dy;
		sprite_.move(sf::Vector2f(dx, dy));

		if (pose_.x > WINDOW_WIDTH + 30)
		{
			sprite_.setPosition(sf::Vector2f(0, pose_.y));
			pose_.x = -30;
		}
		if (pose_.x < -30)
		{
			sprite_.setPosition(sf::Vector2f(WINDOW_WIDTH, pose_.y));
			pose_.x = WINDOW_WIDTH + 30;
		}
		if (pose_.y < -30)
		{
			sprite_.setPosition(sf::Vector2f(pose_.x, WINDOW_HEIGHT));
			pose_.y = WINDOW_HEIGHT + 30;
		}
		if (pose_.y > WINDOW_HEIGHT + 30)
		{
			sprite_.setPosition(sf::Vector2f(pose_.x, 0));
			pose_.y = -30;
		}
	}

	void Asteroid::draw()
	{
		this->window_->draw(sprite_);
	}

	void Asteroid::animate()
	{
		if (animation_counter_ >= 15)
			animation_counter_ = 0;
		else
			animation_counter_ += animation_speed_;
		sprite_.setTextureRect(sf::IntRect(64 * int(animation_counter_), 0, 64, 64));
	}
}