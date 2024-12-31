#pragma once

#include "Date.hpp"

template < typename _Data >
struct Interval
{
	using DataType = _Data;

	Date From, To;
	DataType Data;
};

template < typename _Data >
class IntervalList
{
public:

	using DataType = _Data;
	using IntervalType = Interval< DataType >;

	std::vector< IntervalType > Intervals;

	IntervalType* GetInterval( const Date& a_Date )
	{
		for ( auto& Interval : Intervals )
		{
			if ( a_Date >= Interval.From && a_Date <= Interval.To )
			{
				return &Interval;
			}
		}

		return nullptr;
	}

	void AddInterval( const Date& a_From, const Date& a_To, const DataType& a_Data )
	{
		Intervals.push_back( IntervalType{ a_From, a_To, a_Data } );
	}

	void AddInterval( const Date& a_When, const DataType& a_Data )
	{
		Intervals.push_back( IntervalType{ a_When, a_When, a_Data } );
	}
};

struct RecordBase
{
	Date When;
};

template < typename _State, typename _Record >
class RecordGenerator
{
public:

	using RecordType = _Record;
	using StateType = _State;

	Date Start;
	Date End;
	EFrequency Frequency;

	RecordGenerator() = default;

	virtual ~RecordGenerator() = default;

	RecordType operator[]( Date a_Date )
	{
		if ( m_Next == Date{} )
		{
			m_Next = Start;
		}

		// If we are trying to sample before the state allows, then this is an empty record.
		if ( a_Date < Start )
		{
			RecordType Record;
			Record.When = a_Date;
			return Record;
		}

		// If there is an end date, and we are past the end, then we will give back the
		// last record, or a default one if we have none.

		if ( End != Date{} && a_Date > End )
		{
			a_Date = End;
		}

		int32_t IndexRequested = GetIndex( a_Date );

		// If we already have a record for the date requested, just return it.
		if ( IndexRequested < Records.size() )
		{
			return Records[ IndexRequested ];
		}

		// If we get to this point, it means we need to generate to the index.
		// The way we do this is by generating to the currently set Next.
		// Once we generate to this next, we increment the Next.
		// Filling up to a date is done by filling in the last record available up
		// until the requested index.

		while ( true )
		{
			const Date CorrectedDate = Dates::Round( m_Next );
			const int32_t IndexNext = GetIndex( CorrectedDate );

			for ( int32_t i = ( int32_t )Records.size(); i <= IndexRequested && i < IndexNext; ++i )
			{
				RecordType Back = Records.back();
				Back.When = Dates::IncrementDays( Back.When, 1 );
				Records.push_back( Back );
			}

			if ( ( int32_t )Records.size() - 1 == IndexRequested )
			{
				return Records.back();
			}

			if ( ( int32_t )Records.size() == IndexNext )
			{
				m_Next = Dates::FindNext( m_Next, Frequency );
				Date NextCorrected = Dates::Round( m_Next );

				if ( NextCorrected > End )
				{
					NextCorrected = End;
				}

				RecordType Record = Generate( CorrectedDate, m_Last, NextCorrected );
				Record.When = CorrectedDate;

				Records.push_back( Record );
				m_Last = CorrectedDate;
			}
		}
	}

	std::vector< RecordType > Records;

protected:

	const StateType& GetState() const { return static_cast< const StateType& >( *this ); }
	StateType& GetState() { return static_cast< StateType& >( *this ); }

	double GetDaysInPeriod() const
	{
		switch ( Frequency )
		{
		default:
		case EFrequency::Once:
			return 0;
		case EFrequency::Daily:
			return 1;
		case EFrequency::Weekly:
			return 7;
		case EFrequency::Fortnightly:
			return 14;
		case EFrequency::Monthly:
			return Dates::AverageDaysInMonth();
		case EFrequency::Annually:
			return Dates::AverageDaysInYear();
		}
	}

	virtual RecordType Generate( const Date& a_Date, const Date& a_Last, const Date& a_Next ) = 0;

private:

	int32_t GetIndex( const Date& a_Date ) const { return Dates::Diff( a_Date, Start ); }

	Date m_Next = {};
	Date m_Last = {};
};