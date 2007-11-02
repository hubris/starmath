#include <StarMath.h>
#include <iostream>

int
main()
{

  StarFloat2 a;    
  StarFloat3 b;
  StarFloat4 c;

  StarFloat3 d;

  StarFloat4x4 mat;
  StarFloat4x4 mat2;
  mat.toIdentity();
  mat *= 5.f;
  mat2.toIdentity();
  mat *= mat;
  mat /= 5;

  std::cerr << a << std::endl;
  std::cerr << b << std::endl;
  std::cerr << c << std::endl;
  std::cerr << mat << std::endl;

  return 0;
}
