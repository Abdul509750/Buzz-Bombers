#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
using namespace std;
using namespace sf;

// Initializing Dimensions
const int resolutionX = 1920;
const int resolutionY = 1080;
const int boxPixelsX = 32;
const int boxPixelsY = 32;

const int gameRows = resolutionX / boxPixelsX;
const int gameColumns = resolutionY / boxPixelsY;
// Function to load  font
  
  bool loadFont(Font& font ){
      if(!font.loadFromFile("/home/rafay/Jaro/Jaro-Regular-VariableFont_opsz.ttf")){
      return false;
      
      }else{
      
      return true;
	      }
}
// Function to load textures
bool loadTextures3(Texture& playerTexture, Texture& bulletTexture, Texture& enemyTexture, Texture& hummingTexture , Texture& honeycombTexture, Texture& hiveTexture , Texture& flowerTexture , Texture& enemy2Texture , Texture& honeycomb2Texture) {
    if (!playerTexture.loadFromFile("Textures/spray.png") ||
        !bulletTexture.loadFromFile("Textures/bullet.png") ||
        !enemyTexture.loadFromFile("Textures/yellow3_1_-removebg-preview.png") ||
        !hummingTexture.loadFromFile("Textures/bird(1).png")  ||
        !honeycombTexture.loadFromFile("Textures/honeycomb.png") ||
        !hiveTexture.loadFromFile("Textures/hive.png")  ||
        !flowerTexture.loadFromFile("Textures/obstacles.png") ||
        !enemy2Texture.loadFromFile("Textures/red3-removebg-preview.png") || 
        !honeycomb2Texture.loadFromFile("Textures/honeycomb_red.png") 
        ) {
        cout << "Failed to load textures!" << endl;
        return false;
    }
    return true;
}

   bool loadTextureinfantBee(Texture& infantBeeTexture){
      
      if(!infantBeeTexture.loadFromFile("Textures/infantbee-removebg-preview.png")){
   return false;
   }else{
   return true;
   		}
   	}
    bool loadTextures(Texture& playerTexture, Texture& bulletTexture, Texture& enemyTexture, Texture& hummingTexture , Texture& honeycombTexture, Texture& hiveTexture , Texture& flowerTexture ) {
    
    if (!playerTexture.loadFromFile("Textures/spray.png") ||
        !bulletTexture.loadFromFile("Textures/bullet.png") ||
        !enemyTexture.loadFromFile("Textures/yellow3_1_-removebg-preview.png") ||
        !hummingTexture.loadFromFile("Textures/bird(1).png")  ||
        !honeycombTexture.loadFromFile("Textures/honeycomb.png") ||
        !hiveTexture.loadFromFile("Textures/hive.png")  ||
        !flowerTexture.loadFromFile("Textures/obstacles.png"))
    
    { 
    cout << "Failed to load textures!" << endl;
        return false;
    }
    return true;
}
  bool loadTexturepower( Texture& power1 ,Texture& power2 , Texture& power3 , Texture&  power4){
  
  if(!power1.loadFromFile("Sprites/Height_Dec.png") || 
     !power2.loadFromFile("Sprites/Height_Inc.png") ||
     !power3.loadFromFile("Sprites/Speed_Dec.png") ||
     !power4.loadFromFile("Sprites/Speed_Inc.png")){
  cout<<" failed to load the textures"<<endl;
  return false;
  }
  return true;
  } 

 void createInfantBee(float beeHive_x[], float beeHive_y[], 
                     float honeycomb_x[], float honeycomb_y[], 
                     int maxBeeHives, int maxHoneycomb, 
                     Texture& infantBeeTexture, int& numInfantBees, 
                     float*& infantBee_x, float*& infantBee_y, 
                     bool*& infantBeeExists, Sprite*& infantBeeSprites) {
    for (int i = 0; i < maxBeeHives; ++i) {
            // Allocate memory for one more bee
            float* newBee_x = new float[numInfantBees + 1]; // x dimensions
            float* newBee_y = new float[numInfantBees + 1];  // y dimensions
            bool* newBeeExists = new bool[numInfantBees + 1];
            Sprite* newBeeSprites = new Sprite[numInfantBees + 1];

            // Copy existing bees to new arrays
            for (int k = 0; k < numInfantBees; ++k) {
                newBee_x[k] = infantBee_x[k];
                newBee_y[k] = infantBee_y[k];
                newBeeExists[k] = infantBeeExists[k];
                newBeeSprites[k] = infantBeeSprites[k];
            }

            // Free old memory
            delete[] infantBee_x;
            delete[] infantBee_y;
            delete[] infantBeeExists;
            delete[] infantBeeSprites;

            // Point to new arrays
            infantBee_x = newBee_x;
            infantBee_y = newBee_y;
            infantBeeExists = newBeeExists;
            infantBeeSprites = newBeeSprites;

            // Initialize the new Infant Bee
            infantBee_x[numInfantBees] = beeHive_x[i];
            infantBee_y[numInfantBees] = beeHive_y[i] - boxPixelsY;  // Above the beehive
            infantBeeExists[numInfantBees] = true;
            infantBeeSprites[numInfantBees].setTexture(infantBeeTexture);
            infantBeeSprites[numInfantBees].setPosition(infantBee_x[numInfantBees], infantBee_y[numInfantBees]);

            numInfantBees++;  // Incrementing the counter of Infant Bees bcz i have setted maximum bees upto 100 
           break;
        }
    }
void updateInfantBee(float infantBee_x[], float infantBee_y[], 
                     bool infantBeeExists[], int numInfantBees, 
                     Sprite infantBeeSprites[], float EnemySpeed, 
                     int direction[], float moveDownStart[], 
                     bool isMovingDown[], int moveDownDistance, 
                     Texture& enemy2Texture ,bool state2[]) {
    for (int i = 0; i < numInfantBees; ++i) {
        if (infantBeeExists[i]) {
            // Move Infant Bee upwards smoothly
            infantBee_y[i] -= 0.1f;  // Adjust speed for a smooth transition

            // Check if the Infant Bee has reached maturity
            if (infantBee_y[i] <= 20) {  // Close to the top
                infantBeeSprites[i].setTexture(enemy2Texture);  // Change to enemy texture
                infantBeeExists[i] = false;  // Mark as no longer an infant
                state2[i] = true;            // Mark as a mature enemy
            } else {
                // Update sprite position during upward movement
                infantBeeSprites[i].setPosition(infantBee_x[i], infantBee_y[i]);
            }
        } else if (state2[i]) {  // Mature bees move in zig-zag
            if (isMovingDown[i]) {
                // Move down
                infantBee_y[i] += 0.5f;
                moveDownStart[i] += 0.5f;

                // Check if down movement distance is reached
                if (moveDownStart[i] >= moveDownDistance) {
                    moveDownStart[i] = 0;
                    isMovingDown[i] = false;  // Stop moving down
                    direction[i] *= -1;      // Reverse direction
                }
            } else {
                // Horizontal movement
                infantBee_x[i] += direction[i] * EnemySpeed;

                // Check horizontal bounds
                if (infantBee_x[i] >= resolutionX - 2 * boxPixelsX || infantBee_x[i] <= 20) {
                    isMovingDown[i] = true;  // Start moving down
                }
            }

            // Reset position if the bee goes off the screen
            if (infantBee_y[i] >= resolutionY) {
                infantBee_x[i] = rand() % resolutionX;  // Random horizontal position
                infantBee_y[i] = -boxPixelsY;          // Reset to top
                direction[i] = (rand() % 2 == 0) ? 1 : -1;  // Random direction
                isMovingDown[i] = false;               // Reset downward state
            }

            // Update the position of the mature bee sprite
            infantBeeSprites[i].setPosition(infantBee_x[i], infantBee_y[i]);
        }
    }
}


//Function to load high scores from a file into an array
void loadHighScores(int highScores[], int& count, const string& fileName) {
    ifstream inputFile(fileName);
    count = 0;
   int MAX_SCORES = 5;
    if (inputFile.is_open()) {
        while (count < MAX_SCORES && inputFile >> highScores[count]) {
            ++count;
        }
        inputFile.close();
    } else {
        // Initialize with default scores if file doesn't exist
        for (int i = 0; i < MAX_SCORES; ++i) {
            highScores[i] = 0;
        }
        count = MAX_SCORES;
    }
}

// Function to save high scores from an array to a file
void saveHighScores(int highScores[], int scoreCount, const string& fileName) {
    ofstream file(fileName, ios::trunc);  // Open in truncate mode to overwrite the file
    if (file.is_open()) {
        for (int i = 0; i < scoreCount; i++) {
            file << highScores[i] << endl;  // Save each score on a new line
        }
        file.close();
    } else {
        cout << "Error opening file to save high scores." << endl;
    }
}

void promptPlayerName(RenderWindow& window, Font& font, int score, const string& fileName) {
    // Create a Text object to display the prompt and the player's input
    Text promptText("Enter your name:", font, 40);
    promptText.setFillColor(Color::White);
    promptText.setPosition(200, 200);  // Position the prompt

    Text nameText("", font, 40);  // Text to display the player's name
    nameText.setFillColor(Color::White);
    nameText.setPosition(200, 300);  // Position the entered name below the prompt

    string playerName = "";  // Store the player's name
    bool nameEntered = false;

    while (window.isOpen() && !nameEntered) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
            // Capture key presses
            if (e.type == Event::TextEntered) {
                if (e.text.unicode == '\b' && playerName.length() > 0) {  // Backspace to delete
                    playerName.pop_back();
                } else if (e.text.unicode < 128 && e.text.unicode != '\b') {  // If it's a valid character
                    playerName += static_cast<char>(e.text.unicode);
                }
            }

            // If the user presses Enter, save the score and exit
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter) {
                nameEntered = true;
               // saveHighScores(playerName, score, fileName);  // Save name and score to file
            }
        }

        // Update the name text to display the current player name
        nameText.setString(playerName);

        // Clear the window and draw everything
        window.clear();
        window.draw(promptText);
        window.draw(nameText);
        window.display();
    }
}
 // Function to manually sort high scores in descending order
void sortHighScores(int highScores[], int count) {
 int MAX_SCORES = 5;
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (highScores[i] < highScores[j]) {
                // Manual swap
                int temp = highScores[i];
                highScores[i] = highScores[j];
                highScores[j] = temp;
            }
        }
    }
}  
bool loadTexture2(Texture& lavaTexture){
      if(!lavaTexture.loadFromFile("Textures/lava2.png"))
      {
      cout<<"Failed to load texture "<<endl;
      return false;
      }
      return true; 
      }
    void  DisplayRemainingBullets(Text& bulletstext  , int bulletsFired , Font& font){
      bulletstext.setFont(font);
      bulletstext.setCharacterSize(30);
      int bulletsRemaining = 58 - bulletsFired;
      bulletstext.setFillColor(Color::Black);
      
      // setting the position of the bullets text based on the resolution and the boxSize
      bulletstext.setPosition((resolutionX / 2 - 12 * boxPixelsX) , (resolutionY - 3 * boxPixelsX));
      //set the size of the bullets text
      bulletstext.setScale(2.5f , 2.5f);
      bulletstext.setString("Remaining Bullets " + to_string(bulletsRemaining));
       
      } 
      void displayScore( Text &scoreText ,int score, Font& font, int resolutionX, int resolutionY, int boxPixelsX, int boxPixelsY) {
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);  // Font size
    scoreText.setFillColor(Color::Black);
    
    // Set the position of the score text based on resolution and box size
    scoreText.setPosition((resolutionX - 20 * boxPixelsX), resolutionY - 3 * boxPixelsY);
    
    // Scale the text
    scoreText.setScale(2.5f, 2.5f);
    
    // Set the score text string
    scoreText.setString("Score: " + to_string(score));
  
}

