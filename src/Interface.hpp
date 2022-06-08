#ifndef INTERFACE_H
#define INTERFACE_H


#include <cmath>

// Base Interface for all components
class IComponent{

    public:

        // Pure Virtual: Need to be implemented in Inheriting classes
        virtual void render(shared_ptr<sf::RenderWindow> ref) = 0;
        virtual void SetPosition(float x, float y) = 0;

        // Releases Base Resources
        virtual ~IComponent(){};
};


class Sprite2DComponent : public IComponent{

    public:

        Sprite2DComponent(){}

        Sprite2DComponent(std::string filepath){
            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);

            m_sprite.setScale(0.2, 0.2);
        }

        virtual void SetPosition(float x, float y) override{
            m_sprite.setPosition(x, y);
        }

        virtual void render(shared_ptr<sf::RenderWindow> ref) override{
            ref->draw(m_sprite);
        }


        // Releases Derived Class Resources
        ~Sprite2DComponent(){}
        // i.e. 
        // IComponent* b = new Sprite2DComponent
        // delete b - makes virtual f. call to ~IComponent()
        // Since it's virtual -> Calls ~Sprite2DComponent() -> ~IComponent()

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

};


class mapCell : public Sprite2DComponent{

    public:

        mapCell(string filepath, bool isTgt, bool isWall, bool isStart, bool isExplored){

            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);

            m_sprite.setScale(0.2, 0.2);

            isTarget = isTgt;
            isWall = isWall;
            isStart = isStart;
            isExplored = isExplored;

			font.loadFromFile("../assets-static/Raleway-Regular.ttf");
        }

        void SetPosition(float x, float y) override{
            m_sprite.setPosition(x, y);
        }

        void render(shared_ptr<sf::RenderWindow> ref) override {
            ref->draw(m_sprite);
            ref->draw(scoreLabel);
        }

        void setTexture(string filepath){
            m_texture.loadFromFile(filepath);
            m_sprite.setTexture(m_texture);
            m_sprite.setScale(0.2, 0.2);
        }


        void resetAttributes(){
            this->isTarget = false;
            this->isWall = false;
            this->isExplored = false;
            this->isStart = false;
        }

        void setScore(int score, int idx){

            scoreLabel.setString(to_string(score));
            scoreLabel.setFont(this->font);
            scoreLabel.setCharacterSize(40);

			scoreLabel.setColor(sf::Color::Red);
			scoreLabel.setPosition(80 * (idx % 20) + 15, 80 * div(idx, 20).quot + 80 + 10);

        }

        const bool checkIsTarget(){return isTarget;}
        const bool checkIsWall(){return isWall;}
        const bool checkIsStart(){return isStart;}
        const bool checkIsExplored(){return isExplored;}
        void setIdx(int idx){cellIdx = idx;}

        void setTarget(){isTarget = true;}
        void setWall(){isWall = true;}
        void setStart(){isStart = true;}
        void setExplored(){isExplored = true;}


        ~mapCell(){}


    private:
    
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        sf::Text scoreLabel;
        sf::Font font;

        bool isTarget;
        bool isWall;
        bool isStart;
        bool isExplored;

        int cellIdx;

        int curEst;
        int curScore;


};




class Button: public Sprite2DComponent{

    public:

        Button(sf::Color colour, sf::Font font, string text, pair<int, int> pos);

        void setInactive();
        void setActive();

        string getString(){return button.getString();}

        void render(shared_ptr<sf::RenderWindow> ref){
            ref->draw(this->button);
        }

        sf::Text getButton(){return button;}

        ~Button(){}

    private:

        bool isActive;
        bool isInactive;

        sf::Text button;

};


Button::Button(sf::Color colour, sf::Font font, string text, pair<int, int> pos){
    
    this->button = sf::Text(text, font, 45);
    this->button.setColor(colour);
    this->button.setPosition(sf::Vector2f(pos.first, pos.second));

    isActive = true;
    isInactive = false;

}

void Button::setActive(){}
void Button::setInactive(){}


#endif