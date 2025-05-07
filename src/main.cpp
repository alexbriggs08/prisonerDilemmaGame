#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <random>
#include <ctime>
#include <string>

// function declarations
int friendAI();
void drawText(float x, float y, const std::string& text);
void renderScene();
void handleKey(unsigned char key, int x, int y);
void restartGame(int value);

// game states
enum GameState { INTRO, GAME, RESULT, EXIT };
GameState state = INTRO;

// game variables
int friendChoice = 0;
char playerChoice = 0;
std::string resultMessage;
int highScore = 0; // total time served

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(nullptr)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Prisoner's Dilemma");

    glClearColor(0.1, 0.1, 0.1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKey);
    glutMainLoop();
    return 0;
}

// generates AI's decision randomly
int friendAI() {
    return (rand() % 2) + 1;
}

// displays text on screen at a given position
void drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// this draws everything based on the current game state
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // show total years served at top-right
    std::string currentScore = "Total Years: " + std::to_string(highScore);
    drawText(0.55f, 0.9f, currentScore);


    if (state == INTRO) {
        drawText(-0.6f, 0.2f, "Prisoner's Dilemma - Are you ready? (Y/N)");
        drawText(-0.5f, -0.1f, "You can quit anytime by press Q");
    } else if (state == GAME) {
        drawText(-0.4f, 0.3f, "1. Stay Silent");
        drawText(-0.4f, 0.2f, "2. Talk");
        drawText(-0.4f, -0.2f, "Press 1 or 2 to choose");
        drawText(0.4f, -0.9f, "Q to Quit at anytime");
    } else if (state == RESULT) {
        drawText(-0.6f, 0.2f, resultMessage);
        drawText(0.4f, -0.9f, "Q to Quit at anytime");
    } else if (state == EXIT) {
        drawText(-0.3f, 0.0f, "Goodbye!");
        glutSwapBuffers();
        exit(0); // closes the game window
    }

    glutSwapBuffers();
}

// automatically restarts the game after result screen
void restartGame(int) {
    if (state == RESULT) {
        state = GAME;
        glutPostRedisplay();
    }
}

// handles key presses during different game states
void handleKey(unsigned char key, int x, int y) {
    if (state == INTRO) {
        if (key == 'y' || key == 'Y') {
            state = GAME;
        } else if (key == 'n' || key == 'N') {
            state = EXIT;
        }
    } else if (state == GAME) {
        if (key == '1' || key == '2') {
            playerChoice = key;
            friendChoice = friendAI();

            int years = 0;

            // figure out the outcome and how many years
            if (playerChoice == '1' && friendChoice == 1) {
                resultMessage = "Both stayed silent (1 year)";
                years = 1;
            } else if (playerChoice == '1') {
                resultMessage = "You silent, friend talked (10 years)";
                years = 10;
            } else if (playerChoice == '2' && friendChoice == 1) {
                resultMessage = "You talked, friend silent (0 years)";
                years = 0;
            } else {
                resultMessage = "Both talked (5 years)";
                years = 5;
            }

            highScore += years; // add to total counter
            state = RESULT;

            glutTimerFunc(2000, restartGame, 0); // restart after 2 seconds
        }
    }

    if (key == 'q' || key == 'Q') {
        state = EXIT;
    }

    glutPostRedisplay(); // refresh display
}
