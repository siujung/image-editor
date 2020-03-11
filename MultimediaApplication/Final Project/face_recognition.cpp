#include "face_recognition.h"
#include "cvui.h"

using namespace std;
using namespace cv;
using namespace face;

vector<Rect> recognize_face(Mat& img, CascadeClassifier& cascade, double scale)
{
	vector<Rect> faces, faces2;
	vector<Mat> images;
	vector<int> labels;
	Mat gray, smallImg;

	//cvtColor(img, gray, COLOR_BGR2GRAY);
	gray = img.clone(); //alternative by not converting to grey
	double fx = 1 / scale;
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);
	//equalizeHist(smallImg, smallImg);

	cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0| CASCADE_SCALE_IMAGE, Size(30, 30));

	return faces;
}

void init_face(Ptr<FaceRecognizer>& model) {
	bool fileExist = false;
	ifstream ifs("face.xml");
	if (ifs.is_open()) {
		fileExist = true;
	}
	ifs.close();

	if (fileExist) {//if there is already a face.xml file that contains remembered faces
		model = Algorithm::load<LBPHFaceRecognizer>("face.xml"); //load that file
		if (model->empty()) {
			model = LBPHFaceRecognizer::create();
		}
	}
	else { //if there aren't any previous face.xml files
		model = LBPHFaceRecognizer::create();//create one
	}
	//set threshold
	//the higher the threshold, the better at prediction
	model->setThreshold(50.0);
}

void save_and_predict_face(Ptr<FaceRecognizer>& model, vector<Rect> faces, Mat& frame, double scale) {
	for (size_t i = 0; i < faces.size(); i++) //for all faces
	{
		Rect r = faces[i];
		bool save = false;

		//get the rectangle of the face
		Rect found_face(Point(cvRound(r.x*scale), cvRound(r.y*scale)), Point(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)));

		//convert to gray to train the FaceRecognizer
		Mat gray;
		cvtColor(Mat(frame, found_face), gray, COLOR_BGR2GRAY);

		//if the user clicked on the face
		if (cvui::mouse(cvui::LEFT_BUTTON, cvui::DOWN)) {
			Point mouse_point(cvui::mouse().x, cvui::mouse().y);
			if (mouse_point.inside(found_face))
			{
				save = true;
			}
			if (save) {
				//save the face
				save_face(model, gray);
			}
		}

		predict_face(model, gray, frame, found_face);		
	}
}

void save_face(Ptr<FaceRecognizer>& model, Mat gray) {
	int i;
	string face_name;
	//get the name of the face as input
	cout << "Input name of face:" << endl;
	getline(cin, face_name);

	vector<Mat> images;
	vector<int> labels;
	int face_label;
	bool found_match = false;
	//if there are already saved faces
	if (!model->empty()) {
		vector<int> match = model->getLabelsByString(face_name);
		//if there are more than 1 matching strings including the name as substring
		if (match.size() >= 1) {
			for (size_t j = 0; j < match.size(); j++) {
				int match_label = match[j];
				String match_name = model->getLabelInfo(match_label);
				//search for the exact same name and set face_label
				if (match_name == face_name) {
					face_label = match_label;
					found_match = true;
					break;
				}
			}
		}
		//if there are no matches give the face an empty label
		if (!found_match) {
			for (i = 0; !model->getLabelInfo(i).empty(); i++);
			face_label = i;
		}
	}
	//else if model is empty this is the first face to remember so predicted = 0
	else {
		face_label = 0;
	}
	labels.push_back(face_label);
	images.push_back(gray);
	//train the face recognizer
	model->update(images, labels);
	model->setLabelInfo(face_label, face_name);
	model->save("face.xml");
}

void predict_face(Ptr<FaceRecognizer>& model, Mat gray, Mat& frame, Rect found_face) {
	int predicted;
	Scalar face_color(255, 0, 0); //blue
	Point nametag;

	nametag = Point(found_face.x + (found_face.width / 2), found_face.y + found_face.height);

	if (!model->empty()) {
		//if the face is predicted
		predicted = model->predict(gray);
		if (predicted != -1) {
			//show its name
			String label_info = model->getLabelInfo(predicted);
			cvui::printf(frame, (int)nametag.x, (int)nametag.y + 10, 0.7, 0x0000ff, "%s", label_info.c_str());
		}
	}
	//draw circle or rectangle around the face
	rectangle(frame, found_face, face_color, 3, 8, 0);
}