#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Stu {
    int id;
    char name[100];
    char dept[4];
    int sem;
    float gpa;
    int cred;
    int yr;
    Stu* nxt;
};

Stu* first = nullptr;
int total = 0;

void load() {
    ifstream in("students_data.txt");
    if (!in) {
        cout << "Cant open\n";
        return;
    }
    
    in >> total;
    Stu* lastone = nullptr;
    
    for (int i = 0; i < total; i++) {
        Stu* n = new Stu;
        in >> n->id;
        in.ignore();
        in.getline(n->name, 100);
        in >> n->dept >> n->sem >> n->gpa >> n->cred >> n->yr;
        n->nxt = nullptr;
        
        if (!first) first = n;
        else lastone->nxt = n;
        lastone = n;
    }
    in.close();
}

void swapStu(Stu* a, Stu* b) {
    Stu t = *a;
    a->id = b->id;
    strcpy(a->name, b->name);
    strcpy(a->dept, b->dept);
    a->sem = b->sem;
    a->gpa = b->gpa;
    a->cred = b->cred;
    a->yr = b->yr;
    
    b->id = t.id;
    strcpy(b->name, t.name);
    strcpy(b->dept, t.dept);
    b->sem = t.sem;
    b->gpa = t.gpa;
    b->cred = t.cred;
    b->yr = t.yr;
}

void selectionSortCGPA() {
    Stu* curr = first;
    while (curr) {
        Stu* maxNode = curr;
        Stu* temp = curr->nxt;
        while (temp) {
            if (temp->gpa > maxNode->gpa || 
               (temp->gpa == maxNode->gpa && temp->cred > maxNode->cred)) {
                maxNode = temp;
            }
            temp = temp->nxt;
        }
        if (maxNode != curr) {
            swapStu(curr, maxNode);
        }
        curr = curr->nxt;
    }
}

void selectionSortYear() {
    Stu* curr = first;
    while (curr) {
        Stu* minNode = curr;
        Stu* temp = curr->nxt;
        while (temp) {
            if (temp->yr < minNode->yr || 
               (temp->yr == minNode->yr && temp->id < minNode->id)) {
                minNode = temp;
            }
            temp = temp->nxt;
        }
        if (minNode != curr) {
            swapStu(curr, minNode);
        }
        curr = curr->nxt;
    }
}

void selectionSortDept() {
    Stu* curr = first;
    while (curr) {
        Stu* best = curr;
        Stu* temp = curr->nxt;
        while (temp) {
            if (strcmp(temp->dept, best->dept) < 0 ||
               (strcmp(temp->dept, best->dept) == 0 && temp->sem < best->sem) ||
               (strcmp(temp->dept, best->dept) == 0 && temp->sem == best->sem && temp->gpa > best->gpa)) {
                best = temp;
            }
            temp = temp->nxt;
        }
        if (best != curr) {
            swapStu(curr, best);
        }
        curr = curr->nxt;
    }
}

void makeFile1() {
    Stu* copyHead = nullptr;
    Stu* copyLast = nullptr;
    Stu* orig = first;
    
    while (orig) {
        Stu* n = new Stu;
        *n = *orig;
        n->nxt = nullptr;
        
        if (!copyHead) copyHead = n;
        else copyLast->nxt = n;
        copyLast = n;
        orig = orig->nxt;
    }
    
    Stu* curr = copyHead;
    while (curr) {
        Stu* maxN = curr;
        Stu* temp = curr->nxt;
        while (temp) {
            if (temp->gpa > maxN->gpa || 
               (temp->gpa == maxN->gpa && temp->cred > maxN->cred)) {
                maxN = temp;
            }
            temp = temp->nxt;
        }
        if (maxN != curr) {
            swapStu(curr, maxN);
        }
        curr = curr->nxt;
    }
    
    ofstream out("ranked_by_cgpa.txt");
    
    out << "====================================================\n";
    out << "        STUDENTS RANKED BY CGPA\n";
    out << "====================================================\n";
    out << "Rank | ID     | Name              | Dept | Sem | CGPA | Credits | Year\n";
    out << "-----|--------|-------------------|------|-----|------|---------|------\n";
    
    int r = 1;
    curr = copyHead;
    while (curr) {
        out << setw(3) << r++ << "  | " << curr->id << " | "
            << left << setw(17) << curr->name << " | "
            << setw(4) << curr->dept << " | "
            << setw(3) << curr->sem << " | "
            << fixed << setprecision(2) << curr->gpa << " | "
            << setw(7) << curr->cred << " | "
            << curr->yr << endl;
        curr = curr->nxt;
    }
    
    Stu* t;
    while (copyHead) {
        t = copyHead;
        copyHead = copyHead->nxt;
        delete t;
    }
    out.close();
}

