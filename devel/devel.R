library(sqlinserts)
test_df<- data.frame(stringsAsFactors = FALSE,
                     col_integer = -9L:5L,
                     col_numeric = seq(from = -123, to = 3.21, length.out = 15L),
                     col_char = LETTERS[1L:15L],
                     col_unicode = strsplit("zażółćgęśląjaźń", split ="")[[1L]],
                     col_factor = as.factor(rep(c("abc", "klm", "xyz"), 5L)),
                     col_date = as.Date(18619L:18633L, origin = "1970-01-01"),
                     col_datetime = seq(from = as.POSIXlt("2020-12-23 21:39:37 CEST"),
                                        to   = as.POSIXlt("2023-12-23 21:39:37 CEST"),
                                        length.out = 15L))
dplyr::glimpse(test_df)
make_inserts(test_df) %>% cat()
