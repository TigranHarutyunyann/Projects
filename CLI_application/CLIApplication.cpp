#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ----------------- Widget Base -----------------
class Widget {
protected:
    string m_type;
    int m_id, m_PID, m_row, m_col;
    vector<int> children;  // store children IDs
public:
    Widget(string t, int id, int PID, int row, int col)
        : m_type(t), m_id(id), m_PID(PID), m_row(row), m_col(col) {}

    virtual ~Widget() {}

    virtual void print(int indent = 0) const = 0;

    const vector<int>& getChildren() const { return children; }
    void addChild(int id) { children.push_back(id); }

    int getID() const { return m_id; }
    int getParentID() const { return m_PID; }

    string getType() const { return m_type; }

    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

    void setPosition(int row, int col) { m_row = row; m_col = col; }
};

// ----------------- Derived Widgets -----------------
class Window : public Widget {
private:
    int m_rowCount, m_colCount;
public:
    Window(int id, int rC, int cC, int PID = -1, int r = -1, int c = -1)
        : Widget("window", id, PID, r, c), m_rowCount(rC), m_colCount(cC) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Window id=" << m_id
             << ", rows=" << m_rowCount << ", cols=" << m_colCount;
        if(m_row != -1 && m_col != -1)
            cout << ", PID=" << m_PID << ", pos=(" << m_row << "," << m_col << ")";
        cout << endl;
    }

    int getRowCount() const { return m_rowCount; }
    int getColCount() const { return m_colCount; }
};

class Table : public Widget {
private:
    int m_rowCount, m_colCount;
public:
    Table(int id, int rC, int cC, int PID, int r, int c)
        : Widget("table", id, PID, r, c), m_rowCount(rC), m_colCount(cC) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Table id=" << m_id
             << ", size=" << m_rowCount << "x" << m_colCount
             << ", PID=" << m_PID << ", pos=(" << m_row << "," << m_col << ")"
             << endl;
    }
};

class Text : public Widget {
private:
    string m_text;
public:
    Text(int id, const string& text, int PID, int r, int c)
        : Widget("text", id, PID, r, c), m_text(text) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Text id=" << m_id
             << ", text=\"" << m_text << "\""
             << ", PID=" << m_PID << ", pos=(" << m_row << "," << m_col << ")"
             << endl;
    }
};

class Button : public Widget {
private:
    string m_btext;
public:
    Button(int id, const string& text, int PID, int r, int c)
        : Widget("button", id, PID, r, c), m_btext(text) {}

    void print(int indent = 0) const override {
        cout << string(indent, ' ') << "Button id=" << m_id
             << ", text=\"" << m_btext << "\""
             << ", PID=" << m_PID << ", pos=(" << m_row << "," << m_col << ")"
             << endl;
    }
};

// ----------------- ApplicationManager Singleton -----------------
class ApplicationManager {
private:
    static ApplicationManager* instance;
    unordered_map<int, Widget*> allObjects;

    ApplicationManager() {}

public:
    static ApplicationManager* getInstance() {
        if (!instance)
            instance = new ApplicationManager();
        return instance;
    }

    ~ApplicationManager() {
        for (auto &p : allObjects) delete p.second;
    }

    bool checkChild(int parentID, int row, int col) {
        if (!allObjects.count(parentID) || allObjects[parentID]->getType() != "window") {
            cerr << "Error: Parent ID is invalid or not a window.\n";
            return false;
        }
        Window* parent = dynamic_cast<Window*>(allObjects[parentID]);
        if (!parent) return false;

        if (row >= parent->getRowCount() || col >= parent->getColCount()) {
            cerr << "Error: Child position out of bounds.\n";
            return false;
        }

        for (int childID : allObjects[parentID]->getChildren()) {
            Widget* child = allObjects[childID];
            if (child->getRow() == row && child->getCol() == col) {
                cerr << "Error: Position already occupied.\n";
                return false;
            }
        }
        return true;
    }

    // Add Widgets
    void addWindow(int id, int rows, int cols, int parent=-1, int row=-1, int col=-1) {
        if (parent != -1 && !checkChild(parent, row, col)) return;

        Window* w = new Window(id, rows, cols, parent, row, col);
        allObjects[id] = w;
        if (parent != -1) allObjects[parent]->addChild(id);
    }

    void addTable(int id, int rows, int cols, int parent, int row, int col) {
        if (!checkChild(parent, row, col)) return;

        Table* t = new Table(id, rows, cols, parent, row, col);
        allObjects[id] = t;
        allObjects[parent]->addChild(id);
    }

