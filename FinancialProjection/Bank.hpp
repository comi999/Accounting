#pragma once
#include <iostream>
#include <string>
#include <map>

#include "Date.hpp"
#include "FinancialRecord.hpp"

class BankAccount;
class Job;
class RentalProperty;
class Cost;
class Tax;

struct BankLoanAccountRecord : RecordBase
{
	double Current_Loan = 0;
	double Current_InterestCharged = 0;
	double Current_PrincipalCharged = 0;
};

class BankLoanAccount final : public RecordGenerator< BankLoanAccount, BankLoanAccountRecord >
{
public:

	std::shared_ptr< BankAccount > Constant_OffsetAccount;

	double Constant_MinRepayment;
	double Constant_InterestRate;
	double Constant_StartingLoan;

	double Total_Loan;
	double Total_PrinciplePaid;
	double Total_InterestPaid;

	BankLoanAccountRecord Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override;
};

struct BankAccountRecord : RecordBase
{
	double Current_Balance = 0;
};

class BankAccount final : public RecordGenerator< BankAccount, BankAccountRecord >
{
public:

	std::vector< std::shared_ptr< BankLoanAccount > >	Constant_LoanAccounts;
	std::vector< std::shared_ptr< Job > >				Constant_Jobs;
	std::vector< std::shared_ptr< RentalProperty > >	Constant_RentalProperties;
	std::vector< std::shared_ptr< Cost > >				Constant_Costs;
	std::shared_ptr< Tax >								Constant_Taxes;

	double Total_Balance;

	BankAccountRecord Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override;
};

inline void Print( const BankAccountRecord& a_Record )
{
	std::cout << "Balance: " << a_Record.Current_Balance << '\n';
}

struct BankRecord : RecordBase
{
	
};

class Bank : public RecordGenerator< Bank, BankRecord >
{
public:

	BankRecord Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override
	{
		BankRecord Record;

		return Record;
	}
};

//struct BankTransactionDescriptor
//{
//	EFrequency Frequency;
//	float Amount;
//};
//
//struct BankAccountDescriptor
//{
//	float InitialBalance;
//	std::vector< BankTransactionDescriptor > BankTransactions;
//};
//
//enum class ELoanType
//{
//	Land,
//	House,
//	InvestmentLand,
//	InvestmentHouse,
//};
//
//struct BankLoanAccountDescriptor
//{
//	Date Started;
//	uint32_t LoanTerm;
//	ELoanType Type;
//	std::optional<std::string> OffsettingAccount;
//	float InitialBalance;
//	float InterestRate;
//	float MinRepayment;
//	EFrequency RepaymentFrequency;
//};
//
//struct BankDescriptor
//{
//	std::map< std::string, BankLoanAccountDescriptor > BankLoanAccounts;
//	std::map< std::string, BankAccountDescriptor > BankAccounts;
//};