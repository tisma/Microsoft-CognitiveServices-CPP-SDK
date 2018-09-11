#ifndef COGNITIVE_CV
#define COGNITIVE_CV

#include <fstream>
#include <map>

#include "microsoft/utils/http.h"
#include "microsoft/utils/json_serializable.h"

using namespace std;

namespace Microsoft {
    namespace CognitiveServices {
        namespace ComputerVision {
            class Analysis;
            class Description;
            struct Image;
            struct Caption;
            struct Metadata;
            struct Category;
            struct Tag;
            struct Celebrity;
            struct Landmark;
            struct Detail;
            struct FaceRectangle;
            struct Face;
            struct Color;
            struct ImageType;
            struct Adult;
			
            void ToFile(std::string filename, ios_base::openmode mode, const char* buffer, int size);
            void ToFile(std::string filename, Image& image);

            enum ApiServerRegion {
                West_US,
                West_US_2,
                East_US,
                East_US_2,
                West_Central_US,
                South_Central_US,
                West_Europe,
                North_Europe,
                Southeast_Asia,
                East_Asia,
                Australia_East,
                Brazil_South,
                Canada_Central,
                Central_India,
                UK_South,
                Japan_East
            };

            std::string ApiServer(ApiServerRegion);

            Analysis describe(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
            Analysis analyze(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
            Microsoft::CognitiveServices::ComputerVision::Image generateThumbnail(HttpContent* data, int width, int height, bool smartCropping, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);

            namespace Text {
                struct Word;
                struct Line;
                using BoundingBox = std::array<int, 8>;
                class RecognitionResult;
                HttpResponse RecognizeText(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");
                RecognitionResult RecognizeTextOperationResult(std::string url, std::string subscriptionKey, std::string ContentType="application/octet-stream");
            }

            namespace Person
            {
                void CreateGroup(HttpContent* data, std::string personGroupId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
                void TrainGroup(std::string personGroupId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
                void CreatePerson(HttpContent* data, std::string personGroupId, ApiServerRegion region,  std::string subscriptionKey, std::string ContentType);
                void AddPersonFace(HttpContent* data, std::string personGroupId, std::string personId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
                std::string Identify(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
                std::string Verify(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType);
            }
        }
    }
}

struct Microsoft::CognitiveServices::ComputerVision::Image {
  char *buffer;
  size_t size;
  std::string content_type;
  int width;
  int height;
};

struct Microsoft::CognitiveServices::ComputerVision::FaceRectangle {
    int left;
    int top;
    int width;
    int height;
	int coveringArea;
};

struct Microsoft::CognitiveServices::ComputerVision::Face {
    int age;
    std::string gender;
    Microsoft::CognitiveServices::ComputerVision::FaceRectangle position;
};

struct Microsoft::CognitiveServices::ComputerVision::Celebrity {
    std::string name;
    double confidence;
    FaceRectangle faceRectangle;
};

struct Microsoft::CognitiveServices::ComputerVision::Landmark {
    std::string name;
    double confidence;
};

struct Microsoft::CognitiveServices::ComputerVision::Detail {
    std::vector<Celebrity> celebrities;
    std::vector<Landmark> landmarks;
};

struct Microsoft::CognitiveServices::ComputerVision::Category {
    std::string name;
    double score;
    Detail detail;
};

struct Microsoft::CognitiveServices::ComputerVision::Tag {
    std::string name;
    double confidence;
};

struct Microsoft::CognitiveServices::ComputerVision::Color {
    std::string dominantColorForeground;
    std::string dominantColorBackground;
    std::vector<std::string> dominantColors;
    std::string accentColor;
    bool isBWImg;
};

struct Microsoft::CognitiveServices::ComputerVision::ImageType {
    bool clipArtType;
    bool lineDrawingType;
};

struct Microsoft::CognitiveServices::ComputerVision::Adult {
    bool isAdultContent;
    bool isRacyContent;
    double adultScore;
    double racyScore;
};

struct Microsoft::CognitiveServices::ComputerVision::Caption {
    std::string text;
    double confidence;
};

struct Microsoft::CognitiveServices::ComputerVision::Metadata {

    int width;
    int height;
    std::string format;
};

struct Microsoft::CognitiveServices::ComputerVision::Text::Word {
    Microsoft::CognitiveServices::ComputerVision::Text::BoundingBox boundingBox;
    std::string text;
};

struct Microsoft::CognitiveServices::ComputerVision::Text::Line : Microsoft::CognitiveServices::ComputerVision::Text::Word {
    std::vector<Microsoft::CognitiveServices::ComputerVision::Text::Word> words;
};

#endif
