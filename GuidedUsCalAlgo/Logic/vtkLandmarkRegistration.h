/*====================================================================
Copyright(c) 2018 Adam Rankin


Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and / or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
====================================================================*/

// .NAME vtkLandmarkRegistration - class for performing point to line registration
// .SECTION Description
// Performs a point to line registration

#ifndef __vtkLandmarkRegistration_h
#define __vtkLandmarkRegistration_h

#include <vtkObject.h>
#include <vtkSmartPointer.h>

#include "vtkSlicerGuidedUsCalAlgoModuleLogicExport.h"

class VTK_SLICER_GUIDEDUSCALALGO_MODULE_LOGIC_EXPORT vtkLandmarkRegistration : public vtkObject
{
  typedef vtkSmartPointer<vtkVector3d> Vec3d;

public:
  static vtkLandmarkRegistration* New();
  vtkTypeMacro(vtkLandmarkRegistration, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  enum REGISTRATION_Mode
  {
    MODE_RIGID,
    MODE_SIMILARITY,
    MODE_AFFINE
  };

  void SetSourceLandmarks(const cv::Mat& landmarks);
  void SetTargetLandmarks(const cv::Mat& landmarks);

  void Swap();

  Mode GetMode() const;
  void SetMode(Mode arg);
  void SetModeToRigid();
  void SetModeToSimilarity();
  void SetModeToAffine();

  vtkMatrix4x4* Compute();
  double GetError() const;

public:
  vtkLandmarkRegistration();
  ~vtkLandmarkRegistration();

protected:
  std::vector<Vec3d>    SourceLandmarks;
  std::vector<Vec3d>    TargetLandmarks;

  REGISTRATION_Mode     Mode = MODE_SIMILARITY;
};
