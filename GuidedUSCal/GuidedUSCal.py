import os
import unittest
import vtk, qt, ctk, slicer
from slicer.ScriptedLoadableModule import *
import logging

# This is the basis of your module and will load the basic module GUI 
class GuidedUSCal(ScriptedLoadableModule):
  # comment string showing where to obtain this 
  """Uses ScriptedLoadableModuleWidget base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """ 
  #define some things about your module here 
  def __init__(self, parent):
    ScriptedLoadableModule.__init__(self, parent)
    #Module title 
    self.parent.title= "US Calibration Module"
    #where in the module list it will appear 
    self.parent.categories=["Examples"]
    #who wrote it 
    self.parent.contributors=["Leah Groves"]
    # discriptor string telling what the module does 
    self.parent.helpText="""
This is a scripted loadable module that performs Ultrsound Calibration
"""
    self.parent.helpText = self.getDefaultModuleDocumentationLink()
    
#this contains the widget (GUI) portion of the code         
class GuidedUSCalWidget(ScriptedLoadableModuleWidget):
  """Uses ScriptedLoadableModuleWidget base class, available at:
  https://github.com/Slicer/Slicer/blob/master/Base/Python/slicer/ScriptedLoadableModule.py
  """
  def __init__(self, parent=None):
    # set variables here
    ScriptedLoadableModuleWidget.__init__(self, parent)
    #sets important variable equal to 0 
    self.fiducialNode = None

  def setup(self):
    # this is the function that implements all GUI 
    ScriptedLoadableModuleWidget.setup(self)

    #This sets the view being used to the red view only 
    redLayout = slicer.app.layoutManager()
    redLayout.setLayout(slicer.vtkMRMLLayoutNode.SlicerLayoutOneUpRedSsetliceView)
    #redLayout.setLayout(slicer.vtkMRMLLayoutNode(6))

    #This code block creates a collapsible button 
    #This defines which type of button you are using 
    self.usButton = ctk.ctkCollapsibleButton()
    #This is what the button will say 
    self.usButton.text = "Ultrasound Information"
    #Thiss actually creates that button
    self.layout.addWidget(self.usButton)
    #This creates a variable that describes layout within this collapsible button 
    self.usLayout = qt.QFormLayout(self.usButton)

    #This creates a new widget with the usbutton 
    self.layout.addWidget(self.usButton)
    #This descirbes the type of widget 
    self.inputIPLineEdit = qt.QLineEdit()
    #This sets a placehoder example of what should be inputted to the line edit 
    self.inputIPLineEdit.setPlaceholderText("127.0.0.1")
    #This is the help tooltip 
    self.inputIPLineEdit.toolTip = "Put the IP address of your ultrasound device here"
    #This is the text that is input inot the line 
    self.usLayout.addRow("Server IP:", self.inputIPLineEdit)

    #This code block is the exact same as the one above only it asks for the server port 
    self.layout.addWidget(self.usButton)
    self.inputPortLineEdit = qt.QLineEdit()
    self.inputPortLineEdit.setPlaceholderText("18944")
    self.inputPortLineEdit.toolTip = "Put the Port of your ultrasound device here"
    self.usLayout.addRow("Server Port:", self.inputPortLineEdit)

    #this creates a different type of widget still within the usButton 
    self.layout.addWidget(self.usButton)
    #This is a push button 
    self.connectButton = qt.QPushButton()
    #This button says connect 
    self.connectButton.text = "Connect"
    #help tooltip that explains the funciton 
    self.connectButton.toolTip = "Connects to Ultrasound"
    #adds the widget to the layout 
    self.usLayout.addWidget(self.connectButton)
    #This says when clicked on run the fnction onConnectButtonClicked
    self.connectButton.connect('clicked(bool)', self.onConnectButtonClicked)

    #This is the exact same as the code block below but it freezes the US to capture a screenshot 
    self.layout.addWidget(self.usButton)
    self.captureButton = qt.QPushButton()
    self.captureButton.text = "Capture Ultrasound Screen Shot"
    self.captureButton.toolTip = "Capture Ultrasound Screen Shot"
    self.usLayout.addWidget(self.captureButton)
    self.captureButton.connect('clicked(bool)', self.onCaptureButtonClicked)

    #This creates another collapsible button
    self.fiducialButton = ctk.ctkCollapsibleButton()
    self.fiducialButton.text = "Registration"
    self.layout.addWidget(self.usButton)
    self.fiducialLayout = qt.QFormLayout(self.fiducialButton)

    # This is another push button 
    self.layout.addWidget(self.fiducialButton)
    self.faducialButton = qt.QPushButton("Set Faducial")  
    self.faducialButton.toolTip = "Creates a faducial to be placed on the straw"
    self.fiducialLayout.addWidget(self.faducialButton)
    #When clicked it runs the function onFaducialButtonClicked
    self.faducialButton.connect('clicked(bool)', self.onFaducialButtonClicked)

    #the code below is neccessary to allow the fiducial to be added 

    # This calculates the path of the crosshair model and load it into the scene
    modelPath = os.path.join(os.path.dirname(slicer.modules.guideduscal.path), 'Resources/Models/CrossHair.vtk')
    success, self.crosshairNode = slicer.util.loadModel(modelPath, True)

    #This adds an observer to scene to listen for mrml node 
    self.sceneObserverTag = slicer.mrmlScene.AddObserver(slicer.mrmlScene.NodeAddedEvent, self.onNodeAdded)

  #This is the function that runs when the connect button is clicked  
  def onConnectButtonClicked(self):
    #creates a connector Node
    self.connectorNode = slicer.vtkMRMLIGTLConnectorNode()
    #Adds this node to the scene, not there is no need for self here as it is its own node
    slicer.mrmlScene.AddNode(self.connectorNode)
    #connects to the system using the typed user input from the lineEdit
    self.connectorNode.SetTypeClient(self.inputIPLineEdit.text, int(self.inputPortLineEdit.text));
    #This starts the connection
    self.connectorNode.Start()

  #This is the function that stops the US stream
  def onCaptureButtonClicked(self):
    #Simply stops this connector node 
    self.connectorNode.Stop()
   
  #This is the function that runs once the fiducial button is pressed
  def onFaducialButtonClicked(self):
    # this line creates the logic for the markup (crosshair) that is being placed 
    #startPlaceMode(0) means only one markup gets places
    slicer.modules.markups.logic().StartPlaceMode(0)

  #this runs when that fiducial node is added 
  @vtk.calldata_type(vtk.VTK_OBJECT)
  def onNodeAdded(self, caller, event, callData):
    # if the node that is created is of type vtkMRMLMarkupsFiducialNODE 
    if type(callData) is slicer.vtkMRMLMarkupsFiducialNode:
      # if there is something in this node 
      if self.fiducialNode is not None:
        # remove the observer 
        self.fiducialNode.RemoveObserver(self.markupAddedObserverTag)
        # set the variable to none 
        self.fiducialNode = None
      #ask adam 
      self.fiducialNode = callData
      #sets a markupObserver to notice when a markup gets added
      self.markupAddedObserverTag = self.fiducialNode.AddObserver(slicer.vtkMRMLMarkupsNode.MarkupAddedEvent, self.onMarkupAdded)
      #this runs the function onMarkupAdded
      self.onMarkupAdded(self.fiducialNode, slicer.vtkMRMLMarkupsNode.MarkupAddedEvent)

  # removes the observer    
  def cleanup(self):
    slicer.mrmlScene.RemoveObserver(self.sceneObserverTag)

  #This gets called when the markup is added
  def onMarkupAdded(self, fiducialNodeCaller, event):
    #set the location and index to zero because its needs to be initialized
    arr=[0,0,0]
    MarkupIndex = 0
    #This checks if there is not a display node 
    if self.fiducialNode.GetDisplayNode() is None:
      #then creates one if that is the case 
      self.fiducialNode.CreateDefaultDisplayNodes()
    # this sets a variable as the display node
    displayNode = self.fiducialNode.GetDisplayNode()
    # This sets the type to be a cross hair
    displayNode.SetGlyphType(3)
    #This sets the size
    displayNode.SetGlyphScale(7.5)
    #this says that you dont want text
    displayNode.SetTextScale(0)
    #this sets the color
    displayNode.SetSelectedColor(0, 0, 1)
    # this saves the location the markup is places
    self.fiducialNode.GetMarkupPoint(self.fiducialNode.GetNumberOfMarkups()-1,0, arr)
    #prints that locatio
    print(arr)

    #this commented code will come in use later for th guidance portion ignore for now 
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





   