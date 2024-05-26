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

QNetworkReply * Request::getNetworkReplyMilliseconds( size_t &request_milliseconds, const size_t &milliseconds ) {
	QNetworkReply *networkReply = waitFinish( milliseconds );
	if( networkReply->error( ) == QNetworkReply::NoError )
		return networkReply; // 没有发生错误
	QUrl qUrl = networkReply->url( );
	// 获取当前时间
	auto startGetNetworkReplyCallFunctionTime = NetworkRequest::getTimeDurationToMilliseconds( NetworkRequest::getNowTimeDuration( ) );
	do {
		if( networkReply->error( ) == QNetworkReply::NoError )
			break; // 没有发生错误
		// 当前时间减去上次请求时间，获得时间间隔
		long long sepMillisecondsTime = NetworkRequest::getTimeDurationToMilliseconds( NetworkRequest::getNowTimeDuration( ) ) - startGetNetworkReplyCallFunctionTime;
		if( sepMillisecondsTime > request_milliseconds )
			break; // 间隔大于设置的时间，则退出请求
		// 重新请求
		netGetWork( qUrl, *this->networkRequest );
		// 阻塞，等待完成
		networkReply = waitFinish( milliseconds );
	} while( true );

	return networkReply;
}
QNetworkReply * Request::getNetworkReply( size_t request_milliseconds, size_t repeatRequestCount, const size_t &milliseconds ) {
	QNetworkReply *networkReply = waitFinish( milliseconds );
	if( networkReply->error( ) == QNetworkReply::NoError )
		return networkReply; // 没有发生错误
	QUrl qUrl = networkReply->url( );
	// 获取当前时间
	auto startGetNetworkReplyCallFunctionTime = NetworkRequest::getTimeDurationToMilliseconds( NetworkRequest::getNowTimeDuration( ) );
	while( repeatRequestCount != 0 && networkReply->error( ) != QNetworkReply::NoError ) {
		// 当前时间减去上次请求时间，获得时间间隔
		long long sepMillisecondsTime = NetworkRequest::getTimeDurationToMilliseconds( NetworkRequest::getNowTimeDuration( ) ) - startGetNetworkReplyCallFunctionTime;
		if( sepMillisecondsTime > request_milliseconds )
			break; // 间隔大于设置的时间，则退出请求
		// 重新请求
		netGetWork( qUrl, *this->networkRequest );
		// 阻塞，等待完成
		networkReply = waitFinish( milliseconds );
		--repeatRequestCount;
	};

	return networkReply;
}
QNetworkReply * Request::getNetworkReplyCount( size_t repeatRequestCount, const size_t &milliseconds ) {
	QNetworkReply *networkReply = waitFinish( milliseconds );
	while( repeatRequestCount != 0 && networkReply->error( ) != QNetworkReply::NoError ) { // 如果发生错误，并且需要重新请求
		// 请求
		netGetWork( networkReply->url( ), *this->networkRequest );
		// 等待，阻塞
		networkReply = waitFinish( milliseconds );
		// 减少请求次数
		repeatRequestCount = repeatRequestCount - 1;
	}
	return networkReply;
}
QNetworkReply * Request::getNetworkReply( size_t milliseconds ) {
	QNetworkReply *networkReply = waitFinish( milliseconds );
	if( networkReply->error( ) != QNetworkReply::NoError ) { // 如果发生错误，并且需要重新请求
		// 请求
		netGetWork( networkReply->url( ), *this->networkRequest );
		// 等待，阻塞
		networkReply = getNetworkReply( milliseconds );
	}
	return networkReply;
}
size_t Request::sleep( const size_t &milliseconds ) {
	if( milliseconds == 0 )
		return milliseconds;
	auto point = std::chrono::system_clock::now( );
	auto timeSinceEpoch = point.time_since_epoch( );
	auto timePoint = NetworkRequest::getTimeDurationToMilliseconds( timeSinceEpoch );
	do {
		point = std::chrono::system_clock::now( );
		timeSinceEpoch = point.time_since_epoch( );
		auto nowPoint = NetworkRequest::getTimeDurationToMilliseconds( timeSinceEpoch );
		auto duration = nowPoint - timePoint;
		if( duration > milliseconds )
			break;
		qApp->processEvents( );
	} while( true );
	return milliseconds;
}

Request::Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, QObject *parent, Qt::ConnectionType connection_type ) : networkAccessManager( networkAccessManager )
, QObject( parent )
, requestConnect( requestConnect )
, networkRequest( nullptr ) {
	requestConnect->setNetworkAccessManager( networkAccessManager, connection_type );
}

Request::Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, Qt::ConnectionType connection_type ): Request( networkAccessManager, requestConnect, nullptr, connection_type ) {
}
Request::~Request( ) {
}

int32_t Request::netGetWork( const QUrl &url, size_t milliseconds, Qt::ConnectionType connect_type ) {
	NetworkRequest request;
	request.setUrl( url );
	return netGetWork( request, milliseconds, connect_type );
}
int32_t Request::netGetWork( const QUrl &url, const NetworkRequest &network_request, size_t milliseconds, Qt::ConnectionType connect_type ) {
	NetworkRequest request = network_request;
	request.setUrl( url );
	return this->netGetWork( request, milliseconds, connect_type );
}
int32_t Request::netGetWork( const QUrl &url, Qt::ConnectionType connect_type ) {
	NetworkRequest request;
	request.setUrl( url );
	return netGetWork( request, connect_type );
}
int32_t Request::netGetWork( const QUrl &url, const NetworkRequest &network_request, Qt::ConnectionType connect_type ) {
	NetworkRequest networkRequest = network_request;
	networkRequest.setUrl( url );
	return netGetWork( networkRequest, connect_type );
}
int32_t Request::netGetWork( const NetworkRequest &network_request, size_t milliseconds, Qt::ConnectionType connect_type ) {
	if( !requestConnect->setNetworkAccessManager( networkAccessManager, connect_type ) )
		return -1;
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
	networkRequest = std::make_shared< NetworkRequest >( network_request );
	QNetworkReply *networkReply = networkAccessManager->get( network_request );
	auto resultCode = 0;
	if( !requestConnect->setNetworkReply( networkReply, connect_type ) )
		resultCode = -2;
	cylHttpNetWork::NetworkRequest::updateCurrentTimeToHostLastRequestTime( qUrl );
	return resultCode;
}
QNetworkReply * Request::waitFinish( size_t milliseconds ) {
	if( requestConnect ) {
		auto networkReply = requestConnect->getNetworkReply( );
		if( !networkReply )
			return nullptr;
		if( networkReply->isRunning( ) )
			while( !networkReply->isFinished( ) )
				sleep( milliseconds );
		return networkReply;
	}
	return nullptr;
}
int32_t Request::netGetWork( const NetworkRequest &network_request, Qt::ConnectionType connect_type ) {
	this->connectType = connect_type;
	if( !requestConnect->setNetworkAccessManager( networkAccessManager, connect_type ) )
		return -1;
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
	networkRequest = std::make_shared< NetworkRequest >( network_request );
	QNetworkReply *networkReply = networkAccessManager->get( network_request );
	auto resultCode = 0;
	if( !requestConnect->setNetworkReply( networkReply, connect_type ) )
		resultCode = -2;
	cylHttpNetWork::NetworkRequest::updateCurrentTimeToHostLastRequestTime( qUrl );
	return resultCode;
}