void makeFile2() {
    Stu* copyHead = nullptr;
    Stu* copyLast = nullptr;
    Stu* orig = first;
    
    while (orig) {
        Stu* n = new Stu;
        *n = *orig;
        n->nxt = nullptr;
        
        if (!copyHead) copyHead = n;
        else copyLast->nxt = n;
        copyLast = n;
        orig = orig->nxt;
    }
    
    Stu* curr = copyHead;
    while (curr) {
        Stu* minN = curr;
        Stu* temp = curr->nxt;
        while (temp) {
            if (temp->yr < minN->yr || 
               (temp->yr == minN->yr && temp->id < minN->id)) {
                minN = temp;
            }
            temp = temp->nxt;
        }
        if (minN != curr) {
            swapStu(curr, minN);
        }
        curr = curr->nxt;
    }
    
    ofstream out("sorted_by_enrollment.txt");
    out << "ENROLLMENT YEAR SORTING\n";
    out << "========================\n\n";
    
    int curYr = -1;
    float sum = 0;
    int cnt = 0;
    curr = copyHead;
    
    while (curr) {
        if (curr->yr != curYr) {
            if (curYr != -1) {
                out << "Avg CGPA for " << curYr << ": " 
                    << fixed << setprecision(2) << (sum/cnt) << "\n\n";
            }
            curYr = curr->yr;
            sum = 0;
            cnt = 0;
            out << "=== Year " << curYr << " ===\n";
        }
        
        out << curr->id << "  " << curr->name << "  "
            << curr->dept << "  " << curr->sem << "  "
            << fixed << setprecision(2) << curr->gpa << "  "
            << curr->cred << endl;
        
        sum += curr->gpa;
        cnt++;
        curr = curr->nxt;
    }
    
    if (cnt > 0) {
        out << "Avg CGPA for " << curYr << ": " 
            << fixed << setprecision(2) << (sum/cnt) << "\n";
    }
    
    Stu* temp;
    while (copyHead) {
        temp = copyHead;
        copyHead = copyHead->nxt;
        delete temp;
    }
    out.close();
}

void makeFile3() {
    Stu* copyHead = nullptr;
    Stu* copyLast = nullptr;
    Stu* orig = first;
    
    while (orig) {
        Stu* n = new Stu;
        *n = *orig;
        n->nxt = nullptr;
        
        if (!copyHead) copyHead = n;
        else copyLast->nxt = n;
        copyLast = n;
        orig = orig->nxt;
    }
    
    Stu* curr = copyHead;
    while (curr) {
        Stu* best = curr;
        Stu* temp = curr->nxt;
        while (temp) {
            if (strcmp(temp->dept, best->dept) < 0 ||
               (strcmp(temp->dept, best->dept) == 0 && temp->sem < best->sem) ||
               (strcmp(temp->dept, best->dept) == 0 && temp->sem == best->sem && temp->gpa > best->gpa)) {
                best = temp;
            }
            temp = temp->nxt;
        }
        if (best != curr) {
            swapStu(curr, best);
        }
        curr = curr->nxt;
    }
    
    ofstream out("department_analysis.txt");
    out << "DEPARTMENT ANALYSIS\n";
    out << "===================\n\n";
    
    char curDep[4] = "";
    float sumGpa = 0;
    int depCnt = 0;
    float sumCred = 0;
    float maxG = -1;
    float minG = 5;
    curr = copyHead;
    
    while (curr) {
        if (strcmp(curr->dept, curDep) != 0) {
            if (depCnt > 0) {
                out << "--- Statistics ---\n";
                out << "Total Students: " << depCnt << "\n";
                out << "Average CGPA: " << fixed << setprecision(2) << (sumGpa/depCnt) << "\n";
                out << "Highest CGPA: " << fixed << setprecision(2) << maxG << "\n";
                out << "Lowest CGPA: " << fixed << setprecision(2) << minG << "\n";
                out << "Avg Credits: " << fixed << setprecision(1) << (sumCred/depCnt) << "\n\n";
            }
            strcpy(curDep, curr->dept);
            sumGpa = 0;
            sumCred = 0;
            depCnt = 0;
            maxG = -1;
            minG = 5;
            out << "=== Department: " << curDep << " ===\n";
        }
        
        out << curr->id << "  " << curr->name << "  Sem" << curr->sem 
            << "  GPA:" << fixed << setprecision(2) << curr->gpa 
            << "  Credits:" << curr->cred << "  Year:" << curr->yr << endl;
        
        sumGpa += curr->gpa;
        sumCred += curr->cred;
        depCnt++;
        if (curr->gpa > maxG) maxG = curr->gpa;
        if (curr->gpa < minG) minG = curr->gpa;
        
        curr = curr->nxt;
    }
    
    if (depCnt > 0) {
        out << "--- Statistics ---\n";
        out << "Total Students: " << depCnt << "\n";
        out << "Average CGPA: " << fixed << setprecision(2) << (sumGpa/depCnt) << "\n";
        out << "Highest CGPA: " << fixed << setprecision(2) << maxG << "\n";
        out << "Lowest CGPA: " << fixed << setprecision(2) << minG << "\n";
        out << "Avg Credits: " << fixed << setprecision(1) << (sumCred/depCnt) << "\n";
    }
    
    Stu* temp;
    while (copyHead) {
        temp = copyHead;
        copyHead = copyHead->nxt;
        delete temp;
    }
    out.close();
}

