#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define MAX_NAME 50

// Player stats structure
struct PlayerStats {
    char name[MAX_NAME];
    int matchesPlayed;
    int wins;
    int losses;
    int ties;
    int totalRuns;
};

// Unified stats structure
struct Stats {
    int matchesPlayed;
    struct PlayerStats player1;
    struct PlayerStats player2;
};

// Function declarations
int toss();
int computerBatting(int target, int overs, int difficulty);
int userBatting(int target, int overs, int difficulty);
int computerGuess(int difficulty, int userRun);
void matchSummary(int score1, int score2, char name1[], char name2[], int isPvP);
void viewStats(struct Stats stats, int mode);
void saveStats(struct Stats stats, int mode);
int tossPvP(char p1[], char p2[]);
int pvpInnings(char batsmanName[], char bowlerName[], int target, int overs, int is2v2);
void playVsComputer();
void playOneVsOne();
void playTwoVsTwo();

// Helper functions
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int getPlayerInput(char playerName[], char prompt[]) {
    int input;
    printf("%s, %s: ", playerName, prompt);
    scanf("%d", &input);
    clearInputBuffer();
    return input;
}

// Global variables
struct Stats vsComputerStats = {0, {"", 0, 0, 0, 0, 0}, {"Computer", 0, 0, 0, 0, 0}};
struct Stats pvp1v1Stats = {0, {"", 0, 0, 0, 0, 0}, {"", 0, 0, 0, 0, 0}};
struct Stats pvp2v2Stats = {0, {"", 0, 0, 0, 0, 0}, {"", 0, 0, 0, 0, 0}};

