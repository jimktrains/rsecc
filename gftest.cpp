#include<iostream>
#include "gf.h"
#include "gfpoly.h"

int main()
{

  using GF2_256 = GF2<8>;
  GF2_256::init();

  auto a = GF2_256(5);
  auto b = GF2_256(135);
  auto c = GF2_256(49);
  auto d = GF2_256(7);

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

  auto y = GF2Poly<4, GF2_256>({GF2_256(1), GF2_256(2), GF2_256(3), GF2_256(9)});
  auto z = GF2Poly<4, GF2_256>({GF2_256(1), GF2_256(1), GF2_256(1), GF2_256(1)});
  std::cout << "y=" << y << std::endl;
  std::cout << "z=" << z << std::endl;
  std::cout << "y*z=" << (y*z) << std::endl;
  auto yzy = ((y*z)/y);
  std::cout << "(y*z)/y=" << yzy.first << " rem: " << yzy.second << std::endl;
  auto yzz = ((y*z)/z);
  std::cout << "(y*z)/z=" << yzz.first << " rem: " << yzz.second << std::endl;

  using GF2_16 = GF2<4>;
  GF2_16::init();

  auto f = GF2_16(3);
  auto g = GF2_16(7);

  std::cout << "f=" << f << std::endl;
  std::cout << "g=" << g << std::endl;
  std::cout << "f^(-1)=" << f.minv() << std::endl;
  std::cout << "f*f^(-1)=" << (f*f.minv()) << std::endl;
  std::cout << "f+f=" << (f+f) << std::endl;
  std::cout << "f+g=" << (f+g) << std::endl;
  std::cout << "f*g=" << (f*g) << std::endl;
  std::cout << "(f*g)/f=" << ((f*g)/f) << std::endl;
  std::cout << "(f*g)/g=" << ((f*g)/g) << std::endl;

  auto r = GF2Poly<4, GF2_16>({GF2_16(1), GF2_16(2), GF2_16(3), GF2_16(9)});
  auto s = GF2Poly<4, GF2_16>({GF2_16(1), GF2_16(1), GF2_16(1), GF2_16(1)});
  std::cout << "r=" << r << std::endl;
  std::cout << "s=" << s << std::endl;
  std::cout << "r*s=" << (r*s) << std::endl;
  auto rsr = ((r*s)/r);
  std::cout << "(r*s)/r=" << rsr.first << " rem: " << rsr.second << std::endl;
  auto rss = ((r*s)/s);
  std::cout << "(r*s)/s=" << rss.first << " rem: " << rss.second << std::endl;

  return 0;
}
