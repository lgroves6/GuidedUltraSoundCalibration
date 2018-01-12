import os
import unittest
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *
import logging

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
    ScriptedLoadableModuleWidget.setup(self)

    layoutManager = slicer.app.layoutManager()
    layoutManager.setLayout(slicer.vtkMRMLLayoutNode.SlicerLayoutOneUpRedSliceView)

    #tells them that you are creating a collapsible button 
    self.usButton = ctk.ctkCollapsibleButton()
    self.usButton.text = "Ultrasound Information"
    self.layout.addWidget(self.usButton)
    self.usLayout = qt.QFormLayout(self.usButton)

    self.layout.addWidget(self.usButton)
    self.inputIPLineEdit = qt.QLineEdit()
    self.inputIPLineEdit.setPlaceholderText("127.0.0.1")
    self.inputIPLineEdit.toolTip = "Put the IP address of your ultrasound device here"
    self.usLayout.addRow("Server IP:", self.inputIPLineEdit)

    self.layout.addWidget(self.usButton)
    self.inputPortLineEdit = qt.QLineEdit()
    self.inputPortLineEdit.setPlaceholderText("18944")
    self.inputPortLineEdit.toolTip = "Put the Port of your ultrasound device here"
    self.usLayout.addRow("Server Port:", self.inputPortLineEdit)

    self.layout.addWidget(self.usButton)
    self.connectButton = qt.QPushButton()
    self.connectButton.text = "Connect"
    self.connectButton.toolTip = "Connects to Ultrasound"
    self.usLayout.addWidget(self.connectButton)
    self.connectButton.connect('clicked(bool)', self.onConnectButtonClicked)

    self.layout.addWidget(self.usButton)
    self.captureButton = qt.QPushButton()
    self.captureButton.text = "Capture Ultrasound Screen Shot"
    self.captureButton.toolTip = "Capture Ultrasound Screen Shot"
    self.usLayout.addWidget(self.captureButton)
    self.captureButton.connect('clicked(bool)', self.onCaptureButtonClicked)

    self.fiducialButton = ctk.ctkCollapsibleButton()
    self.fiducialButton.text = "Registration"
    self.layout.addWidget(self.usButton)
    self.fiducialLayout = qt.QFormLayout(self.fiducialButton)

    self.layout.addWidget(self.fiducialButton)
    self.faducialButton = qt.QPushButton("Set Faducial")  
    self.faducialButton.toolTip = "Creates a faducial to be placed on the straw"
    self.fiducialLayout.addWidget(self.faducialButton)
    self.faducialButton.connect('clicked(bool)', self.onFaducialButtonClicked)

    # Calculate the path of the crosshair model and load it into the scene
    modelPath = os.path.join(os.path.dirname(slicer.modules.guideduscal.path), 'Resources/Models/CrossHair.vtk')
    success, self.crosshairNode = slicer.util.loadModel(modelPath, True)

    #adding an observer to scene to listen for mrml node 
    self.sceneObserverTag = slicer.mrmlScene.AddObserver(slicer.mrmlScene.NodeAddedEvent, self.onNodeAdded)

  def onConnectButtonClicked(self):
    self.connectorNode = slicer.vtkMRMLIGTLConnectorNode()
    slicer.mrmlScene.AddNode(self.connectorNode)
    self.connectorNode.SetTypeClient(self.inputIPLineEdit.text, int(self.inputPortLineEdit.text));
    self.connectorNode.Start()

  def onCaptureButtonClicked(self):
    self.connectorNode.Stop()
   
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
    displayNode.SetSelectedColor(0, 0, 1)

    self.fiducialNode.GetMarkupPoint(self.fiducialNode.GetNumberOfMarkups()-1,0, arr)
    print(arr)

    # self.layout.addWidget(self.fiducialButton)
    # self.crossMarkerButton = qt.QPushButton("Set Straw center Marker")  
    # self.crossMarkerButton.toolTip = "Creates a marker to be placed on the straw"
    # self.fiducialLayout.addWidget(self.crossMarkerButton)
    # self.crossMarkerButton.connect('clicked(bool)', self.onCrossMarkerClicked)

  # def onCrossMarkerClicked(self):
  #   # Create a linear transform node and pair it to the model node 
  #   self.crosshairTransformNode = slicer.vtkMRMLLinearTransformNode()
  #   slicer.mrmlScene.AddNode(self.crosshairTransformNode)

  #   self.crosshairNode.SetAndObserveTransformNodeID(self.crosshairTransformNode.GetID())
  #   self.crosshairNode.GetDisplayNode().SetColor(0, 1, 1)
  #   self.crosshairNode.GetDisplayNode().SetSliceIntersectionVisibility(1)

  #   mat = vtk.vtkMatrix4x4()
  #   mat.SetElement(0,3,-250)
  #   mat.SetElement(1,3,-250)
  #   self.crosshairTransformNode.SetMatrixTransformToParent(mat)




# class GuidedUSCalLogic(ScriptedLoadableModuleLogic):





   