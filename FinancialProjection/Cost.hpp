#pragma once
#include "Record.hpp"

struct CostRecord : RecordBase
{
	double Current_InvestmentDeductibleAmount = 0;
	double Current_WorkDeductibleAmount = 0;
	double Current_BusinessDeductibleAmount = 0;
	double Current_OtherDeductibleAmount = 0;
	double Current_NonDeductibleAmount = 0;
};

class Cost final : public RecordGenerator< Cost, CostRecord >
{
public:

	std::string Constant_Name;

	double Constant_InvestmentDeductibleAmount = 0;
	double Constant_WorkDeductibleAmount = 0;
	double Constant_BusinessDeductibleAmount = 0;
	double Constant_OtherDeductibleAmount = 0;
	double Constant_NonDeductibleAmount = 0;


	double Total_InvestmentDeductibleAmount = 0;
	double Total_WorkDeductibleAmount = 0;
	double Total_BusinessDeductibleAmount = 0;
	double Total_OtherDeductibleAmount = 0;
	double Total_NonDeductibleAmount = 0;

	RecordType Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override;
};