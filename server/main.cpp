#include "src/rpc_server.hpp"
#include "registed_fun/sort/sort.hpp"

int main() {
    jrRPC::server server(8000, 1000);
    server.regist_procedure("int_sort", std::function<std::vector<int>(std::vector<int>)>(int_sort));
    server.run();
    return 0;
}
