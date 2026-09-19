#include <drogon/drogon.h>
#include <sqlite3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


void addCorsHeaders(const drogon::HttpResponsePtr& response)
{
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader(
        "Access-Control-Allow-Methods",
        "GET, POST, PUT, DELETE, OPTIONS"
    );
    response->addHeader(
        "Access-Control-Allow-Headers",
        "Content-Type"
    );
}


bool initializeDatabase()
{
    sqlite3* db = nullptr;

    int result =
        sqlite3_open(
            "database/ArshuMart.db",
            &db
        );

    if (result != SQLITE_OK)
    {
        std::cerr
            << "Database opening failed: "
            << sqlite3_errmsg(db)
            << std::endl;

        sqlite3_close(db);
        return false;
    }


    std::ifstream schemaFile(
        "database/schema.sql"
    );

    if (!schemaFile.is_open())
    {
        std::cerr
            << "schema.sql file not found!"
            << std::endl;

        sqlite3_close(db);
        return false;
    }


    std::stringstream buffer;

    buffer << schemaFile.rdbuf();

    std::string schema =
        buffer.str();


    char* errorMessage = nullptr;


    result =
        sqlite3_exec(
            db,
            schema.c_str(),
            nullptr,
            nullptr,
            &errorMessage
        );


    if (result != SQLITE_OK)
    {
        std::cerr
            << "Database schema error: "
            << errorMessage
            << std::endl;

        sqlite3_free(errorMessage);

        sqlite3_close(db);

        return false;
    }


    sqlite3_close(db);


    std::cout
        << "ArshuMart database initialized successfully!"
        << std::endl;


    return true;
}



std::string getProductsJson()
{
    sqlite3* db = nullptr;


    int result =
        sqlite3_open(
            "database/ArshuMart.db",
            &db
        );


    if (result != SQLITE_OK)
    {
        return
            R"({"success":false,"message":"Database connection failed"})";
    }


    const char* sql =
        "SELECT id, name, description, category, price, stock, image_url "
        "FROM products ORDER BY id;";


    sqlite3_stmt* statement = nullptr;


    result =
        sqlite3_prepare_v2(
            db,
            sql,
            -1,
            &statement,
            nullptr
        );


    if (result != SQLITE_OK)
    {
        sqlite3_close(db);

        return
            R"({"success":false,"message":"Database query failed"})";
    }


    std::string json =
        R"({"success":true,"products":[)";


    bool first = true;


    while (
        sqlite3_step(statement)
        == SQLITE_ROW
    )
    {
        int id =
            sqlite3_column_int(
                statement,
                0
            );


        const unsigned char* nameText =
            sqlite3_column_text(
                statement,
                1
            );


        const unsigned char* descriptionText =
            sqlite3_column_text(
                statement,
                2
            );


        const unsigned char* categoryText =
            sqlite3_column_text(
                statement,
                3
            );


        double price =
            sqlite3_column_double(
                statement,
                4
            );


        int stock =
            sqlite3_column_int(
                statement,
                5
            );


        const unsigned char* imageText =
            sqlite3_column_text(
                statement,
                6
            );


        std::string name =
            nameText
            ? reinterpret_cast<const char*>(
                nameText
              )
            : "";


        std::string description =
            descriptionText
            ? reinterpret_cast<const char*>(
                descriptionText
              )
            : "";


        std::string category =
            categoryText
            ? reinterpret_cast<const char*>(
                categoryText
              )
            : "";


        std::string image =
            imageText
            ? reinterpret_cast<const char*>(
                imageText
              )
            : "";


        if (!first)
        {
            json += ",";
        }


        first = false;


        json +=
            "{\"id\":" +
            std::to_string(id) +
            ",\"name\":\"" +
            name +
            "\",\"description\":\"" +
            description +
            "\",\"category\":\"" +
            category +
            "\",\"price\":" +
            std::to_string(price) +
            ",\"stock\":" +
            std::to_string(stock) +
            ",\"image\":\"" +
            image +
            "\"}";
    }


    json += "]}";


    sqlite3_finalize(statement);

    sqlite3_close(db);


    return json;
}



