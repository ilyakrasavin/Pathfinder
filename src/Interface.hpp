#ifndef INTERFACE_H
#define INTERFACE_H

// Base Interface for all components
class IComponent{

    public:

        // Pure Virtual: Need to be implemented in Inheriting classes
        virtual void render(sf::RenderWindow& ref) = 0;
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

        void render(sf::RenderWindow& ref) override{
            ref.draw(m_sprite);
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

        }

        void SetPosition(float x, float y) override{
            m_sprite.setPosition(x, y);
        }

        void render(sf::RenderWindow& ref) override{
            ref.draw(m_sprite);
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

        bool checkIsTarget(){return isTarget;}
        bool checkIsWall(){return isWall;}
        bool checkIsStart(){return isStart;}
        bool checkIsExplored(){return isExplored;}
        int setIdx(int);

        void setTarget(){isTarget = true;}
        void setWall(){isWall = true;}
        void setStart(){isStart = true;}
        void setExplored(){isExplored = true;}

        ~mapCell(){}


    private:
    
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        bool isTarget;
        bool isWall;
        bool isStart;
        bool isExplored;

        int cellIdx;

};



#endif