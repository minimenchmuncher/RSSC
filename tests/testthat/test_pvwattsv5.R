context("Class Instantiation")

test_that("Instance of pvwattsv5 object", {
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                         losses = 0.03,
                         array_type = 0L,
                         tilt = 30,
                         azimuth = 180,
                         adjust_constant = 1)
  pvwatts_obj <- instantiate_class(pvwatts_inputs, cls = "pvwattsv5")
  expect_is(pvwatts_obj, "pvwattsv5")
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
  expect_error(instantiate_class(pvwatts_inputs, cls = "pvwattsv5"),
               regexp = "losses")
  # contains inputs not in prototype
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                         somethingelse = 0.03,
                         array_type = 0L,
                         tilt = 30,
                         azimuth = 180,
                         adjust_constant = 1)
  expect_error(instantiate_class(pvwatts_inputs, cls = "pvwattsv5"),
               regexp = "somethingelse")
  # mis-classed inputs
  pvwatts_inputs <- list(solar_resource_file = "a file",
                         system_capacity = 10,
                         losses = 0.03,
                         array_type = 0L,
                         tilt = "hello",
                         azimuth = 180,
                         adjust_constant = 1)
  expect_error(instantiate_class(pvwatts_inputs, cls = "pvwattsv5"),
               regexp = "attribute tilt.*character.*numeric")

})
