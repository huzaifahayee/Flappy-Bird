//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <stdlib.h>
//#include <time.h>
//
//using namespace sf;
//using namespace std;
//
//// Rect-Rect collision detection helper function
//bool collides(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
//    return (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2);
//}
//
//int main() {
//    // Create the window
//    RenderWindow window(VideoMode(1000, 600), "Floppy Bird");
//    window.setFramerateLimit(60);
//    srand(time(0));
//
//    // Static array for pipes
//    const int MAX_PIPES = 100;  // Maximum number of pipes allowed
//    Sprite pipes[MAX_PIPES];
//    int pipeCount = 0;          // Current number of active pipes
//
//    // Textures
//    Texture flappyTextures[3], pipeTexture, backgroundTexture, gameOverTexture;
//
//    // Load textures
//    if (!backgroundTexture.loadFromFile("./assets/background.png")) {
//        cerr << "Error: Failed to load background texture.\n";
//        return -1;
//    }
//    if (!pipeTexture.loadFromFile("./assets/pipes.png")) {
//        cerr << "Error: Failed to load pipe texture.\n";
//        return -1;
//    }
//    if (!gameOverTexture.loadFromFile("./assets/gameover.png")) {
//        cerr << "Error: Failed to load game over texture.\n";
//        return -1;
//    }
//    if (!flappyTextures[0].loadFromFile("./assets/bird.png") ||
//        !flappyTextures[1].loadFromFile("./assets/bird.png") ||
//        !flappyTextures[2].loadFromFile("./assets/bird.png")) {
//        cerr << "Error: Failed to load flappy bird textures.\n";
//        return -1;
//    }
//
//    // Flappy bird settings
//    Sprite flappy;
//    flappy.setPosition(250, 300);
//    flappy.setScale(2, 2);
//    int flappyFrame = 0;
//    double flappyVelocity = 0;
//    const float gravity = 0.5;
//
//    // Game settings
//    enum GameState { waiting, started, gameover } gameState = waiting;
//    int score = 0, highscore = 0, frames = 0;
//
//    // Background
//    Sprite backgrounds[3];
//    for (int i = 0; i < 3; i++) {
//        backgrounds[i].setTexture(backgroundTexture);
//        backgrounds[i].setScale(1.15625, 1.171875);
//        backgrounds[i].setPosition(333 * i, 0);
//    }
//
//    // Game Over
//    Sprite gameOverSprite;
//    gameOverSprite.setTexture(gameOverTexture);
//    gameOverSprite.setOrigin(96, 21);
//    gameOverSprite.setPosition(500, 125);
//    gameOverSprite.setScale(2, 2);
//
//    // Main game loop
//    while (window.isOpen()) {
//        // Update flappy animation
//        if (gameState == waiting || gameState == started) {
//            if (frames % 6 == 0) {
//                flappyFrame = (flappyFrame + 1) % 3;
//            }
//        }
//        flappy.setTexture(flappyTextures[flappyFrame]);
//
//        // Update flappy position
//        if (gameState == started) {
//            flappy.move(0, flappyVelocity);
//            flappyVelocity += gravity;
//
//            // Prevent bird from going offscreen
//            if (flappy.getPosition().y < 0) {
//                flappy.setPosition(250, 0);
//                flappyVelocity = 0;
//            }
//            else if (flappy.getPosition().y > 600) {
//                gameState = gameover;
//                flappyVelocity = 0;
//            }
//        }
//
//        // Generate pipes
//        if (gameState == started && frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) {
//            int gap = 150;
//            int randomY = rand() % 275 + 75;
//
//            // Lower pipe
//            pipes[pipeCount].setTexture(pipeTexture);
//            pipes[pipeCount].setPosition(1000, randomY + gap);
//            pipes[pipeCount].setScale(2, 2);
//            pipeCount++;
//
//            // Upper pipe
//            pipes[pipeCount].setTexture(pipeTexture);
//            pipes[pipeCount].setPosition(1000, randomY);
//            pipes[pipeCount].setScale(2, -2);
//            pipeCount++;
//        }
//
//        // Move pipes
//        for (int i = 0; i < pipeCount; i++) {
//            pipes[i].move(-3, 0);
//        }
//
//        // Remove offscreen pipes
//        int newPipeCount = 0;
//        for (int i = 0; i < pipeCount; i++) {
//            if (pipes[i].getPosition().x > -100) {
//                pipes[newPipeCount++] = pipes[i];
//            }
//        }
//        pipeCount = newPipeCount;
//
//        // Check for collisions
//        if (gameState == started) {
//            float fx = flappy.getPosition().x, fy = flappy.getPosition().y;
//            float fw = 34 * flappy.getScale().x, fh = 24 * flappy.getScale().y;
//
//            for (int i = 0; i < pipeCount; i++) {
//                float px = pipes[i].getPosition().x, py = pipes[i].getPosition().y;
//                float pw = 52 * pipes[i].getScale().x, ph = (pipes[i].getScale().y > 0)
//                    ? 320 * pipes[i].getScale().y
//                    : -320 * pipes[i].getScale().y;
//
//                if (collides(fx, fy, fw, fh, px, py, pw, ph)) {
//                    gameState = gameover;
//                }
//            }
//        }
//
//        // Handle events
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//
//            // Spacebar: flap or start game
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
//                if (gameState == waiting) {
//                    gameState = started;
//                }
//                if (gameState == started) {
//                    flappyVelocity = -8;
//                }
//            }
//
//            // Press C to restart after gameover
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C && gameState == gameover) {
//                gameState = waiting;
//                flappy.setPosition(250, 300);
//                score = 0;
//                pipeCount = 0;
//            }
//        }
//
//        // Drawing
//        window.clear();
//        for (int i = 0; i < 3; i++) window.draw(backgrounds[i]);
//        window.draw(flappy);
//
//        // Draw pipes
//        for (int i = 0; i < pipeCount; i++) {
//            window.draw(pipes[i]);
//        }
//
//        // Draw game over message
//        if (gameState == gameover) {
//            window.draw(gameOverSprite);
//        }
//
//        window.display();
//        frames++;
//    }
//
//    return 0;
//}
