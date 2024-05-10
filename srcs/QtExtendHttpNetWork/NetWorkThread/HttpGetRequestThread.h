#ifndef HTTPGETREQUESTTHREAD_H_H_HEAD__FILE__
#define HTTPGETREQUESTTHREAD_H_H_HEAD__FILE__
#pragma once
#include <memory>
#include <QNetworkReply>
#include <QObject>
#include <QThread>
#include <QUrl>

#include "../nameSpace/httpNetWork.h"
namespace cylHttpNetWork {
	class QTEXTENDHTTPNETWORK_EXPORT HttpGetRequestThread : public QThread {
public:
	Q_OBJECT;
public:
	enum THREAD_CURRNT_STATUS {
		None // 准备状态
		, Standby // 待命
		, Exit // 结束状态
		, Request_Root // 请求根状态
		, Request_Page // 请求页面状态
		, Request_Novel // 请求小说状态
		, Work_Net // 请求工作状态当中
		,
	};
private: // - 状态
	THREAD_CURRNT_STATUS currntStatus;
	QUrl currentUrl;
public: // - 构造和析构
	HttpGetRequestThread( QObject *parent = nullptr );
	~HttpGetRequestThread( ) override;
private:
	void initConnect( );
protected:
	void run( ) override;
Q_SIGNALS: // 信号 - 更改工作状态

	/// <summary>
	/// 请求结束后激活该信号
	/// </summary>
	void request_over( RequestConnect &request_connect );

	/// <summary>
	/// 设置工作 url
	/// </summary>
	/// <param name="url">工作的 url</param>
	void set_request_url( const QUrl &url );
	/// <summary>
	/// 更改工作状态
	/// </summary>
	/// <param name="new_work_status">新的工作状态</param>
	void change_request_status( THREAD_CURRNT_STATUS new_work_status );
	/// <summary>
	/// 请求一个根路径-获取被调用
	/// </summary>
	/// <param name="url">根路径</param>
	void requesting_get_root_page_signals( const QUrl &url );
	/// <summary>
	/// 请求一个 type 类型的页面-首次获取被调用
	/// </summary>
	/// <param name="root_url">根链接</param>
	/// <param name="type">小说类型</param>
	/// <param name="url">小说页面链接</param>
	void requesting_get_type_page_url_signals( const QString &root_url, const QString &type, const QUrl &url );
	/// <summary>
	/// 小说网站请求结束
	/// </summary>
	/// <param name="url">小说的网站</param>
	void requested_get_web_page_signals_end( const QUrl &url );

private slots: // 响应函数
	void networkReplyErrorOccurred(QNetworkReply::NetworkError network_error);
	void networkReplyFinished(RequestConnect* request_connect);

};
}

#endif // HTTPGETREQUESTTHREAD_H_H_HEAD__FILE__
