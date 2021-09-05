/**
 * Dice & Word Game Project C++
 * 
 * Copyright @ Myo Aung 2021.
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

//GLOBAL VARIABLES
int Board[3][3];
char Arr[7];
string Arr3[] = { "car", "bed", "apple", "pen" };
string Arr4[] = { "monitor", "orange", "picture", "teacher"};
//--------------------------------------------------------------
void newLine()
{
    char c;
    do
    {
        cin.get(c);
    } while (c != '\n');
}
//---------------------------------------------------------------------
void PrintBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] == 99)
                cout << "X ";
            else if (Board[i][j] == 100)
                cout << "O ";
            else
                cout << Board[i][j] << " ";
        }
        cout << endl;
    }
}
//---------------------------------------------------------------------
int getDiceResult()
{
    int num;
    num = (rand() % 11) + 2;
    return num;
}
//----------------------------------------------------------------------
int randNum1() // random number from 1-100
{
    int num1;
    num1 = (rand() % 100 + 1);
    return num1;
}
//------------------------------------------------------------------------
int randNum2() // random number from 1-150
{
    int num2;
    num2 = (rand() % 150 + 1);
    return num2;
}
//---------------------------------------------------------------------------------------------------
void resumeGame(string saveFile, int& player1Power, int& player2Power)
{
    ifstream inputFile;
    inputFile.open(saveFile);
    if (inputFile.fail())
    {
        cout << "Cannot open file.\n";
        exit(1);
    }

    inputFile >> player1Power;
    inputFile >> player2Power;
    cout<< endl;
    cout<<"Player 1 remaining Power: "<< player1Power<<endl;
    cout<<"Player 2 remaining Power: "<< player2Power<<endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            inputFile >> Board[i][j];
        }
    }

    inputFile.close();
}
//---------------------------------------------------------------------------------------------------
void newGame(int& whoGoFirst)
{
    bool hasOutcome = true;
    int player1diceResult;
    int player2diceResult;

    while (hasOutcome)
    {
        player1diceResult = getDiceResult();
        player2diceResult = getDiceResult();
        cout << "THE DICE GAME" << endl << "-------------" << endl << "Here are the dice results:" << endl;
        cout << "The Dice result for Player 1 is: " << player1diceResult << endl;
        cout << "The Dice result for Player 2 is: " << player2diceResult << endl;
        if (player1diceResult > player2diceResult)
        {
            cout << "Player 1 has a higher dice value!" << endl;
            cout << "Player 1 starts the game.\n" << endl;
            whoGoFirst = 1;
            hasOutcome = false;
        }
        else if (player2diceResult > player1diceResult)
        {
            cout << "Player 2 has a higher dice value!" << endl;
            cout << "Player 2 starts the game.\n" << endl;
            whoGoFirst = 2;
            hasOutcome = false;
        }
        else
        {
            cout << "Player 1 and Player 2 have the same dice value, re-roll the dice.\n" << endl;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------
void menuPick(int& whoGoFirst, int& player1Power, int& player2Power)
{
    string saveFile = "";
    char choice;
    bool flag = true;
    while (flag)
    {
        cout << "CHOOSE ONE OF THE FOLLOWING OPTIONS TO CONTINUE\n";
        cout << "-----------------------------------------------\n";
        cout << "Choose P or p to start a new Game OR continue the existing game Game.\n";
        cout << "Choose R or r to resume an existing Game.\n";
        cout << "Choose E or e or Exit.\n";
        cout << "Choice: ";
        cin >> choice;
        newLine();
        cout << endl;
        switch (choice)
        {
        case 'P':
        case 'p':
            newGame(whoGoFirst);
            flag = false;
            break;

        case 'R':
        case 'r':
            cout << "Resume the existing Game!";
            cout << "Please enter the path to the save file." << endl;
            cin >> saveFile;
            resumeGame(saveFile, player1Power, player2Power);
            whoGoFirst = 0;
            flag = false;
            break;
        case 'E':
        case 'e':
            cout << "BYE! SEE YOU SOON!\n";
            flag = false;
            exit(0);
            break;
        default:flag;
            cout << "Enter a valid choice.\n\n";
        }
    }
}
//--------------------------------------------------------------------------
int PickWhichGame()
{
    char choice;
    bool flag = true;
    while (flag)
    {
        cout << "Enter 'a' to play the \"Number-Guessing Game\"." << endl;
        cout << "Enter 'b' to play the \"Word-Guessing Game\"." << endl;
        cout << "Choice: ";
        cin >> choice;
        newLine();
        cout << endl;
        if (choice == 'a')
        {
            flag = false;
            return 1;
        }
        else if (choice == 'b')
        {
            flag = false;
            return 2;
        }
        else
        {
            cout << "Enter a valid choice.\n\n";

        }
    }
    return 0;
}
//-----------------------------------------------------------------------------------------
void goPickABoard(int winner)
{
    PrintBoard();

    int num;
    while (true)
    {
        if (winner == 1)
        {
            cout << "Player 1, ";
        }
        else
            cout << "Player 2, ";
        cout << "choose the position on the Board" << endl;
        cin >> num;
        newLine();
        if (num > 9 || num < 1)
        {
            cout << "The number is out of range, please reselect!" << endl;
        }
        else if (Board[(num - 1) / 3][(num - 1) % 3] == 99 || Board[(num - 1) / 3][(num - 1) % 3] == 100)
        {
            cout << "That position is already filled, please reselect!" << endl;
        }
        else
            break;
    }

    if (winner == 1)
    {
        Board[(num - 1) / 3][(num - 1) % 3] = 99;
    }
    else if (winner == 2)
    {
        Board[(num - 1) / 3][(num - 1) % 3] = 100;
    }

    return;
}
//----------------------------------------------------------------------------------------------
void goGuessNumber(int goFirst, int Xnum, int max, int& guessplayerPower)
{
    int attempts = 5;
    int num;
    int counter = 0;
    int maxNum = max;
    int minNum = 1;
    while (attempts > 0)
    {
        counter++;
        while (true)
        {
            cout << "The number is between " << minNum << " and " << maxNum << "." << endl;
            cout << "Number Guessed (Attempt " << counter << "): ";
            cin >> num;
            newLine();
            if (num > maxNum || num < minNum)
            {
                cout << "The number is out of range, please reselect!" << endl;
            }
            else
                break;
        }
        if (num == Xnum)
        {
            if (goFirst == 1)
                goFirst = 2;
            else
                goFirst = 1;
            cout << "\nBINGO!! PLAYER " << goFirst << " GUESSED THE NUMBER RIGHT!!" << endl;
            cout << "PLAYER " << goFirst << " WINS THIS ROUND!!\n" << endl;
            goPickABoard(goFirst);
            return;
        }
        else if (num > Xnum)
        {
            maxNum = num;
        }
        else if (num < Xnum)
        {
            minNum = num;
        }
        attempts--;
        if (attempts == 0 && guessplayerPower > 0)
        {
            char choice;
            while (true)
            {
                cout << "\nOh--ohh!! You just used up your attempts!!" << endl;
                cout << "\nDo you want to use your power to get three more attempts?" << endl;
                cout << "Enter 'y' for yes and 'n' for no." << endl;
                cout << "Choice: ";
                cin >> choice;
                newLine();
                if (choice == 'y')
                {
                    cout << "\nYou have decided to use one of your remaining " << guessplayerPower << " powers!" << endl;
                    cout << "You have " << guessplayerPower - 1 << " Powers left." << endl;
                    cout << "Now, you have THREE more attempts.\n" << endl;
                    guessplayerPower--;
                    attempts = 3;
                    break;
                }
                else if (choice == 'n')
                {
                    cout << "You decided not to use your power!" << endl;
                    break;
                }
                else
                {
                    cout << "Enter a valid choice.\n\n";
                }
            }
        }
    }

    if (goFirst == 1)
    {
        cout << "\nPlayer 2, You used up all your attempts!\n" << "PLAYER 1 WINS!!\n" << endl;
        goPickABoard(1);
    }
    else
    {
        cout << "\nPlayer 1, You used up all your attempts!\n" << "PLAYER 2 WINS!!\n" << endl;
        goPickABoard(2);
    }
}
//-----------------------------------------------------------------------------------------------------------------------
void StartNumberGame(int goFirst, int& player1Power, int& player2Power)
{
    char choice;
    bool flag = true;
    int maxNum = 100;
    //-----------------------------------------------------------------------------------
    if (goFirst == 1)
    {
        if (player1Power > 0)
        {
            while (flag)
            {
                cout << "Player 1:" << endl << "Do you want to use your power to increase the limit from 100 to 150?" << endl;
                cout << "Enter 'y' for yes and 'n' for no." << endl;
                cout << "Choice: ";
                cin >> choice;
                cout << endl;
                newLine();
                if (choice == 'y')
                {
                    cout << "Player 1, You have chosen to use one of your remaining " << player1Power << " powers!" << endl;
                    cout << "You have " << player1Power - 1 << "-Powers left.\n" << endl;
                    player1Power--;
                    maxNum = 150;
                    flag = false;
                }
                else if (choice == 'n')
                {
                    cout << "Player 1, You decided not to use your power!" << endl;
                    cout << "You have " << player1Power << "-Powers left.\n" << endl;
                    flag = false;
                }
                else
                {
                    cout << "Enter a valid choice.\n\n";
                }
            }
        }
        //-------------------------------------------------------------------------------------------------
        int Xnum;
        bool numFlag = true;
        while (numFlag)
        {
            Xnum = randNum1();
            cout << "Now, Player 1, Pick any number from 1-" << maxNum << " for Player 2 to guess.\n" << endl;
            cout << "(((*** Player 1 has picked a random number. ***)))" << endl;//cout<< Xnum;
            cout << "\nPlayer 2:" << endl << "Press \"ENTER\" to start guessing." << endl;
            newLine();
            if (Xnum > maxNum || Xnum <= 0)
            {
                cout << "The number is out of range, please reselect the number." << endl;
            }
            else
            {
                numFlag = false;

            }
        }
        goGuessNumber(goFirst, Xnum, maxNum, player2Power);
    }
    //-----------------------------------------------------------------------------------------------------------
    else if (goFirst == 2)
    {
        if (player2Power > 0)
        {
            while (flag)
            {
                cout << "Player 2: " << endl << "Do you want to use your power to increase the limit from 100 to 150?" << endl;
                cout << "Enter 'y' for yes and 'n' for no." << endl;
                cout << "Choice: ";
                cin >> choice;
                newLine();
                cout << endl;
                if (choice == 'y')
                {
                    cout << "Player 2, You have chosen to use one of your remaining " << player2Power << " powers!" << endl;
                    cout << "You have " << player2Power - 1 << "-Power left.\n" << endl;
                    player2Power--;
                    maxNum = 150;
                    flag = false;
                }
                else if (choice == 'n')
                {
                    cout << "Player 2, You decided not to use your power!" << endl;
                    cout << "You have " << player2Power << "-Powers left.\n" << endl;
                    flag = false;
                }
                else
                {
                    cout << "Enter a valid choice.\n\n";
                }
            }
        }

        int Xnum;
        bool numFlag = true;
        while (numFlag)
        {
            Xnum = randNum2();
            cout << "Now, Player 2, Pick any number from 1-" << maxNum << " for Player 1 to guess.\n" << endl;
            cout << "(((*** Player 2 has picked a random number. ***)))" << endl;//cout<< Xnum;
            cout << "\nPlayer 1:" << endl << "Press \"ENTER\" to start guessing." << endl;
            newLine();
            if (Xnum > maxNum || Xnum <= 0)
            {
                cout << "The Number is out of range, please reselect the number again." << endl;
            }
            else
            {
                numFlag = false;
            }
        }

        goGuessNumber(goFirst, Xnum, maxNum, player1Power);
    }
}
//------------------------------------------------------------------------------------------------------------------------
void goGuessWord(int goFirst, int wordLength, string theWord, int& guessplayerPower)
{
    int attempts = 5;
    string currentWord = "";
    int counter = 1;
    char choiceAB;
    char guessChar;
    bool enterWholeWord = false;
    cout << "((( THE WORD HAS BEEN PICKED!! )))" << endl;
    if (goFirst == 1)
    {
        cout << "Player 2, start guessing the word." << endl;
    }
    else
    {
        cout << "Player 1, please start guessing the word." << endl;
    }

    for (int i = 0; i < wordLength; i++)
    {
        Arr[i] = '*';
    }
    while (attempts > 0)
    {
        enterWholeWord = false;
        for (int i = 0; i < wordLength; i++)
        {
            cout << Arr[i];
        }
        cout << endl;
        while (true)
        {
            if (attempts == 1)
            {
                enterWholeWord = true;
                break;
            }
            else
            {
                cout << "Attempt " << counter << ":\n" << "Enter \"A\" to guess the alphabet within the word.\nEnter \"B\" to guess the entire word." << endl;
                cin >> choiceAB;
                newLine();

                if (choiceAB != 'A' && choiceAB != 'B')
                {
                    cout << "The input is not an valid choice, please reselect!" << endl;
                    counter;
                }
                else if (choiceAB == 'A')
                {
                    counter++;
                    break;
                }
                else if (choiceAB == 'B')
                {
                    counter++;
                    enterWholeWord = true;
                    break;
                }
            }
        }
        attempts--;

        if (!enterWholeWord)
        {
            while (true)
            {
                cout << "Enter the guessing alphabet." << endl;
                cin >> guessChar;
                newLine();
                if (!isalpha(guessChar))
                {
                    cout << "The input is not an alphabet character, please reselect!" << endl;
                }
                else
                    break;
            }

            for (int i = 0; i < wordLength; i++)
            {
                if (guessChar == theWord.at(i))
                {
                    Arr[i] = guessChar;
                }
            }
        }
        else
        {
            cout << "Enter the word you guessing" << endl;
            cin >> currentWord;

            if (currentWord == theWord)
            {
                if (goFirst == 1)
                {
                    cout << "\nPlayer 2, you guess the word correctly!\n" << "PLAYER 2 WINS!!\n" << endl;
                    goPickABoard(2);
                    return;
                }
                else
                {
                    cout << "\nPlayer 1, you guess the word correctly!\n" << "PLAYER 1 WINS!!\n" << endl;
                    goPickABoard(1);
                    return;
                }
            }
            else
            {
                if (goFirst == 1 && attempts == 0 && guessplayerPower == 0)
                {
                    cout << "\nPlayer 2, you did not guess the word correctly!\n" << "PLAYER 1 WINS!!\n" << endl;
                    goPickABoard(1);
                    return;
                }
                else if (goFirst == 2 && attempts == 0 && guessplayerPower == 0)
                {
                    cout << "\nPlayer 1, you did not guess the word correctly!\n" << "PLAYER 2 WINS!!\n" << endl;
                    goPickABoard(2);
                    return;
                }
                else
                {
                    cout << "Guess incorrect! Try again." << endl;
                }
            }
        }

        if (attempts == 0 && guessplayerPower > 0)
        {
            char choice;
            while (true)
            {
                cout << "\nOh--ohh!! You just used up your attempts!!" << endl;
                cout << "\nDo you want to use your power to get three more attempts?" << endl;
                cout << "Enter 'y' for yes and 'n' for no." << endl;
                cout << "Choice: ";
                cin >> choice;
                newLine();
                if (choice == 'y')
                {
                    cout << "\nYou used one of your three powers!" << endl;
                    cout << "You have " << guessplayerPower - 1 << " Powers left." << endl;
                    cout << "Now, you have THREE more attempts.\n" << endl;
                    guessplayerPower--;
                    attempts = 3;
                    break;
                }
                else if (choice == 'n')
                {
                    cout << "You decided not to use your power!" << endl;
                    break;
                }
                else
                {
                    cout << "Enter a valid choice.\n\n";
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------
void StartWordGame(int goFirst, int& player1Power, int& player2Power)
{
    char choice;
    bool flag = true;
    int maxLength = 5;
    if ((player1Power > 0 && goFirst == 1) || (player2Power > 0 && goFirst == 2))
    {
        while (flag)
        {
            if (goFirst == 1)
            {
                cout << "Player 1:" << endl << "Do you want to use your power to increase the length limit from 5 to 7?" << endl;
            }
            else
            {
                cout << "Player 2:" << endl << "Do you want to use your power to increase the length limit from 5 to 7?" << endl;
            }
            cout << "Enter 'y' for yes and 'n' for no." << endl;
            cout << "Choice: ";
            cin >> choice;
            cout << endl;
            newLine();
            if (choice == 'y')
            {
                if (goFirst == 1)
                {
                    cout << "Player 1, You have chosen to use one of your remaining " << player1Power << " powers!" << endl;
                    cout << "You have " << player1Power - 1 << "-Powers left.\n" << endl;
                    player1Power--;
                }
                else
                {
                    cout << "Player 2, You have chosen to use one of your remaining " << player2Power << " powers!" << endl;
                    cout << "You have " << player2Power - 1 << "-Powers left.\n" << endl;
                    player2Power--;
                }
                maxLength = 7;
                flag = false;
            }
            else if (choice == 'n')
            {
                if (goFirst == 1)
                {
                    cout << "Player 1, You decided not to use your power!" << endl;
                    cout << "You have " << player1Power << "-Powers left.\n" << endl;
                }
                else
                {
                    cout << "Player 2, You decided not to use your power!" << endl;
                    cout << "You have " << player2Power << "-Powers left.\n" << endl;
                }
                flag = false;
            }
            else
            {
                cout << "Enter a valid choice.\n\n";
            }
        }
    }

    string guessWord = "";
    bool stringFlag = true;
    if (maxLength == 5)
    {

        srand(time(0));
        guessWord = Arr3[rand() % (sizeof(Arr3) / sizeof(Arr3[0]))];
    }
    else if (maxLength == 7)
    {
        srand(time(0));
        guessWord = Arr4[rand() % (sizeof(Arr4) / sizeof(Arr4[0]))];
    }

    maxLength = guessWord.length();

    if (goFirst == 1)
    {
        goGuessWord(1, maxLength, guessWord, player2Power);
    }
    else
    {
        goGuessWord(2, maxLength, guessWord, player1Power);
    }
}
//------------------------------------------------------------------------------------------------------------------------
int determineIfWin()
{
    if (Board[0][0] == Board[0][1] && Board[0][0] == Board[0][2])
    {
        if (Board[0][0] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[1][0] == Board[1][1] && Board[1][0] == Board[1][2])
    {
        if (Board[1][0] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[2][0] == Board[2][1] && Board[2][0] == Board[2][2])
    {
        if (Board[2][0] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[0][0] == Board[1][0] && Board[0][0] == Board[2][0])
    {
        if (Board[0][0] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[0][1] == Board[1][1] && Board[0][1] == Board[2][1])
    {
        if (Board[0][1] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[0][2] == Board[1][2] && Board[0][2] == Board[2][2])
    {
        if (Board[0][2] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[0][0] == Board[1][1] && Board[0][0] == Board[2][2])
    {
        if (Board[0][0] == 99)
            return 99;
        else
            return 100;
    }
    else  if (Board[0][2] == Board[1][1] && Board[0][2] == Board[2][0])
    {
        if (Board[0][2] == 99)
            return 99;
        else
            return 100;
    }
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------
bool determineFullBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] != 99 && Board[i][j] != 100)
            {
                return false;
            }
        }
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------------------
void SaveGameResult(int player1Power, int player2Power)
{
    ofstream outputFile;
    remove("GameSaveFile.txt");
    outputFile.open("GameSaveFile.txt");
    outputFile << player1Power << endl;
    outputFile << player2Power << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            outputFile << Board[i][j] << endl;
        }
    }
    outputFile.close();
}
//=========================================================================================================================================
int main() //MAIN FUNCTION
{
    int diceResult, player1, player2;
    int player1Power = 3;
    int player2Power = 3;
    int whoGoFirst = 0;
    int whichGame = 0;
    int winGame;
    bool fullBoard;

    int counter = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Board[i][j] = counter;
            counter++;
        }
    }

    cout << "                                       !! WELCOME TO THE GAME !!                                        \n";
    cout << "                                       =========================                                        \n\n";
    cout << "!!GAME RULES!!" << endl << "--------------" << endl;
    cout << "- Each Player has FIVE attempts and THREE powers.\n" << "- The winner of the \"Dice Game\" will start the Game.\n";
    cout << "- The winner of the \"Word-Guessing Game\" OR \"the Number-Guessing Game\" will secure a spot on the \"3X3 Score Board\".\n";
    cout << "- \"X\" represents Player 1, \"O\" represents Player 2."<< endl;
    cout << "- The first player to fill up THREE consecutive spots on the Board in any direction will win the entire Game.\n";
    cout << "- To save the game and resume it later, choose \"E\" when promoted.\n";
    cout << "- To retrieve the saved file, choose R or r and type \"GameSaveFile.txt\".\n";
    srand(time(0));
    while (true)
    {
        cout << endl << "THE SCORE BOARD" << endl << "---------------" << endl;
        PrintBoard();
        cout<<endl;
        menuPick(whoGoFirst, player1Power, player2Power);
        if (whoGoFirst == 1 || whoGoFirst == 2)
        {
            cout << "WINNER CHOOSES THE NEXT GAME" << endl << "----------------------------" << endl;
            cout << "Player " << whoGoFirst << ":" << endl;
            whichGame = PickWhichGame();
        }

        if (whichGame == 1)
        {
            srand(time(0));
            cout << "NUMBER-GUESSING GAME BEGINS!" << endl << "----------------------------" << endl;
            StartNumberGame(whoGoFirst, player1Power, player2Power);
        }
        else if (whichGame == 2)
        {
            srand(time(0));
            cout << "WORD-GUESSING GAME BEGINS!" << endl << "--------------------------" << endl;
            StartWordGame(whoGoFirst, player1Power, player2Power);
        }

        SaveGameResult(player1Power, player2Power);

        PrintBoard();
        cout << endl;

        winGame = determineIfWin();
        if (winGame == 99)
        {
            cout << "------------------!!!PLAYER 1 WINS THREE CONSECUTIVE SPOTS ON THE SCORE BOARD!!!------------------"<<endl;
            cout << "--------------------------------!!!CONGRATULATIONS!!!---------------------------------------------"<<endl;
            cout << "-----------------------------!!!PLAYER 1 WINS THE GAME!!!-----------------------------------------" << endl;
            break;
        }
        else if (winGame == 100)
        {
            cout << "------------------!!!PLAYER 2 WINS THREE CONSECUTIVE SPOTS ON THE SCORE BOARD!!!------------------"<<endl;
            cout << "--------------------------------!!!CONGRATULATIONS!!!---------------------------------------------"<<endl;
            cout << "-----------------------------!!!PLAYER 2 WINS THE GAME!!!-----------------------------------------" << endl;
            break;
        }

        fullBoard = determineFullBoard();
        if (fullBoard)
        {
            cout << "The board if full, the game will determine the winner by rolling the dices." << endl;
            while (true)
            {
                player1 = getDiceResult();
                cout << "Player 1 result : " << player1 << endl;
                player2 = getDiceResult();
                cout << "Player 2 result : " << player2 << endl;
                if (player1 > player2)
                {
                    cout << "By Dice Results, Player 1 wins the game!" << endl;
                    break;
                }
                else if (player1 < player2)
                {
                    cout << "By Dice Results, Player 2 wins the game!" << endl;
                    break;
                }
            }
            break;
        }
    }
    return 0;
}
//===========================================================================================================================================
