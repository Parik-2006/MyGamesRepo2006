#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h> // to print any special characters without error.

#define MAX_NAME 50

// Structure to store player stats
struct Stats {
    int matchesPlayed;
    int matchesWon;
    int matchesLost;
    int matchesTied;
    int totalRuns;
};

// Function declarations
int toss();
int computerBatting(int target, int overs, int difficulty);
int userBatting(int target, int overs, int difficulty);
int computerGuess(int difficulty, int userRun);
void matchSummary(int userScore, int compScore, char playerName[]);
void viewStats(struct Stats stats, char playerName[]);
void saveStats(struct Stats stats, char playerName[]);

// Main function
int main() {
    srand(time(0));

    struct Stats stats = {0, 0, 0, 0, 0};
    char playerName[MAX_NAME];
    int choice;

    printf("🏏 Welcome to Hand Cricket!\n\nEnter your name: ");
    scanf("%[^\n]s", playerName);

    while (1) {
        printf("\n========= MAIN MENU =========\n");
        printf("1. Play Match\n");
        printf("2. View My Stats\n");
        printf("3. Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int overs, difficulty;
            printf("\nSelect Overs (1-3): ");
            scanf("%d", &overs);
            if (overs < 1) overs = 1;
            if (overs > 3) overs = 3;

            printf("\nSelect Difficulty:\n1. Easy\n2. Medium\n3. Hard\nYour choice: ");
            scanf("%d", &difficulty);
            if (difficulty < 1 || difficulty > 3) difficulty = 1;

            int tossChoice = toss();
            int userScore, compScore;

            if (tossChoice == 1) {
                printf("\nYou are BATTING first!\n");
                userScore = userBatting(0, overs, difficulty);
                printf("\nComputer needs %d to WIN!\n", userScore + 1);
                compScore = computerBatting(userScore + 1, overs, difficulty);
            } else {
                printf("\nYou are BOWLING first!\n");
                compScore = computerBatting(0, overs, difficulty);
                printf("\nYou need %d to WIN!\n", compScore + 1);
                userScore = userBatting(compScore + 1, overs, difficulty);
            }

            // Match Summary
            matchSummary(userScore, compScore, playerName);

            // Update Stats
            stats.matchesPlayed++;
            stats.totalRuns += userScore;
            if (userScore > compScore)
                stats.matchesWon++;
            else if (compScore > userScore)
                stats.matchesLost++;
            else
                stats.matchesTied++;

            saveStats(stats, playerName);
        }
        else if (choice == 2) {
            viewStats(stats, playerName);
        }
        else if (choice == 3) {
            printf("\nThanks for playing, %s! See you next time!\n", playerName);
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
            break;
        }
    }

    return 0;
}

// Toss function
int toss() {
    int tossChoice;
    printf("\nTOSS TIME! Select 1 for Heads, 2 for Tails: ");
    scanf("%d", &tossChoice);

    int tossResult = (rand() % 2) + 1; // 1=heads, 2=tails
    printf(tossResult == 1 ? "Heads!\n" : "Tails!\n");

    if (tossChoice == tossResult) {
        printf("You won the toss!\n1. Bat\n2. Bowl\nYour choice: ");
        int playChoice;
        scanf("%d", &playChoice);
        return playChoice;
    } else {
        printf("Computer won the toss!\n");
        int compChoice = rand() % 2;
        if (compChoice == 0) {
            printf("Computer chooses to Bat first.\n");
            return 2; // you bowl first
        } else {
            printf("Computer chooses to Bowl first.\n");
            return 1; // you bat first
        }
    }
}

