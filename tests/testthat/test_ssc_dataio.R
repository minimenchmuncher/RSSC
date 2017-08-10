context("Data IO")

test_that("test numeric vector IO", {
  skip_on_travis()
  x <- 3
  res <- dataiotest_num(x)
  expect_equal(res, x)

  x <- c(1, 3)
  res <- dataiotest_num(x)
  expect_equal(res, x[1])
})

test_that("test character vector IO", {
  skip_on_travis()
  x <- "hello"
  res <- dataiotest_char(x)
  expect_equal(res, x)

  x <- c("hello", "world")
  res <- dataiotest_char(x)
  expect_equal(res, x[1])
})

test_that("test logical vector IO", {
  skip_on_travis()
  x <- TRUE
  res <- dataiotest_log(x)
  expect_equal(res, x)

  x <- c(FALSE, TRUE)
  res <- dataiotest_log(x)
  expect_equal(res, x[1])
})

test_that("test numeric vector IO len > 1", {
  skip_on_travis()
  x <- 1:12
  res <- dataiotest_nv(x)  # nv for numerical vector
  expect_equal(res, x)
})

test_that("test numeric matrix IO", {
  skip_on_travis()
  x <- matrix(4:15, nrow = 3)
  res <- dataiotest_nummat(x)
  expect_equal(res, x)
})
