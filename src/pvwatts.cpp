#include <Rcpp.h>
#include <sscapi.h>

using namespace Rcpp;
using namespace std;

//'@export
// [[Rcpp::export]]
List pvwattsv5(List x)
{
  CharacterVector v_filename = as<CharacterVector>(x["solar_resource_file"]);
  NumericVector v_system_capacity = as<NumericVector>(x["system_capacity"]);
  NumericVector v_losses = as<NumericVector>(x["losses"]);
  NumericVector v_array_type = as<NumericVector>(x["array_type"]);
  NumericVector v_tilt = as<NumericVector>(x["tilt"]);
  NumericVector v_azimuth = as<NumericVector>(x["azimuth"]);
  NumericVector v_adjust__constant = as<NumericVector>(x["adjust_constant"]);

  string str_filename = as<string>(v_filename[0]);
  const char * filename = str_filename.c_str();

  ssc_data_t data = ssc_data_create();
  ssc_data_set_string(data, "solar_resource_file", filename);
  ssc_data_set_number(data, "system_capacity", v_system_capacity[0]);
  ssc_data_set_number(data, "losses", v_losses[0]);
  ssc_data_set_number(data, "array_type", (int)v_array_type[0]);
  ssc_data_set_number(data, "tilt", v_tilt[0]);
  ssc_data_set_number(data, "azimuth", v_azimuth[0]);
  ssc_data_set_number(data, "adjust:constant", v_adjust__constant[0]);

  //create module
  ssc_module_t module = ssc_module_create("pvwattsv5");
  if (module == NULL)
  {
    ssc_data_free(data);
    stop("error: could not create pvwattsv5 module.\n");
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

  //collect variables
  int len = 0;
  int yrlen = 8760;
  // initialize res with len from sdktool (hourly tseries)

  NumericVector gh(yrlen);
  NumericVector dn(yrlen);
  NumericVector df(yrlen);
  NumericVector tamb(yrlen);
  NumericVector wspd(yrlen);
  NumericVector sunup(yrlen);
  NumericVector shad_beam_factor(yrlen);
  NumericVector aoi(yrlen);
  NumericVector poa(yrlen);
  NumericVector tpoa(yrlen);
  NumericVector tcell(yrlen);
  NumericVector dc(yrlen);
  NumericVector ac(yrlen);

  NumericVector poa_monthly(12);
  NumericVector solrad_monthly(12);
  NumericVector dc_monthly(12);
  NumericVector ac_monthly(12);
  NumericVector monthly_energy(12);

  // extract vars
  ssc_number_t *ssc_gh = ssc_data_get_array(data, "gh", &len );
  ssc_number_t *ssc_dn = ssc_data_get_array(data, "dn", &len );
  ssc_number_t *ssc_df = ssc_data_get_array(data, "df", &len );
  ssc_number_t *ssc_tamb = ssc_data_get_array(data, "tamb", &len );
  ssc_number_t *ssc_wspd = ssc_data_get_array(data, "wspd", &len );
  ssc_number_t *ssc_sunup = ssc_data_get_array(data, "sunup", &len );
  ssc_number_t *ssc_shad_beam_factor = ssc_data_get_array(data, "shad_beam_factor", &len );
  ssc_number_t *ssc_aoi = ssc_data_get_array(data, "aoi", &len );
  ssc_number_t *ssc_poa = ssc_data_get_array(data, "poa", &len );
  ssc_number_t *ssc_tpoa = ssc_data_get_array(data, "tpoa", &len );
  ssc_number_t *ssc_tcell = ssc_data_get_array(data, "tcell", &len );
  ssc_number_t *ssc_dc = ssc_data_get_array(data, "dc", &len );
  ssc_number_t *ssc_ac = ssc_data_get_array(data, "ac", &len );

  for ( int i=0; i<len; i++ )
  {
    gh[i] = ssc_gh[i];
    dn[i] = ssc_dn[i];
    df[i] = ssc_df[i];
    tamb[i] = ssc_tamb[i];
    wspd[i] = ssc_wspd[i];
    sunup[i] = ssc_sunup[i];
    shad_beam_factor[i] = ssc_shad_beam_factor[i];
    aoi[i] = ssc_aoi[i];
    poa[i] = ssc_poa[i];
    tpoa[i] = ssc_tpoa[i];
    tcell[i] = ssc_tcell[i];
    dc[i] = ssc_dc[i];
    ac[i] = ssc_ac[i];
  }

  len = 0;
  ssc_number_t *ssc_poa_monthly = ssc_data_get_array(data, "poa_monthly", &len );
  ssc_number_t *ssc_solrad_monthly = ssc_data_get_array(data, "solrad_monthly", &len );
  ssc_number_t *ssc_dc_monthly = ssc_data_get_array(data, "dc_monthly", &len);
  ssc_number_t *ssc_ac_monthly = ssc_data_get_array(data, "ac_monthly", &len);
  ssc_number_t *ssc_monthly_energy = ssc_data_get_array(data, "monthly_energy", &len);

  for (int i=0; i<len; i++)
  {
    poa_monthly[i] = ssc_poa_monthly[i];
    solrad_monthly[i] = ssc_solrad_monthly[i];
    dc_monthly[i] = ssc_dc_monthly[i];
    ac_monthly[i] = ssc_ac_monthly[i];
    monthly_energy[i] = ssc_monthly_energy[i];
  }

  ssc_number_t solrad_annual;
  ssc_number_t ac_annual;
  ssc_number_t annual_energy;
  ssc_number_t capacity_factor;
  ssc_number_t kwh_per_kw;
  ssc_number_t lat;
  ssc_number_t lon;
  ssc_number_t elev;
  ssc_number_t inverter_model;
  ssc_number_t inverter_efficiency;
  ssc_number_t ts_shift_hours;
  ssc_number_t system_use_lifetime_output;
  ssc_number_t tz;

  ssc_data_get_number(data, "solrad_annual", &solrad_annual);
  ssc_data_get_number(data, "ac_annual", &ac_annual);
  ssc_data_get_number(data, "annual_energy", &annual_energy);
  ssc_data_get_number(data, "capacity_factor", &capacity_factor);
  ssc_data_get_number(data, "kwh_per_kw", &kwh_per_kw);
  ssc_data_get_number(data, "lat", &lat);
  ssc_data_get_number(data, "lon", &lon);
  ssc_data_get_number(data, "elev", &elev);
  ssc_data_get_number(data, "inverter_model", &inverter_model);
  ssc_data_get_number(data, "inverter_efficiency", &inverter_efficiency);
  ssc_data_get_number(data, "ts_shift_hours", &ts_shift_hours);
  ssc_data_get_number(data, "system_use_lifetime_output", &system_use_lifetime_output);
  ssc_data_get_number(data, "tz", &tz);

  const char *ssc_location = ssc_data_get_string(data, "location");
  string location = string(ssc_location);

  const char *ssc_city = ssc_data_get_string(data, "city");
  string city = string(ssc_city);

  const char *ssc_state = ssc_data_get_string(data, "state");
  string state = string(ssc_state);

  // free module & data
  ssc_module_free(module);
  ssc_data_free(data);

  List res = List::create(Named("solar_resource_file") = x["solar_resource_file"],
                          Named("gh") = gh,
                          Named("dn") = dn,
                          Named("df") = df,
                          Named("tamb") = tamb,
                          Named("wspd") = wspd,
                          Named("sunup") = sunup,
                          Named("shad_beam_factor") = shad_beam_factor,
                          Named("aoi") = aoi,
                          Named("poi") = poa,
                          Named("tpoa") = tpoa,
                          Named("tcell") = tcell,
                          Named("dc") = dc,
                          Named("ac") = ac,
                          Named("poa_monthly") = poa_monthly,
                          Named("solrad_monthly") = solrad_monthly,
                          Named("dc_monthly") = dc_monthly,
                          Named("ac_monthly") = ac_monthly,
                          Named("monthly_energy") = monthly_energy);
  res["solrad_annual"] = solrad_annual;
  res["ac_annual"] = ac_annual;
  res["annual_energy"] = annual_energy;
  res["location"] = location;
  res["city"] = city;
  res["state"] = state;
  res["lat"] = lat;
  res["lon"] = lon;
  res["tz"] = tz;
  res["elev"] = elev;
  res["inverter_model"] = inverter_model;
  res["ts_shift_hours"] = ts_shift_hours;
  res["system_use_lifetime_output"] = system_use_lifetime_output;
  return(res);
}


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
