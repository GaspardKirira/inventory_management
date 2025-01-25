#ifndef ROUTECONFIGURATOR_HPP
#define ROUTECONFIGURATOR_HPP

#include "Router.hpp"
#include "SimpleRequestHandler.hpp"
#include "DynamicRequestHandler.hpp"
#include "IRequestHandler.hpp"
#include <unordered_map>
#include <string>
#include <memory>

namespace Softadastra
{
    class RouteConfigurator
    {
    public:
        explicit RouteConfigurator(Router &router);
        void configure_routes();

    private:
        Router &router_;
    };
}

#endif // ROUTECONFIGURATOR_HPP
