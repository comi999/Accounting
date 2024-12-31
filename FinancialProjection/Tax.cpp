#include "Tax.hpp"

#include "Cost.hpp"
#include "Job.hpp"
#include "Rental.hpp"

const TaxBracketTable TaxBracketTable::FY_23_24 = []
{
    TaxBracketTable Table;
    Table.AddBracket( 0, 0 );
    Table.AddBracket( 18200, 0.19 );
    Table.AddBracket( 45000, 0.325 );
    Table.AddBracket( 120000, 0.37 );
    Table.AddBracket( 180000, 0.45 );
    return Table;
}();

const TaxBracketTable TaxBracketTable::FY_24_25 = []
{
	TaxBracketTable Table;
    Table.AddBracket( 0, 0 );
    Table.AddBracket( 18200, 0.16 );
    Table.AddBracket( 45000, 0.30 );
    Table.AddBracket( 135000, 0.37 );
    Table.AddBracket( 190000, 0.45 );
	return Table;
}();

const StudentLoanRepaymentTable StudentLoanRepaymentTable::FY_23_24 = []
{
	StudentLoanRepaymentTable Table;
	Table.AddBracket( 0		, 0.000 );
	Table.AddBracket( 51550 , 0.010 );
	Table.AddBracket( 59518	, 0.020 );
	Table.AddBracket( 63089 , 0.025 );
	Table.AddBracket( 66875 , 0.030 );
	Table.AddBracket( 70888 , 0.035 );
	Table.AddBracket( 75140 , 0.040 );
	Table.AddBracket( 79649 , 0.045 );
	Table.AddBracket( 84429 , 0.050 );
	Table.AddBracket( 89494 , 0.055 );
	Table.AddBracket( 94865 , 0.060 );
	Table.AddBracket( 100557, 0.065 );
	Table.AddBracket( 106590, 0.070 );
	Table.AddBracket( 112985, 0.075 );
	Table.AddBracket( 119764, 0.080 );
	Table.AddBracket( 126950, 0.085 );
	Table.AddBracket( 134568, 0.090 );
	Table.AddBracket( 142642, 0.095 );
	Table.AddBracket( 151200, 0.100 );
	return Table;
}();

const StudentLoanRepaymentTable StudentLoanRepaymentTable::FY_24_25 = []
{
	StudentLoanRepaymentTable Table;
	Table.AddBracket( 0		, 0.000 );
	Table.AddBracket( 54435	, 0.010 );
	Table.AddBracket( 62850	, 0.020 );
	Table.AddBracket( 66620	, 0.025 );
	Table.AddBracket( 70618	, 0.030 );
	Table.AddBracket( 74855	, 0.035 );
	Table.AddBracket( 79346	, 0.040 );
	Table.AddBracket( 84107	, 0.045 );
	Table.AddBracket( 89154	, 0.050 );
	Table.AddBracket( 94503	, 0.055 );
	Table.AddBracket( 100174, 0.060 );
	Table.AddBracket( 106185, 0.065 );
	Table.AddBracket( 112556, 0.070 );
	Table.AddBracket( 119309, 0.075 );
	Table.AddBracket( 126467, 0.080 );
	Table.AddBracket( 134056, 0.085 );
	Table.AddBracket( 142100, 0.090 );
	Table.AddBracket( 150626, 0.095 );
	Table.AddBracket( 159663, 0.100 );
	return Table;
}();

