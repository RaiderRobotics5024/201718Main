// cTaxFunctions.cpp
#include "cTaxFunctions.h"

float cTaxFunctions::CalcHST( float price )
{
	float HST = price * 0.17f;
	
	float Total = price + HST;
	
	return Total;
}
