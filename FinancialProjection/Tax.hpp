#pragma once
#include <vector>
#include <map>

#include "Record.hpp"

class Job;
class RentalProperty;
class Cost;

struct TaxBracket
{
	double IncomeOver;
	double IncomeLump;
	double Percentage;
};

class TaxBracketTable
{
public:

	TaxBracketTable() = default;

	static double CalculateTax( const uint32_t a_Year, const double a_Income )
	{
		const TaxBracketTable* Table;

		if ( a_Year <= 23 )
		{
			Table = &FY_23_24;
		}
		else
		{
			Table = &FY_24_25;
		}

		const TaxBracket* Previous = nullptr;

		for ( const TaxBracket& Bracket : Table->m_Brackets )
		{
			if ( a_Income < Bracket.IncomeOver )
			{
				break;
			}

			Previous = &Bracket;
		}

		if ( !Previous )
		{
			return 0;
		}

		return ( a_Income - Previous->IncomeOver ) * Previous->Percentage + Previous->IncomeLump;
	}

	static double GetTaxFreeThreshhold( const uint32_t a_Year )
	{
		const TaxBracketTable* Table;

		if ( a_Year <= 23 )
		{
			Table = &FY_23_24;
		}
		else
		{
			Table = &FY_24_25;
		}

		for ( const TaxBracket& Bracket : Table->m_Brackets )
		{
			if ( Bracket.Percentage != 0.0f )
			{
				return Bracket.IncomeOver;
			}
		}

		return 0.0;
	}

private:

	void AddBracket( const double a_IncomeOver, const double a_Percentage )
	{
		TaxBracket* Previous = m_Brackets.size() > 0ull ? &m_Brackets.back() : nullptr;
		const double PreviousIncomeRange = Previous ? a_IncomeOver - Previous->IncomeOver : 0;
		const double PreviousIncomePercentage = Previous ? Previous->Percentage : 0;
		const double PreviousLump = Previous ? Previous->IncomeLump : 0;
		const double Lump = PreviousLump + PreviousIncomeRange * PreviousIncomePercentage;

		TaxBracket& Bracket = m_Brackets.emplace_back();
		Bracket.IncomeOver = a_IncomeOver;
		Bracket.Percentage = a_Percentage;
		Bracket.IncomeLump = Lump;
	}

	std::vector< TaxBracket > m_Brackets;

public:

	static const TaxBracketTable FY_23_24;
	static const TaxBracketTable FY_24_25;
};

struct StudentLoanRepaymentBracket
{
	double IncomeOver;
	double Percentage;
};

class StudentLoanRepaymentTable
{
public:

	StudentLoanRepaymentTable() = default;

	static double CalculateRepayment( const uint32_t a_Year, const double a_RepaymentIncome )
	{
		const StudentLoanRepaymentTable* Table;

		if ( a_Year <= 23 )
		{
			Table = &FY_23_24;
		}
		else
		{
			Table = &FY_24_25;
		}

		const StudentLoanRepaymentBracket* Previous = nullptr;

		for ( const StudentLoanRepaymentBracket& Bracket : Table->m_Brackets )
		{
			if ( a_RepaymentIncome < Bracket.IncomeOver )
			{
				break;
			}

			Previous = &Bracket;
		}

		if ( !Previous )
		{
			return 0;
		}

		return Previous->Percentage * a_RepaymentIncome;
	}

private:

	void AddBracket( const double a_IncomeOver, const double a_Percentage )
	{
		m_Brackets.emplace_back( StudentLoanRepaymentBracket{ a_IncomeOver, a_Percentage } );
	}

	std::vector< StudentLoanRepaymentBracket > m_Brackets;

public:

	static const StudentLoanRepaymentTable FY_23_24;
	static const StudentLoanRepaymentTable FY_24_25;
};

using DepreciationSchedule = std::map<uint32_t, double>;

struct TaxRecord : RecordBase
{
	Date FYFrom;
	Date FYTo;

	double ThisTime_InvestmentDeductions = 0;
	double ThisTime_NonInvestmentDeductions = 0;
	double ThisTime_MedicareLevy = 0;
	double ThisTime_StudentLoanRepayment = 0;
	double ThisTime_StudentLoanLeft = 0;
	double ThisTime_GrossIncome = 0;
	double ThisTime_RepaymentIncome = 0;
	double ThisTime_TaxableIncome = 0;
	double ThisTime_Tax = 0;
	double ThisTime_TaxWithheld = 0;
	double ThisTime_TaxToPay = 0;
	double ThisTime_TaxRefund = 0;

	double Total_InvestmentDeductions = 0;
	double Total_NonInvestmentDeductions = 0;
	double Total_MedicareLevy = 0;
	double Total_StudentLoanRepayment = 0;
	double Total_StudentLoanLeft = 0;
	double Total_GrossIncome = 0;
	double Total_RepaymentIncome = 0;
	double Total_TaxableIncome = 0;
	double Total_Tax = 0;
	double Total_TaxWithheld = 0;
	double Total_TaxToPay = 0;
	double Total_TaxRefund = 0;
};

class Tax final : public RecordGenerator< Tax, TaxRecord >
{
public:

	std::vector< std::shared_ptr< Job > >				Constant_Jobs;
	std::vector< std::shared_ptr< RentalProperty > >	Constant_RentalProperties;
	std::vector< std::shared_ptr< Cost > >				Constant_Costs;
	double												Constant_StudentLoan;

	double Total_InvestmentDeductions;
	double Total_MedicareLevy;
	double Total_StudentLoanRepayment;
	double Total_GrossIncome;
	double Total_RepaymentIncome;
	double Total_TaxableIncome;
	double Total_Tax;
	double Total_TaxWithheld;
	double Total_TaxToPay;
	double Total_TaxRefund;

	TaxRecord Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override;
};