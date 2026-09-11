#include "mainWindow.h"

#include "../Includes/Cities.h"
#include "../Includes/Data.h"
#include "../Includes/Curl.h"
#include "../Includes/Rapidjson.h"

#include <QApplication>
#include <QComboBox>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>


MainWindow::MainWindow(
    Cities& cities,
    QWidget* parent
)
    : QMainWindow(parent),
      cityComboBox(nullptr),
      getWeatherButton(nullptr),
      cityLabel(nullptr),
      dateLabel(nullptr),
      timeLabel(nullptr),
      temperatureLabel(nullptr),
      conditionLabel(nullptr),
      humidityLabel(nullptr),
      windLabel(nullptr),
      statusLabel(nullptr),
      loadingBar(nullptr),
      chartView(nullptr),
      cities(cities)
{
    setupUI();

    setupStyles();

    populateCities();
}


MainWindow::~MainWindow()
{
}


void MainWindow::setupUI()
{

    setWindowTitle("Weather Forecast Application");

    resize(1200, 800);

    setMinimumSize(950, 650);

    QWidget* centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout =
        new QVBoxLayout(centralWidget);

    mainLayout->setContentsMargins(
        35,
        30,
        35,
        25
    );

    mainLayout->setSpacing(20);

    QLabel* title =
        new QLabel("Weather Forecast");

    title->setObjectName("titleLabel");

    mainLayout->addWidget(title);


    QLabel* subtitle =
        new QLabel(
            "Real-time weather information and 7-day forecast"
        );

    subtitle->setObjectName("subtitleLabel");

    mainLayout->addWidget(subtitle);

    QFrame* controlCard =
        new QFrame();

    controlCard->setObjectName("card");

    QHBoxLayout* controlLayout =
        new QHBoxLayout(controlCard);

    controlLayout->setContentsMargins(
        20,
        18,
        20,
        18
    );


    QLabel* chooseCity =
        new QLabel("Choose a city:");

    chooseCity->setObjectName("sectionLabel");

    cityComboBox =
        new QComboBox();

    cityComboBox->setMinimumWidth(280);

    cityComboBox->setMinimumHeight(45);


    getWeatherButton =
        new QPushButton("Get Weather");

    getWeatherButton->setMinimumHeight(45);

    getWeatherButton->setMinimumWidth(150);


    controlLayout->addWidget(chooseCity);

    controlLayout->addWidget(cityComboBox);

    controlLayout->addWidget(getWeatherButton);

    controlLayout->addStretch();


    mainLayout->addWidget(controlCard);


    connect(
        getWeatherButton,
        &QPushButton::clicked,
        this,
        &MainWindow::getWeather
    );


    QFrame* weatherCard =
        new QFrame();

    weatherCard->setObjectName("card");


    QGridLayout* weatherLayout =
        new QGridLayout(weatherCard);

    weatherLayout->setContentsMargins(
        25,
        20,
        25,
        20
    );

    weatherLayout->setHorizontalSpacing(35);

    weatherLayout->setVerticalSpacing(12);

    QLabel* cityTitle =
        new QLabel("CITY");

    cityTitle->setObjectName("smallTitle");


    cityLabel =
        new QLabel("--");

    cityLabel->setObjectName("valueLabel");


    QLabel* dateTitle =
        new QLabel("DATE");

    dateTitle->setObjectName("smallTitle");


    dateLabel =
        new QLabel("--");

    dateLabel->setObjectName("valueLabel");


    QLabel* timeTitle =
        new QLabel("LOCAL TIME");

    timeTitle->setObjectName("smallTitle");


    timeLabel =
        new QLabel("--");

    timeLabel->setObjectName("valueLabel");


    QLabel* temperatureTitle =
        new QLabel("TEMPERATURE");

    temperatureTitle->setObjectName("smallTitle");


    temperatureLabel =
        new QLabel("-- °C");

    temperatureLabel->setObjectName("temperatureLabel");


    QLabel* conditionTitle =
        new QLabel("CONDITION");

    conditionTitle->setObjectName("smallTitle");


    conditionLabel =
        new QLabel("--");

    conditionLabel->setObjectName("conditionLabel");



    QLabel* humidityTitle =
        new QLabel("HUMIDITY");

    humidityTitle->setObjectName("smallTitle");


    humidityLabel =
        new QLabel("-- %");

    humidityLabel->setObjectName("valueLabel");


    QLabel* windTitle =
        new QLabel("WIND SPEED");

    windTitle->setObjectName("smallTitle");


    windLabel =
        new QLabel("-- km/h");

    windLabel->setObjectName("valueLabel");



    weatherLayout->addWidget(
        cityTitle,
        0,
        0
    );

    weatherLayout->addWidget(
        dateTitle,
        0,
        1
    );

    weatherLayout->addWidget(
        timeTitle,
        0,
        2
    );


    weatherLayout->addWidget(
        cityLabel,
        1,
        0
    );

    weatherLayout->addWidget(
        dateLabel,
        1,
        1
    );

    weatherLayout->addWidget(
        timeLabel,
        1,
        2
    );


    weatherLayout->addWidget(
        temperatureTitle,
        2,
        0
    );

    weatherLayout->addWidget(
        conditionTitle,
        2,
        1
    );

    weatherLayout->addWidget(
        humidityTitle,
        2,
        2
    );


    weatherLayout->addWidget(
        temperatureLabel,
        3,
        0
    );

    weatherLayout->addWidget(
        conditionLabel,
        3,
        1
    );

    weatherLayout->addWidget(
        humidityLabel,
        3,
        2
    );


    weatherLayout->addWidget(
        windTitle,
        4,
        0
    );

    weatherLayout->addWidget(
        windLabel,
        5,
        0
    );


    mainLayout->addWidget(weatherCard);


    QLabel* forecastTitle =
        new QLabel("7-Day Temperature Forecast");

    forecastTitle->setObjectName("forecastTitle");

    mainLayout->addWidget(forecastTitle);



    chartView =
        new QChartView();

    chartView->setMinimumHeight(350);

    chartView->setRenderHint(
        QPainter::Antialiasing
    );

    chartView->setObjectName("chartView");


    QChart* chart =
        new QChart();

    chart->setTitle(
        "Minimum and Maximum Temperature"
    );

    chart->legend()->setVisible(true);

    chart->setAnimationOptions(
        QChart::SeriesAnimations
    );


    chartView->setChart(chart);

    mainLayout->addWidget(
        chartView,
        1
    );


    loadingBar =
        new QProgressBar();

    loadingBar->setRange(0, 0);

    loadingBar->setVisible(false);

    loadingBar->setMaximumHeight(5);

    mainLayout->addWidget(
        loadingBar
    );


    statusLabel =
        new QLabel(
            "Select a city and click Get Weather."
        );

    statusLabel->setObjectName("statusLabel");

    mainLayout->addWidget(
        statusLabel
    );
}



