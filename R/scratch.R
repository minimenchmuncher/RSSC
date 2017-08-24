
#' #'@exportClass
#' setClass("pvwattsv5", slots = list(
#'   solar_resource_file = "character",
#'   solar_resource_data = "data.frame",
#'   system_capacity = "numeric",
#'   module_type = "numeric",
#'   dc_ac_ratio = "numeric",
#'   inv_eff = "numeric",
#'   losses = "numeric",
#'   array_type = "numeric",
#'   tilt = "numeric",
#'   azimuth = "numeric",
#'   gcr = "numeric",
#'   shading_timestemp = "matrix",
#'   shading_mxh = "matrix",
#'   shading_diff = "matrix",
#'   batt_simple_enable = "logical"
#' ))

# new_lcoefcr <- function(capital_cost, fixed_operating_cost, variable_operating_cost,
#                         fixed_charge_rate, annual_energy, ...) {
#   dots <- list(...)
#   stopifnot(is.numeric(capital_cost))
#   stopifnot(is.numeric(fixed_operating_cost))
#   stopifnot(is.numeric(variable_operating_cost))
#   stopifnot(is.numeric(fixed_charge_rate))
#   stopifnot(is.numeric(annual_energy))
#   stopifnot(length(capital_cost) == 1)
#   stopifnot(length(fixed_operating_cost) == 1)
#   stopifnot(length(variable_operating_cost) == 1)
#   stopifnot(length(fixed_charge_rate) == 1)
#   stopifnot(length(annual_energy) == 1)
#   structure(.Data = list(capital_cost = capital_cost,
#                          fixed_operating_cost = fixed_operating_cost,
#                          variable_operating_cost = variable_operating_cost,
#                          fixed_charge_rate = fixed_charge_rate,
#                          annual_energy = annual_energy),
#             class = "lcoefcr")
# }
#
# lcoefcr <- function(capital_cost, fixed_operating_cost, variable_operating_cost,
#                     fixed_charge_rate, annual_energy)
