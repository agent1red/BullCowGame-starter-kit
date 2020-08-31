// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); 

    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); // Debug Line   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else //  else Checking PlayerGuess
    {
        ProcessGuess(Input);
     
    }
    
    

    
   


    // Check if Isogram
    // Check for right number of characters
    // Promp to guess again
    
    // Remove Life 

    // Check if Lives > 0 
    // If yes GuessAgain
    // Show lives left
    // If no show GameOver and Hiddenword
    // Press Enter to play again 
    // check user input 
    // PlayAgain or quit 
    
    

}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cows Word game!\n"));  
    HiddenWord = TEXT("cake"); 
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i leter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives left"), Lives);
    PrintLine(TEXT("Type in your guess \nand Press Enter to continue..."));// Prompt player to guess 
    
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Game Over!! Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
        // Checking if valid 
        if (Guess.Equals(HiddenWord, ESearchCase::IgnoreCase))
        {
            PrintLine(TEXT("You guessed correct! You Win the Game!"));
            EndGame();
        } else if (Guess.IsEmpty())
        {
            PrintLine(TEXT("Please Enter your guess.."));
        }
        else
        {
            --Lives;
            if (Guess.Len() != HiddenWord.Len())
            {
                
                
                PrintLine(TEXT("The Hidden Word is %i Characters long \nYou lost a life"), HiddenWord.Len());
                if (Lives > 0)
                {
                    
                    PrintLine(TEXT("Sorry guess again!! \nYou have %i Lives left"), Lives);
                }
                else
                {
                    ClearScreen();
                    PrintLine(TEXT("You have no lives left!"));
                    EndGame();
                } 
               
            }
        
        }
}