#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <ctime>

using namespace sf;

// Game Constants
constexpr float SCREEN_WIDTH = 800.0f;
constexpr float SCREEN_HEIGHT = 600.0f;
constexpr int borderLeft = 140;
constexpr int borderRight = 660;
constexpr int racerWidth = 40;
constexpr int racerHeight = 70;
constexpr float initialGameSpeed = 3.2f;
constexpr float maxGameSpeed = 8.0f;
const std::string GAME_TITLE = "SPEED DEMONS";

// Game State
struct GameState {
    static std::string stringscore;
    static int score;
    static int highestScore;
    static float gameSpeed;
};

std::string GameState::stringscore;
int GameState::score = 0;
int GameState::highestScore = 0;
float GameState::gameSpeed = initialGameSpeed;

// Button structure for UI
struct Button {
    RectangleShape shape;
    Text text;
    bool isHovered = false;
};

// Function declarations
int getRandomNumber(int a, int b);
void gameOver(RenderWindow& app);
void runGame(RenderWindow& app);
void showInstructions(RenderWindow& window, const Font& font);
void showHighestScore(RenderWindow& window, const Font& font);
void createButton(Button& button, const Font& font, const std::string& label,
    float x, float y, float width, float height);
void drawMainMenu(RenderWindow& window, const Text& title,
    const std::vector<Button>& buttons, const Texture& backgroundTexture);
void handleButtonHover(std::vector<Button>& buttons, RenderWindow& window);

int main() {
    // Create the main window
    RenderWindow window(VideoMode(static_cast<unsigned int>(SCREEN_WIDTH),
        static_cast<unsigned int>(SCREEN_HEIGHT)),
        GAME_TITLE);
    window.setFramerateLimit(60);

    // Load fonts
    Font titleFont;
    Font menuFont;
    if (!titleFont.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading title font!" << std::endl;
        return -1;
    }
    if (!menuFont.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading menu font!" << std::endl;
        return -1;
    }

    // Create game title
    Text title(GAME_TITLE, titleFont, 70);
    title.setFillColor(Color(255, 50, 50));
    title.setStyle(Text::Bold);
    title.setOutlineColor(Color(30, 30, 30));
    title.setOutlineThickness(3.f);

    // Center the title
    FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    title.setPosition(Vector2f(SCREEN_WIDTH / 2.0f, 100.0f));

    // Create buttons
    std::vector<Button> buttons;

    // Start Game button
    Button startButton;
    createButton(startButton, menuFont, "Start New Game",
        SCREEN_WIDTH / 2 - 150, 200, 300, 50);
    buttons.push_back(startButton);

    // High Score button
    Button scoreButton;
    createButton(scoreButton, menuFont, "Highest Score",
        SCREEN_WIDTH / 2 - 150, 280, 300, 50);
    buttons.push_back(scoreButton);

    // Instructions button
    Button instructionsButton;
    createButton(instructionsButton, menuFont, "How to Play",
        SCREEN_WIDTH / 2 - 150, 360, 300, 50);
    buttons.push_back(instructionsButton);

    // Quit button
    Button quitButton;
    createButton(quitButton, menuFont, "Quit",
        SCREEN_WIDTH / 2 - 150, 440, 300, 50);
    buttons.push_back(quitButton);

    // Load background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("road.png")) {
        std::cerr << "Error loading background image! Using solid color instead." << std::endl;
    }

    // Main loop
    while (window.isOpen()) {
        // Process events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = window.mapPixelToCoords(
                        Vector2i(event.mouseButton.x, event.mouseButton.y));

                    for (size_t i = 0; i < buttons.size(); ++i) {
                        if (buttons[i].shape.getGlobalBounds().contains(mousePos)) {
                            switch (i) {
                            case 0: runGame(window); break;
                            case 1: showHighestScore(window, menuFont); break;
                            case 2: showInstructions(window, menuFont); break;
                            case 3: window.close(); break;
                            }
                        }
                    }
                }
            }
        }

        handleButtonHover(buttons, window);
        drawMainMenu(window, title, buttons, backgroundTexture);
        window.display();
    }

    return 0;
}

