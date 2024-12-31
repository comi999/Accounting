#pragma once
#include <memory>

#include "Date.hpp"
#include "FinancialRecord.hpp"

struct JobRecord : RecordBase
{
	double Current_Earned = 0;
	double Current_TaxWithheld = 0;
};

class Job : public RecordGenerator< Job, JobRecord >
{
public:

	double Constant_TaxWithheldFraction;
	double Constant_Wages;

	double Total_Earned;
	double Total_TaxWithheld;

	JobRecord Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override
	{
		JobRecord Record = {};

		const double TaxWithheld = Constant_TaxWithheldFraction * Constant_Wages;
		const double AfterTaxWage = Constant_Wages - TaxWithheld;

		Total_Earned += AfterTaxWage;
		Total_TaxWithheld += TaxWithheld;

		Record.Current_Earned = Total_Earned;
		Record.Current_TaxWithheld = Total_TaxWithheld;

		return Record;
	}
};