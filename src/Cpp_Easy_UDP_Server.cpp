#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

char buff[512];
io_service service;
boost::asio::ip::udp::endpoint sender_ep;
ip::udp::socket sock(service);

void on_read(const boost::system::error_code & err,std::size_t read_bytes){
    std::cout << "read " << read_bytes << std::endl;
    sock.async_receive_from(buffer(buff), sender_ep,on_read);
}

int main(void){
    ip::udp::endpoint ep(ip::address::from_string("127.0.0.1"),8001);
    sock.open(ep.protocol());
    sock.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    sock.bind(ep);
    sock.async_receive_from(buffer(buff,512),sender_ep,on_read);
    service.run();

    return 0;
}
