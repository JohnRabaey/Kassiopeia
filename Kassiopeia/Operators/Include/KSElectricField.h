#ifndef Kassiopeia_KSElectricField_h_
#define Kassiopeia_KSElectricField_h_

#include "KSComponentTemplate.h"

#include "KThreeVector.hh"
using KGeoBag::KThreeVector;

#include "KThreeMatrix.hh"
using KGeoBag::KThreeMatrix;

namespace Kassiopeia
{

    class KSElectricField :
        public KSComponentTemplate< KSElectricField >
    {
        public:
            KSElectricField();
            virtual ~KSElectricField();

        public:
            virtual void CalculatePotential( const KThreeVector& aSamplePoint, const double& aSampleTime, double& aPotential ) = 0;
            virtual void CalculateField( const KThreeVector& aSamplePoint, const double& aSampleTime, KThreeVector& aField ) = 0;
    };

}

#endif
