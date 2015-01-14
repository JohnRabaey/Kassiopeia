#ifndef Kassiopeia_KSSpaceNavigator_h_
#define Kassiopeia_KSSpaceNavigator_h_

#include "KSComponentTemplate.h"
#include "KSTrajectory.h"
#include "KSParticle.h"

namespace Kassiopeia
{

    class KSSpaceNavigator :
        public KSComponentTemplate< KSSpaceNavigator >
    {
        public:
            KSSpaceNavigator();
            virtual ~KSSpaceNavigator();

        public:
            virtual void CalculateNavigation(
                const KSTrajectory& aTrajectory,
                const KSParticle& aTrajectoryInitialParticle,
                const KSParticle& aTrajectoryFinalParticle,
                const KThreeVector& aTrajectoryCenter,
                const double& aTrajectoryRadius,
                const double& aTrajectoryStep,
                KSParticle& aNavigationParticle,
                double& aNavigationStep,
                bool& aNavigationFlag
            ) = 0;

            virtual void ExecuteNavigation(
                const KSParticle& anInitialParticle,
                KSParticle& aFinalParticle,
                KSParticleQueue& aSecondaries
            ) const = 0;

            virtual void StartNavigation(
                KSParticle& aParticle,
                KSSpace* aRoot
            ) = 0;

            virtual void StopNavigation(
                KSParticle& aParticle,
                KSSpace* aRoot
            ) = 0;
    };

}

#endif
