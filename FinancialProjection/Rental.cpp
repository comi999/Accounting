#include "Rental.hpp"
#include "Bank.hpp"

RentalPropertyRecord RentalProperty::Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next )
{
	RentalPropertyRecord Record = {};

	Record.When = a_Date;

	const Date PreviousDay = Dates::IncrementDays( a_Date, -1 );

	// Has the land been acquired yet?
	Record.Current_LandAcquired = a_Date >= Constant_LandBought;

	// Is the house constructed by this date?
	Record.Current_HouseAcquired = a_Date >= Constant_HouseConstructed;

	// Are we in the construction phase?
	if ( a_Date > Constant_HouseBought && !Record.Current_HouseAcquired && Constant_HouseLoan )
	{
		// If we are, we can keep a record of interest payments for house loan, while it's being constructed.
		Date InterestPaidFrom = Constant_HouseBought > a_Last ? Constant_HouseBought : a_Last;
		Date InterestPaidTo = a_Date;

		const BankLoanAccountRecord LoanFrom = ( *Constant_HouseLoan )[ InterestPaidFrom ];
		const BankLoanAccountRecord LoanTo = ( *Constant_HouseLoan )[ InterestPaidTo ];

		const double InterestPaidThisPeriod = LoanTo.Current_InterestCharged - LoanFrom.Current_InterestCharged;
		Total_PreStructuredHouseLoanInterest += InterestPaidThisPeriod;
	}
	else if ( Record.Current_HouseAcquired && Constant_HouseLoan )
	{
		// If we are, we can keep a record of interest payments for house loan.
		const Date InterestPaidFrom = Constant_HouseConstructed > a_Last ? Constant_HouseConstructed : a_Last;
		const Date InterestPaidTo = a_Date;

		const BankLoanAccountRecord LoanFrom = ( *Constant_HouseLoan )[ InterestPaidFrom ];
		const BankLoanAccountRecord LoanTo = ( *Constant_HouseLoan )[ InterestPaidTo ];

		const double InterestPaidThisPeriod = LoanTo.Current_InterestCharged - LoanFrom.Current_InterestCharged;
		Total_HouseLoanInterest += InterestPaidThisPeriod;
	}

	Record.Current_PreStructuredHouseLoanInterest = Total_PreStructuredHouseLoanInterest;
	Record.Current_HouseLoanInterest = Total_HouseLoanInterest;

	// Are we in the structureless land phase?
	if ( a_Date > Constant_LandBought && !Record.Current_HouseAcquired && Constant_LandLoan )
	{
		// If we are, we can keep a record of interest payments for land loan, while it's being constructed.
		const Date InterestPaidFrom = Constant_LandBought > a_Last ? Constant_LandBought : a_Last;
		const Date InterestPaidTo = a_Date;

		const BankLoanAccountRecord LoanFrom = ( *Constant_LandLoan )[ InterestPaidFrom ];
		const BankLoanAccountRecord LoanTo = ( *Constant_LandLoan )[ InterestPaidTo ];

		const double InterestPaidThisPeriod = LoanTo.Current_InterestCharged - LoanFrom.Current_InterestCharged;
		Total_PreStructuredLandLoanInterest += InterestPaidThisPeriod;
	}
	else if ( Record.Current_HouseAcquired && Constant_LandLoan )
	{
		// If we are, we can keep a record of interest payments for land loan.
		const Date InterestPaidFrom = Constant_HouseConstructed > a_Last ? Constant_HouseConstructed : a_Last;
		const Date InterestPaidTo = a_Date;

		const BankLoanAccountRecord LoanFrom = ( *Constant_LandLoan )[ InterestPaidFrom ];
		const BankLoanAccountRecord LoanTo = ( *Constant_LandLoan )[ InterestPaidTo ];

		const double InterestPaidThisPeriod = LoanTo.Current_InterestCharged - LoanFrom.Current_InterestCharged;
		Total_LandLoanInterest += InterestPaidThisPeriod;
	}

	Record.Current_PreStructuredLandLoanInterest = Total_PreStructuredLandLoanInterest;
	Record.Current_LandLoanInterest = Total_LandLoanInterest;

	// Is the house currently being leased?
	if ( Record.Current_HouseAcquired )
	{
		// If we are within a lease period, we can set info.
		if ( const auto LeasePeriod = Constant_LeasePeriods.GetInterval( a_Date ) )
		{
			Record.Current_Leased = true;
			Record.Current_Rent = LeasePeriod->Data.Rent;
			Record.Current_LeasedSince = LeasePeriod->From;
		}
	}

	// If we are currently leased, then we need to calculate management fee and rent.
	if ( Record.Current_Leased )
	{
		const bool BeforeNext = Record.Current_LeasedSince < a_Next;
		const bool AfterNow = Record.Current_LeasedSince >= a_Date;
		const bool IsLeasingStarting = BeforeNext && AfterNow;
		const double DaysToPayFor = Dates::Diff( a_Next, IsLeasingStarting ? Record.Current_LeasedSince : a_Date );
		double PeriodFraction = DaysToPayFor / GetDaysInPeriod();

		double ManagementFee = PeriodFraction * Constant_ManagementFee;
		double RentPayment = PeriodFraction * Record.Current_Rent;

		Current_ManagementFeesTotal += ManagementFee;
		Current_RentTotal += RentPayment;
	}

	// If we are within a lease period, we can set info.
	if ( const auto RentalCosts = Constant_RentalCosts.GetInterval( a_Date ) )
	{
		Total_RentalCosts += RentalCosts->Data.Cost;
		Record.Current_RentalCosts.push_back( RentalCosts->Data );
	}

	Record.Current_RentTotal = Current_RentTotal;
	Record.Current_ManagementFeesTotal = Current_ManagementFeesTotal;
	Record.Current_RentalCostsTotal = Total_RentalCosts;

	const double DaysSinceLandBought = Dates::Diff( a_Date, Constant_LandBought );
	const double YearsSinceLandBought = DaysSinceLandBought / Dates::AverageDaysInYear();
	const double LandGrowth = Constant_ExpectedAnnualIncrease * YearsSinceLandBought;
	const double CurrentLandValue = Constant_LandCost * ( LandGrowth + 1.0 );

	const double DaysSinceHouseBought = Dates::Diff( a_Date, Constant_HouseBought );
	const double YearsSinceHouseBought = DaysSinceHouseBought / Dates::AverageDaysInYear();
	const double HouseGrowth = Constant_ExpectedAnnualIncrease * YearsSinceHouseBought;
	const double CurrentHouseValue = Constant_HouseCost * ( HouseGrowth + 1.0 );

	Record.Current_PropertyValue = CurrentLandValue + CurrentHouseValue;

	// Next we need to check if we are pulling out any equity this period.

	Record.Current_WithdrawableValue = 0.8 * Record.Current_PropertyValue;

	// If we are within a lease period, we can set info.
	if ( const auto EquityWithdrawal = Constant_EquityWithdrawals.GetInterval( Dates::IncrementDays( a_Last, 1 ), a_Date ) )
	{
		Total_WithdrawnEquity += EquityWithdrawal->Data.Amount;
	}

	Record.Current_WithdrawnEquity = Total_WithdrawnEquity;
	Record.Current_EquityAvailable = Record.Current_WithdrawableValue - Record.Current_WithdrawnEquity;

	return Record;
}