// Function to initialize bullets
void initializeBullets(float bullets_x[], float bullets_y[], bool bullets_exists[], Sprite bulletSprites[], Texture& bulletTexture) {
    for (int i = 0; i < 10; ++i) { // here we assumed that the maximum bullets are 10
        bullets_exists[i] = false; // Initially, no bullets exist
        bulletSprites[i].setTexture(bulletTexture);
        bulletSprites[i].setScale(3, 3);
        bulletSprites[i].setTextureRect(IntRect(0, 0, boxPixelsX, boxPixelsY));
    }
}
  void checkBulletCollisionForInfant(float bullet_x[], float bullet_y[], 
                                    float infantBee_x[], float infantBee_y[], 
                                    bool infantBeeExists[], int numInfantBees, 
                                    Sprite infantBeeSprites[], float EnemySpeed, 
                                    Texture& honeycomb2Texture, bool state2[], 
                                    int& score, bool bullets_exists[], bool honeycomb2_exists[], 
                                    float honeycomb2_y[], float honeycomb2_x[], 
                                    Texture power[], bool power_exists[], 
                                    float power_y[], float power_x[]) {
for (int i = 0; i < numInfantBees; i++) {
        if (infantBeeExists[i]) {
            // Checking for the collision between the infant bee and the bullet
            if (bullets_exists[i] &&
                bullet_x[i] >= infantBee_x[i] - boxPixelsX && bullet_x[i] <= infantBee_x[i] + boxPixelsX &&
                bullet_y[i] >= infantBee_y[i] - boxPixelsX && bullet_y[i] <= infantBee_y[i] + boxPixelsX) {
                infantBeeExists[i] = false;
                bullets_exists[i] = false;    
                score -= 500;  // Penalty for killing the small bee.
            }
        } else if (!infantBeeExists[i]) {  // Mature bees that turn into honeycombs
            if (bullets_exists[i] &&
                bullet_x[i] >= infantBee_x[i] - boxPixelsX && bullet_x[i] <= infantBee_x[i] + boxPixelsX &&
                bullet_y[i] >= infantBee_y[i] - boxPixelsX && bullet_y[i] <= infantBee_y[i] + boxPixelsX) {
                
                state2[i] = false;  // Bee disappears
                bullets_exists[i] = false; // Bullet disappears
                infantBeeSprites[i].setTexture(honeycomb2Texture); // Set honeycomb texture
                honeycomb2_exists[i] = true; // Mark honeycomb as existing
                honeycomb2_x[i] = infantBee_x[i];
                honeycomb2_y[i] = infantBee_y[i];
                score+=2000;
                
                }
     /*}else if(honeycomb2_exists[i]){
     
     if (bullets_exists[i] &&
                bullet_x[i] >= honeycomb2_x[i] - 2*boxPixelsX && bullet_x[i] <= honeycomb2_x[i] + 2*boxPixelsX &&
                bullet_y[i] >= honeycomb2_y[i] - 2*boxPixelsX && bullet_y[i] <= honeycomb2_y[i] + 2*boxPixelsX){
                // Generate power-up and set its texture
                power_exists[i] = true;
                int randomIndex = rand() % 4;  // Randomly select a power-up
                infantBeeSprites[i].setTexture(power[randomIndex]);
                bullets_exists[i] = false;  // Bullet disappears
                power_y[i] = infantBee_y[i];  // Set initial position of power-up to the bee's position
                power_x[i] = infantBee_x[i];
            }
        } else if (power_exists[i]) {  // Power-up exists and moves down
          {
                // Move power-up down until it reaches `resolutionY - 110`
                if (power_y[i] < resolutionY - 110) {
                    power_y[i] += 0.4;  // Move power-up down
                } else {
                    // Once the power-up reaches the height, stop moving it and save its position.
                    infantBeeSprites[i].setPosition(power_x[i] , power_y[i]);                    
                }*/
            }
        }
    }
//}

void initializeBeeHives(float beeHive_x[], float beeHive_y[], 
                        float honeycomb_x[], float honeycomb_y[], 
                        Sprite beeHiveSprite[], Texture& hiveTexture, 
                        bool canBeGenerated[], int maxBeeHives) {
    for (int i = 0; i < maxBeeHives; i++){
             {
                beeHive_x[i] = rand() % resolutionX;
                beeHive_y[i] = resolutionY / 3 + rand() % (resolutionY / 3);
// This ensures the range is from resolutionY/3 to 2*resolutionY/3


                // Set sprite texture and position
                beeHiveSprite[i].setTexture(hiveTexture);
                beeHiveSprite[i].setPosition(beeHive_x[i], beeHive_y[i]);
            }
        }
    }   
void initializesprays(float maxSpray_x[], float maxSpray_y[], Sprite maxSprite[], Texture& playerTexture, int maxSprays) {
    for (int i = 0; i < maxSprays; i++) {
        // Default position for sprays
        maxSpray_x[i] = boxPixelsX / 2; 
        maxSpray_y[i] = resolutionY - 3.8 * boxPixelsY;

        // Special case for the second spray (i == 1)
        if (i == 1) {
            maxSpray_x[i] = 2*boxPixelsX + boxPixelsX ;  // Place at far-left edge
            maxSpray_y[i] = resolutionY - 3.8 * boxPixelsY; // Adjust height
        }

        // Set the texture for the sprite
        maxSprite[i].setTexture(playerTexture);
    }
}

    
// Function to initialize player
void initializePlayer(Sprite& playerSprite, float& player_x, float& player_y, Texture& playerTexture) {
    player_x = resolutionX / 2 - boxPixelsX / 2; //or gameRows / 2 * boxPixels;
    player_y = resolutionY - 7 * boxPixelsY;  // these position are specified to initilize the player int he center of the screen
    playerSprite.setTexture(playerTexture);
}

// Function to initialize enemy
void initializeEnemies( float enemy_x[], float enemy_y[], Sprite enemySprites[], Texture& enemyTexture, int maxEnemies, int resolutionX, int resolutionY) {
    for (int i = 0; i < maxEnemies; ++i) {
        enemy_x[i] = rand() % resolutionX;
        enemy_y[i] = rand() % (resolutionY / 2);
        enemySprites[i].setTexture(enemyTexture);
        enemySprites[i].setPosition(enemy_x[i], enemy_y[i]);
    }
}


 void initializeEnemy2( float enemy2_x[] ,float enemy2_y[] , Sprite enemy2Sprite[] ,  Texture& enemy2Texture , int KillerEnemies){
 
       for (int i = 0; i < KillerEnemies; ++i) {
        enemy2_x[i] = rand() % resolutionX;
        enemy2_y[i] = rand() % (resolutionY / 2);
        enemy2Sprite[i].setTexture(enemy2Texture);
        enemy2Sprite[i].setPosition(enemy2_x[i], enemy2_y[i]);
    }
}
     
  // initializing and loading the honeycombs
  void initializeHoneycomb(float bullet_x[], float bullet_y[], float honeycomb_x[], float honeycomb_y[], 
                          Sprite honeycombSprite[], Texture& honeycombTexture, int maxHoneycomb, 
                          float new_x[], float new_y[], bool honeycomb_exists[], 
                          int resolutionX, int resolutionY) {
    for (int i = 0; i < maxHoneycomb; i++) {
        // Initialize random positions for honeycomb within screen boundaries
        honeycomb_x[i] = rand() % resolutionX;
        honeycomb_y[i] = rand() % (resolutionY / 2); // Upper half of the screen

        // Copy initial positions to new_x and new_y
        new_x[i] = honeycomb_x[i];
        new_y[i] = honeycomb_y[i];

        // Set the texture and position of the honeycomb sprite
        honeycombSprite[i].setTexture(honeycombTexture);
        honeycombSprite[i].setPosition(honeycomb_x[i], honeycomb_y[i]);

        // Mark the honeycomb as existing
        honeycomb_exists[i] = true;
    }
}


// Initialization of the hummingbird attributes
void initializeHummingbird(float& humming_x, float& humming_y, Sprite& hummingSprite, Texture& hummingTexture) {
    humming_x = rand() % resolutionX;
    humming_y = rand() % (resolutionY / 2);
    hummingSprite.setTexture(hummingTexture);
    hummingSprite.setPosition(humming_x, humming_y);
}
void  handleKillerBeeMovement(float& enemy2_x, float& enemy2_y, float& honeycomb2_x, float& honeycomb2_y, Sprite& enemy2Sprite, int& direction, 
                 float& moveDownStart, bool& isMovingDown, float moveDownDistance, 
                 bool& obstaclesExists, float& flower_x, float& flower_y , float EnemySpeed , bool& state2) {
    const int collisionThreshold = boxPixelsX; // Define collision threshold

    // 1. Normal enemy state (state == false)
    if ( !state2 && !obstaclesExists ) {
        if (isMovingDown) {
            // Moving the enemy down
            enemy2_y += 0.6;
            moveDownStart += 0.6;

            // Reset movement when distance is reached
            if (moveDownStart >= moveDownDistance) {
                moveDownStart = 0;
                isMovingDown = false;
                direction *= -1;  // Reverse direction when reaching the boundary
            }
        } else {
            // Moving the enemy horizontally based on direction
            enemy2_x += direction * EnemySpeed;
            
            // Check for boundary conditions and switch to moving down
            if (enemy2_x >= resolutionX - 2 * boxPixelsX || enemy2_x <= 20) {
                isMovingDown = true;
            }
        }

        // Reset enemy position if it goes off the screen or if it matches `new_y`
        if (enemy2_y >= resolutionY || enemy2_y == honeycomb2_y) {
            enemy2_y = -boxPixelsY;
            enemy2_x = rand() % resolutionX;  // Randomize starting position
            direction = (rand() % 2 == 0) ? 1 : -1;  // Random direction (left or right)
            isMovingDown = false;
        }

        // Update enemy position on screen
        enemy2Sprite.setPosition(enemy2_x, enemy2_y);

    // 2. Honeycomb state (state == true)
    } else if (  state2 && !obstaclesExists) {
        // Set the position to the new_x, new_y values where the bee was
        enemy2Sprite.setPosition(honeycomb2_x, honeycomb2_y);
        
        // Collision detection between the bee and the honeycomb
        if (enemy2_x >= honeycomb2_x - 0.5*collisionThreshold && enemy2_x <= honeycomb2_x + 0.5*collisionThreshold &&
            enemy2_y >= honeycomb2_y - 0.5*collisionThreshold && enemy2_y <= honeycomb2_y + 0.5*collisionThreshold) {
            enemy2_x *= -1;
            enemy2_y += boxPixelsY;  
            // Update the enemy sprite's position
            enemy2Sprite.setPosition(enemy2_x, enemy2_y);
        }

    // 3. Obstacles state
    } else if (obstaclesExists) {
        // Set enemy's position to match the obstacle's position
        enemy2Sprite.setPosition(flower_x, flower_y);
    }
}

void updateEnemy(float& enemy_x, float& enemy_y, float& new_x, float& new_y, Sprite& enemySprite, int& direction, 
                 float& moveDownStart, bool& isMovingDown, float moveDownDistance, bool& state, 
                 bool& obstaclesExists, float& flower_x, float& flower_y , float EnemySpeed) {
    const int collisionThreshold = boxPixelsX; // Define collision threshold

    // 1. Normal enemy state (state == false)
    if (!state && !obstaclesExists) {
        if (isMovingDown) {
            // Moving the enemy down
            enemy_y += EnemySpeed;
            moveDownStart += EnemySpeed;

            // Reset movement when distance is reached
            if (moveDownStart >= moveDownDistance) {
                moveDownStart = 0;
                isMovingDown = false;
                direction *= -1;  // Reverse direction when reaching the boundary
            }
        } else {
            // Moving the enemy horizontally based on direction
            enemy_x += direction * EnemySpeed;
            
            // Check for boundary conditions and switch to moving down
            if (enemy_x >= resolutionX - 2 * boxPixelsX || enemy_x <= 20) {
                isMovingDown = true;
            }
        }
        // Reset enemy position if it goes off the screen or if it matches `new_y`
        if (enemy_y >= resolutionY || enemy_y == new_y) {
            enemy_y = -boxPixelsY;
            enemy_x = rand() % resolutionX;  // Randomize starting position
            direction = (rand() % 2 == 0) ? 1 : -1;  // Random direction (left or right)
            isMovingDown = false;
        }

        // Update enemy position on screen
        enemySprite.setPosition(enemy_x, enemy_y);

    // 2. Honeycomb state (state == true)
    } else if (state && !obstaclesExists) {
        // Set the position to the new_x, new_y values where the bee was
        enemySprite.setPosition(new_x, new_y);
        
        // Collision detection between the bee and the honeycomb
        if (enemy_x >= new_x - 0.5*collisionThreshold && enemy_x <= new_x + 0.5*collisionThreshold &&
            enemy_y >= new_y - 0.5*collisionThreshold && enemy_y <= new_y + 0.5*collisionThreshold) {
            // Reverse direction and move down by one `boxPixelsX`
            enemy_x *= -1;
            enemy_y += boxPixelsY;
            
            // Update the enemy sprite's position
            enemySprite.setPosition(enemy_x, enemy_y);
        }

    // 3. Obstacles state
    } else if (obstaclesExists) {
        // Set enemy's position to match the obstacle's position
        enemySprite.setPosition(flower_x, flower_y);
    }
}
// Function to handle player movement
void handlePlayerMovement(float& player_x, float& player_y, float flower_x[], float flower_y[], bool obstaclesExists[], int maxEnemies) {
    // Check if player is trying to move to the left
    if (Keyboard::isKeyPressed(Keyboard::Left) && player_x > 0) {
        bool canMoveLeft = true;
        
        // Loop through all the obstacles (flowers)
        for (int i = 0; i < maxEnemies; i++) {
            if (obstaclesExists[i]) {
                // Check if the player is near the flower and block movement if there's an obstacle
                if (player_x >= flower_x[i] - 2*boxPixelsX && player_x < flower_x[i] + 2*boxPixelsX &&
                    player_y >= flower_y[i] - 2*boxPixelsY && player_y < flower_y[i] + 2*boxPixelsY) {
                    canMoveLeft = false;  // Block the movement if the player is near the obstacle
                    break;  // Exit the loop if we found a collision
                }
            }
        }

        // If no obstacle is in the way, move the player left
        if (canMoveLeft) {
            player_x -= 0.4f;
        }
    }

    // Check if player is trying to move to the right
    if (Keyboard::isKeyPressed(Keyboard::Right) && player_x < resolutionX - 4 * boxPixelsX) {
        bool canMoveRight = true;

        // Loop through all the obstacles (flowers)
        for (int i = 0; i < maxEnemies; i++) {
            if (obstaclesExists[i]) {
                // Check if the player is near the flower and block movement if there's an obstacle
                if (player_x >= flower_x[i] - boxPixelsX && player_x < flower_x[i] + boxPixelsX &&
                    player_y >= flower_y[i] - boxPixelsY && player_y < flower_y[i] + boxPixelsY) {
                    canMoveRight = false;  // Block the movement if the player is near the obstacle
                    break;  // Exit the loop if we found a collision
                }
            }
        }

        // If no obstacle is in the way, move the player right
        if (canMoveRight) {
            player_x += 0.4f;
        }
    }
}

