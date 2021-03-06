// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


void UBullCowCartridge::BeginPlay() // When the game starts 
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordsList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);

    Isograms = GetValidWords(WordList);
    SetupGame(); 
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
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)]; 
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i leter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives left"), Lives);
    PrintLine(TEXT("Type in your guess \nand Press Enter to continue..."));// Prompt player to guess 
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); // Debug Line   
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nGame Over!! Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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

       
        FBullCowCount Score = GetBullCows(Guess);

        PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls , Score.Cows);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

       for (FString Word : WordsList)
    {

        if (IsIsogram(Word) &&  Word.Len() >= 4 && Word.Len() <= 7)
        {
        
            ValidWords.Emplace(Word);

        }   
    }
    return ValidWords;
  
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
   FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] ==  HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len();  HiddenIndex++)
        {
            if (Guess[GuessIndex] ==  HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
            
        }
 
    }
    return Count;
}