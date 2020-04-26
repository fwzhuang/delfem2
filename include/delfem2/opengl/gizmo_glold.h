//
//  gizmo_glold.h
//  examples_glfwold_hdronly
//
//  Created by Nobuyuki Umetani on 2020-04-19.
//

#ifndef DFM2_GIZMO_GLOLD_H
#define DFM2_GIZMO_GLOLD_H

#include "delfem2/opengl/v3q_glold.h"
#include "delfem2/opengl/funcs_glold.h"

namespace delfem2{
namespace opengl{

template <typename REAL>
DFM2_INLINE void DrawAxisHandler
 (REAL s, const CVec3<REAL>& p,
  int ielem_picked);

template <typename REAL>
DFM2_INLINE void DrawHandlerRotation_PosQuat
(const CVec3<REAL>& pos,
 const REAL quat[4],
 REAL size,
 int ielem_picked);


template <typename REAL>
void Draw(const CGizmo_Affine<REAL>& ga)
{
  if( ga.igizmo_mode == 0 ){
    DrawAxisHandler(ga.gizmo_trnsl.size,
                    ga.gizmo_trnsl.pos,
                    ga.gizmo_trnsl.ielem_picked);
  }
  else if( ga.igizmo_mode == 1 ){
    DrawHandlerRotation_PosQuat(ga.gizmo_rot.pos,
                                ga.gizmo_rot.quat,
                                ga.gizmo_rot.size,
                                ga.gizmo_rot.ielem_picked);
  }
  {
    ::glDisable(GL_DEPTH_TEST);
    ::glDisable(GL_LIGHTING);
    {
      ::glColor3d(1,1,1);
      const CVec3<REAL>& p0 = ga.pivot0;
      DrawSphereAt(32, 32, 0.02, p0.x(), p0.y(), p0.z());
    }
    {
      ::glColor3d(1,1,0);
      const CVec3<REAL>& p0 = ga.gizmo_trnsl.pos;
      DrawSphereAt(32, 32, 0.02, p0.x(), p0.y(), p0.z());
    }
    ::glEnable(GL_DEPTH_TEST);
  }
}

template <typename REAL>
void Draw(const CGizmo_Rotation<REAL>& gizmo_rot)
{
  DrawHandlerRotation_PosQuat(gizmo_rot.pos,
                              gizmo_rot.quat,
                              gizmo_rot.size,
                              gizmo_rot.ielem_picked);
}

}
}




template <typename REAL>
DFM2_INLINE void delfem2::opengl::DrawAxisHandler
(REAL s, const CVec3<REAL>& p,
 int ielem_picked)
{
  GLboolean is_lighting = ::glIsEnabled(GL_LIGHTING);
  ::glDisable(GL_LIGHTING);
  if( ielem_picked == 0 ){ ::glColor3d(1,1,0); }   else{ ::glColor3d(1,0,0); }
  opengl::DrawArrow(p,CVec3<REAL>(+s, 0, 0));
  opengl::DrawArrow(p,CVec3<REAL>(-s, 0, 0));
  //
  if( ielem_picked == 1 ){ ::glColor3d(1,1,0); }   else{ ::glColor3d(0,1,0); }
  opengl::DrawArrow(p, CVec3<REAL>(0, +s, 0));
  opengl::DrawArrow(p, CVec3<REAL>(0, -s, 0));
  //
  if( ielem_picked == 2 ){ ::glColor3d(1,1,0); }   else{ ::glColor3d(0,0,1); }
  opengl::DrawArrow(p, CVec3<REAL>(0, 0, +s));
  opengl::DrawArrow(p, CVec3<REAL>(0, 0, -s));
  
  if (is_lighting){ ::glEnable(GL_LIGHTING); }
}
#ifndef DFM2_HEADER_ONLY
template void delfem2::opengl::DrawAxisHandler
 (float s, const CVec3f& p,
  int ielem_picked);
template void delfem2::opengl::DrawAxisHandler
(double s, const CVec3d& p,
 int ielem_picked);
#endif

// ------------------------------------------

template <typename REAL>
DFM2_INLINE void delfem2::opengl::DrawHandlerRotation_PosQuat
 (const CVec3<REAL>& pos,
  const REAL quat[4],
  REAL size,
  int ielem_picked)
{
  ::glDisable(GL_LIGHTING);
  {
    if( ielem_picked == 0 ){ ::glColor3d(1,1,0); }   else{ ::glColor3d(1,0,0); }
    const CVec3<REAL>& ax = QuatVec(quat,CVec3<REAL>(1,0,0));
    opengl::DrawCircleWire(ax, pos, size);
  }
  {
    if( ielem_picked == 1 ){ ::glColor3d(1,1,0); }   else{ ::glColor3d(0,1,0); }
    const CVec3<REAL>& ay = QuatVec(quat,CVec3<REAL>(0,1,0));
    opengl::DrawCircleWire(ay, pos, size);
  }
  {
    if( ielem_picked == 2 ){ ::glColor3d(1,1,0); }   else{ ::glColor3d(0,0,1); }
    const CVec3<REAL>& az = QuatVec(quat,CVec3<REAL>(0,0,1));
    opengl::DrawCircleWire(az, pos, size);
  }
}
#ifndef DFM2_HEADER_ONLY
template DFM2_INLINE void delfem2::opengl::DrawHandlerRotation_PosQuat
(const CVec3d& pos,
 const double quat[4],
 double size,
 int ielem_picked);
template DFM2_INLINE void delfem2::opengl::DrawHandlerRotation_PosQuat
 (const CVec3f& pos,
  const float quat[4],
  float size,
  int ielem_picked);
#endif


#endif /* gizmo_glold_h */
