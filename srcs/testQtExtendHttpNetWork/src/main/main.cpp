#include <QApplication>
#include <HttpNetWork/NetworkRequest.h>
#include <HttpNetWork/NetworkAccessManager.h>
#include <HttpNetWork/Request.h>
#include <HttpNetWork/RequestConnect.h>

void testRequest( cylHttpNetWork::NetworkAccessManager &networkAccessManager, QUrl qUrl ) {
	// 请求信号转发对象
	cylHttpNetWork::RequestConnect *requestConnect = new cylHttpNetWork::RequestConnect;
	// 请求发送
	cylHttpNetWork::Request *request = new cylHttpNetWork::Request( &networkAccessManager, requestConnect );
	// 响应
	auto time = std::chrono::system_clock::now( ).time_since_epoch( );
	QObject::connect( requestConnect, &cylHttpNetWork::RequestConnect::networkReplyFinished, [=]( cylHttpNetWork::RequestConnect *request_connect ) {
		auto subTime = time - std::chrono::system_clock::now( ).time_since_epoch( );
		auto timeCount = std::chrono::duration_cast< std::chrono::milliseconds >( subTime ).count( );
		qDebug( ) << "over : " << timeCount << "\t" << request;
		requestConnect->deleteLater( );
		request->deleteLater( );
	} );
	// 开始请求
	request->netGetWork( qUrl );
}
void testRequest( cylHttpNetWork::NetworkAccessManager &networkAccessManager, QUrl qUrl, size_t mill ) {
	// 请求信号转发对象
	cylHttpNetWork::RequestConnect *requestConnect = new cylHttpNetWork::RequestConnect;
	// 请求发送
	cylHttpNetWork::Request *request = new cylHttpNetWork::Request( &networkAccessManager, requestConnect );
	// 响应
	auto time = std::chrono::system_clock::now( ).time_since_epoch( );
	QObject::connect( requestConnect, &cylHttpNetWork::RequestConnect::networkReplyFinished, [=]( cylHttpNetWork::RequestConnect *request_connect ) {
		auto subTime = time - std::chrono::system_clock::now( ).time_since_epoch( );
		auto timeCount = std::chrono::duration_cast< std::chrono::milliseconds >( subTime ).count( );
		qDebug( ) << "over : " << timeCount << "\t" << request;
		requestConnect->deleteLater( );
		request->deleteLater( );
	} );
	// 开始请求，但是使用自定义的时间，而并非已经定义的时间间隔
	request->netGetWork( qUrl, mill );
}
int main( int argc, char *argv[ ] ) {
	QApplication app( argc, argv );
	// 请求管理
	cylHttpNetWork::NetworkAccessManager networkAccessManager;
	// 请求体
	cylHttpNetWork::NetworkRequest qNetworkRequest;
	// 配置 url
	QUrl qUrl( "https://www.121ds.cc/" );
	// 设置 url
	qNetworkRequest.setUrl( qUrl );
	// 设置请求头
	qNetworkRequest.setHeader( QNetworkRequest::UserAgentHeader, cylHttpNetWork::NetworkRequest::getRandomUserAgentHeader( ) );
	// 初始化等待功能
	cylHttpNetWork::NetworkRequest::initTools( );
	// 设置 url 等待 15000 毫秒
	cylHttpNetWork::NetworkRequest::setHostUrlRequestInterval( qUrl, 15000 );

	// 使用默认等待时间
	testRequest( networkAccessManager, qUrl );
	// 使用请求等待时间-使用已经设定的时间
	testRequest( networkAccessManager, qUrl );
	// 使用请求等待时间-但是自定义
	testRequest( networkAccessManager, qUrl, 8000 );
	qDebug( ) << "\n\n\n\n=============\n" << "int main( int argc, char *argv[ ] ) ";
	qDebug( ) << "return app.exec( );";
	return app.exec( );
}
