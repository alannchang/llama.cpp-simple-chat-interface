#include "LLMInference.h"
#include <memory>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string modelPath = "../../gguf-models/Llama-3.2-3B-Instruct.IQ2_XS.gguf";
    float temperature = 1.0f;
    float minP = 0.05f;
    std::unique_ptr<LLMInference> llmInference = std::make_unique<LLMInference>();
    llmInference->loadModel(modelPath, minP, temperature);
    llmInference->addChatMessage("You are a helpful assistant", "system");
    while (true) {
        std::cout << "Enter query:\n";
        std::string query;
        std::getline(std::cin, query);
        if (query == "exit") {
            break;
        }
        llmInference->startCompletion(query);
        std::string predictedToken;
        while ((predictedToken = llmInference->completionLoop()) != "[EOG]") {
            std::cout << predictedToken;
            fflush(stdout);
        }
        std::cout << '\n';
    }
    return 0;
}
