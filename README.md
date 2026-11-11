# xangle

An angle type that knows its unit. Header-only, C++20.

```cpp
debug_draw::cone(world, eyes, forward, 5.0f, 25.0f, yellow);  // 25 degrees or 25 radians?
```

A bare `float` doesn't say whether it holds degrees or radians, and the compiler can't tell either. With xangle the unit is part of the type:

```cpp
#include "angle.h"
using namespace utl::angle_literals;

void cone(..., float length, utl::rad_angle half_angle, color c);

cone(..., 25_deg, ...);   // converted to radians on the way in
cone(..., 0.44_rad, ...); // already radians
cone(..., 25.0f, ...);    // error: a bare float has no unit
```

This is the sibling of [xyesno](https://github.com/Dyronix/xyesno), which does the same for literal `true` and `false`.

## Usage

Copy `include/angle.h` into your project, or add the repository as a subdirectory:

```cmake
add_subdirectory(xangle)
target_link_libraries(my_game PRIVATE xangle::xangle)
```

### Types and literals

| | |
|---|---|
| `utl::deg_angle` | An angle in degrees |
| `utl::rad_angle` | An angle in radians |
| `25_deg`, `22.5_deg` | Degree literals, in `utl::angle_literals` |
| `1_rad`, `0.44_rad` | Radian literals, in `utl::angle_literals` |
| `.get()` | The raw `float`, for example to pass to `std::sin` |

### What compiles

| Compiles | Doesn't compile |
|---|---|
| `90_deg + 45_deg` | `25_deg * 25_deg`: angle times angle isn't an angle |
| `90_deg * 2.0f`, `90_deg / 2.0f` | `25_deg + 1_rad`: convert one side first |
| `90_deg / 45_deg` gives the `float` `2.0f` | `25_deg + 1.0f`: a float has no unit |
| `rad_angle r = 25_deg;` | `rad_angle r = 1.0f;`: the float constructor is explicit |
| `rad_angle(30_deg) < 1_rad` | `30_deg < 1_rad`: convert one side first |

### Design

- `angle<Unit>` is a single class template. A unit is a tag struct that says how many of it fit in one full turn (`360` for degrees, `2π` for radians). Adding a unit, such as turns or gradians, takes one more struct.
- Converting between units is implicit, because the angle stays the same. Constructing from a `float` is explicit.
- Operators need the same unit on both sides.
- `sizeof(rad_angle) == sizeof(float)` and everything is `constexpr`, so the checks cost nothing at runtime.

## Tests

`tests/angle_tests.cpp` checks everything with `static_assert`. If it builds, the tests pass.

```
cmake -B build
cmake --build build
```

## Credits

Based on `deg_angle.h` and `rad_angle.h` from [RexStl](https://github.com/RisingLiberty/RexStl) by Nick De Breuck ([@RisingLiberty](https://github.com/RisingLiberty)). xangle merges the two classes into one template and fixes a few issues along the way: an ambiguous default constructor, literals that rejected decimals, and no conversion between the two types.

## License

MIT. See [LICENSE](LICENSE).
