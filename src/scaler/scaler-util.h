#ifndef SCALER_UTIL_H_
#define SCALER_UTIL_H_
/*****************************************************************************
* This file is part of Kvazaar HEVC encoder.
*
* Copyright (C) 2013-2015 Tampere University of Technology and others (see
* COPYING file).
*
* Kvazaar is free software: you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License as published by the
* Free Software Foundation; either version 2.1 of the License, or (at your
* option) any later version.
*
* Kvazaar is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with Kvazaar.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

/*  Define functions/constants shared by scaler and scaler-avx2  */

#define SCALER_MIN(x,y) (((x) < (y)) ? (x) : (y))
#define SCALER_MAX(x,y) (((x) > (y)) ? (x) : (y))
#define SCALER_CLIP(val, mn, mx) (SCALER_MIN(mx,SCALER_MAX(mn,val)))

#define SCALER_SHIFT(val,shift) (((shift) < 0) ? ((val)>>(-(shift))) : ((val)<<(shift)))
#define SCALER_ROUND_SHIFT(val,shift) (((shift) < 0) ? SCALER_SHIFT((val)+(1<<(-(shift)))-1,shift) : SCALER_SHIFT(val, shift))

#define SCALER_SHIFT_CONST 16 //TODO: Make dependant on stuff?
#define SCALER_UNITY_SCALE_CONST (1<<SCALER_SHIFT_CONST)

#define getFilterCoeff(filter, stride, phase, ind) ((filter)[(ind)+(phase)*(stride)])

//Used for clipping values
int kvz_clip_scaler(int val, int min, int max);

