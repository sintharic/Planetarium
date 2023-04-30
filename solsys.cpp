/*
MIT License

Copyright (c) 2023 Christian Mueller (https://github.com/sintharic)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "header.h"

void testVecMat() {
  Mat3x3 Mat = {2, 3, 0, 1, 1, 1, 0, 0, 2};
  Mat3x3 Solution = {-1,  3,  -1.5,  1,  -2,  1,  0,  0,  0.5};
  Mat3x3 Inv = inverse(Mat);

  assert(determinant(Mat) == -2);
  
  assert(Inv[0] == Solution[0]);
  assert(Inv[1] == Solution[1]);
  assert(Inv[2] == Solution[2]);
  assert(Inv[3] == Solution[3]);
  assert(Inv[4] == Solution[4]);
  assert(Inv[5] == Solution[5]);
  assert(Inv[6] == Solution[6]);
  assert(Inv[7] == Solution[7]);
  assert(Inv[8] == Solution[8]);

  Vec3D v1 = {2, 1, 5}, v2 = {7, 8, 10};
  Vec3D v3 = Mat*v1;

  assert(v3[0] == v2[0]);
  assert(v3[1] == v2[1]);
  assert(v3[2] == v2[2]);
};



int main() {
  testVecMat();
};