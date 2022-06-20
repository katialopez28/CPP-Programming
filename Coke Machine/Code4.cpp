//Katia Lopez

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "CokeMachine.h"
#include "CokeLib.h"


using namespace std;

//functions from CokeLib.cpp
void get_command_line_params(int, char*[], string&, string&);
bool ParseCokeLine(const string&, vector<string>&);


//Create a menu in your .cpp file to use your Coke Machine.
int menu()
{
    int choice{};
    cout << "\n0. Walk away\n" << endl;
    cout << "1. Buy a Coke\n" << endl;
    cout << "2. Restock Machine\n" << endl;
    cout << "3. Add Change\n" << endl;
    cout << "4. Display Machine Info\n" << endl;
    cout << "5. Update Machine Name\n" << endl; //add menu item
    cout << "6. Update Coke Price\n\n" << endl; //add menu item

    cin >> choice;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');

        cout << "Input must be numeric. Please reenter: ";
        cin >> choice;
    }
    return choice;
}


int PickMachineMenu(vector<CokeMachine> &SetOfCokeMachines)
{
    int choice{};
    cout << "Pick a Coke Machine" << endl;
    cout << "\n0. Exit\n" << endl;

    for (int i=0; i<=SetOfCokeMachines.size(); i++)
    {
        if (i==SetOfCokeMachines.size())
        {
            cout << i+1 << ". " << "Add a new machine" << "\n" << endl;
        }
        else
        {
            cout << i+1 << ". " << SetOfCokeMachines.at(i).getMachineName() << "\n" << endl;
        }
    }

    cout << "Enter choice ";
    cin >> choice;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');

        cout << "Input must be numeric. Please reenter: ";
        cin >> choice;
    }
    return choice;
}



