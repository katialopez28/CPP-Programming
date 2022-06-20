//Katia Lopez

#include <iostream>
#include <sstream>
#include <fstream> 
#include "CokeMachine.h"

//use scope resolution operator to tie prototypes left in the class definition to actual member function code

//friend function
std::string CreateCokeOutputLine(CokeMachine& MyCokeMachine)
{
    std::ostringstream output;
    output << MyCokeMachine.getMachineName() << "|" << MyCokeMachine.CokePrice 
           << "|" << MyCokeMachine.changeLevel << "|" << MyCokeMachine.getInventoryLevel();
    std::string result = output.str();

    return result;
}


CokeMachine::CokeMachine() //default constructor
{
    //defaults for all parameters
    machineName = "New Machine";
    CokePrice = 50;
    changeLevel= 500;
    inventoryLevel = 100; 
}

CokeMachine::CokeMachine(std::string name, int price, int change, int inventory) // constructor
{
    machineName = name;
    CokePrice = price;
    changeLevel= change;
    inventoryLevel = inventory; 
}


CokeMachine::~CokeMachine() //destructor
{
    std::cout << "Coke Machine " << machineName << " has been destroyed" << std::endl; //message in destructor
}


//the << should be overloaded as a friend function in CokeMachine.cpp
std::ostream& operator<<(std::ostream& output, CokeMachine& MyCokeMachine)
{
    output << "\nMachine Name : " << MyCokeMachine.getMachineName()
           << "\n\nCurrent Inventory Level " << MyCokeMachine.getInventoryLevel()
           << "\nMax Inventory Capacity  " << MyCokeMachine.getMaxInventoryCapacity()
           << "\nCurrent Change Level    " << MyCokeMachine.getChangeLevel()
           << "\nMax Change Capacity     " << MyCokeMachine.getMaxChangeCapcity()
           << "\nCurrent Coke price is   " << MyCokeMachine.getCokePrice() << "\n";

    return output;
}


void CokeMachine::setMachineName(std::string newMachineName) //new member function
{
    machineName = newMachineName;
}


void CokeMachine::setCokePrice(int newCokePrice) //new member function
{
    CokePrice = newCokePrice;
}


std::string CokeMachine::getMachineName()
{
    return machineName;
}                                                                                                        


bool CokeMachine::buyACoke(int payment, std::string &change, int &action)
{
    //returns true/false to indicate whether or not the function worked
    //sets action to different values depending on what happened

    bool a {true}; //if Coke is bought return true

    if(maxChangeCapacity == changeLevel)
    {
        action = BOXFULL;
        a = false;
    }

    //c) Check if exact payment was entered or not
    else if (CokePrice == payment)
    {
        if (inventoryLevel >= 1) //b) Check inventory level
        {
            bool increaseCL = incrementChangeLevel(CokePrice);
            if (increaseCL) //true
            {
                //changeLevel = changeLevel + CokePrice; //increment change level
                inventoryLevel--;
                action = EXACT_CHANGE;
            }
            else
            {
                action = NO_CHANGE; 
                a = false;
            }
        }
        else
        {
            action = NO_INVENTORY;
            a = false; //returns false if no Coke is bought
        }
    }

    /*d) Check if enough change is already in the machine to give back change to the user. Money from the
    payment itself may not be used for providing change for the payment during the current transaction. */
    else if (payment > CokePrice) //change needs to be given
    {
        int chg {payment - CokePrice}; //calculating change

        if (inventoryLevel < 1) //b) Check inventory level
        {
            action = NO_INVENTORY;
            a = false;
        }
        else if (chg > changeLevel) //if ($4) is more than machine change ($2)
        {
            action = NO_CHANGE; //not enough change
            a = false; //pencil is NOT bought
        }
        else //chg < change
        {
            changeLevel = changeLevel + CokePrice;
            inventoryLevel--;
            change = displayMoney(chg);
            action = OK;
        }
    }

    //e) Check if insufficient payment was given
    else //payment < CokePrice
    {
        action = INSUFFICIENT;
        a = false;
    }

    return a;
}


int CokeMachine::getInventoryLevel() 
{
    return inventoryLevel;
}


int CokeMachine::getMaxInventoryCapacity()
{
    return maxInventoryCapacity;
}


bool CokeMachine::incrementInventory(int amountToAdd)
{
    bool b = true; //return true if it was able to add inventory
    int total = amountToAdd + inventoryLevel;
    if (total > maxInventoryCapacity)
        b = false;

    if(b == true)
        inventoryLevel = inventoryLevel + amountToAdd;

    return b;
}


std::string CokeMachine::getChangeLevel()
{
    std::string CL = displayMoney(changeLevel);
    return CL;
}


bool CokeMachine::incrementChangeLevel(int amountToAdd)
{
    //verifies that taking a payment will not exceed the change max capacity
    bool b = true;
    int total = amountToAdd + changeLevel;
    if (total > maxChangeCapacity)
        b = false;

    if (b == true)
        changeLevel = changeLevel + amountToAdd;            

    return b;
}       


std::string CokeMachine::getMaxChangeCapcity()
{
    std::string max = displayMoney(maxChangeCapacity);
    return max;
}


std::string CokeMachine::getCokePrice()
{
    std::string CP = displayMoney(CokePrice);
    return CP;
}


std::string CokeMachine::displayMoney(int amount)
{
    //converts pennies to dollars and cents into a string
    std::string dollars{std::to_string(amount / 100)};
    std::string cents{std::to_string(amount % 100)};
    std::string result{"$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents};
    return result;
}
