#include "headers/generator.h"

/**
 * @brief Shows the usage of this file.
 */
void usage(){
    cout << "#_____________________________ HELP _____________________________#" << endl;
	cout << "|                                                                |" << endl;
    cout << "|   SYNOPSIS                                                     |" << endl;
    cout << "|          ./generator {COMMAND} ... {OUTPUT FILE}               |" << endl;
	cout << "|                      [-h]                                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   COMMANDS:                                                    |" << endl;
	cout << "| - plane [SIZE]                                                 |" << endl;
	cout << "|      Creates a square in the XZ plane, centred in the origin.  |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - box [SIZE X] [SIZE Y] [SIZE Z] [DIVISIONS]                   |" << endl;
	cout << "|      Creates a box with the dimensions and divisions specified.|" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - sphere [RADIUS] [SLICE] [STACK]                              |" << endl;
	cout << "|      Creates a sphere with the radius, number of slices and    |" << endl;
	cout << "|      stacks given.                                             |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - cone [RADIUS] [HEIGHT] [SLICE] [STACK]                       |" << endl;
	cout << "|      Creates a cone with the radius, height, number of slices  |" << endl;
	cout << "|      and stacks given.                                         |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - cylinder [RADIUS] [HEIGHT] [SLICE] [STACK]                   |" << endl;
	cout << "|      Creates a cylinder with the radius, height, number of     |" << endl;
	cout << "|      slices and stacks given.                                  |" << endl;
	cout << "|                                                                |" << endl;
	cout << "| - patch [INPUT FILE] [TESSELLATION]                            |" << endl;
	cout << "|      Creates a new model using the given input file with the   |" << endl;
	cout << "|      tesselation specified, based on Bezier patches.           |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   OUTPUT FILE:                                                 |" << endl;
	cout << "| In the file section you can specify any file in which you wish |" << endl;
	cout << "| to save the coordinates generated with the previous commands.  |" << endl;
	cout << "|                                                                |" << endl;
    cout << "| The file should be in the 'files' directory.                   |" << endl;
	cout << "| If the file doesn't exist it will be created. If it does it    |" << endl;
	cout << "| will be truncated.                                             |" << endl;
	cout << "|                                                                |" << endl;
    cout << "#________________________________________________________________#" << endl;

}

/**
 * @brief Makes the .3d and .xml files
 * @param filename Filename for .3d file
 * @param points   List of points
 */
void printfile(string filename, vector<Point*> points) {
    ofstream file;
    string fileDir = "files/" + filename;
    file.open(fileDir, ios_base::trunc);
    if (!file.is_open()) {
        cout << "Error while opening file " << filename << endl;
    } else {
        for (vector<Point*>::iterator i = points.begin(); i!= points.end(); i++)
            file << (*i)->toString();

        file.close();
    }
}

int main(int argc, char* argv[]) {
    string filename;
    Figure* f = new Figure();

    if ((argc == 4) && strcmp(argv[1],"plane") == 0){
        double size = atof(argv[2]);
        if (size<=0) {
            cout << "Size must be positive." << endl;
            return 1;
        }
        filename = argv[3];

        f->createPlane(size);
    }

    else if ((argc == 6 || argc == 7) && (strcmp(argv[1],"box") == 0)){
        double x = atof(argv[2]);
        double y = atof(argv[3]);
        double z = atof(argv[4]);
        int d = (argc == 7) ? stoi(argv[5]) : 1;
        filename = (argc == 7) ? argv[6] : argv[5];

        f->createBox(x, y, z, d);
    }

    else if (argc == 6 && (strcmp(argv[1],"sphere") == 0)){
        double radius = atof(argv[2]);
        int slices = (int) stoi(argv[3]);
        int stacks = (int) stoi(argv[4]);
        filename = argv[5];

        f->createSphere(radius, slices, stacks);
    }

    else if (argc == 7 && (strcmp(argv[1],"cone") == 0)){
        double radius = atof(argv[2]);
        double height = atof(argv[3]);
        int slices = (int) stoi(argv[4]);
        int stacks = (int) stoi(argv[5]);
        filename = argv[6];

        f->createCone(radius, height, slices, stacks);
    }

    else if (argc == 7 && (strcmp(argv[1],"cylinder") == 0)){
        double radius = atof(argv[2]);
        double height = atof(argv[3]);
        int slices = (int) stoi(argv[4]);
        int stacks = (int) stoi(argv[5]);
        filename = argv[6];

        f->createCylinder(radius, height, slices, stacks);
    }

    else if ((argc == 5) && strcmp(argv[1],"patch") == 0){
        int tesselation = atoi(argv[3]);
        if (tesselation <=0) {
            cout << "Tesselation must be positive." << endl;
            return 1;
        }
        PatchParser *p = new PatchParser(argv[4],argv[2], tesselation);
        p->parsePatch();
        return 0;
    }

    else {
        usage();
        return 0;
    }

    printfile(filename, f->getPoints());
    return 0;
}
