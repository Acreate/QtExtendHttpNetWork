#include "Request.h"

#include <QFileDialog>
#include <QNetworkReply>

#include "NetworkAccessManager.h"
#include <qguiapplication.h>
#include <thread>

#include "RequestConnect.h"
#include "NetworkRequest.h"
using namespace cylHttpNetWork;


Request::Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, QObject *parent, Qt::ConnectionType connection_type ) : networkAccessManager( networkAccessManager )
, QObject( parent )
, requestConnect( requestConnect ) {
	requestConnect->setNetworkAccessManager( networkAccessManager, connection_type );
}

Request::Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, Qt::ConnectionType connection_type ): Request( networkAccessManager, requestConnect, nullptr, connection_type ) {
}
Request::~Request( ) {
}


QNetworkReply * Request::netGetWork( const QUrl &url, std::chrono::microseconds microseconds, Qt::ConnectionType connect_type ) {
	NetworkRequest request;
	request.setUrl( url );
	return netGetWork( request, microseconds, connect_type );
}

QNetworkReply * Request::netGetWork( const QUrl &url, NetworkRequest &network_request, std::chrono::microseconds microseconds, Qt::ConnectionType connect_type ) {
	NetworkRequest networkRequest = network_request;
	networkRequest.setUrl( url );
	return netGetWork( networkRequest, microseconds, connect_type );
}
QNetworkReply * Request::netGetWork( NetworkRequest &network_request, std::chrono::microseconds microseconds, Qt::ConnectionType connect_type ) {
	requestConnect->setNetworkAccessManager( networkAccessManager, connect_type );
	QNetworkReply *networkReply = networkAccessManager->get( network_request );
	requestConnect->setNetworkReply( networkReply, connect_type );
	std::this_thread::sleep_for( microseconds );
	return networkReply;
}
