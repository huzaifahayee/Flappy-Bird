//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <fstream>
//#include <stdlib.h>
//#include <time.h>
//
//using namespace sf;
//using namespace std;
//
//// Function to check collision between bird and pipes
//bool collides(FloatRect birdBounds, FloatRect pipeBounds) {
//    // Use global bounds directly for accurate collision detection
//    return birdBounds.intersects(pipeBounds);
//}
//
//// Save high score to a file
//void saveHighScore(int highScore) {
//    ofstream file("highscore.txt");
//    if (file.is_open()) {
//        file << highScore;
//        file.close();
//    }
//}
//
//// Load high score from a file
//int loadHighScore() {
//    ifstream file("highscore.txt");
//    int highScore = 0;
//    if (file.is_open()) {
//        file >> highScore;
//        file.close();
//    }
//    return highScore;
//}
//
//int main() {
//    RenderWindow window(VideoMode(1000, 600), "Udta Punjab");
//    window.setFramerateLimit(70);
//    srand(time(0));
//
//    int highScore = loadHighScore();
//
//    const int MAX_PIPES = 100;
//    Sprite pipes[MAX_PIPES];
//    bool scoredFlags[MAX_PIPES] = { false }; // Boolean array to track scored pipes
//    int pipeCount = 0;
//
//    Texture flappyTexture, pipeTexture, backgroundTexture, gameOverTexture;
//    if (!backgroundTexture.loadFromFile("./assets/background.png") ||
//        !pipeTexture.loadFromFile("./assets/pipes.png") ||
//        !gameOverTexture.loadFromFile("./assets/gameover.png") ||
//        !flappyTexture.loadFromFile("./assets/bird.png")) {
//        cout << "Error: Failed to load textures.\n";
//        return -1;
//    }
//
//    Sprite flappy;
//    flappy.setTexture(flappyTexture);
//    flappy.setPosition(250.0f, 250.0f);
//    flappy.setScale(0.5f, 0.5f); // Scale the bird
//
//    float flappyVelocity = 0.0f;
//    const float gravity = 0.5f;
//
//    enum GameState { lobby, started, gameover } gameState = lobby;
//
//    int score = 0, frames = 0;
//
//    Font font;
//    if (!font.loadFromFile("./assets/arimo.ttf")) {
//        cout << "Error: Failed to load font.\n";
//        return -1;
//    }
//
//    Text currentScoreText, highScoreText;
//    currentScoreText.setFont(font);
//    highScoreText.setFont(font);
//
//    currentScoreText.setCharacterSize(30);
//    highScoreText.setCharacterSize(30);
//
//    currentScoreText.setFillColor(Color::Red);
//    highScoreText.setFillColor(Color(0, 0, 139));
//
//    currentScoreText.setPosition(20.0f, 20.0f);
//    highScoreText.setPosition(20.0f, 60.0f);
//
//    Sprite backgrounds[3];
//    for (int i = 0; i < 3; i++) {
//        backgrounds[i].setTexture(backgroundTexture);
//        backgrounds[i].setPosition(333.0f * i, 0.0f);
//    }
//
//    Sprite gameOverSprite;
//    gameOverSprite.setTexture(gameOverTexture);
//    gameOverSprite.setPosition(275.0f, 125.0f);
//    gameOverSprite.setScale(2.0f, 2.0f);
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
//                if (gameState == lobby) {
//                    gameState = started;
//                }
//                if (gameState == started) {
//                    flappyVelocity = -8.0f;
//                }
//            }
//
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C && gameState == gameover) {
//                gameState = lobby;
//                flappy.setPosition(250.0f, 250.0f);
//                flappyVelocity = 0.0f;
//                score = 0;
//                pipeCount = 0;
//                cout << "Game reset! Score: " << score << endl;
//            }
//        }
//
//        if (gameState == started) {
//            flappy.move(0.0f, flappyVelocity);
//            flappyVelocity += gravity;
//
//            if (flappy.getPosition().y < 0.0f) {
//                flappy.setPosition(250.0f, 0.0f);
//                flappyVelocity = 0.0f;
//            }
//            else if (flappy.getPosition().y > 600.0f) {
//                gameState = gameover;
//                if (score > highScore) {
//                    highScore = score;
//                    saveHighScore(highScore);
//                }
//            }
//
//            if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) {
//                int gap = 170;
//                int randomY = rand() % 275 + 75;
//
//                pipes[pipeCount].setTexture(pipeTexture);
//                pipes[pipeCount].setPosition(1000.0f, randomY + gap);
//                pipes[pipeCount].setScale(0.5f, 2.0f);
//                scoredFlags[pipeCount] = false;
//                pipeCount++;
//
//                pipes[pipeCount].setTexture(pipeTexture);
//                pipes[pipeCount].setPosition(1000.0f, randomY);
//                pipes[pipeCount].setScale(0.5f, -2.0f);
//                scoredFlags[pipeCount] = false;
//                pipeCount++;
//            }
//
//            for (int i = 0; i < pipeCount; i++) {
//                pipes[i].move(-3.0f, 0.0f);
//            }
//
//            // Collision and scoring logic
//            for (int i = 0; i < pipeCount; i++) {
//                FloatRect birdBounds = flappy.getGlobalBounds();
//                FloatRect pipeBounds = pipes[i].getGlobalBounds();
//
//                if (!scoredFlags[i] && birdBounds.left > pipeBounds.left + pipeBounds.width) {
//                    if (i % 2 == 0) {
//                        score++;
//                        cout << "Score: " << score << endl;
//                    }
//                    scoredFlags[i] = true;
//                }
//
//                // Check collision
//                if (collides(birdBounds, pipeBounds)) {
//                    cout << "Collision detected with pipe " << i << endl;
//                    gameState = gameover;
//                    break;
//                }
//            }
//
//            int newPipeCount = 0;
//            for (int i = 0; i < pipeCount; i++) {
//                if (pipes[i].getPosition().x > -100.0f) {
//                    pipes[newPipeCount] = pipes[i];
//                    scoredFlags[newPipeCount] = scoredFlags[i];
//                    newPipeCount++;
//                }
//            }
//            pipeCount = newPipeCount;
//        }
//
//        if (gameState == started) {
//            for (int i = 0; i < 3; i++) {
//                backgrounds[i].move(-3.0f, 0.0f);
//                if (backgrounds[i].getPosition().x <= -333.0f) {
//                    backgrounds[i].setPosition(667.0f, 0.0f);
//                }
//            }
//        }
//
//        currentScoreText.setString("Score: " + to_string(score));
//        highScoreText.setString("High Score: " + to_string(highScore));
//        window.clear();
//
//        for (int i = 0; i < 3; i++) {
//            window.draw(backgrounds[i]);
//        }
//        for (int i = 0; i < pipeCount; i++) {
//            window.draw(pipes[i]);
//        }
//        window.draw(flappy);
//
//        if (gameState == gameover) {
//            window.draw(gameOverSprite);
//        }
//
//        window.draw(currentScoreText);
//        window.draw(highScoreText);
//
//        window.display();
//        frames++;
//    }
//
//    return 0;
//}
