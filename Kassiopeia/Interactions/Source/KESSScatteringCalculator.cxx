#include "KESSScatteringCalculator.h"
#include "KTextFile.h"
#include "KFile.h"
#include "KSInteractionsMessage.h"
#include <map>
#include "KThreeVector.hh"
using KGeoBag::KThreeVector;
#include "KConst.h"
using katrin::KConst;

namespace Kassiopeia
{

    KESSScatteringCalculator::KESSScatteringCalculator() :
            fInteraction( "none" ),
            fIonisationCalculator( NULL ),
            fRelaxationCalculator( NULL )
    {
    }

    KESSScatteringCalculator::~KESSScatteringCalculator()
    {
    }


    void KESSScatteringCalculator::ReadMFP( std::string data_filename,
                                            std::map< double, double > &MapForTables )
    {
        char line[ 196 ];
        double one = 0, two = 0, three = 0;

        std::string myPathToTable = DATA_DEFAULT_DIR;

        std::string UnusedReturnValue;
        FILE *MapFile = fopen( (myPathToTable + "/" + data_filename).c_str(), "r" );

        if( MapFile == 0 )
        {
            intmsg( eError ) << "FILE " << myPathToTable + "/" + data_filename << " NOT FOUND!\n"
                             << ret << "CHECK YOUR IO CONFIGFILE FOR DATA DIRECTORY" << eom;
        }

        for( unsigned int i = 0; i < 2; i++ )
        {
            UnusedReturnValue = fgets( line, 195, MapFile );
        }

        while( fgets( line, 195, MapFile ) != NULL )
        {            
            sscanf( line, "%lf %lf %lf", &one, &two, &three );
            if( feof( MapFile ) == false )
            {
                MapForTables.insert( std::pair< double, double >( one, two ) );
            }
        }
    }

    void KESSScatteringCalculator::ReadPDF( std::string data_filename,
                                            std::map< double, std::vector< std::vector< double > > > &MapForTables )
    {
        char line[ 196 ];
        double one = 0, two = 0, three = 0;

        std::string myPathToTable = DATA_DEFAULT_DIR;

        std::string UnusedReturnValue;

        double oldOne = 0.;

        std::vector< std::vector< double > > elScTable;
        vector< double > theta; //
        vector< double > integralTheta; //

        //change filename here
        FILE *elasticTable = fopen( (myPathToTable + "/" + data_filename).c_str(), "r" );

        if( elasticTable == 0 )
        {
            intmsg( eError ) << "FILE " << myPathToTable + "/" + data_filename << " NOT FOUND!\n"
                             << ret << "CHECK YOUR IO CONFIGFILE FOR DATA DIRECTORY" << eom;
        }
        for( unsigned int i = 0; i < 3; i++ )
        {
            UnusedReturnValue = fgets( line, 195, elasticTable );
        }
        while( fgets( line, 195, elasticTable ) != NULL )
        {            
            sscanf( line, "%lf %lf %lf", &one, &two, &three );
            if( feof( elasticTable ) == false )
            {
                //if all values for one energy are read in
                //save the vectors to the big vector
                //make a entry in the map for faster searching
                //clear the value tables
                if( one != oldOne && oldOne > 0. )
                {
                    elScTable.push_back( theta );
                    elScTable.push_back( integralTheta );

                    MapForTables.insert( std::pair< double, std::vector< std::vector< double > > >( oldOne, elScTable ) );

                    theta.clear();
                    integralTheta.clear();
                    elScTable.clear();
                }
                theta.push_back( two );
                integralTheta.push_back( three );
            }
            oldOne = one;
        }
        fclose( elasticTable );
    }
}

/* namespace Kassiopeia */

