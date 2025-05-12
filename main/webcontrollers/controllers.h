#ifndef _CONTROLLERS_H_
#define _CONTROLLERS_H_

#include "routes.h"

namespace NWebControllers {

    class AppController {
    public:
        static void setup(NWebServer::NRoutes::Routes& routes);
    };

}

#endif // _CONTROLLERS_H