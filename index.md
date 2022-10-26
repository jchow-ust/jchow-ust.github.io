# Portfolio
---

## Data Science & Statistical Analysis Projects

### Yelp Review Sentiment Analysis

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project1_SentimentAnalysis/Submission/Bi-LSTM-RNN.ipynb)
[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project1_SentimentAnalysis/Submission/Report.pdf)

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Tensorflow-orange
https://img.shields.io/badge/-Keras-red
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-lightgrey
https://img.shields.io/badge/-Regression-lightgrey

This project involves sentiment analysis of text from Yelp reviews of various businesses. The task is to predict the number of stars (1-5) from the corresponding rating text. As the dataset is imbalanced in favour of 5-star reviews, F1 score is used as the evaluation metric instead of accuracy. Interestingly, we observe that the best model (logistic regression) outperformed all CNN/RNN-based models we tested, though both had a validation F1 score ~10% higher than the baseline given by our instructor.

<img src="images/GANs_1.png"/>

---
### Social Network Link Prediction

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project2_GraphLinkPrediction/Submission/Code.ipynb)
[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/quick-portfolio-master/projects/COMP4332_Project2_GraphLinkPrediction/Submission/Report.pdf)

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-lightgrey

This project involves link prediction between nodes of an undirected graph, where the nodes denote Yelp users and the links denote friendships between users. An ensemble of first-order and second-order random walk models were used to achieve an AUC-ROC score of 93.9% on the validation set, which outperforms the baseline given by our instructor.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Rating Prediction with Wide & Deep Model

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project3_WideDeepModel/Jasper_Proj3_Wide_&_Deep_Learning.ipynb)
[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project3_WideDeepModel/Report%20%3.pdf)

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-lightgrey

This project involves predicting ratings (from 1-5) of users on given products given a sparse initial user-item rating matrix, which is typical of recommendation systems. The evaluation metric is the RMSE (Root Mean Squared Error.) After hyperparameter tuning and feature engineering, the wide and deep model achieves a validation RMSE of 1.014 which far outperforms the instructor baseline RMSE of 1.09.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Spark with Machine Learning

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4651_A5_SparkML/ml_pipeline.ipynb)

https://img.shields.io/badge/-R-black
https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pyspark-blue

This repo contains an end-to-end implementation of machine learning with Spark. The task is to predict power output given a set of environmental readings from a power plant. This notebook was run on a Databricks Community Edition cluster (this can be done for free) after uploading the requisite data files to DBFS (Databricks File Storage). Models used include linear regression, decision tree, and random forest. 

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Regression Analysis Homework

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH3424_RegressionAnalysis)

https://img.shields.io/badge/-R-black
https://img.shields.io/badge/-DeepLearning-lightgrey

This repo contains all homework done for the HKUST course "MATH3424 Regression Analysis". Homework is written in Markdown with commented R code. Topics covered in the course include:

1. Multiple Linear Regression

2. Regression Diagnostics: Analysis of Residuals

3. Qualitative Predictor Variables in Regression

4. Transformation of Variables and Collinearity, Variable and Model Selection

5. Logistic Regression

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
<center>Powered by Jekyll and the Minimal Theme.</center>
