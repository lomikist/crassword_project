#include "../includes/model.h"
#include "../includes/word.h"


Model::Model(){

}

Model::~Model(){

}

std::vector<Word> Model::getQuestions(){

    std::ifstream file("other/questions.json");
    if (!file.is_open()) {

    }
    json jsonArray;
    try {
        file >> jsonArray; 
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
    }
    file.close(); 
    std::vector<Word> list;
    for (const auto& obj : jsonArray) {
        Word item;

        item.question   = obj["clue"].get<std::string>().c_str();
        item.answer     = obj["answer"].get<std::string>().c_str();
        item.length     = obj["length"].get<int>();
        list.push_back(item);
    }
    return list;
}