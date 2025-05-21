#include <iostream>
#include <list>
#include <string>
#include <chrono>

namespace Logger {

enum class LogLevel {
    LOG_NORMAL,
    LOG_WARNING,
    LOG_ERROR
};

class LogContent {
public:
    std::chrono::system_clock::time_point timestamp;
    LogLevel level;
    std::string message;
};

class Logger {
private:
    static Logger* instance;
    std::list<LogContent> log;
    const int MAX_LOG_SIZE = 10;

    Logger() = default;
    ~Logger() {delete instance;}
public:
    static Logger* get_instance() {
        if (instance == nullptr)
            instance = new Logger();
        return instance;
    }

    void log_event(LogLevel level, const std::string& message) {
        LogContent log_cont;
        log_cont.timestamp = std::chrono::system_clock::now();
        log_cont.level = level;
        log_cont.message = message;
        log.push_front(log_cont);

        if (log.size() > MAX_LOG_SIZE) {
            log.pop_back();
        }
    }

    void print_events() {
        for (auto elem : log) {
            std::time_t timestamp = std::chrono::system_clock::to_time_t(elem.timestamp);
            std::cout << std::ctime(&timestamp) << " - " << static_cast<int>(elem.level)
                      << " - " << elem.message << std::endl;
        }
    }
};

Logger* Logger::instance = nullptr;

}


int main()
{
    Logger::Logger  *log = Logger::Logger::get_instance();
    log->log_event(Logger::LogLevel::LOG_NORMAL, "programm loaded");
    log->log_event(Logger::LogLevel::LOG_ERROR, "error happens!");
    log->print_events();
    return 0;
}