void MainWindow::setupStyles()
{
    setStyleSheet(

        "QMainWindow {"
        "    background-color: #1d2675;"
        "}"

        "QWidget {"
        "    color: #F3F4F6;"
        "    font-family: 'Segoe UI';"
        "    font-size: 14px;"
        "}"

        "#titleLabel {"
        "    font-size: 36px;"
        "    font-weight: 700;"
        "    color: #FFFFFF;"
        "}"

        "#subtitleLabel {"
        "    font-size: 16px;"
        "    color: #9CA3AF;"
        "    margin-bottom: 5px;"
        "}"

        "#card {"
        "    background-color: #172033;"
        "    border: 1px solid #263247;"
        "    border-radius: 14px;"
        "}"

        "#sectionLabel {"
        "    font-size: 15px;"
        "    font-weight: 600;"
        "}"

        "#smallTitle {"
        "    color: #8B95A7;"
        "    font-size: 11px;"
        "    font-weight: 700;"
        "}"

        "#valueLabel {"
        "    font-size: 18px;"
        "    font-weight: 600;"
        "}"

        "#temperatureLabel {"
        "    font-size: 32px;"
        "    font-weight: 700;"
        "}"

        "#conditionLabel {"
        "    font-size: 19px;"
        "    font-weight: 600;"
        "}"

        "#forecastTitle {"
        "    font-size: 22px;"
        "    font-weight: 700;"
        "    margin-top: 5px;"
        "}"

        "#statusLabel {"
        "    color: #9CA3AF;"
        "    font-size: 13px;"
        "}"

        "QComboBox {"
        "    background-color: #0F172A;"
        "    border: 1px solid #334155;"
        "    border-radius: 8px;"
        "    padding: 8px 12px;"
        "    min-height: 25px;"
        "}"

        "QComboBox:hover {"
        "    border: 1px solid #64748B;"
        "}"

        "QComboBox::drop-down {"
        "    border: none;"
        "    width: 30px;"
        "}"

        "QComboBox QAbstractItemView {"
        "    background-color: #172033;"
        "    color: white;"
        "    selection-background-color: #334155;"
        "}"

        "QPushButton {"
        "    background-color: #2563EB;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 10px 18px;"
        "    font-weight: 700;"
        "}"

        "QPushButton:hover {"
        "    background-color: #3B82F6;"
        "}"

        "QPushButton:pressed {"
        "    background-color: #1D4ED8;"
        "}"

        "QPushButton:disabled {"
        "    background-color: #374151;"
        "    color: #9CA3AF;"
        "}"

        "#chartView {"
        "    background-color: #172033;"
        "    border: 1px solid #263247;"
        "    border-radius: 14px;"
        "}"

        "QProgressBar {"
        "    border: none;"
        "    background-color: #1F2937;"
        "}"

        "QProgressBar::chunk {"
        "    background-color: #3B82F6;"
        "}"
    );
}


