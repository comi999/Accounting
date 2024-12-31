#include <complex>
#include <iostream>

#include "Bank.hpp"
#include "Date.hpp"
#include "Rental.hpp"
#include "Job.hpp"
#include "Tax.hpp"
#include "Cost.hpp"

template < typename _State, typename _Record >
void Print( const RecordGenerator< _State, _Record >& a_RecordGenerator )
{
	for ( auto& Record : a_RecordGenerator.Records )
	{
		std::cout << Record.When << '\n';
		Print( Record );
		std::cout << '\n';
	}
}

constexpr Date Final = 31d / December / 2030;

std::shared_ptr< RentalProperty > CreateRentalProperty()
{
	std::shared_ptr< RentalProperty > RentalProperty( new class RentalProperty );
	RentalProperty->Start = 20d / April / 2023;
	RentalProperty->End = Final;
	RentalProperty->Frequency = EFrequency::Monthly;
	RentalProperty->Constant_Address = "94 Moncrieff Parade, Golden Bay 2174, WA";
	RentalProperty->Constant_LandBought = 20d / April / 2023;
	RentalProperty->Constant_HouseBought = 20d / April / 2023;
	RentalProperty->Constant_HouseConstructed = 23d / July / 2024;
	RentalProperty->Constant_LandCost = 209'000;
	RentalProperty->Constant_HouseCost = 334'000;
	RentalProperty->Constant_ExpectedAnnualIncrease = 0.1118;
	RentalProperty->Constant_ManagementFee = 225;
	RentalProperty->Constant_LeasePeriods = { RentalLeasePeriodInterval{ 20d / August / 2024, Final, 2'600 } };
	RentalProperty->Constant_RentalCosts = {};
	RentalProperty->Constant_EquityWithdrawals = {};

	RentalProperty->Constant_DepreciationSchedule[ 2024 ] = 16'810;
	RentalProperty->Constant_DepreciationSchedule[ 2025 ] = 12'385;
	RentalProperty->Constant_DepreciationSchedule[ 2026 ] = 11'194;
	RentalProperty->Constant_DepreciationSchedule[ 2027 ] = 10'330;
	RentalProperty->Constant_DepreciationSchedule[ 2028 ] = 9'693;
	RentalProperty->Constant_DepreciationSchedule[ 2029 ] = 9'216;
	RentalProperty->Constant_DepreciationSchedule[ 2030 ] = 8'855;
	RentalProperty->Constant_DepreciationSchedule[ 2031 ] = 8'577;
	RentalProperty->Constant_DepreciationSchedule[ 2032 ] = 8'362;
	RentalProperty->Constant_DepreciationSchedule[ 2033 ] = 8'193;
	RentalProperty->Constant_DepreciationSchedule[ 2034 ] = 8'059;
	RentalProperty->Constant_DepreciationSchedule[ 2035 ] = 7'953;
	RentalProperty->Constant_DepreciationSchedule[ 2036 ] = 7'867;
	RentalProperty->Constant_DepreciationSchedule[ 2037 ] = 7'798;
	RentalProperty->Constant_DepreciationSchedule[ 2038 ] = 7'742;
	RentalProperty->Constant_DepreciationSchedule[ 2039 ] = 7'696;
	RentalProperty->Constant_DepreciationSchedule[ 2040 ] = 7'658;
	RentalProperty->Constant_DepreciationSchedule[ 2041 ] = 7'627;
	RentalProperty->Constant_DepreciationSchedule[ 2042 ] = 7'602;
	RentalProperty->Constant_DepreciationSchedule[ 2043 ] = 7'581;
	RentalProperty->Constant_DepreciationSchedule[ 2044 ] = 7'563;
	RentalProperty->Constant_DepreciationSchedule[ 2045 ] = 7'549;
	RentalProperty->Constant_DepreciationSchedule[ 2046 ] = 7'537;
	RentalProperty->Constant_DepreciationSchedule[ 2047 ] = 7'527;
	RentalProperty->Constant_DepreciationSchedule[ 2048 ] = 7'518;
	RentalProperty->Constant_DepreciationSchedule[ 2049 ] = 7'511;
	RentalProperty->Constant_DepreciationSchedule[ 2050 ] = 7'505;
	RentalProperty->Constant_DepreciationSchedule[ 2051 ] = 7'500;
	RentalProperty->Constant_DepreciationSchedule[ 2052 ] = 7'496;
	RentalProperty->Constant_DepreciationSchedule[ 2053 ] = 7'492;
	RentalProperty->Constant_DepreciationSchedule[ 2054 ] = 7'489;
	RentalProperty->Constant_DepreciationSchedule[ 2055 ] = 7'486;
	RentalProperty->Constant_DepreciationSchedule[ 2056 ] = 7'484;
	RentalProperty->Constant_DepreciationSchedule[ 2057 ] = 7'482;
	RentalProperty->Constant_DepreciationSchedule[ 2058 ] = 7'481;
	RentalProperty->Constant_DepreciationSchedule[ 2059 ] = 7'479;
	RentalProperty->Constant_DepreciationSchedule[ 2060 ] = 7'478;
	RentalProperty->Constant_DepreciationSchedule[ 2061 ] = 7'477;
	RentalProperty->Constant_DepreciationSchedule[ 2062 ] = 7'476;
	RentalProperty->Constant_DepreciationSchedule[ 2063 ] = 7'476;
	RentalProperty->Constant_DepreciationSchedule[ 2064 ] = 556;

	return RentalProperty;
}

std::shared_ptr< Job > CreateJob()
{
	std::shared_ptr< Job > Job( new class Job );
	Job->Start = 1d / July / 2022;
	Job->End = Final;
	Job->Frequency = EFrequency::Monthly;
	Job->Constant_Wages = 8'750;
	Job->Constant_TaxWithheldFraction = 0.312;
	return Job;
}

std::shared_ptr< BankLoanAccount > CreateBankLoanLand()
{
	std::shared_ptr< BankLoanAccount > BankLoanAccount( new class BankLoanAccount );
	BankLoanAccount->Start = 20d / April / 2023;
	BankLoanAccount->End = Final;
	BankLoanAccount->Frequency = EFrequency::Monthly;
	BankLoanAccount->Constant_InterestRate = 0.0695;
	BankLoanAccount->Constant_MinRepayment = 803;

	BankLoanAccount->Constant_BankLoanReleases.AddInterval( 22d / May / 2023, { 119'866 } );

	return BankLoanAccount;
}

std::shared_ptr< BankLoanAccount > CreateBankLoanHouse()
{
	std::shared_ptr< BankLoanAccount > BankLoanAccount( new class BankLoanAccount );
	BankLoanAccount->Start = 20d / April / 2023;
	BankLoanAccount->End = Final;
	BankLoanAccount->Frequency = EFrequency::Monthly;
	BankLoanAccount->Constant_InterestRate = 0.0695;
	BankLoanAccount->Constant_MinRepayment = 2'200;

	BankLoanAccount->Constant_BankLoanReleases.AddInterval( 31d / July / 2023, { 68'966 } );
	BankLoanAccount->Constant_BankLoanReleases.AddInterval( 19d / October / 2023, { 83'682 } );
	BankLoanAccount->Constant_BankLoanReleases.AddInterval( 15d / November / 2023, { 66'945 } );
	BankLoanAccount->Constant_BankLoanReleases.AddInterval( 19d / January / 2024, { 66'945 } );
	BankLoanAccount->Constant_BankLoanReleases.AddInterval( 10d / July / 2024, { 48'188 } );

	return BankLoanAccount;
}

std::shared_ptr< BankAccount > CreateBankAccount()
{
	std::shared_ptr< BankAccount > BankAccount( new class BankAccount );
	BankAccount->Start = 20d / April / 2023;
	BankAccount->End = Final;
	BankAccount->Frequency = EFrequency::Monthly;
	return BankAccount;
}

std::shared_ptr< Tax > CreateTax()
{
	std::shared_ptr< Tax > Tax( new class Tax );
	Tax->Start = 1d / August / 2023;
	Tax->End = Final;
	Tax->Frequency = EFrequency::Annually;
	Tax->Constant_StudentLoan = 55'429;
	return Tax;
}

std::shared_ptr< Cost > CreateCost1()
{
	std::shared_ptr< Cost > Cost( new class Cost );
	Cost->Constant_Name = "Anytime Fitness subscription";
	Cost->Start = 20d / April / 2023;
	Cost->End = Final;
	Cost->Frequency = EFrequency::Weekly;
	Cost->Constant_NonDeductibleAmount = 19.95;
	return Cost;
}

std::shared_ptr< Cost > CreateCost2()
{
	std::shared_ptr< Cost > Cost( new class Cost );
	Cost->Constant_Name = "Offset value of bank to reflect now (31Dec2024)";
	Cost->Start = 1d / December / 2024;
	Cost->End = Final;
	Cost->Frequency = EFrequency::Once;
	Cost->Constant_NonDeductibleAmount = 125'000;
	return Cost;
}

void RunScenario()
{
	auto RentalProperty = CreateRentalProperty();
	auto Job = CreateJob();
	auto BankLoanLand = CreateBankLoanLand();
	auto BankLoanHouse = CreateBankLoanHouse();
	auto BankAccount = CreateBankAccount();
	auto Tax = CreateTax();

	auto Cost1 = CreateCost1();
	auto Cost2 = CreateCost2();

	BankLoanLand->Constant_OffsetAccount = BankAccount;
	BankAccount->Constant_LoanAccounts.push_back( BankLoanLand );
	BankAccount->Constant_LoanAccounts.push_back( BankLoanHouse );
	BankAccount->Constant_Jobs.push_back( Job );
	BankAccount->Constant_RentalProperties.push_back( RentalProperty );
	BankAccount->Constant_Costs.push_back( Cost1 );
	BankAccount->Constant_Costs.push_back( Cost2 );
	BankAccount->Constant_Taxes = Tax;
	Tax->Constant_Jobs.push_back( Job );
	Tax->Constant_RentalProperties.push_back( RentalProperty );
	Tax->Constant_Costs.push_back( Cost1 );
	Tax->Constant_Costs.push_back( Cost2 );
	RentalProperty->Constant_LandLoan = BankLoanLand;
	RentalProperty->Constant_HouseLoan = BankLoanHouse;

	auto Record0 = ( *BankAccount )[ 31d / December / 2024 ];
	auto Record1 = ( *RentalProperty )[ 30d / June / 2025 ];
	auto Record2 = ( *Tax )[ 1d / August / 2024 ];
	auto Record3 = ( *BankLoanLand )[ 30d / June / 2025 ];
	auto Record4 = ( *BankLoanHouse )[ 30d / June / 2025 ];

	Print( *BankAccount );
}

// Bank -> Taxreturn
// Rental depreciation schedule
// Studentloan should be an event with a when

int main()
{
	RunScenario();
}
