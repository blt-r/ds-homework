#pragma once

#include <numeric>
#include <ostream>
#include <stdexcept>

namespace yourname {

template <typename T>
class RationalNumber {
    T top;
    T bottom;

    void zero_bottom_check() const;
    void zero_top_check();
    void negative_bottom_check();
    void reduce();

   public:
    T get_top() const;
    T get_bottom() const;

    RationalNumber();
    RationalNumber(const T& top_);
    RationalNumber(const T& top_, const T& bottom_);

    RationalNumber operator+() const;
    RationalNumber operator-() const;

    RationalNumber& operator+=(const RationalNumber& other);
    RationalNumber& operator-=(const RationalNumber& other);
    RationalNumber& operator*=(const RationalNumber& other);
    RationalNumber& operator/=(const RationalNumber& other);

    // Prefix
    RationalNumber& operator++();
    // Postfix
    RationalNumber operator++(int);

    auto operator<=>(const RationalNumber& other) const;
    bool operator==(const RationalNumber& other) const;

    template <std::constructible_from<T> U>
        requires requires(U a, U b) {
            { a / b } -> std::same_as<U>;
        }
    explicit operator U();
};

template <typename T>
T RationalNumber<T>::get_top() const {
    return top;
}

template <typename T>
T RationalNumber<T>::get_bottom() const {
    return bottom;
}

template <typename T>
void RationalNumber<T>::zero_bottom_check() const {
    if (bottom == 0) {
        throw std::invalid_argument("bottom of a fraction cannot be 0");
    }
}
template <typename T>
void RationalNumber<T>::zero_top_check() {
    if (top == 0) {
        bottom = 1;
    }
}
template <typename T>
void RationalNumber<T>::negative_bottom_check() {
    if (bottom < 0) {
        top = -top;
        bottom = -bottom;
    }
}

template <typename T>
void RationalNumber<T>::reduce() {
    auto gcd = std::gcd(top, bottom);
    top /= gcd;
    bottom /= gcd;
}

template <typename T>
RationalNumber<T>::RationalNumber() : top(0), bottom(1) {}

template <typename T>
RationalNumber<T>::RationalNumber(const T& top_) : top(top_), bottom(1) {}

template <typename T>
RationalNumber<T>::RationalNumber(const T& top_, const T& bottom_)
    : top(top_), bottom(bottom_) {
    // Invariants:
    zero_bottom_check();
    negative_bottom_check();
    zero_top_check();
    reduce();
}

template <typename T>
RationalNumber<T> RationalNumber<T>::operator+() const {
    return *this;
}
template <typename T>
RationalNumber<T> RationalNumber<T>::operator-() const {
    RationalNumber r;
    r.top = -top;
    r.bottom = bottom;
    return r;
}

template <typename T>
RationalNumber<T>& RationalNumber<T>::operator+=(const RationalNumber& other) {
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
RationalNumber<T>& RationalNumber<T>::operator-=(const RationalNumber& other) {
    *this += (-other);
    return *this;
}

template <typename T>
RationalNumber<T>& RationalNumber<T>::operator*=(const RationalNumber& other) {
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
RationalNumber<T>& RationalNumber<T>::operator/=(const RationalNumber& other) {
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
RationalNumber<T>& RationalNumber<T>::operator++() {
    top += bottom;
    return *this;
}
// Postfix
template <typename T>
RationalNumber<T> RationalNumber<T>::operator++(int) {
    auto old = *this;
    top += bottom;
    return old;
}

template <typename T>
auto RationalNumber<T>::operator<=>(const RationalNumber& other) const {
    return top * other.bottom <=> other.top * bottom;
}
template <typename T>
bool RationalNumber<T>::operator==(const RationalNumber& other) const = default;

template <typename T>
template <std::constructible_from<T> U>
    requires requires(U a, U b) {
        { a / b } -> std::same_as<U>;
    }
RationalNumber<T>::operator U() {
    return U(top) / U(bottom);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const RationalNumber<T>& self) {
    os << self.get_top() << '/' << self.get_bottom();
    return os;
}

template <typename T>
RationalNumber<T> operator+(const RationalNumber<T>& lhs,
                            const RationalNumber<T>& rhs) {
    auto result = lhs;
    result += rhs;
    return result;
}

template <typename T>
RationalNumber<T> operator-(const RationalNumber<T>& lhs,
                            const RationalNumber<T>& rhs) {
    auto result = lhs;
    result -= rhs;
    return result;
}

template <typename T>
RationalNumber<T> operator*(const RationalNumber<T>& lhs,
                            const RationalNumber<T>& rhs) {
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T>
RationalNumber<T> operator/(const RationalNumber<T>& lhs,
                            const RationalNumber<T>& rhs) {
    auto result = lhs;
    result /= rhs;
    return result;
}

template <typename T>
RationalNumber<T> operator+(const T& lhs, const RationalNumber<T>& rhs) {
    return RationalNumber(lhs) + rhs;
}
template <typename T>
RationalNumber<T> operator-(const T& lhs, const RationalNumber<T>& rhs) {
    return RationalNumber(lhs) - rhs;
}
template <typename T>
RationalNumber<T> operator*(const T& lhs, const RationalNumber<T>& rhs) {
    return RationalNumber(lhs) * rhs;
}
template <typename T>
RationalNumber<T> operator/(const T& lhs, const RationalNumber<T>& rhs) {
    return RationalNumber(lhs) / rhs;
}

namespace literals {
RationalNumber<unsigned long long> operator""_r(unsigned long long t) {
    return RationalNumber(t);
}
}  // namespace literals

}  // namespace yourname
