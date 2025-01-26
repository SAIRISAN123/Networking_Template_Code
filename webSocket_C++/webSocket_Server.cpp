#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <functional>

using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    // cout << "Server received: " << msg->get_payload() << endl;
    try {
        // Echo the message back to the client UPPER Case

        // Convert the message to upper case
        string upper_case_msg = msg->get_payload();
        for (char& c : upper_case_msg) {
            c = toupper(c);
        }

        // send
        s->send(hdl, upper_case_msg, msg->get_opcode());
        
        // s->send(hdl, msg->get_payload(), msg->get_opcode());
        
    } catch (const websocketpp::exception& e) {
        cerr << "Error sending message: " << e.what() << endl;
    }
}

void on_open(server* s, websocketpp::connection_hdl hdl) {
    cout << "Client connected!" << endl;
}

int main() {
    server ws_server;

    // Initialize Asio transport
    ws_server.init_asio();

    // Set up the message handler
    ws_server.set_message_handler(bind(&on_message, &ws_server, placeholders::_1, placeholders::_2));

    // Set up the open handler
    ws_server.set_open_handler(bind(&on_open, &ws_server, placeholders::_1));

    // Listen on port 9002
    ws_server.listen(9002);

    // Start the server accept loop
    ws_server.start_accept();

    // Start the ASIO io_service run loop
    cout << "WebSocket server started on port 9002" << endl;
    ws_server.run();

    return 0;
}