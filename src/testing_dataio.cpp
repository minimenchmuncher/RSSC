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

//'@export
// [[Rcpp::export]]
NumericVector dataiotest_nv(NumericVector x)
{
  ssc_data_t data = ssc_data_create();
  int len_arr = x.size();
  ssc_number_t *x_arr = (ssc_number_t*) malloc( sizeof(ssc_number_t)*len_arr);
  for ( int i=0; i<len_arr; i++ )
  {
    x_arr[i] = x[i];
  }
  ssc_data_set_array(data, "nday", x_arr, len_arr);
  free(x_arr);

  int len_res_arr = 0;  //I definitely don't understand this syntax.
  ssc_number_t *res_arr = ssc_data_get_array(data, "nday", &len_res_arr);

  NumericVector res_nv(len_arr);
  for (int j=0; j<len_arr; j++)
  {
    res_nv[j] = res_arr[j];
  }
  ssc_data_free(data);
  //free(res_arr); // this crashes. According to the ssc_guide, ssc_data_get_array()
                   // reterns a reference to internally managed memory, and not to
                   // deallocate it. Well, okay then.
  return(res_nv);
}

//'@export
// [[Rcpp::export]]
NumericMatrix dataiotest_nummat(NumericMatrix x)
{
  ssc_data_t data = ssc_data_create();
  // Essentially like a numeric vector, but with rows and columns.
  int cols = x.cols();
  int rows = x.rows();
  int len = x.length();  //going to assume here
  ssc_number_t *x_mat = (ssc_number_t*) malloc(sizeof(ssc_number_t)*len);

  for ( int i=0; i<len; i++)
    x_mat[i] = x[i];  //maybe this will work

  ssc_data_set_matrix(data, "mat1", x_mat, rows, cols);
  free(x_mat);

  int res_rows, res_cols;
  ssc_number_t *res_mat = ssc_data_get_matrix(data, "mat1", &res_rows, &res_cols);
  NumericMatrix res_nm(res_rows, res_cols);
  for (int j=0; j<len; j++)
  {
    res_nm[j] = res_mat[j];
  }

  ssc_data_free(data);
  return(res_nm);
}
