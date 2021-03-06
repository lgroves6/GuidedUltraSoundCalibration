/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// .NAME vtkSlicerGuidedUSCalAlgoLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerGuidedUSCalAlgoLogic_h
#define __vtkSlicerGuidedUSCalAlgoLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"

// MRML includes

// STD includes
#include <cstdlib>

// VTK includes
#include <vtkSmartPointer.h>

#include "vtkSlicerGuidedUSCalAlgoModuleLogicExport.h"

class vtkPointToLineRegistration;
class vtkMatrix4x4;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class VTK_SLICER_GUIDEDUSCALALGO_MODULE_LOGIC_EXPORT vtkSlicerGuidedUSCalAlgoLogic :
  public vtkSlicerModuleLogic
{
public:
  static vtkSlicerGuidedUSCalAlgoLogic* New();
  vtkTypeMacro(vtkSlicerGuidedUSCalAlgoLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);

  void AddPointAndLine(double point[3], double lineOrigin[3], double lineDirection[3]);
  void Reset();

  vtkMatrix4x4* CalculateRegistration();

  void SetTolerance(double arg);
  double GetTolerance() const;
  unsigned int GetCount() const;
  double GetError() const;

protected:
  vtkSlicerGuidedUSCalAlgoLogic();
  virtual ~vtkSlicerGuidedUSCalAlgoLogic();

  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);

  vtkSmartPointer<vtkPointToLineRegistration> PointToLineRegistration;

private:
  vtkSlicerGuidedUSCalAlgoLogic(const vtkSlicerGuidedUSCalAlgoLogic&); // Not implemented
  void operator=(const vtkSlicerGuidedUSCalAlgoLogic&); // Not implemented
};

#endif
