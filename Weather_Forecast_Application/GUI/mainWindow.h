#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QComboBox;
class QPushButton;
class QLabel;
class QChartView;
class QProgressBar;

class Cities;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(
        Cities& cities,
        QWidget* parent = nullptr
    );

    ~MainWindow();

private slots:

    void getWeather();

private:


    QComboBox* cityComboBox;
    QPushButton* getWeatherButton;

    QLabel* cityLabel;
    QLabel* dateLabel;
    QLabel* timeLabel;

    QLabel* temperatureLabel;
    QLabel* conditionLabel;
    QLabel* humidityLabel;
    QLabel* windLabel;

    QLabel* statusLabel;

    QProgressBar* loadingBar;

    QChartView* chartView;


    Cities& cities;

    void setupUI();

    void setupStyles();

    void populateCities();


    void displayWeather(
        const std::string& cityName
    );

    void updateCurrentWeather();

    void updateForecastChart();


    QString weatherDescription(int weatherCode) const;

    QString weatherIcon(int weatherCode) const;

    void setStatus(
        const QString& message,
        bool error = false
    );
};

#endif