void MainWindow::populateCities()
{
    std::vector<std::string> cityList =
        cities.GetCities();


    for (const std::string& city : cityList)
    {
        cityComboBox->addItem(
            QString::fromStdString(city)
        );
    }


    if (cityComboBox->count() > 0)
    {
        cityComboBox->setCurrentIndex(0);
    }
}


void MainWindow::getWeather()
{
    if (cityComboBox->currentIndex() < 0)
    {
        setStatus(
            "Please select a city.",
            true
        );

        return;
    }


    QString selectedCity =
        cityComboBox->currentText();


    displayWeather(
        selectedCity.toStdString()
    );
}


void MainWindow::displayWeather(
    const std::string& cityName
)
{

    getWeatherButton->setEnabled(false);

    loadingBar->setVisible(true);


    setStatus(
        "Fetching weather data..."
    );



    std::pair<std::string, std::string> coordinates =
        cities.GetAxis(cityName);


    if (coordinates.first.empty() ||
        coordinates.second.empty())
    {
        setStatus(
            "City coordinates were not found.",
            true
        );

        loadingBar->setVisible(false);

        getWeatherButton->setEnabled(true);

        return;
    }


    Data data;

    Curl curl(
        coordinates.first,
        coordinates.second,
        &data
    );

    CURLcode initResult =
        curl.Curl_Init();


    if (initResult != CURLE_OK)
    {
        setStatus(
            QString(
                "cURL initialization error: %1"
            )
            .arg(
                QString::fromUtf8(
                    curl_easy_strerror(initResult)
                )
            ),
            true
        );


        loadingBar->setVisible(false);

        getWeatherButton->setEnabled(true);

        return;
    }


    CURLcode setupResult =
        curl.Curl_Setup();


    if (setupResult != CURLE_OK)
    {
        setStatus(
            QString(
                "cURL setup error: %1"
            )
            .arg(
                QString::fromUtf8(
                    curl_easy_strerror(setupResult)
                )
            ),
            true
        );


        loadingBar->setVisible(false);

        getWeatherButton->setEnabled(true);

        return;
    }


    CURLcode performResult =
        curl.Curl_Preform();


    if (performResult != CURLE_OK)
    {
        setStatus(
            QString(
                "Network error: %1"
            )
            .arg(
                QString::fromUtf8(
                    curl_easy_strerror(performResult)
                )
            ),
            true
        );


        loadingBar->setVisible(false);

        getWeatherButton->setEnabled(true);

        return;
    }


    char* response =
        data.GetResponse();


    if (response == nullptr ||
        data.GetSize() == 0)
    {
        setStatus(
            "The weather API returned an empty response.",
            true
        );


        loadingBar->setVisible(false);

        getWeatherButton->setEnabled(true);

        return;
    }


    Rapidjson weather(
        response
    );

    cityLabel->setText(
        QString::fromStdString(cityName)
    );


    dateLabel->setText(
        QString::fromStdString(
            weather.GetData()
        )
    );


    timeLabel->setText(
        QString::fromStdString(
            weather.GetTime()
        )
    );


    float temperature =
        weather.GetTemp();


    temperatureLabel->setText(
        QString("%1 °C")
            .arg(
                QString::number(
                    temperature,
                    'f',
                    1
                )
            )
    );


    int weatherCode =
        weather.GetWeatherCode();


    conditionLabel->setText(
        weatherIcon(weatherCode) +
        " " +
        weatherDescription(weatherCode)
    );


    float humidity =
        weather.GetHumidity();


    humidityLabel->setText(
        QString("%1 %")
            .arg(
                QString::number(
                    humidity,
                    'f',
                    0
                )
            )
    );


    float windSpeed =
        weather.GetWindSpeed();


    windLabel->setText(
        QString("%1 km/h")
            .arg(
                QString::number(
                    windSpeed,
                    'f',
                    1
                )
            )
    );

    updateForecastChart();


    loadingBar->setVisible(false);

    getWeatherButton->setEnabled(true);


    setStatus(
        QString(
            "Weather updated successfully • %1"
        )
        .arg(
            QString::fromStdString(cityName)
        )
    );
}


void MainWindow::updateCurrentWeather()
{
}



