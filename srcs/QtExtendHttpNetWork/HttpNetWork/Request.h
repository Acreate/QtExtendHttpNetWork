#ifndef REQUEST_H_H_HEAD__FILE__
#define REQUEST_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QSettings>
#include <QNetworkReply>
#include "../nameSpace/httpNetWork.h"
#include "RequestConnect.h"
namespace cylHttpNetWork {

	class QTEXTENDHTTPNETWORK_EXPORT Request : public QObject {
		Q_OBJECT;
	private:
		NetworkAccessManager *networkAccessManager;
		RequestConnect *requestConnect;
		std::shared_ptr< NetworkRequest > networkRequest;
		Qt::ConnectionType connectType;
	public:
		Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, Qt::ConnectionType connection_type = Qt::AutoConnection );
		Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, QObject *parent, Qt::ConnectionType connection_type = Qt::AutoConnection );
		~Request( ) override;
	public:
		RequestConnect * getRequestConnect( ) {
			return requestConnect;
		}
		/// <summary>
		/// 发送 get 请求<br/>
		/// 返回 -2 时，你仍然可以使用 NetworkAccessManager 信号槽，但作为转发的 RequestConnect 将会失去效果
		/// </summary>
		/// <param name="url">请求的 rul</param>
		/// <param name="connect_type">信号链接类型</param>
		/// <returns>执行编码，非0表示失败</returns>
		int32_t netGetWork( const QUrl &url, Qt::ConnectionType connect_type = Qt::AutoConnection );
		/// <summary>
		/// 使用模板发送 get 请求，请求 url 来自参数 url，并非模板 network_request<br/>
		/// 返回 -2 时，你仍然可以使用 NetworkAccessManager 信号槽，但作为转发的 RequestConnect 将会失去效果
		/// </summary>
		/// <param name="url">请求的 rul</param>
		/// <param name="network_request">模板</param>
		/// <param name="connect_type">信号链接类型</param>
		/// <returns>执行编码，非0表示失败</returns>
		int32_t netGetWork( const QUrl &url, const NetworkRequest &network_request, Qt::ConnectionType connect_type = Qt::AutoConnection );
		/// <summary>
		/// 使用模板发送 get 请求，请求 url 来自 network_request 模板<br/>
		/// 返回 -2 时，你仍然可以使用 NetworkAccessManager 信号槽，但作为转发的 RequestConnect 将会失去效果
		/// </summary>
		/// <param name="network_request">模板</param>
		/// <param name="connect_type">信号链接类型</param>
		/// <returns>执行编码，非0表示失败</returns>
		int32_t netGetWork( const NetworkRequest &network_request, Qt::ConnectionType connect_type = Qt::AutoConnection );
		/// <summary>
		/// 使用模板发送 get 请求，并且等待时间 microseconds 毫秒<br/>
		/// 返回 -2 时，你仍然可以使用 NetworkAccessManager 信号槽，但作为转发的 RequestConnect 将会失去效果
		/// </summary>
		/// <param name="url">请求地址</param>
		/// <param name="microseconds">等待毫秒</param>
		/// <param name="connect_type">信号链接类型</param>
		/// <returns>执行编码，非0表示失败</returns>
		int32_t netGetWork( const QUrl &url, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		/// <summary>
		/// 使用模板发送 get 请求，并且等待时间 microseconds 毫秒<br/>
		/// 使用的请求模板来自 network_request，链接来自参数 url<br/>
		/// 返回 -2 时，你仍然可以使用 NetworkAccessManager 信号槽，但作为转发的 RequestConnect 将会失去效果
		/// </summary>
		/// <param name="url">请求地址</param>
		/// <param name="network_request">请求模板</param>
		/// <param name="microseconds">等待毫秒</param>
		/// <param name="connect_type">信号链接类型</param>
		/// <returns>执行编码，非0表示失败</returns>
		int32_t netGetWork( const QUrl &url, const NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
		/// <summary>
		/// 使用模板发送 get 请求，并且等待时间 microseconds 毫秒<br/>
		/// 使用的请求链接来自 network_request 对象<br/>
		/// 返回 -2 时，你仍然可以使用 NetworkAccessManager 信号槽，但作为转发的 RequestConnect 将会失去效果
		/// </summary>
		/// <param name="network_request">请求模板</param>
		/// <param name="microseconds">等待毫秒</param>
		/// <param name="connect_type">信号链接类型</param>
		/// <returns>执行编码，非0表示失败</returns>
		int32_t netGetWork( const NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );

		/// <summary>
		/// 等待完成
		/// </summary>
		/// <param name="milliseconds">等待间隔</param>
		/// <returns>请求完成体</returns>
		QNetworkReply * waitFinish( size_t milliseconds );
		/// <summary>
		/// 获取 请求完成体 <br/>
		/// 获取失败，它会重新反复请求 <br/>
		/// 如果需要单次请求，请使用 waitFinish
		/// </summary>
		/// <param name="milliseconds">等待间隔</param>
		/// <returns>请求完成体</returns>
		QNetworkReply * getNetworkReply( size_t milliseconds = 200 );
		/// <summary>
		/// 计数并且获取 请求完成体 <br/>
		/// 计数为 0 时候，不再发生请求 <br/>
		/// 如果一直发射了错误，请求次数大于或者等于 repeatRequestCount 时，此时不再发生请求
		/// </summary>
		/// <param name="repeatRequestCount">发生错误请求时，重新请求的次数</param>
		/// <param name="milliseconds">等待间隔</param>
		/// <returns>请求完成体</returns>
		QNetworkReply * getNetworkReplyCount( size_t repeatRequestCount, const size_t &milliseconds );
		/// <summary>
		/// 计时并且获取 请求完成体 <br/>
		/// 发生请求错误时，自动重新请求 <br/>
		/// 如果一直发射了错误，请求时间大于或者 等于 request_milliseconds 时，此时不再发生请求
		/// </summary>
		/// <param name="request_milliseconds">发生错误请求时，重新请求的总时间</param>
		/// <param name="milliseconds">等待间隔</param>
		/// <returns>请求完成体</returns>
		QNetworkReply * getNetworkReplyMilliseconds( size_t &request_milliseconds, const size_t &milliseconds );
		/// <summary>
		/// 获取请求完成体  <br/>
		/// 使用计时与计数限制请求功能 <br/>
		/// 满足以下其中一个条件时候，不再发生请求 <br/>
		///	<para>1.请求时间大于或者 等于 request_milliseconds 时</para> 
		///	<para>2.请求次数大于或者等于 repeatRequestCount 时</para> 
		/// </summary>
		/// <param name="request_milliseconds"></param>
		/// <param name="repeatRequestCount"></param>
		/// <param name="milliseconds"></param>
		/// <returns></returns>
		QNetworkReply * getNetworkReply( size_t request_milliseconds, size_t repeatRequestCount, const size_t &milliseconds );
	public: // - 静态对象
		/// <summary>
		/// 睡眠指定的时间-毫秒
		/// </summary>
		/// <param name="milliseconds">毫秒</param>
		/// <returns>毫秒</returns>
		static size_t sleep( const size_t &milliseconds );
	};

}
#endif // REQUEST_H_H_HEAD__FILE__
