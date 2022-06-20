//Katia Lopez

#include <iostream>
#include <string>
#define price 60 //1. Pencil price must be a define and not hard-coded
using namespace std;


//The enum definition should be OUTSIDE of all functions at the top of the program
enum status{OK=4, EXACT_CHANGE=5, NO_INVENTORY=6, NO_CHANGE=7, INSUFFICIENT=8};


//2. Create a function to display any money amounts
std::string moneyConversion(int a)
{
	std::string dollars{std::to_string(a / 100)};
	std::string cents{std::to_string(a % 100)};
	std::string amount{"$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents};
	return amount;
}


//3. Create a function to buy pencils
/*The function to buy pencils has a return type of boolean and a parameter that tells main() the status of the transaction.
The value of status has been enumerated.
a) No cins or couts in the buy a pencil function. */
bool buyPencils(int numpen, int total, int payment, int &inv, int &change, int &status1) //pass by reference
{
    bool a {true}; //if pencil is bought return true

    //c) Check if exact payment was entered or not
    if (total == payment)
    {
        if (inv >= numpen) //b) Check inventory level
        {
            inv = inv - numpen;
            change = change + total;
            status1 = EXACT_CHANGE;
        }
        else
        {
            status1 = NO_INVENTORY;
            a = false; //returns false if no pencil is bought
        }
    }

    /*d) Check if enough change is already in the machine to give back change to the user. Money from the
        payment itself may not be used for providing change for the payment during the current transaction.
        For example, if the required payment is $6.00 and the user gives a payment of $10.00 and there is $2.00
        of change in the machine, then the machine should not accept the payment since $4.00 of change is
        required and the machine only contains $2.00 of change. Payment amount should be added to change
        level after change has been given. */
    else if (payment > total) //change needs to be given
    {
        int chg {payment - total}; //$4.00 of change required

        if (inv < numpen) //b) Check inventory level
        {
            status1 = NO_INVENTORY;
            a = false;
        }
        else if (chg > change) //if ($4) is more than machine change ($2)
        {
            a = false; //pencil is NOT bought
            status1 = NO_CHANGE; //not enough change
        }
        else //chg < change
        {
            change = change + total;
            inv = inv - numpen;
            status1 = OK;
        }
    }

    //e) Check if insufficient payment was given
    else //payment < total
    {
        status1 = INSUFFICIENT;
        a = false;
    }

    return a;
}


//4. Create a function to handle the menu
int menu()
{
    int choice{};
    cout << "\nPlease choose from the following options\n\n" << endl;
    cout << "0. No pencils for me today" << endl;
    cout << "1. Purchase pencils" << endl;
    cout << "2. Check inventory level" << endl;
    cout << "3. Check change level\n" << endl;

    cout << "Choice: ";
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');

        cout << "Input must be numeric. Please reenter: ";
        cin >> choice;
    }

    return choice;
}



int main(void)
{
    cout << "Welcome to my Pencil Machine\n" << endl;

    //5. variables for checking inventory and change level
    int inventory{100}; //100 pencils
    int change{500}; //500 cents

    int option = menu();
    do
    {
        //6. Create a switch statement that acts upon menu choice returned by menu handling function
        switch(option)
        {
            case 0:
            {
                return 0; //exit program
            }
            case 1: //if (option == 1)
            {
                if (inventory <= 0)
                {
                    cout << "This Pencil Dispenser is out of inventory." << endl;
                    option = menu();
                }
                if (option != 1)
                {
                    break;
                }

                //Purchase pencils
                int numpencils{};
                string cost {moneyConversion(price)};
                cout << "\nA pencil costs " << cost << endl;
                cout << "\nHow many pencils would you like to purchase? ";
                cin >> numpencils;

                if (cin.fail()) //if user does not input NUMBER (int) of pencils
                {
                    cin.clear();
                    cin.ignore(32767, '\n');

                    cout << "\nInput must be numeric. Please reenter: ";
                    cin >> numpencils;
                }

                if(numpencils > inventory)
                {
                    string invstr{to_string(inventory)};
                    cout << "\nThe machine does not have that many pencils - buy " << invstr << " or fewer" << endl; 
                    option = menu();
                }
                if (option != 1)
                {
                    break;
                }

                if (numpencils <= 0)
                {
                    cout << "\nYou must purchase at least one pencil." << endl;
                    option = menu();
                }
                else
                {
                    int total{price * numpencils};
                    string totalstr{moneyConversion(total)};
                    cout << "\nYour total is " << totalstr << endl;

                    int payment{};
                    cout << "\nEnter your payment (in cents) ";
                    cin >> payment;
                    if (cin.fail()) //if user does not input payment (int)
                    {
                        cin.clear();
                        cin.ignore(32767, '\n');

                        cout << "\nInput must be numeric. Please reenter ";
                        cin >> payment;
                    }

                    int status1{};
                    bool a = buyPencils(numpencils, total, payment, inventory, change, status1);


                    //Status should have at least 5 different values - OK, no inventory, no change, insufficient funds and exact change
                    //7. Based on the status returned by buyPencil function, print the messages in main() to the user shown in video
                    switch(status1)
                    {
                        case OK :
                        {
                            //Pencils were sold and change was given
                            int c {payment - total};
                            string cstring{moneyConversion(c)};
                            cout << "\nHere's your pencils and your change of " << cstring << endl;
                            break;
                        }
                        case EXACT_CHANGE :
                        {
                            //Pencils were sold and exact payment was given and no change was needed
                            cout << "\nHere's your pencils. Thank you for exact payment" << endl;
                            break;
                        }
                        case NO_INVENTORY :
                        {
                            //not enough inventory to complete purchase
                            /*string invstr{to_string(inventory)};
                            cout << "\nThe machine does not have that many pencils - buy " << invstr << "or fewer" << endl;*/
                            break;
                        }
                        case NO_CHANGE :
                        {
                            //not enough change was available to complete the purchase
                            cout << "\nThe Pencil Dispenser does not have enough change and cannot accept your payment." << endl;
                            break;
                        }
                        case INSUFFICIENT :
                        {
                            //the provided payment was insufficient (no sale took place)
                            cout << "\nYou did not enter a sufficient payment. No pencils for you." << endl;
                            break;
                        }
                    }
                    option = menu();
                }
            }
            break;

            case 2:
            {
                cout << "The current inventory level is " << inventory << endl;
                option = menu();
            }
            break;

            case 3:
            {
                cout << "The current change level is " << change << endl;
                option = menu();
            }
            break;

            default:
            {
                cout << "Invalid menu choice. Please choose again." << endl;
                option = menu();
            }
        }

    }
    while (option != 0); //if option is 0, system will exit
    return 0;

}
