//Katia Lopez

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>

//1. Create four defines
#define numdice 5 //the number of dice set to 5
#define faces 6 //the number of faces per die set to 6
#define maxrolls 3 //the number of rolls set to 3
#define testrolls 23 //the number of test rolls set to 23

using namespace std;

//function from Test.cpp
string TestRollDice(vector<int> &);


//2. function named RollDice
void RollDice(vector<int> &dice)
{
    //fills each element with random numbers between 1 and number of faces
    int n = numdice - dice.size(); //number of dice that needs to be rolled/rerolled
    srand(time(NULL));
    for (int i=0; i< n; i++) 
    {
        //function rand() and srand() are used
        int randnum = rand() % faces + 1; //random number between 1 and 6
        dice.push_back(randnum); //use push_back to add to the vector
    }
}



//3. function named PrintRoll
void PrintRoll(vector<int> &dice)
{
    //ONLY prints the contents of the vector and no other text
    //use a range based for loop
    for (int x : dice)
        cout << x << " ";
}



//4. function named FillHowMany
void FillHowMany(vector<int> &dice, vector<int> &howMany)
{
    //ONLY use range based for loops
  
    for (int &it : howMany) //Initialize howMany vector to 0.
        it = 0; 

    for (int x : dice)
        howMany[x-1]++; //Loop over dice vector and determine how many of each face are showing.
}



//8. function named PickDice
void PickDice(vector<int> &dice)
{
    //print instructions
    cout << "\nPick which dice to reroll. Answer Y at the prompt to keep that die" << endl;

    //prompt user to decide whether or not to keep a die
    for(int i=0; i < dice.size(); i++)
    {
        string ans;
        cout << "\nKeep " <<  dice[i] << "? ";
        cin >> ans;

        if (ans == "n" || ans == "N")
        {
            //if user does not keep a die, vector member function erase() should be used to delete it
            dice.erase(dice.begin()+i);
            i--;
        }
    }
}



string Combination(vector<int> &howMany)
{
    //7 combinations:
    int ofAKind = 0;
    int FullHouse = 0;
    int TwoPair = 0;
    int CPPSlam = 0;
    int LargeStraight = 0;
    int SmallStraight = 0;

    string result;
    int i;
    for (i=0; i<howMany.size(); i++)
    {
        if (howMany[i] == 3) //if howMany[i] is 3, then add 3 to FullHouse
        {
            FullHouse = FullHouse + 3;
        }
        if(howMany[i] == 2) //if howMany[i] is 2, then add 2 to FullHouse and increment TwoPair
        {
            FullHouse = FullHouse + 2;
            TwoPair++;
        }
        if (howMany[i] == 5) //if howMany[i] is 5, then increment CPPSlam
        {
            CPPSlam++;
        }
        if(howMany[i] == 1)//if howMany[i] is 1, then increment LargeStraight
        {
            LargeStraight++;
        }
        else if (howMany[i] == 0 && LargeStraight>0 && LargeStraight<5)//else if howMany[i] is 0 and LargeStraight is greater than 0 and LargeStraight is less than 5
        {
            LargeStraight = 0; //then set LargeStraight equal to 0
        }
        if (howMany[i] >= 1)//if howMany[i] is greater than or equal to 1, then increment SmallStraight
        {
            SmallStraight++;
        }
        else if (howMany[i] == 0 && SmallStraight>0 && SmallStraight<4)//else if howMany[i] is 0 and SmallStraight is greater than 0 and SmallStraight is less than 4
        {
            SmallStraight = 0;//then set SmallStraight equal to 0
        }
        if (howMany[i] == 4)//if howMany[i] is 4, then set ofAKind to 4
        {
            ofAKind = 4;
        }
        if (howMany[i] == 3) //if howMany[i] is 3, then set ofAKind to 3
        {
            ofAKind =  3;
        }
    }


    //After checking every element of howMany
    if (LargeStraight == 5)//if LargeStraight is 5, then "Large Straight"
    {
        result = "Large Straight";
    }
    else if (SmallStraight >= 4)//else if SmallStraight is greater than or equal to 4, then "Small Straight"
    {
        result = "Small Straight";
    }
    else if (FullHouse == 5)//else if FullHouse is 5, then "Full House"
    {
        result = "Full House";
    }
    else if (CPPSlam == 1)//else if CPPSlam is 1, then "C++Slam!"
    {
        result = "C++Slam!";
    }
    else if (ofAKind == 4)//else if ofAKind is 4, then "Four of a Kind"
    {
        result = "Four of a Kind";
    }
    else if (ofAKind == 3) //else if ofAKind is 3, then "Three of a Kind"
    {
        result = "Three of a Kind";
    }
    else if (TwoPair == 2)//else if TwoPair == 2, then "Two Pair"
    {
        result = "Two Pair";
    }
    else
    {
        result = "You have nothing";
    }
    return result;
}



int main(int argc, char *argv[])
{
    //5. NO global variables, vectors must be declared in main
    vector<int> dice; 
    vector<int> howMany(faces);
    int rollcount = 0;
    string reroll;

    //6. check command line arguments,if it is run with TEST then going to use TestRollDice function in Test.cpp
    int testpass = 0;
    if (argc ==2 && strcmp(argv[1], "TEST") == 0)
    {
        do
        {
            string result;
            result = TestRollDice(dice);
            rollcount++;
            cout << "\n\nYou rolled ";
            PrintRoll(dice);
            cout << endl << result << endl;
                
            FillHowMany(dice, howMany);
            string result2;
            result2 = Combination(howMany);
                
            if (result == result2) //compare result with YOUR result from code
            {
                    cout << "Test Passed" << endl;
                    testpass++; //Test passed
            }
        }
        while (rollcount < testrolls); //use number of testrolls

        //print number of passes and fails
        int fail = testrolls - testpass;
        cout << endl << "Out of " << testrolls << " tests, " << testpass << " tests passed and " << fail << " tests failed." << endl;
    }
    else
    {       
        do //9. Game play should be controlled by a while/do-while loop in main
        {
            RollDice(dice);
            rollcount++;
            cout << "\n\nYou rolled "; 
            PrintRoll(dice);
            cout << "" << endl;

            //Loop over howMany
            FillHowMany(dice, howMany);

            string result = Combination(howMany);
            cout << result << endl;            

            
            if (rollcount < maxrolls)
            {
                cout << "\n\nDo you want to reroll? ";
                cin >> reroll;
                if ((reroll == "Y") || (reroll == "y"))
                {
                    PickDice(dice);
                }
           }

        }
        while (rollcount < maxrolls && (reroll == "y" || reroll == "Y"));
    }
    return 0;
}