void runGame(RenderWindow& app) {
    SoundBuffer gameSoundBuffer;
    if (!gameSoundBuffer.loadFromFile("sound/game.wav")) {
        std::cerr << "Error loading game sound!" << std::endl;
    }
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    Texture background, racer, obs1, obs2, obs3, obs4;
    //Init font
    Font myfont;
    if (!myfont.loadFromFile("font/xirod.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    //Load all images
    if (!background.loadFromFile("cars/background.png")) return;
    if (!racer.loadFromFile("cars/racer.png")) return;
    if (!obs1.loadFromFile("cars/obs1.png")) return;
    if (!obs2.loadFromFile("cars/obs2.png")) return;
    if (!obs3.loadFromFile("cars/obs3.png")) return;
    if (!obs4.loadFromFile("cars/obs4.png")) return;

    //Create sprite
    Sprite Background(background), Background1(background), Racer(racer),
        Obs1(obs1), Obs2(obs2), Obs3(obs3), Obs4(obs4);

    float RacerX, RacerY, Obs1X, Obs1Y, Obs2X, Obs2Y, Obs3X, Obs3Y, Obs4X, Obs4Y;

    //Set racer and Obs pos
    RacerX = SCREEN_WIDTH / 2;
    RacerY = SCREEN_HEIGHT - racerHeight;
    Obs1X = static_cast<float>(getRandomNumber(borderLeft, borderRight));
    Obs2X = static_cast<float>(getRandomNumber(borderLeft, borderRight));
    Obs3X = static_cast<float>(getRandomNumber(borderLeft, borderRight));
    Obs4X = static_cast<float>(getRandomNumber(borderLeft, borderRight));
    Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300;
    float BackgroundY1 = 0;
    float BackgroundY2 = -600;

    GameSound.play();
    GameSound.setLoop(true);

    bool gameRunning = true;
    //GAME LOOP
    while (gameRunning && app.isOpen()) {
        //Init and count score
        GameState::stringscore = "SCORE:" + std::to_string(GameState::score);
        Text text(GameState::stringscore, myfont, 15);
        text.setPosition(5, 0);

        //Set car position
        Racer.setPosition(RacerX, RacerY);
        Obs1.setPosition(Obs1X, Obs1Y);
        Obs2.setPosition(Obs2X, Obs2Y);
        Obs3.setPosition(Obs3X, Obs3Y);
        Obs4.setPosition(Obs4X, Obs4Y);

        //Create scrolling background
        Background.setPosition(0, BackgroundY1);
        Background1.setPosition(0, BackgroundY2);
        if (BackgroundY2 > 0) {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        BackgroundY1 += 0.1f;
        BackgroundY2 += 0.1f;

        //Set Obs LOOP
        if (Obs1Y > SCREEN_HEIGHT) {
            Obs1Y = 0; Obs1X = static_cast<float>(getRandomNumber(borderLeft, borderRight)); GameState::score++;
        }
        else { Obs1Y = Obs1Y + GameState::gameSpeed; }
        if (Obs2Y > SCREEN_HEIGHT) {
            Obs2Y = 0; Obs2X = static_cast<float>(getRandomNumber(borderLeft, borderRight)); GameState::score++;
        }
        else { Obs2Y = Obs2Y + GameState::gameSpeed; }
        if (Obs3Y > SCREEN_HEIGHT) {
            Obs3Y = 0; Obs3X = static_cast<float>(getRandomNumber(borderLeft, borderRight)); GameState::score++;
        }
        else { Obs3Y = Obs3Y + GameState::gameSpeed; }
        if (Obs4Y > SCREEN_HEIGHT) {
            Obs4Y = 0; Obs4X = static_cast<float>(getRandomNumber(borderLeft, borderRight)); GameState::score++;
        }
        else { Obs4Y = Obs4Y + GameState::gameSpeed; }

        // Game level - smoother speed progression
        if (GameState::score > 0 && GameState::score <= 20) {
            GameState::gameSpeed = initialGameSpeed + (GameState::score * 0.05f);
        }
        else if (GameState::score > 20 && GameState::score <= 40) {
            GameState::gameSpeed = initialGameSpeed + 1.0f + ((GameState::score - 20) * 0.03f);
        }
        else if (GameState::score > 40) {
            GameState::gameSpeed = initialGameSpeed + 1.6f + ((GameState::score - 40) * 0.02f);
        }

        // Cap the maximum speed
        if (GameState::gameSpeed > maxGameSpeed) {
            GameState::gameSpeed = maxGameSpeed;
        }

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) {
                app.close();
                gameRunning = false;
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left) {
                    if (RacerX > borderLeft) { RacerX = RacerX - 10; }
                }
                if (event.key.code == Keyboard::Right) {
                    if (RacerX < borderRight) { RacerX = RacerX + 10; }
                }
                if (event.key.code == Keyboard::Up) {
                    if (RacerY > 0) { RacerY = RacerY - 10; }
                }
                if (event.key.code == Keyboard::Down) {
                    if (RacerY < SCREEN_HEIGHT - 70) { RacerY = RacerY + 10; }
                }
                if (event.key.code == Keyboard::Escape) {
                    GameSound.stop();
                    gameRunning = false;
                }
            }
        }

        //Check if accident happen
        bool collisionDetected = false;
        if (((RacerX >= (Obs1X - 30)) && (RacerX <= (Obs1X + 30))) && ((RacerY >= (Obs1Y - 30)) && (RacerY <= (Obs1Y + 30)))) {
            collisionDetected = true;
        }
        if (((RacerX >= (Obs2X - 30)) && (RacerX <= (Obs2X + 30))) && ((RacerY >= (Obs2Y - 30)) && (RacerY <= (Obs2Y + 30)))) {
            collisionDetected = true;
        }
        if (((RacerX >= (Obs3X - 30)) && (RacerX <= (Obs3X + 30))) && ((RacerY >= (Obs3Y - 30)) && (RacerY <= (Obs3Y + 30)))) {
            collisionDetected = true;
        }
        if (((RacerX >= (Obs4X - 30)) && (RacerX <= (Obs4X + 30))) && ((RacerY >= (Obs4Y - 30)) && (RacerY <= (Obs4Y + 30)))) {
            collisionDetected = true;
        }

        if (collisionDetected) {
            GameSound.stop();
            gameOver(app);
            gameRunning = false;
        }

        //Clear and redraw position
        app.clear();
        app.draw(Background);
        app.draw(Background1);
        app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text);
        app.display();
    }

    // Reset game state
    GameState::score = 0;
    GameState::gameSpeed = initialGameSpeed;
}

