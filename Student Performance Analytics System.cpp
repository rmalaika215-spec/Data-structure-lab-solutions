#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Stu {
    int id;
    char name[100];
    char dept[10];
    int sem;
    float gpa;
    int cred;
    int yr;
    Stu* nxt;
};

Stu* first = nullptr;
int total = 0;

// --- LINKED LIST UTILITIES ---

void load() {
    ifstream in("students_data.txt");
    if (!in) {
        cout << "Error: students_data.txt not found!\n";
        return;
    }
    in >> total;
    Stu* lastone = nullptr;
    for (int i = 0; i < total; i++) {
        Stu* n = new Stu;
        in >> n->id;
        in.ignore(); // skip space
        
        // Read name carefully
        char firstN[50], lastN[50];
        in >> firstN >> lastN;
        strcpy(n->name, firstN);
        strcat(n->name, " ");
        strcat(n->name, lastN);
        
        in >> n->dept >> n->sem >> n->gpa >> n->cred >> n->yr;
        n->nxt = nullptr;
        if (!first) first = n;
        else lastone->nxt = n;
        lastone = n;
    }
    in.close();
}

Stu* duplicateList(Stu* head) {
    if (!head) return nullptr;
    Stu* newHead = nullptr;
    Stu* newLast = nullptr;
    while (head) {
        Stu* n = new Stu;
        *n = *head;
        n->nxt = nullptr;
        if (!newHead) newHead = n;
        else newLast->nxt = n;
        newLast = n;
        head = head->nxt;
    }
    return newHead;
}

void freeList(Stu* head) {
    while (head) {
        Stu* t = head;
        head = head->nxt;
        delete t;
    }
}

// --- MERGE SORT IMPLEMENTATION (O(n log n)) ---
// Selection sort is too slow for 1,000,000 records.



Stu* split(Stu* head) {
    Stu* fast = head;
    Stu* slow = head;
    while (fast->nxt && fast->nxt->nxt) {
        fast = fast->nxt->nxt;
        slow = slow->nxt;
    }
    Stu* temp = slow->nxt;
    slow->nxt = nullptr;
    return temp;
}

// 1. Merge for CGPA (File 1)
Stu* mergeCGPA(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    bool aBetter = (a->gpa > b->gpa) || (a->gpa == b->gpa && a->cred > b->cred);
    if (aBetter) {
        a->nxt = mergeCGPA(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeCGPA(a, b->nxt);
        return b;
    }
}

// 2. Merge for Year (File 2)
Stu* mergeYear(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    bool aBetter = (a->yr < b->yr) || (a->yr == b->yr && a->id < b->id);
    if (aBetter) {
        a->nxt = mergeYear(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeYear(a, b->nxt);
        return b;
    }
}

// 3. Merge for Dept (File 3)
Stu* mergeDept(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    int d = strcmp(a->dept, b->dept);
    bool aBetter = (d < 0) || (d == 0 && a->sem < b->sem) || (d == 0 && a->sem == b->sem && a->gpa > b->gpa);
    if (aBetter) {
        a->nxt = mergeDept(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeDept(a, b->nxt);
        return b;
    }
}

// 4. Merge for Name (File 4)
Stu* mergeName(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    if (strcmp(a->name, b->name) <= 0) {
        a->nxt = mergeName(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeName(a, b->nxt);
        return b;
    }
}

// Generic MergeSort caller
typedef Stu* (*MergeFunc)(Stu*, Stu*);
Stu* mergeSort(Stu* head, MergeFunc m) {
    if (!head || !head->nxt) return head;
    Stu* second = split(head);
    return m(mergeSort(head, m), mergeSort(second, m));
}

// --- FILE GENERATION ---

void makeFile1() {
    Stu* copy = mergeSort(duplicateList(first), mergeCGPA);
    ofstream out("ranked_by_cgpa.txt");
    out << left << setw(6) << "Rank" << " | " << setw(8) << "ID" << " | " << setw(20) << "Name" << " | " << setw(5) << "Dept" << " | " << "GPA\n";
    int r = 1;
    for (Stu* c = copy; c; c = c->nxt) {
        out << left << setw(6) << r++ << " | " << setw(8) << c->id << " | " << setw(20) << c->name << " | " << setw(5) << c->dept << " | " << fixed << setprecision(2) << c->gpa << "\n";
    }
    freeList(copy);
}

void makeFile2() {
    Stu* copy = mergeSort(duplicateList(first), mergeYear);
    ofstream out("sorted_by_enrollment.txt");
    int curYr = -1; float sum = 0; int cnt = 0;
    for (Stu* c = copy; c; c = c->nxt) {
        if (c->yr != curYr) {
            if (curYr != -1) out << "Avg CGPA for " << curYr << ": " << (sum / cnt) << "\n\n";
            curYr = c->yr; sum = 0; cnt = 0;
            out << "=== Year " << curYr << " ===\n";
        }
        out << c->id << " " << c->name << " " << c->gpa << "\n";
        sum += c->gpa; cnt++;
    }
    if (cnt > 0) out << "Avg CGPA for " << curYr << ": " << (sum / cnt) << "\n";
    freeList(copy);
}

void makeFile3() {
    Stu* copy = mergeSort(duplicateList(first), mergeDept);
    ofstream out("department_analysis.txt");
    char curDep[10] = ""; int depCnt = 0; float sumG = 0;
    for (Stu* c = copy; c; c = c->nxt) {
        if (strcmp(c->dept, curDep) != 0) {
            if (depCnt > 0) out << "Dept Avg: " << (sumG / depCnt) << "\n\n";
            strcpy(curDep, c->dept); sumG = 0; depCnt = 0;
            out << "=== Dept: " << curDep << " ===\n";
        }
        out << c->name << " GPA: " << c->gpa << "\n";
        sumG += c->gpa; depCnt++;
    }
    freeList(copy);
}

void makeFile4() {
    Stu* tiers[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    const char* titles[] = {"Elite", "High Achiever", "Good Standing", "Satisfactory", "Needs Improvement"};
    
    for (Stu* c = first; c; c = c->nxt) {
        Stu* n = new Stu; *n = *c; n->nxt = nullptr;
        int idx = (c->gpa >= 3.7) ? 0 : (c->gpa >= 3.3) ? 1 : (c->gpa >= 3.0) ? 2 : (c->gpa >= 2.5) ? 3 : 4;
        n->nxt = tiers[idx]; tiers[idx] = n;
    }

    ofstream out("performance_tiers.txt");
    for (int i = 0; i < 5; i++) {
        tiers[i] = mergeSort(tiers[i], mergeName);
        out << "--- " << titles[i] << " ---\n";
        for (Stu* c = tiers[i]; c; c = c->nxt) out << c->name << " (" << c->gpa << ")\n";
        out << endl;
        freeList(tiers[i]);
    }
}

int main() {
    cout << "Loading records..." << endl;
    load();
    if (!first) return 1;
    
    cout << "Sorting and generating files (this will be fast)..." << endl;
    makeFile1();
    makeFile2();
    makeFile3();
    makeFile4();
    
    freeList(first);
    cout << "Success! All files generated.\n";
    return 0;
}
