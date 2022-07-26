# Portfolio
---

## Data Science & Statistical Analysis Projects

### Deep Reinforcement Learning in Big Two

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/big2-rl)

[View Report](https://github.com/jchow-ust/big2-rl/blob/main/DRL%20with%20Big2.pdf)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)
![](https://img.shields.io/badge/-ReinforcementLearning-purple)
![](https://img.shields.io/badge/-MonteCarlo-purple)

In this project supervised by Dr. Chen Qifeng, we developed Big2-RL, a reinforcement learning framework for Big Two (Cantonese: 鋤大弟), a four-player card-shedding game popular in Southeast Asia. The evaluation metric is average expected value (EV) of the winnings. Due to the symmetry of all players in the game, a reinforcement learning (RL) agent achieves an EV significantly above 0 has a winning strategy and is said to be performing well. Our reinforcement learning agent was trained on HKUST's HPC3 (High Performance Computing Cluster) for multiprocessing in order to improve training time and reduce variance. We consider a variety of training approaches and model architectures, and when combined with Deep Monte Carlo, we demonstrate that a simple MLP with residual connections trained against prior iterations of itself far outperforms other model architectures, managing to achieve a statistically significant average EV of +1.09/1000 hands (where the agent played all 4 positions in each hand) against prior copies of itself, and average EV of +1.81/1000 hands over the current state-of-the-art PPO algorithm proposed and implemented by Charlesworth ([GitHub](https://github.com/henrycharlesworth/big2_PPOalgorithm)). This thereby demonstrates the effectiveness of Monte Carlo methods for multi-agent imperfect information tasks. 

<img src="images/big2-1.png"/>

---
### Yelp Review Sentiment Analysis

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project1_SentimentAnalysis/Submission/Bi-LSTM-RNN.ipynb)

[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project1_SentimentAnalysis/Submission/Report.pdf)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Tensorflow-orange)
![](https://img.shields.io/badge/-Keras-red)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)
![](https://img.shields.io/badge/-Regression-lightgrey)

This project involves sentiment analysis of text from Yelp reviews of various businesses. The task is to predict the number of stars (1-5) from the corresponding rating text. As the dataset is imbalanced in favour of 5-star reviews, F1 score is used as the evaluation metric instead of accuracy. Interestingly, we observe that the best model (logistic regression) outperformed all CNN/RNN-based models we tested, though both had a validation F1 score ~10% higher than the baseline given by our instructor. Our final model's F1 score is one of the highest in the class, ranking in the top 10%.

<img src="images/4332-1.png"/>

---
### Social Network Link Prediction

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project2_GraphLinkPrediction/Submission/Code.ipynb)

[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project2_GraphLinkPrediction/Submission/Report.pdf)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

This project involves link prediction between nodes of an undirected graph, where the nodes denote Yelp users and the links denote friendships between users. An ensemble of first-order and second-order random walk models were used to achieve an AUC-ROC score of 93.9% on the validation set, which outperformed all other teams in our class.

<img src="images/4332-2.png"/>

---
### Rating Prediction with Wide & Deep Model

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project3_WideDeepModel/Jasper_Proj3_Wide_&_Deep_Learning.ipynb)

[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4332_Project3_WideDeepModel)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

This project involves predicting ratings (from 1-5) of users on given products given a sparse initial user-item rating matrix, which is typical of recommendation systems. The evaluation metric is the RMSE (Root Mean Squared Error.) After hyperparameter tuning and feature engineering, the wide and deep model achieved a validation RMSE of 1.014 which far outperformed the best instructor-given baseline RMSE of 1.09. Additionally, our final model's RMSE was the lowest in the class, outperforming all other teams.

<img src="images/4332-3.png"/>

---
### Pawpularity Prediction of Pet Photos with CNN

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH4995_CapstoneProject/MATH4995_Pawpularity/MATH4995_P2.ipynb)

[View Report](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH4995_CapstoneProject/MATH4995_Pawpularity/4995_report_f.pdf)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Keras-red)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

Capstone project for predicting the popularity scores of pets based on their pictures on the online pet adoption website Petfinder.my. Although certain breeds may be more popular overall, it is hypothesised that features such as whether pets' faces are shown, or whether humans are present in the picture may influence how popular that pet profile is. This information can guide adoption agencies into taking profile pictures that are more eye-catching so that stray animals can find caring families as soon as possible. The pawpularity score of an image ranges from 0-100, and the evaluation metric used is Root Mean Squared Error (RMSE). Ultimately, the final model used both metadata and image features, and when combined with a customised weighted loss function, I managed to achieve an RMSE of 17.09 on the Kaggle private leaderboard, for which I was awarded a bronze medal. It should be noted that the top score (lowest RMSE) was 16.82.