    void addText(int id, const string& text, int parent, int row, int col) {
        if (!checkChild(parent, row, col)) return;
        
		Text* t = new Text(id, text, parent, row, col);
        allObjects[id] = t;
        allObjects[parent]->addChild(id);
    }

    void addButton(int id, const string& text, int parent, int row, int col) {
        if (!checkChild(parent, row, col)) return;
        
		Button* b = new Button(id, text, parent, row, col);
        allObjects[id] = b;
        allObjects[parent]->addChild(id);
    }

    void printAll(int rootId = -1, int indent = 0) {
        if (rootId == -1) {
            for (auto &p : allObjects) {
                if (p.second->getParentID() == -1)
                    printAll(p.first, indent);
            }
        } else {
            Widget* obj = allObjects[rootId];
            obj->print(indent);
            for (int childID : obj->getChildren())
                printAll(childID, indent + 4);
        }
    }
};

ApplicationManager* ApplicationManager::instance = nullptr;

// ----------------- Command Pattern -----------------
class ICommand {
public:
    virtual ~ICommand() {}
    virtual void execute(vector<string> args) = 0;
};

class WindowCommand : public ICommand {
public:
    void execute(vector<string> args) override {
        if (args.size() < 3) { 
			cerr << "Usage: add_window <id> <rowCount> <colCount> [parent row col]\n"; return; 
		}
        int id = stoi(args[0]),	rows = stoi(args[1]), cols = stoi(args[2]);
        int parent=-1, row=-1, col=-1;
		
        if (args.size() >= 6) { 
			parent=stoi(args[3]); 
			row=stoi(args[4]); 
			col=stoi(args[5]); 
		}
        ApplicationManager::getInstance()->addWindow(id, rows, cols, parent, row, col);
    }
};

class TableCommand : public ICommand {
public:
    void execute(vector<string> args) override {
        if (args.size() < 6) { 
			cerr << "Usage: add_table <id> <rows> <cols> <parent> <row> <col>\n"; return; 
		}
        ApplicationManager::getInstance()->addTable(
            stoi(args[0]), stoi(args[1]), stoi(args[2]),
            stoi(args[3]), stoi(args[4]), stoi(args[5])
        );
    }
};

class TextCommand : public ICommand {
public:
    void execute(vector<string> args) override {
        if (args.size() < 5) { cerr << "Usage: add_text <id> <text> <parent> <row> <col>\n"; return; }
        ApplicationManager::getInstance()->addText(
            stoi(args[0]), args[1], stoi(args[2]), stoi(args[3]), stoi(args[4])
        );
    }
};

class ButtonCommand : public ICommand {
public:
    void execute(vector<string> args) override {
        if (args.size() < 5) { cerr << "Usage: add_button <id> <text> <parent> <row> <col>\n"; return; }
        ApplicationManager::getInstance()->addButton(
            stoi(args[0]), args[1], stoi(args[2]), stoi(args[3]), stoi(args[4])
        );
    }
};

class PrintAllCommand : public ICommand {
public:
    void execute(vector<string> args) override {
        ApplicationManager::getInstance()->printAll();
    }
};

// ----------------- CommandManager -----------------
class CommandManager {
    unordered_map<string, ICommand*> commands;
public:
    CommandManager() {
        commands["add_window"] = new WindowCommand();
        commands["add_table"] = new TableCommand();
        commands["add_text"] = new TextCommand();
        commands["add_button"] = new ButtonCommand();
        commands["printAll"] = new PrintAllCommand();
    }

    ~CommandManager() {
        for (auto& c : commands) delete c.second;
    }

    void executeCommand(const string& cmd, vector<string> args) {
        if (commands.count(cmd)) commands[cmd]->execute(args);
        else cout << "Unknown command.\n";
    }
};

// ----------------- CLI -----------------
void instruction() {
    cout << "Welcome CLI Window Management Application\n"
         << "Commands:\n"
         << "add_window <id> <rows> <cols> [parent row col]\n"
         << "add_table <id> <rows> <cols> <parent> <row> <col>\n"
         << "add_text <id> <text> <parent> <row> <col>\n"
         << "add_button <id> <text> <parent> <row> <col>\n"
         << "printAll\n";
}

int main() {
    instruction();
    CommandManager manager;

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        vector<string> args;
        string arg;

        while (ss >> arg) args.push_back(arg);
        manager.executeCommand(cmd, args);
        if (cmd == "printAll") break;
    }

    return 0;
}

