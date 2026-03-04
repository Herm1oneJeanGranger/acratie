# Прогноз оттока клиентов (Customer Churn Prediction)

**Описание проекта:**  
Проект демонстрирует workflow машинного обучения для прогнозирования оттока клиентов на основе числовых и категориальных признаков.  
Используются модели **Logistic Regression** и **CatBoostClassifier**.  
Метрика качества: **ROC-AUC**.

**Структура проекта:**
ML_Customer_Churn/
│
├── notebooks/
│ └── churn_prediction.ipynb
├── data/
│ ├── train.csv # обучающие данные
│ ├── test.csv # тестовые данные
│ └── submission.csv
├── requirements.txt
└── README.md