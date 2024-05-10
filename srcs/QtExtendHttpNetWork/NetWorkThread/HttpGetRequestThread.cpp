#include "HttpGetRequestThread.h"

#include <qbrush.h>

#include "../HttpNetWork/NetworkAccessManager.h"
#include "../HttpNetWork/RequestConnect.h"
#include "../HttpNetWork/NetworkRequest.h"
#include "../HttpNetWork/Request.h"

using namespace cylHttpNetWork;
HttpGetRequestThread::HttpGetRequestThread( QObject *parent ) : QThread( parent ), currntStatus( None ) {
	initConnect( );
}
HttpGetRequestThread::~HttpGetRequestThread( ) {
}
void HttpGetRequestThread::initConnect( ) {
	connect( this, &HttpGetRequestThread::change_request_status, [&]( THREAD_CURRNT_STATUS new_work_status ) {
		while( this->currntStatus != Standby )
			usleep( 100 );
		this->currntStatus = new_work_status;
	} );
	connect( this, &HttpGetRequestThread::set_request_url, [&]( const QUrl &url ) {
		currentUrl = url;
	} );
}
void HttpGetRequestThread::run( ) {
	auto networkAccessManagerSPtr = new NetworkAccessManager( );
	auto networkRequestSPtr = new NetworkRequest( );
	networkRequestSPtr->setHeader( QNetworkRequest::UserAgentHeader, networkRequestSPtr->getRandomUserAgentHeader( ) );
	currntStatus = Standby;
	RequestConnect *requestConnect = new RequestConnect;
	Request *request = new Request( networkAccessManagerSPtr, requestConnect, Qt::QueuedConnection );
	while( currntStatus != Exit ) {
		switch( currntStatus ) {
			case Request_Root : { // 处理网页请求
				currntStatus = Work_Net;
				connect( requestConnect, &RequestConnect::networkReplyFinished,
					this, &HttpGetRequestThread::networkReplyFinished, Qt::QueuedConnection );
				connect( requestConnect, &RequestConnect::networkReplyErrorOccurred,
					this, &HttpGetRequestThread::networkReplyErrorOccurred, Qt::QueuedConnection );
				qDebug( ) << u8"case Request_Root : " << currentUrl;
				emit requesting_get_root_page_signals( currentUrl );
				request->netGetWork( currentUrl, *networkRequestSPtr, Qt::QueuedConnection );
				break;
			}
			case Request_Page : { // 处理页面请求
				qDebug( ) << u8"case Request_Page : " << currentUrl;
				break;
			}
			case Request_Novel : { // 处理小说请求
				qDebug( ) << u8"case Request_Novel : " << currentUrl;
				break;
			}
		}
		usleep( 500 );
	}
	delete networkAccessManagerSPtr;
	delete networkRequestSPtr;
	if( requestConnect )
		requestConnect->deleteLater( );
	if( request )
		request->deleteLater( );
}
void HttpGetRequestThread::networkReplyErrorOccurred( QNetworkReply::NetworkError network_error ) {
	currntStatus = Standby;
	qDebug( ) << u8"requestConnect, &RequestConnect::networkReplyErrorOccurred : " << network_error;
}
void HttpGetRequestThread::networkReplyFinished( RequestConnect *request_connect ) {
	currntStatus = Standby;
	qDebug( ) << u8"requestConnect, &RequestConnect::networkReplyFinished";
	emit request_over( *request_connect );
}
