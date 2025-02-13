#include "weathermanager.h"

//static constexpr QString METEO_API_QUERY="https://api.open-meteo.com/v1/forecast?latitude=41.34&longitude=2&current=temperature_2m,relative_humidity_2m,apparent_temperature,precipitation,rain,showers,weather_code&hourly=temperature_2m,apparent_temperature,precipitation_probability,rain,showers,snowfall,weather_code&daily=temperature_2m_max,temperature_2m_min,apparent_temperature_max,apparent_temperature_min&timezone=Europe%2FBerlin&forecast_days=3";
//static constexpr QString GEO_API_QUERY="https://nominatim.openstreetmap.org/search?q=terrassa&format=xml";

WeatherManager::WeatherManager(QObject *parent)
    : QObject{parent},
    m_currentTemperature{},
    m_currentTemperatureFeeling{},
    m_umbrella{false} {

}
