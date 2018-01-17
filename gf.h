
/* https://www.kernel.org/pub/linux/kernel/people/hpa/raid6.pdf */

/* x^8 + x^4 + x^3 + x^2 + 1 mod 255 */
// 00011101

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
class GF2
{
  public:
    STORAGE value;
		static STORAGE log[PRIME];
		static STORAGE ilog[PRIME];

    static void init()
    {
      STORAGE c = 1;
      for(int i = 0; i < PRIME; i++, c = GF2::LFSR(c))
      {
        GF2::log[c] = i;
        GF2::ilog[i] = c;
      }
    }

    constexpr GF2(STORAGE value) : value(value)
    {
    }
    constexpr GF2() : value(0)
    {
    }

    constexpr static STORAGE LFSR(STORAGE c)
    {
      return ((( (c) << 1) ^ ((c & 1 << (8 *sizeof(STORAGE) -1) ) ?  POLY : 0) ));
    }

    bool operator == (GF2 b);
    GF2<STORAGE, POLY, PRIME> operator +(GF2<STORAGE, POLY, PRIME> b);
    GF2<STORAGE, POLY, PRIME> operator +=(GF2<STORAGE, POLY, PRIME> b);
    GF2<STORAGE, POLY, PRIME> operator -(GF2<STORAGE, POLY, PRIME> b);
    GF2<STORAGE, POLY, PRIME> operator -=(GF2<STORAGE, POLY, PRIME> b);
    GF2<STORAGE, POLY, PRIME> operator *(GF2<STORAGE, POLY, PRIME> b);
    GF2<STORAGE, POLY, PRIME> operator /(GF2<STORAGE, POLY, PRIME> b);
    GF2<STORAGE, POLY, PRIME> minv();

};

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
STORAGE GF2<STORAGE, POLY, PRIME> :: log[PRIME];

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
STORAGE GF2<STORAGE, POLY, PRIME> :: ilog[PRIME];

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
bool GF2<STORAGE, POLY, PRIME> :: operator == (GF2<STORAGE, POLY, PRIME> b)
{
  return (value == b.value);
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: operator +(GF2<STORAGE, POLY, PRIME> b)
{
  return this->value ^ b.value;
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: operator +=(GF2<STORAGE, POLY, PRIME> b)
{
  return this->value ^= b.value;
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: operator -(GF2<STORAGE, POLY, PRIME> b)
{
  return *this + b;
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: operator -=(GF2<STORAGE, POLY, PRIME> b)
{
  return *this += b;
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: operator *(GF2<STORAGE, POLY, PRIME> b)
{
  if (*this == 0 || b == 0) return 0;

  int log_sum = GF2<STORAGE, POLY, PRIME>::log[value] + GF2<STORAGE, POLY, PRIME>::log[b.value];
  if (log_sum >= PRIME) log_sum -= PRIME;
  return GF2<STORAGE, POLY, PRIME>::ilog[log_sum];
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: operator /(GF2<STORAGE, POLY, PRIME> b)
{
  if (*this == 0 || b == 0) return 0;

  int log_sub = GF2<STORAGE, POLY, PRIME>::log[value] - GF2<STORAGE, POLY, PRIME>::log[b.value];
  if (log_sub < 0) log_sub += PRIME;
  return GF2<STORAGE, POLY, PRIME>::ilog[log_sub];
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
GF2<STORAGE, POLY, PRIME> GF2<STORAGE, POLY, PRIME> :: minv()
{
  return GF2<STORAGE, POLY, PRIME>::ilog[PRIME - GF2<STORAGE, POLY, PRIME>::log[value]];
}

template<typename STORAGE, unsigned int POLY, unsigned int PRIME>
std::ostream &operator<<(std::ostream &os, GF2<STORAGE, POLY, PRIME> const &m) {
      return os << static_cast<int>(m.value);
}

