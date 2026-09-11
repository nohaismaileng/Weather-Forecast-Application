#include <QApplication>

#include "Cities.h"
#include "GUI/mainWindow.h"


int main(int argc, char *argv[])
{


    QApplication app(argc, argv);


    Cities cities;


    cities.AddCity(
        "Cairo",
        "30.0444",
        "31.2357"
    );

    cities.AddCity(
        "Alexandria",
        "31.2001",
        "29.9187"
    );

    cities.AddCity(
        "Giza",
        "30.0131",
        "31.2089"
    );

    cities.AddCity(
        "Luxor",
        "25.6872",
        "32.6396"
    );

    cities.AddCity(
        "Aswan",
        "24.0889",
        "32.8998"
    );

    cities.AddCity(
        "Hurghada",
        "27.2579",
        "33.8116"
    );

    cities.AddCity(
        "Sharm El Sheikh",
        "27.9158",
        "34.3299"
    );

    cities.AddCity(
        "Port Said",
        "31.2653",
        "32.3019"
    );

    cities.AddCity(
        "Suez",
        "29.9668",
        "32.5498"
    );

    cities.AddCity(
        "Mansoura",
        "31.0409",
        "31.3785"
    );

    MainWindow window(cities);


    window.show();

    return app.exec();
}