void insertNameSort(Stu** h, Stu* n) {
    if (!*h || strcmp(n->name, (*h)->name) < 0) {
        n->nxt = *h;
        *h = n;
    } else {
        Stu* cur = *h;
        while (cur->nxt && strcmp(n->name, cur->nxt->name) > 0) {
            cur = cur->nxt;
        }
        n->nxt = cur->nxt;
        cur->nxt = n;
    }
}

void makeFile4() {
    Stu* elite = nullptr;
    Stu* high = nullptr;
    Stu* good = nullptr;
    Stu* sat = nullptr;
    Stu* need = nullptr;
    
    int e = 0, h = 0, g = 0, s = 0, n = 0;
    
    Stu* curr = first;
    while (curr) {
        Stu* newNode = new Stu;
        *newNode = *curr;
        newNode->nxt = nullptr;
        
        if (curr->gpa >= 3.70) {
            insertNameSort(&elite, newNode);
            e++;
        } else if (curr->gpa >= 3.30) {
            insertNameSort(&high, newNode);
            h++;
        } else if (curr->gpa >= 3.00) {
            insertNameSort(&good, newNode);
            g++;
        } else if (curr->gpa >= 2.50) {
            insertNameSort(&sat, newNode);
            s++;
        } else {
            insertNameSort(&need, newNode);
            n++;
        }
        curr = curr->nxt;
    }
    
    ofstream out("performance_tiers.txt");
    out << "PERFORMANCE TIERS\n";
    out << "=================\n\n";
    
    out << "*** ELITE TIER (CGPA >= 3.70) ***\n";
    out << "Count: " << e << " (" 
        << fixed << setprecision(1) << (e*100.0/total) << "%)\n";
    curr = elite;
    while (curr) {
        out << curr->name << " [" << curr->id << "] " << curr->dept 
            << " Sem" << curr->sem << " GPA:" << fixed << setprecision(2) << curr->gpa << endl;
        curr = curr->nxt;
    }
    out << endl;
    
    out << "*** HIGH ACHIEVERS (3.30 <= CGPA < 3.70) ***\n";
    out << "Count: " << h << " (" 
        << fixed << setprecision(1) << (h*100.0/total) << "%)\n";
    curr = high;
    while (curr) {
        out << curr->name << " [" << curr->id << "] " << curr->dept 
            << " Sem" << curr->sem << " GPA:" << fixed << setprecision(2) << curr->gpa << endl;
        curr = curr->nxt;
    }
    out << endl;
    
    out << "*** GOOD STANDING (3.00 <= CGPA < 3.30) ***\n";
    out << "Count: " << g << " (" 
        << fixed << setprecision(1) << (g*100.0/total) << "%)\n";
    curr = good;
    while (curr) {
        out << curr->name << " [" << curr->id << "] " << curr->dept 
            << " Sem" << curr->sem << " GPA:" << fixed << setprecision(2) << curr->gpa << endl;
        curr = curr->nxt;
    }
    out << endl;
    
    out << "*** SATISFACTORY (2.50 <= CGPA < 3.00) ***\n";
    out << "Count: " << s << " (" 
        << fixed << setprecision(1) << (s*100.0/total) << "%)\n";
    curr = sat;
    while (curr) {
        out << curr->name << " [" << curr->id << "] " << curr->dept 
            << " Sem" << curr->sem << " GPA:" << fixed << setprecision(2) << curr->gpa << endl;
        curr = curr->nxt;
    }
    out << endl;
    
    out << "*** NEEDS IMPROVEMENT (CGPA < 2.50) ***\n";
    out << "Count: " << n << " (" 
        << fixed << setprecision(1) << (n*100.0/total) << "%)\n";
    curr = need;
    while (curr) {
        out << curr->name << " [" << curr->id << "] " << curr->dept 
            << " Sem" << curr->sem << " GPA:" << fixed << setprecision(2) << curr->gpa << endl;
        curr = curr->nxt;
    }
    
    Stu* temp;
    while (elite) {
        temp = elite;
        elite = elite->nxt;
        delete temp;
    }
    while (high) {
        temp = high;
        high = high->nxt;
        delete temp;
    }
    while (good) {
        temp = good;
        good = good->nxt;
        delete temp;
    }
    while (sat) {
        temp = sat;
        sat = sat->nxt;
        delete temp;
    }
    while (need) {
        temp = need;
        need = need->nxt;
        delete temp;
    }
    
    out.close();
}

void freeAll() {
    Stu* curr = first;
    while (curr) {
        Stu* t = curr;
        curr = curr->nxt;
        delete t;
    }
    first = nullptr;
}

int main() {
    load();
    if (total == 0) {
        cout << "No data\n";
        return 1;
    }
    
    makeFile1();
    makeFile2();
    makeFile3();
    makeFile4();
    
    freeAll();
    
    cout << "Files done\n";
    return 0;
}