// Computer batting
int computerBatting(int target, int overs, int difficulty) {
    int compScore = 0;
    int userGuess, compRun;
    int balls = overs * 6;
    int lastComment = -1;

    for (int ball = 1; ball <= balls; ball++) {
        printf("\nBall %d of %d\nENTER YOUR GUESS (1–6): ", ball, balls);
        scanf("%d", &userGuess);
        if (userGuess < 1 || userGuess > 6) {
            printf("Invalid number! Try 1–6.\n");
            ball--;
            continue;
        }

        compRun = (rand() % 6) + 1;
        printf("Computer played: %d\n", compRun);

        if (userGuess == compRun) {
            printf("OUT! Great delivery!\n");
            break;
        }

        compScore += compRun;
        int comment;
        do { comment = rand() % 5; } while (comment == lastComment);
        lastComment = comment;
        char *comments[] = {
            "Computer slices it away for %d run%s!",
            "Nice timing! %d run%s.",
            "Sneaky single! %d added.",
            "Clean hit! %d run%s more.",
            "That’s well played! %d run%s."
        };
        printf(comments[comment], compRun, compRun > 1 ? "s" : "");
        printf("\nComputer total: %d\n", compScore);

        if (target > 0 && compScore >= target) {
            printf("\nComputer has chased it successfully!\n");
            break;
        }
    }
    printf("\nComputer’s FINAL SCORE: %d\n", compScore);
    return compScore;
}

// User batting
int userBatting(int target, int overs, int difficulty) {
    int userScore = 0;
    int userRun, compGuess;
    int balls = overs * 6;
    int lastComment = -1;

    for (int ball = 1; ball <= balls; ball++) {
        printf("\nBall %d of %d\nENTER YOUR RUNS (1–6): ", ball, balls);
        scanf("%d", &userRun);
        if (userRun < 1 || userRun > 6) {
            printf("Invalid input! Try 1–6.\n");
            ball--;
            continue;
        }

        compGuess = computerGuess(difficulty, userRun);
        printf("Computer bowled: %d\n", compGuess);

        if (userRun == compGuess) {
            printf("OUT! Computer guessed correctly!\n");
            break;
        }

        userScore += userRun;
        int comment;
        do { comment = rand() % 5; } while (comment == lastComment);
        lastComment = comment;
        char *comments[] = {
            "Cracked that! %d run%s.",
            "Beautiful shot! %d more.",
            "That’s class! %d run%s added.",
            "Lovely touch! %d run%s.",
            "Crowd erupts! %d scored."
        };
        printf(comments[comment], userRun, userRun > 1 ? "s" : "");
        printf("\nYour total: %d\n", userScore);

        if (target > 0 && userScore >= target) {
            printf("\nYou have chased the target successfully!\n");
            break;
        }
    }
    printf("\nYour FINAL SCORE: %d\n", userScore);
    return userScore;
}

// Computer's guessing logic based on difficulty
int computerGuess(int difficulty, int userRun) {
    int chance = rand() % 100;
    if (difficulty == 3 && chance < 60) return userRun;        // Hard
    else if (difficulty == 2 && chance < 30) return userRun;   // Medium
    else return (rand() % 6) + 1;                              // Easy
}

// Match summary
void matchSummary(int userScore, int compScore, char playerName[]) {
    printf("\n=============================\n");
    printf("        MATCH SUMMARY        \n");
    printf("=============================\n");
    printf("%s's Score: %d\n", playerName, userScore);
    printf("Computer's Score: %d\n", compScore);

    if (userScore > compScore)
        printf("\033[1;32m%s WON by %d runs!\033[0m\n", playerName, userScore - compScore);
    else if (compScore > userScore)
        printf("\033[1;31mComputer WON by %d runs!\033[0m\n", compScore - userScore);
    else
        printf("\033[1;33mMatch TIED!\033[0m\n");

    printf("=============================\n\n");
}

// View stats
void viewStats(struct Stats stats, char playerName[]) {
    printf("\n======= PLAYER STATS =======\n");
    printf("Player name: %s\n",playerName);
    printf("Matches Played: %d\n", stats.matchesPlayed);
    printf("Wins: %d | Losses: %d | Ties: %d\n", stats.matchesWon, stats.matchesLost, stats.matchesTied);
    printf("Total Runs Scored: %d\n", stats.totalRuns);
    printf("============================\n");
}

// Save stats to file
void saveStats(struct Stats stats, char playerName[]) {
    FILE *f = fopen("player_stats.txt", "w");
    if (!f) return;
    fprintf(f, "Player: %s\nMatches: %d\nWins: %d\nLosses: %d\nTies: %d\nTotal Runs: %d\n",
            playerName, stats.matchesPlayed, stats.matchesWon, stats.matchesLost, stats.matchesTied, stats.totalRuns);
    fclose(f);
}
