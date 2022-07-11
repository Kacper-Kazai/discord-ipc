#include "discord-ipc/ipc_connection.h"
#include "discord-ipc/serialization.h"
#include <nlohmann/json.hpp>

#include <iostream>
#include <curl/curl.h>

using nlohmann::json;

static std::string application_id = "*PUT CLIENT_ID HERE*";
static std::string client_secret = "*PUT CLIENT_SECRET HERE*";

size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s){
    s->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

int main() {
    ipc_connection* connection = ipc_connection::create(application_id.c_str());

    std::function<void(std::string&)> authenticate = [connection](std::string& event_data) {
        json data_json = json::parse(event_data);

        packet speaking_start_packet = create_command_packet("GET_GUILDS", "");
        connection->send(speaking_start_packet, [](std::string& event_data) {
            json data_json = json::parse(event_data);
            std::cout << data_json.dump(2) << "\n";
        });
    };

    std::function<void(std::string&)> authorization = [connection, authenticate](std::string& event_data) {
        json data_json = json::parse(event_data);

        if (!data_json.contains("code") || !data_json.at("code").is_string()) return;
        std::string code{};
        data_json.at("code").get_to(code);

        CURL* curl;
        CURLcode res;

        std::string s;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

            std::string fields = "grant_type=authorization_code&client_id="+application_id+"&client_secret="+client_secret+"&code=" + code;
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());


            curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/oauth2/token");

            res = curl_easy_perform(curl);

            if (res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
        }
        json test = json::parse(s);
        std::string token{};
        test.at("access_token").get_to(token);
        
        packet send_packet = create_authenticate_packet(token);
        connection->send(send_packet, authenticate);
    };

    connection->on("READY", [connection, authorization](std::string& event_data) {
        json data_json = json::parse(event_data);

        std::string username{};
        data_json.at("user").at("username").get_to(username);
        std::cout << "Welcome " << username << "!\n";

        std::vector<std::string> scopes = { "rpc" };
        packet send_packet = create_authorize_packet(application_id.c_str(), scopes);
        connection->send(send_packet, authorization);
    });

    while (true) {
        connection->loop();
    }
    return 0;
}