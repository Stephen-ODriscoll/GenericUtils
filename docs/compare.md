# PlutoUtils
[Back to README](https://www.github.com/Stephen-ODriscoll/PlutoUtils/blob/main/README.md#documentation)

## Compare.hpp
Contains comparison operators used by other utilities. Also contains case insensitive comparison operators.

The case insensitive comparison operators have two optimisations worth mentioning. Firstly, they take a locale and acquire the ctype facet at construction. This facet is then stored and used for conversions. In contrast, boost::algorithm::is_iequal() stores the locale and acquires the facet for every conversion.

Secondly, the functions that compare equality do an initial equality check. If this check returns true, then there is equality and no conversion is necessary, otherwise they convert and compare again. The performance hit for a worst case scenario when comparing lowercase vs uppercase is negligible, and there is a major performance gain from a best case scenario when comparing both lowercase or both uppercase. I have found that this is much more practical for real world scenarios.

### IsEqual
Alias of std::equal_to<>.

### IsNotEqual
Alias of std::not_equal_to<>.

### IsLess
Alias of std::less<>.

### IsGreater
Alias of std::greater<>.

### IsLessEqual
Alias of std::less_equal<>.

### IsGreaterEqual
Alias of std::greater_equal<>.

### IsEqualIgnoreCase
Case insensitive comparison. Returns true if left and right are equal, ignoring case.

### IsNotEqualIgnoreCase
Case insensitive comparison. Returns true if left and right are not equal, ignoring case.

### IsLessIgnoreCase
Case insensitive comparison. Returns true if left is less than right, ignoring case.

### IsGreaterIgnoreCase
Case insensitive comparison. Returns true if left is greater than right, ignoring case.

### IsLessEqualIgnoreCase
Case insensitive comparison. Returns true if left is less than or equal to right, ignoring case.

### IsGreaterEqualIgnoreCase
Case insensitive comparison. Returns true if left is greater than or equal to right, ignoring case.
