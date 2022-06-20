/*
    Testing Module for Coding Assignment 2
 */

#include <iostream>
#include <vector>

std::string TestRollDice(std::vector<int> &dice)
{
	static int testCase = 1;
	std::string Result;
	
	std::vector<int> CSdice{1,1,1,1,1};		 
	std::vector<int> FHdice1{1,1,2,2,2}; 
	std::vector<int> FHdice2{1,1,1,2,2}; 
	std::vector<int> FHdice3{2,3,2,3,2};
	std::vector<int> LSdice1{1,2,3,4,5}; 
	std::vector<int> LSdice2{2,3,4,5,6}; 
	std::vector<int> LSdice3{3,4,1,2,5};
	std::vector<int> SSdice1{1,2,3,4,6}; 
	std::vector<int> SSdice2{2,3,4,5,5}; 
	std::vector<int> SSdice3{3,4,5,6,1}; 
	std::vector<int> SSdice4{6,1,2,3,4}; 
	std::vector<int> SSdice5{5,2,3,4,5}; 
	std::vector<int> SSdice6{1,3,4,5,6};
	std::vector<int> SSdice7{3,5,1,6,4};
	std::vector<int> TwoPair1{1,1,2,2,3};
	std::vector<int> TwoPair2{4,5,5,6,6};
	std::vector<int> TwoPair3{1,5,2,5,1};
	std::vector<int> ThreeKind1{1,1,1,2,3};
	std::vector<int> ThreeKind2{1,6,2,6,6};
	std::vector<int> ThreeKind3{3,4,2,2,2};
	std::vector<int> FourKind1{1,1,1,1,2}; 
	std::vector<int> FourKind2{3,2,2,2,2}; 
	std::vector<int> FourKind3{3,6,3,3,3}; 

	switch(testCase)
	{
		case 1:  
			dice = CSdice;
			Result = "C++Slam!"; 
			break;
		case 2:  
			dice = FHdice1; 
			Result = "Full House"; 
			break;
		case 3:  
			dice = FHdice2;
			Result = "Full House"; 
			break;
		case 4:  
			dice = FHdice3;
			Result = "Full House"; 
			break;     
		case 5:  
			dice = LSdice1;
			Result = "Large Straight"; 
			break;
		case 6:  
			dice = LSdice2;
			Result = "Large Straight"; 
			break;
		case 7:  
			dice = LSdice3;
			Result = "Large Straight"; 
			break;     
		case 8:  
			dice = SSdice1;
			Result = "Small Straight"; 
			break;
		case 9:  
			dice = SSdice2;
			Result = "Small Straight"; 
			break;
		case 10: 
			dice = SSdice3;
			Result = "Small Straight"; 
			break;
		case 11: 
			dice = SSdice4;
			Result = "Small Straight"; 
			break;
		case 12: 
			dice = SSdice5;
			Result = "Small Straight"; 
			break;
		case 13: 
			dice = SSdice6;
			Result = "Small Straight"; 
			break;
		case 14: 
			dice = SSdice7;
			Result = "Small Straight"; 
			break;
		case 15: 
			dice = TwoPair1;
			Result = "Two Pair"; 
			break;
		case 16: 
			dice = TwoPair2;
			Result = "Two Pair"; 
			break;
		case 17: 
			dice = TwoPair3;
			Result = "Two Pair"; 
			break;     
		case 18: 
			dice = ThreeKind1;
			Result = "Three of a Kind"; 
			break;
		case 19: 
			dice = ThreeKind2;
			Result = "Three of a Kind"; 
			break;
		case 20: 
			dice = ThreeKind3;
			Result = "Three of a Kind"; 
			break;
		case 21: 
			dice = FourKind1;
			Result = "Four of a Kind"; 
			break;
		case 22: 
			dice = FourKind2;
			Result = "Four of a Kind"; 
			break;
		case 23: 
			dice = FourKind3;
			Result = "Four of a Kind"; 
			break;
	}
	testCase++;
	return Result;
}
