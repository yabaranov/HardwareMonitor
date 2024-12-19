#pragma once

#include <string>
#include <functional>

struct sqlite3;

class Database
{
public:
    Database(const std::string& dbPath);
    ~Database();

    bool execute(const std::string& query);
    bool execute(const std::string& query, const std::function<void(int, char**, char**)>& callback);

private:
    bool open(const std::string& dbPath);
    void close();

    std::string m_dbPath;
    sqlite3* m_db;
};
