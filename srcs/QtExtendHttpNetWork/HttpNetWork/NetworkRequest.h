#ifndef NETWORKREQUEST_H_H_HEAD__FILE__
#define NETWORKREQUEST_H_H_HEAD__FILE__
#pragma once
#include <QNetworkRequest>

#include "../nameSpace/httpNetWork.h"
namespace cylHttpNetWork {
	class QTEXTENDHTTPNETWORK_EXPORT NetworkRequest : public QNetworkRequest {
	public:
		NetworkRequest( );
		virtual ~NetworkRequest( );
	private:  // 静态-成员
		/// <summary>
		/// 包含所有的 User Agent
		/// </summary>
		static QStringList userAgentHeaders;
		/// <summary>
		/// 域请求间隔
		/// </summary>
		static QMap< QUrl, size_t > hostRequestInterval;
		/// <summary>
		/// 默认的请求间隔-毫秒
		/// </summary>
		static size_t defaultHostRequestIntervalMilliseconds;
	public:
		/// <summary>
		/// 初始化
		/// </summary>
		static void init( );
		/// <summary>
		/// 设置域请求间隔-毫秒
		/// </summary>
		/// <param name="q_url">域url</param>
		/// <param name="microseconds">时间</param>
		static void setHostUrlRequestInterval( const QUrl &q_url, const size_t &microseconds );

		/// <summary>
		/// 获取域的休眠间隔时间-毫秒。默认返回 defaultHostRequestIntervalMilliseconds
		/// </summary>
		/// <param name="q_url">域</param>
		static size_t getHostUrlRequestInterval( const QUrl &q_url );
	public: // 静态-功能性
		static QStringList getUserAgentHeaders( );
		static QString getRandomUserAgentHeader( );
	};
}

#endif // NETWORKREQUEST_H_H_HEAD__FILE__
