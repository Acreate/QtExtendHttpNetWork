#include <QApplication>
#include <HttpNetWork/NetworkRequest.h>
#include <HttpNetWork/NetworkAccessManager.h>
#include <HttpNetWork/Request.h>
#include <HttpNetWork/RequestConnect.h>

#include "NetWorkThread/HttpGetRequestThread.h"
int main( int argc, char *argv[ ] ) {
	QApplication app( argc, argv );
	QNetworkAccessManager qNetworkAccessManager;

	QNetworkAccessManager::connect( &qNetworkAccessManager, &QNetworkAccessManager::finished, []( QNetworkReply *reply ) {
		reply->seek( 0 );
		QString msg( reply->readAll( ) );
		qDebug( ) << "\n\n\n\n=============\n" "&qNetworkAccessManager, &QNetworkAccessManager::finished";
		qDebug( ) << msg << "\n\n\n\n=============\n";
	} );

	QNetworkRequest qNetworkRequest;
	qNetworkRequest.setUrl( QUrl( "https://www.121ds.cc/" ) );
	qNetworkRequest.setHeader( QNetworkRequest::UserAgentHeader, cylHttpNetWork::NetworkRequest::getRandomUserAgentHeader( ) );
	QNetworkReply *networkReply = qNetworkAccessManager.get( qNetworkRequest );
	bool isRunning = networkReply->isRunning( );
	while( isRunning && !networkReply->isFinished( ) ) {
		if( networkReply->error( ) )
			break;
		app.processEvents( );
	}
	qDebug( ) << "\n\n\n\n=============\n" << "int main( int argc, char *argv[ ] ) ";
	qDebug( ) << "return app.exec( );";
	return app.exec( );
}