<img src="images/4995-2-1.png"/>

---
### Simple C# Website interfacing with Oracle SQL Database

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/UniversityWebsite)

![](https://img.shields.io/badge/-C%23-purple)
![](https://img.shields.io/badge/-SQL-green)

This repo contains source code for building a simple website in C# that interfaces with Oracle SQL database to display results for popularly used queries. The web application also supports addition and deletion of records to said database.

<img src="images/sqlwebsite.png"/>

---
### MongoDB NoSQL Credential Storage System

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/mongodb-passwords)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-NoSQL-green)
![](https://img.shields.io/badge/-MongoDB-green)

Created a cluster in MongoDB Atlas and NoSQL database to store my login credentials and associated information, such as birth dates, security questions and answers, etc. For websites which were used to submit job applications, further information such as job requirements, date applied, expected salary, and follow-up information can also be saved for ease of access during interviews or future applications with the same organisation.

<img src="images/mongodb.png"/>

---
### Emoji Style Transfer with DCGAN & CycleGAN 

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/comp5214-hw3/tree/main/skeleton_code)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

This project involved implementing DCGAN and CycleGAN architectures from scratch for style transfer of emojis from Windows to Apple. Windows emojis tend to be flatter and have black borders, whereas Apple-style emojis tend to have depth and are borderless. After experimentation, it is observed that the introduction of the cycle consistency loss in CycleGAN greatly helped improve performance during such style transfer, as the vanilla DCGAN method produces checkerboard effects and the discriminator loss quickly saturates to 0 without causing the generator loss to further decrease.

<center><img src="images/GANs_1.png"/></center>

---
### Turbulence detection in multispectral images

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4211%20Machine%20Learning/Final_Project/group6-final.ipynb)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

This project involved classifying multispectral images of particles, where each spectra (or channel) captured specific information (e.g. UV light) into different types of turbulence (moderate, severe, or none). F1 score was used as the evaluation metric. The dataset was imbalanced as only a small number of samples showed severe turbulence. However, through experimentation with data augmentation, different loss metrics, and different CNN model architectures, we observe that the focal loss paired with an ensemble of different CNN architectures best improved performance and achieved an average 70% F1 score on the validation set across all three classes.

<img src="images/4211.png"/>

---
### Object detection with bounding boxes on Caltech birds dataset

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4211%20Machine%20Learning/mini_project/miniproj.ipynb)

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

This project involved object detection by finding the bounding box of birds in images from the Caltech birds dataset. IoU (intersection over union) (of predicted vs actual bounding boxes) was used as the evaluation metric. After employing hyperparameter tuning and cross validation, the tuned ResNet model achieved an average test set IoU of 0.85 and was the highest performing model in our class. The below figure shows the performance of our final model on one such image, where the ground truth bounding box is highlighted in red and the final model's predicted bounding box is highlighted in blue.

<img src="images/caltechbirds.png"/>

---
### Spark with Machine Learning

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4651_A5_SparkML/ml_pipeline.ipynb)

![](https://img.shields.io/badge/-R-black)
![](https://img.shields.io/badge/-SQL-green)
![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pyspark-blue)

This repo contains an end-to-end implementation of machine learning with Spark. The task is to predict power output given a set of environmental readings from a power plant. This notebook was run on a Databricks Community Edition cluster (this can be done for free) after uploading the requisite data files to DBFS (Databricks File Storage). Models used include linear regression, decision tree, and random forest. It is observed that the random forest model outperforms both the decision tree and linear regression models.

---
### COMP5214: Advanced Deep Learning Architectures Assignments

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)

This repository contains completed homework assignments for course "COMP5214: Advanced Deep Learning Architectures". Topics covered include:

1. KNN, MLP, and customised CNN implementation (MNIST) ([GitHub](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/5214_Assignments/HW1))

2. Word2Vec Embeddings and Graph Neural Networks ([GitHub](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/5214_Assignments/HW2))

<img src="images/5214_1.png"/>

---
### MATH3424: Regression Analysis Homework

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH3424_RegressionAnalysis)