//Define filters for scaling operations
//Values from SHM
static const int downFilter[8][16][12] = {
  // ratio <= 20/19
  {
    { 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 2, -6, 127, 7, -2, 0, 0, 0, 0 },
    { 0, 0, 0, 3, -12, 125, 16, -5, 1, 0, 0, 0 },
    { 0, 0, 0, 4, -16, 120, 26, -7, 1, 0, 0, 0 },
    { 0, 0, 0, 5, -18, 114, 36, -10, 1, 0, 0, 0 },
    { 0, 0, 0, 5, -20, 107, 46, -12, 2, 0, 0, 0 },
    { 0, 0, 0, 5, -21, 99, 57, -15, 3, 0, 0, 0 },
    { 0, 0, 0, 5, -20, 89, 68, -18, 4, 0, 0, 0 },
    { 0, 0, 0, 4, -19, 79, 79, -19, 4, 0, 0, 0 },
    { 0, 0, 0, 4, -18, 68, 89, -20, 5, 0, 0, 0 },
    { 0, 0, 0, 3, -15, 57, 99, -21, 5, 0, 0, 0 },
    { 0, 0, 0, 2, -12, 46, 107, -20, 5, 0, 0, 0 },
    { 0, 0, 0, 1, -10, 36, 114, -18, 5, 0, 0, 0 },
    { 0, 0, 0, 1, -7, 26, 120, -16, 4, 0, 0, 0 },
    { 0, 0, 0, 1, -5, 16, 125, -12, 3, 0, 0, 0 },
    { 0, 0, 0, 0, -2, 7, 127, -6, 2, 0, 0, 0 }
  },
  // 20/19 < ratio <= 5/4
  {
    { 0, 2, 0, -14, 33, 86, 33, -14, 0, 2, 0, 0 },
    { 0, 1, 1, -14, 29, 85, 38, -13, -1, 2, 0, 0 },
    { 0, 1, 2, -14, 24, 84, 43, -12, -2, 2, 0, 0 },
    { 0, 1, 2, -13, 19, 83, 48, -11, -3, 2, 0, 0 },
    { 0, 0, 3, -13, 15, 81, 53, -10, -4, 3, 0, 0 },
    { 0, 0, 3, -12, 11, 79, 57, -8, -5, 3, 0, 0 },
    { 0, 0, 3, -11, 7, 76, 62, -5, -7, 3, 0, 0 },
    { 0, 0, 3, -10, 3, 73, 65, -2, -7, 3, 0, 0 },
    { 0, 0, 3, -9, 0, 70, 70, 0, -9, 3, 0, 0 },
    { 0, 0, 3, -7, -2, 65, 73, 3, -10, 3, 0, 0 },
    { 0, 0, 3, -7, -5, 62, 76, 7, -11, 3, 0, 0 },
    { 0, 0, 3, -5, -8, 57, 79, 11, -12, 3, 0, 0 },
    { 0, 0, 3, -4, -10, 53, 81, 15, -13, 3, 0, 0 },
    { 0, 0, 2, -3, -11, 48, 83, 19, -13, 2, 1, 0 },
    { 0, 0, 2, -2, -12, 43, 84, 24, -14, 2, 1, 0 },
    { 0, 0, 2, -1, -13, 38, 85, 29, -14, 1, 1, 0 }
  },
  // 5/4 < ratio <= 5/3
  {
    { 0, 5, -6, -10, 37, 76, 37, -10, -6, 5, 0, 0 },
    { 0, 5, -4, -11, 33, 76, 40, -9, -7, 5, 0, 0 },
    { -1, 5, -3, -12, 29, 75, 45, -7, -8, 5, 0, 0 },
    { -1, 4, -2, -13, 25, 75, 48, -5, -9, 5, 1, 0 },
    { -1, 4, -1, -13, 22, 73, 52, -3, -10, 4, 1, 0 },
    { -1, 4, 0, -13, 18, 72, 55, -1, -11, 4, 2, -1 },
    { -1, 4, 1, -13, 14, 70, 59, 2, -12, 3, 2, -1 },
    { -1, 3, 1, -13, 11, 68, 62, 5, -12, 3, 2, -1 },
    { -1, 3, 2, -13, 8, 65, 65, 8, -13, 2, 3, -1 },
    { -1, 2, 3, -12, 5, 62, 68, 11, -13, 1, 3, -1 },
    { -1, 2, 3, -12, 2, 59, 70, 14, -13, 1, 4, -1 },
    { -1, 2, 4, -11, -1, 55, 72, 18, -13, 0, 4, -1 },
    { 0, 1, 4, -10, -3, 52, 73, 22, -13, -1, 4, -1 },
    { 0, 1, 5, -9, -5, 48, 75, 25, -13, -2, 4, -1 },
    { 0, 0, 5, -8, -7, 45, 75, 29, -12, -3, 5, -1 },
    { 0, 0, 5, -7, -9, 40, 76, 33, -11, -4, 5, 0 },
  },
  // 5/3 < ratio <= 2
  {
    { 2, -3, -9, 6, 39, 58, 39, 6, -9, -3, 2, 0 },
    { 2, -3, -9, 4, 38, 58, 43, 7, -9, -4, 1, 0 },
    { 2, -2, -9, 2, 35, 58, 44, 9, -8, -4, 1, 0 },
    { 1, -2, -9, 1, 34, 58, 46, 11, -8, -5, 1, 0 },
    { 1, -1, -8, -1, 31, 57, 47, 13, -7, -5, 1, 0 },
    { 1, -1, -8, -2, 29, 56, 49, 15, -7, -6, 1, 1 },
    { 1, 0, -8, -3, 26, 55, 51, 17, -7, -6, 1, 1 },
    { 1, 0, -7, -4, 24, 54, 52, 19, -6, -7, 1, 1 },
    { 1, 0, -7, -5, 22, 53, 53, 22, -5, -7, 0, 1 },
    { 1, 1, -7, -6, 19, 52, 54, 24, -4, -7, 0, 1 },
    { 1, 1, -6, -7, 17, 51, 55, 26, -3, -8, 0, 1 },
    { 1, 1, -6, -7, 15, 49, 56, 29, -2, -8, -1, 1 },
    { 0, 1, -5, -7, 13, 47, 57, 31, -1, -8, -1, 1 },
    { 0, 1, -5, -8, 11, 46, 58, 34, 1, -9, -2, 1 },
    { 0, 1, -4, -8, 9, 44, 58, 35, 2, -9, -2, 2 },
    { 0, 1, -4, -9, 7, 43, 58, 38, 4, -9, -3, 2 },
  },
  // 2 < ratio <= 5/2
  {
    { -2, -7, 0, 17, 35, 43, 35, 17, 0, -7, -5, 2 },
    { -2, -7, -1, 16, 34, 43, 36, 18, 1, -7, -5, 2 },
    { -1, -7, -1, 14, 33, 43, 36, 19, 1, -6, -5, 2 },
    { -1, -7, -2, 13, 32, 42, 37, 20, 3, -6, -5, 2 },
    { 0, -7, -3, 12, 31, 42, 38, 21, 3, -6, -5, 2 },
    { 0, -7, -3, 11, 30, 42, 39, 23, 4, -6, -6, 1 },
    { 0, -7, -4, 10, 29, 42, 40, 24, 5, -6, -6, 1 },
    { 1, -7, -4, 9, 27, 41, 40, 25, 6, -5, -6, 1 },
    { 1, -6, -5, 7, 26, 41, 41, 26, 7, -5, -6, 1 },
    { 1, -6, -5, 6, 25, 40, 41, 27, 9, -4, -7, 1 },
    { 1, -6, -6, 5, 24, 40, 42, 29, 10, -4, -7, 0 },
    { 1, -6, -6, 4, 23, 39, 42, 30, 11, -3, -7, 0 },
    { 2, -5, -6, 3, 21, 38, 42, 31, 12, -3, -7, 0 },
    { 2, -5, -6, 3, 20, 37, 42, 32, 13, -2, -7, -1 },
    { 2, -5, -6, 1, 19, 36, 43, 33, 14, -1, -7, -1 },
    { 2, -5, -7, 1, 18, 36, 43, 34, 16, -1, -7, -2 }
  },
  // 5/2 < ratio <= 20/7
  {
    { -6, -3, 5, 19, 31, 36, 31, 19, 5, -3, -6, 0 },
    { -6, -4, 4, 18, 31, 37, 32, 20, 6, -3, -6, -1 },
    { -6, -4, 4, 17, 30, 36, 33, 21, 7, -3, -6, -1 },
    { -5, -5, 3, 16, 30, 36, 33, 22, 8, -2, -6, -2 },
    { -5, -5, 2, 15, 29, 36, 34, 23, 9, -2, -6, -2 },
    { -5, -5, 2, 15, 28, 36, 34, 24, 10, -2, -6, -3 },
    { -4, -5, 1, 14, 27, 36, 35, 24, 10, -1, -6, -3 },
    { -4, -5, 0, 13, 26, 35, 35, 25, 11, 0, -5, -3 },
    { -4, -6, 0, 12, 26, 36, 36, 26, 12, 0, -6, -4 },
    { -3, -5, 0, 11, 25, 35, 35, 26, 13, 0, -5, -4 },
    { -3, -6, -1, 10, 24, 35, 36, 27, 14, 1, -5, -4 },
    { -3, -6, -2, 10, 24, 34, 36, 28, 15, 2, -5, -5 },
    { -2, -6, -2, 9, 23, 34, 36, 29, 15, 2, -5, -5 },
    { -2, -6, -2, 8, 22, 33, 36, 30, 16, 3, -5, -5 },
    { -1, -6, -3, 7, 21, 33, 36, 30, 17, 4, -4, -6 },
    { -1, -6, -3, 6, 20, 32, 37, 31, 18, 4, -4, -6 }
  },
  // 20/7 < ratio <= 15/4
  {
    { -9, 0, 9, 20, 28, 32, 28, 20, 9, 0, -9, 0 },
    { -9, 0, 8, 19, 28, 32, 29, 20, 10, 0, -4, -5 },
    { -9, -1, 8, 18, 28, 32, 29, 21, 10, 1, -4, -5 },
    { -9, -1, 7, 18, 27, 32, 30, 22, 11, 1, -4, -6 },
    { -8, -2, 6, 17, 27, 32, 30, 22, 12, 2, -4, -6 },
    { -8, -2, 6, 16, 26, 32, 31, 23, 12, 2, -4, -6 },
    { -8, -2, 5, 16, 26, 31, 31, 23, 13, 3, -3, -7 },
    { -8, -3, 5, 15, 25, 31, 31, 24, 14, 4, -3, -7 },
    { -7, -3, 4, 14, 25, 31, 31, 25, 14, 4, -3, -7 },
    { -7, -3, 4, 14, 24, 31, 31, 25, 15, 5, -3, -8 },
    { -7, -3, 3, 13, 23, 31, 31, 26, 16, 5, -2, -8 },
    { -6, -4, 2, 12, 23, 31, 32, 26, 16, 6, -2, -8 },
    { -6, -4, 2, 12, 22, 30, 32, 27, 17, 6, -2, -8 },
    { -6, -4, 1, 11, 22, 30, 32, 27, 18, 7, -1, -9 },
    { -5, -4, 1, 10, 21, 29, 32, 28, 18, 8, -1, -9 },
    { -5, -4, 0, 10, 20, 29, 32, 28, 19, 8, 0, -9 }
  },
  // ratio > 15/4
  {
    { -8, 7, 13, 18, 22, 24, 22, 18, 13, 7, 2, -10 },
    { -8, 7, 13, 18, 22, 23, 22, 19, 13, 7, 2, -10 },
    { -8, 6, 12, 18, 22, 23, 22, 19, 14, 8, 2, -10 },
    { -9, 6, 12, 17, 22, 23, 23, 19, 14, 8, 3, -10 },
    { -9, 6, 12, 17, 21, 23, 23, 19, 14, 9, 3, -10 },
    { -9, 5, 11, 17, 21, 23, 23, 20, 15, 9, 3, -10 },
    { -9, 5, 11, 16, 21, 23, 23, 20, 15, 9, 4, -10 },
    { -9, 5, 10, 16, 21, 23, 23, 20, 15, 10, 4, -10 },
    { -10, 5, 10, 16, 20, 23, 23, 20, 16, 10, 5, -10 },
    { -10, 4, 10, 15, 20, 23, 23, 21, 16, 10, 5, -9 },
    { -10, 4, 9, 15, 20, 23, 23, 21, 16, 11, 5, -9 },
    { -10, 3, 9, 15, 20, 23, 23, 21, 17, 11, 5, -9 },
    { -10, 3, 9, 14, 19, 23, 23, 21, 17, 12, 6, -9 },
    { -10, 3, 8, 14, 19, 23, 23, 22, 17, 12, 6, -9 },
    { -10, 2, 8, 14, 19, 22, 23, 22, 18, 12, 6, -8 },
    { -10, 2, 7, 13, 19, 22, 23, 22, 18, 13, 7, -8 }
  }
};

