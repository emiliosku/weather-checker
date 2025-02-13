#ifndef LOCATIONSMANAGER_H
#define LOCATIONSMANAGER_H

#include <QObject>

#include "locations.h"
#include "apirequestresponse.h"


class LocationsManager : public QObject {
private:
    Q_OBJECT

    APIRequestResponse m_apiClient;

    Locations m_location;


public:
    explicit LocationsManager(QObject *parent = nullptr);



private:


signals:
};

#endif // LOCATIONSMANAGER_H
