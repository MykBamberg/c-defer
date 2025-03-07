#include "defer.h"

#include <curl/curl.h>
#include <stdio.h>

int main(int argc, char* argv[argc]) {
    char* url = "https://wttr.in";
    char* output_file = "/dev/stdout";
    if (argc >= 2) {
        url = argv[1];
    } if (argc >= 3) {
        output_file = argv[2];
    } if (argc > 3) {
        fprintf(stderr, "Usage: %s [URL] [output file]\n", argv[0]);
        return 1;
    }

    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
        fprintf(stderr, "Error during curl init.\n");
        return 1;
    }
    defer {curl_global_cleanup();};

    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error during curl init.\n");
        return 1;
    }
    defer {curl_easy_cleanup(curl);};

    FILE* file = fopen(output_file, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    defer {fclose(file);};

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/8.12.0");

    if (curl_easy_perform(curl) != CURLE_OK) {
        fprintf(stderr, "Error during network transfer.\n");
        return 1;
    }
}
