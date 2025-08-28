#install.packages('readr')
#install.packages('dplyr')
library(readr)
library(dplyr)

# 80000 rows and 31 columns
shp <- read_csv("data/raw/student_habits_performance.csv")
unique(shp$parental_education_level)

shp <- shp %>% 
  
  # Group each parental education into binary values (None & High School as 0; Bachelor & Master as 1).
  mutate(
    parental_education_binary = case_when(
      parental_education_level %in% c("None", "High School") ~ "low",
      parental_education_level %in% c("Bachelor", "Master")  ~ "high"),
    parental_education_binary = factor(parental_education_binary,
                                       levels = c("low", "high"))) %>%
  # Filter out the null values
  filter(!is.na(sleep_hours),
         !is.na(parental_education_binary),
         !is.na(exam_score))

# 48000 rows and 4 columns
shp <- subset(shp, select = c('sleep_hours', 'parental_education_level', 
                              'parental_education_binary', 'exam_score'))
unique(shp$parental_education_binary)

write_csv(shp, file = 'data/processed/student_habits_performance.csv')