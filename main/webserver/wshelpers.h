#ifndef _HELPERS_H_
#define _HELPERS_H_

namespace NWebServer {

    class NetworkInterface {
    public:
        virtual void initAndStart() = 0;
        virtual void stop() = 0;
    };

    class WiFiNetworkInterface : public NetworkInterface {
    public:
        void initAndStart();
        void stop();
    };

}

#endif // _HELPERS_H