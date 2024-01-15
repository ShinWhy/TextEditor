#ifndef TextEditor_H
#define TextEditor_H
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Editor.H> //莫名其妙报错
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <stdio.h>
#include <cstdlib>
static void build_Menu(Fl_Menu_Bar* menu, Fl_Window* window);
void changed_cb(int, int nInserted, int nDeleted, int, const char*, void* v);
void copy_cb(Fl_Widget *, void* v);
void cut_cb(Fl_Widget *, void* v);
void delete_cb(Fl_Widget *, void* v);
void find_cb(Fl_Widget* w, void* v);
void find2_cb(Fl_Widget* w, void* v);
void new_cb(Fl_Widget*, void*);
void open_cb(Fl_Widget*, void*);
void undo_cb(void);
void paste_cb(Fl_Widget*, void* v);
void quit_cb(Fl_Widget*, void*);
void replace_cb(Fl_Widget*, void* v);
void replace2_cb(Fl_Widget*, void* v);
void replacall_cb(Fl_Widget* , void* v);
void replcan_cb(Fl_Widget*, void* v);
void save_cb(void);
void saveas_cb(void);
int check_save(void);
void load_file(char *newfile, int ipos);
void save_file(char *newfile);
void set_title(Fl_Window* w);
Fl_Window* new_view();

int loading = 0;    


#endif