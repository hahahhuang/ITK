/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkNeighborhoodInnerProduct.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNeighborhoodInnerProduct_h
#define __itkNeighborhoodInnerProduct_h

#include "itkNeighborhoodIterator.h"
#include "itkSmartNeighborhoodIterator.h"
#include "itkNeighborhood.h"
#include "itkConstSliceIterator.h"
#include "itkImageBoundaryCondition.h"

namespace itk {
  
/** \class NeighborhoodInnerProduct
 *
 * This class defines the inner product operation between an
 * itk::Neighborhood and and itk::NeighborhoodOperator.  The
 * operator() method is overloaded to support various types of
 * neighborhoods as well as inner products with slices of
 * neighborhoods. The second template parameter allows you to set the
 * value type of the operator. The third templage parameter allows you
 * to set the value type used as the return type of the inner product
 * calculation. The operator value type defaults to the image pixel
 * type and the output value type defaults to the operator type.
 *
 * \ingroup Operators
 */
template<class TImage, class TOperator=ITK_TYPENAME TImage::PixelType, class TComputation=TOperator>
class NeighborhoodInnerProduct
{
public:
  /** Capture some typedefs from the template parameters. */
  typedef typename TImage::PixelType ImagePixelType;
  typedef TOperator OperatorPixelType;
  typedef TComputation OutputPixelType;
    
  /** Capture some typedefs from the template parameters. */
  enum {ImageDimension = TImage::ImageDimension};

  /** Reference oeprator. */
  OutputPixelType operator()(const ConstNeighborhoodIterator<TImage> &it,
                       const Neighborhood<OperatorPixelType, ImageDimension>
                       &op) const;
  OutputPixelType operator()(const std::slice &s,
                       const ConstNeighborhoodIterator<TImage> &it,
                       const Neighborhood<OperatorPixelType, ImageDimension>
                       &op) const;
  };

template<class TImage, class TOperator=ITK_TYPENAME TImage::PixelType, class TComputation=TOperator>
class SmartNeighborhoodInnerProduct
{
public:
  /** Capture some typedefs from the template parameters. */
  typedef typename TImage::PixelType ImagePixelType;
  typedef TOperator OperatorPixelType;
  typedef TComputation OutputPixelType;
  
  /** Capture some typedefs from the template parameters. */
  enum {ImageDimension = TImage::ImageDimension};

  /** Reference oeprator. */
  OutputPixelType operator()(const std::slice &s,
                       const ConstSmartNeighborhoodIterator<TImage> &it,
                       const Neighborhood<OperatorPixelType, ImageDimension>
                       &op) const;
  OutputPixelType operator()(const ConstSmartNeighborhoodIterator<TImage> &it,
                       const Neighborhood<OperatorPixelType, ImageDimension>
                       &op) const
    {
      return this->operator()(std::slice(0, it.Size(), 1), it, op);
    }
  };
  
  
  
} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkNeighborhoodInnerProduct.txx"
#endif

#endif
