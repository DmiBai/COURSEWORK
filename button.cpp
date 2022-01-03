#include "button.h"

    Button::Button(Vector2f pos, Vector2f sizes, RenderWindow* wind) {
        position = pos;
        size = sizes;
        window = wind;
    }

    void  Button::setButtonColor(Color col) {
        ButtonColor = col;
        ButtonTextureEnabled = false;
    }

    void  Button::setButtonTexture(String name, Vector2i place, Vector2i siz) {
        TextureSize = siz, TextureStart = place;
        if (!ButtonTexture.loadFromFile(name)) {};
        ButtonTexture.setRepeated(false);
        ButtonSprite.setTexture(ButtonTexture);
        ButtonTextureEnabled = true;
    }

    void  Button::setBorder(int sizew) {
        if (sizew % 2 != 0) { BorderSize = sizew + 1; }
        else BorderSize = sizew;
        BorderSet = true;
    }

    void  Button::setBorderColor(Color col) {
        BorderColor = col;
        BorderSet = true;
    }

    void  Button::setMouseClickButton(Mouse::Button click) {
        MouseClickButton = click;
    }

    Vector2f  Button::getPos() {
        return position;
    }

    Vector2f  Button::getSize() {
        return size;
    }

    bool  Button::draw() {
        if (in) normal = size;
        if (size.x > TextureSize.x || size.y > TextureSize.y) size.x = TextureSize.y; size.y = TextureSize.y;
        if (!BorderSet && !ButtonTextureEnabled) {
            RectangleShape Button(size);
            Button.setPosition(position);
            Button.setFillColor(ButtonColor);
            (*window).draw(Button);
        }
        if (!BorderSet && ButtonTextureEnabled) {
            ButtonSprite.setPosition(position);
            (*window).draw(ButtonSprite);
        }
        if (BorderSet && !ButtonTextureEnabled) {
            Vector2f BorderVecSize = { BorderSize, BorderSize };
            Vector2f BorderVecPos = { BorderSize / 2, BorderSize / 2 };

            RectangleShape Button(size - BorderVecSize);
            Button.setPosition(position + BorderVecPos);
            Button.setFillColor(ButtonColor);

            RectangleShape border(size);
            border.setPosition(position);
            border.setFillColor(BorderColor);

            (*window).draw(border);
            (*window).draw(Button);
        }
        if (BorderSet && ButtonTextureEnabled) {
            ButtonSprite.setTextureRect(IntRect(TextureStart.x, TextureStart.y, size.x - BorderSize, size.y - BorderSize));
            ButtonSprite.setPosition(position.x + BorderSize / 2, position.x + BorderSize / 2);

            RectangleShape border(normal);
            border.setPosition(position);
            border.setFillColor(BorderColor);


            RectangleShape mask(Vector2f(normal.x - BorderSize, normal.y - BorderSize));
            mask.setPosition(position.x + BorderSize / 2, position.x + BorderSize / 2);
            mask.setFillColor(Color::Black);
            in = false;

            (*window).draw(border);
            (*window).draw(mask);
            (*window).draw(ButtonSprite);
        }

        Vector2i MouseCoords = Mouse::getPosition(*window);
        Vector2u WinSize = (*window).getSize();
        if (MouseCoords.x <= WinSize.x && MouseCoords.y <= WinSize.y && MouseCoords.x >= position.x && MouseCoords.x <= position.x + normal.x && MouseCoords.y >= position.y && MouseCoords.y <= position.x + normal.y && Mouse::isButtonPressed(MouseClickButton)) {
            return true;
        }
        else return false;
    }