void gameOver(RenderWindow& app) {
    Texture gameover, troll;
    if (!gameover.loadFromFile("cars/over.png")) return;
    if (!troll.loadFromFile("cars/troll.png")) return;

    // Update highest score if current score is higher
    if (GameState::score > GameState::highestScore) {
        GameState::highestScore = GameState::score;
    }

    Sprite Gameover(gameover);
    Sprite Troll(troll);
    Troll.setPosition(10, 350);

    SoundBuffer gameOverBuffer;
    if (!gameOverBuffer.loadFromFile("sound/crash.wav")) {
        std::cerr << "Error loading crash sound!" << std::endl;
    }
    Sound GameOverSound;
    GameOverSound.setBuffer(gameOverBuffer);
    GameOverSound.play();

    Font myfont;
    if (!myfont.loadFromFile("font/xirod.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    bool waitingForInput = true;
    while (waitingForInput && app.isOpen()) {
        Event event;
        while (app.pollEvent(event)) {
            if (event.type == Event::Closed) {
                app.close();
                waitingForInput = false;
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape ||
                    event.key.code == Keyboard::Enter) {
                    waitingForInput = false;
                }
            }
        }

        // Create score texts
        std::string currentScoreStr = "YOUR SCORE: " + std::to_string(GameState::score);
        std::string highestScoreStr = "HIGHEST SCORE: " + std::to_string(GameState::highestScore);

        Text currentScoreText(currentScoreStr, myfont, 30);
        currentScoreText.setPosition(210, 450);
        currentScoreText.setFillColor(Color::White);

        Text highestScoreText(highestScoreStr, myfont, 30);
        highestScoreText.setPosition(210, 490);
        highestScoreText.setFillColor(Color(255, 215, 0)); // Gold color for high score

        app.clear();
        app.draw(Gameover);
        app.draw(currentScoreText);
        app.draw(highestScoreText);
        app.draw(Troll);
        app.display();
    }

    // Reset game state
    GameState::score = 0;
    GameState::gameSpeed = initialGameSpeed;
}

int getRandomNumber(int a, int b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);
    int result = dist(gen);
    return (result / 10) * 10; // Round to nearest 10
}

