

#include <iostream>
#include <cstring>
#include <cctype>

#include "utils.h"

using namespace std;

const int IGNORE_CHARS = 256;
const char * INPUT_ERROR_STRING = "input error, try again";


void playGame();
bool wantToPlayAgain();

int getSecretPhrase(char secretPhrase[], int maxLength);
char * MakeHiddenPhrase(const char * secretPhrase, int secretPhraseLength);
void DrawBoard(int numberOfGuessLeft,const char * noptrhiddenPhrase);

char getGuess();
void updateBoard(char guess, char * noptrhiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & numberOfGuessLeft);
bool isGameOver(int numberOfGuessLeft, const char * noptrhiddenPhrase, int secretPhraseLength);
void displayResult(const char *secretPhrase, int numberOfGuessLeft);








int main() {

	do {

		playGame();

	} while (wantToPlayAgain());

	return 0;
}

void playGame() {

	const int MAX_LENGTH = 256;
	const int MAX_GUESSES = 6;

	char secretPhrase[MAX_LENGTH];
	char * optrhiddenPhrase = nullptr;
	int numberOfGuessLeft = MAX_GUESSES;

	int secretPhraseLength = getSecretPhrase(secretPhrase, MAX_LENGTH);

	optrhiddenPhrase = MakeHiddenPhrase(secretPhrase, secretPhraseLength);

	DrawBoard(numberOfGuessLeft, optrhiddenPhrase);

	char guess;

	do {
		guess = getGuess();
		updateBoard(guess, optrhiddenPhrase, secretPhrase, secretPhraseLength, numberOfGuessLeft);

		DrawBoard(numberOfGuessLeft, optrhiddenPhrase);

	} while (!isGameOver(numberOfGuessLeft, optrhiddenPhrase, secretPhraseLength));

	displayResult(secretPhrase, numberOfGuessLeft);

	delete[] optrhiddenPhrase;


}

bool wantToPlayAgain() {
	const char validInputs[] = { 'y', 'n' };

	char response = getCharacter("would you like to play again? (y/n)", INPUT_ERROR_STRING, validInputs, 2);
	return response == 'y';
}


int getSecretPhrase(char secretPhrase[], int maxLength) {

	bool failure;
	int length;

	do {
		failure = false;

		cout << "Enter secret phrase: ";
		cin.get(secretPhrase, maxLength);

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << INPUT_ERROR_STRING << endl;
			failure = true;

		}
		else {
			length = strlen(secretPhrase);
			if (length == 0) {
				cout << "enter a word longer than 0 chars" << endl;
				failure = true;
			}
		}

	} while (failure);

	return length;

}

char * MakeHiddenPhrase(const char * secretPhrase, int secretPhraseLength) {

	char* hiddenPhrase = new char[secretPhraseLength + 1];
	for (int i = 0; i < secretPhraseLength; i++) {
		if (secretPhrase[i] != ' ') {
			hiddenPhrase[i] = '-';
		}
		else {
			hiddenPhrase[i] = ' ';
		}
	}

	hiddenPhrase[secretPhraseLength] = '\0';
	return hiddenPhrase;
}

void DrawBoard(int numberOfGuessLeft, const char * noptrhiddenPhrase) {

	clearScreen();

	switch (numberOfGuessLeft)
	{
	case 0:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  / \\" << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 1:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  /" << endl;
		cout << "-+-" << endl << endl;
	}
	break;

	case 2:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 3:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 4:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |   |" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 5:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 6:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	default:
		break;
	}

	cout << "Secret Phrase: " << noptrhiddenPhrase << endl << endl;
}

char getGuess() {
	return getCharacter("input your guess: ", INPUT_ERROR_STRING);
}

void updateBoard(char guess, char * noptrhiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & numberOfGuessLeft) {
	bool found = false;

	for (int i = 0; i < secretPhraseLength; i++) {
		if (tolower(secretPhrase[i]) == guess) {
			noptrhiddenPhrase[i] = secretPhrase[i];
			found = true;

		}
	}
	if (!found) {
		numberOfGuessLeft--;
	}
}

bool isGameOver(int numberOfGuessLeft, const char * noptrhiddenPhrase, int secretPhraseLength) {
	bool hasDash = false;
	for (int i = 0; i < secretPhraseLength; i++) {
		if (noptrhiddenPhrase[i] == '-') {
			hasDash = true;
			break;
		}
	}

	return numberOfGuessLeft == 0 || !hasDash;
}

void displayResult(const char *secretPhrase, int numberOfGuessLeft) {

	if (numberOfGuessLeft > 0) {
		cout << "you got it, the phrase was: " << secretPhrase << endl;
	}
	else {
		cout << "you didn't get it, the phrase was: " << secretPhrase << endl;

	}
}



