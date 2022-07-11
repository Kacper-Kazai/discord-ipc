#include "discord-ipc/ipc_connection.h"
#include "discord-ipc/serialization.h"

#include <nlohmann/json.hpp>
#include <curl/curl.h>

using discord_ipc::events;
using discord_ipc::packets;
using discord_ipc::types::scopes;

using nlohmann::json;

static std::string discord_auth_token_endpoint = "https://discordapp.com/api/oauth2/token";

size_t curl_writefunction_to_string(void* ptr, size_t size, size_t nmemb, std::string* response) {
    response->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

std::string get_access_token(std::string client_id, std::string client_secret, std::string code) {
    CURL* curl;
    CURLcode curl_code;
    curl = curl_easy_init();
    if (!curl) {
        curl_easy_cleanup(curl);
        return "";
    }
    curl_easy_setopt(curl, CURLOPT_URL, discord_auth_token_endpoint.c_str());

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writefunction_to_string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    std::string postfields = "grant_type=authorization_code&client_id=" + client_id + "&client_secret=" + client_secret + "&code=" + code;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());

    curl_code = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (curl_code != CURLE_OK) return "";

    json response_json = json::parse(response);
    if (!response_json.contains("access_token")) return "";

    return response_json["access_token"];
}

int main(int argc, char* argv[]) {
    std::string client_id = "";
    std::string client_secret = "";

    for (int arg_counter = 1; arg_counter < argc; arg_counter++) {
        std::string arg = argv[arg_counter];
        if (arg.substr(0, 2) != "--") continue;

        size_t delimiter_position = arg.find("=");
        std::string key = arg.substr(2, delimiter_position - 2);
        std::string value = arg.substr(delimiter_position + 1, arg.length() - delimiter_position - 1);

        if (key == "client_id") client_id = value;
        else if (key == "client_secret") client_secret = value;
    }
    if (client_id.empty() || client_secret.empty()) {
        printf("Please provide --client-id and --client-secret arguments.\n\nexample:\n%s --client_id=332269999912132097 --client_secret=937it3ow87i4ery69876wqire\n", argv[0]);
        return 0;
    }

    ipc_connection* connection = new ipc_connection(client_id);

    std::function<void(std::string&)> authenticate = [connection](std::string& event_data) {
        connection->send(packets::get_guilds(), [connection](std::string& event_data) {
            json packet_json = json::parse(event_data);
            printf("%s\n", packet_json["data"]["guilds"].dump(2).c_str());
            connection->stop();
        });
    };

    std::function<void(std::string&)> authorization = [client_secret, connection, authenticate](std::string& event_data) {
        json packet_json = json::parse(event_data);
        json data_json = packet_json["data"];

        if (!data_json.contains("code") || !data_json.at("code").is_string()) {
            connection->stop();
            return;
        }
        std::string code = data_json["code"];

        std::string token = get_access_token(connection->get_application_id(), client_secret, code);
        if (token.empty()) {
            printf("Token exchange failed.\n");
            connection->stop();
            return;
        }
        connection->send(packets::authenticate(token), authenticate);
    };

    connection->on(events::ready, [connection, authorization](std::string& event_data) {
        json packet_json = json::parse(event_data);
        json data_json = packet_json["data"];

        std::string username = data_json["user"]["username"];
        printf("Welcome %s!\n", username.c_str());

        scopes scopes;
        scopes.add(scopes::rpc);
        connection->send(packets::authorize(connection->get_application_id(), scopes), authorization);
    });

    connection->start();
    connection->join();

    return 0;
}