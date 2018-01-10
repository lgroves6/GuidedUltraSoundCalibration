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

// Qt includes
#include <QDebug>

// SlicerQt includes
#include "qSlicerGuidedUsCalAlgoModuleWidget.h"
#include "ui_qSlicerGuidedUsCalAlgoModuleWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerGuidedUsCalAlgoModuleWidgetPrivate: public Ui_qSlicerGuidedUsCalAlgoModuleWidget
{
public:
  qSlicerGuidedUsCalAlgoModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerGuidedUsCalAlgoModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerGuidedUsCalAlgoModuleWidgetPrivate::qSlicerGuidedUsCalAlgoModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerGuidedUsCalAlgoModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerGuidedUsCalAlgoModuleWidget::qSlicerGuidedUsCalAlgoModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerGuidedUsCalAlgoModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerGuidedUsCalAlgoModuleWidget::~qSlicerGuidedUsCalAlgoModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerGuidedUsCalAlgoModuleWidget::setup()
{
  Q_D(qSlicerGuidedUsCalAlgoModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();
}
