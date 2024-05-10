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
		static QStringList userAgentHeaders; // 包含所有的 User Agent
	public: // 静态-功能性
		static QStringList getUserAgentHeaders( );
		static QString getRandomUserAgentHeader( );
	};
}

#endif // NETWORKREQUEST_H_H_HEAD__FILE__