![](https://img.shields.io/badge/-R-black)
![](https://img.shields.io/badge/-Regression-lightgrey)

This repo contains all homework done for the HKUST course "MATH3424: Regression Analysis". Homework is written in Markdown with commented R code. Topics covered in the course include:

1. Multiple Linear Regression

2. Regression Diagnostics: Analysis of Residuals

3. Qualitative Predictor Variables in Regression

4. Transformation of Variables and Collinearity, Variable and Model Selection

5. Logistic Regression

---
### MATH2411: Applied Statistics Final Project

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/MATH2411_Project)

![](https://img.shields.io/badge/-R-black)
![](https://img.shields.io/badge/-Regression-lightgrey)

This repo contains the final project for the HKUST course "MATH2411: Applied Statistics", including the dataset used (`basketball_data.csv`), our written report, and R code. The project involved conducting statistical analysis on whether certain performance metrics such as high offensive rating and having more star players lead to more wins.

<img src="images/2411-final.png"/>

---
### COMP4211: Machine Learning Assignments

![](https://img.shields.io/badge/-Python-blue)
![](https://img.shields.io/badge/-Pytorch-orange)
![](https://img.shields.io/badge/-Numpy-blue)
![](https://img.shields.io/badge/-DeepLearning-lightgrey)
![](https://img.shields.io/badge/-UnsupervisedLearning-purple)
![](https://img.shields.io/badge/-ReinforcementLearning-purple)

This repository contains completed homework assignments for course "COMP4211: Machine Learning". Topics covered include:

1. Multi-layer perceptron (MNIST) ([GitHub](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4211%20Machine%20Learning/Assignment%201%20MNIST))

2. Unsupervised learning (k-means clustering) and visualisation ([GitHub](https://github.com/jchow-ust/jchow-ust.github.io/blob/main/projects/COMP4211%20Machine%20Learning/Assignment%202%20Unsupervised%20Learning))

3. Reinforcement learning (Q-learning) ([GitHub](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP4211%20Machine%20Learning/Assignment%203%20Reinforcement%20Learning))

---
## Software Engineering

### COVID-based game with GUI

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/CovidGameGUI)

![](https://img.shields.io/badge/-Java-orange)
![](https://img.shields.io/badge/-JavaFX-orange)

This repo contains source code for a GUI-based resource management game developed using JavaFX for the course "COMP3021: Java Programming". Rules for the game are detailed on pages 2 and 3 of the assignment instructions found [here.](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/CovidGameGUI/COMP3021-PA1.pdf)

<img src="images/covid_game.png"/>

---
### 'Battle City' arcade game in MIPS

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/mips_battleCity)

![](https://img.shields.io/badge/-Java-orange)
![](https://img.shields.io/badge/-MIPS-brightgreen)

This repo contains source code in MIPS and Java for the implementation of the 'Battle City' arcade game, in which the player controls a tank and attempts to destroy enemy tanks on varied terrain.

<img src="images/mips_bc.png"/>

---

## Miscellanea

### Simple Shell Commands with C/POSIX

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP3511_A1_SimpleTerminal)

![](https://img.shields.io/badge/-C-brightgreen)
![](https://img.shields.io/badge/-Shell-yellowgreen)

This repo contains an implementation of simple shell commands (I/O redirection and two-level pipes) via POSIX file operations for understanding process management and inter-process communication.

---
### Banker's algorithm implementation in C

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP3511_A2_Banker)

![](https://img.shields.io/badge/-C-brightgreen)
![](https://img.shields.io/badge/-Shell-yellowgreen)

This repo contains an implementation of Banker's algorithm in C to detect deadlocks within a set of processes.

---
### COMP2012 Assignments

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP2012_notes)

![](https://img.shields.io/badge/-C++-brightgreen)

This repo contains class notes and assignments for the course "COMP2012: Object-Oriented Programming and Data Structures with C++".

---
### MIPS scripts

[![View on GitHub](https://img.shields.io/badge/GitHub-View_on_GitHub-blue?logo=GitHub)](https://github.com/jchow-ust/jchow-ust.github.io/tree/main/projects/COMP2611_MIPS_Homework)

![](https://img.shields.io/badge/-MIPS-brightgreen)

Miscellaneous MIPS scripts for homework in the course "COMP2611: Computer Organization".

---
<center>Powered by Jekyll and the Minimal Theme.</center>
