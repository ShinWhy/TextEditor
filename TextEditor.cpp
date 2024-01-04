#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Editor.H> //莫名其妙报错
#include <FL/Fl_Menu_Item.H>
#include <stdio.h>

class EditorWindow: public Fl_Double_Window {
    public:
        EditorWindow(int w, int h, const char *t);//构造函数，该函数接受三个参数，t参数是窗口的标题
        ~EditorWindow();

        //Fl_Double_Window和Fl_Text_Editor是FLTK库中的类，用于创建窗口和文本编辑器控件。
        //Fl_Input、Fl_Button和Fl_Return_Button也是FLTK库中的类，分别用于创建输入框、普通按钮和默认按钮。
        Fl_Window *replace_dlg; 
        Fl_Input *replace_find;
        Fl_Input *replace_with;
        Fl_Button *replace_all;
        //The Fl_Return_Button is a subclass of Fl_Button that generates a callback when it is pressed or when the user presses the Enter key.
        Fl_Return_Button *replace_next;
        Fl_Button *replace_cancel;

        Fl_Text_Editor *editor;
        char search[256];  
};

//some global variables
int changed =0; //记录文件是否被修改过
char filename[256] = "";//记录当前打开的文件名
Fl_Text_Buffer *textbuf;//记录当前打开的文件内容

/**Menubars and Menus**/
Fl_Menu_Item menuitems[] = {
    /*FL_SUBMENU表示该菜单项是一个子菜单，快捷键，回调函数的ID，用于控制菜单项的行为*/
    {"&File",               0, 0, 0, FL_SUBMENU},
        {"&New File",       0, (Fl_Callback *)new_cb },
        {"&Open File...",   FL_CTRL + 'o', (Fl_Callback *)open_cb },
        {"&Insert File...", FL_CTRL + 'i', (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER }, //分割线
        {"&Save File",      FL_CTRL + 's', (Fl_Callback *)save_cb},
        {"Save File &As...",FL_CTRL + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER},
        {"New &View",       FL_ALT + 'v', (Fl_Callback *)view_cb, 0},//在FLTK库中，使用“&”符号可以将紧随其后的字母作为菜单项的快捷键。
        {"&Close View",     FL_CTRL + 'w', (Fl_Callback *)close_cb, 0, FL_MENU_DIVIDER},
        {"E&xit",           FL_CTRL + 'q', (Fl_Callback *)quit_cb, 0},
        {0},//结束标志
    {"&Edit",               0, 0, 0, FL_SUBMENU},
        {"&Undo",           FL_CTRL + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER},
        {"Cu&t",            FL_CTRL + 'x', (Fl_Callback *)cut_cb },
        {"&Copy",           FL_CTRL + 'c', (Fl_Callback *)copy_cb },
        {"&Paste",          FL_CTRL + 'v', (Fl_Callback *)paste_cb },
        {"&Delete",         0, (Fl_Callback *)delete_cb},
        {0},
    {"&Search",             0, 0, 0, FL_SUBMENU},
        {"&Find...",        FL_CTRL + 'f', (Fl_Callback *)find_cb },
        {"F&ind Again",     FL_CTRL + 'g', find2_cb},
        {"&Replace...",     FL_CTRL + 'r', replace_cb },
        {"&Re&place Again", FL_CTRL + 't', replace2_cb },
        {0},
    {0}

};
Fl_Menu_Bar *m = new Fl_Menu_bar(0, 0, 640, 30);
m->copy(menuitems);


/**Editing the Text**/
w->editor = new Fl_Text_Editor(0, 30, 640, 370);
w->editor->buffer(textbuf);
// keep track of changes to the file, we also want to add a "modify" callback
textbuf->add_modify_callback(changed_cb, w);
textbuf->call_modify_callbacks();

/**The Replace Dialog**/
Fl_Window *replace_dlg = new Fl_Window(300, 105, "Replace");
Fl_Input *replace_find = new Fl_Input(70, 10, 200, 25, "Find:");
Fl_Input *replace_with = new Fl_Input(70, 40, 200, 25, "Replace:");
Fl_Button *replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
Fl_Button *replace_next = new Fl_Button(105, 70, 90, 25, "Replace Next");
Fl_Button *replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");

/**Callbacks**/
void changed_cb(int, int nInserted, int nDeleted, int, const char*, void* v) {
    if((nInserted || nDeleted) && !loading) changed = 1;
    EditorWindow *w = (EditorWindow*)v;
    set_titile(w);
    if(loading) w->editor->show_insert_position();
}

void copy_cb(Fl_Widget *, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    Fl_Text_Editor::kf_copy(0, e->editor);
    //0:int, which is the index of the selected text, 0 means the entire selected text will be copied to the clipboard
    //the third and fourth arguments are set to 0, which means that the entire selected text will be copied.
}

void cut_cb(Fl_Widget *, void* v) {
    EditorWindow* e = (EditorWindow*)v;
    Fl_Text_Editor::kf_cut(0, e->editor);
    //0:int, which is the index of the selected text, 0 means the entire selected text will be copied to the clipboard
    //the third and fourth arguments are set to 0, which means that the entire selected text will be cut.
}

//删除选中文字
void delete_cb(Fl_Widget *, void* v) {
    textbuf->remove_selection();
}

