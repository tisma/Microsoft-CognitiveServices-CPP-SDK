#include <iostream>
#include <string.h>
#include <fstream>
#include <unistd.h>

#include "microsoft/cognitive/cognitive.h"
#include "microsoft/cognitive/cv/cv.h"

using namespace Microsoft::CognitiveServices;
using namespace Microsoft::CognitiveServices::ComputerVision;

int main(int argc, char **argv)
{
    cout << "Microsoft Cognitive Services in C++" << endl;
    cout << "Thumbnail" << endl;

    std::ifstream subscriptionKeyFile;
    std::string subscriptionKey;
    subscriptionKeyFile.open("subscriptionKey");
    std::getline(subscriptionKeyFile, subscriptionKey);
    subscriptionKeyFile.close();

    HttpContent wt;

    std::ifstream input;
    input.open(argv[1], std::ios::binary );

    // copies all data into buffer
    std::vector<char> buffer((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));

    wt.size = buffer.size();
    wt.buffer = reinterpret_cast<char*>(buffer.data());

    Image image = GenerateThumbnail(&wt, 300, 200, true, ApiServerRegion::West_Europe, subscriptionKey, "application/octet-stream");

    Microsoft::CognitiveServices::ComputerVision::ToFile("thumbnail.jpg", image);

    return 0;
}
