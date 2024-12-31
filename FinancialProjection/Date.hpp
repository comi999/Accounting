#pragma once
#include <chrono>

using namespace std::chrono_literals;
using namespace std::chrono;
using Date = year_month_day;

enum class EFrequency
{
	Once,
	Daily,
	Weekly,
	Fortnightly,
	Monthly,
	Annually,
};

namespace Dates
{
	constexpr double AverageDaysInYear()
	{
		return 365.2425;
	}

	constexpr double AverageDaysInMonth()
	{
		return AverageDaysInYear() / 12.0;
	}

	constexpr EFrequency HigherFrequency( const EFrequency a_Left, const EFrequency a_Right )
	{
		return ( int32_t )a_Left < ( int32_t )a_Right ? a_Left : a_Right;
	}

	constexpr int32_t Diff( const Date& a_Left, const Date& a_Right )
	{
		return ( sys_days{ a_Left } - sys_days{ a_Right } ).count();
	}

	constexpr Date Round( const Date& a_Date )
	{
		const Date Last = last/a_Date.month()/a_Date.year();
		if ( Last < a_Date ) return Last;
		return a_Date;
	}

	constexpr Date IncrementDays( const Date& a_Date, const int32_t a_Days )
	{
		return sys_days{ a_Date } + days{ a_Days };
	}

	constexpr Date IncrementWeeks( const Date& a_Date, const int32_t a_Weeks )
	{
		return sys_days{ a_Date } + weeks{ a_Weeks };
	}

	constexpr Date IncrementMonths( const Date& a_Date, const int32_t a_Months, const bool a_Rounded = false )
	{
		return a_Rounded ? Round( a_Date + months{ a_Months } ) : a_Date + months{ a_Months };
	}

	constexpr Date IncrementYears( const Date& a_Date, const int32_t a_Years, const bool a_Rounded = false )
	{
		return a_Rounded ? Round( a_Date + years{ a_Years } ) : a_Date + years{ a_Years };
	}

	constexpr Date FindNext( const Date& a_Current, const EFrequency a_Frequency )
	{
		switch ( a_Frequency )
		{
		default:
		case EFrequency::Once:
			return a_Current + years{1000};
		case EFrequency::Daily:
			return sys_days{ a_Current } + days{ 1 };
		case EFrequency::Weekly:
			return sys_days{ a_Current } + weeks{ 1 };
		case EFrequency::Fortnightly:
			return sys_days{ a_Current } + weeks{ 2 };
		case EFrequency::Monthly:
			return a_Current + months{ 1 };
		case EFrequency::Annually:
			return a_Current + years{ 1 };
		}
	}

	template < typename _Action >
	constexpr void ForEach( const Date& a_Start, const Date& a_End, const EFrequency a_Frequency, const _Action& a_Action )
	{
		Date Start = a_Start;

		while ( Start <= a_End )
		{
			Date Rounded = Round( Start );
			int32_t Index = Diff( Rounded, a_Start );
			a_Action( Rounded, Index );
			Start = FindNext( Start, a_Frequency );
		}
	}
}