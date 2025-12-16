# Predicting Readmission Rate for Diabetic Patients Using Machine Learning

**DS 207 Final Project**

---

##  Project Overview

This project implements machine learning models to predict hospital readmission for diabetic patients.

---

### Directory Structure

```
. 
├── notebooks/ 
│ ├── terra_tf_rf_xgb.ipynb 
├── results/ 
│ ├── terra_final_report_tables.pdf
│ ├── terra_rf.pkl 
│ ├── terra_stats_tf_rf_xgb.csv
│ ├── terra_tf.pkl
│ ├── terra_xgb.pkl 
└── README.md
```

---

## Contribution Distribution & Workflow

The project is structured so that each notebook's "Run All" execution follows a logical step in the overall methodology.

### ...

### Terra: Random Forest & XGBoost Models

**`notebooks/terra_tf_rf_xgb.ipynb`**

* **Primary Responsibility:** Developing and tuning 3 models - **Logistic Regression**, **Random Forest**, and **XGBoost**.
* **Workflow:**
    1.  **Input:** Load processed data splits (train, val, and test) from `/results`.
    2.  Build, **tune**, and evaluate the **Logistic Regression (LR) Model**.
    3.  **Output:** Save the trained LR model to `/results/terra_tf.pkl`.
    4.  Build, **tune**, and evaluate the **Random Forest (RF) Model**.
    5.  **Output:** Save the trained RF model to `/results/terra_rf.pkl`.
    6.  Build, **tune**, and evaluate the **XGBoost (XGB) Model**.
    7.  **Output:** Save the trained XGB model to `/results/terra_xgb.pkl`.
    8.  **Output:** Save the statistics from the 3 models to `/results/terra_stats_tf_rf_xgb.csv`.

---

## Execution Order

For a full project run, please execute the notebooks in the following order:

1.  **(data processing files)
2.  **`terra_rf_xgb.ipynb`** (Needs data splits)