#include "Cost.hpp"


CostRecord Cost::Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next )
{
	CostRecord Record = {};

	Total_InvestmentDeductibleAmount += Constant_InvestmentDeductibleAmount;
	Total_WorkDeductibleAmount += Constant_WorkDeductibleAmount;
	Total_BusinessDeductibleAmount += Constant_BusinessDeductibleAmount;
	Total_OtherDeductibleAmount += Constant_OtherDeductibleAmount;
	Total_NonDeductibleAmount += Constant_NonDeductibleAmount;

	Record.Current_InvestmentDeductibleAmount = Total_InvestmentDeductibleAmount;
	Record.Current_WorkDeductibleAmount = Total_WorkDeductibleAmount;
	Record.Current_BusinessDeductibleAmount = Total_BusinessDeductibleAmount;
	Record.Current_OtherDeductibleAmount = Total_OtherDeductibleAmount;
	Record.Current_NonDeductibleAmount = Total_NonDeductibleAmount;

	return Record;
}