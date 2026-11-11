// xangle: an angle type that knows its unit.
// https://github.com/Dyronix/xangle
//
// Based on deg_angle.h and rad_angle.h from RexStl by Nick De Breuck
// (https://github.com/RisingLiberty/RexStl).
//
// One class template replaces the two classes. The unit is part of the type,
// so degrees and radians can't be mixed up, and a bare float can't be passed
// where an angle is expected.

#pragma once

namespace utl
{
  inline constexpr float pi_v = 3.14159265358979323846f;

  // A unit says how many of it fit in one full turn.
  struct deg_unit
  {
    static constexpr float per_turn = 360.0f;
  };
  struct rad_unit
  {
    static constexpr float per_turn = 2.0f * pi_v;
  };

  template <typename Unit>
  class angle
  {
  public:
    constexpr angle() = default;
    constexpr explicit angle(float value)
        : m_value(value)
    {
    }

    // Converting between units keeps the same angle, so it's allowed implicitly.
    template <typename OtherUnit>
    constexpr angle(angle<OtherUnit> other)
        : m_value(other.get() * (Unit::per_turn / OtherUnit::per_turn))
    {
    }

    constexpr float get() const
    {
      return m_value;
    }

    constexpr angle& operator+=(angle other)
    {
      m_value += other.m_value;
      return *this;
    }
    constexpr angle& operator-=(angle other)
    {
      m_value -= other.m_value;
      return *this;
    }
    constexpr angle& operator*=(float scale)
    {
      m_value *= scale;
      return *this;
    }
    constexpr angle& operator/=(float scale)
    {
      m_value /= scale;
      return *this;
    }

  private:
    float m_value = 0.0f;
  };

  // Free templates: both sides must have the same unit. Convert first, then compute.
  template <typename U>
  constexpr angle<U> operator+(angle<U> a, angle<U> b)
  {
    return a += b;
  }
  template <typename U>
  constexpr angle<U> operator-(angle<U> a, angle<U> b)
  {
    return a -= b;
  }
  template <typename U>
  constexpr angle<U> operator-(angle<U> a)
  {
    return angle<U>(-a.get());
  }
  template <typename U>
  constexpr angle<U> operator*(angle<U> a, float scale)
  {
    return a *= scale;
  }
  template <typename U>
  constexpr angle<U> operator*(float scale, angle<U> a)
  {
    return a *= scale;
  }
  template <typename U>
  constexpr angle<U> operator/(angle<U> a, float scale)
  {
    return a /= scale;
  }
  // An angle divided by an angle is a plain ratio, not an angle.
  template <typename U>
  constexpr float operator/(angle<U> a, angle<U> b)
  {
    return a.get() / b.get();
  }

  template <typename U>
  constexpr bool operator==(angle<U> a, angle<U> b)
  {
    return a.get() == b.get();
  }
  template <typename U>
  constexpr bool operator<(angle<U> a, angle<U> b)
  {
    return a.get() < b.get();
  }
  template <typename U>
  constexpr bool operator<=(angle<U> a, angle<U> b)
  {
    return a.get() <= b.get();
  }
  template <typename U>
  constexpr bool operator>(angle<U> a, angle<U> b)
  {
    return a.get() > b.get();
  }
  template <typename U>
  constexpr bool operator>=(angle<U> a, angle<U> b)
  {
    return a.get() >= b.get();
  }

  using deg_angle = angle<deg_unit>;
  using rad_angle = angle<rad_unit>;

  inline namespace angle_literals
  {
    constexpr deg_angle operator""_deg(long double value)
    {
      return deg_angle(static_cast<float>(value));
    }
    constexpr deg_angle operator""_deg(unsigned long long value)
    {
      return deg_angle(static_cast<float>(value));
    }
    constexpr rad_angle operator""_rad(long double value)
    {
      return rad_angle(static_cast<float>(value));
    }
    constexpr rad_angle operator""_rad(unsigned long long value)
    {
      return rad_angle(static_cast<float>(value));
    }
  } // namespace angle_literals

} // namespace utl
