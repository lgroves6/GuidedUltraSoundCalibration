cmake_minimum_required(VERSION 3.5)

project(GuidedUSCalibration)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/GuidedUltrasoundCalibration")
set(EXTENSION_CATEGORY "IGT")
set(EXTENSION_CONTRIBUTORS "Leah Groves(Roberts Research Institute), Adam Rankin(Roberts Research Institute), Elvis Chen(Roberts Research Institute)")
set(EXTENSION_DESCRIPTION "This is a guided ultrasound calibration algorithm")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/GuidedUSCalibration.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/GuidedUltrasoundCalibration/Screenshots/1.png")
set(EXTENSION_DEPENDS "SlicerOpenCV SlicerIGT") # Specified as a space separated string, a list or 'NA' if any

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
find_package(SlicerOpenCV REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(GuidedUSCal)
add_subdirectory(GuidedUSCalAlgo)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_GENERATE_CONFIG})
include(${Slicer_EXTENSION_CPACK})
