#include <Rcpp.h>
#include "sscapi.h"
using namespace Rcpp;
using namespace std;


/**
 * The purpose of these functions is to serve as a template for getting data into
 * and out of the ssc data structures. They all have the same basic form, taking
 * the R equivalent, putting into a ssc_data_t, retrieving the data, marshalling
 * it back into a data structure for R and returning it.
 *
 * numeric: ssc equiv is an ssc_number_t
 * character: ssc equiv requires a *char. Looks like the easiest way is to pass
 *   the character from R into a std::string, and convert that to a *char
 * logical: C++ has a logical data type (bool), C doesn't though, and it looks
 *   like it can use implicit type conversion with numeric.
 * numeric vector: ssc equiv is an array
 *
 * Don't forget to do ssc_data_free() in each case, including on errors.
 */


//'@export
// [[Rcpp::export]]
NumericVector dataiotest_num(NumericVector x)
{
  ssc_data_t data = ssc_data_create();
  ssc_number_t system_capacity = x[0];  // convert the NumericVector to ssc_number_t
  ssc_data_set_number(data, "system_capacity", system_capacity);
  ssc_number_t res;
  NumericVector res_nv = NumericVector::create(0);
  if( ssc_data_get_number(data, "system_capacity", &res))
    res_nv[0] = res;
  else
  {
    ssc_data_free( data );
    stop("Didnt work");
  }
  ssc_data_free( data );
  return res_nv;
}

//'@export
// [[Rcpp::export]]
CharacterVector dataiotest_char(CharacterVector x)
{
  ssc_data_t data = ssc_data_create();
  // CharacterVector -> std::string -> * char
  string str_x = as<string>(x[0]);
  const char *char_x = str_x.c_str();

  ssc_data_set_string(data, "solar_resource_file", char_x);
  const char *res = ssc_data_get_string(data, "solar_resource_file");
  string str_res(res);

  CharacterVector res_cv = CharacterVector::create("");
  res_cv[0] = str_res;

  ssc_data_free(data);
  return res_cv;
}

//'@export
// [[Rcpp::export]]
LogicalVector dataiotest_log(LogicalVector x)
{
  ssc_data_t data = ssc_data_create();
  ssc_number_t x_num = x[0];
  //implicit type conversion?
  ssc_data_set_number(data, "system_use_lifetime_output", x_num);
  ssc_number_t res;
  LogicalVector res_lv = LogicalVector::create(false);

  if( ssc_data_get_number(data, "system_use_lifetime_output", &res))
  {
    res_lv[0] = res;
  }
  else
  {
    ssc_data_free( data );
    stop("Didnt work");
  }

  ssc_data_free( data );
  return(res_lv);
}

/** Not ready yet
//'@export
// [[Rcpp::export]]
NumericVector dataiotest_nv(NumericVector x)
{
  ssc_data_t data = ssc_data_create();
  int len_arr = 12;
  ssc_number_t x_arr[len_arr];  //length not variable
  for ( int i=0; i<len_arr; i++ )
  {
    x_arr[i] = x[i];
  }
  ssc_data_set_array(data, "poa_monthly", x_arr, len_arr);

  ssc_number_t *res_arr[len_arr] = ssc_data_get_array(data, "poa_monthly", len_arr);
  ssc_data_get_array()
}

**/

/**
CharacterVector dataiotest_fpath(CharacterVector x) {

}


//'@export
// [[Rcpp::export]]
Rcpp::NumericVector pvwattstest(Rcpp::CharacterVector filename) {
  ssc_data_t data = ssc_data_create();
  //marshall the filename input
  string str_filename = as<string>(filename);
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

  // ac variable
  int len = 0;
  Rcpp::NumericVector res;
  ssc_number_t *ac = ssc_data_get_array(data, "ac", &len );
  if ( ac != NULL )
  {
    int i;
    for ( i=0; i<len; i++ )
      res[i] = ac[i];
  }
  return res;
}
**/
