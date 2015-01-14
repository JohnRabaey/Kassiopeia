#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "KFMNamedScalarData.hh"
#include "KFMNamedScalarDataCollection.hh"
#include "KEMFileInterface.hh"

#ifdef KEMFIELD_USE_VTK
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkDoubleArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDiskSource.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkShortArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDataSetMapper.h>
#include <vtkPoints.h>
#include <vtkTriangle.h>
#include <vtkPolygon.h>
#include <vtkLine.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTriangleFilter.h>
#include <vtkStripper.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkActor.h>
#endif /* KEMFIELD_USE_VTK */


using namespace KEMField;

int main(int argc, char** argv)
{

    if(argc != 2){return 1;}

    std::string filename(argv[1]);

    KSAObjectInputNode< KFMNamedScalarDataCollection >* data_node = new KSAObjectInputNode< KFMNamedScalarDataCollection >("data_collection");

    bool result;
    KEMFileInterface::GetInstance()->ReadKSAFile(data_node, filename, result);

    if(!result){return 1;};

    KFMNamedScalarDataCollection* data  = data_node->GetObject();

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

    //Create a vtkPoints object and store the points in it
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    KFMNamedScalarData* x_coord = data->GetDataWithName(std::string("x_coordinate"));
    KFMNamedScalarData* y_coord = data->GetDataWithName(std::string("y_coordinate"));
    KFMNamedScalarData* z_coord = data->GetDataWithName(std::string("z_coordinate"));

    unsigned int n_points = x_coord->GetSize();
    double p[3];
    for(unsigned int i=0; i<n_points; i++)
    {
        p[0] = x_coord->GetValue(i);
        p[1] = y_coord->GetValue(i);
        p[2] = z_coord->GetValue(i);
        points->InsertNextPoint(p);
    }

    // Create a polydata to store everything in
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    // Add the points to the dataset
    polyData->SetPoints(points);

    //collect the rest of the (non-point) scalar data
    unsigned int n_data_sets = data->GetNDataSets();
    for(unsigned int i=0; i<n_data_sets; i++)
    {
        std::string name = data->GetDataSetWithIndex(i)->GetName();
        if( (name != (std::string("x_coordinate") ) ) && (name != (std::string("y_coordinate") ) ) && (name != (std::string("z_coordinate") ) ) )
        {

            vtkSmartPointer<vtkDoubleArray> array;
            array = vtkSmartPointer<vtkDoubleArray>::New();
            array->SetName( (data->GetDataSetWithIndex(i)->GetName()).c_str() );
            array->Initialize();

            unsigned int size = data->GetDataSetWithIndex(i)->GetSize();
            for(unsigned int j=0; j<size; j++)
            {
                array->InsertNextValue( data->GetDataSetWithIndex(i)->GetValue(j) );
            }

            polyData->GetPointData()->AddArray(array);
        }
    }


    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("./test_vtk.vtk");
    writer->SetInput(polyData);
    writer->Write();


    return 0;
}
