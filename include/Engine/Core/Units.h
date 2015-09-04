#ifndef _ENGINE_UNITS_H_
#define _ENGINE_UNITS_H_

namespace Engine
{
	class Meters
	{
	private:
		float mValue;

	public:
		Meters(float m)
		{
			mValue = m;
		}

		float value() const
		{
			return mValue;
		}

		Meters& operator=(const Meters &rhs)
		{
			mValue = rhs.mValue;
			return *this;
		}

		Meters operator+(const Meters &rhs) const
		{
			return Meters(mValue + rhs.mValue);
		}

		Meters& operator+=(const Meters &rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}

		Meters operator-(const Meters &rhs) const
		{
			return Meters(mValue - rhs.mValue);
		}

		Meters& operator-=(const Meters &rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		bool operator<(const Meters &rhs) const
		{
			return mValue < rhs.mValue;
		}

		bool operator<=(const Meters &rhs) const
		{
			return mValue <= rhs.mValue;
		}

		bool operator==(const Meters &rhs) const
		{
			return mValue == rhs.mValue;
		}

		bool operator>=(const Meters &rhs) const
		{
			return mValue >= rhs.mValue;
		}

		bool operator>(const Meters &rhs) const
		{
			return mValue > rhs.mValue;
		}
	};

	class Feet
	{
	private:
		float mValue;

	public:
		Feet(float val)
		{
			mValue = val;
		}

		Feet(const Meters &val)
		{
			mValue = val.value() * 3.28084f;
		}

		float value() const
		{
			return mValue;
		}

		operator Meters() const
		{
			return Meters(mValue * 0.3048);
		}

		Feet& operator=(const Feet &rhs)
		{
			mValue = rhs.mValue;
			return *this;
		}

		Feet operator+(const Feet &rhs)
		{
			return Meters(mValue + rhs.mValue);
		}

		Feet& operator+=(const Feet &rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}

		Feet operator-(const Feet &rhs)
		{
			return Meters(mValue - rhs.mValue);
		}

		Feet& operator-=(const Feet &rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		bool operator<(const Feet &rhs)
		{
			return mValue < rhs.mValue;
		}

		bool operator<=(const Feet &rhs)
		{
			return mValue <= rhs.mValue;
		}

		bool operator==(const Feet &rhs)
		{
			return mValue == rhs.mValue;
		}

		bool operator>=(const Feet &rhs)
		{
			return mValue >= rhs.mValue;
		}

		bool operator>(const Feet &rhs)
		{
			return mValue > rhs.mValue;
		}
	};

	//////////////////////////////

	class Radians
	{
	private:
		float mValue;

	public:
		Radians(float val)
		{
			mValue = val;
		}

		float value() const
		{
			return mValue;
		}

		Radians& operator=(const Radians &rhs)
		{
			mValue = rhs.mValue;
			return *this;
		}

		Radians operator+(const Radians &rhs) const
		{
			return Radians(mValue + rhs.mValue);
		}

		Radians& operator+=(const Radians &rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}

		Radians operator-(const Radians &rhs) const
		{
			return Radians(mValue - rhs.mValue);
		}

		Radians& operator-=(const Radians &rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		bool operator<(const Radians &rhs) const
		{
			return mValue < rhs.mValue;
		}

		bool operator<=(const Radians &rhs) const
		{
			return mValue <= rhs.mValue;
		}

		bool operator==(const Radians &rhs) const
		{
			return mValue == rhs.mValue;
		}

		bool operator>=(const Radians &rhs) const
		{
			return mValue >= rhs.mValue;
		}

		bool operator>(const Radians &rhs) const
		{
			return mValue > rhs.mValue;
		}
	};

	class Degrees
	{
	private:
		float mValue;

	public:
		Degrees(float val)
		{
			mValue = val;
		}

		Degrees(const Radians &val)
		{
			mValue = val.value() * 57.2957795;
		}

		float value() const
		{
			return mValue;
		}

		operator Radians() const
		{
			return Radians(mValue * 0.0174532925);
		}

		Degrees& operator=(const Degrees &rhs)
		{
			mValue = rhs.mValue;
			return *this;
		}

		Degrees operator+(const Degrees &rhs)
		{
			return Degrees(mValue + rhs.mValue);
		}

		Degrees& operator+=(const Degrees &rhs)
		{
			mValue += rhs.mValue;
			return *this;
		}

		Degrees operator-(const Degrees &rhs)
		{
			return Degrees(mValue - rhs.mValue);
		}

		Degrees& operator-=(const Degrees &rhs)
		{
			mValue -= rhs.mValue;
			return *this;
		}

		bool operator<(const Degrees &rhs)
		{
			return mValue < rhs.mValue;
		}

		bool operator<=(const Degrees &rhs)
		{
			return mValue <= rhs.mValue;
		}

		bool operator==(const Degrees &rhs)
		{
			return mValue == rhs.mValue;
		}

		bool operator>=(const Degrees &rhs)
		{
			return mValue >= rhs.mValue;
		}

		bool operator>(const Degrees &rhs)
		{
			return mValue > rhs.mValue;
		}
	};
}

#endif // _ENGINE_UNITS_H_