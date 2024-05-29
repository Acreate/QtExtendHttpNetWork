#ifndef TIMETOOLS_H_H_HEAD__FILE__
#define TIMETOOLS_H_H_HEAD__FILE__
#pragma once

#include "../nameSpace/httpNetWork.h"
#include <chrono>
namespace cylHttpNetWork {

	class QTEXTENDHTTPNETWORK_EXPORT TimeTools {
	public:
		using Time_Duration = std::chrono::system_clock::time_point::duration;
	public:
		/// <summary>
		/// 获取当前时间的时间戳
		/// </summary>
		/// <returns></returns>
		static Time_Duration getNowTimeDuration( ) {
			return std::chrono::system_clock::now( ).time_since_epoch( );
		}
		/// <summary>
		/// 获取当前时间戳
		/// </summary>
		/// <returns>返回时间戳</returns>
		static _CHRONO time_point< std::chrono::system_clock > getCurrentTime( ) {
			return std::chrono::system_clock::now( );
		}
		/// <summary>
		/// 时间戳转换到毫秒
		/// </summary>
		/// <param name="time_duration">时间戳</param>
		/// <returns>毫秒</returns>
		static long long getTimeDurationToMilliseconds( const Time_Duration &time_duration ) {
			return std::chrono::duration_cast< std::chrono::milliseconds >( time_duration ).count( );
		}

	};

}

#endif // TIMETOOLS_H_H_HEAD__FILE__
