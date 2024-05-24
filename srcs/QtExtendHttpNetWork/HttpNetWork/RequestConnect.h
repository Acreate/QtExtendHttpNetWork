#ifndef REQUESTCONNECT_H_H_HEAD__FILE__
#define REQUESTCONNECT_H_H_HEAD__FILE__
#pragma once
#include <QNetworkReply>
#include <qmutex.h>
#include <qtmetamacros.h>

#include "../nameSpace/httpNetWork.h"

namespace cylHttpNetWork {

	class QTEXTENDHTTPNETWORK_EXPORT RequestConnect : public QObject {
		Q_OBJECT;
	public:
		friend class Request;
	private:
		NetworkAccessManager *networkAccessManager;
		QNetworkReply *networkReply;
		Qt::ConnectionType connectType;
	public:
		RequestConnect( QObject *parent = nullptr );
		~RequestConnect( ) override;
	public:
		NetworkAccessManager * getNetworkAccessManager( ) const {
			return networkAccessManager;
		}
		QNetworkReply * getNetworkReply( ) const {
			return networkReply;
		}
	private:
		/// <summary>
		/// 设置 NetworkAccessManager 对象转发体
		/// </summary>
		/// <param name="request">转发对象</param>
		/// <param name="connect_type">信号槽链接类型</param>
		/// <returns>失败返回 false</returns>
		bool setNetworkAccessManager( NetworkAccessManager *request, Qt::ConnectionType connect_type = Qt::AutoConnection );
		/// <summary>
		/// 设置 QNetworkReply 对象转发体
		/// </summary>
		/// <param name="networkReply">转发对象</param>
		/// <param name="connect_type">信号槽链接类型</param>
		/// <returns>失败返回 false</returns>
		bool setNetworkReply( QNetworkReply *networkReply, Qt::ConnectionType connect_type = Qt::AutoConnection );
	Q_SIGNALS: //  QNetworkAccessManager 转发
		void networkAccessManagerAuthenticationRequired( QNetworkReply *reply, QAuthenticator *authenticator );
		void networkAccessManagerEncrypted( QNetworkReply *reply );
		void networkAccessManagerFinished( QNetworkReply *reply );
		void networkAccessManagerPreSharedKeyAuthenticationRequired( QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator );
		void networkAccessManagerProxyAuthenticationRequired( const QNetworkProxy &proxy, QAuthenticator *authenticator );
		void networkAccessManagerSslErrors( QNetworkReply *reply, const QList< QSslError > &errors );
	Q_SIGNALS: //  QNetworkReply 转发
		void networkReplySocketStartedConnecting( );
		void networkReplyRequestSent( );
		void networkReplyMetaDataChanged( );
		void networkReplyMetaDataFinished( );
		void networkReplyFinished( RequestConnect *requestConnect );
		void networkReplyErrorOccurred( QNetworkReply::NetworkError );
#if QT_CONFIG( ssl )
		void networkReplyEncrypted( );
		void networkReplySslErrors( const QList< QSslError > &errors );
		void networkReplyPreSharedKeyAuthenticationRequired( QSslPreSharedKeyAuthenticator *authenticator );
#endif
		void networkReplyRedirected( const QUrl &url );
		void networkReplyRedirectAllowed( );

		void networkReplyUploadProgress( qint64 bytesSent, qint64 bytesTotal );
		void networkReplyDownloadProgress( qint64 bytesReceived, qint64 bytesTotal );
	};

}

#endif // REQUESTCONNECT_H_H_HEAD__FILE__
