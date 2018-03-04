#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>

using namespace std;

map< pair<int,int> , int >pairs;

class Restaurant{
public:
    int cost, r_sat;
};

class Student{
    public:
        int id,M,F,X,Y,Z;
        int min_cost, min_id;
        vector<Restaurant> restaurants;

        // <id,strength>
        vector< pair<int,int > >relations;
        vector<int>days;
};

vector<Student>students;
vector<int>days[30][101];

int S,R,C;

void readInput(){

    scanf("%d %d %d" , &S, &R, &C);
    for(int i=0;i<S;i++){

        Student s;
        scanf("%d %d %d %d %d %d", &s.id, &s.M, &s.F, &s.X, &s.Y, &s.Z);

        s.restaurants.resize(R+1);
        s.relations.resize(s.F);
        s.min_cost = C;
        s.min_id = 0;

        for(int j=1;j<=R;j++){
            scanf("%d" , &s.restaurants[j].cost );
            if( s.restaurants[j].cost < s.min_cost ) {
                s.min_cost = s.restaurants[j].cost;
                s.min_id = j;
            }
        }
        for(int j=1;j<=R;j++)    scanf("%d" , &s.restaurants[j].r_sat );

        for(int j=0;j<30;j++)   scanf("%d" , &s.restaurants[0].r_sat );
        s.restaurants[0].cost = C;

        for(int j=0;j<s.F;j++) {
            scanf("%d %d", &s.relations[j].first, &s.relations[j].second);
            pairs[ make_pair(s.id, s.relations[j].first) ] = s.relations[j].second;
        }

        students.push_back(s);
    }

    return;
}

void optimize(){

    int best_place;
    double best_place_score;
    int c,d;

    for(int i=0;i<students.size();i++){

        students[i].days.resize(30);

        for(int j=0;j<students[i].days.size();j++){

            best_place = students[i].min_id;
            best_place_score =   students[i].X*students[i].restaurants[best_place].r_sat
                               - students[i].Y*students[i].restaurants[best_place].cost;

            for(int k=0;k<=R;k++){

                c = 0;
                d = 0;

                for(int si=0; si<days[j][k].size(); si++)
                    if( pairs[ make_pair( students[i].id , days[j][k][i] ) ] != 0 ){
                        c += pairs[ make_pair( students[i].id , days[j][k][i] ) ];
                        d++;
                    }

                double score =   students[i].X*students[i].restaurants[k].r_sat
                            - students[i].Y*students[i].restaurants[k].cost
                            + students[i].Z*(double(c)/days[j][k].size());

                if(score > best_place_score &&
                   (30-j-1)*students[i].min_cost < students[i].M-students[i].restaurants[k].cost){
                    best_place_score = score;
                    best_place = k;
                }

            }

            students[i].days[j] = best_place;
            students[i].M -= students[i].restaurants[best_place].cost;
            days[j][best_place].push_back(students[i].id);

        }

    }

    return;

}

void print(){

    for(int i=0;i<students.size();i++){

        printf("%d ", students[i].id);
        for(int j=0;j<students[i].days.size();j++)
            printf("%d " , students[i].days[j]);
        puts("");

   //     cout<<" ** "<< students[i].M<< "**"<<endl;

    }

    return;

}

int main(){

    readInput();
    optimize();
    print();

}
