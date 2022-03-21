#include "CSharp.h"
#include "MathHelper.h"

namespace Xna {

	//----------    ----------    ----------//
	//$ TIMESPAN							//
	//----------    ----------    ----------//

	TimeSpan::TimeSpan() :
		_ticks(0) {}

	TimeSpan::TimeSpan(i64 ticks) :
		_ticks(ticks) {}

	TimeSpan::TimeSpan(i32 hours, i32 minutes, i32 seconds) {
		_ticks = TimeSpan::TimeToTicks(hours, minutes, seconds);
	}

	TimeSpan::TimeSpan(i64 days, i64 hours, i64 minutes, i32 seconds, i32 milliseconds) {
		i64 totalMilliSeconds = (days * 3600 * 24 + hours * 3600
			+ minutes * 60 + seconds) * 1000 + milliseconds;

		if (totalMilliSeconds > MaxMilliSeconds) {
			totalMilliSeconds = MaxMilliSeconds;
		}
		else {
			totalMilliSeconds = MinMilliSeconds;
		}

		_ticks = totalMilliSeconds * TicksPerMillisecond;
	}

	TimeSpan TimeSpan::operator- (TimeSpan t) {
		if (t._ticks == TimeSpan::MinValue()._ticks)
			return TimeSpan::Zero();
		
		return TimeSpan(-t._ticks);
	}

	TimeSpan TimeSpan::operator+ (TimeSpan t) {
		return t;
	}

	TimeSpan operator- (TimeSpan t1, TimeSpan t2) {
		return t1.Subtract(t2);
	}

	TimeSpan operator+ (TimeSpan t1, TimeSpan t2) {
		return t1.Add(t2);
	}

	bool operator== (TimeSpan t1, TimeSpan t2) {
		return t1.Equals(t2);
	}

	bool operator!= (TimeSpan t1, TimeSpan t2) {
		return !t1.Equals(t2);
	}
	bool operator< (TimeSpan t1, TimeSpan t2) {
		return t1._ticks < t2._ticks;
	}

	bool operator<= (TimeSpan t1, TimeSpan t2) {
		return t1._ticks <= t2._ticks;
	}

	bool operator> (TimeSpan t1, TimeSpan t2) {
		return t1._ticks > t2._ticks;
	}

	bool operator>= (TimeSpan t1, TimeSpan t2) {
		return t1._ticks >= t2._ticks;
	}

	TimeSpan TimeSpan::Zero() {
		return TimeSpan(0);
	}

	TimeSpan TimeSpan::MaxValue() {
		return TimeSpan(std::numeric_limits<i64>::max());
	}

	TimeSpan TimeSpan::MinValue() {
		return TimeSpan(std::numeric_limits<i64>::min());
	}

	i32 TimeSpan::Compare(TimeSpan const& t1, TimeSpan const& t2) {
		if (t1._ticks > t2._ticks)
			return 1;

		if (t1._ticks < t2._ticks)
			return -1;

		return 0;
	}

	TimeSpan TimeSpan::FromDays(double value) {
		return Interval(value, MillisPerDay);
	}

	TimeSpan TimeSpan::FromHours(double value) {
		return Interval(value, MillisPerHour);
	}

	TimeSpan TimeSpan::FromMilliseconds(double value) {
		return Interval(value, 1);
	}

	TimeSpan TimeSpan::FromMinutes(double value) {
		return Interval(value, MillisPerMinute);
	}

	TimeSpan TimeSpan::FromSeconds(double value) {
		return Interval(value, MillisPerSecond);
	}

	TimeSpan TimeSpan::FromTicks(long value) {
		return TimeSpan(value);
	}
	
	TimeSpan TimeSpan::Interval(double value, i32 scale) {
		if (MathHelper::IsNan(value))
			return TimeSpan::Zero();

		double tmp = value * scale;
		double millis = tmp + (value >= 0 ? 0.5 : -0.5);

		if ((millis > std::numeric_limits<i64>::max() / TicksPerMillisecond)
			|| (millis < std::numeric_limits<i64>::min() / TicksPerMillisecond)) {
			return TimeSpan::Zero();
		}
			
		return TimeSpan(static_cast<i64>(millis) * TicksPerMillisecond);
	}

	long TimeSpan::TimeToTicks(i32 hour, i32 minute, i32 second) {
		long totalSeconds = (long)hour * 3600 + (long)minute * 60 + (long)second;
		
		if (totalSeconds > TimeSpan::MaxSeconds || totalSeconds < TimeSpan::MinSeconds)
			return 0;

		return totalSeconds * TicksPerSecond;
	}

	bool TimeSpan::Equals(TimeSpan const& t1, TimeSpan const& t2) {
		return t1._ticks == t2._ticks;
	}

	i64 TimeSpan::Ticks() const {
		return _ticks; 
	}

	i32 TimeSpan::Days() const { 
		return static_cast<i32>(_ticks / TicksPerDay); 
	}

	i32 TimeSpan::Hours() const { 
		return static_cast<i32>((_ticks / TicksPerHour) % 24);
	}

	i32 TimeSpan::Milliseconds() const {
		return static_cast<i32>((_ticks / TicksPerMillisecond) % 1000);
	}

	i32 TimeSpan::Minutes() const {
		return static_cast<i32>((_ticks / TicksPerMinute) % 60);
	}

	i32 TimeSpan::Seconds() const {
		return static_cast<i32>((_ticks / TicksPerSecond) % 60);
	}

	double TimeSpan::TotalDays() const {
		return static_cast<double>(_ticks) * DaysPerTick;
	}

	double TimeSpan::TotalHours() const { 
		return static_cast<double>(_ticks) * HoursPerTick;
	}

	double TimeSpan::TotalMilliseconds() const {
		double temp = static_cast<double>(_ticks) * MillisecondsPerTick;
		if (temp > MaxMilliSeconds)
			return  static_cast<double>(MaxMilliSeconds);

		if (temp < MinMilliSeconds)
			return  static_cast<double>(MinMilliSeconds);

		return temp;
	}

	double TimeSpan::TotalMinutes() const {
		return static_cast<double>(_ticks) * MinutesPerTick;
	}

	double TimeSpan::TotalSeconds() const { 
		return static_cast<double>(_ticks) * SecondsPerTick;
	}

	TimeSpan TimeSpan::Add(TimeSpan const& ts) const {
		i64 result = _ticks + ts._ticks;

		if ((_ticks >> 63 == ts._ticks >> 63) && (_ticks >> 63 != result >> 63))
			return TimeSpan::Zero();

		return TimeSpan(result);
	}

	TimeSpan TimeSpan::Duration() const {
		if (Ticks() == TimeSpan::MinValue().Ticks())
			return TimeSpan::Zero();
		
		return TimeSpan(_ticks >= 0 ? _ticks : -_ticks);
	}

	TimeSpan TimeSpan::Negate() const {
		if (Ticks() == TimeSpan::MinValue().Ticks())
			return TimeSpan::Zero();

		return TimeSpan(-_ticks);
	}

	TimeSpan TimeSpan::Subtract(TimeSpan ts) const {
		i64 result = _ticks - ts._ticks;
		
		if ((_ticks >> 63 != ts._ticks >> 63) && (_ticks >> 63 != result >> 63))
			return TimeSpan::Zero();

		return TimeSpan(result);
	}
	
	bool TimeSpan::Equals(TimeSpan const& obj) const {
		return _ticks == obj._ticks;
	}
}