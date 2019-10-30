#include "ObjReader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

ObjReader::ObjReader() {

}

ObjReader::~ObjReader() {

}

Mesh* ObjReader::ReadOBJ(string file) {
	Mesh *mesh;
	mesh = new Mesh();
	Group group;

	ifstream modelFile;
	modelFile.open(file);

	cout << "Carregando objeto..." << endl;

	bool groupDetected = false;

	while (!modelFile.eof()) {

		string line;
		stringstream sline;
		string temp;

		if (groupDetected == false) {
			getline(modelFile, line);
			sline << line;
			sline >> temp;
		}

		//mtllib
		if (temp == "mtllib") {
			string materialLib;
			sline >> materialLib;
			mesh->setMaterialLib(materialLib);
		}

		//V
		if (temp == "v") {
			float x, y, z;
			sline >> x >> y >> z;

			glm::vec3 vPosition(x, y, z);

			mesh->getVertices().push_back(vPosition);
		}

		//VT
		if (temp == "vt") {
			float x, y;
			sline >> x >> y;

			glm::vec2 vTextureCoord(x, y);
			Texture texture;
			texture.setPosition(vTextureCoord);

			mesh->getTextures().push_back(texture);
		}

		//VN
		if (temp == "vn") {
			float x, y, z;
			sline >> x >> y >> z;

			glm::vec3 normals(x, y, z);
			Normal normal;
			normal.setNormals(normals);

			mesh->getNormals().push_back(normal);
		}

		//---------------------------------------------------
		if (temp == "f" && !groupDetected) {

			groupDetected = true;
			Group group;
			group.setName("g default");
			cout << "Group name is: " << group.getName() << endl;

			bool groupReading = true;

			while (groupReading) {
				Face face;

				while (!sline.eof()) {
					string token;
					sline >> token; //v (type 1), v//n (type 2), v/t/n (type 3),  v/t (type 4)
					stringstream stoken;
					stoken << token;
					string aux;
					getline(stoken, aux, '/');

					int vertice, texture, normal;

					mesh->increaseVerticesCount();

					if (aux == token) {
						//Type 1
						vertice = stoi(aux) - 1;
						face.getVertices().push_back(vertice);
					}
					else {
						vertice = stoi(aux) - 1;
						getline(stoken, aux, '/');
						if (aux.empty()) {
							//Type 2
							face.getVertices().push_back(vertice);
							getline(stoken, aux, '/');
							normal = stoi(aux) - 1;
							face.getNormals().push_back(normal);
						}
						else {
							texture = stoi(aux) - 1;
							if (stoken.eof()) {
								//Type 4
								face.getVertices().push_back(vertice);
								face.getTextures().push_back(texture);
							}
							else {
								//Type 3
								getline(stoken, aux, '/');
								normal = stoi(aux) - 1;
								face.getVertices().push_back(vertice);
								face.getTextures().push_back(texture);
								face.getNormals().push_back(normal);
							}
						}
					}
				}
				group.getFaces().push_back(face);
				getline(modelFile, line);
				sline.clear();
				sline << line;
				sline >> temp;
				if (temp != "f" || modelFile.eof())
				{
					groupReading = false;
					groupDetected = false;
				}
			}

			mesh->getGroups().push_back(group);
		}

		//G
		if (temp == "g" || groupDetected == true) {

			groupDetected = false;

			Group group;
			group.setName(sline.str());
			cout << "Group name is: " << group.getName() << endl;
			getline(modelFile, line);
			stringstream newSline;
			newSline << line;
			newSline >> temp;

			if (temp == "usemtl") {
				string ID_material;

				newSline >> ID_material;
				group.setMaterialID(ID_material);
			}

			if (temp == "v") {
				float x, y, z;
				newSline >> x >> y >> z;

				glm::vec3 vPosition(x, y, z);

				mesh->getVertices().push_back(vPosition);
			}
			else {
				bool groupReading = true;

				while (groupReading) {

					getline(modelFile, line);
					stringstream slineFace;
					slineFace << line;
					slineFace >> temp;

					if (temp == "f" && !modelFile.eof()) {

						Face face;

						while (!slineFace.eof()) {
							string token;
							slineFace >> token; //v (type 1), v//n (type 2), v/t/n (type 3),  v/t (type 4)
							stringstream stoken;
							stoken << token;
							string aux;
							getline(stoken, aux, '/');

							int vertice, texture, normal;

							mesh->increaseVerticesCount();

							if (aux == token) {
								//Type 1
								vertice = stoi(aux) - 1;
								face.getVertices().push_back(vertice);
							}
							else {
								vertice = stoi(aux) - 1;
								getline(stoken, aux, '/');
								if (aux.empty()) {
									//Type 2
									face.getVertices().push_back(vertice);
									getline(stoken, aux, '/');
									normal = stoi(aux) - 1;
									face.getNormals().push_back(normal);
								}
								else {
									texture = stoi(aux) - 1;
									if (stoken.eof()) {
										//Type 4
										face.getVertices().push_back(vertice);
										face.getTextures().push_back(texture);
									}
									else {
										//Type 3
										getline(stoken, aux, '/');
										normal = stoi(aux) - 1;
										face.getVertices().push_back(vertice);
										face.getTextures().push_back(texture);
										face.getNormals().push_back(normal);
									}
								}
							}
						}
						group.getFaces().push_back(face);
					}
					else if (modelFile.eof() || temp == "g") {
						groupReading = false;
						groupDetected = true;
						sline << slineFace.str();
					}
				}
				mesh->getGroups().push_back(group);
			}
		}
	}

	modelFile.close();

	return mesh;
}

