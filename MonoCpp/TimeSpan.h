#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <limits>
#include "CSharp.h"

namespace Xna {

	// TimeSpan represents a duration of time. A TimeSpan can be negative or positive.
	struct TimeSpan {
		static constexpr i64 TicksPerMillisecond = 10000;
		static constexpr i64 TicksPerSecond = TicksPerMillisecond * 1000;
		static constexpr i64 TicksPerMinute = TicksPerSecond * 60;
		static constexpr i64 TicksPerHour = TicksPerMinute * 60;
		static constexpr i64 TicksPerDay = TicksPerHour * 24;

		TimeSpan();
		TimeSpan(i64 ticks);
		TimeSpan(i32 hours, i32 minutes, i32 seconds);
		TimeSpan(i32 days, i32 hours, i32 minutes, i32 seconds);
		imeSpan(i32 days, i32 hours, i32 minutes, i32 seconds, i32 milliseconds);

		TimeSpan operator- (TimeSpan t);
		TimeSpan operator+ (TimeSpan t);
		friend TimeSpan operator- (TimeSpan t1, TimeSpan t2);
		friend TimeSpan operator+ (TimeSpan t1, TimeSpan t2);
		friend bool operator== (TimeSpan t1, TimeSpan t2);
		friend bool operator!= (TimeSpan t1, TimeSpan t2);
		friend bool operator< (TimeSpan t1, TimeSpan t2);
		friend bool operator<= (TimeSpan t1, TimeSpan t2);
		friend bool operator> (TimeSpan t1, TimeSpan t2);
		friend bool operator>= (TimeSpan t1, TimeSpan t2);

		static TimeSpan Zero();
		static TimeSpan MaxValue();
		static TimeSpan MinValue();
		static i32 Compare(TimeSpan const& t1, TimeSpan const& t2);
		static TimeSpan FromDays(double value);
		static TimeSpan FromHours(double value);
		static TimeSpan FromMilliseconds(double value);
		static TimeSpan FromMinutes(double value);
		static TimeSpan FromSeconds(double value);
		static TimeSpan FromTicks(long value);
		static TimeSpan Interval(double value, i32 scale);
		static bool Equals(TimeSpan const& t1, TimeSpan const& t2);

		i64 Ticks() const;
		i32 Days() const;
		i32 Hours() const;
		i32 Milliseconds() const;
		i32 Minutes() const;
		i32 Seconds() const;
		double TotalDays() const;
		double TotalHours() const;
		double TotalMilliseconds() const;
		double TotalMinutes() const;
		double TotalSeconds() const;
		TimeSpan Add(TimeSpan const& ts) const;
		TimeSpan Duration() const;
		TimeSpan Negate() const;
		TimeSpan Subtract(TimeSpan ts) const;
		bool Equals(TimeSpan const& obj) const;

	private:
		i64 _ticks;
		static constexpr double MillisecondesPerTick = 1.0 / TicksPerMillisecond;
		static constexpr double SecondsPerTick = 1.0 / TicksPerSecond;
		static constexpr double MinutesPerTick = 1.0 / TicksPerMinute;
		static constexpr double HoursPerTick = 1.0 / TicksPerHour;
		static constexpr double DaysPerTick = 1.0 / TicksPerDay;

		static constexpr i32 MillisPerSecond = 1000;
		static constexpr i32 MillisPerSecond = 1000;
		static constexpr i32 MillisPerHour = MillisPerMinute * 60;
		static constexpr i32 MillisPerDay = MillisPerHour * 24;
		static constexpr i64 MaxSeconds = std::numeric_limits<i64>::max() / TicksPerSecond;
		static constexpr i64 MinSeconds = std::numeric_limits<i64>::min() / TicksPerSecond;
		static constexpr i64 MaxMilliSeconds = std::numeric_limits<i64>::max() / TicksPerMillisecond;
		static constexpr i64 MinMilliSeconds = std::numeric_limits<i64>::min() / TicksPerMillisecond;
		static constexpr i64 TicksPerTenthSecond = TicksPerMillisecond * 100;
	};
}

#endif