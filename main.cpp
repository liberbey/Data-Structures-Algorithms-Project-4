#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>

using namespace std;
typedef pair<pair<int, int>, int> myPair;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

float findAmount(const vector<string> words)
{
    float return_value = 0;
    for(int i=0; i< words.size(); i++){
        if (words[i][0] == '$') {
            const char *cstr = (words[i].substr(1)).c_str();
            return_value = strtof(cstr, NULL);
            //        cout << "return_value: " << return_value << endl;
            break;
        }
    }
    return return_value;
}

struct compare{

                bool operator()(myPair a, myPair b){

                    return a.second > b.second;

                }

            };


int main(int argc, char* argv[]) {


    ifstream infile(argv[1]);
    string line;
    vector<string> input;
    getline(infile, line);
    vector<string> words;
    split1(line, words);
    int M = stoi(words[0]);
    int N = stoi(words[1]);

    int** myArray = new int*[M];
    for(int j = 0; j < M; j++){
        myArray[j] = new int[N];
    }

    for (int i = 0; i < M; i++) {

        getline(infile, line);
        vector<string> words1;
        split1(line, words1);
        for(int j = 0; j < N; j++){

            myArray[i][j] =stoi(words1[j]);
            //cout << myArray[i][j];
        }
        //cout<<endl;

    }

    getline(infile, line);
    vector<string> words2;
    split1(line, words2);
    int num = stoi(words2[0]);

    vector<int> results;

    for (int i = 0; i < num; i++){

        getline(infile, line);
        vector<string> words2;
        split1(line, words2);
        int x1 = stoi(words2[0])-1;
        int y1 = stoi(words2[1])-1;
        int x2 = stoi(words2[2])-1;
        int y2 = stoi(words2[3])-1;
        //myArray;
        int** distance = new int*[M];
        for(int j = 0; j < M; j++){
            distance[j] = new int[N];
        }
        bool** visited = new bool*[M];
        for(int j = 0; j < M; j++){
            visited[j] = new bool[N];
        }
        for(int j = 0; j<M; j++){
            for (int k = 0; k<N;k++){
                distance[j][k] = -1;
                visited[j][k] = false;
            }
        }
        priority_queue<myPair, vector<myPair> , compare> pq;
        pq.push(make_pair(make_pair(x1,y1), 0));
        while(!pq.empty()){

            myPair temp = pq.top();
            pq.pop();
            int tempX = temp.first.first;
            int tempY = temp.first.second;
            int dist = temp.second;
            if(!visited[tempX][tempY]) {
                visited[tempX][tempY] = true;
                if (distance[tempX][tempY] == -1) {
                    distance[tempX][tempY] = dist;
                } else {
                    distance[tempX][tempY] = min(distance[tempX][tempY], dist);
                }
                if (tempX == x2 && tempY == y2) {
                    results.push_back(distance[x2][y2]);
                    break;
                }
                if (tempX != 0 && tempY != 0 && tempX != M-1 && tempY != N-1) {

                    if (!visited[tempX - 1][tempY])pq.push(make_pair(make_pair(tempX - 1, tempY),
                                                                     max(abs(myArray[tempX - 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX + 1][tempY]) pq.push(make_pair(make_pair(tempX + 1, tempY),
                                                                     max(abs(myArray[tempX + 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY - 1])pq.push(make_pair(make_pair(tempX, tempY - 1),
                                                                     max(abs(myArray[tempX][tempY - 1] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY] + 1)pq.push(make_pair(make_pair(tempX, tempY + 1),
                                                                     max(abs(myArray[tempX][tempY + 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX == 0 && tempY != 0 && tempX != M-1 && tempY != N-1) {
                    if (!visited[tempX + 1][tempY])pq.push(make_pair(make_pair(tempX + 1, tempY),
                                                                     max(abs(myArray[tempX + 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY - 1])pq.push(make_pair(make_pair(tempX, tempY - 1),
                                                                     max(abs(myArray[tempX][tempY - 1] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY] + 1)pq.push(make_pair(make_pair(tempX, tempY + 1),
                                                                     max(abs(myArray[tempX][tempY + 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX != 0 && tempY == 0 && tempX != M-1 && tempY != N-1) {
                    if (!visited[tempX - 1][tempY])pq.push(make_pair(make_pair(tempX - 1, tempY),
                                                                     max(abs(myArray[tempX - 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX + 1][tempY])pq.push(make_pair(make_pair(tempX + 1, tempY),
                                                                     max(abs(myArray[tempX + 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY] + 1)pq.push(make_pair(make_pair(tempX, tempY + 1),
                                                                     max(abs(myArray[tempX][tempY + 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX != 0 && tempY != 0 && tempX == M-1 && tempY != N-1) {
                    if (!visited[tempX - 1][tempY])pq.push(make_pair(make_pair(tempX - 1, tempY),
                                                                     max(abs(myArray[tempX - 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY - 1])pq.push(make_pair(make_pair(tempX, tempY - 1),
                                                                     max(abs(myArray[tempX][tempY - 1] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY] + 1)pq.push(make_pair(make_pair(tempX, tempY + 1),
                                                                     max(abs(myArray[tempX][tempY + 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX != 0 && tempY != 0 && tempX != M-1 && tempY == N-1) {
                    if (!visited[tempX - 1][tempY])pq.push(make_pair(make_pair(tempX - 1, tempY),
                                                                     max(abs(myArray[tempX - 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX + 1][tempY])pq.push(make_pair(make_pair(tempX + 1, tempY),
                                                                     max(abs(myArray[tempX + 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY - 1])pq.push(make_pair(make_pair(tempX, tempY - 1),
                                                                     max(abs(myArray[tempX][tempY - 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX == 0 && tempY == 0 && tempX != M-1 && tempY != N-1) {

                    if (!visited[tempX + 1][tempY]) pq.push(make_pair(make_pair(tempX + 1, tempY),
                                                                      max(abs(myArray[tempX + 1][tempY] -
                                                                              myArray[tempX][tempY]), dist)));

                    if (!visited[tempX][tempY] + 1)pq.push(make_pair(make_pair(tempX, tempY + 1),
                                                                     max(abs(myArray[tempX][tempY + 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX == 0 && tempY != 0 && tempX != M-1 && tempY == N-1) {
                    if (!visited[tempX + 1][tempY])pq.push(make_pair(make_pair(tempX + 1, tempY),
                                                                     max(abs(myArray[tempX + 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY - 1])pq.push(make_pair(make_pair(tempX, tempY - 1),
                                                                     max(abs(myArray[tempX][tempY - 1] -
                                                                             myArray[tempX][tempY]), dist)));
                } else if (tempX != 0 && tempY == 0 && tempX == M-1 && tempY != N-1) {
                    if (!visited[tempX - 1][tempY])pq.push(make_pair(make_pair(tempX - 1, tempY),
                                                                     max(abs(myArray[tempX - 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));
                    if (!visited[tempX][tempY] + 1)pq.push(make_pair(make_pair(tempX, tempY + 1),
                                                                     max(abs(myArray[tempX][tempY + 1] -
                                                                             myArray[tempX][tempY]), dist)));

                } else if (tempX != 0 && tempY != 0 && tempX == M-1 && tempY == N-1) {

                    if (!visited[tempX - 1][tempY])pq.push(make_pair(make_pair(tempX - 1, tempY),
                                                                     max(abs(myArray[tempX - 1][tempY] -
                                                                             myArray[tempX][tempY]), dist)));

                    if (!visited[tempX][tempY - 1])pq.push(make_pair(make_pair(tempX, tempY - 1),
                                                                     max(abs(myArray[tempX][tempY - 1] -
                                                                             myArray[tempX][tempY]), dist)));

                }
            }




        }

    }

    ofstream myfile;
    myfile.open(argv[2]);

    for(int i = 0; i < results.size(); i++){
        myfile << results[i] << endl;

    }





    return 0;
}