// Every check runs at compile time. If this file builds, the tests pass.
#include "angle.h"

using namespace utl::angle_literals;
using utl::deg_angle;
using utl::rad_angle;

namespace
{
  constexpr bool near(float a, float b)
  {
    return (a > b ? a - b : b - a) < 0.0001f;
  }

  // An example function that wants radians.
  constexpr float half_angle_of(rad_angle half_angle)
  {
    return half_angle.get();
  }
} // namespace

// Construction
static_assert(rad_angle {}.get() == 0.0f);
static_assert(deg_angle(25.0f).get() == 25.0f);
static_assert((22.5_deg).get() == 22.5f);
static_assert((1_rad).get() == 1.0f);

// Conversion between units
static_assert(near(rad_angle(180_deg).get(), utl::pi_v));
static_assert(near(deg_angle(rad_angle(utl::pi_v)).get(), 180.0f));
static_assert(near(half_angle_of(25_deg), 0.436332f));

// Arithmetic
static_assert(90_deg + 45_deg == 135_deg);
static_assert(90_deg - 45_deg == 45_deg);
static_assert(-90_deg == deg_angle(-90.0f));
static_assert(90_deg * 2.0f == 180_deg);
static_assert(2.0f * 90_deg == 180_deg);
static_assert(90_deg / 2.0f == 45_deg);
static_assert(90_deg / 45_deg == 2.0f);

// Comparison
static_assert(30_deg < 45_deg);
static_assert(45_deg <= 45_deg);
static_assert(rad_angle(30_deg) < 1_rad);
static_assert(180_deg != 90_deg);

// Zero cost
static_assert(sizeof(rad_angle) == sizeof(float));

// These don't compile, on purpose:
//   half_angle_of(25.0f);     // a bare float has no unit
//   rad_angle a = 1.0f;       // the float constructor is explicit
//   25_deg * 25_deg;          // angle times angle isn't an angle
//   25_deg + 1_rad;           // convert one side first
//   25_deg + 1.0f;            // a float has no unit

int main()
{
  return 0;
}
