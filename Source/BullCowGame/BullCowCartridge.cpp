// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts 
{
    Super::BeginPlay();
    GetValidWords(Words);
    SetupGame(); 

    PrintLine(TEXT("The number of possible words is: %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is: %i"), GetValidWords(Words).Num());
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
    PrintLine(TEXT("\nGame Over!! Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
        // Checking if valid 
        if (Guess.Equals(HiddenWord, ESearchCase::IgnoreCase))
        {
            PrintLine(TEXT("You guessed correct! You Win the Game!"));
            EndGame();
            return;
        } 

        if (Guess.IsEmpty())
        {
            PrintLine(TEXT("Please Enter your guess.."));
            return;
        }
        --Lives;// Remove a life at this point in checks 
        if (Guess.Len() != HiddenWord.Len() && Lives > 0)
        {
            PrintLine(TEXT("The Hidden Word is %i Characters long \nYou lost a life"), HiddenWord.Len());
            PrintLine(TEXT("Sorry guess again!! \nYou have %i Lives left"), Lives);
            return;
        }

          if (!IsIsogram(Guess)) // Check if Isogram
        {
            PrintLine(TEXT("There are no repeating letters! \nGuess again..."));
            return;
        }

        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
            PrintLine(TEXT("You have no lives left!"));
            EndGame();
            return;       
        }
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    
    return true;   
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordsList) const
{
     TArray<FString> ValidWords;

       for (int32 i = 0; i < WordsList.Num(); i++)
    {

        if (IsIsogram(WordsList[i]) && WordsList[i].Len() >= 4 && WordsList[i].Len() <= 7)
        {
        
            ValidWords.Emplace(WordsList[i]);

        }   
    }
    return ValidWords;
  
}