static const int lumaUpFilter[16][8] = {
  { 0, 0, 0, 64, 0, 0, 0, 0 },
  { 0, 1, -3, 63, 4, -2, 1, 0 },
  { -1, 2, -5, 62, 8, -3, 1, 0 },
  { -1, 3, -8, 60, 13, -4, 1, 0 },
  { -1, 4, -10, 58, 17, -5, 1, 0 },
  { -1, 4, -11, 52, 26, -8, 3, -1 },
  { -1, 3, -9, 47, 31, -10, 4, -1 },
  { -1, 4, -11, 45, 34, -10, 4, -1 },
  { -1, 4, -11, 40, 40, -11, 4, -1 },
  { -1, 4, -10, 34, 45, -11, 4, -1 },
  { -1, 4, -10, 31, 47, -9, 3, -1 },
  { -1, 3, -8, 26, 52, -11, 4, -1 },
  { 0, 1, -5, 17, 58, -10, 4, -1 },
  { 0, 1, -4, 13, 60, -8, 3, -1 },
  { 0, 1, -3, 8, 62, -5, 2, -1 },
  { 0, 1, -2, 4, 63, -3, 1, 0 }
};

static const int chromaUpFilter[16][4] = {
  { 0, 64, 0, 0 },
  { -2, 62, 4, 0 },
  { -2, 58, 10, -2 },
  { -4, 56, 14, -2 },
  { -4, 54, 16, -2 },
  { -6, 52, 20, -2 },
  { -6, 46, 28, -4 },
  { -4, 42, 30, -4 },
  { -4, 36, 36, -4 },
  { -4, 30, 42, -4 },
  { -4, 28, 46, -6 },
  { -2, 20, 52, -6 },
  { -2, 16, 54, -4 },
  { -2, 14, 56, -4 },
  { -2, 10, 58, -2 },
  { 0, 4, 62, -2 }
};


