## start from raw, clean things up, save to model data

#install.packages('readr')
#install.packages('dplyr')
library(readr)
library(dplyr)

# 5521 rows and 1289 columns
anes <- read_csv("data/raw/anes_timeseries_2024_csv_20250430.csv")

anes <- anes %>% 
  mutate(
    # Discard negatives. Remap 1 as decreased, 2 as kept the same, and 3 as increased
    sch_budget = case_when(
      V241264 < 0 ~ NA,
      V241264 == 2 ~ 1, 
      V241264 == 3 ~ 2, 
      V241264 == 1 ~ 3), 
    # Discard negatives. Group each party (D:1-3, R:5-7) and discard independent. 
    lean = case_when(
      V241227x < 0 ~ NA, 
      V241227x %in% 1:3 ~ "Democrat", 
      V241227x == 4 ~ NA, 
      V241227x %in% 5:7 ~ "Republican")) %>% 
  filter(!is.na(sch_budget)) %>%
  filter(!is.na(lean))

# 4870 rows and 2 columns
anes <- subset(anes, select = c('sch_budget','lean'))
write_csv(anes, file = 'data/model/anes_timeseries_2024_csv_20250430.csv')
