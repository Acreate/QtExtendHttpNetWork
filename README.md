# QtExtendHttpNetWork

#### 介绍
基于 qt 实现的 get 请求库

#### 使用说明

– 请求一个页面

```c++
cylHttpNetWork::RequestConnect requestConnect;
cylHttpNetWork::NetworkAccessManager networkAccessManager;
cylHttpNetWork::NetworkRequest networkRequest;
cylHttpNetWork::Request request( &networkAccessManager, &requestConnect );

QObject::connect( &requestConnect, &cylHttpNetWork::RequestConnect::networkReplyFinished,
	[]( cylHttpNetWork::RequestConnect *request_connect ) {
		auto networkReply = request_connect->getNetworkReply( );
		auto byteArray = networkReply->readAll( );
		QString msg( byteArray );
		qDebug( ) << "==================================";
		qDebug( ) << msg;
		qDebug( ) << "==================================";
	} );
networkRequest.setHeader( QNetworkRequest::UserAgentHeader, networkRequest.getRandomUserAgentHeader( ) );
request.netGetWork( QUrl( "https://www.121ds.cc/" ), networkRequest );
```
