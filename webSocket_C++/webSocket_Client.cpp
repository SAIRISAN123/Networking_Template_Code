// #include <websocketpp/config/asio_no_tls_client.hpp>
// #include <websocketpp/client.hpp>
// #include <iostream>
// #include <functional>
// #include <thread>
// #include <chrono>

// using namespace std;

// typedef websocketpp::client<websocketpp::config::asio_client> client;

// void on_message(client* c, websocketpp::connection_hdl hdl, client::message_ptr msg) {
//     cout << "Message from Server: " << msg->get_payload() << endl;
// }

// void on_open(client* c, websocketpp::connection_hdl hdl) {
//     cout << "Connected to server!" << endl;

//     // Send a message to the server
//     c->send(hdl, "Hello from client!", websocketpp::frame::opcode::text);
// }

// int main() {
//     client ws_client;

//     // Initialize Asio transport
//     ws_client.init_asio();

//     // Set up the message handler
//     ws_client.set_message_handler(bind(&on_message, &ws_client, placeholders::_1, placeholders::_2));

//     // Set up the open handler
//     ws_client.set_open_handler(std::bind(&on_open, &ws_client, placeholders::_1));

//     // Create a connection to the server
//     websocketpp::lib::error_code ec;
//     client::connection_ptr con = ws_client.get_connection("ws://localhost:9002", ec);

//     if (ec) {
//         cerr << "Could not create connection: " << ec.message() << endl;
//         return 1;
//     }

//     // Connect to the server
//     ws_client.connect(con);

//     // Start the ASIO io_service run loop in a separate thread
//     std::thread t([&ws_client]() {
//         ws_client.run();
//     });

//     // Wait for the connection to be established and the message to be sent
//     std::this_thread::sleep_for(std::chrono::seconds(2));

//     // Join the thread
//     t.join();

//     return 0;
// }






// chat feature
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

typedef websocketpp::client<websocketpp::config::asio_client> client;

void on_message(client* c, websocketpp::connection_hdl hdl, client::message_ptr msg) {
    cout << "Message from Server: " << msg->get_payload() << endl;
}

void on_open(client* c, websocketpp::connection_hdl hdl) {
    cout << "Connected to server! Type your messages below:" << endl;
}

void on_close(client* c, websocketpp::connection_hdl hdl) {
    cout << "Disconnected from server." << endl;
}

int main() {
    client ws_client;

    // Initialize Asio transport
    ws_client.init_asio();

    // Set up the message handler
    ws_client.set_message_handler(bind(&on_message, &ws_client, placeholders::_1, placeholders::_2));

    // Set up the open handler
    ws_client.set_open_handler(std::bind(&on_open, &ws_client, placeholders::_1));

    // Set up the close handler
    ws_client.set_close_handler(std::bind(&on_close, &ws_client, placeholders::_1));

    // Create a connection to the server
    websocketpp::lib::error_code ec;
    client::connection_ptr con = ws_client.get_connection("ws://localhost:9002", ec);

    if (ec) {
        cerr << "Could not create connection: " << ec.message() << endl;
        return 1;
    }

    // Connect to the server
    ws_client.connect(con);

    // Start the ASIO io_service run loop in a separate thread
    std::thread t([&ws_client]() {
        ws_client.run();
    });

    // Wait for the connection to be established
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Chat loop
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        // Send the message to the server
        ws_client.send(con->get_handle(), input, websocketpp::frame::opcode::text);
    }

    // Close the connection
    ws_client.close(con->get_handle(), websocketpp::close::status::normal, "User disconnected");

    // Join the thread
    t.join();

    return 0;
}
