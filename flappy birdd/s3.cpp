#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace sf;
using namespace std;

// Function to check collision between bird and pipes
bool collides(FloatRect birdArea, FloatRect pipeArea) 
{
    birdArea.left += 28.0f;
    birdArea.width -= 28.0f;
    birdArea.top += 28.0f;
    birdArea.height -= 28.0f;

    pipeArea.left += 28.0f;
    pipeArea.width -= 52.0f;
    pipeArea.top += 28.0f;
    pipeArea.height -= 28.0f;

    return birdArea.intersects(pipeArea);
}

// Save krta hai high score ko in a file
void saveHighScore(int highScore)
{
    ofstream file("highscore.txt");
    if (file.is_open()) 
    {
        file << highScore;
        file.close();
    }
}

// Load high score from a file
int loadHighScore()
{
    ifstream file("highscore.txt");
    int highScore = 0;
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    return highScore;
}

int main()
{
    RenderWindow window(VideoMode(1000, 600), "Udta Punjab");
    window.setFramerateLimit(70);
    srand(time(0));

    int highScore = loadHighScore();

    const int MAX_PIPES = 100;
    Sprite pipes[MAX_PIPES];
    int pipeCount = 0;

    bool pipeScored[MAX_PIPES] = { false }; // Track krta if the pipe pair was already scored

    Texture birdTexture, pipeTexture, backgroundTexture, gameOverTexture;

    if (!backgroundTexture.loadFromFile("./assets/background.png") ||
        !pipeTexture.loadFromFile("./assets/pipes.png")            ||
        !gameOverTexture.loadFromFile("./assets/gameover1.jpg")    ||
        !birdTexture.loadFromFile("./assets/bird.png"))
    {
        cout << "Error: Failed to load textures.\n";
        return -1;
    }

    Sprite flappy;
    flappy.setTexture(birdTexture);
    flappy.setPosition(400.0f, 250.0f);
    flappy.setScale(0.5f, 0.5f);

    float flappyVelocity = 0.0f;    
    const float gravity = 0.5f;      // ye constant rahegi

    enum GameState { lobby, started, gameover }
    gameState = lobby;

    int score = 0;
    int frames = 0;

    Font font;
    if (!font.loadFromFile("./assets/arimo.ttf"))
    {
        cout << "Error: Failed to load font."<<endl;
        return -1;
    }

    //idher text management ho rahi
    Text currentScore, highScoreText;
    currentScore.setFont(font);
    highScoreText.setFont(font);

    currentScore.setCharacterSize(30);
    highScoreText.setCharacterSize(30);

    currentScore.setFillColor(Color::Cyan);   // Score ko cyan color krdega
    highScoreText.setFillColor(Color::Cyan);   // High score ko cyan color krdega
    
    currentScore.setPosition(20.0f, 20.0f);
    highScoreText.setPosition(20.0f, 60.0f);

    //yahan pe background load ho raha

    Sprite backgrounds[3];
    for (int i = 0; i < 3; i++)
    {
        backgrounds[i].setTexture(backgroundTexture);
        backgrounds[i].setPosition(333.0f * i, 0.0f);
    }

    // yahan pe gameOVer ka texture load ho
// raha
    Sprite gameOverSprite;
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(275.0f, 125.0f);
    gameOverSprite.setScale(2.0f, 2.0f);

    // yahan se main game shuru ho rahi
    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event) ) 
        {
            if (event.type == Event::Closed)
            { 
                window.close();
            }

            if (event.type == Event::KeyPressed) 
            {
                // Handle space key
                if (event.key.code == Keyboard::Space) 
                {
                    if (gameState == lobby)
                    {
                        gameState = started;
                    }

                    if (gameState == started)
                    {
                        flappyVelocity = -8.0f;
                    }
                }

                // yahan pe enter krne se restart
                if (event.key.code == Keyboard::Enter && gameState == gameover) 
                {
                    gameState = lobby;
                    flappy.setPosition(400.0f, 250.0f);
                    flappyVelocity = 0.0f;
                    score = 0;
                    pipeCount = 0;

                    // Reset scored status for pipes jab gameover ho jaye

                    for (int i = 0; i < MAX_PIPES; i++)
                    {
                        pipeScored[i] = false;
                    }

                    cout << "Game reset! Score: " << score << endl;
                }

                // ESC krne se game exit
                if (event.key.code == Keyboard::Escape && (gameState == gameover || gameState == lobby ))
                {
                    window.close();

                    cout << "Game closed by user."<<endl;
                }
            }
        }

        if (gameState == started) 
        {
            flappy.move(0.0f, flappyVelocity);
            flappyVelocity += gravity;                                           //first movement

            if (flappy.getPosition().y < 0.0f) 
            {
                flappy.setPosition(400.0f, 0.0f);
                flappyVelocity = 0.0f;
            }
            else if (flappy.getPosition().y > 600.0f)
            {
                gameState = gameover;
                cout << "Game Over! Final Score: " << score << endl;
                if (score > highScore) 
                {
                    highScore = score;
                    saveHighScore(highScore);
                }
            }
            // pipe generation ke liye
            if (score >= 10)
            {
                if (frames % 80 == 0 && pipeCount + 2 < MAX_PIPES)
                {
                    int gap = 170;
                    int randomY = rand() % 300 + 75;

                    //yahan par pipe settings hain

                    //upper pipe
                    pipes[pipeCount].setTexture(pipeTexture);
                    pipes[pipeCount].setPosition(1000.0f, randomY + gap);
                    pipes[pipeCount].setScale(0.5f, 2.0f);

                    pipeScored[pipeCount] = false; // Reset scored status
                    pipeCount++;

                    //lower pipe
                    pipes[pipeCount].setTexture(pipeTexture);
                    pipes[pipeCount].setPosition(1000.0f, randomY);
                    pipes[pipeCount].setScale(0.5f, -2.0f);

                    pipeScored[pipeCount] = false; // Reset scored status
                    pipeCount++;
                }

            }
            else if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) 
            {
                int gap = 170;
                int randomY = rand() % 300 + 75;

                //yahan par pipe settings hain

                //upper pipe
                pipes[pipeCount].setTexture(pipeTexture);
                pipes[pipeCount].setPosition(1000.0f, randomY + gap);
                pipes[pipeCount].setScale(0.5f, 2.0f);

                pipeScored[pipeCount] = false; // Reset scored status
                pipeCount++;

                //lower pipe
                pipes[pipeCount].setTexture(pipeTexture);
                pipes[pipeCount].setPosition(1000.0f, randomY);
                pipes[pipeCount].setScale(0.5f, -2.0f);

                pipeScored[pipeCount] = false; // Reset scored status
                pipeCount++;
            }

            //yahan par pipes ko move kra rahe hain

            for (int i = 0; i < pipeCount; i++) 
            {
                if (score >= 10)
                {
                    pipes[i].move(-5.0f, 0.0f);
                }
                else
                { 
                pipes[i].move(-3.0f, 0.0f);
                }
            }

            int newPipeCount = 0;

            //yahan par pipes remove ho rahe hain
            for (int i = 0; i < pipeCount; i++) 
            {
                if (pipes[i].getPosition().x > -75.0f) 
                {
                    pipes[newPipeCount++] = pipes[i];
                    pipeScored[newPipeCount - 1] = pipeScored[i]; // Maintain scored status
                }
            }
            pipeCount = newPipeCount;

            // Increment score for each pipe pair passed
            for (int i = 0; i < pipeCount; i++) 
            {
                if (i % 2 == 0)
                { // Only process lower pipes (even-indexed)
                    if (pipes[i].getPosition().x + 52.0f < flappy.getPosition().x && !pipeScored[i])
                    {
                        score++; // Increment score for the pipe pair
                        pipeScored[i] = true; // Mark the pipe as scored
                        cout << "Score: " << score << endl;
                    }
                }
            }

            // Check for collisions with pipes
            FloatRect birdBounds = flappy.getGlobalBounds();

            for (int i = 0; i < pipeCount; i++) 
            {
                FloatRect pipeBounds = pipes[i].getGlobalBounds();

                if (collides(birdBounds, pipeBounds))
                {
                    gameState = gameover;
                    cout << "Game Over! Final Score: " << score << endl;
                    if (score > highScore) 
                    {
                        highScore = score;
                        saveHighScore(highScore);
                    }
                }
            }
        }

        // movement krta background ki
        if (gameState == started || gameState == lobby)
            for (int i = 0; i < 3; i++)
            {
                backgrounds[i].move(-3.0f, 0.0f);
                if (backgrounds[i].getPosition().x <= -333.0f)
                {
                    backgrounds[i].setPosition(667.0f, 0.0f);
                }
            }

        currentScore.setString("Score: " + to_string(score));

        highScoreText.setString("High Score: " + to_string(highScore));

        window.clear();

        // Draw everything
        for (int i = 0; i < 3; i++)
        {
            window.draw(backgrounds[i]);
        }

        for (int i = 0; i < pipeCount; i++) 
        {
            window.draw(pipes[i]);
        }

        window.draw(flappy);

        if (gameState == gameover) 
        {
            window.draw(gameOverSprite);
        }

        window.draw(currentScore);
        window.draw(highScoreText);

        window.display();
        frames++;
    }

    return 0;
}