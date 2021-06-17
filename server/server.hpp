#pragma once
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <memory>
#include <vector>


class session : public std::enable_shared_from_this<session> {

  public:
    explicit session(boost::asio::io_context &io_context,
                     boost::asio::ip::tcp::socket t_socket);
    void go(std::string ID);
    void timer_callback(boost::asio::yield_context);
    static std::vector<std::pair<std::shared_ptr<session>, std::string>>
        clients;
    static std::vector<std::pair<std::shared_ptr<session>, std::string>>
        readers;
    boost::asio::ip::tcp::socket socket;
    bool pair;

  private:
    boost::asio::steady_timer timer;
    boost::asio::strand<boost::asio::io_context::executor_type> strand;
};