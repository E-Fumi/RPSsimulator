#include <iostream>
#include <time.h>
using namespace std;


bool isStringNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}


int determineNrOfRounds(string roundsInput)
{
    if (isStringNumber(roundsInput)) {
        if (stoi(roundsInput) > 0) {
            return stoi(roundsInput);
        }
    }
    cout << "It has to be a positive integer. Try again.\n";
    return 0;
}


int encodePlayerInput(string playerInput)
{
    if (playerInput.empty()){
        return -1;
    }
    switch(playerInput[0]) {
        case 'r':
        case 'R':
            return 0;
        case 'p':
        case 'P':
           return 1;
        case 's':
        case 'S':
            return 2;
        default:
            cout << "Choice not recognized. Try again.\n";
            return -1;
    }
}


int determineChoice(int roundWin, int lastPlayerChoice)
{
    switch(roundWin){
        case -1:
            return 1 + (lastPlayerChoice) % 3;
        case 1:
            return lastPlayerChoice;
        default:
            srand (time(NULL));
            return rand() % 3;
    }
}


string choiceDecoder(int choice)
{
    switch(choice) {
        case 0:
            return "rock";
        case 1:
            return "paper"; break;
        case 2:
            return "scissors"; break;
        default:
            return "undefined"; break;
    }
}


int determineWin(int algorithmChoice, int playerChoice)
{
    if (algorithmChoice == playerChoice){
        cout << "\nIt's a tie.\n";
        return 0;
    } else if (algorithmChoice == (playerChoice + 1) % 3){
        cout << "\nThe algorithm wins the round.\n";
        return 1;
    } else {
        cout << "\nYou win the round.\n";
        return -1; 
    }
}


void declareWin(int nrOfRounds, int totalWins, int ties)
{
    int wonRounds = nrOfRounds - ties;
    int algorithmWins = (wonRounds - abs(totalWins)) / 2 + max(0, totalWins);
    int humanWins = nrOfRounds - ties - algorithmWins;
    cout << "\nThe algorithm won " << algorithmWins << " rounds.";
    cout << "\nYou won " << humanWins << " rounds.";
    if (algorithmWins > humanWins){
        cout << "\n\nTHE ALGORITHM PREVAILS!";
    } else if (algorithmWins < humanWins){
        cout << "\n\nYOU WIN THE GAME!";
    } else {
        cout << "\n\nTHE GAME IS TIED\n";
    }
}


int main() {
    cout << "Welcome to Rock-Paper-Scissors Simulator\n\n";
    string roundsInput;
    string playerInput;
    int nrOfRounds = 0;
    int playerChoice = -1;
    int lastPlayerChoice = 0;
    int algorithmChoice = 0;
    int roundWin = 0;
    int totalWins = 0;
    int ties = 0;
  
    cout << "How many rounds would you like to play?\n\n";
    while (nrOfRounds == 0){
        cin >> roundsInput;
        nrOfRounds = determineNrOfRounds(roundsInput);
    }
    for (int i = 0; i < nrOfRounds; i++) {
        cout << "\nRound " << i + 1 << "/" << nrOfRounds << ":\n";
        algorithmChoice = determineChoice(roundWin, lastPlayerChoice);
        cout << "Choose your play.\n";
        while (playerChoice == -1){
            cin >> playerInput;
            playerChoice = encodePlayerInput (playerInput);
        }
        cout << "The algorithm chose " << choiceDecoder(algorithmChoice);
        cout << "\nYou chose " << choiceDecoder(playerChoice);
        roundWin = determineWin(algorithmChoice, playerChoice);
        if (roundWin == 0) {
            ties++;
        }
        totalWins = totalWins + roundWin;
        lastPlayerChoice = playerChoice;
        playerChoice = -1;
    }
    declareWin(nrOfRounds, totalWins, ties);
}
