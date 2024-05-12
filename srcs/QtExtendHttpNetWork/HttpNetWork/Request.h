#ifndef REQUEST_H_H_HEAD__FILE__
#define REQUEST_H_H_HEAD__FILE__
#pragma once
#include <QObject>
#include <QSettings>
#include <QNetworkReply>
#include "../nameSpace/httpNetWork.h"
namespace cylHttpNetWork {

	class QTEXTENDHTTPNETWORK_EXPORT Request : public QObject {
		Q_OBJECT;
	private:
		NetworkAccessManager *networkAccessManager;
		RequestConnect *requestConnect;
	public:
		Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, Qt::ConnectionType connection_type = Qt::AutoConnection );
		Request( NetworkAccessManager *networkAccessManager, RequestConnect *requestConnect, QObject *parent, Qt::ConnectionType connection_type = Qt::AutoConnection );
		~Request( ) override;
	public:
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
		int32_t netGetWork(const NetworkRequest &network_request, size_t microseconds, Qt::ConnectionType connect_type = Qt::AutoConnection );
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