int main(int argc, char *argv[])
{  
    string input;
    string output;

    //Coding Requirement 7: use try catch block
    try
    {
        get_command_line_params(argc, argv, input, output); //use function from CokeLib
    }
    catch (invalid_argument &say) //catch and handle exception thrown by function
    {
        cerr << say.what() << endl;
        exit(0); //exit from program
    }



    vector<CokeMachine> SetOfCokeMachines; //create vector of type CokeMachine

    ifstream CokeInputFile{input}; //open file passed in with INPUTFILENAME
    string CokeMachineLine;
    vector <string> ConstructorValues(4); //machine name, inventory level, change level, price

    ofstream CokeOutputFile{output, ios::out}; //open file passed in with OUTPUTFILENAME

    if(CokeInputFile.is_open())
    {
        while(!CokeInputFile.eof()) //while not reaching EOF of CokeInputFile
        {
            getline(CokeInputFile, CokeMachineLine); //read a line from CokeInputFile into CokeMachineLine
            bool result = ParseCokeLine(CokeMachineLine, ConstructorValues);
            if(result) //true
            {
                /*using each of the elements returned in the vector ConstructorValues, 
                 construct temporary coke machine object */
                CokeMachine Temp(ConstructorValues.at(0), stoi(ConstructorValues.at(1)), stoi(ConstructorValues.at(2)), stoi(ConstructorValues.at(3))); //temporary coke machine object
                SetOfCokeMachines.push_back(Temp); //push temp object into SetOfCokeMachines vector
            }            
        }
    }
    else
    {
        cout << "Unable to open file" << endl;
        exit(0);
    }
    CokeInputFile.close();

    int choice=0;
    while(choice>=0 && choice<=SetOfCokeMachines.size()) //possible machine menu choices
    {
        choice = PickMachineMenu(SetOfCokeMachines);

        if (choice==0)
        {
            //8. write all current state of all Coke Machines to OUTPUTFILENAME 
            //each pipe delimited line of file output should be created by calling function CreateCokeOutputLine
            //pass in a machine, have the function create the line that needs to  be written to the file
            //return that string and simply << it to the output file
            if(CokeOutputFile.is_open())
            {
                for (int i=0; i<SetOfCokeMachines.size(); i++)
                {
                    //pass in a CokeMachine and get back a string, write that string to the file you opened(ouputfile)
                    string cm = CreateCokeOutputLine(SetOfCokeMachines.at(i));
                    CokeOutputFile << cm << "\n";
                }
                CokeOutputFile.close();
            }
            else
            {
                cout << "Unable to open file" << endl;
                exit(0);
            }
            return 0; //return to end program
        }
        else if (choice == SetOfCokeMachines.size()+1) //last choice which is to add new machine
        {
            //add a new machine name
            //call default constructor and add the new machine to the SetOfCokeMachines vector
            CokeMachine newMachine; //no braces to right of object 
            SetOfCokeMachines.push_back(newMachine);      
            cout << "New machine added" << endl;
        }
        else //its a machine so call original menu
        { 
            int option;
            do
            {
                option = menu();

                switch(option)
                {        
                    case 1:
                    {
                        //BuyACoke
                        int payment;
                        cout << "Insert payment ";
                        cin >> payment;

                        string change;
                        int action{};
                        bool result = SetOfCokeMachines.at(choice-1).buyACoke(payment, change, action); //bool buyACoke(int payment, std::string &change, int &action)
                        if (result) //true
                        {
                            switch(action)
                            {
                                case OK :
                                {
                                    //A Coke was sold and change was given
                                    cout << "\nHere's your Coke and your change of " << change << endl;
                                    break;
                                }
                                case EXACT_CHANGE :
                                {
                                    //A Coke was sold and exact payment was given and no change was needed
                                    cout << "\nThank you for the exact change.\nHere's your Coke." << endl;
                                    break;
                                }
                            }
                        }
                        else //false
                        {
                            switch(action)
                            {
                                case NO_INVENTORY :
                                {
                                    //not enough inventory to complete purchase
                                    cout << "\nThe machine does not have any Coke" << endl;
                                    break;
                                }
                                case NO_CHANGE :
                                {
                                    //not enough change was available to complete the purchase
                                    cout << "\nUnable to give change at this time...returning your payment" << endl;
                                    break;
                                }
                                case INSUFFICIENT :
                                {
                                    //the provided payment was insufficient (no sale took place)
                                    cout << "\nInsufficient payment... returning your payment" << endl;
                                    break;
                                }
                                case BOXFULL :
                                {
                                    cout << "\nChange box is full - call 1800IMFULL to get change removed..." << endl; 
                                    cout << "returning your payment" << endl;
                                    break;
                                }
                                default:
                                    cout << "\nCoke Machine is Out of Order" << endl;
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        //Restock Machine
                        int product;
                        cout << "How much product are you adding to the machine? ";
                        cin >> product;
                        if (SetOfCokeMachines.at(choice-1).incrementInventory(product))
                        {
                            cout << "\nYour machine has been restocked" << endl;
                            cout << "Your inventory level is now " << SetOfCokeMachines.at(choice-1).getInventoryLevel() << endl;
                        }
                        else
                        {
                            cout << "\nYou have exceeded your machine's max capacity" << endl;
                            cout << "Your inventory level is now " << SetOfCokeMachines.at(choice-1).getInventoryLevel() << endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        //Add change
                        int addchange;
                        cout << "How much change are you adding to the machine? ";
                        cin >> addchange;
                        if (SetOfCokeMachines.at(choice-1).incrementChangeLevel(addchange))
                        {
                            cout << "\nYour change has been updated" << endl;
                            cout << "Your change level is now " << SetOfCokeMachines.at(choice-1).getChangeLevel() << endl;
                        }
                        else
                        {
                            cout << "\nYou have exceeded your machine's max change capcity" << endl;
                            cout << "Your change level is now " << SetOfCokeMachines.at(choice-1).getChangeLevel() << endl;
                        }
                        break;
                    }
                    case 4:
                    {
                        //Display machine info
                        cout << SetOfCokeMachines.at(choice-1) << endl; //using operator overloading
                        break;
                    }
                    case 5:
                    {
                        //Update Machine Name
                        string newMachineName;
                        cout << "Enter a new machine name: ";
                        cin.ignore();
                        getline(cin, newMachineName);
                        SetOfCokeMachines.at(choice-1).setMachineName(newMachineName); //call new member function
                        cout << "Machine name has been updated" << endl;
                        break;
                    }
                    case 6:
                    {
                        //Update Coke Price
                        int newCokePrice;
                        cout << "Enter a new Coke Price" << endl;
                        cin >> newCokePrice;
                        SetOfCokeMachines.at(choice-1).setCokePrice(newCokePrice);
                        cout << "Coke price has been updated" << endl; 
                        break;
                    }
                    default:
                        cout << "\nAre you sure you aren't really THIRSTY and need a Coke?\n" << endl;
                }
            }
            while (option != 0);
        }
    }

    return 0;
}
