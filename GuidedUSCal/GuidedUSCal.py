import os
import unittest
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *

class GuidedUSCal(ScriptedLoadableModule):
    """Uses ScriptedLoadableModuleWidget base class, available at:
    https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
    """
    def __init__(self, parent):
        ScriptedLoadableModule.__init__(self, parent)
        self.parent.title= "US Calibration Module"
        self.parent.categories=["Examples"]
        self.parent.contributors=["Leah Groves"]
        self.parent.helpText="""
This is a scripted loadable module that performs Ultrsound Calibration
"""
        self.parent.helpText = self.getDefaultModuleDocumentationLink()
        
class GuidedUSCalWidget(ScriptedLoadableModuleWidget):
  """Uses ScriptedLoadableModuleWidget base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """
  def __init__(self, parent=None):
    ScriptedLoadableModuleWidget.__init__(self, parent)
    self.fiducialNode = None

  def setup(self):

    #tells them that you are creating a collapsible button 
    self.usButton = ctk.ctkCollapsibleButton()
    self.usButton.text = "Ultrasound Control"
    self.layout.addWidget(self.usButton)
    self.streamLayout = qt.QFormLayout(self.usButton)
    self.streamButton = qt.QPushButton("Stream")
    self.streamButton.toolTip = "Print 'Calibrate' in standard output."
    self.streamLayout.addWidget(self.streamButton)
    self.streamButton.connect('clicked(bool)', self.onStreamButtonCicked)

    self.layout.addWidget(self.usButton)
    self.freezeButton = qt.QPushButton("Freeze")
    self.freezeButton.toolTip="Print 'Freeze' in standard output"
    self.streamLayout.addWidget(self.freezeButton)
    self.freezeButton.connect('clicked(bool)', self.onFreezeButtonClicked)

    self.inputFrame = qt.QFrame(self.usButton)
    self.inputFrame.setLayout(qt.QHBoxLayout())
    self.streamLayout.addWidget(self.inputFrame)
    self.inputSelector = qt.QLabel("Input Volume: ", self.inputFrame)
    self.inputFrame.layout().addWidget(self.inputSelector)
    self.inputSelector = slicer.qMRMLNodeComboBox(self.inputFrame)
    self.inputSelector.nodeTypes = ( ("vtkMRMLScalarVolumeNode"), "" )
    self.inputSelector.addEnabled = False
    self.inputSelector.removeEnabled = False
    self.inputSelector.setMRMLScene( slicer.mrmlScene )
    self.inputFrame.layout().addWidget(self.inputSelector)
    self.inputFrame.connect('clicked(bool)', self.onApply)
    self.layout.addWidget(self.usButton)
    self.applyButton = qt.QPushButton("Apply Volume")
    self.applyButton.toolTip = "Open volume."
    self.streamLayout.addWidget(self.applyButton)
    self.applyButton.connect('clicked(bool)', self.onApply)

    self.layout.addWidget(self.usButton)
    self.crossMarkerButton = qt.QPushButton("Set Straw center Marker")  
    self.crossMarkerButton.toolTip = "Creates a marker to be placed on the straw"
    self.streamLayout.addWidget(self.crossMarkerButton)
    self.crossMarkerButton.connect('clicked(bool)', self.onCrossMarkerClicked)

    self.layout.addWidget(self.usButton)
    self.faducialButton = qt.QPushButton("Set Faducial")  
    self.faducialButton.toolTip = "Creates a faducial to be placed on the straw"
    self.streamLayout.addWidget(self.faducialButton)
    self.faducialButton.connect('clicked(bool)', self.onFaducialButtonClicked)

    # Calculate the path of the crosshair model and load it into the scene
    modelPath = os.path.join(os.path.dirname(slicer.modules.guideduscal.path), 'Resources/Models/CrossHair.vtk')
    success, self.crosshairNode = slicer.util.loadModel(modelPath, True)

    #adding an observer to scene to listen for mrml node 
    self.sceneObserverTag = slicer.mrmlScene.AddObserver(slicer.mrmlScene.NodeAddedEvent, self.onNodeAdded)

  def onApply(self):
    inputVolume = self.inputSelector.currentNode()
    selectionNode = slicer.app.applicationLogic().GetSelectionNode()
    selectionNode.SetReferenceActiveVolumeID(inputVolume.GetID())
    slicer.app.applicationLogic().PropagateVolumeSelection(0)
  
  def onStreamButtonCicked(self):
    print('Streaming')

  def onFreezeButtonClicked(self):
    print('Frozen') 

  def onFaducialButtonClicked(self):
    slicer.modules.markups.logic().StartPlaceMode(0)



  @vtk.calldata_type(vtk.VTK_OBJECT)
  def onNodeAdded(self, caller, event, callData):
    if type(callData) is slicer.vtkMRMLMarkupsFiducialNode:
      if self.fiducialNode is not None:
        self.fiducialNode.RemoveObserver(self.markupAddedObserverTag)
        self.fiducialNode = None
      self.fiducialNode = callData
      self.markupAddedObserverTag = self.fiducialNode.AddObserver(slicer.vtkMRMLMarkupsNode.MarkupAddedEvent, self.onMarkupAdded)
      self.onMarkupAdded(self.fiducialNode, slicer.vtkMRMLMarkupsNode.MarkupAddedEvent)

  def cleanup(self):
    slicer.mrmlScene.RemoveObserver(self.sceneObserverTag)

  def onMarkupAdded(self, fiducialNodeCaller, event):
    arr=[0,0,0]
    MarkupIndex = 0
    if self.fiducialNode.GetDisplayNode() is None:
      self.fiducialNode.CreateDefaultDisplayNodes()
    displayNode = self.fiducialNode.GetDisplayNode()
    displayNode.SetGlyphType(3)
    displayNode.SetGlyphScale(7.5)
    displayNode.SetTextScale(0)
    displayNode.SetSelectedColor(0, 1, 1)

    self.fiducialNode.GetMarkupPoint(self.fiducialNode.GetNumberOfMarkups()-1,0, arr)
    print(arr)

  def onCrossMarkerClicked(self):
    # Create a linear transform node and pair it to the model node 
    self.crosshairTransformNode = slicer.vtkMRMLLinearTransformNode()
    slicer.mrmlScene.AddNode(self.crosshairTransformNode)

    self.crosshairNode.SetAndObserveTransformNodeID(self.crosshairTransformNode.GetID())
    self.crosshairNode.GetDisplayNode().SetColor(0, 1, 1)
    self.crosshairNode.GetDisplayNode().SetSliceIntersectionVisibility(1)

    mat = vtk.vtkMatrix4x4()
    mat.SetElement(0,3,-250)
    mat.SetElement(1,3,-250)
    self.crosshairTransformNode.SetMatrixTransformToParent(mat)




# class GuidedUSCalLogic(ScriptedLoadableModuleLogic):





   