#ifndef KGSPACEBUILDER_HH_
#define KGSPACEBUILDER_HH_

#include "KComplexElement.hh"

#include "KGCore.hh"
using namespace KGeoBag;

namespace katrin
{

    typedef KComplexElement< KGSpace > KGSpaceBuilder;

    template< >
    inline bool KGSpaceBuilder::AddAttribute( KContainer* anAttribute )
    {
        if( anAttribute->GetName() == "name" )
        {
            anAttribute->CopyTo( fObject, &KGSpace::SetName );
            return true;
        }
        if( anAttribute->GetName() == "node" )
        {
            KGSpace* tSource = KGInterface::GetInstance()->RetrieveSpace( anAttribute->AsReference< string >() );
            if( tSource == NULL )
            {
                return false;
            }

            KGSpace* tClone = tSource->CloneNode();
            tClone->SetName( fObject->GetName() );
            tClone->AddTags( fObject->GetTags() );

            fObject = tClone;
            Set( fObject );

            return true;
        }
        if( anAttribute->GetName() == "tree" )
        {
            KGSpace* tSource = KGInterface::GetInstance()->RetrieveSpace( anAttribute->AsReference< string >() );
            if( tSource == NULL )
            {
                return false;
            }

            KGSpace* tClone = tSource->CloneTree();
            tClone->SetName( fObject->GetName() );
            tClone->AddTags( fObject->GetTags() );

            fObject = tClone;
            Set( fObject );

            return true;
        }
        return false;
    }

    template< >
    inline bool KGSpaceBuilder::AddElement( KContainer* anElement )
    {
        if( anElement->GetName() == "transformation" )
        {
            fObject->Transform( anElement->AsPointer< KTransformation >() );
            return true;
        }
        if( anElement->GetName() == "surface" )
        {
            anElement->ReleaseTo( fObject, &KGSpace::AddChildSurface );
            return true;
        }
        if( anElement->GetName() == "space" || anElement->Is< KGSpace >() )
        {
            anElement->ReleaseTo( fObject, &KGSpace::AddChildSpace );
            return true;
        }
        return false;
    }

}

#endif
