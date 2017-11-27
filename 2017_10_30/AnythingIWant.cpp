#include "TaxFunctions.h"		// fucntion
#include "cTaxFunctions.h"		// class
#include <iostream>
#include <string>

//float CalcHST( float price );

int main()
{
//	int x;
	cTaxFunctions y;
	
	float price = 9.99f;
	float total = y.CalcHST(price);
	std::cout << total;
	
//	cTheRobot bob;
//	bob.DriveForward(10.0f;
	
	
	return 0;
}





