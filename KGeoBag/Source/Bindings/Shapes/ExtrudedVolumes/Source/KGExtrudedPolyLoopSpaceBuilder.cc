#include "KGExtrudedPolyLoopSpaceBuilder.hh"
#include "KGInterfaceBuilder.hh"

namespace katrin
{

    static const int sKGExtrudedPolyLoopSpaceBuilder =
        KGInterfaceBuilder::ComplexElement< KGExtrudedPolyLoopSpace >( "extruded_poly_loop_space" );

    static const int sKGExtrudedPolyLoopSpaceBuilderStructure =
        KGExtrudedPolyLoopSpaceBuilder::Attribute< string >( "name" ) +
        KGExtrudedPolyLoopSpaceBuilder::Attribute< double >( "zmin" ) +
        KGExtrudedPolyLoopSpaceBuilder::Attribute< double >( "zmax" ) +
        KGExtrudedPolyLoopSpaceBuilder::Attribute< unsigned int >( "extruded_mesh_count" ) +
        KGExtrudedPolyLoopSpaceBuilder::Attribute< double >( "extruded_mesh_power" ) +
        KGExtrudedPolyLoopSpaceBuilder::Attribute< unsigned int >( "flattened_mesh_count" ) +
        KGExtrudedPolyLoopSpaceBuilder::Attribute< double >( "flattened_mesh_power" ) +
        KGExtrudedPolyLoopSpaceBuilder::ComplexElement< KGPlanarPolyLoop >( "poly_loop" );

}
