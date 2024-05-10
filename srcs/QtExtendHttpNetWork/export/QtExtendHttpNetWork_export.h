
#ifndef QTEXTENDHTTPNETWORK_EXPORT_H
#define QTEXTENDHTTPNETWORK_EXPORT_H

#ifdef QTEXTENDHTTPNETWORK_STATIC_DEFINE
#  define QTEXTENDHTTPNETWORK_EXPORT
#  define QTEXTENDHTTPNETWORK_NO_EXPORT
#else
#  ifndef QTEXTENDHTTPNETWORK_EXPORT
#    ifdef QtExtendHttpNetWork_EXPORTS
        /* We are building this library */
#      define QTEXTENDHTTPNETWORK_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define QTEXTENDHTTPNETWORK_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef QTEXTENDHTTPNETWORK_NO_EXPORT
#    define QTEXTENDHTTPNETWORK_NO_EXPORT 
#  endif
#endif

#ifndef QTEXTENDHTTPNETWORK_DEPRECATED
#  define QTEXTENDHTTPNETWORK_DEPRECATED __declspec(deprecated)
#endif

#ifndef QTEXTENDHTTPNETWORK_DEPRECATED_EXPORT
#  define QTEXTENDHTTPNETWORK_DEPRECATED_EXPORT QTEXTENDHTTPNETWORK_EXPORT QTEXTENDHTTPNETWORK_DEPRECATED
#endif

#ifndef QTEXTENDHTTPNETWORK_DEPRECATED_NO_EXPORT
#  define QTEXTENDHTTPNETWORK_DEPRECATED_NO_EXPORT QTEXTENDHTTPNETWORK_NO_EXPORT QTEXTENDHTTPNETWORK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QTEXTENDHTTPNETWORK_NO_DEPRECATED
#    define QTEXTENDHTTPNETWORK_NO_DEPRECATED
#  endif
#endif

#endif /* QTEXTENDHTTPNETWORK_EXPORT_H */
