// Base Version of a simple Cricket Game in C.
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int toss(); //Toss function declaration.
int computerBatting(int target); //computer batting function declaration.
int userBatting(int target); //User batting function declaration.


//Main function.
int main(){
    srand(time(0)); // Seed random generator once at the start
    /* seed rand means seed-random. seed is the specific starting point from where random number sequence should start. if you give
    the same seed you'll get the same squence. time(0) returns the current time in seconds since 1st Jan 1970. Since time is always 
    changing, it gives a different value each second */
    
    int choice = toss(); // Call the toss function. It returns 1 if user chooses to bat, 2 if user chooses to bowl 
    int userScore, compScore; // Variables to store scores of user and computer

    if (choice == 1) { 
        // User won the toss and chose to bat first
        userScore = userBatting(0); // User bats first. Target is 0 because it's the first innings
        printf("\nComputer needs %d to WIN!\n", userScore + 1); // Show the target for computer
        compScore = computerBatting(userScore + 1); // Computer bats second, trying to chase the target

        // Compare scores to determine winner
        if (compScore >= userScore + 1)
            printf("\nCOMPUTER WINS!\n"); 
        else if(compScore == userScore)
            printf("Match is Tied!!!");
        else
            printf("\nUSER WINS!\n");

    } else if (choice == 2) { 
        // User won the toss and chose to bowl first (Computer bats first)
        compScore = computerBatting(0); // Computer bats first. Target is 0 because it's first innings
        printf("\nYou need %d to WIN!\n", compScore + 1); // Show the target for user
        userScore = userBatting(compScore + 1); // User bats second, trying to chase the target

        // Compare scores to determine winner
        if (userScore >= compScore + 1)
            printf("\nUSER WINS!\n");
        else if(userScore == compScore)
            printf("Match is Tied!!!");
        else
            printf("\nCOMPUTER WINS!\n");
    }
    return 0; // End the program
}


//Toss function definition.
int toss() {
    int toss_choice;  //Variable to allow user to input their choice of heads or tails.
    printf("Select 1 for heads; 2 for tails:\n");
    scanf("%d", &toss_choice);
    
    int toss_result = rand() % 2; //If the random number is fully divisible by 2 n gives a remainder of 0, then it's considered as heads. Else, tails.
    if (toss_result == 0) {
        printf("Heads\n");
    } else {
        printf("Tails\n");
    }
    
    int userChoice;  //Variable to allow user to choose their stance if they win.
    if(toss_choice == toss_result + 1){ //If the user's choice matches with the results of the toss, then the user wins, and can opt for either batting or bowling.
        printf("User Won\n");
        printf("\n");
        printf("Type 1 for Batting\n2 for Bowling?\n");
        scanf("%d", &userChoice);
        return userChoice; //Whatever the user chooses now, is returned as the output of the "toss" function, which will be used to continue the game further.
    }else{ //Lol, the user lost. The user's fate is in the hands of the computer's random choices now!!
        printf("Computer Won\n");
        int compChoice = rand() % 2; //Computer randomly decides batting or bowling
        if (compChoice == 0) {
            printf("Computer chooses to Bat\n");
            return 2; // computer bats first
        } else {
            printf("Computer chooses to Bowl\n");
            return 1; // user bats first
        }
    }
}