////////////////////////////////////
//___________32-bit filters____________//
static const int downFilter1D[8][16 * 12] = {
  // ratio <= 20/19
  {
    0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, -6, 127, 7, -2, 0, 0, 0, 0,
    0, 0, 0, 3, -12, 125, 16, -5, 1, 0, 0, 0,
    0, 0, 0, 4, -16, 120, 26, -7, 1, 0, 0, 0,
    0, 0, 0, 5, -18, 114, 36, -10, 1, 0, 0, 0,
    0, 0, 0, 5, -20, 107, 46, -12, 2, 0, 0, 0,
    0, 0, 0, 5, -21, 99, 57, -15, 3, 0, 0, 0,
    0, 0, 0, 5, -20, 89, 68, -18, 4, 0, 0, 0,
    0, 0, 0, 4, -19, 79, 79, -19, 4, 0, 0, 0,
    0, 0, 0, 4, -18, 68, 89, -20, 5, 0, 0, 0,
    0, 0, 0, 3, -15, 57, 99, -21, 5, 0, 0, 0,
    0, 0, 0, 2, -12, 46, 107, -20, 5, 0, 0, 0,
    0, 0, 0, 1, -10, 36, 114, -18, 5, 0, 0, 0,
    0, 0, 0, 1, -7, 26, 120, -16, 4, 0, 0, 0,
    0, 0, 0, 1, -5, 16, 125, -12, 3, 0, 0, 0,
    0, 0, 0, 0, -2, 7, 127, -6, 2, 0, 0, 0,
  },
  // 20/19 < ratio <= 5/4
  {
    0, 2, 0, -14, 33, 86, 33, -14, 0, 2, 0, 0,
    0, 1, 1, -14, 29, 85, 38, -13, -1, 2, 0, 0,
    0, 1, 2, -14, 24, 84, 43, -12, -2, 2, 0, 0,
    0, 1, 2, -13, 19, 83, 48, -11, -3, 2, 0, 0,
    0, 0, 3, -13, 15, 81, 53, -10, -4, 3, 0, 0,
    0, 0, 3, -12, 11, 79, 57, -8, -5, 3, 0, 0,
    0, 0, 3, -11, 7, 76, 62, -5, -7, 3, 0, 0,
    0, 0, 3, -10, 3, 73, 65, -2, -7, 3, 0, 0,
    0, 0, 3, -9, 0, 70, 70, 0, -9, 3, 0, 0,
    0, 0, 3, -7, -2, 65, 73, 3, -10, 3, 0, 0,
    0, 0, 3, -7, -5, 62, 76, 7, -11, 3, 0, 0,
    0, 0, 3, -5, -8, 57, 79, 11, -12, 3, 0, 0,
    0, 0, 3, -4, -10, 53, 81, 15, -13, 3, 0, 0,
    0, 0, 2, -3, -11, 48, 83, 19, -13, 2, 1, 0,
    0, 0, 2, -2, -12, 43, 84, 24, -14, 2, 1, 0,
    0, 0, 2, -1, -13, 38, 85, 29, -14, 1, 1, 0,
  },
  // 5/4 < ratio <= 5/3
  {
    0, 5, -6, -10, 37, 76, 37, -10, -6, 5, 0, 0,
    0, 5, -4, -11, 33, 76, 40, -9, -7, 5, 0, 0,
    -1, 5, -3, -12, 29, 75, 45, -7, -8, 5, 0, 0,
    -1, 4, -2, -13, 25, 75, 48, -5, -9, 5, 1, 0,
    -1, 4, -1, -13, 22, 73, 52, -3, -10, 4, 1, 0,
    -1, 4, 0, -13, 18, 72, 55, -1, -11, 4, 2, -1,
    -1, 4, 1, -13, 14, 70, 59, 2, -12, 3, 2, -1,
    -1, 3, 1, -13, 11, 68, 62, 5, -12, 3, 2, -1,
    -1, 3, 2, -13, 8, 65, 65, 8, -13, 2, 3, -1,
    -1, 2, 3, -12, 5, 62, 68, 11, -13, 1, 3, -1,
    -1, 2, 3, -12, 2, 59, 70, 14, -13, 1, 4, -1,
    -1, 2, 4, -11, -1, 55, 72, 18, -13, 0, 4, -1,
    0, 1, 4, -10, -3, 52, 73, 22, -13, -1, 4, -1,
    0, 1, 5, -9, -5, 48, 75, 25, -13, -2, 4, -1,
    0, 0, 5, -8, -7, 45, 75, 29, -12, -3, 5, -1,
    0, 0, 5, -7, -9, 40, 76, 33, -11, -4, 5, 0,
  },
  // 5/3 < ratio <= 2
  {
    2, -3, -9, 6, 39, 58, 39, 6, -9, -3, 2, 0,
    2, -3, -9, 4, 38, 58, 43, 7, -9, -4, 1, 0,
    2, -2, -9, 2, 35, 58, 44, 9, -8, -4, 1, 0,
    1, -2, -9, 1, 34, 58, 46, 11, -8, -5, 1, 0,
    1, -1, -8, -1, 31, 57, 47, 13, -7, -5, 1, 0,
    1, -1, -8, -2, 29, 56, 49, 15, -7, -6, 1, 1,
    1, 0, -8, -3, 26, 55, 51, 17, -7, -6, 1, 1,
    1, 0, -7, -4, 24, 54, 52, 19, -6, -7, 1, 1,
    1, 0, -7, -5, 22, 53, 53, 22, -5, -7, 0, 1,
    1, 1, -7, -6, 19, 52, 54, 24, -4, -7, 0, 1,
    1, 1, -6, -7, 17, 51, 55, 26, -3, -8, 0, 1,
    1, 1, -6, -7, 15, 49, 56, 29, -2, -8, -1, 1,
    0, 1, -5, -7, 13, 47, 57, 31, -1, -8, -1, 1,
    0, 1, -5, -8, 11, 46, 58, 34, 1, -9, -2, 1,
    0, 1, -4, -8, 9, 44, 58, 35, 2, -9, -2, 2,
    0, 1, -4, -9, 7, 43, 58, 38, 4, -9, -3, 2,
  },
  // 2 < ratio <= 5/2
  {
    -2, -7, 0, 17, 35, 43, 35, 17, 0, -7, -5, 2,
    -2, -7, -1, 16, 34, 43, 36, 18, 1, -7, -5, 2,
    -1, -7, -1, 14, 33, 43, 36, 19, 1, -6, -5, 2,
    -1, -7, -2, 13, 32, 42, 37, 20, 3, -6, -5, 2,
    0, -7, -3, 12, 31, 42, 38, 21, 3, -6, -5, 2,
    0, -7, -3, 11, 30, 42, 39, 23, 4, -6, -6, 1,
    0, -7, -4, 10, 29, 42, 40, 24, 5, -6, -6, 1,
    1, -7, -4, 9, 27, 41, 40, 25, 6, -5, -6, 1,
    1, -6, -5, 7, 26, 41, 41, 26, 7, -5, -6, 1,
    1, -6, -5, 6, 25, 40, 41, 27, 9, -4, -7, 1,
    1, -6, -6, 5, 24, 40, 42, 29, 10, -4, -7, 0,
    1, -6, -6, 4, 23, 39, 42, 30, 11, -3, -7, 0,
    2, -5, -6, 3, 21, 38, 42, 31, 12, -3, -7, 0,
    2, -5, -6, 3, 20, 37, 42, 32, 13, -2, -7, -1,
    2, -5, -6, 1, 19, 36, 43, 33, 14, -1, -7, -1,
    2, -5, -7, 1, 18, 36, 43, 34, 16, -1, -7, -2,
  },
  // 5/2 < ratio <= 20/7
  {
    -6, -3, 5, 19, 31, 36, 31, 19, 5, -3, -6, 0,
    -6, -4, 4, 18, 31, 37, 32, 20, 6, -3, -6, -1,
    -6, -4, 4, 17, 30, 36, 33, 21, 7, -3, -6, -1,
    -5, -5, 3, 16, 30, 36, 33, 22, 8, -2, -6, -2,
    -5, -5, 2, 15, 29, 36, 34, 23, 9, -2, -6, -2,
    -5, -5, 2, 15, 28, 36, 34, 24, 10, -2, -6, -3,
    -4, -5, 1, 14, 27, 36, 35, 24, 10, -1, -6, -3,
    -4, -5, 0, 13, 26, 35, 35, 25, 11, 0, -5, -3,
    -4, -6, 0, 12, 26, 36, 36, 26, 12, 0, -6, -4,
    -3, -5, 0, 11, 25, 35, 35, 26, 13, 0, -5, -4,
    -3, -6, -1, 10, 24, 35, 36, 27, 14, 1, -5, -4,
    -3, -6, -2, 10, 24, 34, 36, 28, 15, 2, -5, -5,
    -2, -6, -2, 9, 23, 34, 36, 29, 15, 2, -5, -5,
    -2, -6, -2, 8, 22, 33, 36, 30, 16, 3, -5, -5,
    -1, -6, -3, 7, 21, 33, 36, 30, 17, 4, -4, -6,
    -1, -6, -3, 6, 20, 32, 37, 31, 18, 4, -4, -6,
  },
  // 20/7 < ratio <= 15/4
  {
    -9, 0, 9, 20, 28, 32, 28, 20, 9, 0, -9, 0,
    -9, 0, 8, 19, 28, 32, 29, 20, 10, 0, -4, -5,
    -9, -1, 8, 18, 28, 32, 29, 21, 10, 1, -4, -5,
    -9, -1, 7, 18, 27, 32, 30, 22, 11, 1, -4, -6,
    -8, -2, 6, 17, 27, 32, 30, 22, 12, 2, -4, -6,
    -8, -2, 6, 16, 26, 32, 31, 23, 12, 2, -4, -6,
    -8, -2, 5, 16, 26, 31, 31, 23, 13, 3, -3, -7,
    -8, -3, 5, 15, 25, 31, 31, 24, 14, 4, -3, -7,
    -7, -3, 4, 14, 25, 31, 31, 25, 14, 4, -3, -7,
    -7, -3, 4, 14, 24, 31, 31, 25, 15, 5, -3, -8,
    -7, -3, 3, 13, 23, 31, 31, 26, 16, 5, -2, -8,
    -6, -4, 2, 12, 23, 31, 32, 26, 16, 6, -2, -8,
    -6, -4, 2, 12, 22, 30, 32, 27, 17, 6, -2, -8,
    -6, -4, 1, 11, 22, 30, 32, 27, 18, 7, -1, -9,
    -5, -4, 1, 10, 21, 29, 32, 28, 18, 8, -1, -9,
    -5, -4, 0, 10, 20, 29, 32, 28, 19, 8, 0, -9,
  },
  // ratio > 15/4
  {
    -8, 7, 13, 18, 22, 24, 22, 18, 13, 7, 2, -10,
    -8, 7, 13, 18, 22, 23, 22, 19, 13, 7, 2, -10,
    -8, 6, 12, 18, 22, 23, 22, 19, 14, 8, 2, -10,
    -9, 6, 12, 17, 22, 23, 23, 19, 14, 8, 3, -10,
    -9, 6, 12, 17, 21, 23, 23, 19, 14, 9, 3, -10,
    -9, 5, 11, 17, 21, 23, 23, 20, 15, 9, 3, -10,
    -9, 5, 11, 16, 21, 23, 23, 20, 15, 9, 4, -10,
    -9, 5, 10, 16, 21, 23, 23, 20, 15, 10, 4, -10,
    -10, 5, 10, 16, 20, 23, 23, 20, 16, 10, 5, -10,
    -10, 4, 10, 15, 20, 23, 23, 21, 16, 10, 5, -9,
    -10, 4, 9, 15, 20, 23, 23, 21, 16, 11, 5, -9,
    -10, 3, 9, 15, 20, 23, 23, 21, 17, 11, 5, -9,
    -10, 3, 9, 14, 19, 23, 23, 21, 17, 12, 6, -9,
    -10, 3, 8, 14, 19, 23, 23, 22, 17, 12, 6, -9,
    -10, 2, 8, 14, 19, 22, 23, 22, 18, 12, 6, -8,
    -10, 2, 7, 13, 19, 22, 23, 22, 18, 13, 7, -8,
  }
};

static const int lumaUpFilter1D[16 * 8] = {
  0, 0, 0, 64, 0, 0, 0, 0,
  0, 1, -3, 63, 4, -2, 1, 0,
  -1, 2, -5, 62, 8, -3, 1, 0,
  -1, 3, -8, 60, 13, -4, 1, 0,
  -1, 4, -10, 58, 17, -5, 1, 0,
  -1, 4, -11, 52, 26, -8, 3, -1,
  -1, 3, -9, 47, 31, -10, 4, -1,
  -1, 4, -11, 45, 34, -10, 4, -1,
  -1, 4, -11, 40, 40, -11, 4, -1,
  -1, 4, -10, 34, 45, -11, 4, -1,
  -1, 4, -10, 31, 47, -9, 3, -1,
  -1, 3, -8, 26, 52, -11, 4, -1,
  0, 1, -5, 17, 58, -10, 4, -1,
  0, 1, -4, 13, 60, -8, 3, -1,
  0, 1, -3, 8, 62, -5, 2, -1,
  0, 1, -2, 4, 63, -3, 1, 0
};

