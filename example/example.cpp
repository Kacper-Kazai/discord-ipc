#include "discord-ipc/ipc_connection.h"
#include "discord-ipc/serialization.h"
#include <nlohmann/json.hpp>

#include <curl/curl.h>

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

    response_json.at("access_token").get_to(response);
    return response;
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

    ipc_connection* connection = ipc_connection::create(client_id.c_str());

    std::function<void(std::string&)> authenticate = [connection](std::string& event_data) {
        json data_json = json::parse(event_data);

        packet get_guilds_packet = create_command_packet("GET_GUILDS", "");
        connection->send(get_guilds_packet, [](std::string& event_data) {
            json data_json = json::parse(event_data);
            printf("%s\n", data_json.dump(2).c_str());
        });
    };

    std::function<void(std::string&)> authorization = [client_id, client_secret, connection, authenticate](std::string& event_data) {
        json data_json = json::parse(event_data);

        if (!data_json.contains("code") || !data_json.at("code").is_string()) return;
        std::string code{};
        data_json.at("code").get_to(code);

        std::string token = get_access_token(client_id, client_secret, code);
        if (token.empty()) {
            printf("Token exchange failed.\n");
            return;
        }

        packet send_packet = create_authenticate_packet(token);
        connection->send(send_packet, authenticate);
    };

    connection->on("READY", [client_id, connection, authorization](std::string& event_data) {
        json data_json = json::parse(event_data);

        std::string username{};
        data_json.at("user").at("username").get_to(username);
        printf("Welcome %s!\n", username.c_str());

        std::vector<std::string> scopes = { "rpc" };
        packet send_packet = create_authorize_packet(client_id.c_str(), scopes);
        connection->send(send_packet, authorization);
        });

    while (true) {
        connection->loop();
    }
    return 0;
}