//////////#include <SFML/Graphics.hpp>
//////////#include <iostream>
//////////#include <stdlib.h>
//////////#include <time.h>
//////////
//////////using namespace sf;
//////////using namespace std;
//////////
//////////// Rect-Rect collision detection helper function
//////////bool collides(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
//////////    return (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2);
//////////}
//////////
//////////int main() {
//////////    // Create the window
//////////    RenderWindow window(VideoMode(1000, 600), "Floppy Bird");
//////////    window.setFramerateLimit(60);
//////////    srand(static_cast<unsigned int>(time(0))); // Explicit cast to avoid warnings
//////////
//////////    // Static array for pipes
//////////    const int MAX_PIPES = 100;  // Maximum number of pipes allowed
//////////    Sprite pipes[MAX_PIPES];
//////////    int pipeCount = 0;          // Current number of active pipes
//////////
//////////    // Textures
//////////    Texture flappyTextures[3], pipeTexture, backgroundTexture, gameOverTexture;
//////////
//////////    // Load textures
//////////    if (!backgroundTexture.loadFromFile("./assets/background.png")) {
//////////        cerr << "Error: Failed to load background texture.\n";
//////////        return -1;
//////////    }
//////////    if (!pipeTexture.loadFromFile("./assets/pipes.png")) {
//////////        cerr << "Error: Failed to load pipe texture.\n";
//////////        return -1;
//////////    }
//////////    if (!gameOverTexture.loadFromFile("./assets/gameover.png")) {
//////////        cerr << "Error: Failed to load game over texture.\n";
//////////        return -1;
//////////    }
//////////    if (!flappyTextures[0].loadFromFile("./assets/bird.png") ||
//////////        !flappyTextures[1].loadFromFile("./assets/bird.png") ||
//////////        !flappyTextures[2].loadFromFile("./assets/bird.png")) {
//////////        cerr << "Error: Failed to load flappy bird textures.\n";
//////////        return -1;
//////////    }
//////////
//////////    // Flappy bird settings
//////////    Sprite flappy;
//////////    flappy.setPosition(static_cast<float>(250), static_cast<float>(250)); // Centered
//////////    flappy.setScale(static_cast<float>(0.2), static_cast<float>(0.2));    // Smaller scale
//////////    int flappyFrame = 0;
//////////    float flappyVelocity = 0.0f; // Use float instead of double
//////////    const float gravity = 0.5f;  // Use float for consistency
//////////
//////////    // Game settings
//////////    enum GameState { waiting, started, gameover } gameState = waiting;
//////////    int score = 0, highscore = 0, frames = 0;
//////////
//////////    // Background
//////////    Sprite backgrounds[3];
//////////    for (int i = 0; i < 3; i++) {
//////////        backgrounds[i].setTexture(backgroundTexture);
//////////        backgrounds[i].setScale(static_cast<float>(1.0), static_cast<float>(1.0));
//////////        backgrounds[i].setPosition(static_cast<float>(333 * i), 0.0f);
//////////    }
//////////
//////////    // Game Over
//////////    Sprite gameOverSprite;
//////////    gameOverSprite.setTexture(gameOverTexture);
//////////    gameOverSprite.setOrigin(static_cast<float>(96), static_cast<float>(21));
//////////    gameOverSprite.setPosition(static_cast<float>(500), static_cast<float>(125));
//////////    gameOverSprite.setScale(static_cast<float>(2), static_cast<float>(2));
//////////
//////////    // Debug message
//////////    cout << "Game initialized. Press SPACE to start!" << endl;
//////////
//////////    // Main game loop
//////////    while (window.isOpen()) {
//////////        // Event handling
//////////        Event event;
//////////        while (window.pollEvent(event)) {
//////////            if (event.type == Event::Closed) {
//////////                window.close();
//////////            }
//////////
//////////            // Spacebar: flap or start game
//////////            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
//////////                if (gameState == waiting) {
//////////                    gameState = started;
//////////                    cout << "Game started!" << endl;
//////////                }
//////////                if (gameState == started) {
//////////                    flappyVelocity = -8.0f; // Flap upward
//////////                }
//////////            }
//////////
//////////            // Press C to restart after gameover
//////////            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C && gameState == gameover) {
//////////                gameState = waiting;
//////////                flappy.setPosition(250.0f, 250.0f); // Reset bird's position
//////////                flappyVelocity = 0.0f;
//////////                score = 0;
//////////                pipeCount = 0;
//////////                cout << "Game reset! Press SPACE to start again." << endl;
//////////            }
//////////        }
//////////
//////////        // Game logic
//////////        if (gameState == waiting || gameState == started) {
//////////            if (frames % 6 == 0) {
//////////                flappyFrame = (flappyFrame + 1) % 3; // Animate bird
//////////            }
//////////        }
//////////        flappy.setTexture(flappyTextures[flappyFrame]);
//////////
//////////        if (gameState == started) {
//////////            flappy.move(0.0f, flappyVelocity);
//////////            flappyVelocity += gravity;
//////////
//////////            // Prevent bird from going offscreen
//////////            if (flappy.getPosition().y < 0.0f) {
//////////                flappy.setPosition(250.0f, 0.0f);
//////////                flappyVelocity = 0.0f;
//////////            }
//////////            else if (flappy.getPosition().y > 600.0f) {
//////////                gameState = gameover;
//////////                flappyVelocity = 0.0f;
//////////                cout << "Game over! Press C to restart." << endl;
//////////            }
//////////
//////////            // Generate pipes
//////////            if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) {
//////////                int gap = 180;
//////////                int randomY = rand() % 275 + 75;
//////////
//////////                // Lower pipe
//////////                pipes[pipeCount].setTexture(pipeTexture);
//////////                pipes[pipeCount].setPosition(1000.0f, static_cast<float>(randomY + gap));
//////////                pipes[pipeCount].setScale(0.3f, 0.3f);
//////////                pipeCount++;
//////////
//////////                // Upper pipe
//////////                pipes[pipeCount].setTexture(pipeTexture);
//////////                pipes[pipeCount].setPosition(1000.0f, static_cast<float>(randomY));
//////////                pipes[pipeCount].setScale(0.3f, -0.3f);
//////////                pipeCount++;
//////////
//////////                cout << "Pipe generated at Y = " << randomY << endl;
//////////            }
//////////
//////////            // Move pipes
//////////            for (int i = 0; i < pipeCount; i++) {
//////////                pipes[i].move(-3.0f, 0.0f);
//////////            }
//////////
//////////            // Remove offscreen pipes
//////////            int newPipeCount = 0;
//////////            for (int i = 0; i < pipeCount; i++) {
//////////                if (pipes[i].getPosition().x > -100.0f) {
//////////                    pipes[newPipeCount++] = pipes[i];
//////////                }
//////////            }
//////////            pipeCount = newPipeCount;
//////////
//////////            // Check for collisions
//////////            float fx = flappy.getPosition().x, fy = flappy.getPosition().y;
//////////            float fw = 34.0f * flappy.getScale().x, fh = 24.0f * flappy.getScale().y;
//////////
//////////            for (int i = 0; i < pipeCount; i++) {
//////////                float px = pipes[i].getPosition().x, py = pipes[i].getPosition().y;
//////////                float pw = 52.0f * pipes[i].getScale().x, ph = (pipes[i].getScale().y > 0.0f)
//////////                    ? 320.0f * pipes[i].getScale().y
//////////                    : -320.0f * pipes[i].getScale().y;
//////////
//////////                if (collides(fx, fy, fw, fh, px, py, pw, ph)) {
//////////                    gameState = gameover;
//////////                    cout << "Collision detected! Game over." << endl;
//////////                }
//////////            }
//////////        }
//////////
//////////        // Scroll background
//////////        for (int i = 0; i < 3; i++) {
//////////            backgrounds[i].move(-3.0f, 0.0f);
//////////            if (backgrounds[i].getPosition().x <= -333.0f) {
//////////                backgrounds[i].setPosition(667.0f, 0.0f);
//////////            }
//////////        }
//////////
//////////
//////////
//////////        // Drawing
//////////        window.clear();
//////////        for (int i = 0; i < 3; i++) window.draw(backgrounds[i]);
//////////        window.draw(flappy);
//////////        for (int i = 0; i < pipeCount; i++) window.draw(pipes[i]);
//////////        if (gameState == gameover) window.draw(gameOverSprite);
//////////        window.display();
//////////
//////////        frames++;
//////////    }
//////////
//////////    return 0;
//////////}
////////#include <SFML/Graphics.hpp>
////////#include <iostream>
////////#include <stdlib.h>
////////#include <time.h>
////////
////////using namespace sf;
////////using namespace std;
////////
////////// Rect-Rect collision detection helper function
////////bool collides(FloatRect birdBounds, FloatRect pipeBounds) {
////////    // Shrink the bounds slightly to avoid false positives
////////    birdBounds.left += 5.0f;   // Adjust the bird's bounds
////////    birdBounds.width -= 10.0f;
////////    birdBounds.top += 5.0f;
////////    birdBounds.height -= 10.0f;
////////
////////    pipeBounds.left += 5.0f;   // Adjust the pipe's bounds
////////    pipeBounds.width -= 10.0f;
////////
////////    return birdBounds.intersects(pipeBounds);
////////}
////////
////////int main() {
////////    // Create the window
////////    RenderWindow window(VideoMode(1000, 600), "Floppy Bird");
////////    window.setFramerateLimit(60);
////////    srand(static_cast<unsigned int>(time(0)));
////////
////////    // Static array for pipes
////////    const int MAX_PIPES = 100;
////////    Sprite pipes[MAX_PIPES];
////////    int pipeCount = 0;
////////
////////    // Textures
////////    Texture flappyTextures[3], pipeTexture, backgroundTexture, gameOverTexture;
////////
////////    // Load textures
////////    if (!backgroundTexture.loadFromFile("./assets/background.png") ||
////////        !pipeTexture.loadFromFile("./assets/pipes.png") ||
////////        !gameOverTexture.loadFromFile("./assets/gameover.png") ||
////////        !flappyTextures[0].loadFromFile("./assets/bird.png") ||
////////        !flappyTextures[1].loadFromFile("./assets/bird.png") ||
////////        !flappyTextures[2].loadFromFile("./assets/bird.png")) {
////////        cerr << "Error: Failed to load textures.\n";
////////        return -1;
////////    }
////////
////////    // Flappy bird settings
////////    Sprite flappy;
////////    flappy.setTexture(flappyTextures[0]);
////////    flappy.setPosition(250.0f, 250.0f);
////////    flappy.setScale(0.2f, 0.2f);
////////    int flappyFrame = 0;
////////    float flappyVelocity = 0.0f;
////////    const float gravity = 0.5f;
////////
////////    // Game state
////////    enum GameState { waiting, started, gameover } gameState = waiting;
////////    int score = 0, frames = 0;
////////
////////    // Background
////////    Sprite backgrounds[3];
////////    for (int i = 0; i < 3; i++) {
////////        backgrounds[i].setTexture(backgroundTexture);
////////        backgrounds[i].setPosition(333.0f * i, 0.0f);
////////    }
////////
////////    // Game Over
////////    Sprite gameOverSprite;
////////    gameOverSprite.setTexture(gameOverTexture);
////////    gameOverSprite.setOrigin(96.0f, 21.0f);
////////    gameOverSprite.setPosition(500.0f, 125.0f);
////////    gameOverSprite.setScale(2.0f, 2.0f);
////////
////////    // Main game loop
////////    while (window.isOpen()) {
////////        // Event handling
////////        Event event;
////////        while (window.pollEvent(event)) {
////////            if (event.type == Event::Closed)
////////                window.close();
////////
////////            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
////////                if (gameState == waiting) {
////////                    gameState = started;
////////                }
////////                if (gameState == started) {
////////                    flappyVelocity = -8.0f; // Flap upward
////////                }
////////            }
////////
////////            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C && gameState == gameover) {
////////                gameState = waiting;
////////                flappy.setPosition(250.0f, 250.0f);
////////                flappyVelocity = 0.0f;
////////                score = 0;
////////                pipeCount = 0;
////////            }
////////        }
////////
////////        // Game logic
////////        if (gameState == waiting || gameState == started) {
////////            if (frames % 6 == 0)
////////                flappyFrame = (flappyFrame + 1) % 3;
////////        }
////////        flappy.setTexture(flappyTextures[flappyFrame]);
////////
////////        if (gameState == started) {
////////            // Bird movement
////////            flappy.move(0.0f, flappyVelocity);
////////            flappyVelocity += gravity;
////////
////////            // Prevent bird from going offscreen
////////            if (flappy.getPosition().y < 0.0f) {
////////                flappy.setPosition(250.0f, 0.0f);
////////                flappyVelocity = 0.0f;
////////            }
////////            else if (flappy.getPosition().y > 600.0f) {
////////                gameState = gameover;
////////            }
////////
////////            // Generate pipes
////////            if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) {
////////                int gap = 180; // Increase gap for better passing
////////                int randomY = rand() % 275 + 75;
////////
////////                pipes[pipeCount].setTexture(pipeTexture);
////////                pipes[pipeCount].setPosition(1000.0f, randomY + gap);
////////                pipes[pipeCount].setScale(0.3f, 0.3f);
////////                pipeCount++;
////////
////////                pipes[pipeCount].setTexture(pipeTexture);
////////                pipes[pipeCount].setPosition(1000.0f, randomY);
////////                pipes[pipeCount].setScale(0.3f, -0.3f);
////////                pipeCount++;
////////            }
////////
////////            // Move pipes
////////            for (int i = 0; i < pipeCount; i++) {
////////                pipes[i].move(-3.0f, 0.0f);
////////            }
////////
////////            // Remove offscreen pipes
////////            int newPipeCount = 0;
////////            for (int i = 0; i < pipeCount; i++) {
////////                if (pipes[i].getPosition().x > -100.0f) {
////////                    pipes[newPipeCount++] = pipes[i];
////////                }
////////            }
////////            pipeCount = newPipeCount;
////////
////////            // Check collisions
////////            FloatRect birdBounds = flappy.getGlobalBounds();
////////            for (int i = 0; i < pipeCount; i++) {
////////                FloatRect pipeBounds = pipes[i].getGlobalBounds();
////////                if (collides(birdBounds, pipeBounds)) {
////////                    gameState = gameover;
////////                }
////////            }
////////        }
////////
////////        // Scroll background
////////        for (int i = 0; i < 3; i++) {
////////            backgrounds[i].move(-3.0f, 0.0f);
////////            if (backgrounds[i].getPosition().x <= -333.0f) {
////////                backgrounds[i].setPosition(667.0f, 0.0f);
////////            }
////////        }
////////
////////        // Drawing
////////        window.clear();
////////        for (int i = 0; i < 3; i++) window.draw(backgrounds[i]);
////////        for (int i = 0; i < pipeCount; i++) window.draw(pipes[i]);
////////        window.draw(flappy);
////////        if (gameState == gameover) window.draw(gameOverSprite);
////////        window.display();
////////
////////        frames++;
////////    }
////////
////////    return 0;
////////}
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <stdlib.h>
//#include <time.h>
//
//using namespace sf;
//using namespace std;
//
//// Rect-Rect collision detection helper function
//bool collides(FloatRect birdBounds, FloatRect pipeBounds) {
//    // Shrink the bounds slightly to avoid false positives
//    birdBounds.left += 5.0f;
//    birdBounds.width -= 10.0f;
//    birdBounds.top += 5.0f;
//    birdBounds.height -= 10.0f;
//
//    pipeBounds.left += 5.0f;
//    pipeBounds.width -= 10.0f;
//
//    return birdBounds.intersects(pipeBounds);
//}
//
//int main() 
//{
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
