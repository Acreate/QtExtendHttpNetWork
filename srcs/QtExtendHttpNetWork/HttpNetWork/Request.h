#ifndef REQUEST_H_H_HEAD__FILE__
#define REQUEST_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QSettings>
#include <QNetworkReply>
#include "../nameSpace/httpNetWork.h"
namespace cylHttpNetWork {

	class QTEXTENDHTTPNETWORK_EXPORT Request : public QObject {
		Q_OBJECT;
	private:
		QSettings *setting = nullptr;
		NetworkAccessManager *networkAccessManager;
		RequestConnect *requestConnect;
	public:
		Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, Qt::ConnectionType connection_type = Qt::AutoConnection );
		Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, QObject *parent, Qt::ConnectionType connection_type = Qt::AutoConnection );
		~Request( ) override;
	public:
		QNetworkReply * netGetWork( const QUrl &url, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( const QUrl &url, NetworkRequest &network_request, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( NetworkRequest &network_request, Qt::ConnectionType connect_type = Qt::AutoConnection );

		QNetworkReply * netGetWork( const QUrl &url, std::chrono::microseconds microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( const QUrl &url, NetworkRequest &network_request, std::chrono::microseconds microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( NetworkRequest &network_request, std::chrono::microseconds microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );

		QNetworkReply * netGetWork( const QUrl &url, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( const QUrl &url, NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );

	};

}
#endif // REQUEST_H_H_HEAD__FILE__
