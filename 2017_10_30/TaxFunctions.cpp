// TaxFunctions.cpp
// Returns: price + HST
// Passes: price
float CalcHST( float price )
{
	// price = $5.99 
	// HST =   price * 0.13;
	// Total = price + HST;
	
	float HST = price * 0.13f;
	
	float Total = price + HST;
	
	return Total;
}