static const int chromaUpFilter1D[17 * 4] = {
  0, 64, 0, 0,
  -2, 62, 4, 0,
  -2, 58, 10, -2,
  -4, 56, 14, -2,
  -4, 54, 16, -2,
  -6, 52, 20, -2,
  -6, 46, 28, -4,
  -4, 42, 30, -4,
  -4, 36, 36, -4,
  -4, 30, 42, -4,
  -4, 28, 46, -6,
  -2, 20, 52, -6,
  -2, 16, 54, -4,
  -2, 14, 56, -4,
  -2, 10, 58, -2,
  0, 4, 62, -2,
  0, 0, 0, 0 //Padding for avx2
};


////////////////////////////////////
//__________16-bit filters_________//
static const short downFilter1D_16bit[8][16 * 12] = {
  // ratio <= 20/19
  {
    0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, -6, 127, 7, -2, 0, 0, 0, 0,
    0, 0, 0, 3, -12, 125, 16, -5, 1, 0, 0, 0,
    0, 0, 0, 4, -16, 120, 26, -7, 1, 0, 0, 0,
    0, 0, 0, 5, -18, 114, 36, -10, 1, 0, 0, 0,
    0, 0, 0, 5, -20, 107, 46, -12, 2, 0, 0, 0,
    0, 0, 0, 5, -21, 99, 57, -15, 3, 0, 0, 0,
    0, 0, 0, 5, -20, 89, 68, -18, 4, 0, 0, 0,
    0, 0, 0, 4, -19, 79, 79, -19, 4, 0, 0, 0,
    0, 0, 0, 4, -18, 68, 89, -20, 5, 0, 0, 0,
    0, 0, 0, 3, -15, 57, 99, -21, 5, 0, 0, 0,
    0, 0, 0, 2, -12, 46, 107, -20, 5, 0, 0, 0,
    0, 0, 0, 1, -10, 36, 114, -18, 5, 0, 0, 0,
    0, 0, 0, 1, -7, 26, 120, -16, 4, 0, 0, 0,
    0, 0, 0, 1, -5, 16, 125, -12, 3, 0, 0, 0,
    0, 0, 0, 0, -2, 7, 127, -6, 2, 0, 0, 0,
  },
  // 20/19 < ratio <= 5/4
  {
    0, 2, 0, -14, 33, 86, 33, -14, 0, 2, 0, 0,
    0, 1, 1, -14, 29, 85, 38, -13, -1, 2, 0, 0,
    0, 1, 2, -14, 24, 84, 43, -12, -2, 2, 0, 0,
    0, 1, 2, -13, 19, 83, 48, -11, -3, 2, 0, 0,
    0, 0, 3, -13, 15, 81, 53, -10, -4, 3, 0, 0,
    0, 0, 3, -12, 11, 79, 57, -8, -5, 3, 0, 0,
    0, 0, 3, -11, 7, 76, 62, -5, -7, 3, 0, 0,
    0, 0, 3, -10, 3, 73, 65, -2, -7, 3, 0, 0,
    0, 0, 3, -9, 0, 70, 70, 0, -9, 3, 0, 0,
    0, 0, 3, -7, -2, 65, 73, 3, -10, 3, 0, 0,
    0, 0, 3, -7, -5, 62, 76, 7, -11, 3, 0, 0,
    0, 0, 3, -5, -8, 57, 79, 11, -12, 3, 0, 0,
    0, 0, 3, -4, -10, 53, 81, 15, -13, 3, 0, 0,
    0, 0, 2, -3, -11, 48, 83, 19, -13, 2, 1, 0,
    0, 0, 2, -2, -12, 43, 84, 24, -14, 2, 1, 0,
    0, 0, 2, -1, -13, 38, 85, 29, -14, 1, 1, 0,
  },
  // 5/4 < ratio <= 5/3
  {
    0, 5, -6, -10, 37, 76, 37, -10, -6, 5, 0, 0,
    0, 5, -4, -11, 33, 76, 40, -9, -7, 5, 0, 0,
    -1, 5, -3, -12, 29, 75, 45, -7, -8, 5, 0, 0,
    -1, 4, -2, -13, 25, 75, 48, -5, -9, 5, 1, 0,
    -1, 4, -1, -13, 22, 73, 52, -3, -10, 4, 1, 0,
    -1, 4, 0, -13, 18, 72, 55, -1, -11, 4, 2, -1,
    -1, 4, 1, -13, 14, 70, 59, 2, -12, 3, 2, -1,
    -1, 3, 1, -13, 11, 68, 62, 5, -12, 3, 2, -1,
    -1, 3, 2, -13, 8, 65, 65, 8, -13, 2, 3, -1,
    -1, 2, 3, -12, 5, 62, 68, 11, -13, 1, 3, -1,
    -1, 2, 3, -12, 2, 59, 70, 14, -13, 1, 4, -1,
    -1, 2, 4, -11, -1, 55, 72, 18, -13, 0, 4, -1,
    0, 1, 4, -10, -3, 52, 73, 22, -13, -1, 4, -1,
    0, 1, 5, -9, -5, 48, 75, 25, -13, -2, 4, -1,
    0, 0, 5, -8, -7, 45, 75, 29, -12, -3, 5, -1,
    0, 0, 5, -7, -9, 40, 76, 33, -11, -4, 5, 0,
  },
  // 5/3 < ratio <= 2
  {
    2, -3, -9, 6, 39, 58, 39, 6, -9, -3, 2, 0,
    2, -3, -9, 4, 38, 58, 43, 7, -9, -4, 1, 0,
    2, -2, -9, 2, 35, 58, 44, 9, -8, -4, 1, 0,
    1, -2, -9, 1, 34, 58, 46, 11, -8, -5, 1, 0,
    1, -1, -8, -1, 31, 57, 47, 13, -7, -5, 1, 0,
    1, -1, -8, -2, 29, 56, 49, 15, -7, -6, 1, 1,
    1, 0, -8, -3, 26, 55, 51, 17, -7, -6, 1, 1,
    1, 0, -7, -4, 24, 54, 52, 19, -6, -7, 1, 1,
    1, 0, -7, -5, 22, 53, 53, 22, -5, -7, 0, 1,
    1, 1, -7, -6, 19, 52, 54, 24, -4, -7, 0, 1,
    1, 1, -6, -7, 17, 51, 55, 26, -3, -8, 0, 1,
    1, 1, -6, -7, 15, 49, 56, 29, -2, -8, -1, 1,
    0, 1, -5, -7, 13, 47, 57, 31, -1, -8, -1, 1,
    0, 1, -5, -8, 11, 46, 58, 34, 1, -9, -2, 1,
    0, 1, -4, -8, 9, 44, 58, 35, 2, -9, -2, 2,
    0, 1, -4, -9, 7, 43, 58, 38, 4, -9, -3, 2,
  },
  // 2 < ratio <= 5/2
  {
    -2, -7, 0, 17, 35, 43, 35, 17, 0, -7, -5, 2,
    -2, -7, -1, 16, 34, 43, 36, 18, 1, -7, -5, 2,
    -1, -7, -1, 14, 33, 43, 36, 19, 1, -6, -5, 2,
    -1, -7, -2, 13, 32, 42, 37, 20, 3, -6, -5, 2,
    0, -7, -3, 12, 31, 42, 38, 21, 3, -6, -5, 2,
    0, -7, -3, 11, 30, 42, 39, 23, 4, -6, -6, 1,
    0, -7, -4, 10, 29, 42, 40, 24, 5, -6, -6, 1,
    1, -7, -4, 9, 27, 41, 40, 25, 6, -5, -6, 1,
    1, -6, -5, 7, 26, 41, 41, 26, 7, -5, -6, 1,
    1, -6, -5, 6, 25, 40, 41, 27, 9, -4, -7, 1,
    1, -6, -6, 5, 24, 40, 42, 29, 10, -4, -7, 0,
    1, -6, -6, 4, 23, 39, 42, 30, 11, -3, -7, 0,
    2, -5, -6, 3, 21, 38, 42, 31, 12, -3, -7, 0,
    2, -5, -6, 3, 20, 37, 42, 32, 13, -2, -7, -1,
    2, -5, -6, 1, 19, 36, 43, 33, 14, -1, -7, -1,
    2, -5, -7, 1, 18, 36, 43, 34, 16, -1, -7, -2,
  },
  // 5/2 < ratio <= 20/7
  {
    -6, -3, 5, 19, 31, 36, 31, 19, 5, -3, -6, 0,
    -6, -4, 4, 18, 31, 37, 32, 20, 6, -3, -6, -1,
    -6, -4, 4, 17, 30, 36, 33, 21, 7, -3, -6, -1,
    -5, -5, 3, 16, 30, 36, 33, 22, 8, -2, -6, -2,
    -5, -5, 2, 15, 29, 36, 34, 23, 9, -2, -6, -2,
    -5, -5, 2, 15, 28, 36, 34, 24, 10, -2, -6, -3,
    -4, -5, 1, 14, 27, 36, 35, 24, 10, -1, -6, -3,
    -4, -5, 0, 13, 26, 35, 35, 25, 11, 0, -5, -3,
    -4, -6, 0, 12, 26, 36, 36, 26, 12, 0, -6, -4,
    -3, -5, 0, 11, 25, 35, 35, 26, 13, 0, -5, -4,
    -3, -6, -1, 10, 24, 35, 36, 27, 14, 1, -5, -4,
    -3, -6, -2, 10, 24, 34, 36, 28, 15, 2, -5, -5,
    -2, -6, -2, 9, 23, 34, 36, 29, 15, 2, -5, -5,
    -2, -6, -2, 8, 22, 33, 36, 30, 16, 3, -5, -5,
    -1, -6, -3, 7, 21, 33, 36, 30, 17, 4, -4, -6,
    -1, -6, -3, 6, 20, 32, 37, 31, 18, 4, -4, -6,
  },
  // 20/7 < ratio <= 15/4
  {
    -9, 0, 9, 20, 28, 32, 28, 20, 9, 0, -9, 0,
    -9, 0, 8, 19, 28, 32, 29, 20, 10, 0, -4, -5,
    -9, -1, 8, 18, 28, 32, 29, 21, 10, 1, -4, -5,
    -9, -1, 7, 18, 27, 32, 30, 22, 11, 1, -4, -6,
    -8, -2, 6, 17, 27, 32, 30, 22, 12, 2, -4, -6,
    -8, -2, 6, 16, 26, 32, 31, 23, 12, 2, -4, -6,
    -8, -2, 5, 16, 26, 31, 31, 23, 13, 3, -3, -7,
    -8, -3, 5, 15, 25, 31, 31, 24, 14, 4, -3, -7,
    -7, -3, 4, 14, 25, 31, 31, 25, 14, 4, -3, -7,
    -7, -3, 4, 14, 24, 31, 31, 25, 15, 5, -3, -8,
    -7, -3, 3, 13, 23, 31, 31, 26, 16, 5, -2, -8,
    -6, -4, 2, 12, 23, 31, 32, 26, 16, 6, -2, -8,
    -6, -4, 2, 12, 22, 30, 32, 27, 17, 6, -2, -8,
    -6, -4, 1, 11, 22, 30, 32, 27, 18, 7, -1, -9,
    -5, -4, 1, 10, 21, 29, 32, 28, 18, 8, -1, -9,
    -5, -4, 0, 10, 20, 29, 32, 28, 19, 8, 0, -9,
  },
  // ratio > 15/4
  {
    -8, 7, 13, 18, 22, 24, 22, 18, 13, 7, 2, -10,
    -8, 7, 13, 18, 22, 23, 22, 19, 13, 7, 2, -10,
    -8, 6, 12, 18, 22, 23, 22, 19, 14, 8, 2, -10,
    -9, 6, 12, 17, 22, 23, 23, 19, 14, 8, 3, -10,
    -9, 6, 12, 17, 21, 23, 23, 19, 14, 9, 3, -10,
    -9, 5, 11, 17, 21, 23, 23, 20, 15, 9, 3, -10,
    -9, 5, 11, 16, 21, 23, 23, 20, 15, 9, 4, -10,
    -9, 5, 10, 16, 21, 23, 23, 20, 15, 10, 4, -10,
    -10, 5, 10, 16, 20, 23, 23, 20, 16, 10, 5, -10,
    -10, 4, 10, 15, 20, 23, 23, 21, 16, 10, 5, -9,
    -10, 4, 9, 15, 20, 23, 23, 21, 16, 11, 5, -9,
    -10, 3, 9, 15, 20, 23, 23, 21, 17, 11, 5, -9,
    -10, 3, 9, 14, 19, 23, 23, 21, 17, 12, 6, -9,
    -10, 3, 8, 14, 19, 23, 23, 22, 17, 12, 6, -9,
    -10, 2, 8, 14, 19, 22, 23, 22, 18, 12, 6, -8,
    -10, 2, 7, 13, 19, 22, 23, 22, 18, 13, 7, -8,
  }
};

