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

#ifndef HEADER_H
#define HEADER_H
//endif at EOF

#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include <array>
#include <complex>
#include <string>
#include <limits.h>

using namespace std;

const double INF = 1e256;//std::numeric_limits<double>::infinity();

typedef std::complex<double> Complex;

template <typename T> int sign(T val) {
  return (T(0) < val) - (val < T(0));
}

void terminate(string msg) {
  cerr << msg << endl;
  exit(1);
}



// ----- Vec3D type ----- //

typedef array<double, 3> Vec3D;
typedef array<double, 9> Mat3x3;

Vec3D operator+(Vec3D v1, Vec3D v2) {
  Vec3D result;
  for (int iDim = 0; iDim < 3; ++iDim) result[iDim] = v1[iDim] + v2[iDim];
  return result;
}

Vec3D operator-(Vec3D v1, Vec3D v2) {
  Vec3D result;
  for (int iDim = 0; iDim < 3; ++iDim) result[iDim] = v1[iDim] - v2[iDim];
  return result;
}

Vec3D operator*(double val, Vec3D vec) {
  Vec3D result;
  for (int iDim = 0; iDim < 3; ++iDim) result[iDim] = val*vec[iDim];
  return result;
}

Vec3D operator/(Vec3D vec, double val) {
  Vec3D result;
  for (int iDim = 0; iDim < 3; ++iDim) result[iDim] = vec[iDim]/val;
  return result;
}

double operator*(Vec3D v1, Vec3D v2) { // scalar product
  return (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

Vec3D cross(Vec3D& v1, Vec3D& v2) { // cross product
  Vec3D result;
  result[0] = v1[1]*v2[2] - v1[2]*v2[1];
  result[1] = v1[2]*v2[0] - v1[0]*v2[2];
  result[2] = v1[0]*v2[1] - v1[1]*v2[0];
  return result;
};

double abs2(Vec3D& v) {
  double result = 0;
  for (int idx = 0; idx < 3; ++idx) result += v[idx]*v[idx];
  return result;
};

double abs(Vec3D& v) {
  double result = 0;
  for (int idx = 0; idx < 3; ++idx) result += v[idx]*v[idx];
  return sqrt(result);
};

Vec3D operator*(Mat3x3 M, Vec3D v) {
  Vec3D result = {0,0,0};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      result[i] += M[3*i+j]*v[j];
    }
  }
  return result;
};

Mat3x3 operator*(Mat3x3 M1, Mat3x3 M2) {
  Mat3x3 R;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      R[3*i+j] = 0;
      for (int k = 0; k < 3; ++k) {
        R[3*i+j] += M1[3*i+k] * M2[3*k+j];
      }
    }
  }
  return R;
};

Mat3x3 operator*(double val, Mat3x3 M) {
  Mat3x3 R;
  for (int i = 0; i < 9; ++i) R[i] = val*M[i];
  return R;
}

Mat3x3 operator/(Mat3x3 M, double val) {
  Mat3x3 R;
  for (int i = 0; i < 9; ++i) R[i] = M[i]/val;
  return R;
}

double determinant(Mat3x3& M) {
  return M[0]*(M[4]*M[8]-M[5]*M[7]) - M[1]*(M[3]*M[8]-M[5]*M[6]) + M[2]*(M[3]*M[7]-M[4]*M[6]);
};

Mat3x3 inverse(Mat3x3& M) {
  Mat3x3 R;
  double det = determinant(M);
  R[0] = M[4]*M[8] - M[5]*M[7];
  R[1] = M[2]*M[7] - M[1]*M[8];
  R[2] = M[1]*M[5] - M[2]*M[4];
  R[3] = M[5]*M[6] - M[3]*M[8];
  R[4] = M[0]*M[8] - M[2]*M[6];
  R[5] = M[2]*M[3] - M[0]*M[5];
  R[6] = M[3]*M[7] - M[4]*M[6];
  R[7] = M[1]*M[6] - M[0]*M[7];
  R[8] = M[0]*M[4] - M[1]*M[3];
  return R/det;
};

Mat3x3 eye() {
  Mat3x3 R;
  R[0] = R[4] = R[8] = 1;
  R[1] = R[2] = R[3] = R[5] = R[6] = R[7] = 0;
  return R;
};

void print(Mat3x3 M) {
  for (int iDim = 0; iDim < 3; ++iDim) {
    cout << "|" << M[3*iDim];
    for (int jDim = 1; jDim < 3; ++jDim) {
      cout << "\t" << M[3*iDim+jDim];
    }
    cout << "|\n";
  }
};

const uint8_t STAR = 0;
const uint8_t PLANET = 1;
const uint8_t MOON = 2;
const uint8_t ASTEROID = 3;

struct CelestialBody {
  // static properties
  uint8_t type;
  string name;
  double radius, mass;
  double period; // period of rotation
  Vec3D axis; // axis of rotation
  double temp; // only relevant for stars

  // dynamic properties
  Vec3D position, velocity, posOld, force;
};

struct Planet {
  // static properties
  string name;
};
  

#endif