//Computer Batting Function Definition.
int computerBatting(int target) {
    int compScore = 0;   // It keeps track of the computer's total score/runs. It starts at 0.
    int userGuess, compRun;  // userGuess: It takes and stores the number from 1-6 that the user chose to bowl. compRun: This stores computer's randomly generated score/runs for each ball.
    int lastComment = -1; // To prevent the same commentary to repeat.

    // WHILE LOOP: Its an infinite loop where each iteration is representd as one ball bowled by the user and the loop breaks when the computer becomes OUT!
    while (1) {  
        // User enters guess (bowling)
        printf("\nENTER YOUR GUESS (1 to 6): ");
        if (scanf("%d", &userGuess) != 1) {
            printf("Oops! That's not a number. Try 1-6.\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }

        // Make sure user entered a number between 1 and 6
        if (userGuess < 1 || userGuess > 6) {
            printf("Umpire insists: pick a number between 1 and 6.\n");
            continue;
        }

        // Computer generates a random run (1–6)
        compRun = (rand() % 6) + 1;

        // OUT condition
        if (userGuess == compRun) {
            printf("OUT! You bowled a cracker! Computer is gone!\n");
            printf("Computer's FINAL SCORE: %d\n", compScore);
            break;
        } else {
            // Add runs
            compScore += compRun;
            
            // Fun bowling commentary without repetition
            int comment;
            do {
                comment = rand() % 6;  // Generate a random number from 0 to 5, representing a random commentary line
            } while (comment == lastComment); // Keep generating until it is different from the last one, to avoid repeating the same commentary twice in a row
            lastComment = comment;  // Store the current comment index so the next iteration knows what was used

            switch (comment) {  
                case 0:
                    printf("Oh no! That slipped through, %d run%s!\n", compRun, compRun > 1 ? "s" : ""); //The ternary part (compRun > 1 ? "s" : "") adds "s" if the computer scored more than 1.
                    break;
                case 1:
                    printf("Nice one, bowler! But computer gets %d.\n", compRun);
                    break;
                case 2:
                    printf("Close call! %d run%s raced away!\n", compRun, compRun > 1 ? "s" : "");
                    break;
                case 3:
                    printf("What a crafty delivery! But COMPUTER still fetches %d.\n", compRun);
                    break;
                case 4:
                    printf("Keep it tight! Computer sneaks %d run%s!\n", compRun, compRun > 1 ? "s" : "");
                    break;
                case 5:
                    printf("Good line, good length! But computer manages %d.\n", compRun);
                    break;
            }

            printf("Computer's TOTAL SCORE: %d\n", compScore);

            // Check target if this is the second innings
            if (target > 0 && compScore >= target) {
                printf("Computer has reached the target!\n");
                break;
            }
        }
    }
    return compScore; // Final score returned
}


//User Batting Funtion Definition.
int userBatting(int target){
    int userScore = 0; //Keeps track of the user's score. Set to 0
    int userRun, compGuess; //userRun is used to store the runs scored after each ball. compGuess is the number generated by the computer each ball.
    int lastComment = -1; //To prevent same comment from repeating during commentary. set to -1 to indicate that no comment has been shown yet.

    while (1) {  
        // User enters runs
        printf("\nENTER YOUR RUNS (1 to 6): ");
        if (scanf("%d", &userRun) != 1) {
            printf("Oops! That's not a number. Try 1-6.\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }
    
        //Make sure user enters a number between 1 to 6 only.    
        if(userRun < 1 || userRun > 6 ){
            printf("Umpire says: Pick a number between 1 to 6 only please...\n");
            continue;
        }
        
        compGuess = (rand() % 6) + 1; // Seed random number generator wrt time so that it produces random numbers each time.
        printf("Computer bowled: %d\n", compGuess);

        //Condition if user gets out i.e., if user's number and Computer's guess match.
        if(userRun == compGuess){
            printf("OUT! The Computer Guessed right!\n");
            printf("You Total Score is : %d\n", userScore);
            break;
        }else{
            //Add up the batting score of the user.
            userScore += userRun;
            printf("Your Total Score : %d\n", userScore);

            // Batting commentary without repetition
                int comment;
                do {
                    comment = rand() % 6;  // Generate a random number from 0 to 5, representing a random commentary line
                } while (comment == lastComment); // Keep generating until it is different from the last one, to avoid repeating the same commentary twice in a row
                lastComment = comment;  // Store the current comment index so the next iteration knows what was used

                switch (comment) {  
                    case 0:
                        printf("Well Played!, %d run%s!\n", userRun, userRun > 1 ? "s" : ""); //The ternary part (userRun > 1 ? "s" : "") adds "s" if the computer scored more than 1.
                        break;
                    case 1:
                        printf("That's a shot and a half that is! %d.\n", userRun);
                        break;
                    case 2:
                        printf("Cheeky! %d run%s raced away!\n", userRun, userRun > 1 ? "s" : "");
                        break;
                    case 3:
                        printf("That was a TRACER BULLET! %d.\n", userRun);
                        break;
                    case 4:
                        printf("That was Close! %d run%s added to the tally.\n", userRun, userRun > 1 ? "s" : "");
                        break;
                    case 5:
                        printf("Ohh the Computer nearly got you.  %d.\n", userRun);
                        break;
                }

            //If user crosses the target while chasing in the 2nd innings, user wins.
            if (target > 0 && userScore >= target){
                printf("YOU WIN!!!\nYou Have successfully chased the target!\n");
                break;
            }
        }
    }
    return userScore; //returns the user score.
}