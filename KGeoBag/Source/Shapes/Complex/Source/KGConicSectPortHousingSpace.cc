#include "KGConicSectPortHousingSpace.hh"

#include "KGConicSectPortHousingSurface.hh"
#include "KGDisk.hh"

namespace KGeoBag
{
  template <>
  void KGWrappedSpace< KGConicSectPortHousing >::VolumeInitialize(BoundaryContainer& aBoundaryContainer) const
  {
    fObject->Initialize();

    KGConicSectPortHousingSurface* tSurface =
      new KGConicSectPortHousingSurface(fObject);
    aBoundaryContainer.push_back( tSurface );

    {
      KGDisk* disk = new KGDisk();
      disk->SetP0(KThreeVector(0.,0.,fObject->GetZAMain()));
      disk->SetNormal(KThreeVector(0.,0.,-1.));
      disk->SetRadius(fObject->GetRAMain());
      aBoundaryContainer.push_back(disk);
    }

    {
      KGDisk* disk = new KGDisk();
      disk->SetP0(KThreeVector(0.,0.,fObject->GetZBMain()));
      disk->SetNormal(KThreeVector(0.,0.,1.));
      disk->SetRadius(fObject->GetRBMain());
      aBoundaryContainer.push_back(disk);
    }

    for (unsigned int i=0;i<fObject->GetNPorts();i++)
    {
      const KGConicSectPortHousing::Port* p = fObject->GetPort(i);

      if (const KGConicSectPortHousing::OrthogonalPort* o =
	  dynamic_cast<const KGConicSectPortHousing::OrthogonalPort*>(p))
      {
	KGDisk* disk = new KGDisk();
	disk->SetP0(KThreeVector(o->GetASub(0),
				 o->GetASub(1),
				 o->GetASub(2)));
	double normal_local[3] = {0.,0.,1.};
	double normal_global[3];
	o->GetCoordinateTransform()->ConvertToGlobalCoords(normal_local,normal_global,true);
	KThreeVector n(normal_global[0],normal_global[1],normal_global[2]);
	disk->SetNormal(n.Unit());
	disk->SetRadius(o->GetRSub());
	aBoundaryContainer.push_back(disk);
      }
      else if (const KGConicSectPortHousing::ParaxialPort* c =
	       dynamic_cast<const KGConicSectPortHousing::ParaxialPort*>(p))
      {
	KGDisk* disk = new KGDisk();
	disk->SetP0(KThreeVector(c->GetASub(0),
				 c->GetASub(1),
				 c->GetASub(2)));
	disk->SetNormal(KThreeVector(0.,0.,(c->IsUpstream() ? -1. : 1.)));
	disk->SetRadius(c->GetRSub());
	aBoundaryContainer.push_back(disk);
      }
    }

    return;
  }
}
