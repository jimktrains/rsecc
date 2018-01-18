#include<limits>

/* https://www.kernel.org/pub/linux/kernel/people/hpa/raid6.pdf */

/* x^8 + x^4 + x^3 + x^2 + 1 mod 255 */
// 00011101

template<int N>
struct GF2Constants
{
  static const int64_t POLY;
  static const int64_t MOD;
};

template<>
struct GF2Constants<8>
{
  static const int64_t POLY = 0x1d;
  static const int64_t MOD = 256;
};

template<int N>
class GF2
{
  public:
    int64_t value;
		static int64_t log[GF2Constants<N>::MOD];
		static int64_t ilog[GF2Constants<N>::MOD];

    static void init()
    {
      int64_t c = 1;
      for(int64_t i = 0; i < GF2Constants<N>::MOD; i++, c = GF2::LFSR(c))
      {
        GF2::log[c] = i;
        GF2::ilog[i] = c;
      }
    }

    constexpr GF2(int64_t value) : value(value)
    {
    }

    constexpr GF2() : value(0)
    {
    }

    constexpr static int64_t LFSR(int64_t c)
    {
      return ((( (c) << 1) ^ ((c & 1 << (N-1) ) ?  GF2Constants<N>::POLY : 0) )) % GF2Constants<N>::MOD;
    }

    bool operator == (GF2 b);
    GF2<N> operator +(GF2<N> b);
    GF2<N> operator +=(GF2<N> b);
    GF2<N> operator -(GF2<N> b);
    GF2<N> operator -=(GF2<N> b);
    GF2<N> operator *(GF2<N> b);
    GF2<N> operator /(GF2<N> b);
    GF2<N> minv();

};

template<int N>
int64_t GF2<N> :: log[GF2Constants<N>::MOD];

template<int N>
int64_t GF2<N> :: ilog[GF2Constants<N>::MOD];

template<int N>
bool GF2<N> :: operator == (GF2<N> b)
{
  return (value == b.value);
}

template<int N>
GF2<N> GF2<N> :: operator +(GF2<N> b)
{
  return this->value ^ b.value;
}

template<int N>
GF2<N> GF2<N> :: operator +=(GF2<N> b)
{
  return this->value ^= b.value;
}

template<int N>
GF2<N> GF2<N> :: operator -(GF2<N> b)
{
  return *this + b;
}

template<int N>
GF2<N> GF2<N> :: operator -=(GF2<N> b)
{
  return *this += b;
}

template<int N>
GF2<N> GF2<N> :: operator *(GF2<N> b)
{
  if (*this == 0 || b == 0) return 0;

  int64_t log_sum = GF2<N>::log[value] + GF2<N>::log[b.value];
  if (log_sum >= GF2Constants<N>::MOD) log_sum -= (GF2Constants<N>::MOD - 1);
  return GF2<N>::ilog[log_sum];
}

template<int N>
GF2<N> GF2<N> :: operator /(GF2<N> b)
{
  if (*this == 0 || b == 0) return 0;

  int64_t log_sub = GF2<N>::log[value] - GF2<N>::log[b.value];
  if (log_sub < 0) log_sub += (GF2Constants<N>::MOD - 1);
  return GF2<N>::ilog[log_sub];
}

template<int N>
GF2<N> GF2<N> :: minv()
{
  return GF2<N>(1) / *this;
}

template<int N>
std::ostream &operator<<(std::ostream &os, GF2<N> const &m) {
      return os << static_cast<int>(m.value);
}

