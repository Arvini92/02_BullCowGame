/*the game logic (no view code or direct user iteraction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase
};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

//Please try and ignore this and focus on the interface
private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHidenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};