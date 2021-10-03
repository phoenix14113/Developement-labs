/*
 *  CPTR 245 Lab 07
 *
 *  1. Use dependency injection to provide a StubbedSource for canned responses
 *  2. Avoid the user interface by getting the user type from the command line
 *  3. Use a mock test double for the application analysis
 *  4. Use fake time
 */

#include <algorithm> // std::sort
#include <cassert>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <thread> // std::this_thread::sleep_for
#include <vector>

using namespace std;
using namespace std::chrono;

class Clock {
public:
  virtual uint64_t msSinceEpoch() = 0;
  virtual void sleepMs(int ms) = 0;
};
class FakeClock : public Clock {
public:
  uint64_t msSinceEpoch() { return fakeTime; }
  void sleepMs(int ms) { fakeTime += ms; }

private:
  uint64_t fakeTime = 0;
};
class SystemClock : public Clock {
public:
  uint64_t msSinceEpoch() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
  }
  void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }
};

class DataSource {
public:
  virtual vector<string> names(int userType) = 0;
};
class StubbedSource : public DataSource {
public:
  vector<string> names(int userType);
};
vector<string> StubbedSource::names(int userType) {
  vector<string> names{"Taylor, Adam", "Foster, James", "Sukachevin, Kieran"};
  return names;
}
class FileSource : public DataSource {
public:
  vector<string> names(int userType);
};

vector<string> FileSource::names(int userType) {
  string filename;
  vector<string> names;
  switch (userType) {
  case 1:
    filename = "students.txt";
    break;
  case 2:
    filename = "faculty.txt";
    break;
  default:
    cerr << "Invalid userType: " << userType << endl;
    exit(1);
  }
  ifstream inFS;
  inFS.open(filename);
  if (!inFS.is_open()) {
    cerr << "Could not open \"" << filename << '\"' << endl;
    exit(1);
  }
  while (!inFS.eof()) {
    string name;
    getline(inFS, name);
    if (name.size()) {
      names.push_back(name);
    }
  }
  inFS.close();
  return names;
}

class AnalysisTool {
public:
  bool printThird = false;
  virtual vector<string> filterNames(vector<string> names) = 0;
  virtual vector<string> sortNames(vector<string> names) = 0;
  virtual void printNames(vector<string> names) = 0;
};
class MockAnalysisTool : public AnalysisTool {
public:
  vector<string> filterNames(vector<string> names);
  vector<string> sortNames(vector<string> names);
  void printNames(vector<string> names);
private:
  bool filterFirst = false;
  bool sortSecond = false;
};
vector<string> MockAnalysisTool::filterNames(vector<string> names) {
  assert(!filterFirst && !sortSecond && !printThird);
  filterFirst = true;
  return names;
}
vector<string> MockAnalysisTool::sortNames(vector<string> names) {
  assert(filterFirst && !sortSecond && !printThird);
  sortSecond = true;
  return names;
}
void MockAnalysisTool::printNames(vector<string> names) {
  assert(filterFirst && sortSecond && !printThird);
  printThird = true;
}
class RealAnalysisTool : public AnalysisTool {
public:
  vector<string> filterNames(vector<string> names);
  vector<string> sortNames(vector<string> names);
  void printNames(vector<string> names);
};

vector<string> RealAnalysisTool::filterNames(vector<string> names) {
  vector<string> result;
  for (int i = 0; i < names.size(); ++i) {
    if (names.at(i).at(0) % 2) {
      result.push_back(names.at(i));
    }
  }
  return result;
}

vector<string> RealAnalysisTool::sortNames(vector<string> names) {
  vector<string> result = names;
  sort(result.begin(), result.end());
  return result;
}

void RealAnalysisTool::printNames(vector<string> names) {
  for (int i = 0; i < names.size(); ++i) {
    cout << i << ": " << names.at(i) << endl;
  }
}

class Application {
public:
  Application(DataSource *dataSource) { this->dataSource = dataSource; }
  int getUserInput();
  vector<string> getNames(int userType);

private:
  DataSource *dataSource;
};

int Application::getUserInput() {
  while (true) {
    int choice;
    cout << "Enter user type (1 = student; 2 = faculty): ";
    cin >> choice;
    if (cin && 1 <= choice && choice <= 2) {
      return choice;
    }
    cerr << "Invalid response!" << endl;
    cin.clear();
    cin.ignore(100, '\n');
  }
}

vector<string> Application::getNames(int userType) {
  return dataSource->names(userType);
}

/*
 * Arguments (all optional):
 *   1: DataSource subclass name (defaults to FileSource)
 *   2: user type (defaults to asking user)
 *   3: AnalysisTool subclass name (defaults to RealAnalysisTool)
 *   4: Clock subclass name (defaults to SystemClock)
 *
 */
int main(int argc, char *argv[]) {
  // collect the arguments
  vector<string> args(10);
  for (int i = 0; i < argc; ++i) {
    args.at(i) = argv[i];
  }

  // select the data source
  DataSource *dataSource;
  if (args.at(1) == "" || args.at(1) == "FileSource") {
    dataSource = new FileSource();
  } else if (args.at(1) == "StubbedSource") {
    dataSource = new StubbedSource();
  } else {
    cerr << "unrecognized data source" << endl;
    exit(1);
  }
  // Use dependency injection for the data source
  Application app(dataSource);

  // Get the user type (avoid the user interface during testing)
  int userType;
  if (args.at(2) == "1" || args.at(2) == "2") {
    userType = stoi(args.at(2));
  } else {
    userType = app.getUserInput();
  }

  // read from the data source
  vector<string> names = app.getNames(userType);

  // do analysis of the names (use a mock for testing)
  AnalysisTool *tool;
  if (args.at(3) == "MockAnalysisTool") {
    tool = new MockAnalysisTool();
  } else {
    tool = new RealAnalysisTool();
  }
  names = tool->filterNames(names);
  names = tool->sortNames(names);
  tool->printNames(names);
  if (args.at(3) == "MockAnalysisTool") {
      assert(tool->printThird);
  }
  // do long-running process (faking time for testing)
  Clock *clock;
  if (args.at(4) == "FakeClock") {
    clock = new FakeClock();
  } else {
    clock = new SystemClock();
  }
  uint64_t start = clock->msSinceEpoch();
  cout << "start long-running process at " << start << endl;

  while (clock->msSinceEpoch() < start + 2000) {
    clock->sleepMs(10);
  }
  cout << "  end long-running process at " << clock->msSinceEpoch() << endl;
  return 0;
}