// Unified menu system
void showMainMenu(int mode) {
    int choice;
    char modeName[20];
    struct Stats *currentStats;
    
    switch(mode) {
        case 1: 
            strcpy(modeName, "Vs Computer"); 
            currentStats = &vsComputerStats;
            break;
        case 2: 
            strcpy(modeName, "1 vs 1 PvP"); 
            currentStats = &pvp1v1Stats;
            break;
        case 3: 
            strcpy(modeName, "2 vs 2 PvP"); 
            currentStats = &pvp2v2Stats;
            break;
    }
    
    while (1) {
        printf("\n========= MAIN MENU =========\n");
        printf("Mode: %s\n", modeName);
        if (mode == 1 && strlen(vsComputerStats.player1.name) > 0) {
            printf("Player: %s\n", vsComputerStats.player1.name);
        }
        printf("1. Play Match\n");
        printf("2. View Stats\n");
        printf("3. Exit to Mode Selection\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1:
                if (mode == 1) playVsComputer();
                else if (mode == 2) playOneVsOne();
                else if (mode == 3) playTwoVsTwo();
                break;
            case 2:
                viewStats(*currentStats, mode);
                break;
            case 3:
                printf("\nReturning to mode selection...\n");
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Main function
int main() {
    srand(time(0));
    int mainChoice;

    while (1) {
        clearScreen();
        printf("🏏 Welcome to the Cricket Game!\n");
        printf("\nSelect Mode:\n1. Vs Computer\n2. 1 vs 1 (PvP)\n3. 2 vs 2 (PvP)\n4. Exit Game\nYour choice: ");
        scanf("%d", &mainChoice);
        clearInputBuffer();

        switch(mainChoice) {
            case 1: 
                printf("\nEnter your name: ");
                scanf(" %49[^\n]", vsComputerStats.player1.name);
                clearInputBuffer();
                showMainMenu(1);
                break;
            case 2: showMainMenu(2); break;
            case 3: showMainMenu(3); break;
            case 4: 
                printf("\nThanks for playing! Goodbye!\n");
                return 0;
            default: 
                printf("Invalid choice! Try again.\n");
        }
    }
}

// Unified toss function
int toss() {
    int tossChoice;
    printf("\nTOSS TIME! Select 1 for Heads, 2 for Tails: ");
    scanf("%d", &tossChoice);
    clearInputBuffer();

    int tossResult = (rand() % 2) + 1;
    printf(tossResult == 1 ? "Heads!\n" : "Tails!\n");

    if (tossChoice == tossResult) {
        printf("You won the toss!\n");
        int playChoice = getPlayerInput("You", "Choose 1 to Bat or 2 to Bowl");
        return playChoice;
    } else {
        printf("Computer won the toss!\n");
        return (rand() % 2) ? 2 : 1;
    }
}

int tossPvP(char p1[], char p2[]) {
    int tossChoice = getPlayerInput(p1, "TOSS TIME! Select 1 for Heads, 2 for Tails");
    int tossResult = (rand() % 2) + 1;
    printf(tossResult == 1 ? "Heads!\n" : "Tails!\n");

    if (tossChoice == tossResult) {
        int playChoice = getPlayerInput(p1, "won the toss! Choose 1 to Bat or 2 to Bowl");
        return playChoice == 1 ? 1 : 2;
    } else {
        int playChoice = getPlayerInput(p2, "won the toss! Choose 1 to Bat or 2 to Bowl");
        return playChoice == 1 ? 2 : 1;
    }
}

// Unified batting function
int computerBatting(int target, int overs, int difficulty) {
    int score = 0, balls = overs * 6;
    
    for (int ball = 1; ball <= balls; ball++) {
        int userGuess = getPlayerInput("You", "ENTER YOUR GUESS (1-6)");
        if (userGuess < 1 || userGuess > 6) {
            printf("Invalid number! Try 1-6.\n");
            ball--;
            continue;
        }

        int compRun = (rand() % 6) + 1;
        printf("Computer played: %d\n", compRun);

        if (userGuess == compRun) {
            printf("OUT! Great delivery!\n");
            break;
        }

        score += compRun;
        printf("Computer total: %d\n", score);

        if (target > 0 && score >= target) {
            printf("\nComputer has chased it successfully!\n");
            break;
        }
    }
    printf("\nComputer's FINAL SCORE: %d\n", score);
    return score;
}

int userBatting(int target, int overs, int difficulty) {
    int score = 0, balls = overs * 6;
    
    for (int ball = 1; ball <= balls; ball++) {
        int userRun = getPlayerInput("You", "ENTER YOUR RUNS (1-6)");
        if (userRun < 1 || userRun > 6) {
            printf("Invalid input! Try 1-6.\n");
            ball--;
            continue;
        }

        clearScreen();
        int compGuess = computerGuess(difficulty, userRun);
        printf("Computer bowled: %d\n", compGuess);

        if (userRun == compGuess) {
            printf("OUT! Computer guessed correctly!\n");
            break;
        }

        score += userRun;
        printf("Your total: %d\n", score);

        if (target > 0 && score >= target) {
            printf("\nYou have chased the target successfully!\n");
            break;
        }
    }
    printf("\nYour FINAL SCORE: %d\n", score);
    return score;
}

int computerGuess(int difficulty, int userRun) {
    int chance = rand() % 100;
    if (difficulty == 3 && chance < 60) return userRun;
    else if (difficulty == 2 && chance < 30) return userRun;
    else return (rand() % 6) + 1;
}

// Unified PvP innings function
int pvpInnings(char batsmanName[], char bowlerName[], int target, int overs, int is2v2) {
    int score = 0, wickets = 0, balls = overs * 6;
    char nextBatsman[MAX_NAME] = "";
    
    if (is2v2) {
        printf("🔄 %s is on standby!\n", nextBatsman);
    }
    
    for (int ball = 1; ball <= balls && wickets < (is2v2 ? 2 : 1); ball++) {
        int batsmanRun = getPlayerInput(batsmanName, "ENTER YOUR RUNS (1-6)");
        if (batsmanRun < 1 || batsmanRun > 6) {
            printf("Invalid input! Try 1-6.\n");
            ball--;
            continue;
        }

        clearScreen();
        int bowlerGuess = getPlayerInput(bowlerName, "ENTER YOUR GUESS (1-6)");
        if (bowlerGuess < 1 || bowlerGuess > 6) {
            printf("Invalid input! Try 1-6.\n");
            ball--;
            continue;
        }

        printf("\n%s played: %d | %s guessed: %d\n", batsmanName, batsmanRun, bowlerName, bowlerGuess);

        if (batsmanRun == bowlerGuess) {
            printf("OUT! %s guessed correctly!\n", bowlerName);
            if (is2v2) {
                wickets++;
                if (wickets == 1) {
                    printf("%s comes in to bat!\n", nextBatsman);
                    char temp[MAX_NAME];
                    strcpy(temp, batsmanName);
                    strcpy(batsmanName, nextBatsman);
                    strcpy(nextBatsman, temp);
                }
            } else {
                break;
            }
        } else {
            score += batsmanRun;
            printf("%s total: %d", batsmanName, score);
            if (is2v2) printf(" | Wickets: %d", wickets);
            printf("\n");

            if (target > 0 && score >= target) {
                printf("\nTarget chased successfully!\n");
                break;
            }
        }
    }
    
    printf("\n%s's FINAL SCORE: %d", batsmanName, score);
    if (is2v2) printf("/%d", wickets);
    printf("\n");
    return score;
}

// Unified match summary
void matchSummary(int score1, int score2, char name1[], char name2[], int isPvP) {
    printf("\n=============================\n");
    printf("        MATCH SUMMARY        \n");
    printf("=============================\n");
    printf("%s: %d\n", name1, score1);
    printf("%s: %d\n", name2, score2);

    if (score1 > score2)
        printf("\033[1;32m%s WON by %d runs!\033[0m\n", name1, score1 - score2);
    else if (score2 > score1)
        printf("\033[1;31m%s WON by %d runs!\033[0m\n", name2, score2 - score1);
    else
        printf("\033[1;33mMatch TIED!\033[0m\n");

    printf("=============================\n\n");
}

// Unified stats display
void viewStats(struct Stats stats, int mode) {
    printf("\n======= %s STATS =======\n", 
           mode == 1 ? "PLAYER" : mode == 2 ? "1v1 PvP" : "2v2 PvP");
    
    if (mode == 1) {
        printf("Player: %s\n", stats.player1.name);
        printf("Matches: %d\nWins: %d | Losses: %d | Ties: %d\n", 
               stats.player1.matchesPlayed, stats.player1.wins, stats.player1.losses, stats.player1.ties);
        printf("Total Runs: %d\n", stats.player1.totalRuns);
    } else {
        // Display both players' stats
        printf("\n--- %s ---\n", stats.player1.name);
        printf("Matches: %d\nWins: %d | Losses: %d | Ties: %d\n", 
               stats.player1.matchesPlayed, stats.player1.wins, stats.player1.losses, stats.player1.ties);
        printf("Total Runs: %d\n", stats.player1.totalRuns);
        
        printf("\n--- %s ---\n", stats.player2.name);
        printf("Matches: %d\nWins: %d | Losses: %d | Ties: %d\n", 
               stats.player2.matchesPlayed, stats.player2.wins, stats.player2.losses, stats.player2.ties);
        printf("Total Runs: %d\n", stats.player2.totalRuns);
        
        printf("\nHead-to-Head: %s %d - %d %s\n", 
               stats.player1.name, stats.player1.wins, 
               stats.player2.wins, stats.player2.name);
    }
    printf("============================\n");
}

void saveStats(struct Stats stats, int mode) {
    char *filename = mode == 1 ? "player_stats.txt" : 
                    mode == 2 ? "pvp_1v1_stats.txt" : "pvp_2v2_stats.txt";
    FILE *f = fopen(filename, "a");
    if (!f) return;
    
    if (mode == 1) {
        fprintf(f, "Player: %s | Matches: %d | Wins: %d | Losses: %d | Ties: %d | Runs: %d\n",
                stats.player1.name, stats.player1.matchesPlayed, stats.player1.wins, 
                stats.player1.losses, stats.player1.ties, stats.player1.totalRuns);
    } else {
        fprintf(f, "Match: %s vs %s\n", stats.player1.name, stats.player2.name);
        fprintf(f, "  %s: Wins: %d | Runs: %d\n", stats.player1.name, stats.player1.wins, stats.player1.totalRuns);
        fprintf(f, "  %s: Wins: %d | Runs: %d\n", stats.player2.name, stats.player2.wins, stats.player2.totalRuns);
        fprintf(f, "  Result: ");
        if (stats.player1.wins > stats.player2.wins) fprintf(f, "%s WON\n", stats.player1.name);
        else if (stats.player2.wins > stats.player1.wins) fprintf(f, "%s WON\n", stats.player2.name);
        else fprintf(f, "TIED\n");
        fprintf(f, "------------------------\n");
    }
    fclose(f);
}

// Game mode functions
void playVsComputer() {
    int overs, difficulty;
    printf("\nSelect Overs (1-3): ");
    scanf("%d", &overs);
    clearInputBuffer();
    if (overs < 1) overs = 1;
    if (overs > 3) overs = 3;

    printf("\nSelect Difficulty:\n1. Easy\n2. Medium\n3. Hard\nYour choice: ");
    scanf("%d", &difficulty);
    clearInputBuffer();
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

    matchSummary(userScore, compScore, vsComputerStats.player1.name, "Computer", 0);

    // Update stats
    vsComputerStats.matchesPlayed++;
    vsComputerStats.player1.matchesPlayed++;
    vsComputerStats.player2.matchesPlayed++;
    
    vsComputerStats.player1.totalRuns += userScore;
    vsComputerStats.player2.totalRuns += compScore;

    if (userScore > compScore) {
        vsComputerStats.player1.wins++;
        vsComputerStats.player2.losses++;
    } else if (compScore > userScore) {
        vsComputerStats.player2.wins++;
        vsComputerStats.player1.losses++;
    } else {
        vsComputerStats.player1.ties++;
        vsComputerStats.player2.ties++;
    }

    saveStats(vsComputerStats, 1);
}

void playOneVsOne() {
    char p1[MAX_NAME], p2[MAX_NAME];
    int overs;
    
    printf("\n=== 1 vs 1 PvP Mode ===\n");
    printf("Enter Player 1 name: ");
    scanf(" %49[^\n]", p1);
    clearInputBuffer();
    printf("Enter Player 2 name: ");
    scanf(" %49[^\n]", p2);
    clearInputBuffer();
    
    printf("Select Overs (1-3): ");
    scanf("%d", &overs);
    clearInputBuffer();
    if (overs < 1) overs = 1;
    if (overs > 3) overs = 3;
    
    int tossChoice = tossPvP(p1, p2);
    int score1, score2;
    
    if (tossChoice == 1) {
        printf("\n%s is BATTING first!\n", p1);
        score1 = pvpInnings(p1, p2, 0, overs, 0);
        printf("\n%s needs %d to WIN!\n", p2, score1 + 1);
        score2 = pvpInnings(p2, p1, score1 + 1, overs, 0);
    } else {
        printf("\n%s is BATTING first!\n", p2);
        score2 = pvpInnings(p2, p1, 0, overs, 0);
        printf("\n%s needs %d to WIN!\n", p1, score2 + 1);
        score1 = pvpInnings(p1, p2, score2 + 1, overs, 0);
    }
    
    matchSummary(score1, score2, p1, p2, 1);

    // Update stats
    pvp1v1Stats.matchesPlayed++;
    strcpy(pvp1v1Stats.player1.name, p1);
    strcpy(pvp1v1Stats.player2.name, p2);
    
    pvp1v1Stats.player1.matchesPlayed++;
    pvp1v1Stats.player2.matchesPlayed++;
    
    pvp1v1Stats.player1.totalRuns += score1;
    pvp1v1Stats.player2.totalRuns += score2;

    if (score1 > score2) {
        pvp1v1Stats.player1.wins++;
        pvp1v1Stats.player2.losses++;
    } else if (score2 > score1) {
        pvp1v1Stats.player2.wins++;
        pvp1v1Stats.player1.losses++;
    } else {
        pvp1v1Stats.player1.ties++;
        pvp1v1Stats.player2.ties++;
    }

    saveStats(pvp1v1Stats, 2);
}

void playTwoVsTwo() {
    char teamA[MAX_NAME], teamB[MAX_NAME];
    char a1[MAX_NAME], a2[MAX_NAME], b1[MAX_NAME], b2[MAX_NAME];
    int overs;
    
    printf("\n=== 2 vs 2 PvP Mode ===\n");
    printf("Enter Team A name: "); scanf(" %49[^\n]", teamA); clearInputBuffer();
    printf("Enter Player A1 name: "); scanf(" %49[^\n]", a1); clearInputBuffer();
    printf("Enter Player A2 name: "); scanf(" %49[^\n]", a2); clearInputBuffer();
    printf("Enter Team B name: "); scanf(" %49[^\n]", teamB); clearInputBuffer();
    printf("Enter Player B1 name: "); scanf(" %49[^\n]", b1); clearInputBuffer();
    printf("Enter Player B2 name: "); scanf(" %49[^\n]", b2); clearInputBuffer();
    
    printf("Select Overs (1-3): ");
    scanf("%d", &overs);
    clearInputBuffer();
    if (overs < 1) overs = 1;
    if (overs > 3) overs = 3;

    int tossResult = tossPvP(teamA, teamB);
    int teamABatsFirst = (tossResult == 1);
    int scoreA, scoreB;

    if (teamABatsFirst) {
        printf("\n%s is BATTING first!\n", teamA);
        scoreA = pvpInnings(a1, teamB, 0, overs, 1);
        printf("\n%s needs %d to WIN!\n", teamB, scoreA + 1);
        scoreB = pvpInnings(b1, teamA, scoreA + 1, overs, 1);
    } else {
        printf("\n%s is BATTING first!\n", teamB);
        scoreB = pvpInnings(b1, teamA, 0, overs, 1);
        printf("\n%s needs %d to WIN!\n", teamA, scoreB + 1);
        scoreA = pvpInnings(a1, teamB, scoreB + 1, overs, 1);
    }
    
    matchSummary(scoreA, scoreB, teamA, teamB, 1);

    // Update stats
    pvp2v2Stats.matchesPlayed++;
    strcpy(pvp2v2Stats.player1.name, teamA);
    strcpy(pvp2v2Stats.player2.name, teamB);
    
    pvp2v2Stats.player1.matchesPlayed++;
    pvp2v2Stats.player2.matchesPlayed++;
    
    pvp2v2Stats.player1.totalRuns += scoreA;
    pvp2v2Stats.player2.totalRuns += scoreB;

    if (scoreA > scoreB) {
        pvp2v2Stats.player1.wins++;
        pvp2v2Stats.player2.losses++;
    } else if (scoreB > scoreA) {
        pvp2v2Stats.player2.wins++;
        pvp2v2Stats.player1.losses++;
    } else {
        pvp2v2Stats.player1.ties++;
        pvp2v2Stats.player2.ties++;
    }

    saveStats(pvp2v2Stats, 3); // Save 2v2 stats
}