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

// GuidedUSCalAlgo Logic includes
#include "vtkSlicerGuidedUSCalAlgoLogic.h"
#include "vtkPointToLineRegistration.h"

// MRML includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>

// STD includes
#include <cassert>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerGuidedUSCalAlgoLogic);

//----------------------------------------------------------------------------
vtkSlicerGuidedUSCalAlgoLogic::vtkSlicerGuidedUSCalAlgoLogic()
  : PointToLineRegistration(vtkSmartPointer<vtkPointToLineRegistration>::New())
{
}

//----------------------------------------------------------------------------
vtkSlicerGuidedUSCalAlgoLogic::~vtkSlicerGuidedUSCalAlgoLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//----------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::AddPointAndLine(double point[3], double lineOrigin[3], double lineDirection[3])
{
  this->PointToLineRegistration->AddPoint(point[0], point[1], point[2]);
  PointToLineRegistration->AddLine(lineOrigin[0], lineOrigin[1], lineOrigin[2], lineDirection[0], lineDirection[1], lineDirection[2]);
}

//----------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::Reset()
{
  this->PointToLineRegistration->Reset();
}

//----------------------------------------------------------------------------
vtkMatrix4x4* vtkSlicerGuidedUSCalAlgoLogic::CalculateRegistration()
{
  return this->PointToLineRegistration->Compute();
}

//----------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::SetTolerance(double arg)
{
  this->PointToLineRegistration->SetTolerance(arg);
}

//----------------------------------------------------------------------------
double vtkSlicerGuidedUSCalAlgoLogic::GetTolerance() const
{
  return this->PointToLineRegistration->GetTolerance();
}

//----------------------------------------------------------------------------
unsigned int vtkSlicerGuidedUSCalAlgoLogic::GetCount() const
{
  return this->PointToLineRegistration->GetCount();
}

//----------------------------------------------------------------------------
double vtkSlicerGuidedUSCalAlgoLogic::GetError() const
{
  return this->PointToLineRegistration->GetError();
}

//---------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::SetMRMLSceneInternal(vtkMRMLScene* newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::RegisterNodes()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerGuidedUSCalAlgoLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}
