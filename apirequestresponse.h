#ifndef APIREQUESTRESPONSE_H
#define APIREQUESTRESPONSE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class APIRequestResponse : public QObject {
private:
    Q_OBJECT

    // Private objects that will only be used within this class.

    /**
     * @brief m_networkManager Object to handle network connections.
     */
    QNetworkAccessManager *m_networkManager;


public:
    // Class constructor and destructor
    explicit APIRequestResponse(QObject *parent = nullptr);
    ~APIRequestResponse();

    /**
     * @brief sendGetRequest Sends a GET request to the provided URL.
     * @param url API's URL
     */
    void sendGetRequest(const QString &url);

    /**
     * @brief sendPostRequest Sends a POST request to the provided URL.
     * @param url API's URL
     * @param payload Payload of the sent request.
     */
    void sendPostRequest(const QString &url, const QJsonObject &payload);

private:
    /**
     * @brief parseResponse Parses the API's received reply.
     * @param reply Raw reply from the API.
     * @return Parsed reply from the API.
     */
    QJsonObject parseResponse(QNetworkReply *reply);

signals:
    void requestCompleted(const QJsonObject &response);

public slots:
    /**
     * @brief manageResponse Handles the response when it has already been parsed.
     * @param response Parsed response received from the API.
     */
    void manageResponse(const QJsonObject &response);

private slots:
    void onRequestFinished(QNetworkReply *reply);
};

#endif // APIREQUESTRESPONSE_H
