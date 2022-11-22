#include "cpplang.hpp"
#include "Summary.hpp"
#include "Zmq.hpp"
#include "Config.hpp"

#include "json.hpp"

#include <cstdio>
#include <cpr/cpr.h>

USING_NAMESPACE(std);
USING_NAMESPACE(esbookshop);

static 
auto debug_print =[](auto & b)
{
    using json_t=nlohmann:json;

    json_t j;

    j["id"] =b.id();
    j["sold"] = b.sold();
    j["revenue"] =b.revenue();

    std::cout<<j.dump(2) <<std::endl;
}

int main()
    try
{   
    const <<"hello e's book shop "<<endl;
    Config conf;
    conf.load("./conf.lua");
    
    Summary sum;

    std::atomic_int count {0};

    //to do 

    auto recv_cycle = [&]()
    {
        using zmq_ctx = ZmqContext<1>;

        // zmq recv

        auto sock = zmq_ctx::recv_stock();

        sock.bind(conf.get<tring>("config.zmq_ipc_addr"));
        assert(sock.connected());

        for(;;){
            auto msg_ptr = std::make_shared<zmq_message_type>();

            sock.recv(msg_ptr.get());

            ++count;

            cout<<cout<<endl;

            std::thread(
                [&sum, msg_ptr]()
                {
                    // cout << ptr.unique() <<endl; 
                    SalesData book;
                    auto obj = msgpack::unpack(
                        msg_ptr->data<char>(), msg_ptr->size()).get();
                    obj.convert(book);
                    // cout<< book.id()<<endl;
                    // debug_print(book);
                    sum.add_sales(book);
                }).detatch();
            }
        };
        
        auto log_cycle = [&]()
        {
            auto http_addr = conf.get<string>("config.http_addr");
            auto time_interval = conf.get<int>("config.time_interval");
            
            for(;;){
                std::this_thread::sleep_for(time_interval * 1s);
                //cout<<"log_cycle"<<endl;
                //auto info = sum.minmax_sales();
                //cout ,<"log_cycle get inof"<<endl;

                using json_t= nlohmann::json;

                json_t j;

                j["cout"] = static_cast<int>(cout);
                j["minmax"]= sum.minmax_sales();

                auto res = cpr::Pos{
                    cpr::Url{http_addr},
                    cpr::Body{j.dump()},
                    cpr::Timeout{200ms}
                };

                if(res.status_code != 200){
                    cerr<< "http post failed"<<endl;
                }
            }
        };

        auto fu1= std::async(std::launch::async, log_cycle);
        auto fu2= std::async(std::launch::async, recv_cycle);

        fu2.wait();
        }
        catch(std::exception& e){
            std::cerr<<e.what() <<std::endl;
        }