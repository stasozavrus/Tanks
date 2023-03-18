#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    using namespace std;
    using namespace sf;

    const int GAME_W = 700;
    const int GAME_H = 700;

    //player
    int playerHp = 30;
    float timeBtwnShoot = 0.3f;
    float timeToShoot = 0.f;
    const float speed = 300.f;
    float bulletSpeed = 500.f;
    int score = 0;

    //enemy
    const float thresholdDistance = 100.f;
    const int numEnemies = 10;
    float enemySpeed = 50.f;
    const int directions[] = { 0, 90, 180, 270 };

    Clock clock;
    float deltaTime;

    class Bullet {
    public:
        Bullet(Vector2f position, Vector2f direction, float speed, float radius) :
            position_(position), direction_(direction), speed_(speed), radius_(radius) {
            shape_.setRadius(radius);
            shape_.setOrigin(radius, radius);
            shape_.setPosition(position_);
        }

        void update(float dt) {
            Vector2f velocity = direction_ * speed_ * dt;
            position_ += velocity;
            shape_.setPosition(position_);
        }

        Vector2f getPosition() const { return position_; }

        float getRadius() const { return radius_; }

        CircleShape& getShape() { return shape_; }

    private:
        Vector2f position_;
        Vector2f direction_;
        CircleShape shape_;
        float speed_;
        float radius_;
    };

    class Enemy {
        std::shared_ptr<Texture> enemyTexture_;
    public:

        Enemy(Vector2f position, Vector2f direction, float speed) :
            position_(position), direction_(direction), enemySpeed_(speed) {
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction_.x = direction.x / length;
            direction_.y = direction.y / length;
            enemyTexture_ = std::make_shared<Texture>();
            if (!enemyTexture_->loadFromFile("Assets\\Sprites\\Enemytank.png")) {
                cout << "Failed to load enemy texture" << endl;
            }
            sprite_.setTexture(*enemyTexture_);
            sprite_.setScale(1.3, 1.3);
            sprite_.setPosition(position_);
            sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);
            float angle = atan2(direction_.x, direction_.y) * 180.0f / 3.14159265f;
            sprite_.setRotation(angle);
        }

        void update(float dt, Vector2f playerPosition) {
            float distance = sqrt(pow(playerPosition.x - position_.x, 2) + pow(playerPosition.y - position_.y, 2));
            if (distance < 150 && abs(acos((direction_.x * direction_.x + direction_.y * direction_.y) / (sqrt(direction_.x * direction_.x + direction_.y * direction_.y) * enemySpeed_))) < 3.14159 / 2) {
                Vector2f direction = playerPosition - position_;
                float angle = atan2(direction.x, direction.y) * 180 / 3.141592;
                if (abs(direction.x) >= abs(direction.y)) {
                    if (direction.x > 0) {
                        angle = 90;
                    }
                    else {
                        angle = -90;
                    }
                }
                else {
                    if (direction.y > 0) {
                        angle = 180;
                    }
                    else {
                        angle = 0;
                    }
                }

                sprite_.setRotation(angle);
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;
                Vector2f velocity = direction * enemySpeed_ * dt;

                position_ += velocity;
                sprite_.setPosition(position_);
            }
            else {
                Vector2f velocity = Vector2f(direction_.x * enemySpeed_, -direction_.y * enemySpeed_) * dt;
                position_ += velocity;
                sprite_.setPosition(position_);
                if (direction_.y > 0) { sprite_.setRotation(0); }
                else if (direction_.y < 0) { sprite_.setRotation(180); }
                if (direction_.x > 0) { sprite_.setRotation(90); }
                else if (direction_.x < 0) { sprite_.setRotation(-90); }
            }



        }
        Vector2f getPosition() const { return position_; }

        Sprite& getSprite() { return sprite_; }

        void setDirection(Vector2f direction) { direction_ = direction; }

        Vector2f getDirection() const { return direction_; }

    private:
        Vector2f position_;
        Vector2f direction_;
        Sprite sprite_;
        float enemySpeed_;
    };
    vector<Enemy> enemies;
    vector<Bullet> bullets;

    srand(time(nullptr));
    RenderWindow window(VideoMode(GAME_W, GAME_H), "Tanks Game");

    window.setFramerateLimit(60);
    Texture playerTexture, background, wallTexture;
    Font font;
    if (!playerTexture.loadFromFile("Assets\\Sprites\\tank.png")) {
        cout << "Failed to load player texture" << endl;
        return 1;
    }
    if (!background.loadFromFile("Assets\\Sprites\\bg.png")) {
        cout << "Failed to load bg" << endl;
        return 1;
    }
    if (!wallTexture.loadFromFile("Assets\\Sprites\\border.png")) {
        cout << "Failed to load wall" << endl;
        return 1;
    }
    if (!font.loadFromFile("Assets\\Font\\ok.ttf")) {
        cout << "Failed to load font" << endl;
        return 1;
    }
    Text HP("30", font);
    HP.setCharacterSize(48);
    HP.setPosition(25, 10);
    HP.setFillColor(Color::Blue);

    Text Score("0", font);
    Score.setCharacterSize(48);
    Score.setPosition(530, 15);
    Score.setFillColor(Color::Green);

    Sprite player(playerTexture), backgroundSprite(background), wallSprite(wallTexture);
    backgroundSprite.setScale(3, 3);
    player.setScale(1.3, 1.3);
    player.setPosition(400, 500);
    player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
    Vector2f lastValidPosition = player.getPosition();

    for (int i = 0; i < numEnemies; ++i) {
        int directionIndex = rand() % 4;
        Vector2f direction;
        switch (directions[directionIndex]) {
        case 0:
            direction = Vector2f(0.0f, -1.0f);
            break;
        case 90:
            direction = Vector2f(1.0f, 0.0f);
            break;
        case 180:
            direction = Vector2f(0.0f, 1.0f);
            break;
        case 270:
            direction = Vector2f(-1.0f, 0.0f);
            break;
        }
        enemies.emplace_back(
            Vector2f(rand() % (window.getSize().x - 100) + 50, rand() % (window.getSize().y - 100) + 50),
            direction,
            enemySpeed
        );
    }

    while (window.isOpen())
    {
        Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();
        Vector2f playerPos = player.getPosition();
        vector<int> bulletsToRemove;
        vector<int> enemiesToRemove;
        if (score > 5) {
            enemySpeed = 60;
        }
        if (score > 15) {
            enemySpeed = 75;
        }
        for (auto& enemy : enemies) {
            Vector2f enemyPos = enemy.getPosition();
            if (enemyPos.x < 40 && enemy.getDirection().x < 0) {
                enemy.setDirection(Vector2f(-enemy.getDirection().x, enemy.getDirection().y));
            }
            else if (enemyPos.x > window.getSize().x - 40 && enemy.getDirection().x > 0) {
                enemy.setDirection(Vector2f(-enemy.getDirection().x, enemy.getDirection().y));
            }
            if (enemyPos.y < 40 && enemy.getDirection().y < 35) {
                enemy.setDirection(Vector2f(enemy.getDirection().x, -enemy.getDirection().y));
            }
            else if (enemyPos.y > window.getSize().y - 40 && enemy.getDirection().y < 35) {
                enemy.setDirection(Vector2f(enemy.getDirection().x, -enemy.getDirection().y));
            }
            enemy.update(deltaTime, playerPos);

            for (int i = 0; i < enemies.size(); i++)
            {
                if (enemies.size() < 10)
                {
                    int directionIndex = rand() % 4;
                    Vector2f direction;
                    switch (directions[directionIndex]) {
                    case 0:
                        direction = Vector2f(0.0f, -1.0f);
                        break;
                    case 90:
                        direction = Vector2f(1.0f, 0.0f);
                        break;
                    case 180:
                        direction = Vector2f(0.0f, 1.0f);
                        break;
                    case 270:
                        direction = Vector2f(-1.0f, 0.0f);
                        break;
                    }
                    enemies.emplace_back(
                        Vector2f(rand() % (window.getSize().x - 100) + 50, rand() % (window.getSize().y - 100) + 50),
                        direction,
                        enemySpeed
                    );
                }
                if (player.getGlobalBounds().intersects(enemies[i].getSprite().getGlobalBounds()))
                {
                    playerHp -= 3;
                    enemies.erase(enemies.begin() + i);
                    score += 1;
                }

            }
        }
        if (playerHp <= 0)
        {
            window.close();
            cout << "GAME OVER";
        }
        if (player.getPosition().y > 665 || player.getPosition().x > 665 || player.getPosition().x < 35 || player.getPosition().y < 35)
        {
            player.setPosition(lastValidPosition);
        }
        else
        {
            lastValidPosition = player.getPosition();
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            player.setRotation(-90);
            player.move(-speed * deltaTime, 0);

        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
            player.setRotation(90);
            player.move(speed * deltaTime, 0);

        }
        else if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player.setRotation(0);
            player.move(0, -speed * deltaTime);

        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player.setRotation(-180);
            player.move(0, speed * deltaTime);

        }
        if ((Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Left)) && timeToShoot <= 0) {
            timeToShoot = timeBtwnShoot;
            Vector2f bulletPosition = player.getPosition();
            Vector2f bulletDirection = { sin(player.getRotation() * 3.14159265f / 180.f), -cos(player.getRotation() * 3.14159265f / 180.f) };
            Bullet bullet(bulletPosition, bulletDirection, bulletSpeed, 4);
            bullets.push_back(bullet);
        }

        else {
            timeToShoot -= deltaTime;
        }

        window.clear();
        window.draw(backgroundSprite);
        for (auto& bullet : bullets)
        {
            bullet.update(deltaTime);
            CircleShape bulletShape(6.f);
            bulletShape.setPosition(bullet.getPosition());
            bulletShape.setFillColor(Color::Green);
            window.draw(bulletShape);
        }
        for (int i = 0; i < bullets.size(); i++) {
            for (int j = 0; j < enemies.size(); j++) {
                if (bullets[i].getShape().getGlobalBounds().intersects(enemies[j].getSprite().getGlobalBounds())) {
                    if (playerHp < 30)
                    {
                        playerHp += 1;
                        score += 1;
                    }
                    bulletsToRemove.push_back(i);
                    enemiesToRemove.push_back(j);
                    break;
                }
            }
        }
        for (int i = bulletsToRemove.size() - 1; i >= 0; i--) {
            bullets.erase(bullets.begin() + bulletsToRemove[i]);
        }
        for (int i = enemiesToRemove.size() - 1; i >= 0; i--) {
            enemies.erase(enemies.begin() + enemiesToRemove[i]);
        }
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet)
            {
                return bullet.getPosition().x < 0.f || bullet.getPosition().x > 700 ||
                    bullet.getPosition().y < 0.f || bullet.getPosition().y > 700;
            }), bullets.end());

        for (auto& enemy : enemies) {
            enemy.update(deltaTime, playerPos);
            window.draw(enemy.getSprite());
        }
        window.draw(wallSprite);
        HP.setString("HP: " + to_string(playerHp));
        Score.setString("Kills: " + to_string(score));
        window.draw(HP);
        window.draw(Score);
        window.draw(player);
        window.display();
    }
    return 0;
}
