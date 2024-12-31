#pragma once
#include <map>

#include "Date.hpp"
#include "FinancialRecord.hpp"

class BankLoanAccount;

struct RentalCost
{
	std::string Name;
	Date When;
	float Cost;
};

struct RentalLeasePeriod
{
	float Income;
	Date From, To;
};

struct RentalEquityWithdrawal
{
	Date When;
	float Amount;
};

struct RentalPropertyRecord : RecordBase
{
	double Current_RentTotal = 0;
	double Current_ManagementFeesTotal = 0;
	bool Current_LandAcquired = false;
	bool Current_HouseAcquired = false;
	bool Current_Leased = false;
	Date Current_LeasedSince = {};
	double Current_Rent = 0;
	double Current_PropertyValue = 0;
	double Current_WithdrawnEquity = 0;
	double Current_WithdrawableValue = 0;
	double Current_RentalCostsTotal = 0;
	double Current_EquityAvailable = 0;

	double Current_PreStructuredLandLoanInterest = 0;
	double Current_PreStructuredHouseLoanInterest = 0;
	double Current_LandLoanInterest = 0;
	double Current_HouseLoanInterest = 0;

	std::vector< RentalCost > Current_RentalCosts;
};

class RentalProperty final : public RecordGenerator< RentalProperty, RentalPropertyRecord >
{
public:

	std::string Constant_Address;
	Date Constant_LandBought;
	Date Constant_HouseBought;
	Date Constant_HouseConstructed;
	double Constant_LandCost;
	double Constant_HouseCost;
	double Constant_ExpectedAnnualIncrease;
	double Constant_ManagementFee;
	std::vector< RentalLeasePeriod > Constant_LeasePeriods;
	std::vector< RentalCost > Constant_RentalCosts;
	std::vector< RentalEquityWithdrawal > Constant_EquityWithdrawals;
	std::shared_ptr< BankLoanAccount > Constant_LandLoan;
	std::shared_ptr< BankLoanAccount > Constant_HouseLoan;
	std::map< int32_t, double > Constant_DepreciationSchedule;

	double Current_RentTotal = 0;
	double Current_ManagementFeesTotal = 0;
	double Total_RentalCosts = 0;
	double Total_WithdrawnEquity = 0;
	double Total_PreStructuredLandLoanInterest = 0;
	double Total_PreStructuredHouseLoanInterest = 0;
	double Total_LandLoanInterest = 0;
	double Total_HouseLoanInterest = 0;

	RentalPropertyRecord Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) override;
};