#include <QApplication>
#include <HttpNetWork/NetworkRequest.h>
#include <HttpNetWork/NetworkAccessManager.h>
#include <HttpNetWork/Request.h>
#include <HttpNetWork/RequestConnect.h>

int main( int argc, char *argv[ ] ) {
	QApplication app( argc, argv );
	cylHttpNetWork::NetworkAccessManager networkAccessManager;


	cylHttpNetWork::NetworkRequest qNetworkRequest;
	QUrl qUrl( "https://www.121ds.cc/" );
	qNetworkRequest.setUrl( qUrl );
	qNetworkRequest.setHeader( QNetworkRequest::UserAgentHeader, cylHttpNetWork::NetworkRequest::getRandomUserAgentHeader( ) );
	cylHttpNetWork::NetworkRequest::init( );
	cylHttpNetWork::NetworkRequest::setHostUrlRequestInterval( qUrl, 15000 );


	cylHttpNetWork::RequestConnect requestConnect;
	cylHttpNetWork::Request request( &networkAccessManager, &requestConnect );
	QObject::connect( &requestConnect, &cylHttpNetWork::RequestConnect::networkReplyFinished, []( cylHttpNetWork::RequestConnect *request_connect ) {
		qDebug( ) << "over";
	} );

	request.netGetWork( qUrl, 12000 );

	qDebug( ) << "\n\n\n\n=============\n" << "int main( int argc, char *argv[ ] ) ";
	qDebug( ) << "return app.exec( );";
	return app.exec( );
}
