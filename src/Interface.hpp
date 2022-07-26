#ifndef INTERFACE_H
#define INTERFACE_H


#include <cmath>

#include <iostream>

using std::shared_ptr, std::string, std::cout, std::endl, std::pair, std::to_string;


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

        virtual void render(std::shared_ptr<sf::RenderWindow> ref) override{
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

			this->font.loadFromFile("../assets-static/Raleway-Regular.ttf");
        }

        void SetPosition(float x, float y) override{
            m_sprite.setPosition(x, y);
        }

        void render(shared_ptr<sf::RenderWindow> ref) override {

            ref->draw(m_sprite);
            ref->draw(scoreLabel);
            ref->draw(scoreLabelNextRight);
            ref->draw(scoreLabelNext45Up);
            ref->draw(scoreLabelNextUp);
            ref->draw(scoreLabelPrev45Up);
            ref->draw(scoreLabelPrevLeft);
            ref->draw(scoreLabelPrev45Down);
            ref->draw(scoreLabelNextDown);
            ref->draw(scoreLabelNext45Down);

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

            if(score == -1){
                scoreLabel.setString("");
                return;
            }
    
            scoreLabel.setString(to_string(score));
            scoreLabel.setFont(this->font);
            scoreLabel.setCharacterSize(35);

			scoreLabel.setFillColor(sf::Color::Red);
			scoreLabel.setPosition(80 * (idx % 20) + 25, 80 * div(idx, 20).quot + 80 + 12);

        }


        void resetScore8Way(){

            scoreLabelNextRight.setString("");
            scoreLabelNext45Down.setString("");
            scoreLabelNextDown.setString("");
            scoreLabelPrev45Down.setString("");
            scoreLabelPrevLeft.setString("");
            scoreLabelPrev45Up.setString("");
            scoreLabelNextUp.setString("");
            scoreLabelNext45Up.setString("");

        }

        // Set the cell scores based on cell location
        void setScore8Way(int scoreRight, int scoreNext45Up, int scoreNextUp, int scorePrev45Up, int scorePrevLeft, int scorePrev45Down, int scoreNextDown, int scoreNext45Down){

            int cellIdx = this->cellIdx;
            int indexIncrements = 20;

            bool isTopLeft = cellIdx % indexIncrements == 0 && (cellIdx == 0);
            bool isTopEdge = (cellIdx > 0) && (cellIdx < (indexIncrements - 1));
            bool isTopRight = (cellIdx % indexIncrements == (indexIncrements - 1)) && (cellIdx == ((indexIncrements - 1)));
            bool isLeftEdge = (cellIdx % indexIncrements == 0) && ((cellIdx + indexIncrements) < 340);
            bool isRightEdge = (cellIdx % indexIncrements == (indexIncrements - 1)) && ((cellIdx + indexIncrements) < 340);
            bool isBottomLeft = (cellIdx % indexIncrements == 0) && ((cellIdx + indexIncrements) > 340);
            bool isBottomEdge = (cellIdx > (340 - (indexIncrements + 1))) && (cellIdx < (340 - 1));
            bool isBottomRight = (cellIdx % indexIncrements == (indexIncrements - 1)) && (cellIdx + 1 >= 340);
            bool isMiddle = {!(isTopLeft || isTopEdge || isTopRight || isLeftEdge 
                            || isRightEdge || isBottomLeft || isBottomEdge || isBottomRight)};

            cout<<isTopLeft<<endl;
            cout<<isTopEdge<<endl;
            cout<<isTopRight<<endl;
            cout<<isLeftEdge<<endl;
            cout<<isRightEdge<<endl;
            cout<<isBottomLeft<<endl;
            cout<<isBottomEdge<<endl;
            cout<<isBottomRight<<endl;
            cout<<isMiddle<<endl;


            // Ex. Set scores in appropriate location depending on cell location
            // if(isTopLeft){
                
            //     scoreLabelNextRight.setString(to_string(scoreRight));
            //     scoreLabelNext45Down.setString(to_string(scoreNext45Down));
            //     scoreLabelNextDown.setString(to_string(scoreNextDown));

            //     scoreLabelNextRight.setFont(this->font);
            //     scoreLabelNext45Down.setFont(this->font);
            //     scoreLabelNextDown.setFont(this->font);

            //     scoreLabelNextRight.setCharacterSize(25);
            //     scoreLabelNext45Down.setCharacterSize(25);
            //     scoreLabelNextDown.setCharacterSize(25);

            //     scoreLabelNextRight.setColor(sf::Color::Red);
            //     scoreLabelNext45Down.setColor(sf::Color::Red);
            //     scoreLabelNextDown.setColor(sf::Color::Red);

            //     scoreLabelNextRight.setPosition(80 * (cellIdx % 20) + 70, 80 * div(cellIdx, 20).quot + 80 + 25);
            //     scoreLabelNext45Down.setPosition(80 * (cellIdx % 20) + 70, 80 * div(cellIdx, 20).quot + 80 + 50);
            //     scoreLabelNextDown.setPosition(80 * (cellIdx % 20) + 27, 80 * div(cellIdx, 20).quot + 80 + 60);

            // }

            // if(isMiddle){

            //     scoreLabelNextRight.setString(to_string(scoreRight));
            //     scoreLabelNextRight.setFont(this->font);
            //     scoreLabelNextRight.setCharacterSize(25);
            //     scoreLabelNextRight.setColor(sf::Color::Red);
            //     scoreLabelNextRight.setPosition(80 * (cellIdx % 20) + 50, 80 * div(cellIdx, 20).quot + 80 + 25);

            //     scoreLabelNext45Down.setString(to_string(scoreNext45Down));
            //     scoreLabelNextDown.setString(to_string(scoreNextDown));
            //     scoreLabelPrev45Down.setString(to_string(scorePrev45Down));
            //     scoreLabelPrevLeft.setString(to_string(scorePrevLeft));

            //     scoreLabelNext45Down.setFont(this->font);
            //     scoreLabelNextDown.setFont(this->font);
            //     scoreLabelPrev45Down.setFont(this->font);
            //     scoreLabelPrevLeft.setFont(this->font);

            //     scoreLabelNext45Down.setCharacterSize(25);
            //     scoreLabelNextDown.setCharacterSize(25);
            //     scoreLabelPrev45Down.setCharacterSize(25);
            //     scoreLabelPrevLeft.setCharacterSize(25);
                

            //     scoreLabelNext45Down.setColor(sf::Color::Red);
            //     scoreLabelNextDown.setColor(sf::Color::Red);
            //     scoreLabelPrev45Down.setColor(sf::Color::Red);
            //     scoreLabelPrevLeft.setColor(sf::Color::Red);


            //     scoreLabelNext45Down.setPosition(80 * (cellIdx % 20) + 70, 80 * div(cellIdx, 20).quot + 80 + 50);
            //     scoreLabelNextDown.setPosition(80 * (cellIdx % 20) + 27, 80 * div(cellIdx, 20).quot + 80 + 60);
            //     scoreLabelPrev45Down.setPosition(80 * (cellIdx % 20) + 5, 80 * div(cellIdx, 20).quot + 80 + 60);
            //     scoreLabelPrevLeft.setPosition(80 * (cellIdx % 20) + 5, 80 * div(cellIdx, 20).quot + 80 + 25);

            // }

            // else if(isMiddle){

            // }


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

        sf::Text scoreLabelNextRight;
        sf::Text scoreLabelNext45Up;
        sf::Text scoreLabelNextUp;
        sf::Text scoreLabelPrev45Up;
        sf::Text scoreLabelPrevLeft;
        sf::Text scoreLabelPrev45Down;
        sf::Text scoreLabelNextDown;
        sf::Text scoreLabelNext45Down;


        bool isTarget;
        bool isWall;
        bool isStart;
        bool isExplored;

        int cellIdx;

        int curEst;
        int curScore;


};





// class Button: public Sprite2DComponent{

//     public:

//         Button(sf::Color colour, sf::Font font, string text, pair<int, int> pos);

//         void setInactive();
//         void setActive();

//         string getString(){return button.getString();}

//         void render(shared_ptr<sf::RenderWindow> ref){
//             ref->draw(this->button);
//         }

//         sf::Text getButton(){return button;}

//         ~Button(){}

//     private:

//         bool isActive;
//         bool isInactive;

//         sf::Text button;

// };


// Button::Button(sf::Color colour, sf::Font font, string text, std::pair<int, int> pos){
    
//     this->button = sf::Text(text, font, 45);
//     this->button.setColor(colour);
//     this->button.setPosition(sf::Vector2f(pos.first, pos.second));

//     isActive = true;
//     isInactive = false;

// }

// void Button::setActive(){}
// void Button::setInactive(){}


#endif