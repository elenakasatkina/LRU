#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <stdint.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

using namespace std;

class Page {
private:
	string name;
	int count;

public:
	Page(string name) {
		this->name = name;
		this->count = 0;
	}

	Page() {

	}

	string getName() {
		return name;
	}

	int getCount() {
		return count;
	}

	void setName(string name) {
		this->name = name;
	}

	void upCount() {
		this->count++;
	}
};


class ArrayList {
private:
	int N;
	Page *a;
	int size;

public:
	ArrayList(int size) {
		this->size = size;
		a = new Page[size];
	}

	void push(Page page) {
		if (N == size) {
			return;
		}
		a[N++] = page;
	}

	Page get(int index) {
		return a[index];
	}

	bool isEmpty() {
		return N == 0;
	}

	int len() {
		return size;
	}
};

static ArrayList *list = new ArrayList(10);
static Fl_Box **pagesNameBox;
static Fl_Box **pagesCountBox;
static Fl_Button **pagesUpCountBtn;

/*change labels of name and date Fl_Box*/
/*void update_pages() {
	for (int i = 0; i < list->len(); i++) {
		string pageName = list->get(i).getName();
		char *charArrayPageName = new char[pageName.size() + 1];
		charArrayPageName[pageName.size()] = 0;
		memcpy(charArrayPageName, pageName.c_str(), pageName.size());
		pagesNameBox[i]->label(charArrayPageName);

		long date = list->get(i).getDate();
		stringstream ss;
		ss << date;
		string pageDate = ss.str();
		char *charArrayPageDate = new char[pageDate.size() + 1];
		charArrayPageDate[pageDate.size()] = 0;
		memcpy(charArrayPageDate, pageDate.c_str(), pageDate.size());
		pagesDateBox[i]->label(charArrayPageDate);
	}
}


void on_press_use_page(Fl_Widget*, void *w) {
	int index = (intptr_t)w; //get page index
	list->update(index);

	update_pages();
}

void on_press_replace_page(Fl_Widget*, void *w) {
	Fl_Input *nameInput = (Fl_Input*)w; //get Fl_Input
	string name(nameInput->value()); //get name of Fl_Input
	Page page(name);
	list->push(page);

	update_pages();
}
void on_press_help(Fl_Widget*, void *w)
{
	Fl_Window *windowHelp = new Fl_Window(500, 500, "Help");
	Fl_Text_Display *displayHelp = new Fl_Text_Display(25, 25, 450, 450, "Help");
	Fl_Text_Buffer *helpBuff = new Fl_Text_Buffer();
	displayHelp->buffer(helpBuff);
	helpBuff->loadfile("help.txt");
	windowHelp->show();
}
void on_press_start(Fl_Widget*, void *w)
{
	Fl_Window *window = new Fl_Window(1000, 520, "LRU algorithm");
	Fl_Box *inputBox = new Fl_Box(100, 70, 200, 30, "Enter new page name");
	Fl_Input *nameInput = new Fl_Input(100, 100, 200, 30);
	Fl_Button *replaceBtn = new Fl_Button(150, 140, 100, 30, "Replace");
	replaceBtn->callback(on_press_replace_page, (void*)nameInput);

	for (int i = 0; i < list->len(); i++) {
		stringstream ss;
		ss << i + 1;
		list->push(Page(ss.str()));
	}

	Fl_Box *pageNameHeader = new Fl_Box(450, 60, 200, 50, "Page name");
	pageNameHeader->labelfont(FL_BOLD);
	Fl_Box *pageDateHeader = new Fl_Box(650, 60, 200, 50, "Page date (seconds)");
	pageDateHeader->labelfont(FL_BOLD);
	int y = 100;
	pagesNameBox = new Fl_Box*[list->len()];
	pagesDateBox = new Fl_Box*[list->len()];
	pagesUseBtn = new Fl_Button*[list->len()];
	for (int i = 0; i < list->len(); i++) {
		string name = list->get(i).getName();

		long date = list->get(i).getDate();
		stringstream ss;
		ss << date;
		string dateString = ss.str();

		*(pagesNameBox + i) = new Fl_Box(450, y, 200, 50, name.c_str());
		*(pagesDateBox + i) = new Fl_Box(650, y, 200, 50, dateString.c_str());
		*(pagesUseBtn + i) = new Fl_Button(850, y + 10, 100, 30, "Use now");
		pagesUseBtn[i]->callback(on_press_use_page, (void*)(intptr_t)i);
		y += 50;
	}

	update_pages();

	window->show();

	Fl::background(97, 140, 158);
}*/

void update() {
	for (int i = 0; i < list->len(); i++) {
		string name = list->get(i).getName();
		char *charArrayPageName = new char[name.size() + 1];
		charArrayPageName[name.size()] = 0;
		memcpy(charArrayPageName, name.c_str(), name.size());
		pagesNameBox[i]->label(charArrayPageName);

		int count = list->get(i).getCount();
		stringstream ss;
		ss << count;
		string pageCount = ss.str();
		cout << pageCount << "\n";
		char *charArrayPageCount = new char[pageCount.size() + 1];
		charArrayPageCount[pageCount.size()] = 0;
		memcpy(charArrayPageCount, pageCount.c_str(), pageCount.size());
		pagesCountBox[i]->label(charArrayPageCount);
	}
}

void on_press_up_count_page(Fl_Widget*, void *w) {
	int index = (intptr_t)w;

	list->get(index).upCount();

	update();
}

int main() {
	/*Fl_Window *windowStart = new Fl_Window(600, 300, "Start Page");
	Fl_Button *helpBtn = new Fl_Button(100, 140, 100, 30, "Help");
	Fl::background(152, 93, 162);
	helpBtn->callback(on_press_help);
	Fl_Button *startBtn = new Fl_Button(220, 140, 100, 30, "Start");
	startBtn->callback(on_press_start);
//	Fl_Box *imageBox = new Fl_Box(5, 5, 790, 640);
	
	windowStart->show();*/

	Fl_Window *main = new Fl_Window(1000, 500, "Main");
	//int workplace = 5;
	for (int i = 0; i < list->len(); i++) {
		stringstream ss;
		ss << i + 1;
		list->push(Page(ss.str()));
	}

	pagesNameBox = new Fl_Box*[list->len()];
	pagesCountBox = new Fl_Box*[list->len()];
	pagesUpCountBtn = new Fl_Button*[list->len()];

	Fl_Box *pageNameHeader = new Fl_Box(20, 100, 30, 50, "Name");
	pageNameHeader->labelfont(FL_BOLD);
	Fl_Box *pageCountHeader = new Fl_Box(20, 150, 30, 50, "Count");
	pageCountHeader->labelfont(FL_BOLD);

	int x = 100;

	for (int i = 0; i < list->len(); i++) {
		*(pagesNameBox + i) = new Fl_Box(x, 100, 10, 50, "");
		*(pagesCountBox + i) = new Fl_Box(x, 150, 10, 50, "");
		*(pagesUpCountBtn + i) = new Fl_Button(x, 50, 50, 50, "Up");
		pagesUpCountBtn[i]->callback(on_press_up_count_page, (void*)(intptr_t)i);
		x += 70;
	}

	update();

	main->show();
	return Fl::run();
}