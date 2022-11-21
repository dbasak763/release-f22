/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    std::string fileString = file_to_string(filename);
    std::vector<std::string> lines_;
    int lines = SplitString(fileString, '\n', lines_);
    V2D vect = V2D();
    //std::vector<std::vector<std::string>> is V2D
    for (int i = 0; i < lines; i++) {
        std::string courses_line = Trim(lines_[i]);
        std::vector<std::string> words_;
        int words = SplitString(courses_line, ',' , words_);
        for (std::vector<std::string>::iterator it = words_.begin(); it != words_.end(); it++) {
            *it = TrimLeft(*it);
        }
        vect.push_back(words_);
    }
    return vect;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
 //std::vector<std::vector<std::string>> is V2D
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
   
    
    //need a mapping from student to which courses they are taking
    std::map<std::string, std::vector<std::string>> map; 
    for (unsigned s = 0; s < student.size(); s++) {
        std::vector<std::string> courses_;
        for (unsigned i = 1; i < student[s].size(); i++) {
            courses_.push_back(student[s][i]);
        }
        map.insert({student[s][0], courses_});
    }
    V2D valid_course_roster = V2D(cv.size());
    //for all courses, check if all students within that course are valid or not, if they are not valid, 
    //remove from the course roster 
    //iterate through courses
    for (unsigned course = 0; course < cv.size(); course++) {
        std::string course_id = cv[course][0];
        valid_course_roster[course].push_back(course_id);
        //iterate through students within the course
        for (unsigned i = 1; i < cv[course].size(); i++) {
            std::string student_ = cv[course][i];
            std::vector<std::string> v = map[student_];
            //if a student within a course maps to a course, then it is valid
            //add to valid_course_roster list
            if (std::find(v.begin(), v.end(), course_id) != v.end()) {
                valid_course_roster[course].push_back(student_);
            }
        }  
    }
    //else, move on to next student
    //at the end, check if courses are empty, and remove them
    for (unsigned course = 0; course < valid_course_roster.size(); course++) {
        if (valid_course_roster[course].size() == 1) {
            valid_course_roster.erase(valid_course_roster.begin() + course);
            course--;

        }
    }
    return valid_course_roster;

}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    return V2D();
}