void handleBulletFiring(float bullets_x[], float bullets_y[], bool bullets_exists[], 
                        float& player_x, float& player_y, Clock& bulletClock, 
                        Sprite bulletSprites[], int maxBullets, int& bulletsFired) {
    // Check if the space key is pressed, the cooldown time has elapsed, and no bullet is currently active
    if (Keyboard::isKeyPressed(Keyboard::Space) && bulletClock.getElapsedTime().asMilliseconds() > 400) {
        bool canFire = true;

        // Check if any bullet is currently active
        for (int i = 0; i < maxBullets; ++i) {
            if (bullets_exists[i]) {
                canFire = false; // Prevent firing if a bullet is active
                break;
            }
        }

        if (canFire) {
            // Find the first inactive bullet (though there will always be only one active bullet)
            for (int i = 0; i < maxBullets; ++i) {
                if (!bullets_exists[i]) { // Find the first inactive bullet
                    // Set the bullet's initial position relative to the player
                    bullets_x[i] = player_x + boxPixelsX / 2;
                    bullets_y[i] = player_y;
                    bullets_exists[i] = true; // Mark the bullet as active

                    // Update the bullet sprite's position
                    bulletSprites[i].setPosition(bullets_x[i], bullets_y[i]);

                    bulletsFired++; // Increment the bullets fired counter
                    break; // Exit the loop after firing one bullet
                }
            }
            bulletClock.restart(); // Reset the bullet firing cooldown
        }
    }
}

 void checkObstacles(float enemy_x[] ,float enemy_y[] , Texture& flowerTexture , bool obstaclesExists[] ,Sprite enemySprites[] , int resolutionY , int resolutionX , float flower_x[] , float flower_y[] , int& honeyBeeDeactivated){
           const int VerticalMovement = resolutionY - 6 * boxPixelsY ;
      for(int i = 0 ; i < 20; i++ ){
      if(!obstaclesExists[i]){
      if((enemy_y[i] >= VerticalMovement  && enemy_x[i] >= i*gameColumns) || (enemy_y[i] >= VerticalMovement  && enemy_x[i] >= i * gameColumns / 2)){
      
      enemySprites[i].setTexture(flowerTexture); 
      flower_x[i] = enemy_x[i];
      flower_y[i] = enemy_y[i];    
      obstaclesExists[i] = true; 
           honeyBeeDeactivated++;
            // Create a second obstacle on the opposite side when i == 1
                if (i == 1) {
                    int oppositeIndex = i+1; // Ensure an available index for the new obstacle
                    if (oppositeIndex < 20) { // Adjust this condition as needed
                        enemySprites[oppositeIndex].setTexture(flowerTexture);

                        // Calculate the opposite position
                        float opposite_x = resolutionX - enemy_x[i]; // Mirrored on X-axis
                        float opposite_y = enemy_y[i];               // Same Y position

                        //flower_x[oppositeIndex] = opposite_x;
                        //flower_y[oppositeIndex] = opposite_y;
                        obstaclesExists[oppositeIndex] = true;
               }  
      	    }
      	 }
      }
   }
}	
void checkObstaclesforEnemy2(float enemy2_x[], float enemy2_y[], Texture& flowerTexture, 
                             bool obstaclesExists[], Sprite enemy2Sprite[], 
                             int resolutionY, int resolutionX, 
                             float flower_x[], float flower_y[], 
                             int& honeyBeeDeactivated) {
    const int VerticalMovement = resolutionY - 6 * boxPixelsY;

    for (int i = 0; i < 20; i++) {
        if (!obstaclesExists[i]) {
            if ((enemy2_y[i] >= VerticalMovement && enemy2_x[i] >= i * gameColumns) || 
                (enemy2_y[i] >= VerticalMovement && enemy2_x[i] >= i * gameColumns / 2)) {

                // Convert the enemy into an obstacle
                enemy2Sprite[i].setTexture(flowerTexture);
                flower_x[i] = enemy2_x[i];
                flower_y[i] = enemy2_y[i];
                obstaclesExists[i] = true;
                honeyBeeDeactivated++;

                // Create a second obstacle on the opposite side when i == 1
                if (i == 1) {
                    int oppositeIndex = i+1; // Ensure an available index for the new obstacle
                    if (oppositeIndex < 20) { // Adjust this condition as needed
                        enemy2Sprite[oppositeIndex].setTexture(flowerTexture);

                        // Calculate the opposite position
                        float opposite_x = resolutionX - enemy2_x[i]; // Mirrored on X-axis
                        float opposite_y = enemy2_y[i];               // Same Y position

                        //flower_x[oppositeIndex] = opposite_x;
                        //flower_y[oppositeIndex] = opposite_y;
                        obstaclesExists[oppositeIndex] = true;
                        
                    }
                }
            }
        }
    }
}


void handleKillerBeeCollision(float bullets_x[], float bullets_y[], bool bullets_exists[], 
 float& enemy2_x, float& enemy2_y, Sprite& enemy2Sprite, Texture& honeycomb2Texture, float& honeycomb2_x, float& honeycomb2_y, 
 int& honeyBeeDeactivated, int killerEnemies, bool& state2, int& score, bool& honeycomb2_exists) {
    int collisionThreshold = boxPixelsX;

    // Collision with the enemy (normal enemy state)
    if (!state2) {
        for (int i = 0; i < killerEnemies; i++) {
            if (bullets_exists[i] &&
                bullets_x[i] >= enemy2_x - collisionThreshold && bullets_x[i] <= enemy2_x + collisionThreshold &&
                bullets_y[i] >= enemy2_y - collisionThreshold && bullets_y[i] <= enemy2_y + collisionThreshold) {

                enemy2Sprite.setTexture(honeycomb2Texture);  // Change to honeycomb texture
                state2 = true;  // Mark enemy as transformed to honeycomb
                honeycomb2_exists = true;  // Honeycomb becomes visible
                honeycomb2_x = enemy2_x;  // Store enemy's x position in honeycomb_x
                honeycomb2_y = enemy2_y;  // Store enemy's y position in honeycomb_y
                bullets_exists[i] = false;  // Deactivate bullet
                honeyBeeDeactivated++;
                score += 1000;
            }
        }
    } 

    // Collision with the honeycomb (after transformation)
    else {
        for (int i = 0; i < killerEnemies; i++) {
            if (bullets_exists[i] && honeycomb2_exists &&
                bullets_x[i] >= honeycomb2_x - 2*collisionThreshold && bullets_x[i] <= honeycomb2_x +2* collisionThreshold &&
                bullets_y[i] >= honeycomb2_y - 2*collisionThreshold && bullets_y[i] <= honeycomb2_y + 2*collisionThreshold) {

                bullets_exists[i] = false;  // Deactivate bullet
                honeycomb2_exists = false;  // Honeycomb disappears
            }
        }
    }
}

void checkCollision(float bullets_x[], float bullets_y[], float& new_x, float& new_y, bool bullets_exists[], 
                    float& enemy_x, float& enemy_y, Sprite& enemySprite, Texture& honeycombTexture, 
                    bool& state, bool& honeycomb_visible, bool& hiveExist, Texture& hiveTexture, 
                    float& hive_x, float& hive_y , int maxEnemies , int& score , bool obstaclesExists , Texture& flowerTexture , int& honeyBeeDeactivated) {
    const int collisionThreshold = boxPixelsX;
     static float moveDown;
    // Check collision with the enemy (normal enemy state)
    if (!state) {   // means that the  
        for (int i = 0; i < maxEnemies; i++) {
            if (bullets_exists[i]) {
                if (bullets_x[i] >= enemy_x - collisionThreshold && bullets_x[i] <= enemy_x + collisionThreshold &&
                    bullets_y[i] >= enemy_y - collisionThreshold && bullets_y[i] <= enemy_y + collisionThreshold) {

                    enemySprite.setTexture(honeycombTexture);  // Change to honeycomb texture
                    state = true;  // Mark enemy as transformed to honeycomb
                    honeycomb_visible = true;  // Honeycomb becomes visible
                    new_x = enemy_x;  // Store enemy's x position in new_x
                    new_y = enemy_y;  // Store enemy's y position in new_y
                    bullets_exists[i] = false;  // Deactivate bullet
                    honeyBeeDeactivated++;
                    score += 100;
                }
            }
        }
    }
 
    // Now check for collision with the honeycomb (when enemy is transformed into honeycomb)
    else if(state) {  // Only check if honeycomb is visible
        for (int i = 0; i < maxEnemies; i++) {
            if (bullets_exists[i] &&  honeycomb_visible) {
                if (bullets_x[i] >= new_x - collisionThreshold && bullets_x[i] <= new_x + collisionThreshold &&
                    bullets_y[i] >= new_y - collisionThreshold && bullets_y[i] <= new_y + collisionThreshold) {

                    bullets_exists[i] = false;  // Deactivate bullet
                    honeycomb_visible = false;  // Honeycomb disappears
                }
                        }
                   }
                }
            }
 // Function to display the transition message dynamically during gameplay
void displayLevelStart(RenderWindow& window, int level) {
    // Create a font and text for the level message
    Font font;
    if (!font.loadFromFile("/home/rafay/Jaro/Jaro-Regular-VariableFont_opsz.ttf")) {
        // Handle font loading error
        return;
    }
    
    Text levelText;
    levelText.setFont(font);
    levelText.setString("LEVEL " + to_string(level) + " STARTING Dont be Hasty ...");
    levelText.setCharacterSize(80);   // Large font size
    levelText.setFillColor(Color::Red); // Red color for the text
    levelText.setStyle(Text::Bold);

    // Center the text on the screen
    levelText.setPosition(resolutionX / 16 ,  resolutionY -  1000);

    // Draw the transition message on top of the current game frame
    window.draw(levelText);
}
   
