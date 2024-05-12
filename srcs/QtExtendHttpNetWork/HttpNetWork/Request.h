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

		QNetworkReply * netGetWork( const QUrl &url, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( const QUrl &url, NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		QNetworkReply * netGetWork( NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
	public: // - 静态对象
		/// <summary>
		/// 睡眠指定的时间-毫秒
		/// </summary>
		/// <param name="milliseconds">毫秒</param>
		/// <returns>毫秒</returns>
		static size_t sleep(const size_t &milliseconds);
	};

}
#endif // REQUEST_H_H_HEAD__FILE__
