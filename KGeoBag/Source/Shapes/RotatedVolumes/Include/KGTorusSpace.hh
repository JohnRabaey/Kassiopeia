#ifndef KGTORUSSPACE_HH_
#define KGTORUSSPACE_HH_

#include "KGRotatedCircleSpace.hh"

namespace KGeoBag
{

    class KGTorusSpace :
        public KGRotatedCircleSpace
    {
        public:
            KGTorusSpace();
            virtual ~KGTorusSpace();

        public:
            void Z( const double& aZ );
            void R( const double& anR );
            void Radius( const double& aRadius );
            void ToroidalMeshCount( const unsigned int& aToroidalMeshCount );
            void AxialMeshCount( const unsigned int& anAxialMeshCount );

            const double& Z() const;
            const double& R() const;
            const double& Radius() const;
            const unsigned int& ToroidalMeshCount() const;
            const unsigned int& AxialMeshCount() const;

        private:
            double fZ;
            double fR;
            double fRadius;
            unsigned int fToroidalMeshCount;
            unsigned int fAxialMeshCount;

        public:
            class Visitor
            {
                public:
                    Visitor();
                    virtual ~Visitor();

                    virtual void VisitTorusSpace( KGTorusSpace* aTorusSpace ) = 0;
            };

        public:
            virtual void VolumeInitialize( BoundaryContainer& aBoundaryContainer ) const;
            virtual void VolumeAccept( KGVisitor* aVisitor );
    };

}

#endif
