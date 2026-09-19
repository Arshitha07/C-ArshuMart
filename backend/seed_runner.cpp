#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main()
{
    sqlite3* db = nullptr;

    if (sqlite3_open("database/ArshuMart.db", &db) != SQLITE_OK)
    {
        std::cout << "Database opening failed!" << std::endl;

        if (db != nullptr)
        {
            sqlite3_close(db);
        }

        return 1;
    }

    const char* cleanupSql = R"SQL(
        DELETE FROM products
        WHERE id NOT IN (
            SELECT MIN(id)
            FROM products
            GROUP BY name
        );
    )SQL";

    char* errorMessage = nullptr;

    if (sqlite3_exec(
        db,
        cleanupSql,
        nullptr,
        nullptr,
        &errorMessage
    ) != SQLITE_OK)
    {
        std::cout << "Duplicate cleanup failed: "
                  << (errorMessage ? errorMessage : "Unknown error")
                  << std::endl;

        if (errorMessage != nullptr)
        {
            sqlite3_free(errorMessage);
        }

        sqlite3_close(db);
        return 1;
    }

    std::ifstream file("database/seed.sql");

    if (!file.is_open())
    {
        std::cout << "seed.sql not found!" << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string sql = buffer.str();

    errorMessage = nullptr;

    if (sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        &errorMessage
    ) != SQLITE_OK)
    {
        std::cout << "Seed failed: "
                  << (errorMessage ? errorMessage : "Unknown error")
                  << std::endl;

        if (errorMessage != nullptr)
        {
            sqlite3_free(errorMessage);
        }

        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    std::cout << "Duplicate products cleaned successfully!" << std::endl;
    std::cout << "ArshuMart products seeded successfully!" << std::endl;

    return 0;
}