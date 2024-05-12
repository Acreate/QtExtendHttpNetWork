#include "RequestConnect.h"
#include "Request.h"
using namespace cylHttpNetWork;
#include "NetworkAccessManager.h"
RequestConnect::RequestConnect( QObject *parent ): QObject( parent )
, networkAccessManager( nullptr )
, networkReply( nullptr ) {
}
RequestConnect::~RequestConnect( ) {

}
bool RequestConnect::setNetworkAccessManager( NetworkAccessManager *networkAccessManager, Qt::ConnectionType connect_type ) {
	if( this->networkAccessManager )
		if( this->networkAccessManager == networkAccessManager )
			return true;
		else
			return false;
	this->networkAccessManager = networkAccessManager;
	connect( networkAccessManager, &QNetworkAccessManager::authenticationRequired,
		this, &RequestConnect::networkAccessManagerAuthenticationRequired, connect_type );
	connect( networkAccessManager, &QNetworkAccessManager::encrypted,
		this, &RequestConnect::networkAccessManagerEncrypted, connect_type );
	connect( networkAccessManager, &QNetworkAccessManager::finished,
		this, &RequestConnect::networkAccessManagerFinished, connect_type );
	connect( networkAccessManager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired,
		this, &RequestConnect::networkAccessManagerPreSharedKeyAuthenticationRequired, connect_type );
	connect( networkAccessManager, &QNetworkAccessManager::proxyAuthenticationRequired,
		this, &RequestConnect::networkAccessManagerProxyAuthenticationRequired, connect_type );
	connect( networkAccessManager, &QNetworkAccessManager::sslErrors,
		this, &RequestConnect::networkAccessManagerSslErrors, connect_type );
	return true;
}
bool RequestConnect::setNetworkReply( QNetworkReply *networkReply, Qt::ConnectionType connect_type ) {
	if( this->networkReply )
		if( this->networkReply == networkReply )
			return true;
		else
			return false;

	this->networkReply = networkReply;
	connect( this, &RequestConnect::networkReplyMetaDataFinished, [=]( ) {
		emit networkReplyFinished( this );
	} );

	connect( networkReply, &QNetworkReply::socketStartedConnecting,
		this, &RequestConnect::networkReplySocketStartedConnecting, connect_type );
	connect( networkReply, &QNetworkReply::requestSent,
		this, &RequestConnect::networkReplyRequestSent, connect_type );
	connect( networkReply, &QNetworkReply::metaDataChanged,
		this, &RequestConnect::networkReplyMetaDataChanged, connect_type );
	connect( networkReply, &QNetworkReply::finished,
		this, &RequestConnect::networkReplyMetaDataFinished, connect_type );
	connect( networkReply, &QNetworkReply::errorOccurred,
		this, &RequestConnect::networkReplyErrorOccurred, connect_type );
#if QT_CONFIG( ssl )
	connect( networkReply, &QNetworkReply::encrypted,
		this, &RequestConnect::networkReplyEncrypted,
		connect_type );
	connect( networkReply, &QNetworkReply::sslErrors,
		this, &RequestConnect::networkReplySslErrors,
		connect_type );
	connect( networkReply, &QNetworkReply::preSharedKeyAuthenticationRequired,
		this, &RequestConnect::networkReplyPreSharedKeyAuthenticationRequired,
		connect_type );
#endif
	connect( networkReply, &QNetworkReply::redirected,
		this, &RequestConnect::networkReplyRedirected,
		connect_type );
	connect( networkReply, &QNetworkReply::redirectAllowed,
		this, &RequestConnect::networkReplyRedirectAllowed,
		connect_type );
	connect( networkReply, &QNetworkReply::uploadProgress,
		this, &RequestConnect::networkReplyUploadProgress,
		connect_type );
	connect( networkReply, &QNetworkReply::downloadProgress,
		this, &RequestConnect::networkReplyDownloadProgress,
		connect_type );
	return true;
}
