#include "Request.h"

#include <QFileDialog>
#include <QNetworkReply>
#include <QThread>
#include "NetworkAccessManager.h"
#include <qguiapplication.h>
#include <thread>

#include "../../../../../libs/ShaderModel/shaders/Tools/Thread/DateTimeThread.h"
#include "RequestConnect.h"
#include "NetworkRequest.h"
using namespace cylHttpNetWork;

size_t Request::sleep( const size_t &milliseconds ) {
	if( milliseconds == 0 )
		return milliseconds;
	auto point = std::chrono::system_clock::now( );
	auto timeSinceEpoch = point.time_since_epoch( );
	auto timePoint = std::chrono::duration_cast< std::chrono::milliseconds >( timeSinceEpoch ).count( );
	do {
		point = std::chrono::system_clock::now( );
		timeSinceEpoch = point.time_since_epoch( );
		auto nowPoint = std::chrono::duration_cast< std::chrono::milliseconds >( timeSinceEpoch ).count( );
		auto duration = nowPoint - timePoint;
		if( duration > milliseconds )
			break;
		qApp->processEvents( );
	} while( true );
	return milliseconds;
}

Request::Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, QObject *parent, Qt::ConnectionType connection_type ) : networkAccessManager( networkAccessManager )
, QObject( parent )
, requestConnect( requestConnect ) {
	requestConnect->setNetworkAccessManager( networkAccessManager, connection_type );
}

Request::Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, Qt::ConnectionType connection_type ): Request( networkAccessManager, requestConnect, nullptr, connection_type ) {
}
Request::~Request( ) {
}

QNetworkReply * Request::netGetWork( const QUrl &url, size_t milliseconds, Qt::ConnectionType connect_type ) {
	NetworkRequest request;
	request.setUrl( url );
	return netGetWork( request, milliseconds, connect_type );
}
QNetworkReply * Request::netGetWork( const QUrl &url, const NetworkRequest &network_request, size_t milliseconds, Qt::ConnectionType connect_type ) {
	NetworkRequest request = network_request;
	request.setUrl( url );
	return this->netGetWork( request, milliseconds, connect_type );
}
QNetworkReply * Request::netGetWork( const QUrl &url, Qt::ConnectionType connect_type ) {
	NetworkRequest request;
	request.setUrl( url );
	return netGetWork( request, connect_type );
}
QNetworkReply * Request::netGetWork( const QUrl &url, const NetworkRequest &network_request, Qt::ConnectionType connect_type ) {
	NetworkRequest networkRequest = network_request;
	networkRequest.setUrl( url );
	return netGetWork( networkRequest, connect_type );
}
QNetworkReply * Request::netGetWork( const NetworkRequest &network_request, size_t milliseconds, Qt::ConnectionType connect_type ) {
	requestConnect->setNetworkAccessManager( networkAccessManager, connect_type );
	// 上次请求的时间
	NetworkRequest::Time_Duration timeDuration;
	auto qUrl = network_request.url( );
	if( NetworkRequest::getHostLastRequestTime( qUrl, timeDuration ) ) {
		NetworkRequest::Time_Duration nowTimeDuration = NetworkRequest::getNowTimeDuration( );
		auto duration = nowTimeDuration - timeDuration;
		auto timeDurationToMilliseconds = cylHttpNetWork::NetworkRequest::getTimeDurationToMilliseconds( duration );
		if( timeDurationToMilliseconds >= 0 && timeDurationToMilliseconds < milliseconds )
			sleep( milliseconds - timeDurationToMilliseconds );
	}
	QNetworkReply *networkReply = networkAccessManager->get( network_request );
	requestConnect->setNetworkReply( networkReply, connect_type );
	cylHttpNetWork::NetworkRequest::updateCurrentTimeToHostLastRequestTime( qUrl );
	return networkReply;
}
QNetworkReply * Request::netGetWork( const NetworkRequest &network_request, Qt::ConnectionType connect_type ) {
	requestConnect->setNetworkAccessManager( networkAccessManager, connect_type );
	// 上次请求的时间
	NetworkRequest::Time_Duration timeDuration;

	auto qUrl = network_request.url( );
	if( NetworkRequest::getHostLastRequestTime( qUrl, timeDuration ) ) {
		auto milliseconds = cylHttpNetWork::NetworkRequest::getHostUrlRequestInterval( qUrl );
		NetworkRequest::Time_Duration nowTimeDuration = NetworkRequest::getNowTimeDuration( );
		auto duration = nowTimeDuration - timeDuration;
		auto timeDurationToMilliseconds = cylHttpNetWork::NetworkRequest::getTimeDurationToMilliseconds( duration );
		if( timeDurationToMilliseconds >= 0 && timeDurationToMilliseconds < milliseconds )
			sleep( milliseconds - timeDurationToMilliseconds );
	}

	QNetworkReply *networkReply = networkAccessManager->get( network_request );
	requestConnect->setNetworkReply( networkReply, connect_type );
	cylHttpNetWork::NetworkRequest::updateCurrentTimeToHostLastRequestTime( qUrl );
	return networkReply;
}
