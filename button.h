#pragma once
#include "Header.h"
using namespace sf;
class Button
{
    bool clicked;
    Vector2f position;
    Vector2f size;
    Vector2f normal;
    Vector2i TextureSize;
    Vector2i TextureStart; RenderWindow* window;
    Color ButtonColor;
    Color BorderColor;
    bool BorderSet = false, ButtonTextureEnabled = false, BorderTextureEnabled, in = true;
    float BorderSize = 0;
    Texture ButtonTexture;

    Mouse::Button MouseClickButton;
public:
    Sprite ButtonSprite;
    Button(Vector2f pos, Vector2f sizes, RenderWindow* wind);

    void setButtonColor(Color col);

    void setButtonTexture(String name, Vector2i place, Vector2i siz);
    void setBorder(int sizew);

    void setBorderColor(Color col);

    void setMouseClickButton(Mouse::Button click);

    Vector2f getPos();

    Vector2f getSize();

    bool draw();
};

