#pragma once
#include "FBullCowGame.h"
#include <map>

//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHidenWord.length(); }
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHidenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "donkey"; // this must be isogram
	MyHidenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{	
	if (!IsIsogram(Guess))// if the guess isn't isogram
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase 
	{ 
		return EGuessStatus::Not_Lowercase;
	} 
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{ 
		return EGuessStatus::Wrong_Lenght;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}
//recives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WorldLenght = MyHidenWord.length(); // assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WorldLenght; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WorldLenght; GChar++) {
			//if the mutch then
			if (Guess[GChar] == MyHidenWord[MHWChar]) {
				if (MHWChar == GChar) { // if there're in the same place
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WorldLenght) {
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) {//if the letter is in the map
			return false; //we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}
				
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter))// if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}