static const short lumaUpFilter1D_16bit[16 * 8] = {
  0, 0, 0, 64, 0, 0, 0, 0,
  0, 1, -3, 63, 4, -2, 1, 0,
  -1, 2, -5, 62, 8, -3, 1, 0,
  -1, 3, -8, 60, 13, -4, 1, 0,
  -1, 4, -10, 58, 17, -5, 1, 0,
  -1, 4, -11, 52, 26, -8, 3, -1,
  -1, 3, -9, 47, 31, -10, 4, -1,
  -1, 4, -11, 45, 34, -10, 4, -1,
  -1, 4, -11, 40, 40, -11, 4, -1,
  -1, 4, -10, 34, 45, -11, 4, -1,
  -1, 4, -10, 31, 47, -9, 3, -1,
  -1, 3, -8, 26, 52, -11, 4, -1,
  0, 1, -5, 17, 58, -10, 4, -1,
  0, 1, -4, 13, 60, -8, 3, -1,
  0, 1, -3, 8, 62, -5, 2, -1,
  0, 1, -2, 4, 63, -3, 1, 0
};

static const short chromaUpFilter1D_16bit[17 * 4] = {
  0, 64, 0, 0,
  -2, 62, 4, 0,
  -2, 58, 10, -2,
  -4, 56, 14, -2,
  -4, 54, 16, -2,
  -6, 52, 20, -2,
  -6, 46, 28, -4,
  -4, 42, 30, -4,
  -4, 36, 36, -4,
  -4, 30, 42, -4,
  -4, 28, 46, -6,
  -2, 20, 52, -6,
  -2, 16, 54, -4,
  -2, 14, 56, -4,
  -2, 10, 58, -2,
  0, 4, 62, -2,
  0, 0, 0, 0 //Padding for avx2
};


