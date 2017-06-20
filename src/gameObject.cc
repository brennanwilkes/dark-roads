#include "gameObject.hpp"

GameObject::GameObject(float rad){
	sprite=sf::CircleShape(rad);
	r=rad;
}
