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
#include <cmath>
#include <vector>
#include <array>
#include <complex>
#include <string>
#include <limits.h>

using namespace std;

const double INF = std::numeric_limits<double>::infinity();

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

Vec3D cross(Vec3D v1, Vec3D v2) { // cross product
  Vec3D result;
  result[0] = v1[1]*v2[2] - v1[2]*v2[1];
  result[1] = v1[2]*v2[0] - v1[0]*v2[2];
  result[2] = v1[0]*v2[1] - v1[1]*v2[0];
  return result;
}

const uint8_t STAR = 0;
const uint8_t PLANET = 1;
const uint8_t MOON = 2;
const uint8_t ASTEROID = 3;

struct CelestialBody {
  // static properties
  uint8_t type;
  string name;
  double radius, mass, period;
  Vec3D axis; // axis of rotation
  double temp; // only relevant for stars

  // dynamic properties
  Vec3D position, velocity, posOld, force;
}

struct Planet {
  // static properties
  string name;
  

#endif