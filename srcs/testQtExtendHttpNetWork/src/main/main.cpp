#include <QApplication>
#include <HttpNetWork/NetworkRequest.h>
#include <HttpNetWork/NetworkAccessManager.h>
#include <HttpNetWork/Request.h>
#include <HttpNetWork/RequestConnect.h>

#include "NetWorkThread/HttpGetRequestThread.h"
int main( int argc, char *argv[ ] ) {
	QApplication app( argc, argv );


	//cylHttpNetWork::RequestConnect requestConnect;
	//cylHttpNetWork::NetworkAccessManager networkAccessManager;
	//cylHttpNetWork::NetworkRequest networkRequest;
	//cylHttpNetWork::Request request( &networkAccessManager, &requestConnect );

	//QObject::connect( &requestConnect, &cylHttpNetWork::RequestConnect::networkReplyFinished,
	//	[]( cylHttpNetWork::RequestConnect *request_connect ) {
	//		auto networkReply = request_connect->getNetworkReply( );
	//		auto byteArray = networkReply->readAll( );
	//		QString msg( byteArray );
	//		qDebug( ) << "==================================";
	//		qDebug( ) << msg;
	//		qDebug( ) << "==================================";
	//	} );
	//networkRequest.setHeader( QNetworkRequest::UserAgentHeader, networkRequest.getRandomUserAgentHeader( ) );
	//request.netGetWork( QUrl( "https://www.121ds.cc/" ), networkRequest );


	cylHttpNetWork::HttpGetRequestThread httpGetRequestThread;
	QObject::connect( &httpGetRequestThread, &cylHttpNetWork::HttpGetRequestThread::requesting_get_root_page_signals,
		[]( const QUrl &url ) {
			qDebug( ) << "&httpGetRequestThread, &cylHttpNetWork::HttpGetRequestThread::requesting_get_root_page_signals";
			qDebug( ) << "\t" << url.url( );
		} );
	// void request_over( RequestConnect &request_connect );

	QObject::connect( &httpGetRequestThread, &cylHttpNetWork::HttpGetRequestThread::request_over,
		[]( cylHttpNetWork::RequestConnect &request_connect ) {
			qDebug( ) << "&httpGetRequestThread, &cylHttpNetWork::HttpGetRequestThread::request_over";
		} );
	QObject::connect( &httpGetRequestThread, &QThread::finished,
		[]( ) {
			qDebug( ) << "线程结束";
		} );
	httpGetRequestThread.start( );
	httpGetRequestThread.set_request_url( QUrl( "https://www.121ds.cc/" ) );
	httpGetRequestThread.change_request_status( cylHttpNetWork::HttpGetRequestThread::Request_Root );

	qDebug( ) << "return app.exec( );";
	return app.exec( );
}