int main()
{
    if (!initializeDatabase())
    {
        return 1;
    }



    drogon::app().registerHandler(
        "/",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&
           )>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();


            addCorsHeaders(response);


            response->setBody(
                "ArshuMart Backend is Running!"
            );


            callback(response);
        }
    );



    drogon::app().registerHandler(
        "/api/products",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&
           )>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();


            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );


            addCorsHeaders(response);


            if (req->method() == drogon::Options)
            {
                response->setStatusCode(
                    drogon::k204NoContent
                );


                callback(response);

                return;
            }


            if (req->method() != drogon::Get)
            {
                response->setStatusCode(
                    drogon::k405MethodNotAllowed
                );


                response->setBody(
                    R"({"success":false,"message":"GET method required"})"
                );


                callback(response);

                return;
            }


            response->setStatusCode(
                drogon::k200OK
            );


            response->setBody(
                getProductsJson()
            );


            callback(response);
        }
    );



    drogon::app().registerHandler(
        "/api/register",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&
           )>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();


            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );


            addCorsHeaders(response);


            if (req->method() == drogon::Options)
            {
                response->setStatusCode(
                    drogon::k204NoContent
                );


                callback(response);

                return;
            }


            if (req->method() != drogon::Post)
            {
                response->setStatusCode(
                    drogon::k405MethodNotAllowed
                );


                response->setBody(
                    R"({"success":false,"message":"POST method required"})"
                );


                callback(response);

                return;
            }


            auto dataPtr =
                req->getJsonObject();


            if (!dataPtr)
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Invalid JSON data"})"
                );


                callback(response);

                return;
            }


            const Json::Value& data =
                *dataPtr;


            if (
                data.empty() ||
                !data.isMember("name") ||
                !data.isMember("email") ||
                !data.isMember("password") ||
                !data.isMember("role")
            )
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"All fields are required"})"
                );


                callback(response);

                return;
            }


            std::string name =
                data["name"].asString();


            std::string email =
                data["email"].asString();


            std::string password =
                data["password"].asString();


            std::string role =
                data["role"].asString();


            if (
                name.empty() ||
                email.empty() ||
                password.empty() ||
                role.empty()
            )
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Fields cannot be empty"})"
                );


                callback(response);

                return;
            }


            if (
                role != "buyer" &&
                role != "seller"
            )
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Invalid role"})"
                );


                callback(response);

                return;
            }


            sqlite3* db = nullptr;


            int result =
                sqlite3_open(
                    "database/ArshuMart.db",
                    &db
                );


            if (result != SQLITE_OK)
            {
                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Database connection failed"})"
                );


                sqlite3_close(db);

                callback(response);

                return;
            }


            const char* sql =
                "INSERT INTO users "
                "(name, email, password_hash, role) "
                "VALUES (?, ?, ?, ?);";


            sqlite3_stmt* statement =
                nullptr;


            result =
                sqlite3_prepare_v2(
                    db,
                    sql,
                    -1,
                    &statement,
                    nullptr
                );


            if (result != SQLITE_OK)
            {
                sqlite3_close(db);


                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Database query failed"})"
                );


                callback(response);

                return;
            }


            sqlite3_bind_text(
                statement,
                1,
                name.c_str(),
                -1,
                SQLITE_TRANSIENT
            );


            sqlite3_bind_text(
                statement,
                2,
                email.c_str(),
                -1,
                SQLITE_TRANSIENT
            );


            sqlite3_bind_text(
                statement,
                3,
                password.c_str(),
                -1,
                SQLITE_TRANSIENT
            );


            sqlite3_bind_text(
                statement,
                4,
                role.c_str(),
                -1,
                SQLITE_TRANSIENT
            );


            result =
                sqlite3_step(statement);


            if (result != SQLITE_DONE)
            {
                std::string error =
                    sqlite3_errmsg(db);


                sqlite3_finalize(statement);

                sqlite3_close(db);


                response->setStatusCode(
                    drogon::k409Conflict
                );


                response->setBody(
                    R"({"success":false,"message":"Email already registered"})"
                );


                callback(response);

                return;
            }


            sqlite3_finalize(statement);

            sqlite3_close(db);


            response->setStatusCode(
                drogon::k201Created
            );


            response->setBody(
                R"({"success":true,"message":"Account created successfully"})"
            );


            callback(response);
        }
    );



    drogon::app().registerHandler(
        "/api/login",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&
           )>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();


            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );


            addCorsHeaders(response);


            if (req->method() == drogon::Options)
            {
                response->setStatusCode(
                    drogon::k204NoContent
                );


                callback(response);

                return;
            }


            if (req->method() != drogon::Post)
            {
                response->setStatusCode(
                    drogon::k405MethodNotAllowed
                );


                response->setBody(
                    R"({"success":false,"message":"POST method required"})"
                );


                callback(response);

                return;
            }


            auto dataPtr =
                req->getJsonObject();


            if (!dataPtr)
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Invalid JSON data"})"
                );


                callback(response);

                return;
            }


            const Json::Value& data =
                *dataPtr;


            if (
                !data.isMember("email") ||
                !data.isMember("password")
            )
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Email and password are required"})"
                );


                callback(response);

                return;
            }


            std::string email =
                data["email"].asString();


            std::string password =
                data["password"].asString();


            sqlite3* db = nullptr;


            int result =
                sqlite3_open(
                    "database/ArshuMart.db",
                    &db
                );


            if (result != SQLITE_OK)
            {
                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Database connection failed"})"
                );


                sqlite3_close(db);

                callback(response);

                return;
            }


            const char* sql =
                "SELECT id, name, role "
                "FROM users "
                "WHERE email = ? AND password_hash = ?;";


            sqlite3_stmt* statement =
                nullptr;


            result =
                sqlite3_prepare_v2(
                    db,
                    sql,
                    -1,
                    &statement,
                    nullptr
                );


            if (result != SQLITE_OK)
            {
                sqlite3_close(db);


                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Database query failed"})"
                );


                callback(response);

                return;
            }


            sqlite3_bind_text(
                statement,
                1,
                email.c_str(),
                -1,
                SQLITE_TRANSIENT
            );


            sqlite3_bind_text(
                statement,
                2,
                password.c_str(),
                -1,
                SQLITE_TRANSIENT
            );


            result =
                sqlite3_step(statement);


            if (result == SQLITE_ROW)
            {
                int userId =
                    sqlite3_column_int(
                        statement,
                        0
                    );


                const unsigned char* nameText =
                    sqlite3_column_text(
                        statement,
                        1
                    );


                const unsigned char* roleText =
                    sqlite3_column_text(
                        statement,
                        2
                    );


                std::string name =
                    nameText
                    ? reinterpret_cast<const char*>(
                        nameText
                      )
                    : "";


                std::string role =
                    roleText
                    ? reinterpret_cast<const char*>(
                        roleText
                      )
                    : "";


                std::string json =
                    "{\"success\":true,"
                    "\"message\":\"Login successful\","
                    "\"userId\":" +
                    std::to_string(userId) +
                    ",\"name\":\"" +
                    name +
                    "\",\"role\":\"" +
                    role +
                    "\"}";


                response->setStatusCode(
                    drogon::k200OK
                );


                response->setBody(
                    json
                );
            }
            else
            {
                response->setStatusCode(
                    drogon::k401Unauthorized
                );


                response->setBody(
                    R"({"success":false,"message":"Invalid email or password"})"
                );
            }


            sqlite3_finalize(statement);

            sqlite3_close(db);


            callback(response);
        }
    );



    drogon::app().registerHandler(
        "/api/checkout",
        [](const drogon::HttpRequestPtr& req,
           std::function<void(
               const drogon::HttpResponsePtr&
           )>&& callback)
        {
            auto response =
                drogon::HttpResponse::newHttpResponse();


            response->setContentTypeCode(
                drogon::CT_APPLICATION_JSON
            );


            addCorsHeaders(response);


            if (req->method() == drogon::Options)
            {
                response->setStatusCode(
                    drogon::k204NoContent
                );


                callback(response);

                return;
            }


            if (req->method() != drogon::Post)
            {
                response->setStatusCode(
                    drogon::k405MethodNotAllowed
                );


                response->setBody(
                    R"({"success":false,"message":"POST method required"})"
                );


                callback(response);

                return;
            }


            auto json =
                req->getJsonObject();


            if (
                !json ||
                !json->isMember("buyerId") ||
                !json->isMember("items")
            )
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Invalid checkout data"})"
                );


                callback(response);

                return;
            }


            int buyerId =
                (*json)["buyerId"].asInt();


            const auto& items =
                (*json)["items"];


            if (
                buyerId <= 0 ||
                !items.isArray() ||
                items.empty()
            )
            {
                response->setStatusCode(
                    drogon::k400BadRequest
                );


                response->setBody(
                    R"({"success":false,"message":"Cart is empty"})"
                );


                callback(response);

                return;
            }


            sqlite3* db = nullptr;


            int result =
                sqlite3_open(
                    "database/ArshuMart.db",
                    &db
                );


            if (result != SQLITE_OK)
            {
                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Database connection failed"})"
                );


                if (db)
                {
                    sqlite3_close(db);
                }


                callback(response);

                return;
            }


            sqlite3_exec(
                db,
                "BEGIN TRANSACTION;",
                nullptr,
                nullptr,
                nullptr
            );


            double totalAmount = 0.0;


            for (const auto& item : items)
            {
                if (
                    !item.isMember("productId") ||
                    !item.isMember("quantity")
                )
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k400BadRequest
                    );


                    response->setBody(
                        R"({"success":false,"message":"Invalid cart item"})"
                    );


                    callback(response);

                    return;
                }


                int productId =
                    item["productId"].asInt();


                int quantity =
                    item["quantity"].asInt();


                if (
                    productId <= 0 ||
                    quantity <= 0
                )
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k400BadRequest
                    );


                    response->setBody(
                        R"({"success":false,"message":"Invalid product quantity"})"
                    );


                    callback(response);

                    return;
                }


                sqlite3_stmt* statement =
                    nullptr;


                result =
                    sqlite3_prepare_v2(
                        db,
                        "SELECT price, stock "
                        "FROM products "
                        "WHERE id = ?;",
                        -1,
                        &statement,
                        nullptr
                    );


                if (result != SQLITE_OK)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k500InternalServerError
                    );


                    response->setBody(
                        R"({"success":false,"message":"Product query failed"})"
                    );


                    callback(response);

                    return;
                }


                sqlite3_bind_int(
                    statement,
                    1,
                    productId
                );


                result =
                    sqlite3_step(
                        statement
                    );


                if (result != SQLITE_ROW)
                {
                    sqlite3_finalize(
                        statement
                    );


                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k400BadRequest
                    );


                    response->setBody(
                        R"({"success":false,"message":"Product not found"})"
                    );


                    callback(response);

                    return;
                }


                double price =
                    sqlite3_column_double(
                        statement,
                        0
                    );


                int stock =
                    sqlite3_column_int(
                        statement,
                        1
                    );


                sqlite3_finalize(
                    statement
                );


                if (quantity > stock)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k400BadRequest
                    );


                    response->setBody(
                        R"({"success":false,"message":"Insufficient stock"})"
                    );


                    callback(response);

                    return;
                }


                totalAmount +=
                    price * quantity;
            }



            sqlite3_stmt* orderStatement =
                nullptr;


            result =
                sqlite3_prepare_v2(
                    db,
                    "INSERT INTO orders "
                    "(buyer_id, total_amount, status) "
                    "VALUES (?, ?, 'Confirmed');",
                    -1,
                    &orderStatement,
                    nullptr
                );


            if (result != SQLITE_OK)
            {
                sqlite3_exec(
                    db,
                    "ROLLBACK;",
                    nullptr,
                    nullptr,
                    nullptr
                );


                sqlite3_close(db);


                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Order creation failed"})"
                );


                callback(response);

                return;
            }


            sqlite3_bind_int(
                orderStatement,
                1,
                buyerId
            );


            sqlite3_bind_double(
                orderStatement,
                2,
                totalAmount
            );


            result =
                sqlite3_step(
                    orderStatement
                );


            sqlite3_finalize(
                orderStatement
            );


            if (result != SQLITE_DONE)
            {
                sqlite3_exec(
                    db,
                    "ROLLBACK;",
                    nullptr,
                    nullptr,
                    nullptr
                );


                sqlite3_close(db);


                response->setStatusCode(
                    drogon::k500InternalServerError
                );


                response->setBody(
                    R"({"success":false,"message":"Order creation failed"})"
                );


                callback(response);

                return;
            }


            sqlite3_int64 orderId =
                sqlite3_last_insert_rowid(
                    db
                );



            for (const auto& item : items)
            {
                int productId =
                    item["productId"].asInt();


                int quantity =
                    item["quantity"].asInt();


                sqlite3_stmt* itemStatement =
                    nullptr;


                result =
                    sqlite3_prepare_v2(
                        db,
                        "SELECT price "
                        "FROM products "
                        "WHERE id = ?;",
                        -1,
                        &itemStatement,
                        nullptr
                    );


                if (result != SQLITE_OK)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k500InternalServerError
                    );


                    response->setBody(
                        R"({"success":false,"message":"Order item query failed"})"
                    );


                    callback(response);

                    return;
                }


                sqlite3_bind_int(
                    itemStatement,
                    1,
                    productId
                );


                result =
                    sqlite3_step(
                        itemStatement
                    );


                if (result != SQLITE_ROW)
                {
                    sqlite3_finalize(
                        itemStatement
                    );


                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k400BadRequest
                    );


                    response->setBody(
                        R"({"success":false,"message":"Product not found"})"
                    );


                    callback(response);

                    return;
                }


                double price =
                    sqlite3_column_double(
                        itemStatement,
                        0
                    );


                sqlite3_finalize(
                    itemStatement
                );


                sqlite3_stmt* insertItem =
                    nullptr;


                result =
                    sqlite3_prepare_v2(
                        db,
                        "INSERT INTO order_items "
                        "(order_id, product_id, quantity, price) "
                        "VALUES (?, ?, ?, ?);",
                        -1,
                        &insertItem,
                        nullptr
                    );


                if (result != SQLITE_OK)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k500InternalServerError
                    );


                    response->setBody(
                        R"({"success":false,"message":"Order item creation failed"})"
                    );


                    callback(response);

                    return;
                }


                sqlite3_bind_int64(
                    insertItem,
                    1,
                    orderId
                );


                sqlite3_bind_int(
                    insertItem,
                    2,
                    productId
                );


                sqlite3_bind_int(
                    insertItem,
                    3,
                    quantity
                );


                sqlite3_bind_double(
                    insertItem,
                    4,
                    price
                );


                result =
                    sqlite3_step(
                        insertItem
                    );


                sqlite3_finalize(
                    insertItem
                );


                if (result != SQLITE_DONE)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k500InternalServerError
                    );


                    response->setBody(
                        R"({"success":false,"message":"Order item creation failed"})"
                    );


                    callback(response);

                    return;
                }


                sqlite3_stmt* stockStatement =
                    nullptr;


                result =
                    sqlite3_prepare_v2(
                        db,
                        "UPDATE products "
                        "SET stock = stock - ? "
                        "WHERE id = ?;",
                        -1,
                        &stockStatement,
                        nullptr
                    );


                if (result != SQLITE_OK)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k500InternalServerError
                    );


                    response->setBody(
                        R"({"success":false,"message":"Stock update failed"})"
                    );


                    callback(response);

                    return;
                }


                sqlite3_bind_int(
                    stockStatement,
                    1,
                    quantity
                );


                sqlite3_bind_int(
                    stockStatement,
                    2,
                    productId
                );


                result =
                    sqlite3_step(
                        stockStatement
                    );


                sqlite3_finalize(
                    stockStatement
                );


                if (result != SQLITE_DONE)
                {
                    sqlite3_exec(
                        db,
                        "ROLLBACK;",
                        nullptr,
                        nullptr,
                        nullptr
                    );


                    sqlite3_close(db);


                    response->setStatusCode(
                        drogon::k500InternalServerError
                    );


                    response->setBody(
                        R"({"success":false,"message":"Stock update failed"})"
                    );


                    callback(response);

                    return;
                }
            }



            sqlite3_exec(
                db,
                "COMMIT;",
                nullptr,
                nullptr,
                nullptr
            );


            sqlite3_close(db);



            std::string checkoutResponse =
                "{\"success\":true,"
                "\"message\":\"Order placed successfully\","
                "\"orderId\":" +
                std::to_string(orderId) +
                ",\"totalAmount\":" +
                std::to_string(totalAmount) +
                "}";


            response->setStatusCode(
                drogon::k200OK
            );


            response->setBody(
                checkoutResponse
            );


            callback(response);
        }
    );




    drogon::app().registerHandler(
    "/api/orders",
    [](const drogon::HttpRequestPtr &req,
       std::function<void(const drogon::HttpResponsePtr &)>&& callback)
    {
        const auto &params = req->getParameters();

        if (params.find("buyerId") == params.end())
        {
            Json::Value errorJson;
            errorJson["success"] = false;
            errorJson["message"] = "Buyer ID is required.";

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(errorJson);

            addCorsHeaders(response);
            callback(response);
            return;
        }

        int buyerId =
            std::stoi(params.at("buyerId"));

        sqlite3 *db = nullptr;

        if (sqlite3_open(
                "database/ArshuMart.db",
                &db) != SQLITE_OK)
        {
            Json::Value errorJson;
            errorJson["success"] = false;
            errorJson["message"] = "Unable to open database.";

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(errorJson);

            addCorsHeaders(response);
            callback(response);

            if (db)
                sqlite3_close(db);

            return;
        }

        const char *sql =
    "SELECT "
    "o.id, o.total_amount, o.status, o.created_at, "
    "oi.product_id, oi.quantity, oi.price, "
    "p.name, p.image_url "
    "FROM orders o "
    "JOIN order_items oi ON o.id = oi.order_id "
    "LEFT JOIN products p ON oi.product_id = p.id "
    "WHERE o.buyer_id = ? "
    "ORDER BY o.id DESC, oi.id ASC;";

        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(
                db,
                sql,
                -1,
                &stmt,
                nullptr) != SQLITE_OK)
        {
            Json::Value errorJson;
            errorJson["success"] = false;
            errorJson["message"] = "Unable to fetch orders.";

            auto response =
                drogon::HttpResponse::newHttpJsonResponse(errorJson);

            addCorsHeaders(response);
            callback(response);

            sqlite3_close(db);
            return;
        }

        sqlite3_bind_int(
            stmt,
            1,
            buyerId
        );

        Json::Value responseJson;
        responseJson["success"] = true;
        responseJson["orders"] = Json::arrayValue;

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            Json::Value order;

            order["id"] =
                sqlite3_column_int(stmt, 0);

            order["totalAmount"] =
                sqlite3_column_double(stmt, 1);

            order["status"] =
                reinterpret_cast<const char *>(
                    sqlite3_column_text(stmt, 2)
                );

            order["createdAt"] =
                reinterpret_cast<const char *>(
                    sqlite3_column_text(stmt, 3)
                );

            responseJson["orders"].append(order);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        auto response =
            drogon::HttpResponse::newHttpJsonResponse(
                responseJson
            );

        addCorsHeaders(response);
        callback(response);
    },
    {drogon::Get}
);

    drogon::app()
        .addListener(
            "127.0.0.1",
            8080
        )
        .run();


    return 0;
}