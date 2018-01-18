#include<utility>

template<int N, typename GF>
class GF2Poly
{
  public:
    GF poly[N+1];

    GF2Poly(GF poly[N+1]) : poly(poly) {}
    GF2Poly(std::initializer_list<GF> c) {
      std::copy(c.begin(), c.end(), poly);
    }
    GF2Poly()
    {
      for (int i = 0; i < N+1; i++)
      {
        poly[i] = 0;
      }
    }

    template<int M>
    GF2Poly<N + M, GF> operator *(GF2Poly<M, GF> b)
    {
      GF2Poly<N + M, GF> accum;
      for (int i = 0; i < N+1; i++)
      {
        for (int j = 0; j < M+1; j++)
        {
          accum.poly[i + j] += poly[i] * b.poly[j];
        }
      }
      return accum;
    }

    GF2Poly<N, GF> operator *(GF b)
    {
      GF2Poly<N, GF> accum = *this;
      for (int i = 0; i < N+1; i++)
      {
          accum.poly[i] = poly[i] * b;
      }
      return accum;
    }

    template<int M>
    GF2Poly<N, GF> operator +(GF2Poly<M, GF> b)
    {
      GF2Poly<N, GF> accum = *this;
      for (int i = 0; i < N+1; i++)
      {
        if ( i < (M+1) )
        {
          accum.poly[i] += b.poly[i];
        }
      }
      return accum;
    }

    template<int M>
    GF2Poly<N, GF> operator -(GF2Poly<M, GF> b)
    {
      GF2Poly<N, GF> accum = *this;
      for (int i = 0; i < N+1; i++)
      {
        if ( i < (M+1) )
        {
          accum.poly[i] -= b.poly[i];
        }
      }
      return accum;
    }
    template<int M>
    GF2Poly<N, GF> operator -=(GF2Poly<M, GF> b)
    {
      for (int i = 0; i < N+1; i++)
      {
        if ( i < (M+1) )
        {
         poly[i] -= b.poly[i];
        }
      }
      return *this;
    }

    int order()
    {
      for (int i = N+1; i > 0; i--)
      {
        if ( !(poly[i-1] == 0))
        {
          return i-1;
        }
      }
      return -1;
    }

    template<int M>
    std::pair<GF2Poly<N, GF>, GF2Poly<N, GF>> operator /(GF2Poly<M, GF> b)
    {
      GF2Poly<N, GF> accum;
      GF2Poly<N, GF> remainder = *this;

      int order_b = b.order();

      int order_remainder;
      int order_res;
      for (int i = 0; i < order_b + 1; i++)
      {
        order_remainder = remainder.order();
        order_res = order_remainder - order_b;
        if (order_res > -1){}

        accum.poly[order_res] = remainder.poly[order_remainder] / b.poly[order_b];

        auto x = b * accum.poly[order_res];
        for (int j = order_b + 1; j > 0; j--)
        {
           remainder.poly[j + order_res - 1] -= x.poly[j - 1];
        }
      }

      return std::make_pair(accum, remainder);
    }
};

template<int N, typename GF>
std::ostream &operator<<(std::ostream &os, GF2Poly<N, GF> const &m)
{
  for (int i = N + 1; i > 0; i--)
  {
    os << m.poly[i - 1];
    os << " ";
  }
  return os;
}
