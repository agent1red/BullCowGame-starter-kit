// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();


    PrintLine(TEXT("Welcome to the Bull Cows Word game!\n"));

    PrintLine(TEXT("Guess the 4 letter word! : \"cake\"")); // remove number later 
    PrintLine(TEXT("Press Enter to start..."));
    
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("cake"); // move this outside function 
    
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You guessed correct!"));

    } else
    {
        PrintLine(TEXT("You guessed incorrect. Please try again"));
    }
    
    

}