void createButton(Button& button, const Font& font, const std::string& label,
    float x, float y, float width, float height) {
    button.shape.setSize(Vector2f(width, height));
    button.shape.setPosition(x, y);
    button.shape.setFillColor(Color(70, 70, 70, 220));
    button.shape.setOutlineThickness(2.f);
    button.shape.setOutlineColor(Color::Transparent);
    button.isHovered = false;

    button.text.setFont(font);
    button.text.setString(label);
    button.text.setCharacterSize(24);
    button.text.setFillColor(Color::White);

    FloatRect textRect = button.text.getLocalBounds();
    button.text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    button.text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void drawMainMenu(RenderWindow& window, const Text& title,
    const std::vector<Button>& buttons, const Texture& backgroundTexture) {
    if (backgroundTexture.getSize().x > 0) {
        Sprite bgSprite(backgroundTexture);
        bgSprite.setScale(
            SCREEN_WIDTH / backgroundTexture.getSize().x,
            SCREEN_HEIGHT / backgroundTexture.getSize().y
        );
        window.draw(bgSprite);
    }
    else {
        window.clear(Color(30, 30, 30));
    }

    RectangleShape overlay(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    overlay.setFillColor(Color(0, 0, 0, 100));
    window.draw(overlay);
    window.draw(title);

    for (const auto& button : buttons) {
        window.draw(button.shape);
        window.draw(button.text);
    }
}

void handleButtonHover(std::vector<Button>& buttons, RenderWindow& window) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    for (auto& button : buttons) {
        if (button.shape.getGlobalBounds().contains(mousePos)) {
            if (!button.isHovered) {
                button.shape.setFillColor(Color(120, 120, 120, 220));
                button.shape.setOutlineColor(Color::White);
                button.isHovered = true;
            }
        }
        else {
            if (button.isHovered) {
                button.shape.setFillColor(Color(70, 70, 70, 220));
                button.shape.setOutlineColor(Color::Transparent);
                button.isHovered = false;
            }
        }
    }
}

void showInstructions(RenderWindow& window, const Font& font) {
    std::vector<std::string> lines = {
        "HOW TO PLAY",
        "",
        "Use LEFT and RIGHT arrow keys to move your car",
        "Avoid the obstacles coming down the road",
        "Game speed increases as you earn points",
        "The longer you survive, the higher your score",
        "",
        "CONTROLS:",
        "LEFT/RIGHT arrows - Steer your car",
        "ESC - Return to main menu",
        "",
        "Press ESC or ENTER to return"
    };

    const float boxWidth = 700.f;
    const float boxHeight = 500.f;
    const float boxX = (SCREEN_WIDTH - boxWidth) / 2.f;
    const float boxY = (SCREEN_HEIGHT - boxHeight) / 2.f;

    RectangleShape box(Vector2f(boxWidth, boxHeight));
    box.setPosition(boxX, boxY);
    box.setFillColor(Color(40, 40, 40, 220));
    box.setOutlineColor(Color(255, 50, 50));
    box.setOutlineThickness(3.f);

    Text title(lines[0], font, 50);
    title.setFillColor(Color(255, 50, 50));
    title.setStyle(Text::Bold);
    FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    title.setPosition(boxX + boxWidth / 2.0f, boxY + 40.f);

    bool waitingForInput = true;
    while (waitingForInput && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                waitingForInput = false;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape ||
                    event.key.code == Keyboard::Enter) {
                    waitingForInput = false;
                }
            }
        }

        window.clear(Color(20, 20, 20));
        RectangleShape overlay(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        overlay.setFillColor(Color(0, 0, 0, 150));
        window.draw(overlay);
        window.draw(box);
        window.draw(title);

        float y = boxY + 100.f;
        for (size_t i = 1; i < lines.size(); ++i) {
            if (lines[i].empty()) {
                y += 20.f;
                continue;
            }

            Text text(lines[i], font, (i == 7 ? 26 : 24));
            text.setFillColor(i == 7 ? Color(100, 255, 100) :
                (i >= 8 && i <= 9) ? Color(255, 215, 0) : Color::White);
            text.setPosition(boxX + 30.f, y);
            window.draw(text);
            y += (i == 7 ? 35.f : 30.f);
        }

        window.display();
    }
}

void showHighestScore(RenderWindow& window, const Font& font) {
    RectangleShape overlay(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    overlay.setFillColor(Color(0, 0, 0, 150));

    RectangleShape box(Vector2f(500.f, 200.f));
    box.setPosition((SCREEN_WIDTH - 500.f) / 2.f,
        (SCREEN_HEIGHT - 200.f) / 2.f);
    box.setFillColor(Color(40, 40, 40, 220));
    box.setOutlineColor(Color(255, 215, 0));
    box.setOutlineThickness(3.f);

    Text title("HIGHEST SCORE", font, 50);
    title.setFillColor(Color(255, 215, 0));
    title.setStyle(Text::Bold);
    FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    title.setPosition(SCREEN_WIDTH / 2.0f,
        (SCREEN_HEIGHT - 200.f) / 2.f - 30.f);

    std::string scoreStr = std::to_string(GameState::highestScore);
    Text scoreText(scoreStr, font, 60);
    scoreText.setFillColor(Color::White);
    scoreText.setStyle(Text::Bold);
    FloatRect scoreRect = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreRect.left + scoreRect.width / 2.0f,
        scoreRect.top + scoreRect.height / 2.0f);
    scoreText.setPosition(SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT / 2.0f + 20.f);

    Text prompt("Press ESC or ENTER to return", font, 24);
    prompt.setFillColor(Color(200, 200, 200));
    FloatRect promptRect = prompt.getLocalBounds();
    prompt.setOrigin(promptRect.left + promptRect.width / 2.0f,
        promptRect.top + promptRect.height / 2.0f);
    prompt.setPosition(SCREEN_WIDTH / 2.0f,
        (SCREEN_HEIGHT + 200.f) / 2.f + 60.f);

    bool waitingForInput = true;
    while (waitingForInput && window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                waitingForInput = false;
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape ||
                    event.key.code == Keyboard::Enter) {
                    waitingForInput = false;
                }
            }
        }

        window.clear(Color(20, 20, 20));
        window.draw(overlay);
        window.draw(box);
        window.draw(title);
        window.draw(scoreText);
        window.draw(prompt);
        window.display();
    }
}