////////////////////////////////////
//_________8-bit filters_________//
static const char downFilter1D_8bit[8][16 * 12] = {
  // ratio <= 20/19
  {
    0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, -6, 127, 7, -2, 0, 0, 0, 0,
    0, 0, 0, 3, -12, 125, 16, -5, 1, 0, 0, 0,
    0, 0, 0, 4, -16, 120, 26, -7, 1, 0, 0, 0,
    0, 0, 0, 5, -18, 114, 36, -10, 1, 0, 0, 0,
    0, 0, 0, 5, -20, 107, 46, -12, 2, 0, 0, 0,
    0, 0, 0, 5, -21, 99, 57, -15, 3, 0, 0, 0,
    0, 0, 0, 5, -20, 89, 68, -18, 4, 0, 0, 0,
    0, 0, 0, 4, -19, 79, 79, -19, 4, 0, 0, 0,
    0, 0, 0, 4, -18, 68, 89, -20, 5, 0, 0, 0,
    0, 0, 0, 3, -15, 57, 99, -21, 5, 0, 0, 0,
    0, 0, 0, 2, -12, 46, 107, -20, 5, 0, 0, 0,
    0, 0, 0, 1, -10, 36, 114, -18, 5, 0, 0, 0,
    0, 0, 0, 1, -7, 26, 120, -16, 4, 0, 0, 0,
    0, 0, 0, 1, -5, 16, 125, -12, 3, 0, 0, 0,
    0, 0, 0, 0, -2, 7, 127, -6, 2, 0, 0, 0,
  },
  // 20/19 < ratio <= 5/4
  {
    0, 2, 0, -14, 33, 86, 33, -14, 0, 2, 0, 0,
    0, 1, 1, -14, 29, 85, 38, -13, -1, 2, 0, 0,
    0, 1, 2, -14, 24, 84, 43, -12, -2, 2, 0, 0,
    0, 1, 2, -13, 19, 83, 48, -11, -3, 2, 0, 0,
    0, 0, 3, -13, 15, 81, 53, -10, -4, 3, 0, 0,
    0, 0, 3, -12, 11, 79, 57, -8, -5, 3, 0, 0,
    0, 0, 3, -11, 7, 76, 62, -5, -7, 3, 0, 0,
    0, 0, 3, -10, 3, 73, 65, -2, -7, 3, 0, 0,
    0, 0, 3, -9, 0, 70, 70, 0, -9, 3, 0, 0,
    0, 0, 3, -7, -2, 65, 73, 3, -10, 3, 0, 0,
    0, 0, 3, -7, -5, 62, 76, 7, -11, 3, 0, 0,
    0, 0, 3, -5, -8, 57, 79, 11, -12, 3, 0, 0,
    0, 0, 3, -4, -10, 53, 81, 15, -13, 3, 0, 0,
    0, 0, 2, -3, -11, 48, 83, 19, -13, 2, 1, 0,
    0, 0, 2, -2, -12, 43, 84, 24, -14, 2, 1, 0,
    0, 0, 2, -1, -13, 38, 85, 29, -14, 1, 1, 0,
  },
  // 5/4 < ratio <= 5/3
  {
    0, 5, -6, -10, 37, 76, 37, -10, -6, 5, 0, 0,
    0, 5, -4, -11, 33, 76, 40, -9, -7, 5, 0, 0,
    -1, 5, -3, -12, 29, 75, 45, -7, -8, 5, 0, 0,
    -1, 4, -2, -13, 25, 75, 48, -5, -9, 5, 1, 0,
    -1, 4, -1, -13, 22, 73, 52, -3, -10, 4, 1, 0,
    -1, 4, 0, -13, 18, 72, 55, -1, -11, 4, 2, -1,
    -1, 4, 1, -13, 14, 70, 59, 2, -12, 3, 2, -1,
    -1, 3, 1, -13, 11, 68, 62, 5, -12, 3, 2, -1,
    -1, 3, 2, -13, 8, 65, 65, 8, -13, 2, 3, -1,
    -1, 2, 3, -12, 5, 62, 68, 11, -13, 1, 3, -1,
    -1, 2, 3, -12, 2, 59, 70, 14, -13, 1, 4, -1,
    -1, 2, 4, -11, -1, 55, 72, 18, -13, 0, 4, -1,
    0, 1, 4, -10, -3, 52, 73, 22, -13, -1, 4, -1,
    0, 1, 5, -9, -5, 48, 75, 25, -13, -2, 4, -1,
    0, 0, 5, -8, -7, 45, 75, 29, -12, -3, 5, -1,
    0, 0, 5, -7, -9, 40, 76, 33, -11, -4, 5, 0,
  },
  // 5/3 < ratio <= 2
  {
    2, -3, -9, 6, 39, 58, 39, 6, -9, -3, 2, 0,
    2, -3, -9, 4, 38, 58, 43, 7, -9, -4, 1, 0,
    2, -2, -9, 2, 35, 58, 44, 9, -8, -4, 1, 0,
    1, -2, -9, 1, 34, 58, 46, 11, -8, -5, 1, 0,
    1, -1, -8, -1, 31, 57, 47, 13, -7, -5, 1, 0,
    1, -1, -8, -2, 29, 56, 49, 15, -7, -6, 1, 1,
    1, 0, -8, -3, 26, 55, 51, 17, -7, -6, 1, 1,
    1, 0, -7, -4, 24, 54, 52, 19, -6, -7, 1, 1,
    1, 0, -7, -5, 22, 53, 53, 22, -5, -7, 0, 1,
    1, 1, -7, -6, 19, 52, 54, 24, -4, -7, 0, 1,
    1, 1, -6, -7, 17, 51, 55, 26, -3, -8, 0, 1,
    1, 1, -6, -7, 15, 49, 56, 29, -2, -8, -1, 1,
    0, 1, -5, -7, 13, 47, 57, 31, -1, -8, -1, 1,
    0, 1, -5, -8, 11, 46, 58, 34, 1, -9, -2, 1,
    0, 1, -4, -8, 9, 44, 58, 35, 2, -9, -2, 2,
    0, 1, -4, -9, 7, 43, 58, 38, 4, -9, -3, 2,
  },
  // 2 < ratio <= 5/2
  {
    -2, -7, 0, 17, 35, 43, 35, 17, 0, -7, -5, 2,
    -2, -7, -1, 16, 34, 43, 36, 18, 1, -7, -5, 2,
    -1, -7, -1, 14, 33, 43, 36, 19, 1, -6, -5, 2,
    -1, -7, -2, 13, 32, 42, 37, 20, 3, -6, -5, 2,
    0, -7, -3, 12, 31, 42, 38, 21, 3, -6, -5, 2,
    0, -7, -3, 11, 30, 42, 39, 23, 4, -6, -6, 1,
    0, -7, -4, 10, 29, 42, 40, 24, 5, -6, -6, 1,
    1, -7, -4, 9, 27, 41, 40, 25, 6, -5, -6, 1,
    1, -6, -5, 7, 26, 41, 41, 26, 7, -5, -6, 1,
    1, -6, -5, 6, 25, 40, 41, 27, 9, -4, -7, 1,
    1, -6, -6, 5, 24, 40, 42, 29, 10, -4, -7, 0,
    1, -6, -6, 4, 23, 39, 42, 30, 11, -3, -7, 0,
    2, -5, -6, 3, 21, 38, 42, 31, 12, -3, -7, 0,
    2, -5, -6, 3, 20, 37, 42, 32, 13, -2, -7, -1,
    2, -5, -6, 1, 19, 36, 43, 33, 14, -1, -7, -1,
    2, -5, -7, 1, 18, 36, 43, 34, 16, -1, -7, -2,
  },
  // 5/2 < ratio <= 20/7
  {
    -6, -3, 5, 19, 31, 36, 31, 19, 5, -3, -6, 0,
    -6, -4, 4, 18, 31, 37, 32, 20, 6, -3, -6, -1,
    -6, -4, 4, 17, 30, 36, 33, 21, 7, -3, -6, -1,
    -5, -5, 3, 16, 30, 36, 33, 22, 8, -2, -6, -2,
    -5, -5, 2, 15, 29, 36, 34, 23, 9, -2, -6, -2,
    -5, -5, 2, 15, 28, 36, 34, 24, 10, -2, -6, -3,
    -4, -5, 1, 14, 27, 36, 35, 24, 10, -1, -6, -3,
    -4, -5, 0, 13, 26, 35, 35, 25, 11, 0, -5, -3,
    -4, -6, 0, 12, 26, 36, 36, 26, 12, 0, -6, -4,
    -3, -5, 0, 11, 25, 35, 35, 26, 13, 0, -5, -4,
    -3, -6, -1, 10, 24, 35, 36, 27, 14, 1, -5, -4,
    -3, -6, -2, 10, 24, 34, 36, 28, 15, 2, -5, -5,
    -2, -6, -2, 9, 23, 34, 36, 29, 15, 2, -5, -5,
    -2, -6, -2, 8, 22, 33, 36, 30, 16, 3, -5, -5,
    -1, -6, -3, 7, 21, 33, 36, 30, 17, 4, -4, -6,
    -1, -6, -3, 6, 20, 32, 37, 31, 18, 4, -4, -6,
  },
  // 20/7 < ratio <= 15/4
  {
    -9, 0, 9, 20, 28, 32, 28, 20, 9, 0, -9, 0,
    -9, 0, 8, 19, 28, 32, 29, 20, 10, 0, -4, -5,
    -9, -1, 8, 18, 28, 32, 29, 21, 10, 1, -4, -5,
    -9, -1, 7, 18, 27, 32, 30, 22, 11, 1, -4, -6,
    -8, -2, 6, 17, 27, 32, 30, 22, 12, 2, -4, -6,
    -8, -2, 6, 16, 26, 32, 31, 23, 12, 2, -4, -6,
    -8, -2, 5, 16, 26, 31, 31, 23, 13, 3, -3, -7,
    -8, -3, 5, 15, 25, 31, 31, 24, 14, 4, -3, -7,
    -7, -3, 4, 14, 25, 31, 31, 25, 14, 4, -3, -7,
    -7, -3, 4, 14, 24, 31, 31, 25, 15, 5, -3, -8,
    -7, -3, 3, 13, 23, 31, 31, 26, 16, 5, -2, -8,
    -6, -4, 2, 12, 23, 31, 32, 26, 16, 6, -2, -8,
    -6, -4, 2, 12, 22, 30, 32, 27, 17, 6, -2, -8,
    -6, -4, 1, 11, 22, 30, 32, 27, 18, 7, -1, -9,
    -5, -4, 1, 10, 21, 29, 32, 28, 18, 8, -1, -9,
    -5, -4, 0, 10, 20, 29, 32, 28, 19, 8, 0, -9,
  },
  // ratio > 15/4
  {
    -8, 7, 13, 18, 22, 24, 22, 18, 13, 7, 2, -10,
    -8, 7, 13, 18, 22, 23, 22, 19, 13, 7, 2, -10,
    -8, 6, 12, 18, 22, 23, 22, 19, 14, 8, 2, -10,
    -9, 6, 12, 17, 22, 23, 23, 19, 14, 8, 3, -10,
    -9, 6, 12, 17, 21, 23, 23, 19, 14, 9, 3, -10,
    -9, 5, 11, 17, 21, 23, 23, 20, 15, 9, 3, -10,
    -9, 5, 11, 16, 21, 23, 23, 20, 15, 9, 4, -10,
    -9, 5, 10, 16, 21, 23, 23, 20, 15, 10, 4, -10,
    -10, 5, 10, 16, 20, 23, 23, 20, 16, 10, 5, -10,
    -10, 4, 10, 15, 20, 23, 23, 21, 16, 10, 5, -9,
    -10, 4, 9, 15, 20, 23, 23, 21, 16, 11, 5, -9,
    -10, 3, 9, 15, 20, 23, 23, 21, 17, 11, 5, -9,
    -10, 3, 9, 14, 19, 23, 23, 21, 17, 12, 6, -9,
    -10, 3, 8, 14, 19, 23, 23, 22, 17, 12, 6, -9,
    -10, 2, 8, 14, 19, 22, 23, 22, 18, 12, 6, -8,
    -10, 2, 7, 13, 19, 22, 23, 22, 18, 13, 7, -8,
  }
};

