/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkBloxCoreAtomItem.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkBloxCoreAtomItem_h
#define __itkBloxCoreAtomItem_h

#include "vnl/vnl_vector_fixed.h"
#include "itkBloxBoundaryPointItem.h"
#include "itkBloxItem.h"

namespace itk
{

/**
 * \class BloxCoreAtomItem
 * \brief A core atom object, stored in a BloxPixel
 *
 * A core atom is two boundary points whose gradients face each other
 * They store pointers to the two boundary points and a vnl_vector_fixed
 * representing the "center" of the core atom (i.e. the midpoint along the
 * vector between the two boundary points).
 * \ingroup ImageObjects
 * */

template <unsigned int VImageDimension>
class BloxCoreAtomItem: public BloxItem
{
public:
  /** The point type used to store the position of the CoreAtomItem. */
  typedef Point<double, VImageDimension> TPositionType;

  /** The type of boundary point item we store pointers to. * */
  typedef BloxBoundaryPointItem<VImageDimension> TBPItemType;

  /** Set the position of the first boundary point in physical space. */
  void SetBoundaryPointA(TBPItemType* pointA)
    { m_BoundaryPointA = pointA; }

  /** Get the position of the first boundary point in physical space. */
  TBPItemType* GetBoundaryPointA()
    { return m_BoundaryPointA; }

  /** Set the position of the second boundary point in physical space. */
  void SetBoundaryPointB(TBPItemType* pointB)
    { m_BoundaryPointB = pointB; }

  /** Get the position of the first boundary point in physical space. */
  TBPItemType* GetBoundaryPointB()
    { return m_BoundaryPointB; }

  /** Set the position of the center of the core atom in physical space. */
  void SetCenterPosition(TPositionType pos)
    { m_CenterPosition = pos; }

  /** Get the position of the center of the core atom in physical space. */
  TPositionType GetCenterPosition()
    {return m_CenterPosition; }

  /** Set the diameter of the atom. */
  void SetDiameter(double diameter)
    { m_Diameter = diameter; }

  /** Get the diameter. */
  double GetDiameter()
    {return m_Diameter; }

  /** Calculate the position of the center of the core atom in physical
   * space (assumes that the two boundary points are initialized)
   * Also calculates the core atom's diameter
   * This function is not often used because center and diameter
   * are usually initialized via set() functions when the core atom
   * is created elsewhere. */
  void CalcCenterAndDiameter();
  
  BloxCoreAtomItem();
  ~BloxCoreAtomItem();

private:
  /** The position of the center of the core atom. */
  TPositionType m_CenterPosition;

  /** The diameter of the core atom
   * This is the magnitude of the vector from boundary points A->B. */
  double m_Diameter;

  /** The first boundary point that's part of the core atom. */
  TBPItemType* m_BoundaryPointA;

  /** The second boundary point that's part of the core atom. */
  TBPItemType* m_BoundaryPointB;

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBloxCoreAtomItem.txx"
#endif

#endif
