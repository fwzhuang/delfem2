/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#ifndef DFM2_OBJFUNC_v23_H
#define DFM2_OBJFUNC_v23_H

#include "delfem2/dfm2_inline.h"
#include <vector>
#include "delfem2/mat3.h"
#include "delfem2/vec3.h"

namespace delfem2 {

DFM2_INLINE void PBD_Pre3D(
    std::vector<double>& aXYZt,
    double dt,
    const double gravity[3],
    const std::vector<double>& aXYZ,
    const std::vector<double>& aUVW,
    const std::vector<int>& aBCFlag);

DFM2_INLINE void PBD_Post(
    std::vector<double>& aXYZ,
    std::vector<double>& aUVW,
    double dt,
    const std::vector<double>& aXYZt,
    const std::vector<int>& aBCFlag);

DFM2_INLINE void PBD_Update_Const3_Point3_Dim3(
    std::vector<double>& aXYZt,
    const double m[3],
    const double C[3],
    const double dCdp[3][9],
    const int aIP[3]);

DFM2_INLINE void PBD_Update_Const3(
    double* aXYZt,
    const int np,
    const int ndim,
    const double* m,
    const double* C,
    const double* dCdp,
    const unsigned int* aIP,
    double ratio);

DFM2_INLINE void PBD_ConstProj_Rigid2D(
    double* aXYt,
    double stiffness,
    const unsigned int *clstr_ind, unsigned int nclstr_ind,
    const unsigned int *clstr, unsigned int nclstr0,
    const double* aXY0, unsigned int nXY0);

DFM2_INLINE void PBD_ConstProj_Rigid3D(
    double* aXYZt,
    double stiffness,
    const int* clstr_ind, int nclstr_ind,
    const int* clstr,     int nclstr0,
    const double* aXYZ0,   int nXYZ0);

DFM2_INLINE void PBD_CdC_TriStrain2D3D(
    double C[3],
    double dCdp[3][9],
    const double P[3][2], // (in) undeformed triangle vertex positions
    const double p[3][3]); // (in) deformed triangle vertex positions

DFM2_INLINE void PBD_ConstraintProjection_DistanceTri2D3D(
    double C[3],
    double dCdp[3][9],
    const double P[3][2], // (in) undeformed triangle vertex positions
    const double p[3][3]); // (in) deformed triangle vertex positions

DFM2_INLINE void PBD_ConstraintProjection_EnergyStVK(
    double& C,
    double dCdp[9],
    const double P[3][2], // (in) undeformed triangle vertex positions
    const double p[3][3], // (in) deformed triangle vertex positions)
    const double lambda,
    const double myu);

DFM2_INLINE void PBD_ConstraintProjection_DistanceTet(
    double C[6],
    double dCdp[6][12],
    const double P[4][3], // (in) undeformed triangle vertex positions
    const double p[4][3]); // (in) deformed triangle vertex positions

DFM2_INLINE void PBD_CdC_QuadBend(
    double C[3],
    double dCdp[3][12],
    const double P[4][3],
    const double p[4][3]);

DFM2_INLINE void PBD_Seam(
    double* aXYZt,
    unsigned int nXYZ,
    const unsigned int* aLine,
    unsigned int nline);

DFM2_INLINE void WdWddW_MIPS(
    double& E, double dE[3][3], double ddE[3][3][3][3],
    const double c[3][3],
    const double C[3][3]);
  

DFM2_INLINE double W_ArapEnergy
 (const std::vector<double>& aXYZ0,
  const std::vector<double>& aXYZ1,
  const std::vector<double>& aQuat1,
  const std::vector<unsigned int>& psup_ind,
  const std::vector<unsigned int>& psup);

DFM2_INLINE void dW_ArapEnergy
 (std::vector<double>& aRes,
  const std::vector<double>& aXYZ0,
  const std::vector<double>& aXYZ1,
  const std::vector<double>& aQuat1,
  const std::vector<unsigned int>& psup_ind,
  const std::vector<unsigned int>& psup);

DFM2_INLINE void ddW_ArapEnergy
 (std::vector<double>& eM,
  const std::vector<unsigned int>& aIP,
  const std::vector<double>& aXYZ0,
  const std::vector<double>& aQuat1);


template <typename T>
DFM2_INLINE void GetConstConstDiff_Bend
 (double& C,
  CVec3<T> dC[4],
  // -----
  const CVec3<T>& p0,
  const CVec3<T>& p1,
  const CVec3<T>& p2,
  const CVec3<T>& p3);

}

#ifdef DFM2_HEADER_ONLY
#  include "delfem2/objf_geo3.cpp"
#endif

#endif /* pbd_v23_h */
