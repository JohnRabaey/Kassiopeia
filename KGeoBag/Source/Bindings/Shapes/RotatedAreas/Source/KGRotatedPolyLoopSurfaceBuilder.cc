#include "KGRotatedPolyLoopSurfaceBuilder.hh"
#include "KGInterfaceBuilder.hh"

namespace katrin
{

    static const int sKGRotatedPolyLoopSurfaceBuilder =
        KGInterfaceBuilder::ComplexElement< KGRotatedPolyLoopSurface >( "rotated_poly_loop_surface" );

    static const int sKGRotatedPolyLoopSurfaceBuilderStructure =
        KGRotatedPolyLoopSurfaceBuilder::Attribute< string >( "name" ) +
        KGRotatedPolyLoopSurfaceBuilder::Attribute< unsigned int >( "rotated_mesh_count" ) +
        KGRotatedPolyLoopSurfaceBuilder::ComplexElement< KGPlanarPolyLoop >( "poly_loop" );

}