void updateHoneyComb(float bullet_x[], float bullet_y[], float honeycomb_x[], float honeycomb_y[], 
                     Sprite honeycombSprite[], Texture& honeycombTexture, int maxHoneycomb, 
                     float new_x[], float new_y[], bool honeycomb_exists[], bool bullets_exists[], 
                     int maxBullets) {
    const int collisionThreshold = boxPixelsX;

    for (int i = 0; i < maxHoneycomb; i++) {
        if (honeycomb_exists[i]) {  // Only update existing honeycombs
            // Update sprite properties
            honeycombSprite[i].setTexture(honeycombTexture);
            honeycombSprite[i].setPosition(honeycomb_x[i], honeycomb_y[i]);

            // Update new_x and new_y 
            new_x[i] = honeycomb_x[i];
            new_y[i] = honeycomb_y[i];

            // Check collision with bullets
            for (int j = 0; j < maxBullets; j++) {  // Iterate over bullets
                if (bullets_exists[j]) {  // Only check for bullets that exist
                    // Check if the bullet is within the collision threshold of the honeycomb
                    if (bullet_x[j] >= honeycomb_x[i] - collisionThreshold &&
                        bullet_x[j] <= honeycomb_x[i] + collisionThreshold &&
                        bullet_y[j] >= honeycomb_y[i] - collisionThreshold &&
                        bullet_y[j] <= honeycomb_y[i] + collisionThreshold) {

                        // Mark bullet and honeycomb as non-existent after collision
                        bullets_exists[j] = false;  // Bullet disappears
                        honeycomb_exists[i] = false;  // Honeycomb disappears
                        break;  // Exit the bullet loop
                    }
                }
            }
        }
    }
}


// Function to update bullets
void updateBullets(float bullets_x[], float bullets_y[], bool bullets_exists[], Sprite bulletSprites[], int maxBullets) {
    for (int i = 0; i < maxBullets; ++i) {
        if (bullets_exists[i]) {
            bullets_y[i] -= 10;
            if (bullets_y[i] < 0) {
                bullets_exists[i] = false;
            }
            bulletSprites[i].setPosition(bullets_x[i], bullets_y[i]);
        }
    }
}
// Function to update hummingbird position (random movement)
void updateHummingbird(float& humming_x, float& humming_y, float& humming_dx, float& humming_dy, 
                       Sprite& hummingSprite, float resolutionX, float resolutionY, 
                       float boxPixelsX, float boxPixelsY, bool honeycomb_exists[], 
                       float new_x[], float new_y[], const int maxEnemies , int& score) {
    // Update the hummingbird's position
    humming_x += humming_dx;
    humming_y += humming_dy;

    // Gradually change the direction slightly for more natural movement
    humming_dx += (static_cast<float>(rand() % 3) - 1) * 0.01f; // Small random change in dx
    humming_dy += (static_cast<float>(rand() % 3) - 1) * 0.01f; // Small random change in dy

   
    float maxSpeedSquare = 0.5f; // Max speed squared
    float currentSpeedSquare = humming_dx * humming_dx + humming_dy * humming_dy;

    if (currentSpeedSquare > maxSpeedSquare) {
        float scale = maxSpeedSquare / currentSpeedSquare;
        humming_dx *= scale; // Scale down dx
        humming_dy *= scale; // Scale down dy
    }

    // Check if the hummingbird hits the screen boundaries
    if (humming_x <= 0 || humming_x >= (resolutionX-30) - boxPixelsX) {
        humming_dx = -humming_dx; // Reverse horizontal direction
    }
    if (humming_y <= 0 || humming_y >= (resolutionY-111) - boxPixelsY) {
        humming_dy = -humming_dy; // Reverse vertical direction
    }

   // Check if there is any honeycomb on the screen
for (int i = 0; i < maxEnemies; i++) {
    const int rectangleHeight = resolutionY - 110; // Some offset height for the rectangle area
    const int numTiers = 8; // Dividing the screen into 8 tiers
    int tierHeight = resolutionY / numTiers;

    // Calculate the distance squared between the hummingbird and the honeycomb
    float distanceSquared = (humming_x - new_x[i]) * (humming_x - new_x[i]) + 
                            (humming_y - new_y[i]) * (humming_y - new_y[i]);

    // Check if the honeycomb exists
    if (honeycomb_exists[i]) {
        // Check which tier the honeycomb is in and assign the score
        if (new_y[i] <= (tierHeight * 2)) { // First and second tiers
            if (distanceSquared < 1000.0f) { // If close enough, "eat" the honeycomb
                honeycomb_exists[i] = false; // Mark honeycomb as "eaten"
                humming_dx = -humming_dx * 0.01f; // Bounce back after eating
                humming_dy = -humming_dy * 0.01f;
                score += 1000; // Score for first and second tiers
            }
        } else if (new_y[i] > (tierHeight * 2) && new_y[i] <= (tierHeight * 5)) { // Third, fourth, and fifth tiers
            if (distanceSquared < 1000) { // If close enough, "eat" the honeycomb
                honeycomb_exists[i] = false; // Mark honeycomb as "eaten"
                humming_dx = -humming_dx * 0.01f; // Bounce back after eating
                humming_dy = -humming_dy * 0.01f;
                score += 800; // Score for third, fourth, and fifth tiers
            }
        } else { // Lower tiers (sixth to eighth)
            if (distanceSquared < 1000) { // If close enough, "eat" the honeycomb
                honeycomb_exists[i] = false; // Mark honeycomb as "eaten"
                humming_dx = -humming_dx * 0.01f; // Bounce back after eating
                humming_dy = -humming_dy * 0.01f;
                score += 500; // Score for lower tiers
            }
        }
    }
}

// Set the position of the hummingbird
hummingSprite.setPosition(humming_x, humming_y);

}

