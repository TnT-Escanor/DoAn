#include "CalcResourceFactory.h"

#include <sstream>
#include <iomanip>
#include "json.hpp"
#include "Source.h"

using namespace nlohmann;

CalcResourceFactory::CalcResourceFactory() {
    _resource = make_shared<Resource>();
    _resource->set_path(
        "/{operation: [0-9,()]*}"
        "/{num1: [-+]?[0-9]*\\.?[0-9]*}"
        "/{num2: [-+]?[0-9]*\\.?[0-9]*}");
    _resource->set_method_handler("GET", 
        [&](const auto session) {
            get_handler(session);
        });
}

shared_ptr<Resource> CalcResourceFactory::get_resource() const {
        return _resource;
}

tuple<int, int, string> CalcResourceFactory::get_path_parameters(
        const shared_ptr<Session> session) const {
    const auto& request = session->get_request();
    const auto operation = request->get_path_parameter("operation");
    auto num1 = atoi(request->get_path_parameter("num1").c_str());
    auto num2 = atoi(request->get_path_parameter("num2").c_str());
    return make_tuple(num1, num2, operation);
} 

string CalcResourceFactory::to_json(string result) {
    ostringstream str_stream;
    str_stream << result;
    json jsonResult = {
        {"result", str_stream.str()}
    };
    return jsonResult.dump();
}

void CalcResourceFactory::get_handler(const shared_ptr<Session> session) {
    const auto [num1, num2, operation] = get_path_parameters(session);
    auto result = Calculation(num1, num2, operation);
    cout << result;
    cout << endl;
    auto content = to_json(result);
    session->close(OK, content, 
        {{"Content-Length", to_string(content.size())}});
}