context("Class Instantiation")

test_that("Instance of pvwattsv5 object", {
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                         losses = 0.03,
                         array_type = 0L,
                         tilt = 30,
                         azimuth = 180,
                         adjust_constant = 1)
  pvwatts_obj <- instantiate_class(pvwatts_inputs, cls = "pvwattsv5_obj")
  expect_is(pvwatts_obj, "pvwattsv5_obj")
})

test_that("Instance of pvwattsv5 obj raises errors", {
  # doesn't contain required inputs
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                       # losses = 0.03,
                         array_type = 0L,
                         tilt = 30,
                         azimuth = 180,
                         adjust_constant = 1)
  expect_error(instantiate_class(pvwatts_inputs, cls = "pvwattsv5_obj"),
               regexp = "losses")
  # contains inputs not in prototype
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                         somethingelse = 0.03,
                         array_type = 0L,
                         tilt = 30,
                         azimuth = 180,
                         adjust_constant = 1)
  expect_error(instantiate_class(pvwatts_inputs, cls = "pvwattsv5_obj"),
               regexp = "somethingelse")
  # mis-classed inputs
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                         losses = 0.03,
                         array_type = 0L,
                         tilt = "hello",
                         azimuth = 180,
                         adjust_constant = 1)
  expect_error(instantiate_class(pvwatts_inputs, cls = "pvwattsv5_obj"),
               regexp = "attribute tilt.*character.*numeric")

})

test_that("Calculates properly with actual rsc file", {
  # uses TMY3 for Boston Logan, USA tmy file. Provided in inst
  pvwatts_inputs <- list(solar_resource_file = "../../inst/USA MA Boston Logan Int'l Arpt (TMY3).csv",
                         system_capacity = 10,
                         losses = 0.03,
                         array_type = 0L,
                         tilt = 30,
                         azimuth = 180,
                         adjust_constant = 1)
  pvwatts_obj <- instantiate_class(pvwatts_inputs, cls = "pvwattsv5_obj")

  # run with resource provided
  test_out <- pvwattsv5.pvwattsv5_obj(pvwatts_obj)
  ncf <- sum(test_out$ac) / (8760 * 1000 * pvwatts_inputs$system_capacity)
  expect_equal(mean(test_out$ac), 1771.911, tolerance = 0.01)
  expect_equal(ncf, 0.1772, tolerance = 0.0001)
})
