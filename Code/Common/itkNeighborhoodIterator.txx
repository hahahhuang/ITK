/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkNeighborhoodIterator.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkNeighborhoodIterator_txx
#define _itkNeighborhoodIterator_txx
namespace itk {

template<class TImage>
void
NeighborhoodIterator<TImage>
::PrintSelf(std::ostream &os, Indent indent) const
{
  os << indent;
  os << "NeighborhoodIterator {this= " << this << "}" << std::endl;
  Superclass::PrintSelf(os, indent.GetNextIndent());
}

template<class TImage>
void
NeighborhoodIterator<TImage>
::SetNeighborhood(const NeighborhoodType &N)
{
  Iterator this_it;
  const Iterator _end = Superclass::End();
  typename NeighborhoodType::ConstIterator N_it;
  N_it = N.Begin();
  
  for (this_it = Superclass::Begin(); this_it < _end; this_it++, N_it++)
    {
      **this_it = *N_it;
    }
}

} // namespace itk

#endif
