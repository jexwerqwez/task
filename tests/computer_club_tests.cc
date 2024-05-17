#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/computer_club.h"

std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

void compareFiles(const std::string& outputFile, const std::string& expectedFile) {
    std::vector<std::string> outputLines = readFile(outputFile);
    std::vector<std::string> expectedLines = readFile(expectedFile);

    ASSERT_EQ(outputLines.size(), expectedLines.size()) << "Line count mismatch between " << outputFile << " and " << expectedFile;

    for (size_t i = 0; i < outputLines.size(); ++i) {
        EXPECT_TRUE(expectedLines[i].find(outputLines[i]) != std::string::npos) << "Line " << i + 1 << " mismatch:\n"
                                                    << "Output: " << outputLines[i] << "\n"
                                                    << "Expected: " << expectedLines[i];
    }
}

class ComputerClubTest : public ::testing::Test {
 protected:
    void runTest(const std::string& testInput, const std::string& expectedOutput) {
        std::string command = "./main " + testInput + " > output.txt";
        int result = system(command.c_str());
        ASSERT_EQ(result, 0) << "Execution of the command failed: " << command;
        compareFiles("output.txt", expectedOutput);
    }
};


TEST_F(ComputerClubTest, Test1) {
    runTest("tests/test_file1_in.txt", "tests/test_file1_out.txt");
}

TEST_F(ComputerClubTest, Test2) {
    runTest("tests/test_file2_in.txt", "tests/test_file2_out.txt");
}

TEST_F(ComputerClubTest, Test3) {
    runTest("tests/test_file3_in.txt", "tests/test_file3_out.txt");
}

TEST_F(ComputerClubTest, Test4) {
    runTest("tests/test_file4_in.txt", "tests/test_file4_out.txt");
}

TEST_F(ComputerClubTest, Test5) {
    runTest("tests/test_file5_in.txt", "tests/test_file5_out.txt");
}

TEST_F(ComputerClubTest, Test6) {
    runTest("tests/test_file6_in.txt", "tests/test_file6_out.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
