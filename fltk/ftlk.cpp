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

using namespace std;

class Page {
private:
	string name;
	long date;

public:
	Page(string name) {
		this->name = name;
		setDate();
	}

	Page() {

	}

	string getName() {
		return name;
	}

	long getDate() {
		return date;
	}

	void setName(string name) {
		this->name = name;
	}

	void setDate() {
		this->date = time(0);
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
			replace(page);
			return;
		}
		a[N++] = page;
	}

	Page get(int index) {
		return a[index];
	}

	void replace(Page page) {
		long min = a[0].getDate();
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (a[i].getDate() < min) {
				min = a[i].getDate();
				index = i;
			}
		}
		a[index] = page;
	}

	bool isEmpty() {
		return N == 0;
	}

	int len() {
		return size;
	}

	void update(int index) {
		if (N < index || index >= size) {
			return;
		}
		a[index].setDate();
	}
};

static ArrayList *list = new ArrayList(5);
static Fl_Box **pagesNameBox;
static Fl_Box **pagesDateBox;
static Fl_Button **pagesUseBtn;

/*change labels of name and date Fl_Box*/
void update_pages() {
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

int main() {
	Fl_Window *window = new Fl_Window(1280, 720, "LRU algorithm");
	/* draw input area */
	Fl_Box *inputBox = new Fl_Box(100, 70, 200, 30, "Enter new page name");
	Fl_Input *nameInput = new Fl_Input(100, 100, 200, 30);
	Fl_Button *replaceBtn = new Fl_Button(150, 140, 100, 30, "Replace");
	replaceBtn->callback(on_press_replace_page, (void*)nameInput);


	/*define default pages names*/
	for (int i = 0; i < list->len(); i++) {
		stringstream ss;
		ss << i + 1;
		list->push(Page(ss.str()));
	}

	/*draw pages*/
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

	Fl::background(251, 134, 50);

	return Fl::run();
}