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

        ~mapCell(){}


    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        bool isTarget;
        bool isWall;
        bool isStart;
        bool isExplored;

};

