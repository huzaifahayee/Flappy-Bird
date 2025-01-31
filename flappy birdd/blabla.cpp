//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <stdlib.h>
//#include <time.h>
//
//using namespace sf;
//using namespace std;
//
//// Rect-Rect collision detection helper function
//// Rect-Rect collision detection helper function
//bool collides(FloatRect birdBounds, FloatRect pipeBounds) {
//    // Shrink the bounds slightly to avoid false positives
//    birdBounds.left += 7.0f;
//    birdBounds.width -= 50.0f;
//    birdBounds.top += 50.0f;
//    birdBounds.height -= 100.0f;
//
//    pipeBounds.left += 5.0f;
//    pipeBounds.width -= 50.0f;
//
//    return birdBounds.intersects(pipeBounds);
//}
//
//int main() {
//    // Create the window
//    RenderWindow window(VideoMode(1000, 600), "Floppy Bird");
//    window.setFramerateLimit(60);
//    srand(static_cast<unsigned int>(time(0)));
//
//    // Static array for pipes
//    const int MAX_PIPES = 100;
//    Sprite pipes[MAX_PIPES];
//    int pipeCount = 0;
//
//    // Textures
//    Texture flappyTextures[3], pipeTexture, backgroundTexture, gameOverTexture;
//
//    // Load textures
//    if (!backgroundTexture.loadFromFile("./assets/background.png") ||
//        !pipeTexture.loadFromFile("./assets/pipes.png") ||
//        !gameOverTexture.loadFromFile("./assets/gameover.png") ||
//        !flappyTextures[0].loadFromFile("./assets/bird.png") ||
//        !flappyTextures[1].loadFromFile("./assets/bird.png") ||
//        !flappyTextures[2].loadFromFile("./assets/bird.png")) {
//        cerr << "Error: Failed to load textures.\n";
//        return -1;
//    }
//
//    // Flappy bird settings
//    Sprite flappy;
//    flappy.setTexture(flappyTextures[0]);
//    flappy.setPosition(250.0f, 250.0f);
//    flappy.setScale(0.35f, 0.35f);
//    int flappyFrame = 0;
//    float flappyVelocity = 0.0f;
//    const float gravity = 0.5f;
//
//    // Game state
//    enum GameState { waiting, started, gameover } gameState = waiting;
//    int score = 0, frames = 0;
//
//    // Background
//    Sprite backgrounds[3];
//    for (int i = 0; i < 3; i++) {
//        backgrounds[i].setTexture(backgroundTexture);
//        backgrounds[i].setPosition(333.0f * i, 0.0f);
//    }
//
//    // Game Over
//    Sprite gameOverSprite;
//    gameOverSprite.setTexture(gameOverTexture);
//    gameOverSprite.setOrigin(96.0f, 21.0f);
//    gameOverSprite.setPosition(500.0f, 125.0f);
//    gameOverSprite.setScale(2.0f, 2.0f);
//
//    // Main game loop
//    while (window.isOpen()) {
//        // Event handling
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
//                if (gameState == waiting) {
//                    gameState = started;
//                }
//                if (gameState == started) {
//                    flappyVelocity = -8.0f; // Flap upward
//                }
//            }
//
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C && gameState == gameover) {
//                gameState = waiting;
//                flappy.setPosition(250.0f, 250.0f);
//                flappyVelocity = 0.0f;
//                score = 0; // Reset the score
//                pipeCount = 0;
//                cout << "Game reset! Score: " << score << endl;
//            }
//        }
//
//        // Game logic
//        if (gameState == waiting || gameState == started) {
//            if (frames % 6 == 0)
//                flappyFrame = (flappyFrame + 1) % 3;
//        }
//        flappy.setTexture(flappyTextures[flappyFrame]);
//
//        if (gameState == started) {
//            // Bird movement
//            flappy.move(0.0f, flappyVelocity);
//            flappyVelocity += gravity;
//
//            // Prevent bird from going offscreen
//            if (flappy.getPosition().y < 0.0f) {
//                flappy.setPosition(250.0f, 0.0f);
//                flappyVelocity = 0.0f;
//            }
//            else if (flappy.getPosition().y > 600.0f) {
//                gameState = gameover;
//                cout << "Game Over! Final Score: " << score << endl;
//            }
//
//            // Generate pipes
//            if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) {
//                int gap = 180; // Adjust gap
//                int randomY = rand() % 275 + 75;
//
//                pipes[pipeCount].setTexture(pipeTexture);
//                pipes[pipeCount].setPosition(1000.0f, randomY + gap);
//                pipes[pipeCount].setScale(0.5f, 2.0f);
//                pipeCount++;
//
//                pipes[pipeCount].setTexture(pipeTexture);
//                pipes[pipeCount].setPosition(1000.0f, randomY);
//                pipes[pipeCount].setScale(0.5f, -2.0f);
//                pipeCount++;
//            }
//
//            // Move pipes
//            for (int i = 0; i < pipeCount; i++) {
//                pipes[i].move(-3.0f, 0.0f);
//            }
//
//            // Remove offscreen pipes and update score
//            int newPipeCount = 0;
//            for (int i = 0; i < pipeCount; i++) {
//                if (pipes[i].getPosition().x > -100.0f) {
//                    pipes[newPipeCount++] = pipes[i];
//                }
//                else if (pipes[i].getPosition().x + 52.0f < flappy.getPosition().x && i % 2 == 0) {
//                    score++; // Increment score when passing a pipe
//                    cout << "Score: " << score << endl;
//                }
//            }
//            pipeCount = newPipeCount;
//
//            // Check collisions
//            FloatRect birdBounds = flappy.getGlobalBounds();
//            for (int i = 0; i < pipeCount; i++) {
//                FloatRect pipeBounds = pipes[i].getGlobalBounds();
//                if (collides(birdBounds, pipeBounds)) {
//                    gameState = gameover;
//                    cout << "Collision! Final Score: " << score << endl;
//                }
//            }
//        }
//
//        // Scroll background
//        for (int i = 0; i < 3; i++) {
//            backgrounds[i].move(-3.0f, 0.0f);
//            if (backgrounds[i].getPosition().x <= -333.0f) {
//                backgrounds[i].setPosition(667.0f, 0.0f);
//            }
//        }
//
//        // Drawing
//        window.clear();
//        for (int i = 0; i < 3; i++) window.draw(backgrounds[i]);
//        for (int i = 0; i < pipeCount; i++) window.draw(pipes[i]);
//        window.draw(flappy);
//        if (gameState == gameover) window.draw(gameOverSprite);
//        window.display();
//
//        frames++;
//    }
//
//    return 0;
//}
