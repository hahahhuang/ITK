/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkRigid3DTransform.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkRigid3DTransform_h
#define __itkRigid3DTransform_h

#include <iostream>
#include "itkTransform.h"
#include "itkExceptionObject.h"
#include "vnl/vnl_quaternion.h"
#include "itkMatrix.h"
#include "itkVersor.h"

namespace itk
{

/** \brief Rigid3DTransform of a vector space (e.g. space coordinates)
 *
 * This transform applies a rotation and translation to the space
 *
 * \ingroup Transforms
 */
template < class TScalarType=double >    // Data type for scalars (float or double)
class ITK_EXPORT Rigid3DTransform : 
            public Transform< TScalarType, 
                              3, 3,       // Dimensions of input and output spaces
                              Point< double, 6 >, // a versor plus a vector
                              Matrix<double, 3, 6 > >
{
public:
  /** Standard class typedefs. */
  typedef Rigid3DTransform Self;
  typedef Transform< TScalarType, 3, 3,
                     Point< double, 6 >, 
                     Matrix< double, 3, 6 > >   Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  
  /** Run-time type information (and related methods). */
  itkTypeMacro( Rigid3DTransform, Transform );

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro( Self );

  /** Dimension of the space. */
  enum { InputSpaceDimension = 3,
         OutputSpaceDimension = 3 };

  /** Scalar type. */
  typedef typename Superclass::ScalarType  ScalarType;

  /** Parameters type. */
  typedef typename Superclass::ParametersType  ParametersType;

  /** Jacobian type. */
  typedef typename Superclass::JacobianType  JacobianType;

  /// Standard matrix type for this class
  typedef Matrix<ScalarType, InputSpaceDimension, InputSpaceDimension> MatrixType;

  /// Standard vector type for this class
  typedef Vector<TScalarType, InputSpaceDimension> OffsetType;

  /// Standard vector type for this class
  typedef Vector<TScalarType, InputSpaceDimension> InputVectorType;
  typedef Vector<TScalarType, OutputSpaceDimension> OutputVectorType;

  /// Standard covariant vector type for this class
  typedef CovariantVector<TScalarType, InputSpaceDimension> InputCovariantVectorType;
  typedef CovariantVector<TScalarType, OutputSpaceDimension> OutputCovariantVectorType;

  /// Standard vnl_vector type for this class
  typedef vnl_vector_fixed<TScalarType, InputSpaceDimension> InputVnlVectorType;
  typedef vnl_vector_fixed<TScalarType, OutputSpaceDimension> OutputVnlVectorType;

  /// Standard coordinate point type for this class
  typedef Point<TScalarType, InputSpaceDimension>    InputPointType;
  typedef Point<TScalarType, OutputSpaceDimension>    OutputPointType;

  /// Standard vnl_quaternion type
  typedef vnl_quaternion<TScalarType>           VnlQuaternionType;

  /// Standard Versor type
  typedef Versor<TScalarType>           VersorType;


  /**
   * Get offset of an Rigid3DTransform
   *
   * This method returns the value of the offset of the
   * Rigid3DTransform.
   **/
  const OffsetType & GetOffset(void) const
      { return m_Offset; }


  /**
   * Get rotation MAtrix from an Rigid3DTransform
   *
   * This method returns the value of the rotation of the
   * Rigid3DTransform.
   **/
  const MatrixType & GetRotationMatrix(void) const
    { return m_DirectMatrix; }


  /**
   * Set offset of a Rigid3D Transform
   *
   * This method sets the offset of an Rigid3DTransform to a
   * value specified by the user.
   **/
  void SetOffset(const OffsetType &offset)
      { m_Offset = offset; return; }


  /**
   * Compose with another Rigid3DTransform
   *
   **/
  void Compose(const Self *other, bool pre=false);


  /**
   * Compose the transformation with a translation
   *
   * This method modifies self to include a translation of the
   * origin.  The translation is precomposed with self if pre is
   * true, and postcomposed otherwise.
   **/
  void Translate(const OffsetType &offset, bool pre=false);


  /**
   * Transform by an affine transformation
   *
   * This method applies the affine transform given by self to a
   * given point or vector, returning the transformed point or
   * vector.
   **/
  OutputPointType     TransformPoint(const InputPointType  &point ) const;
  OutputVectorType    TransformVector(const InputVectorType &vector) const;
  OutputVnlVectorType    TransformVector(const InputVnlVectorType &vector) const;

  OutputCovariantVectorType TransformCovariantVector(
                                 const InputCovariantVectorType &vector) const;

  /**
   * Back transform by an affine transformation
   *
   * This method finds the point or vector that maps to a given
   * point or vector under the affine transformation defined by
   * self.  If no such point exists, an exception is thrown.
   **/
  inline InputPointType      BackTransform(const OutputPointType  &point ) const;
  inline InputVectorType     BackTransform(const OutputVectorType &vector) const;
  inline InputVnlVectorType  BackTransform(const OutputVnlVectorType &vector) const;

  inline InputCovariantVectorType BackTransform(
                                     const OutputCovariantVectorType &vector) const;

  /**
   * Print contents of an Rigid3DTransform
   **/
  void PrintSelf(std::ostream &os, Indent indent) const;

  /**
   * Find inverse of an affine transformation
   *
   * This method creates and returns a new Rigid3DTransform object
   * which is the inverse of self.  If self is not invertible,
   * an exception is thrown.
   **/
  Pointer Inverse( void ) const;

protected:
  Rigid3DTransform();
  ~Rigid3DTransform();

  // matrix representation of the rotation
  // Should be protected in order to be modified 
  // by derived classes that instantiate an interface
  // to rotation computation
  MatrixType          m_DirectMatrix;   

  // representation of the inverse rottion
  MatrixType          m_InverseMatrix; 

private:
  Rigid3DTransform(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  // Offset of the transformation
  OffsetType          m_Offset;   

}; //class Rigid3DTransform


}  // namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkRigid3DTransform.txx"
#endif

#endif /* __itkRigid3DTransform_h */
