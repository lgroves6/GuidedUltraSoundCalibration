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

// GuidedUsCalAlgo Logic includes
#include <vtkSlicerGuidedUsCalAlgoLogic.h>

// GuidedUsCalAlgo includes
#include "qSlicerGuidedUsCalAlgoModule.h"
#include "qSlicerGuidedUsCalAlgoModuleWidget.h"

//-----------------------------------------------------------------------------
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QtPlugin>
Q_EXPORT_PLUGIN2(qSlicerGuidedUsCalAlgoModule, qSlicerGuidedUsCalAlgoModule);
#endif

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerGuidedUsCalAlgoModulePrivate
{
public:
  qSlicerGuidedUsCalAlgoModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerGuidedUsCalAlgoModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerGuidedUsCalAlgoModulePrivate::qSlicerGuidedUsCalAlgoModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerGuidedUsCalAlgoModule methods

//-----------------------------------------------------------------------------
qSlicerGuidedUsCalAlgoModule::qSlicerGuidedUsCalAlgoModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerGuidedUsCalAlgoModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerGuidedUsCalAlgoModule::~qSlicerGuidedUsCalAlgoModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerGuidedUsCalAlgoModule::helpText() const
{
  return "This is a hidden loadable module that contains a point to line registration algorithm";
}

//-----------------------------------------------------------------------------
QString qSlicerGuidedUsCalAlgoModule::acknowledgementText() const
{
  return "The algorithm was written by Elvis Chen (Robarts Research Institute). This extention was created by Leah Groves (Robarts Research Institute), with help from Adam Rankin (Robarts Research Institute)";
}

//-----------------------------------------------------------------------------
QStringList qSlicerGuidedUsCalAlgoModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("Elvis Chen (Robarts Research Intitute)")
  << QString("Leah Groves (Robarts Research Institute)") 
  <<QString("Adam Rankin (Robarts Research Institute)")
  <<QString("Funding through OGS");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerGuidedUsCalAlgoModule::icon() const
{
  return QIcon(":/Icons/GuidedUsCalAlgo.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerGuidedUsCalAlgoModule::categories() const
{
  return QStringList() << "IGT";
}

//-----------------------------------------------------------------------------
QStringList qSlicerGuidedUsCalAlgoModule::dependencies() const
{
  return QStringList()<< "SlicerOpenCV";
}

//-----------------------------------------------------------------------------
void qSlicerGuidedUsCalAlgoModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerGuidedUsCalAlgoModule
::createWidgetRepresentation()
{
  return new qSlicerGuidedUsCalAlgoModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerGuidedUsCalAlgoModule::createLogic()
{
  return vtkSlicerGuidedUsCalAlgoLogic::New();
}
