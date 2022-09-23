#include <iostream>
#include <chrono>
#include <thread>

#define ASIO_STANDALONE
#include "asio.hpp"

struct PeriodicWorker {
    PeriodicWorker(asio::io_context& ioc) : theTimer(ioc) {}

    void theCallback(asio::error_code ec) {
        std::cout << '\a' << std::flush;
        if (ec) {
            std::cout << "Cancelled!\n";
            return;
        }
        theTimer.expires_after(waitPeriod);
        theTimer.async_wait([this](auto ec) { theCallback(ec); });
    }

    void start(std::chrono::seconds d) {
        waitPeriod = d;
        theTimer.expires_after(waitPeriod);
        theTimer.async_wait([this](auto ec) { theCallback(ec); });
    }

    void cancel() {
        theTimer.cancel();
    }

    asio::steady_timer theTimer;
    std::chrono::seconds waitPeriod = std::chrono::seconds{1};
};

void setAlarm(int sec) {
    asio::io_context ioc;
    asio::executor_work_guard<asio::io_context::executor_type> work_guard =
            asio::make_work_guard(ioc.get_executor());

    std::thread worker([&ioc]{
        while(true) {
            std::cout << "Running ioc\n";
            ioc.run();
        }
        std::cout << "Bad!\n";
    });

    PeriodicWorker periodicWorker(ioc);

    std::cout << "Created timer...\n";
    std::this_thread::sleep_for(std::chrono::seconds{2});

    std::cout << "Starting timer...\n";
    periodicWorker.start(std::chrono::seconds{sec});

    // work_guard.reset();
    worker.join();
}