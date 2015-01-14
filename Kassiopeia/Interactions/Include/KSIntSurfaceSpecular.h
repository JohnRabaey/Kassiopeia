#ifndef Kassiopeia_KSIntSurfaceSpecular_h_
#define Kassiopeia_KSIntSurfaceSpecular_h_

#include "KSSurfaceInteraction.h"

#include "KField.h"

namespace Kassiopeia
{

    class KSStep;

    class KSIntSurfaceSpecular :
        public KSComponentTemplate< KSIntSurfaceSpecular, KSSurfaceInteraction >
    {
        public:
            KSIntSurfaceSpecular();
            KSIntSurfaceSpecular( const KSIntSurfaceSpecular& aCopy );
            KSIntSurfaceSpecular* Clone() const;
            virtual ~KSIntSurfaceSpecular();

        public:
            void ExecuteInteraction( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries );
            void ExecuteReflection( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries );
            void ExecuteTransmission( const KSParticle& anInitialParticle, KSParticle& aFinalParticle, KSParticleQueue& aSecondaries );

        public:
            ;K_SET_GET( double, Probability )
            ;K_SET_GET( double, ReflectionLoss )
            ;K_SET_GET( double, TransmissionLoss )
    };

}

#endif