void updateHummingbirdForEnemy2(float& humming_x, float& humming_y, float& humming_dx, float& humming_dy, 
                       Sprite& hummingSprite, float resolutionX, float resolutionY, 
                       float boxPixelsX, float boxPixelsY, bool honeycomb2_exists[], 
                       float honeycomb2_x[], float honeycomb2_y[], const int killerEnemies , int& score) {
    // Update the hummingbird's position
    humming_x += humming_dx;
    humming_y += humming_dy;

    // Gradually change the direction slightly for more natural movement
    humming_dx += (static_cast<float>(rand() % 3) - 1) * 0.01f; // Small random change in dx
    humming_dy += (static_cast<float>(rand() % 3) - 1) * 0.01f; // Small random change in dy

   
    float maxSpeedSquare = 0.5f; // Max speed squared
    float currentSpeedSquare = humming_dx * humming_dx + humming_dy * humming_dy;

    if (currentSpeedSquare > maxSpeedSquare) {
        float scale = maxSpeedSquare / currentSpeedSquare;
        humming_dx *= scale; // Scale down dx
        humming_dy *= scale; // Scale down dy
    }

    // Check if the hummingbird hits the screen boundaries
    if (humming_x <= 0 || humming_x >= (resolutionX-30) - boxPixelsX) {
        humming_dx = -humming_dx; // Reverse horizontal direction
    }
    if (humming_y <= 0 || humming_y >= (resolutionY-111) - boxPixelsY) {
        humming_dy = -humming_dy; // Reverse vertical direction
    }

   // Check if there is any honeycomb on the screen
for (int i = 0; i < killerEnemies; i++) {
    const int rectangleHeight = resolutionY - 110; // Some offset height for the rectangle area
    const int numTiers = 8; // Dividing the screen into 8 tiers
    int tierHeight = resolutionY / numTiers;

    // Calculate the distance squared between the hummingbird and the honeycomb
    float distanceSquared = (humming_x - honeycomb2_x[i]) * (humming_x - honeycomb2_x[i]) + 
                            (humming_y - honeycomb2_y[i]) * (humming_y - honeycomb2_y[i]);

    // Check if the honeycomb exists
    if (honeycomb2_exists[i]) {
        // Check which tier the honeycomb is in and assign the score
        if (honeycomb2_y[i] <= (tierHeight * 2)) { // First and second tiers
            if (distanceSquared < 1000.0f) { // If close enough, "eat" the honeycomb
                honeycomb2_exists[i] = false; // Mark honeycomb as "eaten"
                humming_dx = -humming_dx * 0.01f; // Bounce back after eating
                humming_dy = -humming_dy * 0.01f;
                score += 2000; // Score for first and second tiers
            }
        } else if (honeycomb2_y[i] > (tierHeight * 2) && honeycomb2_y[i] <= (tierHeight * 5)) { // Third, fourth, and fifth tiers
            if (distanceSquared < 1000) { // If close enough, "eat" the honeycomb
                honeycomb2_exists[i] = false; // Mark honeycomb as "eaten"
                humming_dx = -humming_dx * 0.01f; // Bounce back after eating
                humming_dy = -humming_dy * 0.01f;
                score += 1800; // Score for third, fourth, and fifth tiers
            }
        } else { // Lower tiers (sixth to eighth)
            if (distanceSquared < 1000) { // If close enough, "eat" the honeycomb
                honeycomb2_exists[i] = false; // Mark honeycomb as "eaten"
                humming_dx = -humming_dx * 0.01f; // Bounce back after eating
                humming_dy = -humming_dy * 0.01f;
                score += 1500; // Score for lower tiers
            }
        }
    }
}

// Set the position of the hummingbird
hummingSprite.setPosition(humming_x, humming_y);

}
  void BossLevel(int& score){
   
  int    maxEnemies = 20;
     int   maxHoneycomb = 10;
      int  killerEnemies = 10;
      float  EnemySpeed = 0.4f;
      int maxBeeHives = 5;
      int maxSprays = 3;
     float humming_dx = 0.4f; // Initial horizontal speed
    float humming_dy = 0.4f; // Initial vertical speed
    int bulletsFired = 0;
    const int maxBullets = 58;
    bool state[maxEnemies] = {false};
    bool state2[killerEnemies] = {false};
    float enemy_x[maxEnemies], enemy_y[maxEnemies];
    float new_x[maxEnemies], new_y[maxEnemies];
    Sprite enemySprites[maxEnemies];
    float moveDownStart[maxEnemies] = {0};
    bool isMovingDown[maxEnemies] = {false};
    int direction[maxEnemies];
    Texture enemyTexture;
    float enemy2_x[killerEnemies] , enemy2_y[killerEnemies];
        Sprite enemy2Sprite[killerEnemies];
     float  honeycomb2_x[killerEnemies];
       float honeycomb2_y[killerEnemies];
    float flower_x[maxEnemies], flower_y[maxEnemies];
    bool honeycomb_exists[maxEnemies] = {false};
    bool honeycomb2_exists[killerEnemies] = {false};
    bool hiveExist[maxEnemies] = {false};
    bool obstaclesExists[maxEnemies] = {false};
    Text scoreText;
    Text bulletstext;
    Font font;
    float bullets_x[maxBullets], bullets_y[maxBullets];
    bool bullets_exists[maxBullets];
    Sprite bulletSprites[maxBullets];
     int honeyBeeDeactivated = 0;
     bool canBeGenerated[maxBeeHives] = {false};
     bool isMovetoNextLevel = false;
          // credentials of the infant bee 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
  
   float* infantBee_x = nullptr;  //  for x-coordinates
   float* infantBee_y = nullptr;  //  for y-coordinates
   bool* infantBeeExists = nullptr;  // to track active bees
   Sprite* infantBeeSprites = nullptr;  //  for Infant Bee sprites
   int numInfantBees = 0;  // Number of active Infant Bees
   Clock infantBeeClock;  // clock for the bees to respawn
float power_x[100] , power_y[100];
                 bool power_exists[100] = {false};    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    
  int level = 4;
        
 RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers Boss Level", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(300, 200));
    displayLevelStart( window, level);    
     Music bgMusic;
    if (!bgMusic.openFromFile("Forest.ogg")) {
        cout << "Failed to load background music!" << endl;
        return;
    }
    bgMusic.setLoop(true);
    bgMusic.play();
    bgMusic.setVolume(50);
          
    Texture playerTexture, bulletTexture, hummingTexture, honeycombTexture, lavaTexture, hiveTexture, flowerTexture , enemy2Texture , honeycomb2Texture , infantBeeTexture , power1 , power2 , power3 , power4;
    if (!loadTextures3( playerTexture,bulletTexture , enemyTexture, hummingTexture , honeycombTexture, hiveTexture , flowerTexture , enemy2Texture , honeycomb2Texture)) {
        return;
    }
    if (!loadTexture2(lavaTexture)) {
        return;
    }
if (!loadTextureinfantBee(infantBeeTexture)) {
        return;
    }
    if (!loadFont(font)) {
        cout << "Failed to load font!" << endl;
        return ;
    }
    
 if(!loadTexturepower(power1 , power2 , power3 , power4)){
    cout<<" Failed to load power textures"<<endl;
    return;
    }
    Texture powers[4] = {power1 , power2 , power3 , power4};
       
     Sprite background(lavaTexture);
    background.setTextureRect(IntRect(0, 0, resolutionX, resolutionY));

    float maxSpray_x[maxSprays], maxSpray_y[maxSprays];
    Sprite maxSprite[maxSprays];
    initializesprays(maxSpray_x, maxSpray_y, maxSprite, playerTexture, maxSprays);
      
    float player_x, player_y;
    Sprite playerSprite;
    initializePlayer(playerSprite, player_x, player_y, playerTexture);

    RectangleShape groundRectangle(Vector2f(resolutionX , 110));
    groundRectangle.setPosition(0, resolutionY - 110);
    groundRectangle.setFillColor(Color::Green);

    float honeycomb_x[maxHoneycomb], honeycomb_y[maxHoneycomb];
    Sprite honeycombSprite[maxHoneycomb];
   initializeHoneycomb( bullets_x,  bullets_y,  honeycomb_x, honeycomb_y, 
                           honeycombSprite, honeycombTexture, maxHoneycomb, 
                           new_x, new_y, honeycomb_exists, 
                           resolutionX,  resolutionY);
  float beeHive_x[maxBeeHives] , beeHive_y[maxBeeHives];
      Sprite beeHiveSprite[maxBeeHives]; 
      initializeBeeHives(beeHive_x , beeHive_y ,honeycomb_x ,honeycomb_y , beeHiveSprite , hiveTexture , canBeGenerated , maxBeeHives);
    float humming_x, humming_y;
    Sprite hummingSprite;
    initializeHummingbird(humming_x, humming_y, hummingSprite, hummingTexture);

    initializeBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, bulletTexture);
    initializeEnemy2(enemy2_x , enemy2_y , enemy2Sprite , enemy2Texture , killerEnemies);
    initializeEnemies(enemy_x, enemy_y, enemySprites, enemyTexture, maxEnemies, resolutionX, resolutionY);
        
    for (int i = 0; i < maxEnemies; ++i) {
        direction[i] = (rand() % 2 == 0) ? 1 : -1;
    }
        Clock bulletClock;
        
      while (window.isOpen() && !isMovetoNextLevel ) {
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) {
            window.close();
        }
    }
      // 1. Check Level Transition or Game Over
    if (honeyBeeDeactivated >= 30) {
        // Player has cleared the level
       isMovetoNextLevel = true;  // Exit the loop and move to the next level
        continue;                 // Skip the rest of the frame logic
    } else if (maxSprays == 0) {
        // Player has lost all sprays
        cout << "Game Over" << endl;
        isMovetoNextLevel = true;  // Exit the loop
        continue;                 // Skip the rest of the frame logic
    }
    
    // creating the clock to manage the bee movment
    if (infantBeeClock.getElapsedTime().asSeconds() > 10.0f) {  // Respawning the bees  after every 10 seconds
    createInfantBee(beeHive_x, beeHive_y, honeycomb_x, honeycomb_y, 
                    maxBeeHives, maxHoneycomb, infantBeeTexture, 
                    numInfantBees, infantBee_x, infantBee_y, 
                    infantBeeExists, infantBeeSprites);
    infantBeeClock.restart();
}
   handleBulletFiring(bullets_x, bullets_y, bullets_exists, player_x, player_y, bulletClock, bulletSprites, maxBullets, bulletsFired);
        updateBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, maxBullets);
        
 updateInfantBee( infantBee_x, infantBee_y, infantBeeExists, numInfantBees, infantBeeSprites,  EnemySpeed, direction , moveDownStart, isMovingDown, boxPixelsX ,enemy2Texture , state2);
              
          checkBulletCollisionForInfant( bullets_x , bullets_y , infantBee_x , infantBee_y, infantBeeExists, numInfantBees, infantBeeSprites,  EnemySpeed , honeycomb2Texture , state2 , score , bullets_exists , honeycomb2_exists , honeycomb2_y , honeycomb2_x , powers ,power_exists, power_y,  power_x) ;
 
        // Update honeycomb state
        updateHoneyComb(bullets_x, bullets_y, honeycomb_x, honeycomb_y, honeycombSprite, 
                        honeycombTexture, maxHoneycomb, new_x, new_y, honeycomb_exists, 
                       bullets_exists, maxBullets );

        // Update enemies and collisions
        for (int i = 0; i < maxEnemies; ++i) {
            checkCollision(bullets_x, bullets_y, new_x[i], new_y[i], bullets_exists,
                           enemy_x[i], enemy_y[i], enemySprites[i], honeycombTexture,
                           state[i], honeycomb_exists[i], hiveExist[i], hiveTexture,
                          beeHive_x[i], beeHive_y[i], maxEnemies, score, obstaclesExists[i], flowerTexture ,honeyBeeDeactivated);
        }    
        for(int i = 0 ; i < killerEnemies ; i++){
          handleKillerBeeCollision( bullets_x, bullets_y,  bullets_exists, 
                              enemy2_x[i],  enemy2_y[i], enemy2Sprite[i],honeycomb2Texture, 
                             honeycomb2_x[i],  honeycomb2_y[i], 
                          honeyBeeDeactivated , killerEnemies , state2[i] , score , honeycomb2_exists[i]);
              }
        
              
                      for(int i = 0; i < killerEnemies ; i++){       
           handleKillerBeeMovement( enemy2_x[i], enemy2_y[i],honeycomb2_x[i], honeycomb2_y[i], enemy2Sprite[i], direction[i], 
               moveDownStart[i], isMovingDown[i], boxPixelsX , 
                obstaclesExists[i],flower_x[i],  flower_y[i] , EnemySpeed , state2[i]);
               }      
        // Check obstacles
        checkObstacles(enemy_x, enemy_y, flowerTexture, obstaclesExists, enemySprites, resolutionY, resolutionX, flower_x, flower_y , honeyBeeDeactivated);
               checkObstaclesforEnemy2(enemy2_x, enemy2_y, flowerTexture, obstaclesExists, enemy2Sprite, resolutionY, resolutionX, flower_x, flower_y , honeyBeeDeactivated);
        // Update hummingbird
        updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                          resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb_exists, new_x, new_y, maxEnemies, score );
                          
                          updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                          resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb2_exists, honeycomb2_x, honeycomb2_y, killerEnemies, score );
                             
        // Reset bullets if maxSprays is exceeded
        if (bulletsFired > 57) {
    maxSprays = max(maxSprays - 1, 0); // Ensure sprays don't go negative
    bulletsFired = 0;
}

             for (int i = 0; i < maxEnemies; ++i) {
            updateEnemy(enemy_x[i], enemy_y[i], new_x[i], new_y[i], enemySprites[i],
                        direction[i], moveDownStart[i], isMovingDown[i], 2*boxPixelsX, state[i],
                        obstaclesExists[i], flower_x[i], flower_y[i] , EnemySpeed);
        }
        
         
       
         handlePlayerMovement( player_x, player_y, flower_x,  flower_y,  obstaclesExists, maxEnemies);
         DisplayRemainingBullets( bulletstext , bulletsFired , font );
        // Update score
        displayScore(scoreText, score, font, resolutionX, resolutionY, boxPixelsX, boxPixelsY);     
            
        // Clear the window and draw all entities
        window.clear();

        // Draw background and ground
        window.draw(background);
        window.draw(groundRectangle);

        // Draw player
        playerSprite.setPosition(player_x, player_y);
        playerSprite.setScale(1.8f, 1.8f);
        window.draw(playerSprite);

        // Draw bullets
        for (int i = 0; i < maxBullets; ++i) {
            if (bullets_exists[i]) {
                window.draw(bulletSprites[i]);
            }
      }

        // Draw honeycombs
        for (int i = 0; i < maxHoneycomb; ++i) {
            if (honeycomb_exists[i]) {  // Only draw existing honeycombs
                window.draw(honeycombSprite[i]);
            }
        }
        // draw beeHives
        for(int i = 0 ; i< maxBeeHives ; i++){
        window.draw(beeHiveSprite[i]);
        }
        
        // Draw enemies
        for (int i = 0; i < maxEnemies; ++i) {
            if (!state[i] || honeycomb_exists[i] || hiveExist[i] || obstaclesExists[i]) {
                window.draw(enemySprites[i]);
            }
        }
            
            // Draw enemies
        for (int i = 0; i < killerEnemies; ++i) {
            if (!state2[i] || honeycomb2_exists[i] || hiveExist[i] || obstaclesExists[i]) {
                window.draw(enemy2Sprite[i]);
            }
        }
           
           for (int i = 0; i < numInfantBees; ++i) {
    if (infantBeeExists[i] ||state2[i] || honeycomb2_exists[i] ||  power_exists[i]) {
        window.draw(infantBeeSprites[i]);
    }
}

            
        // Draw sprays
        for (int i = 0; i < maxSprays - 1; ++i) {
            maxSprite[i].setPosition(maxSpray_x[i], maxSpray_y[i]);
            maxSprite[i].setScale(1.8f, 1.8f);
            window.draw(maxSprite[i]);
        }

        // Draw score and hummingbird
        window.draw(bulletstext);
        window.draw(scoreText);
        window.draw(hummingSprite);
        
        

        // Display the frame
        window.display();
    }
    if(honeyBeeDeactivated >= 30){
    window.close();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const string fileName = "highscores.txt";
      int MAX_SCORES = 5;
    int highScores[MAX_SCORES];
    int scoreCount = 0;

    loadHighScores(highScores, scoreCount, fileName);
    // Add the current score if it's higher than the lowest score or the list isn't full
    if (scoreCount < MAX_SCORES || score > highScores[scoreCount - 1]) {
        if (scoreCount < MAX_SCORES) {
            highScores[scoreCount++] = score;
        } else {
            highScores[scoreCount - 1] = score;
        }
        sortHighScores(highScores, scoreCount);
       saveHighScores(highScores, scoreCount, fileName);
    } 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
    cout<<"Congratulations you completed the game"<<endl;
    }else if(maxSprays == 0){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const string fileName = "highscores.txt";
      int MAX_SCORES = 5;
    int highScores[MAX_SCORES];
    int scoreCount = 0;

    loadHighScores(highScores, scoreCount, fileName);

    // Add the current score if it's higher than the lowest score or the list isn't full
    if (scoreCount < MAX_SCORES || score > highScores[scoreCount - 1]) {
        if (scoreCount < MAX_SCORES) {
            highScores[scoreCount++] = score;
        } else {
            highScores[scoreCount - 1] = score;
        }
        sortHighScores(highScores, scoreCount);
        saveHighScores(highScores, scoreCount, fileName);
    } 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

    cout<<"unfortunately you lost the Game!"<<endl;
    
    	}
    		}
    		//	}
  
