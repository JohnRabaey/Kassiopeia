#include "KGRotatedLineSegmentSurfaceBuilder.hh"
#include "KGInterfaceBuilder.hh"

namespace katrin
{

    static const int sKGRotatedLineSegmentSurfaceBuilder =
        KGInterfaceBuilder::ComplexElement< KGRotatedLineSegmentSurface >( "rotated_line_segment_surface" );

    static const int sKGRotatedLineSegmentSurfaceBuilderStructure =
        KGRotatedLineSegmentSurfaceBuilder::Attribute< string >( "name" ) +
        KGRotatedLineSegmentSurfaceBuilder::Attribute< unsigned int >( "rotated_mesh_count" ) +
        KGRotatedLineSegmentSurfaceBuilder::ComplexElement< KGPlanarLineSegment >( "line_segment" );

}