static const char lumaUpFilter1D_8bit[16 * 8] = {
  0, 0, 0, 64, 0, 0, 0, 0,
  0, 1, -3, 63, 4, -2, 1, 0,
  -1, 2, -5, 62, 8, -3, 1, 0,
  -1, 3, -8, 60, 13, -4, 1, 0,
  -1, 4, -10, 58, 17, -5, 1, 0,
  -1, 4, -11, 52, 26, -8, 3, -1,
  -1, 3, -9, 47, 31, -10, 4, -1,
  -1, 4, -11, 45, 34, -10, 4, -1,
  -1, 4, -11, 40, 40, -11, 4, -1,
  -1, 4, -10, 34, 45, -11, 4, -1,
  -1, 4, -10, 31, 47, -9, 3, -1,
  -1, 3, -8, 26, 52, -11, 4, -1,
  0, 1, -5, 17, 58, -10, 4, -1,
  0, 1, -4, 13, 60, -8, 3, -1,
  0, 1, -3, 8, 62, -5, 2, -1,
  0, 1, -2, 4, 63, -3, 1, 0
};

static const char chromaUpFilter1D_8bit[17 * 4] = {
  0, 64, 0, 0,
  -2, 62, 4, 0,
  -2, 58, 10, -2,
  -4, 56, 14, -2,
  -4, 54, 16, -2,
  -6, 52, 20, -2,
  -6, 46, 28, -4,
  -4, 42, 30, -4,
  -4, 36, 36, -4,
  -4, 30, 42, -4,
  -4, 28, 46, -6,
  -2, 20, 52, -6,
  -2, 16, 54, -4,
  -2, 14, 56, -4,
  -2, 10, 58, -2,
  0, 4, 62, -2,
  0, 0, 0, 0 //Padding for avx2
};


//Helper function for choosing the correct filter
//Returns the size of the filter and the filter param is set to the correct filter
int kvz_getFilter(const int** const filter, int is_upsampling, int is_luma, int phase, int filter_ind);

//Helper function for choosing the correct filter
//Returns the size of the filter and the filter param is set to the correct filter
unsigned kvz_prepareFilter(const int** const filter, int is_upsampling, int is_luma, int filter_ind);

//Helper function for choosing the correct filter with the given depth
//Returns the size of the filter and the filter param is set to the correct filter
unsigned kvz_prepareFilterDepth(const void** const filter, int is_upsampling, int is_luma, int filter_ind, int depth);

#endif