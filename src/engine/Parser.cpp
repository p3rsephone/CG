#include "headers/Parser.h"

using namespace tinyxml2;
using namespace std;

/**
 * Creates a new Parser structure
 */
Parser::Parser(){
}

void Parser::ColourComp(Model* model, XMLElement* pElement){
    Colour* diffuse = new Colour(0.7f,0.7f,0.7f);
    Colour* ambient = new Colour(0.3f,0.3f,0.3f);
    Colour* emission = new Colour(0,0,0);
    Colour* specular = new Colour(0,0,0);
    float shine = 0;

    if(pElement->Attribute("diffR")){
        diffuse->setR(stof(pElement->Attribute("diffR")));
    }
    if(pElement->Attribute("diffG")){
        diffuse->setG(stof(pElement->Attribute("diffG")));
    }
    if(pElement->Attribute("diffB")){
        diffuse->setB(stof(pElement->Attribute("diffB")));
    }   

    if(pElement->Attribute("ambR")){
        ambient->setR(stof(pElement->Attribute("ambR")));
    }
    if(pElement->Attribute("ambG")){
        ambient->setG(stof(pElement->Attribute("ambG")));
    }
    if(pElement->Attribute("ambB")){
        ambient->setB(stof(pElement->Attribute("ambB")));
    }

    if(pElement->Attribute("emiR")){
        emission->setR(stof(pElement->Attribute("emiR")));
    }
    if(pElement->Attribute("emiG")){
        emission->setG(stof(pElement->Attribute("emiG")));
    }
    if(pElement->Attribute("emiB")){
        emission->setB(stof(pElement->Attribute("emiB")));
    }

    if(pElement->Attribute("specR")){
        specular->setR(stof(pElement->Attribute("specR")));
    }
    if(pElement->Attribute("specG")){
        specular->setG(stof(pElement->Attribute("specG")));
    }
    if(pElement->Attribute("specB")){
        specular->setB(stof(pElement->Attribute("specB")));
    }

    if(pElement->Attribute("shine")){
        shine = stof(pElement->Attribute("specB"));
    }

    Material* mat = new Material(diffuse, ambient, specular, emission, shine);

    model->setColourComponent(mat);
}

Model* Parser::Parse3d(XMLElement* pElement){
    Model* model;
    string s;
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

            if(pElement->Attribute("texture")){
                string textura = pElement->Attribute("texture");
                model = new Model(s, size, textura);
            }
            else{
                model = new Model(s, size);
            }

            int coord = 3;
            while (getline(infile, line) && (coord<size))
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

                model->addElementPoint(x);
                model->addElementPoint(y);
                model->addElementPoint(z);
                coord+=3;
            }

            coord=3;
            while (getline(infile, line) && (coord<size))
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
                model->addElementNormal(x);
                model->addElementNormal(y);
                model->addElementNormal(z);
                coord+=3;
            }

            coord=0;

            while (getline(infile, line) && (coord<size))
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

                model->addElementTexture(x);
                model->addElementTexture(y);
                model->addElementTexture(z);
                coord+=3;
            }
        }
    }

    return model;
}

void Parser::ParseRow(XMLNode* pRoot, Group* group){
    XMLNode * pNode = pRoot->FirstChild();
    if (pNode == nullptr){

        cout<< "no models" << endl;
        exit(0);

    }
    else{
        float speed = 0;
        for(;pNode; pNode=pNode->NextSibling()){

            XMLElement* pElement = pNode->ToElement();

            if(strcmp(pElement->Name(),"model") == 0){
                Model* model = Parse3d(pElement);

                ColourComp(model, pElement);

                group->addModel(model);

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
