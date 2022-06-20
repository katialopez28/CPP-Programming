//Katia Lopez

enum status{OK=5, EXACT_CHANGE=6, NO_INVENTORY=7, NO_CHANGE=8, INSUFFICIENT=9, BOXFULL=10}; //The enum definition

//include guard
#ifndef COKE_MACHINE_H
#define COKE_MACHINE_H

//only prototypes and data members should reside in CokeMachine.h
class CokeMachine
{
    //friend declarations
    friend std::string CreateCokeOutputLine(CokeMachine&);
    friend std::ostream& operator<<(std::ostream&, CokeMachine&);//const CokeMachine&); //operator overloading

    public:
        //member function prototypes:
        CokeMachine(); //default constructor

        CokeMachine(std::string, int, int, int); //constructor

        ~CokeMachine(); //destructor

        //ostream& operator<<(ostream&, const CokeMachine&); //operator overloading

        void setMachineName(std::string); //new member function

        void setCokePrice(int); //new member function
        
        std::string getMachineName();

        bool buyACoke(int, std::string&, int&);

        int getInventoryLevel();

        int getMaxInventoryCapacity();

        bool incrementInventory(int);

        std::string getChangeLevel();

        bool incrementChangeLevel(int);    

        std::string getMaxChangeCapcity();

        std::string getCokePrice();

        std::string displayMoney(int);


    private:
        //data members
        std::string machineName;
        int changeLevel;
        int maxChangeCapacity{5000};
        int CokePrice;
        int inventoryLevel;
        int maxInventoryCapacity{100};
};

#endif
