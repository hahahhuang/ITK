/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkNeighborhoodInnerProduct.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNeighborhoodInnerProduct_txx
#define __itkNeighborhoodInnerProduct_txx

#include "itkNumericTraits.h"

namespace itk {

template<class TImage, class TOperator, class TComputation>
typename NeighborhoodInnerProduct<TImage, TOperator, TComputation>::OutputPixelType
NeighborhoodInnerProduct<TImage, TOperator, TComputation>
::operator()(const ConstNeighborhoodIterator<TImage> &n,
             const Neighborhood<OperatorPixelType, ImageDimension> &op) const
{
  typedef ConstNeighborhoodIterator<TImage> Neighborhood_t;
  typedef Neighborhood<OperatorPixelType, ImageDimension> Operator_t;
  
  OutputPixelType sum = NumericTraits<OutputPixelType>::Zero;
  typename Neighborhood_t::ConstIterator n_it;
  typename Operator_t::ConstIterator o_it;
  
  n_it = n.Begin();
  const typename Operator_t::ConstIterator op_end = op.End();
  for (o_it = op.Begin(); o_it < op_end; ++o_it, ++n_it)
    {
    sum += *o_it * **n_it;
    }

  return sum;
}

template<class TImage, class TOperator, class TComputation>
typename NeighborhoodInnerProduct<TImage, TOperator, TComputation>::OutputPixelType
NeighborhoodInnerProduct<TImage, TOperator, TComputation>
::operator()(const std::slice &s,
             const ConstNeighborhoodIterator<TImage> &n,
             const Neighborhood<OperatorPixelType, ImageDimension> &op) const
{
  typedef ConstNeighborhoodIterator<TImage> Neighborhood_t;
  typedef Neighborhood<OperatorPixelType, ImageDimension> Operator_t;
  
  OutputPixelType sum = NumericTraits<OutputPixelType>::Zero;
  ConstSliceIterator<ImagePixelType *, Neighborhood_t> s_it(&n, s);
  typename Operator_t::ConstIterator o_it;

  s_it = s_it.Begin();
  const typename Operator_t::ConstIterator op_end = op.End();
  for (o_it = op.Begin(); o_it < op_end; ++o_it, ++s_it)
    {
    sum += *o_it * **s_it;
    }

  return sum;
}

template<class TImage, class TOperator, class TComputation>
typename SmartNeighborhoodInnerProduct<TImage, TOperator, TComputation>::OutputPixelType
SmartNeighborhoodInnerProduct<TImage, TOperator, TComputation>
::operator()(const std::slice &s,
             /*           const ImageBoundaryCondition<TImage> *,*/
             const ConstSmartNeighborhoodIterator<TImage> &it,
             const Neighborhood<OperatorPixelType, ImageDimension>
             &op) const
{
  typedef ConstSmartNeighborhoodIterator<TImage> Neighborhood_t;
  typedef Neighborhood<OperatorPixelType, ImageDimension> Operator_t;

  typename Operator_t::ConstIterator o_it;
  OutputPixelType sum = NumericTraits<OutputPixelType>::Zero;

  o_it = op.Begin();
  const typename Operator_t::ConstIterator op_end = op.End();

  for ( unsigned int i = s.start(); o_it < op_end; i+=s.stride(), ++o_it )
    {
    sum += *o_it * it.GetPixel(i);
    }
  

   return sum;
} 

}// end namespace itk
#endif
