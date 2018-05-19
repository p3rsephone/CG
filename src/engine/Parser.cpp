#include "headers/Parser.h"

using namespace tinyxml2;
using namespace std;

/**
 * Creates a new Parser structure
 */
Parser::Parser(){
}

void Parser::ParseRow(XMLNode* pRoot, Group* group){
    XMLNode * pNode = pRoot->FirstChild();
    if (pNode == nullptr){

        cout<< "no models" << endl;
        exit(0);

    }
    else{

        string s;
        float speed = 0;
        for(;pNode; pNode=pNode->NextSibling()){

            XMLElement* pElement = pNode->ToElement();

            if(strcmp(pElement->Name(),"model") == 0){

                if(pElement->Attribute("file")){
                    s =pElement->Attribute("file");

                    string fileDir = "files/" + s;
                    ifstream infile(fileDir);

                    if(!infile) {
                        cout << "Cannot open input file.\n";
                    }
                    else {
                        string line;

                        getline(infile, line);
                        int size = stof(line);

                        Model* model = new Model(s, size);

                        int coord = 0;
                        while (getline(infile, line) && (coord<sizep))
                        {
                            vector<string> v;
                            istringstream buf(line);
                            for(string word; buf >> word; )
                                v.push_back(word);
                            int it = 0;
                            float x;
                            float y;
                            float z;
                            for(vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
                                if(it==0) x=stof(*i);
                                if(it==1) y=stof(*i);
                                if(it==2) z=stof(*i);
                                it++;
                            }

                            model->addElementP(x);
                            model->addElementP(y);
                            model->addElementP(z);
                            coord+=3;
                        }

                        coord=0;

                        while (getline(infile, line) && (coord<sizen))
                        {
                            vector<string> v;
                            istringstream buf(line);
                            for(string word; buf >> word; )
                                v.push_back(word);
                            int it = 0;
                            float x;
                            float y;
                            float z;
                            for(vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
                                if(it==0) x=stof(*i);
                                if(it==1) y=stof(*i);
                                if(it==2) z=stof(*i);
                                it++;
                            }

                            model->addElementN(x);
                            model->addElementN(y);
                            model->addElementN(z);
                            coord+=3;
                        }

                        coord=0;

                        while (getline(infile, line) && (coord<sizen))
                        {
                            vector<string> v;
                            istringstream buf(line);
                            for(string word; buf >> word; )
                                v.push_back(word);
                            int it = 0;
                            float x;
                            float y;
                            float z;
                            for(vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
                                if(it==0) x=stof(*i);
                                if(it==1) y=stof(*i);
                                if(it==2) z=stof(*i);
                                it++;
                            }

                            model->addElementT(x);
                            model->addElementT(y);
                            model->addElementT(z);
                            coord+=3;
                        }

                        group->addModel(model);
                    }
                }

                if(pElement->Attribute("texture")){

                }

                if(pElement->Attribute("diffR")){

                }

                if(pElement->Attribute("diffG")){

                }

                if(pElement->Attribute("diffB")){

                }

                if(pElement->Attribute("ambR")){

                }

                if(pElement->Attribute("ambG")){

                }

                if(pElement->Attribute("ambB")){

                }

                if(pElement->Attribute("emiR")){

                }

                if(pElement->Attribute("emiG")){

                }

                if(pElement->Attribute("emiB")){

                }

                if(pElement->Attribute("specR")){

                }

                if(pElement->Attribute("specG")){

                }

                if(pElement->Attribute("specB")){

                }

            } else

            if(strcmp(pElement->Name(),"translate") == 0){
                float ti=10;
                if(pElement->Attribute("time")) {
                    ti = atoi(pElement->Attribute("time"));
                }

                XMLNode * pNode1 = pNode->FirstChild();
                vector<Point*> pontos;
                float x=0;
                float y=0;
                float z=0;

                Translate* t = new Translate(ti);

                for(;pNode1; pNode1 = pNode1->NextSibling()){

                    XMLElement* pElement1 = pNode1->ToElement();
                    
                    if(strcmp(pElement1->Name(),"point") == 0){

                        if(pElement1->Attribute("X")) {
                            x = stof(pElement1->Attribute("X"));
                        }
                        if(pElement1->Attribute("Y")) {
                            y = stof(pElement1->Attribute("Y"));
                        }
                        if(pElement1->Attribute("Z")){
                            z = stof(pElement1->Attribute("Z"));
                        }

                        t->addElement(new Point(x,y,z));
                    }

                }

                group->addTransformation(t);

            } else

            if(strcmp(pElement->Name(),"rotate") == 0){

                double angle = 0;
                double axisx = 0;
                double axisy = 0;
                double axisz = 0;
                double time = 0;

                if(pElement->Attribute("angle")) {
                    angle = stod(pElement->Attribute("angle"));
                }

                if(pElement->Attribute("time")) {
                    time = stod(pElement->Attribute("time"));
                }

                if(pElement->Attribute("axisX")) {
                    axisx = stod(pElement->Attribute("axisX"));
                }
                if(pElement->Attribute("axisY")) {
                    axisy = stod(pElement->Attribute("axisY"));
                }
                if(pElement->Attribute("axisZ")){
                    axisz = stod(pElement->Attribute("axisZ"));
                }

                Rotate* r = new Rotate(angle,time,axisx,axisy,axisz);

                group->addTransformation(r);

            } else

            if(strcmp(pElement->Name(),"scale") == 0){

                double x = 0;
                double y = 0;
                double z = 0;

                if(pElement->Attribute("X")) {
                    x = stod(pElement->Attribute("X"));
                }
                if(pElement->Attribute("Y")) {
                    y = stod(pElement->Attribute("Y"));
                }
                if(pElement->Attribute("Z")){
                    z = stod(pElement->Attribute("Z"));
                }

                Scale* s = new Scale(x,y,z);

                group->addTransformation(s);

            } else

            if(strcmp(pElement->Name(),"group") == 0) {

                float speed = 0;

                if(pElement->Attribute("speed")) {
                    speed = stof(pElement->Attribute("speed"));
                }

                Group* g = new Group();

                ParseRow(pNode,g);

                group->addGroup(g);
            } else

            if(strcmp(pElement->Name(),"models") == 0){

                ParseRow(pNode,group);
            }
        }
    }
}

/**
 * Reads a XML file with models
 * Add those models to the scene
 @param scene Where models will be placed
 @param xml Name of the XML file
 */
void Parser::ReadXML(Group* group, char* xml){
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
        ParseRow(pRoot,group);
    }
}
