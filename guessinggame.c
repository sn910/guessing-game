// guessing game
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define LEADERBOARD_SIZE 5

struct Player { // struct for defining player
	char name[50];
	int guess;
};

struct Player leaderboard[LEADERBOARD_SIZE]; // array for top 5 players


void askName(struct Player* player) { // prompts user for their name
	while (getchar() != '\n'); // clears buffer
	printf("Please enter your name to start: \n");
	scanf("%s", player->name);
	while (getchar() != '\n'); // clears buffer
}

void leaders(struct Player leaderboard[]) { // prints our leaderboard for game
	printf("Here are the current leaders: \n");
	for (int i = 0; i < LEADERBOARD_SIZE; i++) {
		if (leaderboard[i].guess != 0) {
			printf("%s made %d guesses\n", leaderboard[i].name, leaderboard[i].guess);
		}
	}
}

void countGuesses(struct Player* player) { // gives the game to user and allows them to guess a value
	int count = 0;
	int guess = 0;
	srand((unsigned int)time(NULL));
	int answer = rand() % 91 + 10;
	double value = sqrt(answer);
	printf("%.8f is the square root of what number? Guess a value between 10 and 100: \n", value);
	scanf("%d", &guess);
	while (1) { // results depending on what the user guesses
		count++;
		if (guess > answer) {
			printf("Too high, guess again: Guess a value between 10 and 100: \n");
			scanf("%d", &guess);
		}
		else if (guess < answer) {
			printf("Too low, guess again: Guess a value between 10 and 100: \n");
			scanf("%d", &guess);
		}
		else if (guess == answer) {
			printf("You got it baby! \n");
			printf("You made %d guesses. \n", count);
			player->guess = count;
			break;
		}
	}
}

void writeToFile(struct Player person) { // saves the leaderboard to the text file
	char fileName[] = "leaderboard.txt";
	FILE* fp = NULL;
	fp = (fopen(fileName, "a"));
	if (fp == NULL) {
		fprintf(stderr, "Cannot open %s. \n)", fileName);
		exit(1);
	}
	fprintf(fp, "%s made %d guesses. \n", person.name, person.guess);
	fclose(fp);
}

void PlayGuessingGame(struct Player leaderboard[]) { // main gaim method to play the game and insert players into the leaderboard
	struct Player player;
	askName(&player);
	countGuesses(&player);
	writeToFile(player);
	int insert = LEADERBOARD_SIZE;
	for (int i = 0; i < LEADERBOARD_SIZE; i++) {
		if ((player.guess < leaderboard[i].guess) || (leaderboard[i].guess == 0)) { // insert the player into the leaderboard
			insert = i;
			break;
		}
	}
	for (int j = LEADERBOARD_SIZE - 1; j > insert; j--) {
		leaderboard[j] = leaderboard[j - 1];
	}
	leaderboard[insert] = player;
	leaders(leaderboard);
}

int main() {
	char c;
	printf("Welcome! Press 'q' to quit or any other key to continue: \n"); //prints starting statement
	scanf(" %c", &c); //gets player's input to continue playing
	while (c != 'q') { //while the player does not type q to quit
		PlayGuessingGame(leaderboard);
		printf("Press 'q' to quit or any other key to continue: \n");
		scanf(" %c", &c); //gets player's input to continue playings
	}
	printf("Bye Bye!");
}
