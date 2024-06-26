﻿#ifndef NETWORKREQUEST_H_H_HEAD__FILE__
#define NETWORKREQUEST_H_H_HEAD__FILE__
#pragma once
#include <QNetworkRequest>
#include <QMutex>
#include "../nameSpace/httpNetWork.h"
#include "TimeTools.h"
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
		/// <summary>
		/// 时间获取锁
		/// </summary>
		static QMutex *mutex;
		/// <summary>
		/// 保存上次域请求的时间映射
		/// </summary>
		static QMap< QUrl, TimeTools::Time_Duration > urlTimeMap;
	public: // 静态-功能性
		/// <summary>
		/// 初始化
		/// </summary>
		static void initTools( );
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

		/// <summary>
		/// 获取域请求时间
		/// </summary>
		/// <param name="q_url">域链接</param>
		/// <param name="result">返回的时间</param>
		/// <returns>成功返回 true，flase 表示不存在</returns>
		static bool getHostLastRequestTime( const QUrl &q_url, TimeTools::Time_Duration &result );
		/// <summary>
		/// 设置域请求时间
		/// </summary>
		/// <param name="q_url">设置的域</param>
		/// <param name="time_duration">请求的时间</param>
		static void setHostLastRequestTime( const QUrl &q_url, const TimeTools::Time_Duration &time_duration );
		/// <summary>
		/// 设置当前时间到域时间请求上
		/// </summary>
		/// <param name="q_url">设置的域</param>
		static void updateCurrentTimeToHostLastRequestTime( const QUrl &q_url ) {
			setHostLastRequestTime( q_url, std::chrono::system_clock::now( ).time_since_epoch( ) );
		}
		/// <summary>
		/// 获取已经库存的 UserAgentHeader
		/// </summary>
		/// <returns>所有的 UserAgentHeader</returns>
		static QStringList getUserAgentHeaders( );
		/// <summary>
		/// 获取一个随机的 UserAgentHeader
		/// </summary>
		/// <returns>随机的 UserAgentHeader</returns>
		static QString getRandomUserAgentHeader( );
	};
}

#endif // NETWORKREQUEST_H_H_HEAD__FILE__
