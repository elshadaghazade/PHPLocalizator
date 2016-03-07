#include <phpcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "rapidxml-1.13/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class PHPLocalizator : public Php::Base {
private:
    Php::Value _folderPath = "";
    Php::Value _locale = "";
    Php::Array _words;
    string _specialKey = "{%w}";
public:

    PHPLocalizator() {
    }

    virtual ~PHPLocalizator() {
    }

    void __construct(Php::Parameters &params) {

    }

    void loadXml(string &param) {
        string fileName = param;
        string filePath;
        if (_folderPath) {
            string s = _folderPath;
            filePath = s + "/";
        }

        if (_locale) {
            string s = _locale;
            filePath += s + "/";
        }

        filePath += fileName;
        string xmlFileName = filePath + ".xml";
        ifstream myfile(xmlFileName);
        rapidxml::xml_document<> doc;


        bool xmlSyntaxValid = false;


        vector<char> buffer((istreambuf_iterator<char>(myfile)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        doc.parse<0>(&buffer[0]);

        std::string s = "contents";

        if (doc.first_node("contents")) {
            if (doc.first_node("contents")->first_node("element")) {
                if (doc.first_node("contents")->first_node("element")->first_node("name")) {
                    if (doc.first_node("contents")->first_node("element")->first_node("value")) {
                        xmlSyntaxValid = true;
                    }
                }
            }
        }

        if (!xmlSyntaxValid) {
            return;
        }

        for (xml_node<> *node = doc.first_node("contents")->first_node("element"); node; node = node->next_sibling()) {
            string keyword = param + "/";
            keyword += node->first_node("name")->value();
            _words[keyword] = node->first_node("value")->value();
        }
    }

    Php::Value get(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("The length of parameters of the get method is less than one");
        }

        // first argument should be the keyword of string in xml
        string keywordPath = params[0];
        string arg1 = keywordPath;
        /* keyword string should be looks like this: (([inner folder name]/){1,})?[xml file name]/[keyword].
         * This ierarchy shows the exact location of keyword. As you see the inner folders ierarchy should be as many as it needs.
         * If a xml file locates in the root folder than keyword string should looks like this: [xml file name]/[keyword].
         * We are separating the keyword from file path.
         */
        for (int i = keywordPath.size() - 1; i >= 0; i--) {
            if (keywordPath[i] != '/') {
                keywordPath.erase(i, 1);
            } else {
                break;
            }
        }

        // clean a slash at the end of file path
        if (keywordPath[keywordPath.size() - 1] == '/') {
            keywordPath.erase(keywordPath.size() - 1, 1);
        }

        if (!_words[arg1]) {
            loadXml(keywordPath);
        }


        if (_words[arg1]) {
            string word = _words[arg1];

            if (params.size() > 1) {
                for (int unsigned i = 1; i < params.size(); i++) {
                    string rplc = params[i];
                    size_t f;
                    if ((f = word.find(_specialKey)) != string::npos) {
                        word.replace(f, std::string(_specialKey).length(), rplc);
                    }
                }
            }

            return word;

        } else {
            return "";
        }
    }

    Php::Value setSpecialKey(Php::Parameters &params) {
        string specialKey = params[0];
        _specialKey = specialKey;
        return this;
    }

    Php::Value getSpecialKey() {
        return _specialKey;
    }

    Php::Value setFolderPath(Php::Parameters &params) {
        _folderPath = params[0];
        return this;
    }

    Php::Value getFolderPath() {
        return _folderPath;
    }

    Php::Value setLocale(Php::Parameters &params) {
        _locale = params[0];
        return this;
    }

    Php::Value getLocale() {
        return _locale;
    }
};

extern "C" {

    PHPCPP_EXPORT void *get_module() {

        static Php::Extension myExtension("php_localizator", "1.0");

        Php::Class<PHPLocalizator> myClass("PHPLocalizator");

        myClass.method("__construct", &PHPLocalizator::__construct);

        myClass.method("getFolderPath", &PHPLocalizator::getFolderPath, Php::Public | Php::Final);
        myClass.method("setFolderPath", &PHPLocalizator::setFolderPath, Php::Public | Php::Final,{
            Php::ByVal("folderPath", Php::Type::String, true)
        });

        myClass.method("getLocale", &PHPLocalizator::getLocale, Php::Public | Php::Final);
        myClass.method("setLocale", &PHPLocalizator::setLocale, Php::Public | Php::Final,{
            Php::ByVal("locale", Php::Type::String, true)
        });

        myClass.method("getSpecialKey", &PHPLocalizator::getSpecialKey, Php::Public | Php::Final);
        myClass.method("setSpecialKey", &PHPLocalizator::setSpecialKey, Php::Public | Php::Final,{
            Php::ByVal("specialKey", Php::Type::String, true)
        });

        myClass.method("get", &PHPLocalizator::get, Php::Public | Php::Final);

        myExtension.add(std::move(myClass));

        return myExtension;
    }
}
