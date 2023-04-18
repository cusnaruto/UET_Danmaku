#include "GameObject.hpp"
#include "TextureManager.hpp"
GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(textureSheet);
    xPos = x;
    yPos = y;
}

void GameObject::Update()
{
   
    srcRect.h = 200;
    srcRect.w = 200;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}