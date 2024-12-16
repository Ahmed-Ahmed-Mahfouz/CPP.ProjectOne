#include <iostream>

using namespace std;

enum enGameChoices{Rock = 1, Paper = 2, Scissors = 3};
enum enWinner{Player = 1, Computer = 2, Draw = 3};

struct stGameVariables
{
    enGameChoices PlayerChoice, ComputerChoice;
    enWinner RoundResult, GameResult;
    short PlayerWinsCount = 0, ComputerWinsCount = 0, DrawCount = 0;
};

short ReadRoundsNumber(string Message)
{
    short RoundsNumber = 0;
    do
    {
        cout << Message << endl;
        cin >> RoundsNumber;
    } while (RoundsNumber < 1 || RoundsNumber > 10);
    return RoundsNumber;
}

short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

char ContinuePlaying(string Message)
{
    char ContinueChar;
    cout << Message << endl;
    cin >> ContinueChar;
    return ContinueChar;
}

enGameChoices ReadUserChoice()
{
    short UserChoice = 0;
    do
    {
        cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
        cin >> UserChoice;
    } while (UserChoice < 1 || UserChoice > 3);
    return static_cast<enGameChoices>(UserChoice);
}

enGameChoices GetComputerChoice()
{
    return static_cast<enGameChoices>(RandomNumber(1, 3));
}

enWinner CountRoundWinner(enGameChoices PlayerChoice, enGameChoices ComputerChoice)
{
    enWinner RoundResult = enWinner::Draw;
    if (PlayerChoice == enGameChoices::Rock)
    {
        if (ComputerChoice == enGameChoices::Paper)
            RoundResult = enWinner::Computer;
        else if (ComputerChoice == enGameChoices::Scissors)
            RoundResult = enWinner::Player;
    }
    else if (PlayerChoice == enGameChoices::Paper)
    {
        if (ComputerChoice == enGameChoices::Scissors)
            RoundResult = enWinner::Computer;
        else if (ComputerChoice == enGameChoices::Rock)
            RoundResult = enWinner::Player;
    }
    else if (PlayerChoice == enGameChoices::Scissors)
    {
        if (ComputerChoice == enGameChoices::Rock)
            RoundResult = enWinner::Computer;
        else if (ComputerChoice == enGameChoices::Paper)
            RoundResult = enWinner::Player;
    }

    return RoundResult;
}

enWinner CountGameWinner(short PlayerWinsCount, short ComputerWinsCount, short DrawCount)
{
    if (PlayerWinsCount > ComputerWinsCount)
        return enWinner::Player;
    else if (ComputerWinsCount > PlayerWinsCount)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

void CountGameResults(stGameVariables& GameVariables)
{
    switch (GameVariables.RoundResult)
    {
    case Player:
        GameVariables.PlayerWinsCount++;
        break;
    case Computer:
        GameVariables.ComputerWinsCount++;
        break;
    case Draw:
        GameVariables.DrawCount++;
    }
}

void PrintColor(enWinner RoundResult)
{
    switch (RoundResult)
    {
    case Player:
        system("color 2F");
        break;
    case Computer:
        cout << "\a";
        system("color 4F");
        break;
    case Draw:
        system("color 6F");
        break;
    }
}

string ChoiceToString(enGameChoices Choice)
{
    switch (Choice)
    {
    case Rock:
        return "Rock";
    case Paper:
        return "Paper";
    case Scissors:
        return "Scissors";
    }
}

string ResultToString(enWinner Result)
{
    switch (Result)
    {
    case Player:
        return "Player";
    case Computer:
        return "Computer";
    case Draw:
        return "No Winner";
    }
}

void PrintRoundHeader(int Number)
{
    cout << "\nRound [" << Number << "] begins:\n";
}

void PrintResultHeader(int Number)
{
    cout << "\n_______________Round [" << Number << "]_______________\n\n";
}

void PrintRoundResult(enGameChoices PlayerChoice, enGameChoices ComputerChoice, enWinner RoundResult)
{
    cout << "Player Choice: " << ChoiceToString(PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceToString(ComputerChoice) << endl;
    cout << "Round Winner: [" << ResultToString(RoundResult) << "]" << endl;
}

void PrintResultFooter()
{
    cout << "\n---------------------------------------\n";
}

void PrintRound(int Number, stGameVariables &GameVariables)
{
    for (int i = 1; i <= Number; i++)
    {
        PrintRoundHeader(i);
        GameVariables.PlayerChoice = ReadUserChoice();
        GameVariables.ComputerChoice = GetComputerChoice();
        GameVariables.RoundResult = CountRoundWinner(GameVariables.PlayerChoice, GameVariables.ComputerChoice);
        CountGameResults(GameVariables);
        PrintColor(GameVariables.RoundResult);
        PrintResultHeader(i);
        PrintRoundResult(GameVariables.PlayerChoice, GameVariables.ComputerChoice, GameVariables.RoundResult);
        PrintResultFooter();
    }
    GameVariables.GameResult = CountGameWinner(GameVariables.PlayerWinsCount, GameVariables.ComputerWinsCount, GameVariables.DrawCount);
}

void PrintGameResultHeader()
{
    cout << "\n\t\t\t---------------------------------------------------------\n";
    cout << "\t\t\t\t\t+++ G A M E  O V E R +++\n";
    cout << "\t\t\t---------------------------------------------------------\n";
    cout << "\t\t\t_____________________[Game Results]______________________\n";
}

void PrintGameResult(int Number, stGameVariables& GameVariables)
{
    PrintGameResultHeader();
    cout << "\n\t\t\tGame Rounds          : " << Number << endl;
    cout << "\t\t\tPlayer Won Times     : " << GameVariables.PlayerWinsCount << endl;
    cout << "\t\t\tComputer Won Times   : " << GameVariables.ComputerWinsCount << endl;
    cout << "\t\t\tDraw Times           : " << GameVariables.DrawCount << endl;
    cout << "\t\t\tFinal Winner         : " << ResultToString(GameVariables.GameResult) << endl;
    cout << "\t\t\t----------------------------------------\n";
    PrintColor(GameVariables.GameResult);
}

void StartGame()
{
    char ContinueChar = 'Y';
    do
    {
        stGameVariables GameVariables;
        short RoundsNumber = ReadRoundsNumber("How Many Rounds 1 to 10 ?");
        PrintRound(RoundsNumber, GameVariables);
        PrintGameResult(RoundsNumber, GameVariables);
        ContinueChar = ContinuePlaying("Do you want to play again?  Y/N?");
        system("cls");
    } while (ContinueChar == 'Y' || ContinueChar == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}

