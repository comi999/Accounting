#include "Bank.hpp"

#include "Cost.hpp"
#include "Job.hpp"
#include "Rental.hpp"
#include "Tax.hpp"

BankLoanAccountRecord BankLoanAccount::Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next )
{
	BankLoanAccountRecord Record = {};

	const Date PreviousDay = Dates::IncrementDays( a_Date, -1 );
	const double Offset = Constant_OffsetAccount ? ( *Constant_OffsetAccount )[ PreviousDay ].Current_Balance : 0.0;

	const double OffsetLoan = Total_Loan > Offset ? Total_Loan - Offset : 0.0;
	const double InterestPaid = OffsetLoan * Constant_InterestRate / 12.0;
	const double PrincipalPaid = Constant_MinRepayment - InterestPaid;

	Total_InterestPaid += InterestPaid;
	Total_PrinciplePaid += PrincipalPaid;
	Total_Loan -= PrincipalPaid;

	Record.Current_Loan = Total_Loan;
	Record.Current_InterestCharged = Total_InterestPaid;
	Record.Current_PrincipalCharged = Total_PrinciplePaid;

	return Record;
}

BankAccountRecord BankAccount::Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next )
{
	const Date PreviousDay = Dates::IncrementDays( a_Date, -1 );

	// Process all loan accounts
	double TotalRepaymentsCharged = 0;
	for ( auto& LoanAccount : Constant_LoanAccounts )
	{
		const BankLoanAccountRecord Record = ( *LoanAccount )[ PreviousDay ];

		TotalRepaymentsCharged += Record.Current_PrincipalCharged + Record.Current_InterestCharged;
	}

	// Process all jobs
	double TotalIncome = 0;
	for ( auto& Job : Constant_Jobs )
	{
		const JobRecord Record = ( *Job )[ PreviousDay ];

		TotalIncome += Record.Current_Earned;
	}

	// Process all rental properties
	for ( auto& RentalProperty : Constant_RentalProperties )
	{
		const RentalPropertyRecord Record = ( *RentalProperty )[ PreviousDay ];

		TotalIncome += Record.Current_RentTotal - Record.Current_ManagementFeesTotal - Record.Current_RentalCostsTotal;
	}

	// Process all costs
	double TotalCosts = 0;
	for ( auto& Cost : Constant_Costs )
	{
		const CostRecord Record = ( *Cost )[ PreviousDay ];

		TotalCosts += 
			Record.Current_InvestmentDeductibleAmount + 
			Record.Current_BusinessDeductibleAmount + 
			Record.Current_WorkDeductibleAmount + 
			Record.Current_OtherDeductibleAmount + 
			Record.Current_NonDeductibleAmount;
	}

	// Process all tax returns
	double TotalTaxRefund = Constant_Taxes ? ( *Constant_Taxes )[ PreviousDay ].ThisTime_TaxRefund : 0.0;

	Total_Balance = TotalIncome - TotalRepaymentsCharged - TotalCosts + TotalTaxRefund;

	BankAccountRecord Record = {};

	Record.Current_Balance = Total_Balance;

	return Record;
}