void playLevel3(int& score){        
              
         int    maxEnemies = 20;
     int   maxHoneycomb = 15;
      int  killerEnemies = 10;
      float  EnemySpeed = 0.4f;
      int maxSprays = 3;
        // Adjust maxSprays based on score
        if (score >= 20000 && score < 40000) {
          int  maxSprays = 4;
        } else if (score >= 40000 && score < 80000) {
          int  maxSprays = 5;
        } else if (score >= 80000) {
          int  maxSprays = 6 + (score - 80000) / 80000;
        }else{
         int maxSprays = 3;
         } 
    float humming_dx = 0.4f; // Initial horizontal speed
    float humming_dy = 0.4f; // Initial vertical speed
    int bulletsFired = 0;
    const int maxBullets = 58;
    bool state[maxEnemies] = {false};
    bool state2[killerEnemies] = {false};
    float enemy_x[maxEnemies], enemy_y[maxEnemies];
    float new_x[maxEnemies], new_y[maxEnemies];
    float hive_x[maxEnemies], hive_y[maxEnemies];
    Sprite enemySprites[maxEnemies];
    float moveDownStart[maxEnemies] = {0};
    bool isMovingDown[maxEnemies] = {false};
    int direction[maxEnemies];
    Texture enemyTexture;
    float enemy2_x[killerEnemies] , enemy2_y[killerEnemies];
        Sprite enemy2Sprite[killerEnemies];
      float  honeycomb2_x[killerEnemies];
       float honeycomb2_y[killerEnemies];
    float flower_x[maxEnemies], flower_y[maxEnemies];
    bool honeycomb_exists[maxEnemies] = {false};
    bool honeycomb2_exists[killerEnemies] = {false};
    bool hiveExist[maxEnemies] = {false};
    bool obstaclesExists[maxEnemies] = {false};
    Text scoreText;
    Text bulletstext;
    Font font;
    float bullets_x[maxBullets], bullets_y[maxBullets];
    bool bullets_exists[maxBullets];
    Sprite bulletSprites[maxBullets];
     int honeyBeeDeactivated = 0;
    int level = 3;
    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers Level 3", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(300, 200));
    Music bgMusic;
    if (!bgMusic.openFromFile("Forest.ogg")) {
        cout << "Failed to load background music!" << endl;
        return;
    }
    bgMusic.setLoop(true);
    bgMusic.play();
    bgMusic.setVolume(50);
          
    Texture playerTexture, bulletTexture, hummingTexture, honeycombTexture, lavaTexture, hiveTexture, flowerTexture , enemy2Texture , honeycomb2Texture;
    if (!loadTextures3( playerTexture,bulletTexture , enemyTexture, hummingTexture , honeycombTexture, hiveTexture , flowerTexture , enemy2Texture , honeycomb2Texture)) {
        return;
    }
    if (!loadTexture2(lavaTexture)) {
        return;
    }

    if (!loadFont(font)) {
        cout << "Failed to load font!" << endl;
        return ;
    }

    Sprite background(lavaTexture);
    background.setTextureRect(IntRect(0, 0, resolutionX, resolutionY));

    float maxSpray_x[maxSprays], maxSpray_y[maxSprays];
    Sprite maxSprite[maxSprays];
    initializesprays(maxSpray_x, maxSpray_y, maxSprite, playerTexture, maxSprays);

    float player_x, player_y;
    Sprite playerSprite;
    initializePlayer(playerSprite, player_x, player_y, playerTexture);

    RectangleShape groundRectangle(Vector2f(resolutionX , 110));
    groundRectangle.setPosition(0, resolutionY - 110);
    groundRectangle.setFillColor(Color::Green);

    float honeycomb_x[maxHoneycomb], honeycomb_y[maxHoneycomb];
    Sprite honeycombSprite[maxHoneycomb];
   initializeHoneycomb( bullets_x,  bullets_y,  honeycomb_x, honeycomb_y, 
                           honeycombSprite, honeycombTexture, maxHoneycomb, 
                           new_x, new_y, honeycomb_exists, 
                           resolutionX,  resolutionY);
  
    float humming_x, humming_y;
    Sprite hummingSprite;
    initializeHummingbird(humming_x, humming_y, hummingSprite, hummingTexture);

    initializeBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, bulletTexture);
    initializeEnemy2(enemy2_x , enemy2_y , enemy2Sprite , enemy2Texture , killerEnemies);
    initializeEnemies(enemy_x, enemy_y, enemySprites, enemyTexture, maxEnemies, resolutionX, resolutionY);

    for (int i = 0; i < maxEnemies; ++i) {
        direction[i] = (rand() % 2 == 0) ? 1 : -1;
    }
        Clock bulletClock;
     bool isMovetoNextLevel = false; 
       while (window.isOpen() && !isMovetoNextLevel) {
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) {
            window.close();
        }
    }
        // 1. Check Level Transition or Game Over
    if (honeyBeeDeactivated >= 30) {
        // Player has cleared the level
       isMovetoNextLevel = true;  // Exit the loop and move to the next level
        continue;                 // Skip the rest of the frame logic
    } else if (maxSprays == 0) {
        // Player has lost all sprays
        cout << "Game Over" << endl;
        isMovetoNextLevel = true;  // Exit the loop
        continue;                 // Skip the rest of the frame logic
    }
              
                handleBulletFiring(bullets_x, bullets_y, bullets_exists, player_x, player_y, bulletClock, bulletSprites, maxBullets, bulletsFired);
        updateBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, maxBullets);

        // Update honeycomb state
        updateHoneyComb(bullets_x, bullets_y, honeycomb_x, honeycomb_y, honeycombSprite, 
                        honeycombTexture, maxHoneycomb, new_x, new_y, honeycomb_exists, 
                       bullets_exists, maxBullets);

        // Update enemies and collisions
        for (int i = 0; i < maxEnemies; ++i) {
            checkCollision(bullets_x, bullets_y, new_x[i], new_y[i], bullets_exists,
                           enemy_x[i], enemy_y[i], enemySprites[i], honeycombTexture,
                           state[i], honeycomb_exists[i], hiveExist[i], hiveTexture,
                           hive_x[i], hive_y[i], maxEnemies, score, obstaclesExists[i], flowerTexture ,honeyBeeDeactivated);
        }    
        for(int i = 0 ; i < killerEnemies ; i++){
          handleKillerBeeCollision( bullets_x, bullets_y,  bullets_exists, 
                              enemy2_x[i],  enemy2_y[i], enemy2Sprite[i],honeycomb2Texture, 
                             honeycomb2_x[i],  honeycomb2_y[i], 
                          honeyBeeDeactivated , killerEnemies , state2[i] , score , honeycomb2_exists[i]);
              }
        
              
                      for(int i = 0; i < killerEnemies ; i++){       
           handleKillerBeeMovement( enemy2_x[i], enemy2_y[i],honeycomb2_x[i], honeycomb2_y[i], enemy2Sprite[i], direction[i], 
               moveDownStart[i], isMovingDown[i], boxPixelsX , 
                obstaclesExists[i],flower_x[i],  flower_y[i] , EnemySpeed , state2[i]);
               }      
        // Check obstacles
        checkObstacles(enemy_x, enemy_y, flowerTexture, obstaclesExists, enemySprites, resolutionY, resolutionX, flower_x, flower_y , honeyBeeDeactivated);
               checkObstaclesforEnemy2(enemy2_x, enemy2_y, flowerTexture, obstaclesExists, enemy2Sprite, resolutionY, resolutionX, flower_x, flower_y , honeyBeeDeactivated);
        // Update hummingbird
        updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                          resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb_exists, new_x, new_y, maxEnemies, score );
                          
                          updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                          resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb2_exists, honeycomb2_x, honeycomb2_y, killerEnemies, score );
                          
        // Reset bullets if maxSprays is exceeded
        if (bulletsFired > 57) {
    maxSprays = max(maxSprays - 1, 0); // Ensure sprays don't go negative
    bulletsFired = 0;
}

             for (int i = 0; i < maxEnemies; ++i) {
            updateEnemy(enemy_x[i], enemy_y[i], new_x[i], new_y[i], enemySprites[i],
                        direction[i], moveDownStart[i], isMovingDown[i], 2*boxPixelsX, state[i],
                        obstaclesExists[i], flower_x[i], flower_y[i] , EnemySpeed);
        }
        DisplayRemainingBullets( bulletstext , bulletsFired , font );
        
         
       
         handlePlayerMovement( player_x, player_y, flower_x,  flower_y,  obstaclesExists, maxEnemies);
        // Update score
        displayScore(scoreText, score, font, resolutionX, resolutionY, boxPixelsX, boxPixelsY);
         
            
        // Clear the window and draw all entities
        window.clear();

        // Draw background and ground
        window.draw(background);
        window.draw(groundRectangle);

        // Draw player
        playerSprite.setPosition(player_x, player_y);
        playerSprite.setScale(1.8f, 1.8f);
        window.draw(playerSprite);

        // Draw bullets
        for (int i = 0; i < maxBullets; ++i) {
            if (bullets_exists[i]) {
                window.draw(bulletSprites[i]);
            }
      }

        // Draw honeycombs
        for (int i = 0; i < maxHoneycomb; ++i) {
            if (honeycomb_exists[i]) {  // Only draw existing honeycombs
                window.draw(honeycombSprite[i]);
            }
        }
        
        // Draw enemies
        for (int i = 0; i < maxEnemies; ++i) {
            if (!state[i] || honeycomb_exists[i] || hiveExist[i] || obstaclesExists[i]) {
                window.draw(enemySprites[i]);
            }
        }
            
            // Draw enemies
        for (int i = 0; i < killerEnemies; ++i) {
            if (!state2[i] || honeycomb2_exists[i] || hiveExist[i] || obstaclesExists[i]) {
                window.draw(enemy2Sprite[i]);
            }
        }

            
        // Draw sprays
        for (int i = 0; i < maxSprays; ++i) {
            maxSprite[i].setPosition(maxSpray_x[i], maxSpray_y[i]);
            maxSprite[i].setScale(1.8f, 1.8f);
            window.draw(maxSprite[i]);
        }

        // Draw score and hummingbird
        window.draw(bulletstext);
        window.draw(scoreText);
        window.draw(hummingSprite);
        
        

        // Display the frame
        window.display();
    }
    
    
    if (honeyBeeDeactivated >= 30) {
  window.close();
  BossLevel(score);
} else if (maxSprays == 0) {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const string fileName = "highscores.txt";
      int MAX_SCORES = 5;
    int highScores[MAX_SCORES];
    int scoreCount = 0;

    loadHighScores(highScores, scoreCount, fileName);

    // Add the current score if it's higher than the lowest score or the list isn't full
    if (scoreCount < MAX_SCORES || score > highScores[scoreCount - 1]) {
        if (scoreCount < MAX_SCORES) {
            highScores[scoreCount++] = score;
        } else {
            highScores[scoreCount - 1] = score;
        }
        sortHighScores(highScores, scoreCount);
       saveHighScores(highScores, scoreCount, fileName);
    } 
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
    cout << "You lost the game!" << endl;
         }
         }


