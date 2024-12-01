#pragma once

#include <numeric>
#include <ostream>
#include <stdexcept>

namespace yourname {

template <typename T>
class RationalNumber {
    T top;
    T bottom;

    auto zero_bottom_check() const -> void;
    auto zero_top_check() -> void;
    auto negative_bottom_check() -> void;
    auto reduce() -> void;

  public:
    auto get_top() const -> T;
    auto get_bottom() const -> T;

    RationalNumber();
    RationalNumber(const T& top_);
    RationalNumber(const T& top_, const T& bottom_);

    auto operator+() const -> RationalNumber;
    auto operator-() const -> RationalNumber;

    auto operator+=(const RationalNumber& other) -> RationalNumber&;
    auto operator-=(const RationalNumber& other) -> RationalNumber&;
    auto operator*=(const RationalNumber& other) -> RationalNumber&;
    auto operator/=(const RationalNumber& other) -> RationalNumber&;

    auto operator++() -> RationalNumber&;    // Prefix
    auto operator++(int) -> RationalNumber;  // Postfix

    auto operator<=>(const RationalNumber& other) const;
    auto operator==(const RationalNumber& other) const -> bool;

    template <std::constructible_from<T> U>
        requires requires(U a, U b) {
            { a / b } -> std::same_as<U>;
        }
    explicit operator U();
};

template <typename T>
auto RationalNumber<T>::get_top() const -> T {
    return top;
}

template <typename T>
auto RationalNumber<T>::get_bottom() const -> T {
    return bottom;
}

template <typename T>
auto RationalNumber<T>::zero_bottom_check() const -> void {
    if (bottom == 0) {
        throw std::invalid_argument("bottom of a fraction cannot be 0");
    }
}
template <typename T>
auto RationalNumber<T>::zero_top_check() -> void {
    if (top == 0) {
        bottom = 1;
    }
}
template <typename T>
auto RationalNumber<T>::negative_bottom_check() -> void {
    if (bottom < 0) {
        top = -top;
        bottom = -bottom;
    }
}

template <typename T>
auto RationalNumber<T>::reduce() -> void {
    auto gcd = std::gcd(top, bottom);
    top /= gcd;
    bottom /= gcd;
}

template <typename T>
RationalNumber<T>::RationalNumber() : top(0), bottom(1) {}

template <typename T>
RationalNumber<T>::RationalNumber(const T& top) : top(top), bottom(1) {}

template <typename T>
RationalNumber<T>::RationalNumber(const T& top, const T& bottom)
    : top(top), bottom(bottom) {
    // Invariants:
    zero_bottom_check();
    negative_bottom_check();
    zero_top_check();
    reduce();
}

template <typename T>
auto RationalNumber<T>::operator+() const -> RationalNumber<T> {
    return *this;
}
template <typename T>
auto RationalNumber<T>::operator-() const -> RationalNumber<T> {
    RationalNumber r;
    r.top = -top;
    r.bottom = bottom;
    return r;
}

template <typename T>
auto RationalNumber<T>::operator+=(const RationalNumber& other)
    -> RationalNumber<T>& {
    auto gcd = std::gcd(bottom, other.bottom);
    auto top1 = top * (other.bottom / gcd);
    auto top2 = other.top * (bottom / gcd);

    top = top1 + top2;
    bottom = bottom / gcd * other.bottom;

    reduce();
    zero_top_check();

    return *this;
}

template <typename T>
auto RationalNumber<T>::operator-=(const RationalNumber& other)
    -> RationalNumber<T>& {
    *this += (-other);
    return *this;
}

template <typename T>
auto RationalNumber<T>::operator*=(const RationalNumber& other)
    -> RationalNumber<T>& {
    auto gcd1 = std::gcd(top, other.bottom);
    auto gcd2 = std::gcd(bottom, other.top);
    top = (top / gcd1) * (other.top / gcd2);
    bottom = (bottom / gcd2) * (other.bottom / gcd1);

    zero_top_check();
    negative_bottom_check();
    reduce();

    return *this;
}

template <typename T>
auto RationalNumber<T>::operator/=(const RationalNumber& other)
    -> RationalNumber<T>& {
    RationalNumber<T> reciprocal;
    reciprocal.top = other.bottom;
    reciprocal.bottom = other.top;
    reciprocal.zero_bottom_check();
    reciprocal.negative_bottom_check();

    *this *= reciprocal;

    return *this;
}

// Prefix
template <typename T>
auto RationalNumber<T>::operator++() -> RationalNumber<T>& {
    top += bottom;
    return *this;
}
// Postfix
template <typename T>
auto RationalNumber<T>::operator++(int) -> RationalNumber<T> {
    auto old = *this;
    top += bottom;
    return old;
}

template <typename T>
auto RationalNumber<T>::operator<=>(const RationalNumber& other) const {
    return top * other.bottom <=> other.top * bottom;
}
template <typename T>
auto RationalNumber<T>::operator==(const RationalNumber& other) const
    -> bool = default;

template <typename T>
template <std::constructible_from<T> U>
    requires requires(U a, U b) {
        { a / b } -> std::same_as<U>;
    }
RationalNumber<T>::operator U() {
    return U(top) / U(bottom);
}

template <typename T>
auto operator<<(std::ostream& os, const RationalNumber<T>& self)
    -> std::ostream& {
    os << self.get_top() << '/' << self.get_bottom();
    return os;
}

template <typename T>
auto operator+(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    auto result = lhs;
    result += rhs;
    return result;
}

template <typename T>
auto operator-(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    auto result = lhs;
    result -= rhs;
    return result;
}

template <typename T>
auto operator*(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T>
auto operator/(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    auto result = lhs;
    result /= rhs;
    return result;
}

template <typename T>
auto operator+(const T& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    return RationalNumber(lhs) + rhs;
}
template <typename T>
auto operator-(const T& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    return RationalNumber(lhs) - rhs;
}
template <typename T>
auto operator*(const T& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    return RationalNumber(lhs) * rhs;
}
template <typename T>
auto operator/(const T& lhs, const RationalNumber<T>& rhs)
    -> RationalNumber<T> {
    return RationalNumber(lhs) / rhs;
}

namespace literals {
auto operator""_r(unsigned long long t) -> RationalNumber<unsigned long long> {
    return RationalNumber(t);
}
}  // namespace literals

}  // namespace yourname