void MainWindow::updateForecastChart()
{

    QString selectedCity =
        cityComboBox->currentText();


    if (selectedCity.isEmpty())
    {
        return;
    }
    std::pair<std::string, std::string> coordinates =
        cities.GetAxis(
            selectedCity.toStdString()
        );


    if (coordinates.first.empty())
    {
        return;
    }


    Data data;


    Curl curl(
        coordinates.first,
        coordinates.second,
        &data
    );


    if (curl.Curl_Init() != CURLE_OK)
    {
        return;
    }


    if (curl.Curl_Setup() != CURLE_OK)
    {
        return;
    }


    if (curl.Curl_Preform() != CURLE_OK)
    {
        return;
    }


    if (data.GetResponse() == nullptr)
    {
        return;
    }


    Rapidjson weather(
        data.GetResponse()
    );


    float* minTemp =
        weather.GetMinForecastTemp();


    float* maxTemp =
        weather.GetMaxForecastTemp();


    std::string* dates =
        weather.GetForecastDate();


    QChart* chart =
        new QChart();


    chart->setTitle(
        "7-Day Temperature Forecast"
    );


    chart->setAnimationOptions(
        QChart::SeriesAnimations
    );


    chart->legend()->setVisible(true);


    QLineSeries* minSeries =
        new QLineSeries();


    minSeries->setName(
        "Minimum °C"
    );


    QLineSeries* maxSeries =
        new QLineSeries();


    maxSeries->setName(
        "Maximum °C"
    );


    for (int i = 0; i < 7; i++)
    {
        minSeries->append(
            i,
            minTemp[i]
        );


        maxSeries->append(
            i,
            maxTemp[i]
        );
    }


    chart->addSeries(
        minSeries
    );


    chart->addSeries(
        maxSeries
    );

    QCategoryAxis* axisX =
        new QCategoryAxis();


    for (int i = 0; i < 7; i++)
    {
        QString date =
            QString::fromStdString(
                dates[i]
            );


        if (date.length() >= 10)
        {
            date =
                date.mid(5, 5);
        }


        axisX->append(
            date,
            i
        );
    }


    axisX->setTitleText(
        "Date"
    );


    QValueAxis* axisY =
        new QValueAxis();


    axisY->setTitleText(
        "Temperature (°C)"
    );


    float minimum =
        minTemp[0];


    float maximum =
        maxTemp[0];


    for (int i = 0; i < 7; i++)
    {
        minimum =
            std::min(
                minimum,
                minTemp[i]
            );


        maximum =
            std::max(
                maximum,
                maxTemp[i]
            );
    }

    axisY->setRange(
        std::floor(minimum - 2),
        std::ceil(maximum + 2)
    );


    axisY->setLabelFormat(
        "%.0f°C"
    );

    chart->addAxis(
        axisX,
        Qt::AlignBottom
    );


    chart->addAxis(
        axisY,
        Qt::AlignLeft
    );


    minSeries->attachAxis(
        axisX
    );


    minSeries->attachAxis(
        axisY
    );


    maxSeries->attachAxis(
        axisX
    );


    maxSeries->attachAxis(
        axisY
    );

    chartView->setChart(
        chart
    );
}


QString MainWindow::weatherDescription(
    int weatherCode
) const
{
 
    switch (weatherCode)
    {
        case 0:
            return "Clear sky";

        case 1:
            return "Mainly clear";

        case 2:
            return "Partly cloudy";

        case 3:
            return "Overcast";

        case 45:
        case 48:
            return "Fog";

        case 51:
        case 53:
        case 55:
            return "Drizzle";

        case 56:
        case 57:
            return "Freezing drizzle";

        case 61:
        case 63:
        case 65:
            return "Rain";

        case 66:
        case 67:
            return "Freezing rain";

        case 71:
        case 73:
        case 75:
            return "Snow fall";

        case 77:
            return "Snow grains";

        case 80:
        case 81:
        case 82:
            return "Rain showers";

        case 85:
        case 86:
            return "Snow showers";

        case 95:
            return "Thunderstorm";

        case 96:
        case 99:
            return "Thunderstorm with hail";

        default:
            return "Unknown";
    }
}

QString MainWindow::weatherIcon(
    int weatherCode
) const
{
    if (weatherCode == 0)
    {
        return "☀";
    }


    if (weatherCode == 1 ||
        weatherCode == 2)
    {
        return "🌤";
    }


    if (weatherCode == 3)
    {
        return "☁";
    }


    if (weatherCode == 45 ||
        weatherCode == 48)
    {
        return "🌫";
    }


    if (weatherCode >= 51 &&
        weatherCode <= 67)
    {
        return "🌧";
    }


    if (weatherCode >= 71 &&
        weatherCode <= 86)
    {
        return "❄";
    }


    if (weatherCode >= 95)
    {
        return "⛈";
    }


    return "🌡";
}


void MainWindow::setStatus( 
    const QString& message,
    bool error
)
{
    statusLabel->setText(
        message
    );


    if (error)
    {
        statusLabel->setStyleSheet(
            "color: #F87171;"
        );
    }
    else
    {
        statusLabel->setStyleSheet(
            "color: #9CA3AF;"
        );
    }


    QApplication::processEvents();}
