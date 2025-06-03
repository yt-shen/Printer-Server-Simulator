#pragma once
// PrintJob represents a print task
struct PrintJob {
    int id;
    int pages;
    int priority;

    // Define comparison operator: higher priority means higher precedence
    bool operator<(const PrintJob& other) const {
        return priority < other.priority;
    }
};