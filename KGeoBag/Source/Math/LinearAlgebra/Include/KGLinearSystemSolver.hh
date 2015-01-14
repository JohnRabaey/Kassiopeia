#ifndef KGLinearSystemSolver_HH__
#define KGLinearSystemSolver_HH__

#include "KGArrayMath.hh"

#include <vector>
#include <cmath>

#include "KGVectorOperations.hh"
#include "KGMatrixOperations.hh"
#include "KGMatrixVectorOperations.hh"

namespace KGeoBag
{

/*
*
*@file KGLinearSystemSolver.hh
*@class KGLinearSystemSolver
*@brief interface class to GSL linear algebra routines,
* only intended to solve Ax=b in small dimensions i.e. < 30
* for bouding ball calculations, etc.
*@details
*
*<b>Revision History:<b>
*Date Name Brief Description
*Thu Aug 29 12:51:02 CEST 2013 J. Barrett (barrettj@mit.edu) First Version
*
*/


class KGLinearSystemSolver
{
    public:

        KGLinearSystemSolver(size_t dim);

        virtual ~KGLinearSystemSolver();

        size_t GetDimension() const {return fDim;};


        void SetMatrix(const double* mx);

        void SetMatrixElement(size_t row, size_t col, const double& val);

        void SetBVector(const double* vec);

        void SetBVectorElement(size_t index, const double& val);

        void Reset(); //reset fA, fX, and fB to zero

        void Solve();

        void GetXVector(double* vec) const;

        double GetXVectorElement(size_t i) const;

    private:

        size_t fDim;
        size_t fDimSize[2];

        kg_matrix* fA;
        kg_matrix* fU;
        kg_vector* fX;
        kg_vector* fB;

        //for SVD
        kg_matrix* fV;
        kg_vector* fS;
        kg_vector* fWork;

};

}//end of KGeoBag

#endif /* KGLinearSystemSolver_H__ */
