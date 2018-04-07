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
        int contador = 0;
        for(;pNode; pNode=pNode->NextSibling()){

            XMLElement* pElement = pNode->ToElement();

            if(strcmp(pElement->Name(),"model") == 0){

                if(pElement->Attribute("file")){
                    Triangle* t;
                    s =pElement->Attribute("file");
                    Model* model = new Model(s);

                    string fileDir = "files/" + s;
                    ifstream infile(fileDir);

                    if(!infile) {
                        cout << "Cannot open input file.\n";
                    }
                    else {
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
                            if( contador == 0 )
                                t = new Triangle();

                            Point* p = new Point(x,y,z);
                            t->addPoint(p);

                            if( contador == 2 )
                                model->addElement(t);

                            contador = (contador+1) % 3;
                        }

                        group->addModel(model);
                    }
                }
            } else

            if(strcmp(pElement->Name(),"translate") == 0){

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

                Translate* t = new Translate(x,y,z);

                group->addTransformation(t);

            } else

            if(strcmp(pElement->Name(),"rotate") == 0){

                double angle = 0;
                double axisx = 0;
                double axisy = 0;
                double axisz = 0;

                if(pElement->Attribute("angle")) {
                    angle = stod(pElement->Attribute("angle"));
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

                Rotate* r = new Rotate(angle,axisx,axisy,axisz);

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

                Group* g = new Group(speed);

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
