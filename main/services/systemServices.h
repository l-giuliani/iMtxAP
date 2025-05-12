#ifndef _SYSTEMSERVICES_H_
#define _SYSTEMSERVICES_H_

#ifdef __cplusplus

namespace NSystemServices {

    class NetworkServices {
    public:
        static void initWebServer();
    };

    class Services {
    public: 
        static void initSystem();
    };

}


extern "C" {
#endif
    
    void initWebServer();
    void initSystem();
    
#ifdef __cplusplus
}
#endif

#endif // _SYSTEMSERVICES_H