void playLevel2(int& score){
    
         int    maxEnemies = 15;
     int   maxHoneycomb = 2;
      int  killerEnemies = 5;
      float  EnemySpeed = 0.5f;
      int maxSprays = 3;
        // Adjust maxSprays based on score
        if (score >= 20000 && score < 40000) {
          int  maxSprays = 4;
        } else if (score >= 40000 && score < 80000) {
          int  maxSprays = 5;
        } else if (score >= 80000) {
          int  maxSprays = 6 + (score - 80000) / 80000;
        } 
    float humming_dx = 0.4f; // Initial horizontal speed
    float humming_dy = 0.4f; // Initial vertical speed
    int bulletsFired = 0;
    const int maxBullets = 58;
    bool state[maxEnemies] = {false};
    bool state2[killerEnemies] = {false};
    float enemy_x[maxEnemies], enemy_y[maxEnemies];
    float new_x[maxEnemies], new_y[maxEnemies];
    float hive_x[maxEnemies], hive_y[maxEnemies];
    Sprite enemySprites[maxEnemies];
    float moveDownStart[maxEnemies] = {0};
    bool isMovingDown[maxEnemies] = {false};
    int direction[maxEnemies];
    Texture enemyTexture;
    float enemy2_x[killerEnemies] , enemy2_y[killerEnemies];
        Sprite enemy2Sprite[killerEnemies];
      float  honeycomb2_x[killerEnemies];
       float honeycomb2_y[killerEnemies];
    float flower_x[maxEnemies], flower_y[maxEnemies];
    bool honeycomb_exists[maxEnemies] = {false};
    bool honeycomb2_exists[killerEnemies] = {false};
    bool hiveExist[maxEnemies] = {false};
    bool obstaclesExists[maxEnemies] = {false};
    Text scoreText;
    Text bulletstext;
    Font font;
    float bullets_x[maxBullets], bullets_y[maxBullets];
    bool bullets_exists[maxBullets];
    Sprite bulletSprites[maxBullets];
     int honeyBeeDeactivated = 0;      
    int level = 2;     
  RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers Level 2", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(300, 200));
     displayLevelStart( window, level);
    Music bgMusic;
    if (!bgMusic.openFromFile("Forest.ogg")) {
        cout << "Failed to load background music!" << endl;
        return;
    }
    bgMusic.setLoop(true);
    bgMusic.play();
    bgMusic.setVolume(50);
          
    Texture playerTexture, bulletTexture, hummingTexture, honeycombTexture, lavaTexture, hiveTexture, flowerTexture , enemy2Texture , honeycomb2Texture;
    if (!loadTextures3( playerTexture,bulletTexture , enemyTexture, hummingTexture , honeycombTexture, hiveTexture , flowerTexture , enemy2Texture , honeycomb2Texture)) {
        return;
    }
    if (!loadTexture2(lavaTexture)) {
        return;
    }

    if (!loadFont(font)) {
        cout << "Failed to load font!" << endl;
        return ;
    }

    Sprite background(lavaTexture);
    background.setTextureRect(IntRect(0, 0, resolutionX, resolutionY));

    float maxSpray_x[maxSprays], maxSpray_y[maxSprays];
    Sprite maxSprite[maxSprays];
    initializesprays(maxSpray_x, maxSpray_y, maxSprite, playerTexture, maxSprays);

    float player_x, player_y;
    Sprite playerSprite;
    initializePlayer(playerSprite, player_x, player_y, playerTexture);

    RectangleShape groundRectangle(Vector2f(resolutionX , 110));
    groundRectangle.setPosition(0, resolutionY - 110);
    groundRectangle.setFillColor(Color::Green);

    float honeycomb_x[maxHoneycomb], honeycomb_y[maxHoneycomb];
    Sprite honeycombSprite[maxHoneycomb];
   initializeHoneycomb( bullets_x,  bullets_y,  honeycomb_x, honeycomb_y, 
                           honeycombSprite, honeycombTexture, maxHoneycomb, 
                           new_x, new_y, honeycomb_exists, 
                           resolutionX,  resolutionY);
  
    float humming_x, humming_y;
    Sprite hummingSprite;
    initializeHummingbird(humming_x, humming_y, hummingSprite, hummingTexture);

    initializeBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, bulletTexture);
    initializeEnemy2(enemy2_x , enemy2_y , enemy2Sprite , enemy2Texture , killerEnemies);
    initializeEnemies(enemy_x, enemy_y, enemySprites, enemyTexture, maxEnemies, resolutionX, resolutionY);

    for (int i = 0; i < maxEnemies; ++i) {
        direction[i] = (rand() % 2 == 0) ? 1 : -1;
    }
        Clock bulletClock;
     bool isMovetoNextLevel = false; 
       while (window.isOpen() && !isMovetoNextLevel) {
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) {
            window.close();
        }
    }
        // 1. Check Level Transition or Game Over
    if (honeyBeeDeactivated >= 20) {
        // Player has cleared the level
       isMovetoNextLevel = true;  // Exit the loop and move to the next level
        continue;                 // Skip the rest of the frame logic
    } else if (maxSprays == 0) {
        // Player has lost all sprays
        cout << "Game Over" << endl;
        isMovetoNextLevel = true;  // Exit the loop
        continue;                 // Skip the rest of the frame logic
    }
              
                handleBulletFiring(bullets_x, bullets_y, bullets_exists, player_x, player_y, bulletClock, bulletSprites, maxBullets, bulletsFired);
        updateBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, maxBullets);

        // Update honeycomb state
        updateHoneyComb(bullets_x, bullets_y, honeycomb_x, honeycomb_y, honeycombSprite, 
                        honeycombTexture, maxHoneycomb, new_x, new_y, honeycomb_exists, 
                       bullets_exists, maxBullets);

        // Update enemies and collisions
        for (int i = 0; i < maxEnemies; ++i) {
            checkCollision(bullets_x, bullets_y, new_x[i], new_y[i], bullets_exists,
                           enemy_x[i], enemy_y[i], enemySprites[i], honeycombTexture,
                           state[i], honeycomb_exists[i], hiveExist[i], hiveTexture,
                           hive_x[i], hive_y[i], maxEnemies, score, obstaclesExists[i], flowerTexture ,honeyBeeDeactivated);
        }    
        for(int i = 0 ; i < killerEnemies ; i++){
          handleKillerBeeCollision( bullets_x, bullets_y,  bullets_exists, 
                              enemy2_x[i],  enemy2_y[i], enemy2Sprite[i],honeycomb2Texture, 
                             honeycomb2_x[i],  honeycomb2_y[i], 
                          honeyBeeDeactivated , killerEnemies , state2[i] , score , honeycomb2_exists[i]);
              }
        
              
                      for(int i = 0; i < killerEnemies ; i++){       
           handleKillerBeeMovement( enemy2_x[i], enemy2_y[i],honeycomb2_x[i], honeycomb2_y[i], enemy2Sprite[i], direction[i], 
               moveDownStart[i], isMovingDown[i], boxPixelsX , 
                obstaclesExists[i],flower_x[i],  flower_y[i] , EnemySpeed , state2[i]);
               }      
        // Check obstacles
        checkObstacles(enemy_x, enemy_y, flowerTexture, obstaclesExists, enemySprites, resolutionY, resolutionX, flower_x, flower_y , honeyBeeDeactivated);
               checkObstaclesforEnemy2(enemy2_x, enemy2_y, flowerTexture, obstaclesExists, enemy2Sprite, resolutionY, resolutionX, flower_x, flower_y , honeyBeeDeactivated);
        // Update hummingbird
        updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                          resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb_exists, new_x, new_y, maxEnemies, score );
                          
                          updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                          resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb2_exists, honeycomb2_x, honeycomb2_y, killerEnemies, score );
                          DisplayRemainingBullets( bulletstext , bulletsFired , font );
        // Reset bullets if maxSprays is exceeded
        if (bulletsFired > 57) {
    maxSprays = max(maxSprays - 1, 0); // Ensure sprays don't go negative
    bulletsFired = 0;
}

             for (int i = 0; i < maxEnemies; ++i) {
            updateEnemy(enemy_x[i], enemy_y[i], new_x[i], new_y[i], enemySprites[i],
                        direction[i], moveDownStart[i], isMovingDown[i], 2*boxPixelsX, state[i],
                        obstaclesExists[i], flower_x[i], flower_y[i] , EnemySpeed);
        }
        
         
       
         handlePlayerMovement( player_x, player_y, flower_x,  flower_y,  obstaclesExists, maxEnemies);
        // Update score
        displayScore(scoreText, score, font, resolutionX, resolutionY, boxPixelsX, boxPixelsY);
         
            
        // Clear the window and draw all entities
        window.clear();

        // Draw background and ground
        window.draw(background);
        window.draw(groundRectangle);

        // Draw player
        playerSprite.setPosition(player_x, player_y);
        playerSprite.setScale(1.8f, 1.8f);
        window.draw(playerSprite);

        // Draw bullets
        for (int i = 0; i < maxBullets; ++i) {
            if (bullets_exists[i]) {
                window.draw(bulletSprites[i]);
            }
      }

        // Draw honeycombs
        for (int i = 0; i < maxHoneycomb; ++i) {
            if (honeycomb_exists[i]) {  // Only draw existing honeycombs
                window.draw(honeycombSprite[i]);
            }
        }
        
        // Draw enemies
        for (int i = 0; i < maxEnemies; ++i) {
            if (!state[i] || honeycomb_exists[i] || hiveExist[i] || obstaclesExists[i]) {
                window.draw(enemySprites[i]);
            }
        }
            
            // Draw enemies
        for (int i = 0; i < killerEnemies; ++i) {
            if (!state2[i] || honeycomb2_exists[i] || hiveExist[i] || obstaclesExists[i]) {
                window.draw(enemy2Sprite[i]);
            }
        }

        // draw text
        
        window.draw(bulletstext);    
        // Draw sprays
        for (int i = 0; i < maxSprays - 1; ++i) {
            maxSprite[i].setPosition(maxSpray_x[i], maxSpray_y[i]);
            maxSprite[i].setScale(1.8f, 1.8f);
            window.draw(maxSprite[i]);
        }

        // Draw score and hummingbird
        window.draw(scoreText);
        window.draw(hummingSprite);
        
        

        // Display the frame
        window.display();
    }
    if (honeyBeeDeactivated >= 20) {
    // Move to Level 3
    window.close();
    playLevel3(score);
} else if (maxSprays == 0) {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
     const string fileName = "highscores.txt";
     int MAX_SCORES = 5;
    int highScores[MAX_SCORES];
    int scoreCount = 0;

    loadHighScores(highScores, scoreCount, fileName);

    // Add the current score if it's higher than the lowest score or the list isn't full
    if (scoreCount < MAX_SCORES || score > highScores[scoreCount - 1]) {
        if (scoreCount < MAX_SCORES) {
            highScores[scoreCount++] = score;
        } else {
            highScores[scoreCount - 1] = score;
        }
        sortHighScores(highScores, scoreCount);
         promptPlayerName( window,  font,  score, fileName);
         saveHighScores(highScores, scoreCount, fileName);
    }
     cout << "You lost the game!" << endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

         }
         }
void playLevel1(int& score){ 
       
                 // int score = 0;
            int maxEnemies = 20, maxHoneycomb = 3 , maxSprays = 3;
           float EnemySpeed = 0.3f;
    float humming_dx = 0.3f; // Initial horizontal speed
    float humming_dy = 0.3f; // Initial vertical speed
    int bulletsFired = 0;
    const int maxBullets = 58;
    bool state[maxEnemies] = {false};
    float enemy_x[maxEnemies], enemy_y[maxEnemies];
    float new_x[maxEnemies], new_y[maxEnemies];
    float hive_x[maxEnemies], hive_y[maxEnemies];
    Sprite enemySprites[maxEnemies];
    float moveDownStart[maxEnemies] = {0};
    bool isMovingDown[maxEnemies] = {false};
    int direction[maxEnemies];
    Texture enemyTexture;
    float flower_x[maxEnemies], flower_y[maxEnemies];
    bool honeycomb_exists[maxEnemies] = {false};
    bool hiveExist[maxEnemies] = {false};
    bool obstaclesExists[maxEnemies] = {false};
    Text scoreText;
    Text bulletstext;
    Font font;
    bool isMovetoNextLevel = false;
    float bullets_x[maxBullets], bullets_y[maxBullets];
    bool bullets_exists[maxBullets];
    Sprite bulletSprites[maxBullets];
     int honeyBeeDeactivated = 0;
int level = 1;
 RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(300, 200));
 displayLevelStart( window, level);
    Music bgMusic;
    if (!bgMusic.openFromFile("Forest.ogg")) {
        cout << "Failed to load background music!" << endl;
        return;
    }
    bgMusic.setLoop(true);
    bgMusic.play();
    bgMusic.setVolume(50);
          
    Texture playerTexture, bulletTexture, hummingTexture, honeycombTexture, lavaTexture, hiveTexture, flowerTexture;
    if (!loadTextures(playerTexture, bulletTexture, enemyTexture, hummingTexture, honeycombTexture, hiveTexture, flowerTexture)) {
        return;
    }
            if (!loadTexture2(lavaTexture)) {
        return;
    }

    if (!loadFont(font)) {
        cout << "Failed to load font!" << endl;
        return ;
    }

    Sprite background(lavaTexture);
    background.setTextureRect(IntRect(0, 0, resolutionX, resolutionY));

    float maxSpray_x[maxSprays], maxSpray_y[maxSprays];
    Sprite maxSprite[maxSprays];
    initializesprays(maxSpray_x, maxSpray_y, maxSprite, playerTexture, maxSprays);

    float player_x, player_y;
    Sprite playerSprite;
    initializePlayer(playerSprite, player_x, player_y, playerTexture);

    RectangleShape groundRectangle(Vector2f(resolutionX , 110));
    groundRectangle.setPosition(0, resolutionY - 110);
    groundRectangle.setFillColor(Color::Green);

    float honeycomb_x[maxHoneycomb], honeycomb_y[maxHoneycomb];
    Sprite honeycombSprite[maxHoneycomb];
   initializeHoneycomb( bullets_x,  bullets_y,  honeycomb_x, honeycomb_y, 
                           honeycombSprite, honeycombTexture, maxHoneycomb, 
                           new_x, new_y, honeycomb_exists, 
                           resolutionX,  resolutionY);

    float humming_x, humming_y;
    Sprite hummingSprite;
    initializeHummingbird(humming_x, humming_y, hummingSprite, hummingTexture);

    initializeBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, bulletTexture);
                   
    initializeEnemies(enemy_x, enemy_y, enemySprites, enemyTexture, maxEnemies, resolutionX, resolutionY);

    for (int i = 0; i < maxEnemies; ++i) {
        direction[i] = (rand() % 2 == 0) ? 1 : -1;
    }


        Clock bulletClock;
       
    while (window.isOpen() && !isMovetoNextLevel) {
    Event e;
    while (window.pollEvent(e)) {
        if (e.type == Event::Closed) {
            window.close();
        }
    }
    // 1. Check Level Transition or Game Over
    if (honeyBeeDeactivated >= 20) {
        // Player has cleared the level
        isMovetoNextLevel = true;  // Exit the loop and move to the next level
        continue;                 // Skip the rest of the frame logic
    } else if (maxSprays == 0) {
        // Player has lost all sprays
        cout << "Game Over" << endl;
        isMovetoNextLevel = true;  // Exit the loop
        continue;                 // Skip the rest of the frame logic
    }

    // 2. Update Game Logic
    handleBulletFiring(bullets_x, bullets_y, bullets_exists, player_x, player_y, bulletClock, bulletSprites, maxBullets, bulletsFired);
    updateBullets(bullets_x, bullets_y, bullets_exists, bulletSprites, maxBullets);

    updateHoneyComb(bullets_x, bullets_y, honeycomb_x, honeycomb_y, honeycombSprite, 
                    honeycombTexture, maxHoneycomb, new_x, new_y, honeycomb_exists, 
                    bullets_exists, maxBullets);

    for (int i = 0; i < maxEnemies; ++i) {
        checkCollision(bullets_x, bullets_y, new_x[i], new_y[i], bullets_exists,
                       enemy_x[i], enemy_y[i], enemySprites[i], honeycombTexture,
                       state[i], honeycomb_exists[i], hiveExist[i], hiveTexture,
                       hive_x[i], hive_y[i], maxEnemies, score, obstaclesExists[i], flowerTexture, honeyBeeDeactivated);
    }

    checkObstacles(enemy_x, enemy_y, flowerTexture, obstaclesExists, enemySprites, resolutionY, resolutionX, flower_x, flower_y, honeyBeeDeactivated);

    updateHummingbird(humming_x, humming_y, humming_dx, humming_dy, hummingSprite,
                      resolutionX, resolutionY, boxPixelsX, boxPixelsY, honeycomb_exists, new_x, new_y, maxEnemies, score);


    for (int i = 0; i < maxEnemies; ++i) {
        updateEnemy(enemy_x[i], enemy_y[i], new_x[i], new_y[i], enemySprites[i],
                    direction[i], moveDownStart[i], isMovingDown[i], 2 * boxPixelsX, state[i],
                    obstaclesExists[i], flower_x[i], flower_y[i], EnemySpeed);
    }

    handlePlayerMovement(player_x, player_y, flower_x, flower_y, obstaclesExists, maxEnemies);
         DisplayRemainingBullets( bulletstext , bulletsFired , font ); 
    // Update the score
    if (bulletsFired > 57 && maxSprays > 0) {
        maxSprays = maxSprays - 1; // Ensure sprays don't go negative
        bulletsFired = 0;
    }
    displayScore(scoreText, score, font, resolutionX, resolutionY, boxPixelsX, boxPixelsY);

    // 3. Draw Everything
    window.clear();

    // Draw background and ground
    window.draw(background);
    window.draw(groundRectangle);

    // Draw player
    playerSprite.setPosition(player_x, player_y);
    playerSprite.setScale(1.8f, 1.8f);
    window.draw(playerSprite);
     window.draw(bulletstext);
    // Draw bullets
    for (int i = 0; i < maxBullets; ++i) {
        if (bullets_exists[i]) {
            window.draw(bulletSprites[i]);
        }
    }

    // Draw honeycombs
    for (int i = 0; i < maxHoneycomb; ++i) {
        if (honeycomb_exists[i]) {
            window.draw(honeycombSprite[i]);
        }
    }

    // Draw enemies
    for (int i = 0; i < maxEnemies; ++i) {
        if (!state[i] || honeycomb_exists[i] || hiveExist[i] || obstaclesExists[i]) {
            window.draw(enemySprites[i]);
        }
    }

    // Draw sprays
    for (int i = 0; i < maxSprays-1; ++i) {
        maxSprite[i].setPosition(maxSpray_x[i], maxSpray_y[i]);
        maxSprite[i].setScale(1.8f, 1.8f);
        window.draw(maxSprite[i]);
    }
    // Draw score and hummingbird
    window.draw(scoreText);
    window.draw(hummingSprite);

    // Display everything
    window.display();
} 
if (honeyBeeDeactivated >= 20) {
    // Move to Level 2
    window.close();
    playLevel2(score);
} else if (maxSprays == 0) {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    const string fileName = "highscores.txt";
    int MAX_SCORES = 5;
    int highScores[MAX_SCORES];
    int scoreCount = 0;

    loadHighScores(highScores, scoreCount, fileName);

    // Add the current score if it's higher than the lowest score or the list isn't full
    if (scoreCount < MAX_SCORES || score > highScores[scoreCount - 1]) {
        if (scoreCount < MAX_SCORES) {
            highScores[scoreCount++] = score;
        } else {
            highScores[scoreCount - 1] = score;
        }
        sortHighScores(highScores, scoreCount);
        saveHighScores(highScores, scoreCount, fileName);
        promptPlayerName( window,  font,  score,  fileName);
    }
  cout << "You lost the game!" << endl;  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
    
}

}
// Function to create menu text
Text createMenuText(const string& content, Font& font, int size, Color color, float x, float y) {
    Text text;
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}

