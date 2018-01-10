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

// .NAME PointToLineRegistration - class for performing point to line registration 
// .SECTION Description
// Performs a point to line registration

#ifndef __PointToLineRegistration_h
#define __PointToLineRegistration_h

 class PointToLineRegistration
 {
 public:
   void AddPoint(float x, float y, float z);
   void AddLine(float originX, float originY, float originZ, float directionI, float directionJ, float directionK)
   void Reset();
   void SetTolerance(float arg);
   float GetTolerance() const;
   unsigned int Count() const
   vtkMatrix4x4* Compute(float& outError)
 public:
   PointToLineRegistration(const std::vector<Point>& points, const std::vector<Line>& lines);
   PointToLineRegistration();
   ~PointToLineRegistration()
 protected:
   std::vector<Point>      m_points;
   std::vector<Line>       m_lines
   float                   m_tolerance = 1e-4f;
 };

#endif
 