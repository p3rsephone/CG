#include "headers/Parser.h"

using namespace tinyxml2;
using namespace std;

Parser::Parser(){   
}

void Parser::ReadXML(Scene* scene, char* xml){
    XMLDocument xmlDoc;

    char xmlDir[80];
    memset(xmlDir,0,80);
    strcat(xmlDir,"files/");
    strcat(xmlDir,xml);

    XMLError eResult = xmlDoc.LoadFile(xmlDir);

    XMLCheckResult(eResult);
    XMLNode * pRoot = xmlDoc.FirstChild();

    if (pRoot == nullptr) {

        cout << "wrong xml syntax" << endl;
        exit(0);

    }
    else{

        XMLElement * pElement = pRoot->FirstChildElement("model");
        if (pElement == nullptr){

            cout<< "no models" << endl;
            exit(0);

        }
        else{

            string s;

            for(;pElement; pElement=pElement->NextSiblingElement()){

                if(pElement->Attribute("file")){

                    Model* model = new Model();

                    s =pElement->Attribute("file");

                    string fileDir = "files/" + s;
                    ifstream infile(fileDir);

                    if(!infile) {
                        cout << "Cannot open input file.\n";
                    }

                    string line;

                    while (getline(infile, line))
                    {
                        vector<string> v;
                        istringstream buf(line);
                        for(string word; buf >> word; )
                            v.push_back(word);
                        int it = 0;
                        double x;
                        double y;
                        double z;
                        for(vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
                            if(it==0) x=stof(*i);
                            if(it==1) y=stof(*i);
                            if(it==2) z=stof(*i);
                            it++;
                        }
                        Point* p = new Point(x,y,z);
                        model->addElement(p);
                    }

                    scene->addModel(model);

                }

            }
        }
    }
}