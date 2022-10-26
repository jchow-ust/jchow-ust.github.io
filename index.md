# Portfolio
---

## Data Science & Statistical Analysis Projects

### Yelp Review Sentiment Analysis

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project1_SentimentAnalysis/Submission/Bi-LSTM-RNN.ipynb)
[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project1_SentimentAnalysis/Submission/Report.pdf)

[![P](https://img.shields.io/badge/-Python-blue)]
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
### Pawpularity Prediction of Pet Photos with CNN

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH4995_CapstoneProject/MATH4995_Pawpularity/MATH4995_P2.ipynb)
[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH4995_CapstoneProject/MATH4995_Pawpularity/4995_report_f.pdf)

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Keras-red
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-grey

Capstone project for predicting the popularity scores of pets based on their pictures on the online pet adoption website Petfinder.my. Although certain breeds may be more popular overall, it is hypothesised that features such as whether pets' faces are shown, or whether humans are present in the picture may influence how popular that pet profile is. This information can guide adoption agencies into taking profile pictures that are more eye-catching so that stray animals can find caring families as soon as possible.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Simple C# Website interfacing with Oracle SQL Database]

[![TODO View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/comp5214-hw3/tree/main/skeleton_code)

https://img.shields.io/badge/-C#-purple
https://img.shields.io/badge/-SQL-green

This repo contains source code for building a simple website in C# that interfaces with Oracle SQL database to display results for popularly used queries.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Emoji Style Transfer with DCGAN & CycleGAN 

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/comp5214-hw3/tree/main/skeleton_code)

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-lightgrey

This project involved implementing DCGAN and CycleGAN architectures from scratch for style transfer of emojis from Windows to Apple. Windows emojis tend to be flatter and have black borders, whereas Apple-style emojis tend to have depth and are borderless. After experimentation, it is observed that the introduction of the cycle consistency loss in CycleGAN greatly helped improve performance during such style transfer, as the vanilla DCGAN method produces checkerboard effects and the discriminator loss quickly saturates to 0 without causing the generator loss to further decrease.

<center><img src="images/GANs_1.png"/></center>

---
### Turbulence detection in images

[Example turbulence detection classification in different bands]

TODO link

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-lightgrey

This project involved classifying information received from different bands as different types of turbulence (moderate, severe, or none). F1 score was used as the evaluation metric. TODO expand

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Object detection with bounding boxes on Caltech birds dataset

[2 types of Caltech birds sample image classification]

TODO link

https://img.shields.io/badge/-Python-blue
https://img.shields.io/badge/-Pytorch-orange
https://img.shields.io/badge/-Numpy-blue
https://img.shields.io/badge/-DeepLearning-lightgrey

This project involved bounding box detection of images from the Caltech birds dataset. IoU (intersection over union) (of predicted vs actual bounding boxes) was used as the evaluation metric. TODO expand

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
## Software Engineering

### COVID-based game with GUI]

[image of COVID based game gameplay]

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/CovidGameGUI)

https://img.shields.io/badge/-Java-orange
https://img.shields.io/badge/-JavaFX-orange

This repo contains source code for a GUI-based resource management game developed using JavaFX. Rules for the game are detailed in [TODO need find file].

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### 'Battle City' arcade game in MIPS

[Image of battle city gameplay]

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/mips_battleCity)

https://img.shields.io/badge/-Java-orange
https://img.shields.io/badge/-MIPS-brightgreen

This repo contains source code in MIPS and Java for the implementation of the 'Battle City' arcade game, in which the player controls a tank and attempts to destroy enemy tanks on varied terrain.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---

## Miscellanea

### Simple Shell Commands with C/POSIX

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP3511_A1_SimpleTerminal)

https://img.shields.io/badge/-C-brightgreen
https://img.shields.io/badge/-Shell-yellowgreen

This repo contains an implementation of simple shell commands (I/O redirection and two-level pipes) via POSIX file operations for understanding process management and inter-process communication.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### Banker's algorithm implementation in C

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP3511_A2_Banker)

https://img.shields.io/badge/-C-brightgreen
https://img.shields.io/badge/-Shell-yellowgreen

This repo contains an implementation of Banker's algorithm in C to detect deadlocks within a set of processes.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### COMP2012 Assignments

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP2012_notes)

https://img.shields.io/badge/-C++-brightgreen

This repo contains class notes and assignments for the course COMP2012: Object-Oriented Programming and Data Structures with C++.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
### MIPS scripts

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP2611_MIPS_Homework)

https://img.shields.io/badge/-MIPS-brightgreen

Miscellaneous MIPS scripts for homework in the course COMP2611: Computer Organization.

<img src="images/dummy_thumbnail.jpg?raw=true"/>

---
<center>Powered by Jekyll and the Minimal Theme.</center>
