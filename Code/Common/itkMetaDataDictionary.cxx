/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkMetaDataDictionary.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkMetaDataDictionary.h"
#include <map>

namespace itk{

class MetaDataDictionaryMapType 
  : public std::map<std::string, MetaDataObjectBase::Pointer>
{
};


MetaDataDictionary
::MetaDataDictionary()
{
  m_Dictionary = new MetaDataDictionaryMapType;
}

MetaDataDictionary
::~MetaDataDictionary()
{
  if (m_Dictionary)
    {
    delete m_Dictionary;
    m_Dictionary = 0;
    }
}

void
MetaDataDictionary
::Print(std::ostream& os) const
{
  for(MetaDataDictionaryMapType::const_iterator it=m_Dictionary->begin();
      it != m_Dictionary->end();
      it++)
    {
    os << it->first <<  "  " ;
    it->second->Print(os);
    }
}

MetaDataObjectBase::Pointer &
MetaDataDictionary
::operator [](const std::string &key)
{
  return (*m_Dictionary)[key];
}

bool
MetaDataDictionary
::HasKey(const std::string &key)
{
  return m_Dictionary->find(key) != m_Dictionary->end();
}
}; // namespace
