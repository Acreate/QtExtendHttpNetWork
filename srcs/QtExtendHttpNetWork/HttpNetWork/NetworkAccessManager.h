#ifndef NETWORKACCESSMANAGER_H_H_HEAD__FILE__
#define NETWORKACCESSMANAGER_H_H_HEAD__FILE__
#pragma once
#include <QNetworkAccessManager>

#include "../nameSpace/httpNetWork.h"
namespace cylHttpNetWork {
	class QTEXTENDHTTPNETWORK_EXPORT NetworkAccessManager : public QNetworkAccessManager {
		Q_OBJECT;
	public:
		NetworkAccessManager( QObject *parent = nullptr );
		~NetworkAccessManager( ) override;
	};
}

#endif // NETWORKACCESSMANAGER_H_H_HEAD__FILE__
