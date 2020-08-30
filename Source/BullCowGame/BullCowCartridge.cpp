// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame(); 

    PrintLine(TEXT("The HiddenWord is:  %s"), *HiddenWord); // Debug Line

    // Welcoming the player
    PrintLine(TEXT("Welcome to the Bull Cows Word game!\n"));
    PrintLine(TEXT("Guess the 4 letter word!")); // remove number later 
    PrintLine(TEXT("Press Enter to start..."));
    
    
    

    // Prompt player to guess 
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
     
     // Set Level 

    

    
    // Checking if valid 
    if (Input.Equals(HiddenWord, ESearchCase::IgnoreCase))
    {
        PrintLine(TEXT("You guessed correct!"));
        // Check level 
    } else if (Input.IsEmpty())
    {
        PrintLine(TEXT("Please Enter your guess.."));
    }
    else
    {
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word is 4 Characters long\nPlease try again"));
        }
        
        PrintLine(TEXT("You guessed incorrect. Please try again"));


         
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
    
    HiddenWord = TEXT("cake"); 
    Lives = 4;

}