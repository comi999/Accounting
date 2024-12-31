#pragma once
#include <iostream>
#include <vector>
//
//#include "CalendarDate.hpp"
//
//#define MEDICARE_LEVY_PERCENTAGE 0.02f
//
//struct Aud
//{
//	float Amount;
//
//	Aud( const float a_Amount = 0.0f )
//		: Amount( a_Amount )
//	{}
//
//	operator float() const { return Amount; }
//	operator float& ( ) { return Amount; }
//};
//
//inline std::string ToString( Aud a_Currency )
//{
//	bool IsNegative = a_Currency < 0;
//
//	if ( IsNegative )
//	{
//		a_Currency *= -1;
//	}
//
//	const int DollarAmount = ( int )a_Currency;
//	const int CentsAmount0 = ( int )( 10 * ( a_Currency - DollarAmount ) );
//	const int CentsAmount1 = ( int )( 100 * ( a_Currency - DollarAmount ) ) - CentsAmount0 * 10;
//
//	std::string Result = IsNegative ? "-$" : "+$";
//	Result += std::to_string( DollarAmount );
//	Result += ".";
//	Result += std::to_string( CentsAmount0 ) + std::to_string( CentsAmount1 );
//
//
//
//	return Result;
//}
//

//
//enum class ETransactionType
//{
//	Income,
//	InvestmentCost,
//	BusinessCost,
//	WorkCost,
//	OtherCost,
//	//...
//	TaxPayment,
//};
//
//enum class EFreqencyType
//{
//	Once,
//	Daily,
//	Weekly,
//	Fortnightly,
//	Monthly,
//	Bimonthly,
//	Quarterly,
//	Yearly,
//};
//
//struct FinancialRecord
//{
//	std::string Name;
//	Aud Dollars;
//	ETransactionType Type;
//	EFreqencyType Frequency;
//	CalendarDate From, To;
//	float Withheld;
//};
//
//struct TaxReport
//{
//	// Income
//	Aud GrossIncome;
//	Aud TaxableIncome;
//	Aud RepaymentIncome;
//	Aud TaxFreeThreshhold;
//	Aud TaxFreePortion;
//	Aud TaxablePortion;
//
//	// Student loans
//	Aud StudentLoanRepayment;
//	Aud StudentLoanBefore;
//	Aud StudentLoanAfter;
//
//	// Health insurance
//	// Aud HealthInsuranceOffset;
//	Aud MedicareLevy;
//	// Aud MedicareLevySurcharge;
//
//	// Deductions
//	Aud InvestmentDeductionTotal;
//	Aud WorkDeductionTotal;
//	Aud BusinessDeductionTotal;
//	// Aud CapitalGainsTotal;
//	// Aud CapitalGainsTax;
//
//	// Totals
//	Aud IncomeTax;
//	Aud TotalTax;
//	Aud TaxWithheld;
//	Aud TaxReturn;
//};
//
//struct FinancialTransaction
//{
//	CalendarDate Date;
//	std::string Name;
//	Aud Amount;
//	ETransactionType Type;
//};
//
//struct FinancialStatementDay
//{
//	std::vector< FinancialTransaction > Entries;
//	Aud BankBalance;
//	CalendarDate Date;
//};
//
//struct FinancialStatement
//{
//	uint32_t YearFrom, YearTo;
//	EFreqencyType EntryFrequency;
//	std::vector< FinancialStatementDay > Days;
//	Aud BalanceStart, BalanceEnd;
//	TaxReport Tax;
//};
//
//class FinancialRecordEnd;
//
//class FinancialRecordStart
//{
//public:
//
//	virtual ~FinancialRecordStart() = default;
//
//	FinancialRecordEnd operator[]( CalendarDate a_To ) const;
//
//	FinancialRecordEnd operator[]( const std::string& a_To ) const;
//
//	void AddIncome( const std::string& a_Name, Aud a_Amount, EFreqencyType a_Frequency, float a_Withheld = 0.0f ) const;
//	void AddCost( const std::string& a_Name, Aud a_Amount, EFreqencyType a_Frequency ) const;
//	void AddInvestmentCost( const std::string& a_Name, Aud a_Amount, EFreqencyType a_Frequency ) const;
//
//protected:
//
//	friend class FinancialPlanner;
//
//	FinancialRecordStart( FinancialPlanner& a_FP, const CalendarDate a_From, const CalendarDate a_To = { 0, 0, 0 } )
//		: m_Ref( a_FP )
//		, m_From( a_From )
//		, m_To( a_To )
//	{}
//
//	FinancialPlanner& m_Ref;
//	CalendarDate m_From, m_To;
//};
//
//class FinancialRecordEnd : public FinancialRecordStart
//{
//	friend class FinancialRecordStart;
//
//	FinancialRecordEnd( FinancialPlanner& a_FP, const CalendarDate a_From, const CalendarDate a_To )
//		: FinancialRecordStart( a_FP, a_From, a_To )
//	{}
//};
//
//inline FinancialRecordEnd FinancialRecordStart::operator[]( const CalendarDate a_To ) const
//{
//	return { m_Ref, m_From, a_To };
//}
//
//inline FinancialRecordEnd FinancialRecordStart::operator[]( const std::string& a_To ) const
//{
//	CalendarDate To;
//
//	if ( !FromString( a_To, To ) )
//	{
//		return { *( FinancialPlanner* )nullptr, {}, {} };
//	}
//
//	return { m_Ref, m_From, To };
//}
//
//class FinancialPlanner
//{
//public:
//
//	FinancialRecordStart operator[]( const CalendarDate a_CalendarDate )
//	{
//		return { *this, a_CalendarDate };
//	}
//
//	FinancialRecordStart operator[]( const std::string& a_CalendarDate )
//	{
//		CalendarDate Date;
//
//		if ( !FromString( a_CalendarDate, Date ) )
//		{
//			return FinancialRecordStart{ *( FinancialPlanner* )nullptr, {} };
//		}
//
//		return FinancialRecordStart{ *this, Date };
//	}
//
//	void AddIncome( const std::string& a_Name, const Aud a_Amount, const EFreqencyType a_Frequency, const CalendarDate a_From, const CalendarDate a_To, const float a_Withheld = 0.0f )
//	{
//		Records.emplace_back( FinancialRecord{ a_Name, a_Amount, ETransactionType::Income, a_Frequency, a_From, a_To, a_Withheld } );
//	}
//
//	void AddStudentLoan( const std::string& a_Name, const Aud a_Amount, const uint32_t a_Year )
//	{
//		m_StudentLoans.emplace_back( FinancialRecord{ a_Name, a_Amount, ETransactionType::OtherCost, EFreqencyType::Once, CalendarDate{ 0, 6, a_Year }, {}, 0.0f } );
//	}
//
//	void AddCost( const std::string& a_Name, const Aud a_Amount, const EFreqencyType a_Frequency, const CalendarDate a_From, const CalendarDate a_To )
//	{
//		Records.emplace_back( FinancialRecord{ a_Name, a_Amount, ETransactionType::OtherCost, a_Frequency, a_From, a_To, 0.0f } );
//	}
//
//	void AddInvestmentCost( const std::string& a_Name, const Aud a_Amount, const EFreqencyType a_Frequency, const CalendarDate a_From, const CalendarDate a_To )
//	{
//		Records.emplace_back( FinancialRecord{ a_Name, a_Amount, ETransactionType::InvestmentCost, a_Frequency, a_From, a_To, 0.0f } );
//	}
//
//	std::vector< FinancialStatement > GenerateStatements( uint32_t a_YearFrom, uint32_t a_Count,  EFreqencyType a_Frequency = EFreqencyType::Weekly, Aud a_StartingBalance = 0.0f ) const;
//
//	static void PrintStatements( const std::vector< FinancialStatement >& a_Statements );
//
//private:
//
//	friend class FinancialRecordStart;
//	friend class FinancialRecordEnd;
//
//	static float GetFrequencyMultipler( const EFreqencyType a_Frequency )
//	{
//		switch ( a_Frequency )
//		{
//		case EFreqencyType::Daily:
//			return 365;
//		case EFreqencyType::Weekly:
//			return 52;
//		case EFreqencyType::Fortnightly:
//			return 26;
//		case EFreqencyType::Monthly:
//			return 12;
//		case EFreqencyType::Bimonthly:
//			return 6;
//		case EFreqencyType::Quarterly:
//			return 4;
//		case EFreqencyType::Once:
//		case EFreqencyType::Yearly:
//			return 1;
//		}
//
//		return 0;
//	}
//
//	std::vector< FinancialRecord > Records;
//	std::vector< FinancialRecord > m_StudentLoans;
//};
//
//inline void FinancialRecordStart::AddIncome( const std::string& a_Name, const Aud a_Amount, const EFreqencyType a_Frequency, const float a_Withheld ) const
//{
//	m_Ref.AddIncome( a_Name, a_Amount, a_Frequency, m_From, m_To, a_Withheld );
//}
//
//inline void FinancialRecordStart::AddCost( const std::string& a_Name, Aud a_Amount, EFreqencyType a_Frequency ) const
//{
//	m_Ref.AddCost( a_Name, a_Amount, a_Frequency, m_From, m_To );
//}
//
//inline void FinancialRecordStart::AddInvestmentCost( const std::string& a_Name, const Aud a_Amount, const EFreqencyType a_Frequency ) const
//{
//	m_Ref.AddInvestmentCost( a_Name, a_Amount, a_Frequency, m_From, m_To );
//}
//
//inline std::vector< FinancialStatement > FinancialPlanner::GenerateStatements( const uint32_t a_YearFrom, const uint32_t a_Count, const EFreqencyType a_Frequency, const Aud a_StartingBalance ) const
//{
//	struct SubRange
//	{
//		CalendarDate DateFrom, DateTo;
//		uint32_t IndexFrom, IndexTo;
//		Aud StudentLoanBalance;
//	};
//
//	std::vector< SubRange > SubRanges;
//
//	for ( uint32_t i = 0; i < a_Count; ++i )
//	{
//		CalendarDate Start = { 0, 6, a_YearFrom + i };
//		CalendarDate End = { 29, 5, a_YearFrom + 1 + i };
//
//		SubRanges.emplace_back( SubRange{ Start, End } );
//	}
//
//	CalendarDate StatementFrom = SubRanges.front().DateFrom;
//	CalendarDate StatementTo = SubRanges.back().DateTo;
//
//	// Now we want to figure out
//	Aud AccumulatedStudentLoan;
//	uint32_t AccumulatedIndex = 0;
//
//	for ( auto& [ DateFrom, DateTo, IndexFrom, IndexTo, StudentLoan ] : SubRanges )
//	{
//		// Find any student loan added in the financial year.
//		const uint32_t FinancialYear = DateFrom.Year;
//
//		const auto Iter = std::find_if( m_StudentLoans.begin(), m_StudentLoans.end(), [ FinancialYear ]( const FinancialRecord& a_Record )
//		{
//			return FinancialYear == a_Record.From.Year;
//		} );
//
//		if ( Iter != m_StudentLoans.end() )
//		{
//			AccumulatedStudentLoan.Amount += Iter->Dollars.Amount;
//		}
//
//		StudentLoan = AccumulatedStudentLoan;
//
//		// Set the indices too
//		IndexFrom = AccumulatedIndex;
//		IndexTo = DateTo - DateFrom + IndexFrom;
//		AccumulatedIndex = IndexTo + 1;
//	}
//
//	struct DayRecordEntry
//	{
//		Aud Value;
//		std::string Name;
//		ETransactionType Type;
//	};
//
//	struct DayRecord
//	{
//		CalendarDate Date;
//		Aud TaxWithheld;
//		std::vector< FinancialTransaction > Entries;
//	};
//
//	std::vector< DayRecord > DayRecords( SubRanges.back().IndexTo + 1 );
//
//	// Set all the dates.
//	CalendarDate CurrentDate = StatementFrom;
//	for ( auto& [ Date, TaxWithheld, _1 ] : DayRecords )
//	{
//		Date = CurrentDate;
//		CurrentDate += 1;
//	}
//
//	const auto CalculateTaxWithheld = [ &DayRecords ]( const uint32_t a_Index, const ETransactionType a_Type, const Aud a_Amount, const float a_Withheld ) -> Aud
//	{
//		// If the transaction is positive, then
//		// 'tax withheld' means something.
//		if ( a_Type == ETransactionType::Income && a_Amount > 0 )
//		{
//			const Aud Withheld = a_Amount * a_Withheld;
//			DayRecords[ a_Index ].TaxWithheld += Withheld;
//			return a_Amount - Withheld;
//		}
//
//		// If this is not a withheld amount, return full value.
//		return a_Amount;
//	};
//
//	// Now we want to process all financial records.
//	for ( auto& Record : Records )
//	{
//		// While the date the record started from is ok to start before statement
//		// begin (we just collect them all together and add to first day),
//		// The last should be capped.
//		//... DO THE CODE HERE
//		CalendarDate To = ( Record.To == CalendarDate{ 0, 0, 0 } ? StatementTo : ( StatementTo < Record.To ? StatementTo : Record.To ) );
//
//		// If this is a once time transaction, we will log it once
//		switch ( Record.Frequency )
//		{
//		case EFreqencyType::Once:
//		{
//			// Is this transaction from before the start?
//			if ( Record.From < StatementFrom )
//			{
//				// ...
//			}
//			else
//			{
//				const uint32_t Index = Record.From - StatementFrom;
//				FinancialTransaction& Transaction = DayRecords[ Index ].Entries.emplace_back();
//				Transaction.Date = Record.From;
//				Transaction.Amount = CalculateTaxWithheld( Index, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//			}
//		} break;
//		case EFreqencyType::Daily:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From += 1;
//			}
//
//			// Now we place entries as we go from here.
//			uint32_t FromIndex = From - StatementFrom;
//
//			while ( FromIndex < DayRecords.size() )
//			{
//				FinancialTransaction& Transaction = DayRecords[ FromIndex ].Entries.emplace_back();
//				Transaction.Date = DayRecords[ FromIndex ].Date;
//				Transaction.Amount = CalculateTaxWithheld( FromIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				FromIndex += 1;
//			}
//		} break;
//		case EFreqencyType::Weekly:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From += 7; /*Entries in a week*/
//			}
//
//			// Now we place entries as we go from here.
//			uint32_t FromIndex = From - StatementFrom;
//
//			while ( FromIndex < DayRecords.size() )
//			{
//				FinancialTransaction& Transaction = DayRecords[ FromIndex ].Entries.emplace_back();
//				Transaction.Date = DayRecords[ FromIndex ].Date;
//				Transaction.Amount = CalculateTaxWithheld( FromIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				FromIndex += 7; /*Entries in a week*/
//			}
//		} break;
//		case EFreqencyType::Fortnightly:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From += 14; /*Entries in a fortnight*/
//			}
//
//			// Now we place entries as we go from here.
//			uint32_t FromIndex = From - StatementFrom;
//
//			while ( FromIndex < DayRecords.size() )
//			{
//				FinancialTransaction& Transaction = DayRecords[ FromIndex ].Entries.emplace_back();
//				Transaction.Date = DayRecords[ FromIndex ].Date;
//				Transaction.Amount = CalculateTaxWithheld( FromIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				FromIndex += 14; /*Entries in a fortnight*/
//			}
//		} break;
//		case EFreqencyType::Monthly:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From.Month += 1;
//				if ( From.Month > 11 ) From.Month -= 12, ++From.Year;
//			}
//
//			// Now we place entries as we go from here.
//			while ( From <= To )
//			{
//				uint32_t CappedDay = std::min( From.Day, CalendarDate::DaysInMonth( From.Month, From.Year ) - 1 );
//				CalendarDate CappedDate = { CappedDay, From.Month, From.Year };
//				uint32_t CappedIndex = CappedDate - StatementFrom;
//
//				FinancialTransaction& Transaction = DayRecords[ CappedIndex ].Entries.emplace_back();
//				Transaction.Date = CappedDate;
//				Transaction.Amount = CalculateTaxWithheld( CappedIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				From.Month += 1;
//				if ( From.Month > 11 ) From.Month -= 12, ++From.Year;
//			}
//		} break;
//		case EFreqencyType::Bimonthly:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From.Month += 2;
//				if ( From.Month > 11 ) From.Month -= 12, ++From.Year;
//			}
//
//			// Now we place entries as we go from here.
//			while ( From <= To )
//			{
//				uint32_t CappedDay = std::min( From.Day, CalendarDate::DaysInMonth( From.Month, From.Year ) - 1 );
//				CalendarDate CappedDate = { CappedDay, From.Month, From.Year };
//				uint32_t CappedIndex = CappedDate - StatementFrom;
//
//				FinancialTransaction& Transaction = DayRecords[ CappedIndex ].Entries.emplace_back();
//				Transaction.Date = CappedDate;
//				Transaction.Amount = CalculateTaxWithheld( CappedIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				From.Month += 2;
//				if ( From.Month > 11 ) From.Month -= 12, ++From.Year;
//			}
//		} break;
//		case EFreqencyType::Quarterly:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From.Month += 3;
//				if ( From.Month > 11 ) From.Month -= 12, ++From.Year;
//			}
//
//			// Now we place entries as we go from here.
//			while ( From <= To )
//			{
//				uint32_t CappedDay = std::min( From.Day, CalendarDate::DaysInMonth( From.Month, From.Year ) - 1 );
//				CalendarDate CappedDate = { CappedDay, From.Month, From.Year };
//				uint32_t CappedIndex = CappedDate - StatementFrom;
//
//				FinancialTransaction& Transaction = DayRecords[ CappedIndex ].Entries.emplace_back();
//				Transaction.Date = CappedDate;
//				Transaction.Amount = CalculateTaxWithheld( CappedIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				From.Month += 3;
//				if ( From.Month > 11 ) From.Month -= 12, ++From.Year;
//			}
//		} break;
//		case EFreqencyType::Yearly:
//		{
//			CalendarDate From = Record.From;
//
//			// While we are before the start date.
//			while ( From < StatementFrom )
//			{
//				From.Year += 1;
//			}
//
//			// Now we place entries as we go from here.
//			while ( From <= To )
//			{
//				uint32_t CappedDay = std::min( From.Day, CalendarDate::DaysInMonth( From.Month, From.Year ) - 1 );
//				CalendarDate CappedDate = { CappedDay, From.Month, From.Year };
//				uint32_t CappedIndex = CappedDate - StatementFrom;
//
//				FinancialTransaction& Transaction = DayRecords[ CappedIndex ].Entries.emplace_back();
//				Transaction.Date = CappedDate;
//				Transaction.Amount = CalculateTaxWithheld( CappedIndex, Record.Type, Record.Dollars, Record.Withheld );
//				Transaction.Type = Record.Type;
//				Transaction.Name = Record.Name;
//
//				From.Year += 1;
//			}
//		} break;
//		}
//	}
//
//	// At this stage, we have daily records of all transactions that have occured.
//	// Each day has a certain amount of tax withheld if this was an income transaction.
//	std::vector< FinancialStatement > Statements;
//
//	Aud CurrentBalance = a_StartingBalance;
//	Aud StudentLoanRepaymentTotal = 0;
//
//	for ( auto& FinancialYear : SubRanges )
//	{
//		FinancialStatement& Statement = Statements.emplace_back();
//		Statement.BalanceStart = CurrentBalance;
//		Statement.EntryFrequency = a_Frequency;
//		Statement.YearFrom = FinancialYear.DateFrom.Year;
//		Statement.YearTo = FinancialYear.DateTo.Year;
//		const uint32_t IndexFrom = FinancialYear.IndexFrom;
//		const uint32_t IndexTo = FinancialYear.IndexTo;
//		Statement.Days.resize( IndexTo - IndexFrom + 1 );
//
//		Aud TotalTaxWithheld;
//
//		for ( uint32_t i = 0; i < Statement.Days.size(); ++i )
//		{
//			auto& ThisDayFrom = DayRecords[ i + IndexFrom ];
//			auto& ThisDayTo = Statement.Days[ i ];
//
//			// Transfer tax
//			TotalTaxWithheld += ThisDayFrom.TaxWithheld;
//
//			// Transfer the financial transactions across.
//			ThisDayTo.Entries = std::move( ThisDayFrom.Entries );
//			ThisDayTo.Date = ThisDayFrom.Date;
//		}
//
//		// Calculate this:
//		Statement.Tax.GrossIncome = TotalTaxWithheld; // We'll add in daily income amounts after.
//		// Aud TaxableIncome;
//		// Aud RepaymentIncome;
//		// Aud TaxFreePortion;
//		// Aud TaxablePortion;
//		// Aud StudentLoanRepayment;
//		// Aud StudentLoanBefore;
//		// Aud StudentLoanAfter;
//		// Aud HealthInsuranceOffset;
//		// Aud MedicareLevy;
//		// Aud MedicareLevySurcharge;
//		//Statement.Tax.InvestmentDeductionTotal;
//		//Statement.Tax.WorkDeductionTotal;
//		//Statement.Tax.BusinessDeductionTotal;
//		//Statement.Tax.OtherDeductionTotal;
//		// Aud CapitalGainsTotal;
//		// Aud CapitalGainsTax;
//		//Aud TotalTax;
//		Statement.Tax.TaxWithheld = TotalTaxWithheld;
//		//Aud TaxReturn;
//
//		for ( uint32_t i = 0; i < Statement.Days.size(); ++i )
//		{
//			auto& ThisDay = Statement.Days[ i ];
//			Aud IncomeThisDay;
//			
//			for ( auto& ThisDayEntry : ThisDay.Entries )
//			{
//				switch ( ThisDayEntry.Type )
//				{
//				default: break;
//				case ETransactionType::Income:
//				{
//					IncomeThisDay += ThisDayEntry.Amount;
//					Statement.Tax.GrossIncome += ThisDayEntry.Amount;
//				} break;
//				case ETransactionType::InvestmentCost:
//				{
//					IncomeThisDay -= ThisDayEntry.Amount;
//					Statement.Tax.InvestmentDeductionTotal += ThisDayEntry.Amount;
//				} break;
//				case ETransactionType::BusinessCost:
//				{
//					IncomeThisDay -= ThisDayEntry.Amount;
//					Statement.Tax.BusinessDeductionTotal += ThisDayEntry.Amount;
//				} break;
//				case ETransactionType::WorkCost:
//				{
//					IncomeThisDay -= ThisDayEntry.Amount;
//					Statement.Tax.WorkDeductionTotal += ThisDayEntry.Amount;
//				} break;
//				case ETransactionType::OtherCost:
//				{
//					IncomeThisDay -= ThisDayEntry.Amount;
//				} break;
//				}
//			}
//
//			CurrentBalance += IncomeThisDay;
//			ThisDay.BankBalance = CurrentBalance;
//		}
//
//		Statement.BalanceEnd = CurrentBalance;
//
//		// Fill out rest of tax info.
//		//Statement.Tax.GrossIncome;
//
//		// Taxable Income is deducted income.
//		Statement.Tax.TaxableIncome =
//		+ Statement.Tax.GrossIncome
//		- Statement.Tax.InvestmentDeductionTotal
//		- Statement.Tax.WorkDeductionTotal
//		- Statement.Tax.BusinessDeductionTotal;
//
//		// Repayment Income is deducted income bar investment deductions.
//		Statement.Tax.RepaymentIncome = 
//		+ Statement.Tax.GrossIncome
//		- Statement.Tax.WorkDeductionTotal
//		- Statement.Tax.BusinessDeductionTotal;
//
//		// The level that income has to be over to be taxed.
//		Statement.Tax.TaxFreeThreshhold = 
//			TaxBracketTable::GetTaxFreeThreshhold( StatementFrom.Year );
//
//		// This is the portion of Taxable Income that will not be taxed.
//		Statement.Tax.TaxFreePortion =
//			std::min( Statement.Tax.TaxFreeThreshhold, Statement.Tax.TaxableIncome );
//
//		// This is the portion of the Taxable Income that will be taxed.
//		Statement.Tax.TaxablePortion =
//			Statement.Tax.TaxableIncome - Statement.Tax.TaxFreePortion;
//
//		// The amount student debt at beginning of financial year.
//		Statement.Tax.StudentLoanBefore =
//			FinancialYear.StudentLoanBalance - StudentLoanRepaymentTotal;
//
//		// This is the amount to be paid off of the Student Loans.
//		Statement.Tax.StudentLoanRepayment =
//			Statement.Tax.StudentLoanBefore > 0 ? ( Aud )std::min( StudentLoanRepaymentTable::CalculateRepayment( StatementFrom.Year, Statement.Tax.RepaymentIncome ), Statement.Tax.StudentLoanBefore ) : Aud{0};
//
//		// The amount of student debt after repayment.
//		Statement.Tax.StudentLoanAfter =
//			Statement.Tax.StudentLoanBefore - Statement.Tax.StudentLoanRepayment;
//
//		StudentLoanRepaymentTotal += Statement.Tax.StudentLoanRepayment;
//
//		// Aud HealthInsuranceOffset;
//
//		// This is default of 2% of your taxable portion of your taxable income.
//		Statement.Tax.MedicareLevy =
//			MEDICARE_LEVY_PERCENTAGE * Statement.Tax.TaxableIncome;
//
//		// Aud MedicareLevySurcharge;
//		//Statement.Tax.InvestmentDeductionTotal;
//		//Statement.Tax.WorkDeductionTotal;
//		//Statement.Tax.BusinessDeductionTotal;
//		//Statement.Tax.OtherDeductionTotal;
//		// Aud CapitalGainsTotal;
//		// Aud CapitalGainsTax;
//
//		// Amount of tax to be 
//		Statement.Tax.IncomeTax = 
//			TaxBracketTable::CalculateTax( StatementFrom.Year, Statement.Tax.TaxableIncome );
//
//		Statement.Tax.TaxWithheld = 
//			TotalTaxWithheld;
//
//		// This is the total tax to pay at the end.
//		Statement.Tax.TotalTax =
//		+ Statement.Tax.StudentLoanRepayment
//		+ Statement.Tax.MedicareLevy
//		+ Statement.Tax.IncomeTax;
//
//		Statement.Tax.TaxReturn =
//			Statement.Tax.TaxWithheld - Statement.Tax.TotalTax;
//
//		// Now that we have the Tax Return value, we can now add.
//		auto& TaxTransaction = Statement.Days.back().Entries.emplace_back();
//		TaxTransaction.Name = "[TAX RETURN FY " + std::to_string( Statement.YearFrom ) + "/" + std::to_string( Statement.YearTo ) + "]";
//		TaxTransaction.Amount = Statement.Tax.TaxReturn;
//		TaxTransaction.Type = ETransactionType::TaxPayment;
//		TaxTransaction.Date = Statement.Days.back().Date;
//
//		Statement.Days.back().BankBalance += Statement.Tax.TaxReturn;
//		Statement.BalanceEnd += Statement.Tax.TaxReturn;
//		CurrentBalance += Statement.Tax.TaxReturn;
//
//		// Reduce day entries to the right freqency.
//		uint32_t Frequency = 1;
//		bool IncrementByMonth = false;
//
//		switch ( a_Frequency )
//		{
//		case EFreqencyType::Once:
//			Frequency = 366;
//			break;
//		case EFreqencyType::Daily:
//			Frequency = 1;
//			break;
//		case EFreqencyType::Weekly:
//			Frequency = 7;
//			break;
//		case EFreqencyType::Fortnightly:
//			Frequency = 14;
//			break;
//		case EFreqencyType::Monthly:
//			Frequency = 1;
//			IncrementByMonth = true;
//			break;
//		case EFreqencyType::Bimonthly:
//			Frequency = 2;
//			IncrementByMonth = true;
//			break;
//		case EFreqencyType::Quarterly:
//			Frequency = 3;
//			IncrementByMonth = true;
//			break;
//		case EFreqencyType::Yearly:
//			Frequency = 366;
//			break;
//		}
//
//		std::vector< FinancialStatementDay > NewDays;
//
//		if ( IncrementByMonth )
//		{
//			CalendarDate StartDate = Statement.Days[ 0 ].Date;
//			CalendarDate SentinelDate = StartDate;
//
//			while ( true )
//			{
//				// Might need to cap days to the month.
//				const uint32_t CappedDays = CalendarDate::DaysInMonth( SentinelDate.Month, SentinelDate.Year );
//				const CalendarDate CappedSentinelDate = { SentinelDate.Day >= CappedDays - 1 ? CappedDays - 1 : SentinelDate.Day, SentinelDate.Month, SentinelDate.Year };
//
//				const uint32_t CurrentIndex = CappedSentinelDate - StartDate;
//
//				if ( CurrentIndex >= Statement.Days.size() - 1 )
//				{
//					break;
//				}
//
//				NewDays.push_back( Statement.Days[ CurrentIndex ] );
//
//				// Increment month.
//				SentinelDate.Month += Frequency;
//				if ( SentinelDate.Month > 11 ) SentinelDate.Month -= 12, ++SentinelDate.Year;
//			}
//		}
//		else
//		{
//			uint32_t CurrentIndex = 0;
//			while ( CurrentIndex < Statement.Days.size() - 1 )
//			{
//				NewDays.push_back( Statement.Days[ CurrentIndex ] );
//				CurrentIndex += Frequency;
//			}
//		}
//
//		NewDays.push_back( Statement.Days.back() );
//		Statement.Days = std::move( NewDays );
//	}
//
//	return Statements;
//}
//
//inline void FinancialPlanner::PrintStatements( const std::vector< FinancialStatement >& a_Statements )
//{
//	for ( auto& Statement : a_Statements )
//	{
//		std::cout << "Financial Year " << Statement.YearFrom << "/" << Statement.YearTo << "\n";
//		std::cout << "  Balance Start: " << ToString( Statement.BalanceStart ) << "\n  Balance End: " << ToString( Statement.BalanceEnd ) << "\n\n";
//
//		for ( auto& Day : Statement.Days )
//		{
//			std::cout << "  " << ToString( Day.Date ) << " : " << ToString( Day.BankBalance ) << "\n";
//
//			/*for ( auto& Entry : Day.Entries )
//			{
//				std::cout << "\t  ";
//
//				Aud Amount = Entry.Amount;
//
//				switch ( Entry.Type )
//				{
//				case ETransactionType::Income:
//				case ETransactionType::TaxPayment:
//					Amount *= 1;
//					break;
//				case ETransactionType::InvestmentCost:
//				case ETransactionType::WorkCost:
//				case ETransactionType::BusinessCost:
//				case ETransactionType::OtherCost:
//					Amount *= -1;
//					break;
//				}
//
//				std::cout << ToString( Amount ) << " " << Entry.Name << "\n";
//			}*/
//		}
//
//		// Print tax.
//		std::cout << "\n";
//		std::cout << "Gross Income: " << ToString( Statement.Tax.GrossIncome ) << "\n";
//		std::cout << "Student Loan Repayment: " << ToString( Statement.Tax.StudentLoanRepayment ) << "\n";
//		std::cout << "Student Loan Left: " << ToString( Statement.Tax.StudentLoanAfter ) << "\n";
//		std::cout << "Medicare Levy Payment: " << ToString( Statement.Tax.MedicareLevy ) << "\n";
//		std::cout << "Income Tax: " << ToString( Statement.Tax.IncomeTax ) << "\n";
//		std::cout << "Investment Deductions: " << ToString( Statement.Tax.InvestmentDeductionTotal ) << "\n";
//		std::cout << "Work Deductions: " << ToString( Statement.Tax.WorkDeductionTotal ) << "\n";
//		std::cout << "Business Deductions: " << ToString( Statement.Tax.BusinessDeductionTotal ) << "\n";
//		std::cout << "Total Tax: " << ToString( Statement.Tax.TotalTax ) << "\n";
//
//		std::cout << "\n\n\n";
//	}
//}