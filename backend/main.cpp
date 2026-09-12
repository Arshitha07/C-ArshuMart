#include <drogon/drogon.h>

int main()
{
    drogon::app().registerHandler(
        "/",
        [](const drogon::HttpRequestPtr &req,
           std::function<void(const drogon::HttpResponsePtr &)> &&callback)
        {
            auto response = drogon::HttpResponse::newHttpResponse();
            response->setBody("ArshuMart Backend is Running!");
            callback(response);
        });

    drogon::app()
        .addListener("127.0.0.1", 8080)
        .run();

    return 0;
}