TaxRecord Tax::Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next )
{
	TaxRecord Record = {};

	Date FYEnd = 1d / July / a_Date.year(), FYStart;

	if ( a_Date >= FYEnd )
	{
		FYStart = 1d / July / ( a_Date.year() - years{ 1 } );
	}
	else
	{
		FYEnd = 1d / July / ( a_Date.year() - years{ 1 } );
		FYStart = FYEnd - years{ 1 };
	}

	Record.FYFrom = FYStart;
	Record.FYTo = FYEnd;

	// Calculate total income. This can come from rental properties or a job.
	double Income = 0;
	double TaxWithheld = 0;
	double InvestmentDeductions = 0;
	double NonInvestmentDeductions = 0;

	for ( auto& Job : Constant_Jobs )
	{
		const JobRecord RecordEnd = ( *Job )[ FYEnd ];
		const JobRecord RecordStart = ( *Job )[ FYStart ];

		Income += RecordEnd.Current_Earned - RecordStart.Current_Earned;
		TaxWithheld += RecordEnd.Current_TaxWithheld - RecordStart.Current_TaxWithheld;
	}

	for ( auto& RentalProperty : Constant_RentalProperties )
	{
		const RentalPropertyRecord RecordEnd = ( *RentalProperty )[ FYEnd ];
		const RentalPropertyRecord RecordStart = ( *RentalProperty )[ FYStart ];

		Income += RecordEnd.Current_RentTotal - RecordStart.Current_RentTotal;

		InvestmentDeductions += 
			( RecordEnd.Current_ManagementFeesTotal - RecordStart.Current_ManagementFeesTotal ) + 
			( RecordEnd.Current_RentalCostsTotal - RecordStart.Current_RentalCostsTotal ) + 
			( RecordEnd.Current_PreStructuredHouseLoanInterest - RecordStart.Current_PreStructuredHouseLoanInterest ) + 
			( RecordEnd.Current_HouseLoanInterest - RecordStart.Current_HouseLoanInterest ) + 
			( RecordEnd.Current_LandLoanInterest - RecordStart.Current_LandLoanInterest );

		// Also add in depreciation cost.
		InvestmentDeductions += RentalProperty->Constant_DepreciationSchedule[ ( int32_t )FYStart.year() ];
	}

	for ( auto& Cost : Constant_Costs )
	{
		const CostRecord RecordEnd = ( *Cost )[ FYEnd ];
		const CostRecord RecordStart = ( *Cost )[ FYStart ];

		InvestmentDeductions +=
			( RecordEnd.Current_InvestmentDeductibleAmount - RecordStart.Current_InvestmentDeductibleAmount );

		NonInvestmentDeductions +=
			( RecordEnd.Current_BusinessDeductibleAmount - RecordStart.Current_BusinessDeductibleAmount ) +
			( RecordEnd.Current_WorkDeductibleAmount - RecordStart.Current_WorkDeductibleAmount ) +
			( RecordEnd.Current_OtherDeductibleAmount - RecordStart.Current_OtherDeductibleAmount );
	}

	Record.ThisTime_GrossIncome = Income + TaxWithheld;
	Record.ThisTime_TaxWithheld = TaxWithheld;
	Record.ThisTime_InvestmentDeductions = InvestmentDeductions;
	Record.ThisTime_NonInvestmentDeductions = NonInvestmentDeductions;
	Record.ThisTime_RepaymentIncome = Record.ThisTime_GrossIncome - Record.ThisTime_NonInvestmentDeductions;
	Record.ThisTime_TaxableIncome = Record.ThisTime_GrossIncome - Record.ThisTime_InvestmentDeductions - Record.ThisTime_NonInvestmentDeductions;
	Record.ThisTime_MedicareLevy = 0.02 * Record.ThisTime_TaxableIncome;

	const double StudentLoanLeft = Constant_StudentLoan - Total_StudentLoanRepayment;
	const double StudentLoanRepayment = StudentLoanRepaymentTable::CalculateRepayment( ( int32_t )FYStart.year(), Record.ThisTime_RepaymentIncome );
	const double StudentLoanToRepay = StudentLoanLeft > StudentLoanRepayment ? StudentLoanRepayment : StudentLoanLeft;
	Total_StudentLoanRepayment += StudentLoanToRepay;

	Record.ThisTime_StudentLoanRepayment = StudentLoanToRepay;
	Record.ThisTime_StudentLoanLeft = StudentLoanLeft - Record.ThisTime_StudentLoanRepayment;

	Record.ThisTime_Tax = TaxBracketTable::CalculateTax( ( int32_t )FYStart.year(), Record.ThisTime_TaxableIncome );
	Record.ThisTime_TaxToPay = Record.ThisTime_StudentLoanRepayment + Record.ThisTime_MedicareLevy + Record.ThisTime_Tax;
	Record.ThisTime_TaxRefund = Record.ThisTime_TaxWithheld - Record.ThisTime_TaxToPay;

	Record.Total_GrossIncome += Record.ThisTime_GrossIncome;
	Record.Total_TaxWithheld += Record.ThisTime_TaxWithheld;
	Record.Total_InvestmentDeductions += Record.ThisTime_InvestmentDeductions;
	Record.Total_NonInvestmentDeductions += Record.ThisTime_NonInvestmentDeductions;
	Record.Total_RepaymentIncome += Record.ThisTime_RepaymentIncome;
	Record.Total_TaxableIncome += Record.ThisTime_TaxableIncome;
	Record.Total_MedicareLevy += Record.ThisTime_MedicareLevy;
	Record.Total_StudentLoanRepayment += Record.ThisTime_StudentLoanRepayment;
	Record.Total_StudentLoanLeft = Record.ThisTime_StudentLoanLeft;
	Record.Total_Tax += Record.ThisTime_Tax;
	Record.Total_TaxToPay += Record.ThisTime_TaxToPay;
	Record.Total_TaxRefund += Record.ThisTime_TaxRefund;

	return Record;
}