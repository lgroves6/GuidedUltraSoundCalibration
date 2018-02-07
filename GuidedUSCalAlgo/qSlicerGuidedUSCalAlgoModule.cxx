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
#include <vtkSlicerGuidedUSCalAlgoLogic.h>

// GuidedUSCalAlgo includes
#include "qSlicerGuidedUSCalAlgoModule.h"
#include "qSlicerGuidedUSCalAlgoModuleWidget.h"

//-----------------------------------------------------------------------------
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QtPlugin>
Q_EXPORT_PLUGIN2(qSlicerGuidedUSCalAlgoModule, qSlicerGuidedUSCalAlgoModule);
#endif

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerGuidedUSCalAlgoModulePrivate
{
public:
  qSlicerGuidedUSCalAlgoModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerGuidedUSCalAlgoModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerGuidedUSCalAlgoModulePrivate::qSlicerGuidedUSCalAlgoModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerGuidedUSCalAlgoModule methods

//-----------------------------------------------------------------------------
qSlicerGuidedUSCalAlgoModule::qSlicerGuidedUSCalAlgoModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerGuidedUSCalAlgoModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerGuidedUSCalAlgoModule::~qSlicerGuidedUSCalAlgoModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerGuidedUSCalAlgoModule::helpText() const
{
  return "This is a hidden loadable module that contains a point to line registration algorithm";
}

//-----------------------------------------------------------------------------
QString qSlicerGuidedUSCalAlgoModule::acknowledgementText() const
{
  return "The algorithm was written by Elvis Chen (Robarts Research Institute). This extention was created by Leah Groves (Robarts Research Institute), with help from Adam Rankin (Robarts Research Institute)";
}

//-----------------------------------------------------------------------------
QStringList qSlicerGuidedUSCalAlgoModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("Elvis Chen (Robarts Research Intitute)")
  << QString("Leah Groves (Robarts Research Institute)") 
  <<QString("Adam Rankin (Robarts Research Institute)")
  <<QString("Funding through OGS");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerGuidedUSCalAlgoModule::icon() const
{
  return QIcon(":/Icons/GuidedUSCalAlgo.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerGuidedUSCalAlgoModule::categories() const
{
  return QStringList() << "IGT";
}

//-----------------------------------------------------------------------------
QStringList qSlicerGuidedUSCalAlgoModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerGuidedUSCalAlgoModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerGuidedUSCalAlgoModule
::createWidgetRepresentation()
{
  return new qSlicerGuidedUSCalAlgoModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerGuidedUSCalAlgoModule::createLogic()
{
  return vtkSlicerGuidedUSCalAlgoLogic::New();
}
