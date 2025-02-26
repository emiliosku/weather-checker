#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QObject>
#include <QGeoCoordinate>

class Locations {
private:

    /**
     * @brief m_city Stores the name of the city.
     */
    QString m_city;

    /**
     * @brief m_state Stores the name of the state or region.
     */
    QString m_state;

    /**
     * @brief m_country Stores the name of the country.
     */
    QString m_country;

    /**
     * @brief m_latitude Represents the latitude coordinate.
     */
    float m_latitude;

    /**
     * @brief m_longitude Represents the longitude coordinate.
     */
    float m_longitude;

    /**
     * @brief m_coordinates Stores the geographic coordinates (latitude and longitude) as a QGeoCoordinate object.
     */
    QGeoCoordinate m_coordinates;

public:
    /**
     * @brief Locations Default constructor
     */
    Locations() = default;

    /**
     * @brief Locations Custom constructor.
     *
     * @param city City name.
     * @param state Province or state name.
     * @param country Country name.
     * @param latitude City latitude.
     * @param longitude City longitude.
     */
    Locations(const QString &city,
              const QString &state,
              const QString &country,
              const QString &latitude,
              const QString &longitude);

    /**
     * @brief Locations Custom constructor.
     *
     * @param city City name.
     * @param state Province or state name.
     * @param country Country name.
     * @param latitude City latitude.
     * @param longitude City longitude.
     */
    Locations(const QString &city,
              const QString &state,
              const QString &country,
              const float latitude,
              const float longitude);
    /**
     * @brief getCityName Gets the location city name.
     * @return The location city name.
     */
    QString getCityName();

    /**
     * @brief getStateName Gets the location state name.
     * @return The location state name.
     */
    QString getStateName();

    /**
     * @brief getCountryName Gets the location country name.
     * @return The location country name.
     */
    QString getCountryName();

    /**
     * @brief getCityLatitude Gets the location Latitude.
     * @return The location latitude.
     */
    float getCityLatitude();

    /**
     * @brief getCityLongitude Gets the location longitude.
     * @return The location longitude.
     */
    float getCityLongitude();

    /**
     * @brief getCityCoordinates Gets the location coordinates.
     * @return The location coordinates
     */
    QGeoCoordinate getCityCoordinates();

    /**
     * @brief reset Resets all the location fields.
     */
    void reset();
};

#endif // LOCATIONS_H
