/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkImageLinearIteratorWithIndex.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkImageLinearIteratorWithIndex_txx
#define _itkImageLinearIteratorWithIndex_txx

#include "itkSimpleImageRegionIterator.h"

namespace itk
{




//----------------------------------------------------------------------
//  Pass to the first pixel on the next line
//----------------------------------------------------------------------
template<class TImage>
void 
ImageLinearIteratorWithIndex<TImage>
::NextLine(void)
{

  m_PositionIndex[m_Direction] = m_BeginIndex[m_Direction];   
  m_Position -= m_OffsetTable[ m_Direction+1 ]; 
  

  for( unsigned int n=0; n<TImage::ImageDimension; n++ )
  {

    m_Remaining = false;
    
    if( n == m_Direction ) 
    {
      continue;
    }
    
    m_PositionIndex[ n  ]++;
    if( m_PositionIndex[n] <  m_EndIndex[ n ] )
    {
      m_Position += m_OffsetTable[ n ];
      m_Remaining = true;
      break;
    }
    else 
    {
      m_Position -= m_OffsetTable[ n ] * ( m_Region.GetSize()[n]-1 );
      m_PositionIndex[ n ] = m_BeginIndex[ n ]; 
    }
  }
}



//----------------------------------------------------------------------
//  Pass to the last pixel on the previous line
//----------------------------------------------------------------------
template<class TImage>
void 
ImageLinearIteratorWithIndex<TImage>
::PreviousLine(void)
{

  m_PositionIndex[m_Direction] = m_EndIndex[m_Direction]-1;   
  m_Position += m_OffsetTable[ m_Direction+1 ]; 
  

  for( unsigned int n=0; n<TImage::ImageDimension; n++ )
  {

    m_Remaining = false;
    
    if( n == m_Direction ) 
    {
      continue;
    }
    
    m_PositionIndex[ n  ]--;
    if( m_PositionIndex[ n ] >=  m_BeginIndex[ n ] )
    {
      m_Position -= m_OffsetTable[ n ];
      m_Remaining = true;
      break;
    }
    else 
    {
      m_Position += m_OffsetTable[ n ] * ( m_Region.GetSize()[n]-1 );
      m_PositionIndex[ n ] = m_EndIndex[ n ] - 1; 
    }
  }
}




//----------------------------------------------------------------------
//  Advance along the line
//----------------------------------------------------------------------
template<class TImage>
ImageLinearIteratorWithIndex<TImage>  & 
ImageLinearIteratorWithIndex<TImage>
::operator++()
{
  m_PositionIndex[m_Direction]++;
  m_Position += m_Jump;
  return *this;
}


//----------------------------------------------------------------------
//  Advance along the line
//----------------------------------------------------------------------
template<class TImage>
ImageLinearIteratorWithIndex<TImage>  & 
ImageLinearIteratorWithIndex<TImage>
::operator--()
{
  m_PositionIndex[m_Direction]--;
  m_Position -= m_Jump;
  return *this;
}



//----------------------------------------------------------------------
//  Go to the first pixel of the current line
//----------------------------------------------------------------------
template<class TImage>
void 
ImageLinearIteratorWithIndex<TImage>
::GoToBeginOfLine(void)
{

  long distanceToBegin = 
                m_PositionIndex[ m_Direction ] - m_Begin[ m_Direction ];

  m_Position -= m_Jump * distanceToBegin; 

  m_PositionIndex[m_Direction] = m_Begin[m_Direction];   
  
}




//----------------------------------------------------------------------
//  Pass to the past last pixel of the current line
//----------------------------------------------------------------------
template<class TImage>
void 
ImageLinearIteratorWithIndex<TImage>
::GoToEndOfLine(void)
{

  long distanceToEnd = 
                m_EndIndex[ m_Direction ] - m_PositionIndex[ m_Direction ];


  m_Position += m_Jump * distanceToEnd; 

  m_PositionIndex[m_Direction] = m_EndIndex[m_Direction];   
  
}






} // end namespace itk

#endif
