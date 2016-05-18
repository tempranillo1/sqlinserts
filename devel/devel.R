library(sqlinserts)
library(stringi)
library(RSQLite)
test_df<- data.frame(stringsAsFactors = FALSE,
                     col_integer = -9L:5L,
                     col_numeric = seq(from = -123, to = 3.21, length.out = 15L),
                     col_char = LETTERS[1L:15L],
                     col_unicode = strsplit("zażółćgęśląjaźń", split ="")[[1L]],
                     col_factor = as.factor(rep(c("abc", "klm", "xyz"), 5L)),
                     col_date = as.Date(18619L:18633L, origin = "1970-01-01"),
                     col_datetime = seq(from = as.POSIXlt("2020-12-23 21:39:37 CEST"),
                                        to   = as.POSIXlt("2023-12-23 21:39:37 CEST"),
                                        length.out = 15L),
                     col_NA_character = rep(NA_character_, 15L),
                     col_NA_numeric = rep(NA_integer_, 15L))
dplyr::glimpse(test_df)
inserts <- make_inserts(test_df)

db <- dbConnect(SQLite(), dbname="test_sqlite")


dbSendQuery(conn = db, "

INSERT INTO test_df
(col_integer, col_numeric, col_char, col_unicode, col_factor, col_date, col_datetime, col_NA_character, col_NA_numeric)
VALUES
(-9, -123.000, 'A', 'z', 'abc', '2020-12-23', '2020-12-23 21:39:37', NULL, NULL)
            ")
