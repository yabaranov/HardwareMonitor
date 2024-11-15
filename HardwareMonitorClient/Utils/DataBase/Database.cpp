#include "Database.h"
#include "sqlite3.h"
#include "Logger/Logger.h"

Database::Database() : m_db(nullptr) {}

Database::~Database()
{
    close();
}

bool Database::open(const std::string& dbPath)
{
    m_dbPath = dbPath;
    if (sqlite3_open(m_dbPath.c_str(), &m_db) == SQLITE_OK)
    {
        Logger::instance().info("Open database {}", m_dbPath.c_str());
        return true;
    }
    else
    {
        Logger::instance().error("Failed to open database {}: {}", m_dbPath.c_str(), sqlite3_errmsg(m_db));
        return false;
    }
}

void Database::close()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
        Logger::instance().info("Close database {}", m_dbPath.c_str());
    }
}

bool Database::execute(const std::string& query)
{
    char* errMsg = nullptr;
    if (sqlite3_exec(m_db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        Logger::instance().error("SQL error in database {}: {}", m_dbPath.c_str(), errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::execute(const std::string& query, const std::function<void(int, char**, char**)>& callback)
{
    char* errMsg = nullptr;

    auto cb = [](void* data, int argc, char** argv, char** colNames) -> int {
        auto& func = *static_cast<std::function<void(int, char**, char**)>*>(data);
        func(argc, argv, colNames);
        return 0;
    };

    if (sqlite3_exec(m_db, query.c_str(), cb, const_cast<std::function<void(int, char**, char**)>*>(&callback), &errMsg) != SQLITE_OK) {
        Logger::instance().error("SQL error in database {}: {}", m_dbPath.c_str(), errMsg);
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}
