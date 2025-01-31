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
//    birdBounds.left += 28.0f;   // Shrink the bounding box of the bird for precise collision
//    birdBounds.width -= 28.0f;
//    birdBounds.top += 28.0f;
//    birdBounds.height -= 28.0f;
//
//    pipeBounds.left += 28.0f;   // Shrink the bounding box of the pipes for precise collision
//    pipeBounds.width -= 28.0f;
//    pipeBounds.top += 28.0f;
//    pipeBounds.height -= 28.0f;
//
//    return birdBounds.intersects(pipeBounds); // Check if the bird intersects with the pipe
//}
//
//// Function to save the high score to a file
//void saveHighScore(int highScore) {
//    ofstream file("highscore.txt"); // Open the file to save the high score
//    if (file.is_open()) {
//        file << highScore;
//        file.close();
//    }
//}
//
//// Function to load the high score from a file
//int loadHighScore() {
//    ifstream file("highscore.txt"); // Open the file to read the high score
//    int highScore = 0;
//    if (file.is_open()) {
//        file >> highScore;
//        file.close();
//    }
//    return highScore;
//}
//
//int main() {
//    // Create the game window
//    RenderWindow window(VideoMode(1000, 600), "Udta Punjab");
//    window.setFramerateLimit(70); // Limit frame rate to 70 FPS
//    srand(time(0));               // Seed the random number generator
//
//    int highScore = loadHighScore(); // Load the high score from the file
//
//    const int MAX_PIPES = 100; // Maximum number of pipes
//    Sprite pipes[MAX_PIPES];  // Array to store pipe sprites
//    int pipeCount = 0;        // Count of currently active pipes
//
//    bool pipeScored[MAX_PIPES] = { false }; // Track if a pipe pair has been scored
//
//    // Load textures for bird, pipes, background, and game over screen
//    Texture flappyTexture, pipeTexture, backgroundTexture, gameOverTexture;
//    if (!backgroundTexture.loadFromFile("./assets/background.png") ||
//        !pipeTexture.loadFromFile("./assets/pipes.png") ||
//        !gameOverTexture.loadFromFile("./assets/gameover1.jpg") ||
//        !flappyTexture.loadFromFile("./assets/bird.png")) {
//        cout << "Error: Failed to load textures.\n";
//        return -1;
//    }
//
//    // Create the bird sprite
//    Sprite flappy;
//    flappy.setTexture(flappyTexture);
//    flappy.setPosition(400.0f, 250.0f); // Initial position of the bird
//    flappy.setScale(0.5f, 0.5f);        // Scale the bird sprite
//
//    float flappyVelocity = 0.0f;        // Bird's vertical velocity
//    const float gravity = 0.5f;         // Gravity applied to the bird
//
//    // Define the game states
//    enum GameState { lobby, started, gameover } gameState = lobby;
//
//    int score = 0, frames = 0; // Variables to track the score and frame count
//
//    // Load font for displaying text
//    Font font;
//    if (!font.loadFromFile("./assets/arimo.ttf")) {
//        cout << "Error: Failed to load font.\n";
//        return -1;
//    }
//
//    // Create text objects for the score and high score
//    Text currentScoreText, highScoreText;
//    currentScoreText.setFont(font);
//    highScoreText.setFont(font);
//    currentScoreText.setCharacterSize(30);
//    highScoreText.setCharacterSize(30);
//    currentScoreText.setFillColor(Color::Red);   // Score in red
//    highScoreText.setFillColor(Color::Black);   // High score in black
//    currentScoreText.setPosition(20.0f, 20.0f); // Position for current score
//    highScoreText.setPosition(20.0f, 60.0f);    // Position for high score
//
//    // Create background sprites
//    Sprite backgrounds[3];
//    for (int i = 0; i < 3; i++) {
//        backgrounds[i].setTexture(backgroundTexture);
//        backgrounds[i].setPosition(333.0f * i, 0.0f); // Position backgrounds side by side
//    }
//
//    // Create the game over sprite
//    Sprite gameOverSprite;
//    gameOverSprite.setTexture(gameOverTexture);
//    gameOverSprite.setPosition(275.0f, 125.0f); // Position the game over screen
//    gameOverSprite.setScale(2.0f, 2.0f);        // Scale the game over screen
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close(); // Close the window if the close event is triggered
//
//            if (event.type == Event::KeyPressed) {
//                // Handle space key for jumping or starting the game
//                if (event.key.code == Keyboard::Space) {
//                    if (gameState == lobby) {
//                        gameState = started;
//                    }
//                    if (gameState == started) {
//                        flappyVelocity = -8.0f; // Bird jumps
//                    }
//                }
//
//                // Handle Enter key to restart the game
//                if (event.key.code == Keyboard::Enter && gameState == gameover) {
//                    gameState = lobby;
//                    flappy.setPosition(400.0f, 250.0f); // Reset bird position
//                    flappyVelocity = 0.0f;              // Reset velocity
//                    score = 0;                          // Reset score
//                    pipeCount = 0;                      // Reset pipes
//
//                    // Reset scored status for pipes
//                    for (int i = 0; i < MAX_PIPES; i++) {
//                        pipeScored[i] = false;
//                    }
//
//                    cout << "Game reset! Score: " << score << endl;
//                }
//
//                // Handle ESC key to exit the game
//                if (event.key.code == Keyboard::Escape && (gameState == gameover || gameState == lobby)) {
//                    window.close();
//                    cout << "Game closed by user.\n";
//                }
//            }
//        }
//
//        if (gameState == started) {
//            // Update bird position and apply gravity
//            flappy.move(0.0f, flappyVelocity);
//            flappyVelocity += gravity;
//
//            // Check if the bird goes out of bounds
//            if (flappy.getPosition().y < 0.0f) {
//                flappy.setPosition(250.0f, 0.0f);
//                flappyVelocity = 0.0f;
//            }
//            else if (flappy.getPosition().y > 600.0f) {
//                gameState = gameover;
//                cout << "Game Over! Final Score: " << score << endl;
//                if (score > highScore) {
//                    highScore = score;
//                    saveHighScore(highScore);
//                }
//            }
//
//            // Generate pipes at intervals
//            if (frames % 150 == 0 && pipeCount + 2 < MAX_PIPES) {
//                int gap = 170;
//                int randomY = rand() % 275 + 75;
//                pipes[pipeCount].setTexture(pipeTexture);
//                pipes[pipeCount].setPosition(1000.0f, randomY + gap);
//                pipes[pipeCount].setScale(0.5f, 2.0f);
//                pipeScored[pipeCount] = false; // Reset scored status for this pipe
//                pipeCount++;
//                pipes[pipeCount].setTexture(pipeTexture);
//                pipes[pipeCount].setPosition(1000.0f, randomY);
//                pipes[pipeCount].setScale(0.5f, -2.0f);
//                pipeScored[pipeCount] = false; // Reset scored status for this pipe
//                pipeCount++;
//            }
//
//            // Move pipes
//            for (int i = 0; i < pipeCount; i++) {
//                pipes[i].move(-3.0f, 0.0f);
//            }
//
//            // Remove off-screen pipes and maintain scored status
//            int newPipeCount = 0;
//            for (int i = 0; i < pipeCount; i++) {
//                if (pipes[i].getPosition().x > -100.0f) {
//                    pipes[newPipeCount++] = pipes[i];
//                    pipeScored[newPipeCount - 1] = pipeScored[i];
//                }
//            }
//            pipeCount = newPipeCount;
//
//            // Increment score for passing pipes
//            for (int i = 0; i < pipeCount; i++) {
//                if (i % 2 == 0) { // Only process lower pipes
//                    if (pipes[i].getPosition().x + 52.0f < flappy.getPosition().x && !pipeScored[i]) {
//                        score++;             // Increment score
//                        pipeScored[i] = true; // Mark the pipe as scored
//                        cout << "Score: " << score << endl;
//                    }
//                }
//            }
//
//            // Check for collisions with pipes
//            FloatRect birdBounds = flappy.getGlobalBounds();
//            for (int i = 0; i < pipeCount; i++) {
//                FloatRect pipeBounds = pipes[i].getGlobalBounds();
//                if (collides(birdBounds, pipeBounds)) {
//                    gameState = gameover;
//                    cout << "Game Over! Final Score: " << score << endl;
//                    if (score > highScore) {
//                        highScore = score;
//                        saveHighScore(highScore);
//                    }
//                }
//            }
//        }
//
//        // Update background movement
//        if (gameState == started || gameState == lobby)
//            for (int i = 0; i < 3; i++) {
//                backgrounds[i].move(-3.0f, 0.0f);
//                if (backgrounds[i].getPosition().x <= -333.0f) {
//                    backgrounds[i].setPosition(667.0f, 0.0f);
//                }
//            }
//
//        // Update score text
//        currentScoreText.setString("Score: " + to_string(score));
//        highScoreText.setString("High Score: " + to_string(highScore));
//
//        window.clear();
//
//        // Draw backgrounds
//        for (int i = 0; i < 3; i++) {
//            window.draw(backgrounds[i]);
//        }
//
//        // Draw pipes
//        for (int i = 0; i < pipeCount; i++) {
//            window.draw(pipes[i]);
//        }
//
//        // Draw the bird
//        window.draw(flappy);
//
//        // Draw game over screen if the game is over
//        if (gameState == gameover) {
//            window.draw(gameOverSprite);
//        }
//
//        // Draw score and high score
//        window.draw(currentScoreText);
//        window.draw(highScoreText);
//
//        window.display();
//        frames++;
//    }
//
//    return 0;
//}