void showMenu(RenderWindow& window, Font& font, bool& isGamePaused, Texture& lavaTexture, int& score) {
   
    const string fileName = "highscores.txt";
      int MAX_SCORES = 5;
    int highScores[MAX_SCORES];
    int scoreCount = 0;

    loadHighScores(highScores, scoreCount, fileName);

    // Add the current score if it's higher than the lowest score or the list isn't full
    if (scoreCount < MAX_SCORES || score > highScores[scoreCount - 1]) {
        if (scoreCount < MAX_SCORES) {
            highScores[scoreCount++] = score;
        } else {
            highScores[scoreCount - 1] = score;
        }
        sortHighScores(highScores, scoreCount);
        saveHighScores(highScores, scoreCount, fileName);
        promptPlayerName( window,  font,  score, fileName);
    } 

    Text gameName = createMenuText("Buzz Bombers", font, 300, Color(60, 179, 113), resolutionX / 16, resolutionY - 1100);

    // Menu options and their positions
    Text menuOptions[7];
    menuOptions[0] = createMenuText("Start Game", font, 70, Color::White, resolutionX / 6, resolutionY - 700);
    menuOptions[1] = createMenuText("Highest Scores", font, 70, Color::White, resolutionX / 6, resolutionY - 600);
    menuOptions[2] = createMenuText("Level 2", font, 70, Color::White, resolutionX / 6, resolutionY - 500);
    menuOptions[3] = createMenuText("Level 3", font, 70, Color::White, resolutionX / 6, resolutionY - 400);
    menuOptions[4] = createMenuText("Boss Level", font, 70, Color::White, resolutionX / 6, resolutionY - 300);
    menuOptions[5] = createMenuText("Credits", font, 70, Color::White, resolutionX / 6, resolutionY - 200);
    menuOptions[6] = createMenuText("Quit" , font, 70, Color::White, resolutionX / 6, resolutionY - 100);
    int selectedIndex = 0; // Initially, highlight the first option

    // Create background sprite
    Sprite background(lavaTexture);
    background.setTextureRect(IntRect(0, 0, 1920, 1080));

    bool menuActive = true;

    while (menuActive) {
        // Highlight the selected option
        for (int i = 0; i < 7; ++i) {
            menuOptions[i].setFillColor(i == selectedIndex ? Color::Green : Color::White);
        }

        // Display the menu
        window.clear();
        window.draw(background);
        for (int i = 0; i < 7; ++i) {
            window.draw(menuOptions[i]);
        }
        window.draw(gameName);
        window.display();

        // Handle events
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
                menuActive = false;
            }

            // Handle keyboard navigation
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up) {
                    selectedIndex = (selectedIndex - 1 + 7) % 7; // Cycle upward
                } else if (e.key.code == Keyboard::Down) {
                    selectedIndex = (selectedIndex + 1) % 7; // Cycle downward
                } else if (e.key.code == Keyboard::Enter) {
                    // Perform action based on selected option
                    if (selectedIndex == 0) { // Start Game
                        menuActive = false;
                        isGamePaused = false; // Start the game
                        playLevel1(score);   // Call the playLevel1 function
                    } else if (selectedIndex == 1) { // Display high scores
                        window.clear();
                        window.draw(background);
                        for (int i = 0; i < scoreCount; ++i) {
                            Text scoreText = createMenuText(
                                "Score " + to_string(i + 1) + ": " + to_string(highScores[i]),
                                font, 50, Color::White, 400, 300 + i * 50
                            );
                            window.draw(scoreText);
                        }

                        // Create "Back" option to return to the menu
                        Text backText = createMenuText("Back", font, 70, Color::White, 400, 500 + scoreCount * 50);
                        window.draw(backText);
                        window.display();

                        bool waiting = true;
                        while (waiting) {
                            while (window.pollEvent(e)) {
                                if (e.type == Event::KeyPressed || e.type == Event::MouseButtonPressed) {
                                    waiting = false; // Exit high scores review
                                }
                            }
                        }
                    } else if (selectedIndex == 2) {  // Level 2
                        menuActive = false;
                        isGamePaused = false;
                        playLevel2(score);
                    } else if (selectedIndex == 3) {  // Level 3
                        menuActive = false;
                        isGamePaused = false;
                        playLevel3(score);
                    } else if (selectedIndex == 5) {  // Credits
                        window.clear();
                        window.draw(background);

                        // Display Credits with personalized message and high scores
                        Text creditsHeader = createMenuText("CREDITS", font, 80, Color::Cyan, 400, 100);
                        window.draw(creditsHeader);

 Text creditText = createMenuText("Producer & Owner: Mr. Muhammad Abdul Rafay - Please sir give good marks ",  font, 50, Color::Yellow, 200, 200);
                            window.draw(creditText);

                        // Create "Back" option to return to the menu with a highlight effect
                        Text backText = createMenuText("Back", font, 70, Color::Magenta, 400, 500 + scoreCount * 60);
                        window.draw(backText);

                        window.display();

                        bool waiting = true;
                        while (waiting) {
                            while (window.pollEvent(e)) {
                                if (e.type == Event::KeyPressed || e.type == Event::MouseButtonPressed) {
                                    waiting = false; // Exit credits
                                }
                            }
                        }
                    } else if (selectedIndex == 6) {  // Quit the game                  
                        window.close();
                        menuActive = false;
                    }else if(selectedIndex == 4){
                    BossLevel(score);
                    menuActive = false; 
                    
                    }
                }
            }

            // Handle mouse clicks
            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                for (int i = 0; i < 7; ++i) {
                    if (menuOptions[i].getGlobalBounds().contains(mousePos)) {
                        selectedIndex = i;
                        if (i == 0) { // Start Game
                            menuActive = false;
                            isGamePaused = false;
                            playLevel1(score);   // Call the playLevel1 function
                        } else if (i == 1) { // Display high scores
                            window.clear();
                            window.draw(background);
                            for (int j = 0; j < scoreCount; ++j) {
                                Text scoreText = createMenuText(
                                    "Score " + to_string(j + 1) + ": " + to_string(highScores[j]),
                                    font, 50, Color::White, 400, 300 + j * 50
                                );
                                window.draw(scoreText);
                            }

                            // Create "Back" option to return to the menu
                            Text backText = createMenuText("Back", font, 70, Color::White, 400, 500 + scoreCount * 50);
                            window.draw(backText);
                            window.display();

                            bool waiting = true;
                            while (waiting) {
                                while (window.pollEvent(e)) {
                                    if (e.type == Event::KeyPressed || e.type == Event::MouseButtonPressed) {
                                        waiting = false; // Exit high scores review
                                    }
                                }
                            }
                        } else if (i == 2) {  // Level 2
                            menuActive = false;
                            isGamePaused = false;
                            playLevel2(score);
                        } else if (i == 3) {  // Level 3
                            menuActive = false;
                            isGamePaused = false;
                            playLevel3(score);
                        } else if (i == 5) {  // Credits
                            window.clear();
                            window.draw(background);

                            // Display Credits with personalized message and high scores
                            Text creditsHeader = createMenuText("CREDITS", font, 80, Color::Cyan, 400, 100);
                            window.draw(creditsHeader);

                            for (int j = 0; j < scoreCount; ++j) {
                                Text creditText = createMenuText(
                                    "Producer & Owner: Mr. Muhammad Abdul Rafay - Please sir give good marks ",
                                    font, 50, Color::Yellow, 200, 200 );
                                window.draw(creditText);
                            }

                            // Create "Back" option to return to the menu with a highlight effect
                            Text backText = createMenuText("Back", font, 70, Color::Magenta, 400, 500 + scoreCount * 60);
                            window.draw(backText);

                            window.display();

                            bool waiting = true;
                            while (waiting) {
                                while (window.pollEvent(e)) {
                                    if (e.type == Event::KeyPressed || e.type == Event::MouseButtonPressed) {
                                        waiting = false; // Exit credits
                                    }
                                }
                            }
                        } else if (i == 6) {  // Quit the game
                            window.close();
                            menuActive = false;
                        }else if(i == 4 ){
                        
                        BossLevel(score);
                    menuActive = false; 
                        
                        }
                    }
                }
            }
        }
    }
 }   

int main() {

   srand(static_cast<unsigned int>(time(0)));
   int score = 0;
   Font font;
    if (!loadFont(font)) {
        cout << "Failed to load font!" << endl;
        return 0;
    }
     RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers Menu");
   bool isGamePaused;
    Texture lavaTexture;
    if (!loadTexture2(lavaTexture)) {
        return 0;
    }
           showMenu(window, font, isGamePaused , lavaTexture , score);
  return 0;
  }
