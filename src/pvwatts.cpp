#include <Rcpp.h>
#include "sscapi.h"

using namespace Rcpp;
using namespace std;


//function issues warnings if using / instead of \\ in filenames.
// still works either way.

//'@export
// [[Rcpp::export]]
NumericVector pvwattstest(CharacterVector filename) {
  ssc_data_t data = ssc_data_create();
  //marshall the filename input
  string str_filename = as<string>(filename[0]);
  const char * char_filename = str_filename.c_str();

  // add data to container
  ssc_data_set_string(data, "solar_resource_file", char_filename);
  ssc_data_set_number(data, "system_capacity", 1.0f); // 1 kW
  ssc_data_set_number(data, "losses", 14.0f);  //losses in %
  ssc_data_set_number(data, "array_type", 0);  // fixed tilt
  ssc_data_set_number(data, "tilt", 20);  // 20 deg tilt
  ssc_data_set_number(data, "azimuth", 180); // facing south
  ssc_data_set_number(data, "adjust:constant", 0.0f); //energy adjustment constant

  // create module
  ssc_module_t module = ssc_module_create( "pvwattsv5" );
  if ( NULL == module )
  {
    ssc_data_free( data );
    Rcpp::stop("error: could not create 'pvwattsv5 module.\n");
    return -1;
  }

  //run module
  if ( ssc_module_exec( module, data ) == 0 )
  {
    ssc_module_free( module );
    ssc_data_free( data );
    Rcpp::stop("Error during simplation.\n");
    return -1;
  }

  // ac variable only
  int len = 0;
  NumericVector res(8760);  // initialize res with len from sdktool
  ssc_number_t *ac = ssc_data_get_array(data, "ac", &len );
  if ( ac != NULL )
  {
    for ( int i=0; i<len; i++ )
    {
      res[i] = ac[i];
    }
  }

  // free module & data
  ssc_module_free(module);
  ssc_data_free(data);

  return res;
}
