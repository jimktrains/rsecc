#include<iostream>
#include "gf.h"
#include "gfpoly.h"

int main()
{

  using GF2_255 =  GF2<uint8_t, 0x1d, 255>;
  GF2<uint8_t, 0x1d, 255>::init();

  auto a = GF2_255(5);
  auto b = GF2_255(135);
  auto c = GF2_255(49);
  auto d = GF2_255(7);

  std::cout << "a=" << a << std::endl;
  std::cout << "b=" << b << std::endl;
  std::cout << "c=" << c << std::endl;
  std::cout << "d=" << d << std::endl;
  std::cout << "a+a=" << (a+a) << std::endl;
  std::cout << "a*a=" << (a*a) << std::endl;
  std::cout << "b*b=" << (b*b) << std::endl;
  std::cout << "b^(-1)=" << b.minv() << std::endl;
  std::cout << "c*b=" << (c*b) << std::endl;
  std::cout << "a*b=" << (a*b) << std::endl;
  std::cout << "b*a=" << (b*a) << std::endl;
  std::cout << "(b*a)/a=" << ((b*a)/a) << std::endl;
  std::cout << "(b*a)/b=" << ((b*a)/b) << std::endl;
  std::cout << "a+b=" << (a+b) << std::endl;
  std::cout << "a^(-1)=" << a.minv() << std::endl;
  std::cout << "a*a^(-1)=" << (a*a.minv()) << std::endl;
  std::cout << "b^(-1)=" << b.minv() << std::endl;
  std::cout << "c/d=" << (c/d) << std::endl;

  auto y = GF2Poly<4, GF2_255>({GF2_255(1), GF2_255(2), GF2_255(3), GF2_255(4)});
  auto z = GF2Poly<4, GF2_255>({GF2_255(1),GF2_255(1),GF2_255(1),GF2_255(1)});
  std::cout << "y=" << y << std::endl;
  std::cout << "z=" << z << std::endl;
  std::cout << "y*z=" << (y*z) << std::endl;
  auto yzy = ((y*z)/y);
  auto yzz = ((y*z)/z);
  std::cout << "(y*z)/y=" << yzy.first << " rem: " << yzy.second << std::endl;
  std::cout << "(y*z)/z=" << yzz.first << " rem: " << yzz.second << std::endl;
  return 0;
}