Material* ObjReader::ReadMTL(string materialLib) {

	Material *m;
	m = new Material();

	ifstream materialFile;
	materialFile.open(materialLib);

	cout << "Carregando material..." << endl;

	while (!materialFile.eof()) {

		string line;
		stringstream sline;
		string temp;

		getline(materialFile, line);
		sline << line;
		sline >> temp;

		if (temp == "newmtl") {

			string nameMaterial;
			sline >> nameMaterial;

			m->setNameMaterial(nameMaterial);

			cout << "nameMaterial: " << m->getNameMaterial() << endl;
		}

		if (temp == "Kd") {

			float x, y, z;
			sline >> x >> y >> z;

			glm::vec3 Kd(x, y, z);

			m->setKd(Kd);
			cout << "Kd: " << m->getKd().x << " " << m->getKd().y << " " << m->getKd().z <<  endl;


		}

		if (temp == "Ka") {
			
			float x, y, z;
			sline >> x >> y >> z;

			glm::vec3 Ka(x, y, z);

			m->setKa(Ka);
			cout << "Ka: " << m->getKa().x << " " << m->getKa().y << " " << m->getKa().z << endl;

		}

		if (temp == "Tf") {
			
			float x, y, z;
			sline >> x >> y >> z;

			glm::vec3 Tf(x, y, z);

			m->setTf(Tf);
			cout << "Tf: " << m->getTf().x << " " << m->getTf().y << " " << m->getTf().z << endl;
		}

		if (temp == "Ks") {

			float x, y, z;
			sline >> x >> y >> z;

			glm::vec3 Ks(x, y, z);

			m->setKs(Ks);
			cout << "Ks: " << m->getKs().x << " " << m->getKs().y << " " << m->getKs().z << endl;

		}

		if (temp == "Ns") {

			float Ns;
			sline >> Ns;

			m->setNs(Ns);
			cout << "Ns: " << m->getNs() << endl;
		}

		if (temp == "map_Kd") {

			string nameTexture;
			sline >> nameTexture;

			m->setNameTexture(nameTexture);
			cout << "nameTexture: " << m->getNameTexture() << endl;
		}

	}

	materialFile.close();

	return m;
}

vector<glm::vec3> ObjReader::ReadCurve(string file) {

	vector<glm::vec3> curvePoints;

	ifstream curveFile;
	curveFile.open(file);

	cout << "Carregando curva..." << endl;

	while (!curveFile.eof()) {
		
		string line;
		stringstream sline;

		getline(curveFile, line);
		sline << line;

		float x, y, z;

		sline >> x >> y >> z;

		glm::vec3 point(x, y, z);

		curvePoints.push_back(point);
	}

	curveFile.close();

	return curvePoints;
}