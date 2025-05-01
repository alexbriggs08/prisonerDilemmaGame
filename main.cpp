#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

void introduction();
void gameMessage();
int friendAI();
int endScreen(int friendChoice, char playerChoice);

int main() {
    introduction();
    char introductionConformation;
    std::cin >> introductionConformation;
    while (true) {
        if (introductionConformation == 'y' || introductionConformation == 'Y') {
            gameMessage();
            char playerChoice;
            std::cin >> playerChoice;
            const int finalResult = endScreen(friendAI(), playerChoice);
            std::this_thread::sleep_for(std::chrono::seconds(1)); // adds a delay for restarting because its like hecka quick if you don't and looks buns.
            if (finalResult == -1) {
                break;
            }
        } else {
            std::cout << "Goodbye!";
            break;
        }
    }
    return 0;
}

void introduction() {
    std::cout << "Prisoners Dilemma. Choose to rat on your friend or stay silent. Are you ready? (Y/N) \n";
}

void gameMessage() {
    std::cout << "1. Stay Silent \n2. Talk \n";
}

int friendAI() {
    const std::vector<int> aiChoice = {1, 2}; // creates a list for the "AI" to choose from. This will be converted to text later in the code.
    std::random_device rd; // defines the random generators to pick from the list.
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    return aiChoice[dis(gen)]; // uses the previously defined generators and picks from the list.
}

int endScreen(const int friendChoice, const char playerChoice) {
    int result {};
    switch (playerChoice) {
        case '1': // Stay Silent (Player)
            if (friendChoice == 1) {
                // Player and AI stay quite
                std::cout << "You both kept quiet (1 year)\n";
                result = 1;
            } else {
                // AI talks
                std::cout << "Your friend talked (10 years)\n";
                result = 10;
            }
            break;
        case '2': // Talk (Player)
            if (friendChoice == 1) {
                // AI kept quite
                std::cout << "Your friend kept quiet (0 years)\n";
                result = 0;
            } else {
                // Player and AI talk
                std::cout << "You both talked (5 years)\n";
                result = 5;
            }
            break;
        default:
            std::cout << "Quitting...";
            result = -1;
            break;
    }
    return result;
}


