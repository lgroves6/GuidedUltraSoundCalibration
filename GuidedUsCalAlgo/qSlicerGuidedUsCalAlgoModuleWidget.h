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

#ifndef __qSlicerGuidedUsCalAlgoModuleWidget_h
#define __qSlicerGuidedUsCalAlgoModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerGuidedUsCalAlgoModuleExport.h"

class qSlicerGuidedUsCalAlgoModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_GUIDEDUSCALALGO_EXPORT qSlicerGuidedUsCalAlgoModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerGuidedUsCalAlgoModuleWidget(QWidget *parent=0);
  virtual ~qSlicerGuidedUsCalAlgoModuleWidget();

public slots:


protected:
  QScopedPointer<qSlicerGuidedUsCalAlgoModuleWidgetPrivate> d_ptr;

  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerGuidedUsCalAlgoModuleWidget);
  Q_DISABLE_COPY(qSlicerGuidedUsCalAlgoModuleWidget);
};

#endif
